include(CMakeParseArguments)


# Note:
# nisl_cc_binary will create a binary called ${PACKAGE_NAME}_${NAME}, e.g.
# nisl_base_foo with an alias to ${PACKAGE_NS}::${NAME}.
#
# Usage:
# nisl_cc_library(
#   NAME
#     awesome
#   HDRS
#     "a.h"
#   SRCS
#     "a.cc"
#   PUBLIC
# )
#
# nisl_cc_binary(
#   NAME
#     awesome_tool
#   SRCS
#     "awesome-tool-main.cc"
#   DEPS
#     nisl::awesome
# )

function(nisl_cc_binary)
    cmake_parse_arguments(
      _RULE
      "EXCLUDE_FROM_ALL;HOSTONLY;TESTONLY;SETUP_INSTALL_RPATH"
      "NAME"
      "SRCS;COPTS;DEFINES;LINKOPTS;DATA;DEPS"
      ${ARGN}
    )
    

    set(_NAME "${_RULE_NAME}")

    add_executable(${_NAME})

    target_sources(${_NAME}
        PRIVATE
          ${_RULE_SRCS}
      )

    target_link_libraries(${_NAME}
      PUBLIC
        ${_RULE_DEPS}
    )


    install(TARGETS ${_NAME})

 
endfunction(nisl_cc_binary)

