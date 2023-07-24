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
        TOSA
    HDRS
        "Passes.h"
    SRCS
        "Passes.cpp"
    DEPS
        PassesIncGen
        MLIRArithDialect
        MLIRFuncDialect
        MLIRIR
        MLIRLinalgDialect
        MLIRPass
        MLIRSCFToControlFlow
        MLIRTensorDialect
        MLIRTosaDialect
        MLIRTosaToArith
        MLIRTosaToLinalg
        MLIRTosaToSCF
        MLIRTosaToTensor
        MLIRTransforms


)

