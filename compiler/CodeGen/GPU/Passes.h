
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include <memory>


namespace mlir {
namespace compiler {
namespace GPUCodeGen {
    

void buildTransformPassPipeline(OpPassManager &passManager);


void registerLLVMGPUCodeGenPasspipeline();


std::unique_ptr<OperationPass<ModuleOp>> createLLVMGpuCodeGenPass();
void registerCUDATargetBackend();

inline void registerPasses(){

    // register Cuda Backend;
    registerCUDATargetBackend();
    //register pass
    createLLVMGpuCodeGenPass();
    //register Pipeline
    registerLLVMGPUCodeGenPasspipeline();
}

    }   //  GPUCodeGen
    }  // compiler
}  // mlir