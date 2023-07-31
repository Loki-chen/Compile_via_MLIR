
#include <memory>
#include "mlir/Conversion/LLVMCommon/Pattern.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/Tensor/Transforms/Passes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Pass/PassManager.h"

#include "mlir/Dialect/Arith/Transforms/Passes.h"
#include "mlir/Conversion/ComplexToStandard/ComplexToStandard.h"
#include "mlir/Conversion/SCFToControlFlow/SCFToControlFlow.h"
#include "mlir/Dialect/MemRef/Transforms/Passes.h"
#include "mlir/Dialect/Func/Transforms/Passes.h"
#include "mlir/Dialect/Tensor/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Conversion/ReconcileUnrealizedCasts/ReconcileUnrealizedCasts.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"

#include "mlir/Conversion/ArithToLLVM/ArithToLLVM.h"
#include "mlir/Conversion/MemRefToLLVM/MemRefToLLVM.h"
#include "mlir/Conversion/FuncToLLVM/ConvertFuncToLLVMPass.h"

namespace mlir {
namespace compiler {
namespace ConvertToMlirLLVM {


    void buildTransformPassPipeline(OpPassManager &passManager){


        // passManager.addPass(createConvertTensorToLinalgPass());

        //bufferization
        passManager.addNestedPass<func::FuncOp>(createLinalgBufferizePass());
        passManager.addPass(arith::createConstantBufferizePass());
        passManager.addNestedPass<func::FuncOp>(arith::createArithExpandOpsPass());
        passManager.addNestedPass<func::FuncOp>(memref::createExpandOpsPass());
        passManager.addPass(arith::createArithBufferizePass());
        passManager.addPass(func::createFuncBufferizePass());

        // TODO add a pass eliminate the empty tensor, then delete the next two passs.
        passManager.addPass(bufferization::createEmptyTensorToAllocTensorPass());
        passManager.addNestedPass<func::FuncOp>(tensor::createTensorBufferizePass());
        
        // Finalizing bufferization pass.
        passManager.addNestedPass<func::FuncOp>(mlir::bufferization::createFinalizingBufferizePass());

        // linalg -scf
        passManager.addNestedPass<func::FuncOp>(createConvertLinalgToLoopsPass());
        passManager.addPass(createLowerAffinePass());
        passManager.addNestedPass<func::FuncOp>(createCanonicalizerPass());
        passManager.addNestedPass<func::FuncOp>(createCSEPass());
    
        // Handle complex operation conversion.
        passManager.addPass(createConvertComplexToStandardPass());

        // SCF -> CF
        passManager.addNestedPass<func::FuncOp>(createConvertSCFToCFPass());
        passManager.addNestedPass<func::FuncOp>(createCanonicalizerPass());
        passManager.addNestedPass<func::FuncOp>(createCSEPass());

        // ( Linalg, CF, tensor) -> LLVM

        passManager.addNestedPass<func::FuncOp>(mlir::createArithToLLVMConversionPass());
        passManager.addPass(mlir::createConvertFuncToLLVMPass());
        passManager.addPass(mlir::createFinalizeMemRefToLLVMConversionPass());
        passManager.addPass(createReconcileUnrealizedCastsPass());
        passManager.addPass(createCanonicalizerPass());
        passManager.addPass(createCSEPass());
        
        // Assign the target info on the LLVM module attributes---> TODO

    }


    void registerTransformPassPipeline(){
        PassPipelineRegistration<> transformPassPipeline(
        "nisl-mlir-transformation-llvm-mlir-pipeline",
        "Runs the NISL llvm support pipeline",
        [](OpPassManager &passManager) {
            buildTransformPassPipeline(passManager);
        });

    }
    

    }   // namespace ConvertToMlirLLVM
}   // namespace compiler
}  // namespace mlir
