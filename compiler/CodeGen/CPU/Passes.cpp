

#include "CodeGen/CPU/Passes.h"
#include "mlir/Conversion/SPIRVToLLVM/SPIRVToLLVMPass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include <iostream>

namespace mlir {
namespace compiler {
namespace CPUCodeGen {



void buildTransformPassPipeline(OpPassManager &passManager){
    llvm::errs() << "codeGen cpu " << "\n";
    passManager.addPass(createLLVMCpuCodeGenPass());


}



void registerLLVMCPUCodeGenPasspipeline(){
    PassPipelineRegistration<> codeGenPassPipeline(
        "nisl-llvm-cpu-codegen-pipeline",
        "Run the LLVM CPU CodeGen pipeline",
        [](OpPassManager &passManager)->void{
            buildTransformPassPipeline(passManager);
        }
    );
}


}  // namespace CPUCodeGen
}  //namespace compiler
}   //namespace mlir