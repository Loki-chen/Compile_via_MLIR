#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include <string>
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Error.h"


namespace mlir {
namespace compiler {
namespace CodeGenTools {

std::string getfuncName(mlir::LLVM::LLVMFuncOp llvmFunc);
void DumpBitCodeToFile(const llvm::Module &llvmModule, llvm::StringRef path,
         llvm::StringRef suffix, llvm::StringRef baseName, llvm::StringRef extension);

}}}