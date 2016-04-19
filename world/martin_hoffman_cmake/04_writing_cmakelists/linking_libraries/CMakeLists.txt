#
#
cmake_minimum_required (VERSION 2.8)


# cap 4.8 Linking Libraries
message ("--------------------------------------------------------")

project (Project)
add_executable (app file1.c)


# add_compile_options() adds options to the compiler command line for sources
# in the current directory and below. This command can be used to add any
# options, but alternative commands exist to add preprocessor definitions:
# target_compile_definitions() and add_definitions()
# or include directories:
# target_include_directories() and include_directories()
if (COMMAND add_compile_options)
  add_compile_options (-DWARN_ALL)
else ()
  message ("add_compile_options not supported by CMake ${CMAKE_VERSION}")
endif ()


# Adds definitions to the compiler command line for sources in the
# current directory and below. This command can be used to add any flags,
# but it is intended to add preprocessor definitions.
add_definitions (-DNDEBUG -DUNICODE -DWCHAR)


# Specify compile definitions to use when compiling a given <target>
# The named <target> must have been created by a command such as
# add_executable() or add_library() and must not be an Imported Target.
# The INTERFACE, PUBLIC and PRIVATE keywords are required to specify
# the scope of the following arguments.
target_compile_definitions (app PUBLIC -DTARGET -DPUBLIC)


# Add the given directories to those the compiler uses
# to search for include files. Relative paths are interpreted as relative
# to the current source directory.
include_directories (dir1)


# Add include directories to a target.
# The INTERFACE, PUBLIC and PRIVATE keywords are required to specify
# the scope of the following arguments.
target_include_directories (app PUBLIC dir2)




# search for m library in the system. What do I do in windows?
find_library (M_LIB m)
message ("app will link with m library from: ${M_LIB}")

target_link_libraries (app ${M_LIB})


# does it compile ? can you run it ?
message ("you should now BUILD and RUN the app to see the result")


message ("--------------------------------------------------------")
