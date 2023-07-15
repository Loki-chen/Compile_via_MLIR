nisl_add_all_subdirs()

nisl_cc_library(
  NAME
    WarpEntryPoint
  HDRS
    "Passes.h"
  SRCS
    "ConvertStreamableOps.cpp"
    "Passes.cpp"
    # "WrapEntryPoints.cpp"
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
    
  PUBLIC
)
