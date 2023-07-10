


#include "mlir/Target/LLVMIR/Dialect/ArmNeon/ArmNeonToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/Builtin/BuiltinToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"

namespace mlir {
namespace compiler {
    inline void registerLLVMIRTranslactions(DialectRegistry &registry){
        mlir::registerBuiltinDialectTranslation(registry);
        mlir::registerLLVMDialectTranslation(registry);
        mlir::registerArmNeonDialectTranslation(registry);
    }
} // namespace compiler
} // namespace mlir