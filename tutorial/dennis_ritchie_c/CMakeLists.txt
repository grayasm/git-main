# CMakeLists file for Cap.1 A Tutorial Introduction

cmake_minimum_required(VERSION 3.0)
project(dennis_ritchie_c)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

add_subdirectory(01_introduction)
add_subdirectory(02_types_operators_expr)
add_subdirectory(03_control_flow)