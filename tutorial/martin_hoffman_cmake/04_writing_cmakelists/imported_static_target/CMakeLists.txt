# Testing a concept that existed in MW during the creationg of the CMake port.
# MW CMake structure had a defined macro in the source code like this:
# #ifdef CMAKE_STRUCTURE
# #include <misc/mwString.hpp>
# #else
# #include <mwString.hpp>
# #endif // CMAKE_STRUCTURE
#
# On customer's side, there are cases when all headers are copied into one
# folder, so there is no <misc/mwString.hpp> valid there.


cmake_minimum_required (VERSION 2.8)


add_subdirectory (lib1)
add_subdirectory (lib2)

# configure once, build, comment 2 lines above and uncomment below, and again.
# add_subdirectory (app)
