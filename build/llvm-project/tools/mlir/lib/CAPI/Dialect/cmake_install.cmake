# Install script for directory: /home/MLIR-Compiler/third_party/llvm-project/mlir/lib/CAPI/Dialect

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIAsyncx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIAsync.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIAsyncx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIAsync" TYPE FILE FILES
    "Async.cpp.o"
    "AsyncPasses.cpp.o"
    FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIAsync.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIControlFlowx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIControlFlow.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIControlFlowx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIControlFlow" TYPE FILE FILES "ControlFlow.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIControlFlow.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIGPUx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIGPU.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIGPUx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIGPU" TYPE FILE FILES
    "GPU.cpp.o"
    "GPUPasses.cpp.o"
    FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIGPU.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPILLVMx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPILLVM.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPILLVMx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPILLVM" TYPE FILE FILES "LLVM.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPILLVM.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPILinalgx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPILinalg.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPILinalgx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPILinalg" TYPE FILE FILES
    "Linalg.cpp.o"
    "LinalgPasses.cpp.o"
    FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPILinalg.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIMLProgramx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIMLProgram.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIMLProgramx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIMLProgram" TYPE FILE FILES "MLProgram.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIMLProgram.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPISCFx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPISCF.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPISCFx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPISCF" TYPE FILE FILES "SCF.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPISCF.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIShapex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIShape.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIShapex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIShape" TYPE FILE FILES "Shape.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIShape.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPISparseTensorx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPISparseTensor.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPISparseTensorx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPISparseTensor" TYPE FILE FILES
    "SparseTensor.cpp.o"
    "SparseTensorPasses.cpp.o"
    FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPISparseTensor.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIFuncx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIFunc.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIFuncx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIFunc" TYPE FILE FILES "Func.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIFunc.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPITensorx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPITensor.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPITensorx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPITensor" TYPE FILE FILES "Tensor.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPITensor.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPITransformDialectx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPITransformDialect.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPITransformDialectx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPITransformDialect" TYPE FILE FILES "Transform.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPITransformDialect.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIQuantx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIQuant.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIQuantx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIQuant" TYPE FILE FILES "Quant.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIQuant.dir/./")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xMLIRCAPIPDLx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/MLIR-Compiler/build/llvm-project/lib/libMLIRCAPIPDL.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xobj.MLIRCAPIPDLx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects-Debug/obj.MLIRCAPIPDL" TYPE FILE FILES "PDL.cpp.o" FILES_FROM_DIR "/home/MLIR-Compiler/build/llvm-project/tools/mlir/lib/CAPI/Dialect/CMakeFiles/obj.MLIRCAPIPDL.dir/./")
endif()

