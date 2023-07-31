nisl_add_all_subdirs()

nisl_cc_library(
    NAME
      LLVMGPUCodeGen
    HDRS
      "Passes.h"
    SRCS
      "Passes.cpp"
      "LLVMGPUCodeGenpass.cpp"
    DEPS


      LLVMAnalysis  
      LLVMPasses
      LLVMMC
      LLVMSupport
      LLVMTarget

      LLVMNVPTXCodeGen
      LLVMNVPTXDesc
      LLVMNVPTXInfo

      MLIRIR
      MLIRLLVMDialect
      
      MLIRBuiltinToLLVMIRTranslation
      MLIRGPUOps
      MLIRLLVMDialect
      MLIRLLVMToLLVMIRTranslation
      MLIRNVGPUDialect
      MLIRNVVMDialect
      MLIRNVVMToLLVMIRTranslation
      MLIRPass
      MLIRSupport
      MLIRTargetLLVMIRExport

      CodeGenUtils
)