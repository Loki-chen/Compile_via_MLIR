# Licensed under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

include(CMakeParseArguments)


# nisl_tablegen_library()
#
# Runs nisl-tablegen to produce some artifacts.
function(nisl_tablegen_library)
    cmake_parse_arguments(
        _RULE
        "TESTONLY"
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

  set(LLVM_TARGET_DEFINITIONS ${_RULE_TD_FILE})
  set(_INCLUDE_DIRS
    "${MLIR_INCLUDE_DIRS}"
    "${NISL_SOURCE_DIR}/compiler/src"
    "${NISL_BINARY_DIR}/compiler/src"
  )
  if(DEFINED NISL_COMPILER_TABLEGEN_INCLUDE_DIRS)
    list(APPEND _INCLUDE_DIRS ${NISL_COMPILER_TABLEGEN_INCLUDE_DIRS})
  endif()
  list(APPEND _INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
  
  set(_OUTPUTS)
  while(_RULE_OUTS)
    # Eat any number of flags (--a --b ...) and a single file.
    # Flags only impact the successively declared file.
    set(_COMMAND)
    set(_FILE)
    while(_RULE_OUTS AND NOT _FILE)
      list(GET _RULE_OUTS 0 _PART)
      list(REMOVE_AT _RULE_OUTS 0)
      if(${_PART} MATCHES "^-.*")
        # Flag (- or --).
        list(APPEND _COMMAND ${_PART})
      else()
        # File path.
        set(_FILE ${_PART})
      endif()
    endwhile()
    tablegen(${_TBLGEN} ${_FILE} ${_COMMAND} ${_INCLUDE_DIRS})
    list(APPEND _OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/${_FILE})
   endwhile()

   add_custom_target(${_NAME}_target DEPENDS ${_OUTPUTS})
   set_target_properties(${_NAME}_target PROPERTIES FOLDER "Tablegenning")
 
   add_library(${_NAME} INTERFACE)
   add_dependencies(${_NAME} ${_NAME}_target)
  add_library(${_RULE_NAME} ALIAS ${_NAME})
endfunction(nisl_tablegen_library)
