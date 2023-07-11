# Copyright 2022 The IREE Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception



# if(NISL_INPUT_MHLO)
#   add_subdirectory(MHLO)
#   add_subdirectory(StableHLO)
# endif()
# if(NISL_INPUT_TORCH)
#   add_subdirectory(TMTensor)
# endif()

  add_subdirectory(TOSA)

