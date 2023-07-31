// Copyright 2021 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Conversion/TOSA/Passes.h"


#include "mlir/Conversion/TosaToArith/TosaToArith.h"
#include "mlir/Conversion/TosaToLinalg/TosaToLinalg.h"
#include "mlir/Conversion/TosaToSCF/TosaToSCF.h"
#include "mlir/Conversion/TosaToTensor/TosaToTensor.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/Tosa/Transforms/Passes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include <iostream>
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CommandLine.h"

namespace mlir {
namespace compiler {
namespace InputTosa{
// Prepare InputTosa for use as an input to the Flow dialect.
void buildTransformPassPipeline(OpPassManager &passManager) {
  // Currently we don't handle SCF ops well and have to convert them all to CFG.
  // In the future it would be nice if we could have all of flow be both scf
  // and cfg compatible.
    passManager.addNestedPass<func::FuncOp>(tosa::createTosaToSCF());
    passManager.addPass(mlir::createCanonicalizerPass());

    passManager.addNestedPass<func::FuncOp>(tosa::createTosaMakeBroadcastablePass());
    passManager.addPass(tosa::createTosaToArith());
    passManager.addNestedPass<func::FuncOp>(tosa::createTosaToTensor());
    passManager.addNestedPass<func::FuncOp>(mlir::createCanonicalizerPass());
    passManager.addNestedPass<func::FuncOp>(tosa::createTosaToSCF());
    passManager.addNestedPass<func::FuncOp>(tosa::createTosaToLinalgNamed());
    passManager.addNestedPass<func::FuncOp>(tosa::createTosaToLinalg());
    // Origin pass
    // eliminate-empty-tensors ---TODO


    passManager.addPass(createEliminateEmptyTensorsPass());
    passManager.addPass(bufferization::createEmptyTensorToAllocTensorPass());


    passManager.addNestedPass<func::FuncOp>(tosa::createTosaLayerwiseConstantFoldPass());

    passManager.addNestedPass<func::FuncOp>(tosa::createTosaValidationPass());
    passManager.addPass(mlir::createCanonicalizerPass());
}

void registerTOSAConversionPassPipeline() {
  PassPipelineRegistration<> transformPassPipeline(
      "nisl-tosa-input-transformation-pipeline",
      "Runs the TOSA NISL flow dialect transformation pipeline",
      [](OpPassManager &passManager) {
        buildTransformPassPipeline(passManager);
      });
}


}  // TOSA
}  // namespace compiler
}  // namespace mlir
