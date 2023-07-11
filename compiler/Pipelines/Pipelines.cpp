#include "Pipelines/Pipelines.h"
#include "InputConversion/TOSA/Passes.h"
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
        buildTOSAConversionPassPipeline(passManager);
        

        // 
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