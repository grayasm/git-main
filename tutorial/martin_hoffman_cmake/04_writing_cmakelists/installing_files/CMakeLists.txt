# Mastering CMake - cap 4.11 Installing Files
# I created a simple structure with:
#     - app1 executable linked against
#     - libshared.so  shared object
#     - libstatic.a   static library
#     - headers1/header1.hpp header only interface
#     - resources1/*.png     image only interface
#
# Each target will try to install its files into the CMAKE_INSTALL_PREFIX
# which by default is either /usr/local or C:\Program Files\<ProjectName>
#
# app1 can run from its build location without any evn setup.
# When installed, app1 will search libshared.so in the system or LD_LIBRARY_PATH

cmake_minimum_required (VERSION 3.4)
project ( how_to_install )
add_subdirectory (resources1)
add_subdirectory (headers1)
add_subdirectory (static1)
add_subdirectory (shared1)
add_subdirectory (app1)

# Packaging is available only ONCE for the entire project with commands:
# make package
# make package_source

# CPack must be included only 1 time at the end of top file.
include (CPack)
