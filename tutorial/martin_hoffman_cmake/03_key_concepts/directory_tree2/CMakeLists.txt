
# Hello application links with static lib1.
# CMake policy requires command cmake_minimum_required at the top of the project.

cmake_minimum_required (VERSION 2.8)
project (Hello)
add_subdirectory (lib1)
add_subdirectory (app)
