// RUN: mlir-hlo-opt %s \
// RUN:   -propagate-static-shapes='convert_pointer_args=!llvm.ptr<i8>' \
// RUN: | FileCheck %s

module attributes {gpu.container_module} {
  gpu.module @gpu_module {
    // CHECK: llvm.func @kernel(%arg0: f32, %arg1: !llvm.ptr<i8>, %arg2: f32)
    llvm.func @kernel(
      %arg0: f32,
      %base: !llvm.ptr<f32>, %align: !llvm.ptr<f32>, %offset: i64,
      %size.x: i64, %size.y: i64, %stride.x: i64, %stride.y: i64,
      %argN: f32
    ) attributes {gpu.kernel} {
      // CHECK-DAG:  %[[base:.*]] = llvm.bitcast %arg1 : !llvm.ptr<i8> to !llvm.ptr<f32>
      // CHECK:      %[[ptr:.*]] = llvm.getelementptr %[[base]][4]
      // CHECK:      llvm.call @dummy(%[[ptr]]) : (!llvm.ptr<f32>) -> ()
      %ptr = llvm.getelementptr %align[%stride.x] : (!llvm.ptr<f32>, i64) -> !llvm.ptr<f32>
      llvm.call @dummy(%ptr) : (!llvm.ptr<f32>) -> ()
      llvm.return
    }
    // CHECK: llvm.func @dummy(%arg0: !llvm.ptr<f32>)
    llvm.func @dummy(%arg0: !llvm.ptr<f32>) attributes {gpu.kernel} {
      llvm.return
    }
  }
  func.func @func(%arg0: f32, %arg1: memref<2x4xf32>) {
    %c1 = arith.constant 1 : index
    gpu.launch_func  @gpu_module::@kernel
      blocks in (%c1, %c1, %c1)
      threads in (%c1, %c1, %c1)
      args(%arg0 : f32, %arg1 : memref<2x4xf32>, %arg0 : f32)
    func.return
  }
}  



// RUN: mlir-opt --gpu-kernel-outlining --convert-gpu-to-nvvm %s | FileCheck %s

func.func @main() {
  %data = memref.alloc() : memref<2x6xf32>
  %sum = memref.alloc() : memref<2xf32>
  %mul = memref.alloc() : memref<2xf32>
  %c1 = arith.constant 1 : index

  // ADD + MUL
  gpu.launch blocks(%bx, %by, %bz) in (%grid_x = %c1, %grid_y = %c1, %grid_z = %c1)
             threads(%tx, %ty, %tz) in (%block_x = %c1, %block_y = %c1, %block_z = %c1) {
    %val = memref.load %data[%bx, %tx] : memref<2x6xf32>
    %reduced0 = gpu.all_reduce add %val uniform {} : (f32) -> (f32)
    memref.store %reduced0, %sum[%bx] : memref<2xf32>
    %reduced1 = gpu.all_reduce mul %val uniform {} : (f32) -> (f32)
    memref.store %reduced1, %mul[%bx] : memref<2xf32>
    gpu.terminator
  }

// CHECK:      gpu.module @main_kernel {
// CHECK-NEXT:   llvm.mlir.global internal @{{.*}}() {addr_space = 3 : i32} : !llvm.array<32 x f32>
// CHECK-NEXT:   llvm.mlir.global internal @{{.*}}() {addr_space = 3 : i32} : !llvm.array<32 x f32>

  return
}


