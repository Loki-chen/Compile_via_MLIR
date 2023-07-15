#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Support/LLVM.h"



namespace mlir {
namespace compiler {
namespace WarpEntryPoint {

    void buildTransformPassPipeline(OpPassManager &passManager);

    void registerTransformPassPipeline();

    // Converts streamable ops in dialects into their nisl dialect forms.
    std::unique_ptr<OperationPass<ModuleOp>> createWrapEntryPointsOpsPass();

    // Wraps all entry points in a function
    // std::unique_ptr<OperationPass<ModuleOp>> createWrapEntryPointsPass();

    inline void registerPasses(){
        //regist pass
        createWrapEntryPointsOpsPass();
        // createWrapEntryPointsPass();
        //regist pipeline
        registerTransformPassPipeline();
    }
}   // namespace WarpEnrtyPoint
}   // namespace compiler
}  // namespace mlir