nisl_add_all_subdirs()


nisl_cc_library(
    NAME
        TOSA
    HDRS
        "Passes.h"
    SRCS
        "Passes.cpp"
    DEPS
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