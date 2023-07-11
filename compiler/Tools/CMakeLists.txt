nisl_add_all_subdirs()


nisl_cc_library(
  NAME
    compilerImpl
  HDRS
    "nisl_compile_lib.h"
  SRCS
    "nisl_compile_lib.cc"
  DEPS
  # LLVM support
    LLVMSupport
    LLVMTargetParser
    MLIRBuiltinToLLVMIRTranslation
    # MLIR Support
    MLIRIR
    MLIRParser
    MLIRPass
    MLIROptLib
    MLIRLspServerLib
    MLIRSupport
    MLIRTransformUtils
    MLIRTransforms
    MLIRAffineUtils
    MLIRFuncDialect
    MLIRShapeDialect
    MLIRShapeOpsTransforms
    MLIRTensorDialect
    MLIRControlFlowDialect
    # Dialects and Passes init
    init_passes_and_dialects
    init_llvmir_translations

    #Pipelines dependence
    Pipelines


  INCLUDES
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/.>"
  PUBLIC
)


nisl_cc_library(
  NAME
    optImpl
  HDRS
    "nisl_opt_lib.h"
  SRCS
    "nisl_opt_lib.cc"
  DEPS
    LLVMSupport
    
  PUBLIC
)



nisl_cc_library(
  NAME
    init_mlir_passes_and_dialects
  HDRS
    "init_mlir_dialects.h"
    "init_mlir_passes.h"
  DEPS
  # Dialect DEPS
    MLIRDialect
    MLIRPass
    MLIRIR
    MLIRControlFlowToSPIRV
    MLIRReconcileUnrealizedCasts
    MLIRTransformDialect



    MLIRAffineDialect
    MLIRAffineTransforms
    MLIRArmNeonDialect
    MLIRArmNeon2dToIntr
    MLIRBufferizationDialect
    MLIRComplexDialect
    MLIRControlFlowDialect
    MLIRGPUOps
    MLIRGPUToSPIRV

    MLIRLLVMDialect
    MLIRLinalgDialect
    MLIRLinalgToLLVM
    MLIRLinalgTransforms
    MLIRMLProgramDialect
    MLIRMemRefDialect
    MLIRQuantDialect
    MLIRSCFDialect
    MLIRSCFToGPU
    MLIRSCFTransforms
    MLIRSPIRVDialect
    MLIRSPIRVTransforms
    MLIRShapeOpsTransforms
    MLIRShapeDialect
    MLIRFuncDialect
    MLIRFuncToSPIRV
    MLIRTensorInferTypeOpInterfaceImpl
    MLIRTransforms
    MLIRVectorDialect 
    MLIRShapeOpsTransforms # Shape Dialect transforms
    MLIRAsyncDialect
    MLIRAsyncTransforms

  PUBLIC
)


nisl_cc_library(
  NAME
    init_passes_and_dialects
  HDRS
    "init_dialects.h"
    "init_passes.h"
  DEPS

    init_mlir_passes_and_dialects
    # iree::compiler::Codegen::Codegen
    # iree::compiler::Dialect::HAL::Conversion::Passes
  PUBLIC
)


nisl_cc_library(
  NAME
    init_llvmir_translations
  HDRS
    "init_llvmir_translations.h"
  DEPS
    MLIRArmNeonToLLVMIRTranslation
    MLIRLLVMToLLVMIRTranslation
  PUBLIC
)