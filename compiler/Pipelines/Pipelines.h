


#include "mlir/Pass/PassManager.h"
#include <iostream>
namespace mlir {

namespace compiler {


void bulidNISLTransformPassPipeline(OpPassManager &passManager);


// Registration hooks.
void registerNISLTransformPipeline();
 
    
}  // namespace compiler
}  // namespace mlir

