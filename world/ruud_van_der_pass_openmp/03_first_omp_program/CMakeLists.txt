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


add_executable(01_matrix_vec_mul_book      01_matrix_vec_mul_book.cpp)
add_executable(01_matrix_vec_mul_book_omp  01_matrix_vec_mul_book_omp.cpp)
add_executable(02_tmatrix_mul              02_tmatrix_mul.cpp)
add_executable(02_tmatrix_mul_omp          02_tmatrix_mul_omp.cpp)
add_executable(03_tmatrix_mul_bench        03_tmatrix_mul_bench.cpp)
add_executable(03_tmatrix_mul_bench_omp    03_tmatrix_mul_bench_omp.cpp)
add_executable(04_incorrect_omp            04_incorrect_omp.cpp)
add_executable(05_omp_get_thread_num       05_omp_get_thread_num.cpp)
target_compile_definitions(05_omp_get_thread_num PUBLIC _OPENMP=201107)

set (CMAKE_C_FLAGS       ${CMAKE_C_FLAGS_2})
set (CMAKE_CXX_FLAGS     ${CMAKE_CXX_FLAGS_2})
add_executable(06_disable_omp              06_disable_omp.cpp)
