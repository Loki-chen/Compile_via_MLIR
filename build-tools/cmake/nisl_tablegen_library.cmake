

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
  list(APPEND _INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
  list(TRANSFORM _INCLUDE_DIRS PREPEND "-I")

  
  set(_OUTPUTS)

  list(GET _RULE_OUTS 0 _COMMAND)


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
  tablegen(${_TBLGEN} ${_FILE} ${_COMMAND} ${_INCLUDE_DIRS})
  list(APPEND _OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/${_FILE})
  endwhile()


  add_custom_target(${_NAME}_target DEPENDS ${_OUTPUTS})
  set_target_properties(${_NAME}_target PROPERTIES FOLDER "Tablegenning")
 
  add_library(${_NAME} INTERFACE)
  add_dependencies(${_NAME} ${_NAME}_target)
endfunction(nisl_tablegen_library)


# set(LLVM_TARGET_DEFINITIONS InstCombineTables.td)
# tablegen(LLVM InstCombineTables.inc -gen-searchable-tables)
# add_public_tablegen_target(InstCombineTableGen)