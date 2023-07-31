#include "Conversion/TOSA/PassDetail.h"
#include "Conversion/TOSA/Passes.h"


#include "mlir/Dialect/Bufferization/IR/BufferizableOpInterface.h"
#include "mlir/Dialect/Bufferization/IR/Bufferization.h"
#include "mlir/Dialect/Bufferization/Transforms/OneShotAnalysis.h"
#include "mlir/Dialect/Bufferization/Transforms/Passes.h"
#include "mlir/Dialect/Bufferization/Transforms/Transforms.h"

#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/DialectRegistry.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/Visitors.h"
#include "mlir/Support/LogicalResult.h"
#include <iostream>

using mlir::bufferization::BufferizationOptions;
using  mlir::bufferization::OneShotAnalysisState;
using mlir::bufferization::OneShotBufferizationOptions;

namespace mlir {
namespace compiler {
namespace InputTosa {


static OneShotBufferizationOptions getBufferizationOptions() {
  OneShotBufferizationOptions options;

  // bufferization.to_memref is used to bufferize constants in IREE. IREE has
  // it's own logic to handle constants. We'd like to leave the arith.constant
  // as is and insert bufferization.to_memref to convert the tensor to memref.
  options.opFilter.denyOperation<arith::ConstantOp>();
  options.opFilter.denyOperation<bufferization::ToMemrefOp>();

  // This type converter converts tensor types to memref types when no exact
  // memref type can be inferred from the context.
  options.unknownTypeConverterFn = [](Value value, Attribute memorySpace,
                                      const BufferizationOptions &options) {
    auto tensorType = value.getType().cast<TensorType>();

    // Special rule for ConstantOps: These always lower to some memref with a
    // static identity layout.
    if (value.getDefiningOp<arith::ConstantOp>())
      return bufferization::getMemRefTypeWithStaticIdentityLayout(tensorType,
                                                                  memorySpace);

    // Default case: Fully dynamic layout map for best compatibility.
    return bufferization::getMemRefTypeWithFullyDynamicLayout(tensorType,
                                                              memorySpace);
  };

  return options;
}
class EliminateEmptyTensorsPass : public EliminateEmptyTensorsBase<EliminateEmptyTensorsPass>{
    public:
        StringRef getArgument() const override{
        return "eliminate-empty-tensor-pass";
        }

        StringRef getDescription() const override{
            return "eliminate empty tensor";
        }

        void getDependentDialects(DialectRegistry &registry) const override{
            registry.insert<bufferization::BufferizationDialect, tensor::TensorDialect>();
        }
        void runOnOperation() override;
        
};


LogicalResult eliminateEmptyTensors(
    RewriterBase &rewriter, Operation *op,
    const OneShotBufferizationOptions &options) {
  // Analyze IR.
  OneShotAnalysisState state(op, options);
  if (failed(analyzeOp(op, state))) return failure();

  // Rewrite tensor.empty ops that are anchored on specific ops.
  if (failed(bufferization::insertSliceAnchoredEmptyTensorEliminationStep(
          rewriter, op, state)))
    return failure();
//   if (failed(
//           storeTensorOpAnchoredEmptyTensorEliminationStep(rewriter, op, state)))
//     return failure();

  return success();
}

void EliminateEmptyTensorsPass::runOnOperation(){
    ModuleOp moduleOp = getOperation();
    OneShotBufferizationOptions options = getBufferizationOptions();
    IRRewriter rewriter(moduleOp.getContext());

  if (failed(eliminateEmptyTensors(rewriter, moduleOp, options)))
    return signalPassFailure();
}

std::unique_ptr<OperationPass<ModuleOp>> createEliminateEmptyTensorsPass() {
  return std::make_unique<EliminateEmptyTensorsPass>();
}


} // namespace InputTosa
}   //namespace compiler
}   //namespace mlir