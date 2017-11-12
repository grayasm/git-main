#
# CMake file for cplusplus_11 directory
#
cmake_minimum_required(VERSION 3.0)
project(cplusplus_11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(2.12_keywords)
add_subdirectory(5.1.2_lambda_expressions)
add_subdirectory(7.1.6.2_simple_type_specifiers)
add_subdirectory(20.7.1_unique_ptr)
add_subdirectory(20.7.2.2_shared_ptr)
add_subdirectory(20.7.2.3_weak_ptr)
add_subdirectory(30.3_threads)
add_subdirectory(30.4_mutual_exclusion)
add_subdirectory(30.5_condition_variables)
add_subdirectory(30.6_futures)
