
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "nisl_compile_lib.h"

#include <stdio.h>
#include <stdlib.h>

#include <atomic>
#include <limits>


#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

#include "llvm/ADT/SparseBitVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support//InitLLVM.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/Allocator.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/ToolOutputFile.h"


#include "mlir/Conversion/TosaToArith/TosaToArith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Shape/Transforms/Passes.h"
#include "mlir/Dialect/Tosa/Transforms/Passes.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/Region.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Support/FileUtilities.h"
#include "mlir/Support/LogicalResult.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/IR/OwningOpRef.h"
#include "mlir/IR/Diagnostics.h"  // emitError
#include "mlir/IR/Verifier.h"    // mlir::verify
#include "Tools/init_dialects.h"
#include "Tools/init_passes.h"
#include "Tools/init_llvmir_translations.h"


#include "Pipelines/Pipelines.h"



namespace mlir{
namespace compiler {

/*-------------------------------------------------------------------------------
 nisl-compiler-main-embed
---------------------------------------------------------------------------------*/



/*----------------------------------------
 nisl-compiler-GlobalInit
------------------------------------------*/

struct GlobalInit {
  GlobalInit();
  ~GlobalInit() { llvm::llvm_shutdown(); }
  void registerCommandLineOptions();

  // Command line handling.
  bool usesCommandLine = false;

  mlir::DialectRegistry registry;
};


GlobalInit::GlobalInit() {
  // Global/static registrations.
  mlir::compiler::registerAllPasses();

  mlir::compiler::registerAllDialects(registry);
  mlir::compiler::registerLLVMIRTranslactions(registry);
}

void GlobalInit::registerCommandLineOptions(){
  // Register MLIRContext command-line options like
  // -mlir-print-op-on-diagnostic.
  mlir::registerMLIRContextCLOptions();
  // Register assembly printer command-line options like
  // -mlir-print-op-generic.
  mlir::registerAsmPrinterCLOptions();
  // Register pass manager command-line options like -mlir-print-ir-*.
  mlir::registerPassManagerCLOptions();
  mlir::registerDefaultTimingManagerCLOptions();
}


/*----------------------------------------
 nisl-compiler-Session
------------------------------------------*/
struct Session{
  Session(GlobalInit &globalInit);

  GlobalInit &globalInit;

  MLIRContext context;
  
};


Session::Session(GlobalInit &globalInit): globalInit(globalInit){
     context.appendDialectRegistry(globalInit.registry);
     context.allowsUnregisteredDialects();
     context.appendDialectRegistry(globalInit.registry);
    }



struct Error {
  Error(std::string message) : message(std::move(message)) {}
  std::string message;
};

struct Source {
  Source(Session &session) : session(session) {}

  Error *openFile(const char *filePath);
  Error *wrapBuffer(const char *bufferName, const char *buffer, size_t length,
                    bool isNullTerminated);
  Error *split(void (*callback)(Source *source, void *userData),
               void *userData);
  const llvm::MemoryBuffer *getMemoryBuffer() {
    return sourceMgr.getMemoryBuffer(1);
  }

  Session &session;
  llvm::SourceMgr sourceMgr;
};


Error *Source::openFile(const char *filePath) {
  std::string err;
  std::unique_ptr<llvm::MemoryBuffer> memoryBuffer =
      mlir::openInputFile(llvm::StringRef(filePath, strlen(filePath)), &err);
  if (!memoryBuffer) {
    return new Error(std::move(err));
  }
  sourceMgr.AddNewSourceBuffer(std::move(memoryBuffer), llvm::SMLoc());
  return nullptr;
}

Error *Source::wrapBuffer(const char *bufferName, const char *buffer,
                          size_t length, bool isNullTerminated) {
  std::unique_ptr<llvm::MemoryBuffer> memoryBuffer;
  if (isNullTerminated) {
    // Sharp edge: MemoryBuffer::getMemBuffer will peek one past the passed
    // length to verify a null terminator, but this makes the API really hard to
    // ensure memory safety for. For our API, we just require that the buffer is
    // null terminated and that the null is included in the length. We then
    // subtract by 1 when constructing the underlying MemoryBuffer. This is
    // quite sad :(
    if (length == 0 || buffer[length - 1] != 0) {
      return new Error("expected null terminated buffer");
    }
    memoryBuffer = llvm::MemoryBuffer::getMemBuffer(
        StringRef(buffer, length - 1),
        StringRef(bufferName, strlen(bufferName)),
        /*RequiresNullTerminator=*/true);
  } else {
    // Not a null terminated buffer.
    memoryBuffer = llvm::MemoryBuffer::getMemBuffer(
        StringRef(buffer, length), StringRef(bufferName, strlen(bufferName)),
        /*RequiresNullTerminator=*/false);
  }
  sourceMgr.AddNewSourceBuffer(std::move(memoryBuffer), llvm::SMLoc());
  return nullptr;
}

Error *Source::split(void (*callback)(Source *source,
                                      void *userData),
                     void *userData) {
  const char splitMarkerConst[] = "// -----";
  StringRef splitMarker(splitMarkerConst);

  // This code is adapted from splitAndProcessBuffer which needs to be
  // refactored to be usable. It omits the fuzzy check for near misses
  // because it is very complicated and it is not obvious what it is doing.
  auto *origMemBuffer = getMemoryBuffer();
  SmallVector<StringRef, 8> rawSubBuffers;
  // Split dropping the last checkLen chars to enable flagging near misses.
  origMemBuffer->getBuffer().split(rawSubBuffers, splitMarker);
  if (rawSubBuffers.empty()) return nullptr;

  for (StringRef subBuffer : rawSubBuffers) {
    auto splitLoc = SMLoc::getFromPointer(subBuffer.data());
    unsigned splitLine = sourceMgr.getLineAndColumn(splitLoc).first;
    auto subMemBuffer = llvm::MemoryBuffer::getMemBufferCopy(
        subBuffer, Twine("within split at ") +
                       origMemBuffer->getBufferIdentifier() + ":" +
                       Twine(splitLine) + " offset ");

    Source *subSource = new Source(session);
    subSource->sourceMgr.AddNewSourceBuffer(std::move(subMemBuffer),
                                            llvm::SMLoc());
    callback((Source *)subSource, userData);
  }
  return nullptr;
}




struct Output {
  enum class Type {
    None,
    File,
    Membuffer,
  };

  ~Output();
  Error *openFile(const char *filePath);
  Error *openFD(int fd);
  Error *openMembuffer();
  void keep();

  Error *getWriteError() {
    if (type == Type::File && outputFile->os().has_error()) {
      return new Error(outputFile->os().error().message());
    }
    return nullptr;
  }

  Error *mapMemory(void **data, uint64_t *size) {
    if (type == Type::Membuffer) {
      stringOutputStream->flush();
      *data = static_cast<void *>(&outputString[0]);
      *size = outputString.size();
      return nullptr;
    } else if (type == Type::File) {
#if !NISL_COMPILER_USE_MMAP
      return new Error(
          "Mapping memory of a compiler output not created via "
          "ireeCompilerOutputOpenMembuffer is not supported on this platform");
#else
      if (!this->mapped_data) {
        if (!backingFileDescriptor) {
          return new Error(
              "Output was not opened against a file descriptor and cannot be "
              "mapped");
        }
        outputFile->os().flush();
        if (auto *error = getWriteError()) {
          return error;
        }

        this->mapped_size = lseek(*backingFileDescriptor, 0, SEEK_END);
        if (this->mapped_size == -1 ||
            this->mapped_size >= std::numeric_limits<size_t>::max()) {
          return new Error(
              "Failed to determine size of backing file descriptor");
        }
        void *mmap_result =
            mmap(nullptr, static_cast<size_t>(mapped_size), PROT_READ,
                 MAP_SHARED, *backingFileDescriptor, 0);
        if (mmap_result == MAP_FAILED) {
          return new Error("Failed to mmap file descriptor");
        }
        this->mapped_data = mmap_result;
      }
      *data = this->mapped_data;
      *size = this->mapped_size;
      return nullptr;
#endif
    } else {
      return new Error("Output was not opened in a way that supports mapping");
    }
  }

  Type type = Type::None;
  // Description of the output. If a file, this will be the file path.
  // Otherwise, it will be some debug-quality description.
  std::string description;
  llvm::raw_ostream *outputStream = nullptr;

  // If we have mapped the output, the mapping is stashed here.
  void *mapped_data = nullptr;
  uint64_t mapped_size = 0;

 private:
  // Fields for Type::File.
  // If the output was configured to a file, this is it.
  std::unique_ptr<llvm::ToolOutputFile> outputFile;
  // File descriptor if opened in a way where one was provided.
  std::optional<int> backingFileDescriptor;

  // Fields for Type::Memory.
  std::string outputString;
  std::optional<llvm::raw_string_ostream> stringOutputStream;
};

Output::~Output() {
#if NISL_COMPILER_USE_MMAP
  if (mapped_data) {
    munmap(mapped_data, static_cast<size_t>(mapped_size));
  }
#endif
}

Error *Output::openFile(const char *filePath) {
  std::string err;
  type = Type::File;
  description = filePath;
  outputFile = mlir::openOutputFile(description, &err);
  if (!outputFile) {
    return new Error(std::move(err));
  }
  outputStream = &outputFile->os();
  return nullptr;
}

Error *Output::openFD(int fd) {
  type = Type::File;
  description = "fd-";
  description.append(std::to_string(fd));
  outputFile = std::make_unique<llvm::ToolOutputFile>(description, fd);
  // Don't try to delete, etc.
  outputFile->keep();
  outputStream = &outputFile->os();
  this->backingFileDescriptor = fd;
  return nullptr;
}

Error *Output::openMembuffer() {
#if IREE_COMPILER_USE_MEMFD_CREATE
  int fd = memfd_create("nisl_output.bin", 0);
  if (fd == -1) {
    return new Error("Error creating membuffer output via memfd_create");
  }
  return openFD(fd);
#else
  // Fallback to an std::string based accumulator if no platform support
  // for memfiles.
  type = Type::Membuffer;
  stringOutputStream.emplace(outputString);
  outputStream = &(*stringOutputStream);
  return nullptr;
#endif
}

void Output::keep() {
  if (outputFile) outputFile->keep();
}


enum compilerPipeline{
  NISL_COMPILER_PIPELINE_STD = 0,
  NISL_COMPILER_PIPELINE_HAL_EXECUTABLE = 1,
};


struct Invocation{
  Invocation(Session &session);
  bool parseSource(Source &source);
  bool runPipeline(enum compilerPipeline pipeline);

  Session &session;
  PassManager passManager;

  OwningOpRef<Operation *>  parsedModule;
};



Invocation::Invocation(Session &session)
  :session(session),
  passManager(&session.context){
  if (session.globalInit.usesCommandLine) {
    if (failed(mlir::applyPassManagerCLOptions(passManager))) {
      emitError(UnknownLoc::get(&session.context))
          << "Failed to apply pass manager CL options";
    }
    mlir::applyDefaultTimingPassManagerCLOptions(passManager);
  }
}




bool Invocation::parseSource(Source &source){
  parsedModule = mlir::parseSourceFile<ModuleOp>(source.sourceMgr, &session.context);
  if (!parsedModule || failed(mlir::verify(*parsedModule))) {
    return false;
  }
  return true;
}


bool Invocation::runPipeline(enum compilerPipeline pipeline){
std::cout<<"nisl-compile-runMain-runPipepline!"<<std::endl;
      session.context.allowsUnregisteredDialects();

      passManager.addPass(tosa::createTosaToArith());

  switch (pipeline) {
    case NISL_COMPILER_PIPELINE_STD:{
      /*  nisl-compile Pipeline  */
      // buildTOSATransformePassPipeline(passManager);

      break;
    }
    case NISL_COMPILER_PIPELINE_HAL_EXECUTABLE: {
      break;
    }
    default:
        (*parsedModule)->emitError()
          << "unsupported pipeline type " << (int)pipeline;
      return false;
  }
  
  if (failed(passManager.run(parsedModule.get()))) {
    return false;
  }
  passManager.dump();
  parsedModule.get()->dump();
  return true;
}


} // namespace compiler
} // namespace mlir





/*-------------------------------------------------------------------------------
 nisl-compiler-main
---------------------------------------------------------------------------------*/
int mlir::compiler::nislRunMain(int argc, char **argv) {
  std::cout<<"nisl-compile-runMain!"<<std::endl;
  static llvm::cl::OptionCategory mainOptions("NISL Main Options");

  llvm::cl::opt<std::string> inputFilename(
    llvm::cl::Positional, 
    llvm::cl::desc("<Input file or '-' for stdin"),
    llvm::cl::Required, 
    llvm::cl::cat(mainOptions)
  );

  llvm::cl::opt<std::string> outputFilename(
    "o", 
    llvm::cl::desc("Output filename"), 
    llvm::cl::value_desc("filename"),
    llvm::cl::init("-"),
    llvm::cl::cat(mainOptions)
  );


  GlobalInit *globalInit = new GlobalInit();
  if (globalInit->usesCommandLine) {
      fprintf(stderr, "FATAL ERROR: nislCompileParseCL called multiple times\n");
      abort();
  }

  globalInit->usesCommandLine = true;
  globalInit->registerCommandLineOptions();

  llvm::setBugReportMsg(
      "Please report issues to https://github.com/openxla/iree/issues and "
      "include the crash backtrace.\n");
  llvm::cl::ParseCommandLineOptions(argc, argv, "NISL compilation driver\n");

  if (!globalInit) {
    fprintf(stderr, "FATAL ERROR: Not initialized\n");
    abort();
  }
  Session *session = new Session(*globalInit);
  auto source = new Source(*session);

  const char *inputfilePath = inputFilename.c_str();
  source->openFile(inputfilePath);

  /*
  auto inputfile =  llvm::StringRef(inputFilename.c_str(), strlen(inputFilename.c_str()));
  std::string inputErrorMessage = "cannot open input file '";
  mlir::openInputFile(inputfile, &inputErrorMessage);*/

  auto output = new Output();
  const char *outputfilepath = outputFilename.c_str();
  output->openFile(outputfilepath);

  /*
  std::unique_ptr<llvm::ToolOutputFile> outputFile;
  auto outputfile = outputFilename.c_str();
  std::string outputErrorMessage = "cannot open input file '";
  outputFile = mlir::openOutputFile(outputfile, &outputErrorMessage);*/

  Invocation *inv =  new Invocation(*session);

  if(!inv->parseSource(*source)) 
  {
      llvm::outs() << "parse Source faile!"
               << "\n";
    return false; 
  }

  inv->runPipeline(NISL_COMPILER_PIPELINE_STD);


  Error *outputIR = nullptr;

  











  return 0;
  }