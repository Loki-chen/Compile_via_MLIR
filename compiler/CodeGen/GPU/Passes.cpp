

#include "CodeGen/GPU/Passes.h"
#include "mlir/Conversion/SPIRVToLLVM/SPIRVToLLVMPass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include <iostream>
namespace mlir {
namespace compiler {
namespace GPUCodeGen {



void buildTransformPassPipeline(OpPassManager &passManager){
    llvm::errs() << "codeGen Gpu " << "\n";

    passManager.addPass(createLLVMGpuCodeGenPass());


}



void registerLLVMGPUCodeGenPasspipeline(){
    PassPipelineRegistration<> codeGenPassPipeline(
        "nisl-llvm-Gpu-codegen-pipeline",
        "Run the GPU CodeGen pipeline",
        [](OpPassManager &passManager)->void{
            buildTransformPassPipeline(passManager);
        }
    );
}


}  // namespace GPUCodeGen
}  //namespace compiler
}   //namespace mlir