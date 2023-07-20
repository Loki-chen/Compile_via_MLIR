#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/LLVM.h"



namespace mlir {
namespace compiler {
namespace WarpEntryPoint {

    void buildTransformPassPipeline(OpPassManager &passManager);

    void registerTransformPassPipeline();





    inline void registerPasses(){
        //regist pass

        // createWrapEntryPointsPass();
        //regist pipeline
        registerTransformPassPipeline();
    }
}   // namespace WarpEnrtyPoint
}   // namespace compiler
}  // namespace mlir