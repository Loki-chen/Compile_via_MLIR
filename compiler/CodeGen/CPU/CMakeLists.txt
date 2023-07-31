nisl_add_all_subdirs()

nisl_cc_library(
    NAME
      LLVMCPUCodeGen
    HDRS
      "Passes.h"
    SRCS
      "Passes.cpp"
      "LLVMCPUCodeGenpass.cpp"
    DEPS
      LLVMSupport
      LLVMAnalysis
      LLVMBitReader
      LLVMBitWriter
      MLIRIR
      MLIRLLVMDialect
      CodeGenUtils

)