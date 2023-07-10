include(CMakeParseArguments)

# iree_cc_library()
#
# CMake function to imitate Bazel's cc_library rule.
#
# Parameters:
# PACKAGE: Name of the package (overrides actual path)
# NAME: name of target (see Note)
# HDRS: List of public header files for the library
# TEXTUAL_HDRS: List of public header files that cannot be compiled on their own
# SRCS: List of source files for the library
# DATA: List of other targets and files required for this binary
# DEPS: List of other libraries to be linked in to the binary targets
# COPTS: List of private compile options
# DEFINES: List of public defines
# INCLUDES: Include directories to add to dependencies
# LINKOPTS: List of link options
# PUBLIC: Add this so that this library will be exported under iree::
# Also in IDE, target will appear in IREE folder while non PUBLIC will be in IREE/internal.
# TESTONLY: When added, this target will only be built if user passes -DIREE_BUILD_TESTS=ON to CMake.
# SHARED: If set, will compile to a shared object.
# WINDOWS_DEF_FILE: If set, will add a windows .def file to a shared library link
# Note:
# By default, iree_cc_library will always create a library named iree_${NAME},
# and alias target iree::${NAME}. The iree:: form should always be used.
# This is to reduce namespace pollution.
#
# iree_cc_library(
#   NAME
#     awesome
#   HDRS
#     "a.h"
#   SRCS
#     "a.cc"
# )
# iree_cc_library(
#   NAME
#     fantastic_lib
#   SRCS
#     "b.cc"
#   DEPS
#     iree::package::awesome # not "awesome" !
#   PUBLIC
# )
#
# iree_cc_library(
#   NAME
#     main_lib
#   ...
#   DEPS
#     iree::package::fantastic_lib
# )
function(nisl_cc_library)
  cmake_parse_arguments(
    _RULE
    "PUBLIC;TESTONLY;SHARED"
    "PACKAGE;NAME;WINDOWS_DEF_FILE"
    "HDRS;SRCS;COPTS;DEFINES;LINKOPTS;DATA;DEPS;INCLUDES"
    ${ARGN}
  )
  

  set(_NAME "${_RULE_NAME}")

  add_library(${_NAME})


  # Sources get added to the object library.
  target_sources(${_NAME}
      PRIVATE
        ${_RULE_HDRS}
        ${_RULE_SRCS}
  )
  target_link_libraries(${_NAME}
      PUBLIC
        ${_RULE_DEPS}
  )

endfunction(nisl_cc_library)
