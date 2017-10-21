#
# CMake file for cplusplus_11 directory
#
cmake_minimum_required(VERSION 3.0)
project(cplusplus_11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(5.1.2_lambda_expressions)
add_subdirectory(20.7.2.2_shared_ptr)