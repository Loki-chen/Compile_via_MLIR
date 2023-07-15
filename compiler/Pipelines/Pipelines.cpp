#include "Pipelines/Pipelines.h"
#include "Conversion/TOSA/Passes.h"
#include "Conversion/WarpEntryPoint/Passes.h"
 //===----------------------------------------------------------------------===//
// Pipelines
//===----------------------------------------------------------------------===//

// // Performs input legalization for specific combination of input dialects.
// void buildTOSAInputConversionPassPipeline(OpPassManager &passManager);

// void registerTOSAConversionPassPipeline();

namespace mlir {
namespace compiler {
    
    void bulidNISLTransformPassPipeline(OpPassManager &passManager){
        // TOSA Conversion Pipeline
        InputTosa::buildTransformPassPipeline(passManager);
        
        // func.func ---gpu.func
        WarpEntryPoint::buildTransformPassPipeline(passManager);
    
    
    
    
    }








    void registerNISLTransformPipeline(){
      PassPipelineRegistration<> transformPassPipeline(
      "NISL-transformation-pipeline",
      "Runs the full NISL input to LLVM transformation pipeline",
      [](OpPassManager &passManager) {
      bulidNISLTransformPassPipeline(passManager);
      });
    }
}
}
// void registerTOSAConversionPasses();