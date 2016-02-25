# Mastering CMake - cap 4.11 Installing Files
# I created a simple structure with executable,shared and static objects,
# and headers only interface and a resource directory with 1 image.
# The reason is to test the intall command (e.g. make install) and play with
# CMAKE_INSTALL_PREFIX (by default on linux is /usr/local
                        and default on win  is C:\Program Files\<ProjectName>)

cmake_minimum_required (VERSION 3.4)
project ( how_to_install )
add_subdirectory (resources1)
add_subdirectory (headers1)
add_subdirectory (static1)
add_subdirectory (shared1)
add_subdirectory (app1)
