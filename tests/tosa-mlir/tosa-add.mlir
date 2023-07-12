module {
  func.func @add(%arg0: tensor<3xi32>) -> tensor<3xi32>  {
    %1 = "tosa.const"() {value = dense<[1, 2, 4]> : tensor<3xi32>} : () -> tensor<3xi32>
    %2 = "tosa.add"(%arg0, %1) : (tensor<3xi32>, tensor<3xi32>) -> tensor<3xi32>
    return %2 : tensor<3xi32>
  }
}

//  module{
//      func.func @main(%input: tensor<1x49x42x27xf32>, %weights: tensor<28x3x3x27xf32>, %bias: tensor<28xf32>) -> tensor<1x45x40x28xf32>{
//       %0 = "tosa.conv2d"(%input, %weights, %bias) {pad = array<i64: 0, 0, 0, 0>, stride = array<i64: 1, 1>, dilation = array<i64: 2, 1>} : (tensor<1x49x42x27xf32>, tensor<28x3x3x27xf32>, tensor<28xf32>)  -> (tensor<1x45x40x28xf32>)
//       %1 = "tosa.add"(%0,%0): (tensor<1x45x40x28xf32>,tensor<1x45x40x28xf32>) -> tensor<1x45x40x28xf32>
//       %2 = "tosa.mul"(%1, %1) {shift = 0 : i32 } : (tensor<1x45x40x28xf32>, tensor<1x45x40x28xf32>) -> tensor<1x45x40x28xf32>
//      return  %2: tensor<1x45x40x28xf32>
//    }
//    }


// module{
//   func.func@matmul() -> tensor<2x2x1xi32>{
//     %1 = "tosa.const"(){value = dense<[[[1, 2, 3], [4, 5, 6]], [[1, 2, 3], [4, 5, 6]]]>: tensor<2x2x3xi32>} :()->tensor<2x2x3xi32>
//     %2 = "tosa.const"(){value = dense<[[[7], [8], [9]], [[7], [8], [9]]]> : tensor<2x3x1xi32>} :()->tensor<2x3x1xi32>
//     %3 = "tosa.matmul"(%1, %2) : (tensor<2x2x3xi32>, tensor<2x3x1xi32>) -> tensor<2x2x1xi32>
//   return %3: tensor<2x2x1xi32>
//   }
//   func.func @add(%arg0: tensor<3xi32>) -> tensor<3xi32>  {
//     %1 = "tosa.const"() {value = dense<[1, 2, 4]> : tensor<3xi32>} : () -> tensor<3xi32>
//     %2 = "tosa.add"(%arg0, %1) : (tensor<3xi32>, tensor<3xi32>) -> tensor<3xi32>
//   return %2 : tensor<3xi32>
//   }
// }