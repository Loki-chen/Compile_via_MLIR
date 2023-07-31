
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception


#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Dialect/Tosa/Transforms/Passes.h"
#include "mlir/Conversion/Passes.h"
namespace mlir {
namespace compiler {
namespace InputTosa {


//===----------------------------------------------------------------------===//
// Pipelines
//===----------------------------------------------------------------------===//

// Performs input legalization for specific combination of input dialects.
void buildTransformPassPipeline(OpPassManager &passManager);

void registerTOSAConversionPassPipeline();



/// A pass to eliminate tensor.empty ops that could turn into allocations
/// during bufferization.
std::unique_ptr<OperationPass<ModuleOp>> createEliminateEmptyTensorsPass();


//===----------------------------------------------------------------------===//
// Register all Passes
//===----------------------------------------------------------------------===//

inline void registerPasses(){
  //register pass
  registerTosaToArithPass();
  registerTosaToLinalgPass();
  registerTosaToTensorPass();

  createEliminateEmptyTensorsPass();
  // Pipelines.
  registerTOSAConversionPassPipeline();
}
}   // InputTosa
}  // namespace compiler
}  // namespace mlir


