# Copyright 2020 The IREE Authors
#
# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

include(CMakeParseArguments)

# nisl_tablegen_doc()
#
# Runs nisl-tablegen to produce documentation. For TableGen'ing others,
# please use nisl_tablegen_library().
#
# One-value parameters:
# * NAME: base name of the target. The real target name is mangled from this
#         given name with the package name
# * TBLGEN: the base project to pass to TableGen
#
# Multi-value parameters:
# * TD_FILE: Input .td files
# * OUTS: TableGen generator commands and their outputs in the format of
#         `-gen-<something> <output-file-name>`. Note that the generator
#         commands should only be for documentation.
function(nisl_tablegen_doc)
  if(NOT NISL_BUILD_DOCS)
    return()
  endif()

  cmake_parse_arguments(
    _RULE
    ""
    "NAME;TBLGEN"
    "TD_FILE;OUTS"
    ${ARGN}
  )


  set(_NAME "${_RULE_NAME}")

  if(${_RULE_TBLGEN} MATCHES "NISL")
    set(_TBLGEN "NISL")
  else()
    set(_TBLGEN "MLIR")
  endif()


  set(_INCLUDE_DIRS
    "${MLIR_INCLUDE_DIRS}"
    "${NISL_SOURCE_DIR}/compiler/src"
    "${NISL_BINARY_DIR}/compiler/src"
  )
  list(APPEND _INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
  list(TRANSFORM _INCLUDE_DIRS PREPEND "-I")

  set(_INPUTS ${_RULE_TD_FILE})
  set(LLVM_TARGET_DEFINITIONS ${_INPUTS})

  set(_OUTPUTS)
  while(_RULE_OUTS)
    list(GET _RULE_OUTS 0 _COMMAND)
    list(REMOVE_AT _RULE_OUTS 0)
    list(LENGTH _RULE_OUTS _LEN)
    if(_LEN GREATER 1)
      list(GET _RULE_OUTS 0 _DIALECT)
      list(REMOVE_AT _RULE_OUTS 0)
    endif()
    list(GET _RULE_OUTS 0 _OUTPUT)
    list(REMOVE_AT _RULE_OUTS 0)

    # TableGen this output with the given command.
    tablegen(${_TBLGEN} ${_OUTPUT} ${_COMMAND} ${_DIALECT} ${_INCLUDE_DIRS})
    list(APPEND _OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/${_OUTPUT})
  endwhile()

  # Put all dialect docs at one place.
  set(_DOC_DIR ${NISL_BINARY_DIR}/doc/Dialects/)
  # Set a target to drive copy.
  add_custom_target(${_NAME}_target
            ${CMAKE_COMMAND} -E make_directory ${_DOC_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${_OUTPUTS} ${_DOC_DIR}
    DEPENDS ${_OUTPUTS})
  set_target_properties(${_NAME}_target PROPERTIES FOLDER "Tablegenning")

  # Register this dialect doc to nisl-doc.
  add_dependencies(nisl-doc ${_NAME}_target)
endfunction()
