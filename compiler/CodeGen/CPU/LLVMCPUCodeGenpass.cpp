

#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm-c/Core.h"
#include "llvm-c/Types.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/Triple.h"
#include <memory>
#include <iostream>

#include "mlir/Target/LLVMIR/Dialect/Builtin/BuiltinToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Export.h"

// struct LLVMTarget {
//   std::string triple;
//   std::string data_layout;
// };

// LLVMTarget getmoudleOpTarget(mlir::ModuleOp moudleOp) {
//     auto configAttr = moudleOp;
//     auto tryAttrLookup = [&](llvm::StringRef name, llvm::StringRef fallback);

//     LLVMTarget target;
//     target.triple = tryAttrLookup("llvm.target_triple", "x86_64-unknown-unknown-eabi-elf");
//     target.data_layout =
//         tryAttrLookup("llvm.data_layout", "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128");
//     return target;
//   }
// llvm.data_layout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128", llvm.target_triple = "x86_64-unknown-unknown-eabi-elf"
// // target = 0
// <"llvm-cpu", "embedded-elf-x86_64", 
// {
//     cpu = "generic", 
//     cpu_features = "", 
//     data_layout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128", 
//     native_vector_size = 16 : index, 
//     target_triple = "x86_64-unknown-unknown-eabi-elf", 
//     ukernels = false}> 

/**
static void setMLIRDataLayout(mlir::ModuleOp &mlirModule,
                              const llvm::DataLayout &dl) {
  mlir::MLIRContext *context = mlirModule.getContext();
  mlirModule->setAttr(
      mlir::LLVM::LLVMDialect::getDataLayoutAttrName(),
      mlir::StringAttr::get(context, dl.getStringRepresentation()));
  mlir::DataLayoutSpecInterface dlSpec = mlir::translateDataLayout(dl, context);
  mlirModule->setAttr(mlir::DLTIDialect::kDataLayoutAttrName, dlSpec);
}
*/

  // Additional target information besides that is contained in
  // LLVMTargetOptions options_.
struct ConvertFuncToLLVMPassOptions {
  bool useBarePtrCallConv = false;
  unsigned indexBitwidth = 0;
  std::string dataLayout = "";
  bool useOpaquePointers = true;
}option_;




namespace mlir {
namespace compiler {
namespace CPUCodeGen {

class LLVMCpuCodeGenPass : public PassWrapper<LLVMCpuCodeGenPass, OperationPass<mlir::ModuleOp>>{
    public:
        LLVMCpuCodeGenPass() = default;
    StringRef getArgument() const override{
        return "nisl-cpu-codegen-pass";
    }

    StringRef getDescription() const override{
        return "llvm.mlir.constant ops to  load ptr";
    }

    void runOnOperation() override {
        auto moduleOp = getOperation();

        llvm::LLVMContext context;
        SmallVector<Attribute> targetAttrs; 
        
        // Attribute tripleValue = LLVMTypeRef.getSymbolAttrName;

        moduleOp->setAttr(LLVM::LLVMDialect::getDataLayoutAttrName(), nullptr);
        moduleOp->setAttr(LLVM::LLVMDialect::getTargetTripleAttrName(), nullptr);
        
    }
};

std::unique_ptr<OperationPass<ModuleOp>> createLLVMCpuCodeGenPass(){
    return std::make_unique<LLVMCpuCodeGenPass>();
}

// static PassRegistration<LLVMCpuCodeGenPass> pass;

static PassRegistration<LLVMCpuCodeGenPass> pass([] {
  return std::make_unique<LLVMCpuCodeGenPass>();
});
}
}
}