
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include <memory>


namespace mlir {
namespace compiler {
namespace CPUCodeGen {
    

void buildTransformPassPipeline(OpPassManager &passManager);


void registerLLVMCPUCodeGenPasspipeline();


std::unique_ptr<OperationPass<ModuleOp>> createLLVMCpuCodeGenPass();
void registerCPUTargetBackend();

inline void registerPasses(){
    // 
    registerCPUTargetBackend();
    //register pass
    createLLVMCpuCodeGenPass();
    //register Pipeline
    registerLLVMCPUCodeGenPasspipeline();
}

    }   //  CPUCodeGen
    }  // compiler
}  // mlir