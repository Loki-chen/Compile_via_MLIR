#include "mlir/Support/FileUtilities.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/Path.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <string>



namespace mlir {
namespace compiler {
namespace CodeGenTools {
        
std::string getfuncName(mlir::LLVM::LLVMFuncOp llvmFunc){
    std::string funcName = llvmFunc.getName().str();
    if(!funcName.compare("malloc")) {
        funcName.erase();
    }
    return funcName;
}    

void DumpBitCodeToFile(const llvm::Module &llvmModule, llvm::StringRef path, llvm::StringRef suffix, llvm::StringRef baseName, llvm::StringRef extension){
        llvm::SmallVector<char, 0> data;
        llvm::raw_svector_ostream ostream(data);
        llvm::WriteBitcodeToFile(llvmModule, ostream);
        auto fileName = (llvm::join_items("_", baseName, suffix) + extension).str();
        auto fileParts = llvm::join_items(llvm::sys::path::get_separator(), path, fileName);
        auto filePath = llvm::sys::path::convert_to_slash(fileParts);
        std::string error;
        auto file = mlir::openOutputFile(filePath, &error);
        if (!file) {
            llvm::errs() << "Unable to dump debug output to " << filePath << "\n";
            return;
        }
        file->os().write(data.data(), data.size());
        file->keep();
}


void DumpDataToPath(StringRef path, StringRef baseName, StringRef suffix,
                    StringRef extension, StringRef data) {
  auto fileName = (llvm::join_items("_", baseName, suffix) + extension).str();
  auto fileParts =
      llvm::join_items(llvm::sys::path::get_separator(), path, fileName);
  auto filePath = llvm::sys::path::convert_to_slash(fileParts);
  std::string error;
  auto file = mlir::openOutputFile(filePath, &error);
  if (!file) {
    llvm::errs() << "Unable to dump debug output to " << filePath << "\n";
    return;
  }
  file->os().write(data.data(), data.size());
  file->keep();
}


}  // namespace CodeGenTools
}
}


