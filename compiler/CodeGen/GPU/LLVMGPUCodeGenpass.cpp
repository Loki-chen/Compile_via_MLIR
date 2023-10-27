#include "llvm/IR/Constants.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"



#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Target/LLVMIR/Export.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Support/LogicalResult.h"



#include "CodeGen/CodeGenTools.h"
#include <iostream>
#include <string>




static llvm::cl::opt<std::string> clTargetChip(
    "nisl-cuda-llvm-target-arch", llvm::cl::desc("LLVM target chip."),
    llvm::cl::init("sm_35"));

static llvm::cl::opt<bool> dumpPtx(
    "nisl-cuda-dump-ptx", llvm::cl::init(false),
    llvm::cl::desc("Dump ptx to the debug stream."));


std::string sanitizeSymbolName(llvm::StringRef name) {
  std::string result;
  result.reserve(name.size());
  for (size_t i = 0; i < name.size(); ++i) {
    char c = name[i];
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || c == '_')) {
      c = '_';
    }
    result.push_back(c);
  }
  return result;
}



//link the Attrs into the generated code.
static mlir::LogicalResult setAttrsForLlvmFunc(mlir::Location loc, llvm::Module &module,
                                 llvm::TargetMachine &targetMachine
                                 ) {
  // Ensure consistent target information.
  const llvm::Triple &targetTriple = targetMachine.getTargetTriple();
  module.setDataLayout(targetMachine.createDataLayout());
  module.setTargetTriple(targetTriple.str());

  return mlir::success();
}





static std::string translateLlvmIRModuleToPtx(llvm::Module &module,
                                        llvm::TargetMachine &targetMachine) {
    std::string targetPtx;
    {
        llvm::raw_string_ostream stream(targetPtx);
        llvm::buffer_ostream pstream(stream);
        llvm::legacy::PassManager codegenPass;
        targetMachine.addPassesToEmitFile(codegenPass, pstream, nullptr, llvm::CGFT_AssemblyFile);
        codegenPass.run(module);
    }   
    return targetPtx;                                             
 }


namespace mlir {
namespace compiler {
namespace GPUCodeGen {

//===--------------------------------------------------------------------===//
  // Convert mlir LLVM to ptx.
  //
  // Post-conditions:
  //   - The module contains the final llvm.module ready to be serialized.
//===--------------------------------------------------------------------===//
class LLVMGpuCodeGenPass : public PassWrapper<LLVMGpuCodeGenPass, OperationPass<mlir::ModuleOp>>{

    public:
        LLVMGpuCodeGenPass() =default;
    StringRef getArgument() const override{
        return "nisl-gpu-codeGen";
        }
    StringRef getDescription() const override{
        return "llvm.mlir convert to ptx";
    }
    void runOnOperation() override;
};


void LLVMGpuCodeGenPass::runOnOperation(){

    llvm::LLVMContext context;
    auto moduleOp = getOperation(); 

    auto funcOps = moduleOp.getOps<mlir::LLVM::LLVMFuncOp>();
    std::string funcName; 
    std::string funcNames;
    if(!funcOps.empty()){
        for (auto funcOp:funcOps){
          funcName =  CodeGenTools::getfuncName(funcOp);  
          funcNames = funcOp.getName().str();
        }
    }
    // Get the register backend use mlir:lookupTarget
    std::unique_ptr<llvm::TargetMachine> targetMachine;
    {
        llvm::Triple triple("nvptx64-nvidia-cuda");
        std::string targetChip = clTargetChip;
        std::string features = "+ptx60";
        std::string error;
        const llvm::Target *target =
            llvm::TargetRegistry::lookupTarget("", triple, error);
        if (target == nullptr) {
          moduleOp.emitError() << "cannot initialize target triple";
        }

        targetMachine.reset(target->createTargetMachine(
            triple.str(), targetChip, features, {}, {}));
        if (targetMachine == nullptr) {
          moduleOp.emitError() << "cannot initialize target machine";
        }
    }


    // Remove all the functions that are not part of the CUDA kernel.
    // TODO(thomasraoux): remove this? this should not be required.
    auto illegalFuncOps =
        llvm::to_vector<4>(moduleOp.getOps<func::FuncOp>());
    for (auto funcOp : illegalFuncOps) {
        funcOp.erase();
    }


    // Convert the llvm to the LLVMIR
    auto llvmModule = mlir::translateModuleToLLVMIR(moduleOp, context, funcName);
    if (!llvmModule) {
        llvm::errs() << "failed to translate the MLIR LLVM "
                                      "dialect to the native llvm::Module";
    }

    auto *llvmFunc= llvmModule->getFunction(funcNames);
    // setName will make sure the function name is unique.
    llvmFunc->setName(sanitizeSymbolName(funcName));
    SmallVector<std::string> entryPointNames;
    entryPointNames.emplace_back(funcNames);

    auto *annotations = llvmModule->getOrInsertNamedMetadata("nvvm.annotations");
    auto setMetadataValueI32 = [&](StringRef name, int value)-> void {
        llvm::Metadata *llvmMetadata[] = {
            llvm::ValueAsMetadata::get(llvmFunc),
            llvm::MDString::get(llvmModule->getContext(), name),
            llvm::ValueAsMetadata::get(llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(llvmModule->getContext()), value))};
            annotations->addOperand(
                llvm::MDNode::get(llvmModule->getContext(), llvmMetadata));
    
    };
 
    // Mark the entry point as a kernel.
    setMetadataValueI32("kernel", 1);
    // Set the maximum number of threads in the thread block (CTA).
    setMetadataValueI32("maxntidx", 64);
    setMetadataValueI32("maxntidy", 1);
    setMetadataValueI32("maxntidz", 1);


    // Dump just the codegen LLVM IR to file etc */.bc
    StringRef path="/home/MLIR-Compiler/tests/tosa-mlir/";
    StringRef suffix="cuda";
    StringRef baseName = funcName;
    StringRef extension = "_codegen.bc";
    CodeGenTools::DumpBitCodeToFile(*llvmModule, path, suffix, baseName, extension);



    // Set Attrs for the generated module.
    if (failed(setAttrsForLlvmFunc(moduleOp.getLoc(), *llvmModule, *targetMachine ))) {
        mlir::emitError(moduleOp.getLoc())<<"Failed to set Attrs for the generated module";
      }

    
    // Serialize CUDA kernel into the binary that we will embed in the
    // final FlatBuffer.
    std::string ptxImage;
    ptxImage = translateLlvmIRModuleToPtx(*llvmModule, *targetMachine);


    // The llvm IR now has been converted to ptx by llvm backend utils.
    // Just dump the .ptx file;
    if (dumpPtx) {
      llvm::dbgs() << ptxImage;
    }
    StringRef ptx_extension = "_codegen.ptx";
    CodeGenTools::DumpDataToPath(path, baseName,suffix, ptx_extension, ptxImage);
}


void registerCUDATargetBackend(){

    LLVMInitializeNVPTXTarget();
    LLVMInitializeNVPTXTargetMC();
    LLVMInitializeNVPTXTargetInfo();
    LLVMInitializeNVPTXAsmPrinter();
}

std::unique_ptr<OperationPass<ModuleOp>> createLLVMGpuCodeGenPass(){
    return std::make_unique<LLVMGpuCodeGenPass>();
}


static PassRegistration<LLVMGpuCodeGenPass> pass([] {
  return std::make_unique<LLVMGpuCodeGenPass>();
});

  } // namespace GpuCodeGen
 }  // namespace compiler
 }  // namespcae mlir