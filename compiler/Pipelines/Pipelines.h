


#include "mlir/Pass/PassManager.h"
#include <iostream>
namespace mlir {

namespace compiler {

void buildTOSAConversionPassPipeline(OpPassManager &passManager){
        
        std::cout<<"bulid pipeline!!!";
    };




void registerTOSATransformPassPipeline(OpPassManager &passManager) {

        buildTOSAConversionPassPipeline(passManager);
    
}


// Registration hooks.
void registerTOSATransformPass(OpPassManager &passManager){
    registerTOSATransformPassPipeline(passManager);

        
    }
}  // namespace compiler
}  // namespace mlir

