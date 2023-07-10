# Install script for directory: /home/MLIR-Compiler/third_party/llvm-project/mlir

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmlir-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES
    "/home/MLIR-Compiler/third_party/llvm-project/mlir/include/mlir"
    "/home/MLIR-Compiler/third_party/llvm-project/mlir/include/mlir-c"
    FILES_MATCHING REGEX "/[^/]*\\.def$" REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.inc$" REGEX "/[^/]*\\.td$" REGEX "/LICENSE\\.TXT$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xmlir-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES
    "/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir"
    "/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir-c"
    FILES_MATCHING REGEX "/[^/]*\\.def$" REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.gen$" REGEX "/[^/]*\\.inc$" REGEX "/[^/]*\\.td$" REGEX "/CMakeFiles$" EXCLUDE REGEX "/config\\.h$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-tblgen/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-linalg-ods-gen/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/mlir-pdll/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/include/mlir/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/tools/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/docs/cmake_install.cmake")
  include("/home/MLIR-Compiler/build/llvm-project/tools/mlir/cmake/modules/cmake_install.cmake")

endif()

