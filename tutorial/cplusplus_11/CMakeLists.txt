#
# CMake file for cplusplus_11 directory
#
cmake_minimum_required(VERSION 3.0)
project(cplusplus_11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(02.12_keywords)
add_subdirectory(05.1.2_lambda_expressions)
add_subdirectory(06.5.4_the_range_based_for_statement)
add_subdirectory(07.2_enumeration_declarations)
add_subdirectory(08.4_function_definitions)
add_subdirectory(08.5_initializers)
add_subdirectory(10.3_virtual_functions)
add_subdirectory(12.6_initialization)
add_subdirectory(12.8_copying_and_moving_objects)
add_subdirectory(20.7.1_unique_ptr)
add_subdirectory(20.7.2.2_shared_ptr)
add_subdirectory(20.7.2.3_weak_ptr)
add_subdirectory(30.3_threads)
add_subdirectory(30.4_mutual_exclusion)
add_subdirectory(30.5_condition_variables)
add_subdirectory(30.6_futures)
