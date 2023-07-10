# Install script for directory: /home/MLIR-Compiler/third_party/llvm-project/mlir/include/mlir/Dialect

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/AMDGPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/AMX/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Affine/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Arith/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/ArmNeon/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/ArmSVE/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Async/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Bufferization/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Complex/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/ControlFlow/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/DLTI/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/EmitC/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Func/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/GPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Index/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/IRDL/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/LLVMIR/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Linalg/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/MLProgram/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Math/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/MemRef/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/NVGPU/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/OpenACC/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/OpenMP/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/PDL/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/PDLInterp/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Quant/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/SCF/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/SPIRV/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Shape/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/SparseTensor/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Tensor/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Tosa/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Transform/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Utils/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/Vector/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/Dialect/X86Vector/cmake_install.cmake")

endif()

