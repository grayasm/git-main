#
#
cmake_minimum_required (VERSION 2.8)
project (foo)
add_executable (foo foo.c)


message ("--------------------------------------------------------")

# 4.5 Checking versions of CMake
if (${CMAKE_VERSION} VERSION_GREATER 1.6.1)
    message ("CMake ${CMAKE_VERSION} > 1.6.1")
else ()
    message ("CMake ${CMAKE_VERSION} <= 1.6.1")
endif ()

# 4.5 Check if a command exists.
if (COMMAND get_source_file_property)
    message ("get_source_file_property command exists.")
    get_source_file_property(FOO_LOC_PROP foo.c LOCATION)
    message ("foo.c location=${FOO_LOC_PROP}")
else ()
    message (FATAL_ERROR "get_source_file_property does not exists.")
endif ()

message ("--------------------------------------------------------")
