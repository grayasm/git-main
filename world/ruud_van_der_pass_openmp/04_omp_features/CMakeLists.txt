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
