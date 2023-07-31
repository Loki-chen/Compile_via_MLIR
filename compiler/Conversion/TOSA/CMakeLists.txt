nisl_add_all_subdirs()


nisl_tablegen_library(
  NAME
    PassesIncGen
  TD_FILE
    "Passes.td"
  OUTS
    --gen-pass-decls Passes.h.inc
)

nisl_cc_library(
  NAME
    PassHeaders
  HDRS
    "PassDetail.h"
    "Passes.h"
    "Passes.h.inc"
  DEPS
    PassesIncGen
    MLIRLinalgTransforms
    MLIRMemRefDialect
    MLIRNVGPUDialect
    MLIRPass
    MLIRTransforms
  PUBLIC
)

nisl_cc_library(
  NAME
    Codegen
  SRCS
    "Passes.cpp"
  DEPS
    PassHeaders
    PassesIncGen
  PUBLIC
)



nisl_cc_library(
    NAME
        TOSA
    HDRS
        "Passes.h"
    SRCS
        "Passes.cpp"
        "eliminateEmptyTensors.cpp"
    DEPS
        Codegen
        MLIRArithDialect
        MLIRFuncDialect
        MLIRIR
        MLIRLinalgDialect
        MLIRPass
        MLIRSCFToControlFlow
        MLIRTosaDialect
        MLIRTosaToArith
        MLIRTosaToLinalg
        MLIRTosaToSCF
        MLIRTosaToTensor
        MLIRTransforms

        MLIRTensorDialect
        MLIRTensorTransforms
        
        MLIRTransformDialect
        MLIRTransforms

        MLIRBufferizationDialect
        MLIRBufferizationTransforms

)

