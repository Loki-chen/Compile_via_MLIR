# Install script for directory: /home/MLIR-Compiler/third_party/llvm-project/mlir/tools

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
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-lsp-server/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-opt/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-parser-fuzzer/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-pdll-lsp-server/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-reduce/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-shlib/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-spirv-cpu-runner/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-translate/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-vulkan-runner/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/tblgen-lsp-server/cmake_install.cmake")

endif()
