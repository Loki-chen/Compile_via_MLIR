

// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// This files defines a helper to trigger the registration of dialects to
// the system.
//
// Based on MLIR's InitAllDialects but for NISL dialects.

#ifndef NISL_COMPILER_TOOLS_INIT_DIALECTS_H_
#define NISL_COMPILER_TOOLS_INIT_DIALECTS_H_

#include "mlir/IR/Dialect.h"
#include "init_mlir_dialects.h"
#include "mlir/Dialect/Tosa/IR/TosaOps.h"

namespace mlir {
namespace compiler {

inline void registerAllDialects(DialectRegistry &registry) {
    registerMlirDialects(registry);
    
    // register input dialect: TOSA
    registry.insert<tosa::TosaDialect>();

    

}

}  // namespace compiler
}  // namespace mlir

#endif  // NISL_COMPILER_TOOLS_INIT_DIALECTS_H_
