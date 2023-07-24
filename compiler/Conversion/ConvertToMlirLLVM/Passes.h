#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/LLVM.h"

namespace mlir {
namespace compiler {
namespace ConvertToMlirLLVM {

void buildTransformPassPipeline(OpPassManager &passManager);

void registerTransformPassPipeline();



inline void registerPasses(){
        //regist pass

        //regist pipeline
    registerTransformPassPipeline();

}
}   // namespace ConvertToMlirLLVM
}   // namespace compiler
}  // namespace mlir