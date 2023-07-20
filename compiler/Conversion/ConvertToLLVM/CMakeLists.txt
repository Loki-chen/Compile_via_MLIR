nisl_add_all_subdirs()

nisl_cc_library(
  NAME
    ConvertToLLVM
  HDRS
    "Passes.h"
  SRCS
    "Passes.cpp"

  DEPS
    LLVMSupport
    MLIRAffineUtils
    MLIRFuncDialect
    MLIRIR
    MLIRPass
    MLIRShapeDialect
    MLIRShapeOpsTransforms
    MLIRSupport
    MLIRTensorDialect
    MLIRTransformUtils
    MLIRTransforms
    
    MLIRGPUOps
    MLIRGPUTransforms
    
  PUBLIC
)
