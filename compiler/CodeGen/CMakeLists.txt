add_subdirectory(CPU)
add_subdirectory(GPU)

nisl_cc_library(
    NAME
      CodeGenUtils
    HDRS
      "CodeGenTools.h" 
    SRCS
      "CodeGenTools.cpp"
    DEPS
      LLVMSupport
      MLIRIR
      MLIRLLVMDialect

)