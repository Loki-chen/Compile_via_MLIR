nisl_add_all_subdirs()


nisl_cc_library(
  NAME
    compilerImpl
  HDRS
    "nisl_compile_lib.h"
  SRCS
    "nisl_compile_lib.cc"
  DEPS
    LLVMSupport
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

# nisl_cc_library(
#   NAME
#     init_input_passes_and_dialects
#   HDRS
#     "init_input_dialects.h"
#     "init_input_passes.h"
#   SRCS
#     "init_input_dialects.cc"
#     "init_input_passes.cc"
#   DEPS
#     ${IREE_INPUT_DEPS}
#     CommonInputConversion
#   PUBLIC
# )


nisl_cc_library(
  NAME
    init_mlir_passes_and_dialects
  HDRS
    "init_mlir_dialects.h"
    "init_mlir_passes.h"
  DEPS
    MLIRAffineDialect
    MLIRAffineTransforms
    MLIRArmNeonDialect
    MLIRArmNeon2dToIntr
    MLIRBufferizationDialect
    MLIRComplexDialect
    MLIRControlFlowDialect
    MLIRGPUOps
    MLIRGPUToSPIRV
    MLIRIR
    MLIRLLVMDialect
    MLIRLinalgDialect
    MLIRLinalgToLLVM
    MLIRLinalgTransforms
    MLIRMLProgramDialect
    MLIRQuantDialect
    MLIRSCFDialect
    MLIRSCFToGPU
    MLIRSCFTransforms
    MLIRSPIRVDialect
    MLIRSPIRVTransforms
    MLIRShapeDialect  
    MLIRShapeOpsTransforms # Shape Dialect transforms
    MLIRFuncDialect
    MLIRFuncToSPIRV
    MLIRTensorInferTypeOpInterfaceImpl
    MLIRTransforms
    MLIRVectorDialect
  PUBLIC
)


nisl_cc_library(
  NAME
    init_passes_and_dialects
  HDRS
    "init_dialects.h"
    "init_passes.h"
  DEPS
    # ::init_compiler_modules
    # init_input_passes_and_dialects
    # ::init_iree_passes_and_dialects
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