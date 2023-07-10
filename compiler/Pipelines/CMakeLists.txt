nisl_cc_library(
  NAME
    Pipelines
  HDRS
    "Pipelines.h"
  SRCS
    "Pipelines.cpp"
  DEPS
    ${IREE_INPUT_DEPS}

    LLVMSupport
    MLIRIR
    MLIRPass
    MLIRSupport
  PUBLIC
)