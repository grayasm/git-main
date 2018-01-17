# CMakeLists.txt file for root directory.
cmake_minimum_required(VERSION 3.2)
project(git-main)

# Add -DDEBUG because cmake only adds -D_DEBUG on windows and -g on linux.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
# Fix gcc-4.8.5 strange error on enum.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")


add_subdirectory(world/CppUnit/cppunit/src/cppunit)
add_subdirectory(lib/misc)
add_subdirectory(lib/misctest)
add_subdirectory(lib/fxcore)
add_subdirectory(lib/fxcmAdapter)
add_subdirectory(app/fxmon)