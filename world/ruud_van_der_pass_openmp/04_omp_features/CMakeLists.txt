cmake_minimum_required(VERSION 3.2)


find_package(OpenMP REQUIRED)

# there is no OpenMP_CXX_LIBRARIES only OpenMP_CXX_FLAGS
# you may think only compiler needs it, but NO, the linker wants it also.

set (CMAKE_C_FLAGS_2     ${CMAKE_C_FLAGS})
set (CMAKE_CXX_FLAGS_2   ${CMAKE_CXX_FLAGS})

if(OPENMP_FOUND)
  set (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS}    ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${OpenMP_CXX_FLAGS}")
endif()


add_executable(01_parallel_block      01_parallel_block.cpp)
add_executable(01_parallel_book       01_parallel_book.cpp)
add_executable(01_parallel_branching_illegal 01_parallel_branching_illegal.cpp)
add_executable(01_parallel_throw_restriction 01_parallel_throw_restriction.cpp)
add_executable(01_parallel_throw_illegal     01_parallel_throw_illegal.cpp)
add_executable(02_loop                  02_loop.cpp)
add_executable(02_loop_list_invalid     02_loop_list_invalid.cpp)
add_executable(02_loop_map              02_loop_map.cpp)
add_executable(02_loop_set              02_loop_set.cpp)
add_executable(02_loop_vector           02_loop_vector.cpp)
add_executable(03_sections_intro        03_sections_intro.cpp)
add_executable(03_sections_ind          03_sections_ind.cpp)
add_executable(04_single_book           04_single_book.cpp)
add_executable(04_single_init           04_single_init.cpp)
add_executable(05_shared                05_shared.cpp)
add_executable(06_private               06_private.cpp)
add_executable(07_lastprivate           07_lastprivate.cpp)
