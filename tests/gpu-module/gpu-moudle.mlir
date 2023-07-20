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



module {
  func.func @add(%arg0: tensor<3xi32>) -> tensor<3xi32> {
    %cst = arith.constant dense<[1, 2, 4]> : tensor<3xi32>
    %0 = tensor.empty() : tensor<3xi32>
    %1 = linalg.generic {indexing_maps = [affine_map<(d0) -> (d0)>, affine_map<(d0) -> (d0)>, affine_map<(d0) -> (d0)>], iterator_types = ["parallel"]} ins(%arg0, %cst : tensor<3xi32>, tensor<3xi32>) outs(%0 : tensor<3xi32>) {
    ^bb0(%in: i32, %in_0: i32, %out: i32):
      %2 = arith.addi %in, %in_0 : i32
      linalg.yield %2 : i32
    } -> tensor<3xi32>
    return %1 : tensor<3xi32>
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


// RUN: mlir-opt %s \
// RUN: | mlir-opt -pass-pipeline='builtin.module(gpu.module(strip-debuginfo,convert-gpu-to-rocdl{index-bitwidth=32 runtime=HIP},gpu-to-hsaco{chip=%chip}))' \
// RUN: | mlir-opt -gpu-to-llvm \
// RUN: | mlir-cpu-runner \
// RUN:   --shared-libs=%mlir_rocm_runtime \
// RUN:   --shared-libs=%mlir_runner_utils \
// RUN:   --entry-point-result=void \
// RUN: | FileCheck %s

// CHECK: Hello from 0
// CHECK: Hello from 1
module attributes {gpu.container_module} {
    gpu.module @kernels {
        gpu.func @hello() kernel {
            %0 = gpu.thread_id x
            gpu.printf "Hello from %d\n" %0 : index
            gpu.return
        }
    }

    func.func @main() {
        %c2 = arith.constant 2 : index
        %c1 = arith.constant 1 : index
        gpu.launch_func @kernels::@hello
            blocks in (%c1, %c1, %c1)
            threads in (%c2, %c1, %c1)
        return
    }
}