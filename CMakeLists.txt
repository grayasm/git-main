# CMakeLists.txt file for root directory.
cmake_minimum_required(VERSION 3.2)
project(git-main)
add_subdirectory(world/CppUnit/cppunit/src/cppunit)
add_subdirectory(lib/misc)
add_subdirectory(lib/misctest)
add_subdirectory(lib/fxcore)
add_subdirectory(lib/fxcmAdapter)
add_subdirectory(app/fxmon)