
#include "Conversion/WarpEntryPoint/Passes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Support/LLVM.h"
#include "mlir/Support/LogicalResult.h"
#include "llvm/ADT/StringRef.h"

#include <memory>
#include <iostream>


namespace mlir {
namespace compiler {
namespace WarpEntryPoint{


static constexpr int64_t kUnspecifiedDim = -1;
static constexpr int64_t kTiedDim = -2;



class WrapEntryPointsPass : public PassWrapper<WrapEntryPointsPass, OperationPass<ModuleOp>>{


    public:
      WrapEntryPointsPass() = default;
      WrapEntryPointsPass(const WrapEntryPointsPass &pass) {}

      void getDependentDialects(DialectRegistry &registry) const override {
        registry.insert<func::FuncDialect, mlir::tensor::TensorDialect, mlir::gpu::GPUDialect>();
      }

      StringRef getArgument() const override {
        return "nisl-convert-streamable-ops";
      }

      StringRef getDescription() const override {
        return "Converts streamable ops in input dialects.";
      }

      void runOnOperation() override{
        auto moduleOp = getOperation();

        SmallVector<func::FuncOp> originalFuncOps;

        for(auto funcOp : moduleOp.getOps<func::FuncOp>()){

          originalFuncOps.push_back(funcOp);
        }

        SymbolTable symbolTable(moduleOp);


      }

};


std::unique_ptr<OperationPass<ModuleOp>> createWrapEntryPointsOpsPass() {
    return std::make_unique<WrapEntryPointsPass>();
  }

static PassRegistration<WrapEntryPointsPass> pass;


    }   // namespace WarpEntryPoint     
  }  // namepace compiler
}  // namespace mlir