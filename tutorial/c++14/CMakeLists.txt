#
# CMake file for C++14 directory
#
cmake_minimum_required(VERSION 3.0)
project(cplusplus_14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(01_binary_literals)
add_subdirectory(02_generalized_return_type_deduction)
add_subdirectory(03_decltype_auto)
add_subdirectory(04_generalized_lambda_captures)
add_subdirectory(05_generic_lambdas)
add_subdirectory(06_variable_templates)
add_subdirectory(07_extended_constexpr)
add_subdirectory(08_deprecated_attribute)
add_subdirectory(09_digit_separators)
add_subdirectory(10_shared_locking)
add_subdirectory(11_user_defined_literals)
add_subdirectory(12_make_unique)
add_subdirectory(13_type_transformation_alias)
