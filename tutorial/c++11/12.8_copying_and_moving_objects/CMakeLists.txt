# CMakeLists.txt file for 12.8_copying_and_moving_objects

add_executable(01_lvalue_and_rvalue  01_lvalue_and_rvalue.cpp)

set(CMAKE_CXX_FLAGS_G "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS " -std=c++03")
add_executable(02_a_use_case_for_move_semantics  02_a_use_case_for_move_semantics.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_G}")
add_executable(03_rvalue_references  03_rvalue_references.cpp)
add_executable(04_move_semantics  04_move_semantics.cpp)
add_executable(05_if_it_has_a_name  05_if_it_has_a_name.cpp)
add_executable(06_return_value_optimization  06_return_value_optimization.cpp)
add_executable(07_a_naive_std_move  07_a_naive_std_move.cpp)
