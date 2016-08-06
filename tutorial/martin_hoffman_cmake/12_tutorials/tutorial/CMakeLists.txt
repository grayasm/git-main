#
#
# The version number
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)


# configure a header file to pass some of the CMake settings to the source code
message ("PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message ("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")

# copies <input> to <output> and substitutes variable values referenced in the
# file content
configure_file (
  "${PROJECT_SOURCE_DIR}/tutorial/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/tutorial/TutorialConfig.h"
  )


# PROJECT_BINARY_DIR is a cmake variable from the last project() command.
# add the binary tree to the search path for include files to find TutorialConfig.h
include_directories ("${PROJECT_BINARY_DIR}"
                     "${PROJECT_BINARY_DIR}/tutorial")

#
# add the MathFunctions library?
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/mathfunc")
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
message ("USE_MYMATH=${USE_MYMATH}")
message ("EXTRA_LIBS=${EXTRA_LIBS}")

#
# add the executable
add_executable (Tutorial tutorial.cxx)
target_link_libraries (Tutorial ${EXTRA_LIBS})

#
# add INSTALL target
# from Visual Studio build INSTALL
# from linux terminal: make install [DESTDIR=...]
install (TARGETS Tutorial                                          DESTINATION bin)
install (FILES   "${PROJECT_BINARY_DIR}/tutorial/TutorialConfig.h" DESTINATION include)


# enable CTest and testing framework
# on Visual Studio run RUN_TESTS target
# on linux terminal: cd build/tutorial;  ctest;

enable_testing ()
# does the application run?
add_test (TutorialRuns Tutorial 25)

# does it sqrt of 25 ?
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25
  PROPERTIES  PASS_REGULAR_EXPRESSION  "25 is 5")

# can it handle negative numbers ?
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative
  PROPERTIES  PASS_REGULAR_EXPRESSION  "-25 is 0")

# does it handle small numbers ?
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall
  PROPERTIES  PASS_REGULAR_EXPRESSION  "0.0001 is 0.01")

# does the usage message work ?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage
  PROPERTIES  PASS_REGULAR_EXPRESSION  "Usage:.*number")
