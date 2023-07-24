include "mlir/Pass/PassBase.td"

def EliminateEmptyTensors :
    Pass<"nisl-eliminate-empty-tensors", "ModuleOp"> {
  let summary = "Eliminate tensor.empty ops to avoid buffer allocations";
  let constructor = "mlir::compiler::InputTosa::createEliminateEmptyTensorsPass()";
}

