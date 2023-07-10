# Install script for directory: /home/MLIR-Compiler/third_party/llvm-project/mlir/lib/Dialect

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRDialectx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRDialect.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Affine/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/AMDGPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Arith/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/ArmNeon/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/ArmSVE/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Async/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/AMX/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Bufferization/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Complex/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/ControlFlow/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/DLTI/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/EmitC/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Func/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/GPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Index/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/IRDL/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Linalg/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/LLVMIR/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Math/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/MemRef/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/MLProgram/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/NVGPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/OpenACC/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/OpenMP/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/PDL/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/PDLInterp/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Quant/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/SCF/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Shape/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/SparseTensor/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/SPIRV/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Tensor/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Tosa/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Transform/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Utils/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/Vector/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/Dialect/X86Vector/cmake_install.cmake")

endif()

