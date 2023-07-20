


#include <memory>
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Transforms/Passes.h"


namespace mlir {
namespace compiler {
namespace WarpEntryPoint {


    void buildTransformPassPipeline(OpPassManager &passManager){
        
        // passManager.addPass();
        // passManager.addPass(createWrapEntryPointsPass());
    
    }


    void registerTransformPassPipeline(){
        PassPipelineRegistration<> transformPassPipeline(
        "nisl-warpentrypoint-transformation-pipeline",
        "Runs the NISL warpfunc support pipeline",
        [](OpPassManager &passManager) {
            buildTransformPassPipeline(passManager);
        });

    }
    

    }   // namespace WarpEnrtyPoint
}   // namespace compiler
}  // namespace mlir
