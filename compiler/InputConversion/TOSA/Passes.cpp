// Copyright 2021 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "InputConversion/TOSA/Passes.h"


#include "mlir/Conversion/TosaToArith/TosaToArith.h"
#include "mlir/Conversion/TosaToLinalg/TosaToLinalg.h"
#include "mlir/Conversion/TosaToSCF/TosaToSCF.h"
#include "mlir/Conversion/TosaToTensor/TosaToTensor.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Linalg/Passes.h"
#include "mlir/Dialect/Tosa/Transforms/Passes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassOptions.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
namespace mlir {
namespace compiler {

// Prepare TOSA for use as an input to the Flow dialect.
void buildTOSAConversionPassPipeline(OpPassManager &passManager) {
  // Currently we don't handle SCF ops well and have to convert them all to CFG.
  // In the future it would be nice if we could have all of flow be both scf
  // and cfg compatible.
  passManager.addNestedPass<func::FuncOp>(tosa::createTosaMakeBroadcastablePass());

  
  passManager.addPass(tosa::createTosaToArith());


  passManager.addNestedPass<func::FuncOp>(tosa::createTosaToTensor());

  passManager.addNestedPass<func::FuncOp>(mlir::createCanonicalizerPass());

  passManager.addNestedPass<func::FuncOp>(tosa::createTosaToSCF());

  passManager.addNestedPass<func::FuncOp>(tosa::createTosaToLinalgNamed());
  passManager.addNestedPass<func::FuncOp>(tosa::createTosaToLinalg());

}

void registerTOSAConversionPassPipeline() {
  PassPipelineRegistration<> tosa(
      "nisl-tosa-input-transformation-pipeline",
      "Runs the TOSA NISL flow dialect transformation pipeline",
      [](OpPassManager &passManager) {
        buildTOSAConversionPassPipeline(passManager);
      });
}



void registerTOSAConversionPasses() {


  // Pipelines.
  registerTOSAConversionPassPipeline();
}

}  // namespace compiler
}  // namespace mlir
