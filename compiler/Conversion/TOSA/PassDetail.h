
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/NVGPU/IR/NVGPUDialect.h"
#include "mlir/Pass/Pass.h"

namespace mlir {
namespace compiler {
namespace InputTosa {



#define GEN_PASS_CLASSES
// TODO--fix cmakeFiles.txt
#include "/home/MLIR-Compiler/build/compiler/Conversion/TOSA/Passes.h.inc"

}  // namespace iree_compiler
}  // namespace mlir
}

