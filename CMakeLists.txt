
# LLVM requires CMP0116 for tblgen: https://reviews.llvm.org/D101083
# CMP0116: Ninja generators transform `DEPFILE`s from `add_custom_command()`
# New in CMake 3.10. https://cmake.org/cmake/help/latest/policy/CMP0116.html
cmake_minimum_required(VERSION 3.10...3.24)
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

if(POLICY CMP0116)
    cmake_policy(SET CMP0116 OLD)
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")



# Set the default CMake build type so some of the build type dependent setting
# in the submodules and functions (IREE assertion) can be set properly.
set(DEFAULT_CMAKE_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to ${DEFAULT_CMAKE_BUILD_TYPE}")
  set(CMAKE_BUILD_TYPE "${DEFAULT_CMAKE_BUILD_TYPE}" CACHE STRING "Build type (default ${DEFAULT_CMAKE_BUILD_TYPE})" FORCE)
endif()
include(CMakeDependentOption)


#-------------------------------------------------------------------------------
# Project component configuration
#-------------------------------------------------------------------------------
project(nisl-compiler)
project(nisl-compiler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
option(NISL_ENABLE_THREADING "Builds IREE in with thread library support." ON)
option(NISL_ENABLE_CLANG_TIDY "Builds IREE in with clang tidy enabled on IREE's libraries." OFF)
option(NISL_BUILD_COMPILER "Builds the NISL compiler." ON)
option(NISL_BUILD_BUNDLED_LLVM "Builds the bundled llvm (vs using installed)" ON)



# For development, builds LLVM (and in the future) the whole compiler as
# individual shared libraries similar to if passing -DBUILD_SHARED_LIBS=ON
# to a standalone LLVM build. This can dramatically reduce linking time and
# makes the management of some dependencies more strict.
# This option is considered experimental and should not be relied on until
# CI coverage is established.
option(NISL_COMPILER_BUILD_SHARED_LIBS "Enables BUILD_SHARED_LIBS CMake mode for LLVM and the compiler (this is only suitable for development)" OFF)

# Must be defined as an option (CMake does not do it automatically), even though
# we override it for different parts of the tree.
# This option is considered experimental and should not be relied on until
# CI coverage is established.
option(BUILD_SHARED_LIBS "Instructs CMake to build libraries as shared if possible" OFF)


#-------------------------------------------------------------------------------
# CUDA Toolkit.
#
# Using the (optional) CUDA support in the compiler and runtime requires the
# NVIDIA CUDA Toolkit. The toolkit can either be installed ahead of time or
# it can be automatically downloaded on certain host architectures.
#-------------------------------------------------------------------------------

set(NISL_CUDA_AVAILABLE OFF)
find_package(CUDAToolkit)
if(CUDAToolkit_FOUND)
  set(NISL_CUDA_AVAILABLE ON)
  message("NISL Default CUDA AVALIABLE")
else()
  # We can download the SDK in build_tools/third_party/cuda/CMakeLists.txt, if
  # on a supported platform/arch.
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR WIN32)
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "(x86_64)|(AMD64|amd64)")
      set(NISL_CUDA_AVAILABLE ON)
      message("NISL CUDA AVALIABLE")
    endif()
  endif()
endif()


#-------------------------------------------------------------------------------
# Compiler Target Options
# By default, all compiler targets supported by the current platform are
# enabled. Some compiler targets like CUDA will install external deps as
# needed at configure time. This can be changed with:
#   -DNISL_TARGET_BACKEND_DEFAULTS=OFF
#-------------------------------------------------------------------------------

option(NISL_TARGET_BACKEND_DEFAULTS "Sets the default value for all compiler target backends" ON)

# The VMVX backend is always enabled.
cmake_dependent_option(NISL_TARGET_BACKEND_VMVX "Enables the 'vmvx' compiler target backend" ON ${NISL_BUILD_COMPILER} OFF)
# Supported default target backends.
cmake_dependent_option(NISL_TARGET_BACKEND_LLVM_CPU "Enables the 'llvm-cpu' compiler target backend" ${NISL_TARGET_BACKEND_DEFAULTS} ${NISL_BUILD_COMPILER} OFF)
cmake_dependent_option(NISL_TARGET_BACKEND_LLVM_CPU_WASM "Enables WebAssembly in the 'llvm-cpu' compiler target backend" ${NISL_TARGET_BACKEND_DEFAULTS} ${NISL_TARGET_BACKEND_LLVM_CPU} OFF)
# Supported default target backends that are only available on certain
# platforms.
set(NISL_TARGET_BACKEND_CUDA_DEFAULT ${NISL_TARGET_BACKEND_DEFAULTS})
if(NOT NISL_CUDA_AVAILABLE)
  set(NISL_TARGET_BACKEND_CUDA_DEFAULT OFF)
endif()
cmake_dependent_option(NISL_TARGET_BACKEND_CUDA "Enables the 'cuda' compiler target backend" ${NISL_TARGET_BACKEND_CUDA_DEFAULT} ${NISL_BUILD_COMPILER} OFF)




#-------------------------------------------------------------------------------
# Compiler Input Dialects
#-------------------------------------------------------------------------------

include(CMakeDependentOption)
cmake_dependent_option(NISL_INPUT_MHLO "Builds support for compiling MHLO programs" ON ${NISL_BUILD_COMPILER} OFF)
cmake_dependent_option(NISL_INPUT_TORCH "Builds support for compiling Torch MLIR programs" ON ${NISL_BUILD_COMPILER} OFF)
cmake_dependent_option(NISL_INPUT_TOSA "Builds support for compiling TOSA programs" ON ${NISL_BUILD_COMPILER} OFF)
if(NISL_BUILD_COMPILER)
  message(STATUS "NISL compiler input dialects:")
  if(NISL_INPUT_MHLO)
    message(STATUS "  - MHLO")
  endif()
  if(NISL_INPUT_TORCH)
    message(STATUS "  - Torch MLIR")
  endif()
  if(NISL_INPUT_TOSA)
    message(STATUS "  - TOSA")
  endif()
endif()
option(NISL_LINK_COMPILER_SHARED_LIBRARY "Links NISL tools using the compiler compiled into a shared library" ON)


#-------------------------------------------------------------------------------
#  NISL utility definitions
#-------------------------------------------------------------------------------

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/build-tools/cmake/
)
include(nisl_cc_binary)
include(nisl_cc_library)
include(nisl_import_binary)
include(nisl_tablegen_library)
include(nisl_tablegen_doc)
include(nisl_add_all_subdirs)
include(nisl_llvm)



set(NISL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NISL_ROOT_DIR ${NISL_SOURCE_DIR})
set(NISL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NISL_BINARY_DIR}/tools)
set(NISL_COMPILER_ROOT_DIR ${NISL_SOURCE_DIR}/compiler)
include_directories(${NISL_COMPILER_ROOT_DIR})



#-------------------------------------------------------------------------------
# MLIR/LLVM Dependency
#-------------------------------------------------------------------------------

if(NOT NISL_BUILD_COMPILER)
  message(STATUS "Not adding LLVM/MLIR because the configuration does not require it")
else()
  # Force enable BUILD_SHARED_LIBS for the compiler if instructed.
  set(_NISL_ORIG_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
  if(NISL_COMPILER_BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
  endif()

  # Get the main LLVM deps.
  if(NISL_BUILD_BUNDLED_LLVM)
    nisl_llvm_configure_bundled()
  else()
    nisl_llvm_configure_installed()
  endif()

  # Also add a library that can be depended on to get LLVM includes setup
  # properly. bazel_to_cmake targets this for some header only pseudo deps.
  add_library(NISLLLVMIncludeSetup INTERFACE)
  target_include_directories(NISLLLVMIncludeSetup INTERFACE
    ${LLVM_INCLUDE_DIRS}
    ${MLIR_INCLUDE_DIRS}
    ${LLD_INCLUDE_DIRS}
  )
  # we add usage requirements to libraries at the root of all things LLVM.
  nisl_llvm_add_usage_requirements(LLVMSupport NISLLLVMIncludeSetup)
  nisl_llvm_add_usage_requirements(MLIRSupport NISLLLVMIncludeSetup)
  endif()


#-------------------------------------------------------------------------------
# Other dependencies
#-------------------------------------------------------------------------------

add_subdirectory(build-tools/third_party/llvm-project EXCLUDE_FROM_ALL)


# tools/ can depend on compiler/.
# Note: tools sub directory is added before compiler/ so that phony targets for
# files with the same names from different rules are disambiguated towards
# those in tools/.
add_subdirectory(compiler)
add_subdirectory(tests)
add_subdirectory(tools)