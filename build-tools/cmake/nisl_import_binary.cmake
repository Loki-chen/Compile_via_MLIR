# Copyright 2023 The IREE Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

include(CMakeParseArguments)

# nisl_import_binary()
#
# CMake function to import an executable/binary file into a CMake target.
# This imports from the directory specified by NISL_HOST_BIN_DIR, and
# that variable _must_ be set for calls to the function to be valid.
#
# Parameters:
# NAME: name of target/binary (see Usage below)
#
# Usage:
#   if(BUILD_AWESOME_TOOL)
#     nisl_cc_binary(
#       NAME awesome-tool
#       SRCS "awesome-tool-main.cc"
#     )
#   elseif(NISL_HOST_BIN_DIR)
#     # Import '${NISL_HOST_BIN_DIR}/awesome-tool[.exe]' into the
#     # CMake target 'awesome-tool'.
#     nisl_import_binary(NAME awesome-tool)
#   else()
#     message(STATUS "Not building or importing awesome-tool")
#   endif()
function(nisl_import_binary)
  cmake_parse_arguments(
    _RULE
    ""
    "NAME"
    ""
    ${ARGN}
  )

  # TODO(scotttodd): optional 'TARGET' argument (that defaults to NAME)
  # TODO(scotttodd): SHARED_LIBRARY_DEPS argument?

  if(NOT NISL_HOST_BIN_DIR)
    message(FATAL_ERROR "NISL_HOST_BIN_DIR must be set to use nisl_import_binary")
  endif()

  # We can't use CMAKE_EXECUTABLE_SUFFIX for host tools when cross-compiling for
  # platforms like Emscripten that set the suffix (e.g. to .js).
  # https://gitlab.kitware.com/cmake/cmake/-/issues/17553
  set(_HOST_EXECUTABLE_SUFFIX "")
  if(CMAKE_HOST_WIN32)
    set(_HOST_EXECUTABLE_SUFFIX ".exe")
  endif()

  set(_FULL_BINARY_NAME "${_RULE_NAME}${_HOST_EXECUTABLE_SUFFIX}")
  set(_BINARY_PATH "${NISL_HOST_BIN_DIR}/${_FULL_BINARY_NAME}")
  file(REAL_PATH "${_BINARY_PATH}" _BINARY_PATH
       BASE_DIRECTORY ${NISL_ROOT_DIR} EXPAND_TILDE)

  if(NOT EXISTS ${_BINARY_PATH})
    message(FATAL_ERROR "Could not find '${_FULL_BINARY_NAME}' under "
            "'${NISL_HOST_BIN_DIR}'\n(Expanded to '${_BINARY_PATH}').\n"
            "Ensure that NISL_HOST_BIN_DIR points to a complete binary directory.")
  endif()

  add_executable(${_RULE_NAME} IMPORTED GLOBAL)
  set_property(TARGET "${_RULE_NAME}" PROPERTY IMPORTED_LOCATION "${_BINARY_PATH}")
endfunction()
