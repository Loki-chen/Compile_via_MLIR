nisl_cc_library(
  NAME
    Pipelines
  HDRS
    "Pipelines.h"
  SRCS
    "Pipelines.cpp"
  DEPS


    LLVMSupport
    MLIRIR
    MLIRPass
    MLIRSupport

    # TOSA Conversion
    TOSA
    # ConvertToMlirLLVM
    ConvertToMlirLLVM
    # LLVMCPUCodeGen
    LLVMCPUCodeGen
    # LLVMGPUCodeGen
    LLVMGPUCodeGen
    
  PUBLIC
)