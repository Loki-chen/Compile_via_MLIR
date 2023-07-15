

// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// This file defines a helper to add passes to the global registry.

#ifndef NISL_COMPILER_TOOLS_INIT_PASSES_H_
#define NISL_COMPILER_TOOLS_INIT_PASSES_H_


#include "init_mlir_passes.h"
#include "Conversion/TOSA/Passes.h"
#include "Conversion/WarpEntryPoint/Passes.h"

namespace mlir {
namespace compiler {

// Registers core passes and other important passes to the global registry.
inline void registerAllPasses() {
    registerMlirPasses();
    // init tosa pass
    InputTosa::registerPasses();
    // init warpentryPoint pass
    WarpEntryPoint::registerPasses();


}

}  // namespace compiler
}  // namespace mlir

#endif  // NISL_COMPILER_TOOLS_INIT_PASSES_H_
