cmake_minimum_required(VERSION 3.2)

# ----------------------------------------
add_executable(01_matrix_vec_mul_book
               01_matrix_vec_mul_book.cpp)

# ----------------------------------------
find_package(OpenMP REQUIRED)

# there is no OpenMP_CXX_LIBRARIES only OpenMP_CXX_FLAGS
# you may think only compiler needs it, but NO, the linker wants it also.

if(OPENMP_FOUND)
  set (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS}    ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${OpenMP_CXX_FLAGS}")
endif()

add_executable(01_matrix_vec_mul_book_omp  01_matrix_vec_mul_book_omp.cpp)

# ----------------------------------------
add_executable(02_tmatrix_mul      02_tmatrix_mul.cpp)
add_executable(02_tmatrix_mul_omp  02_tmatrix_mul_omp.cpp)

# ----------------------------------------
add_executable(03_tmatrix_mul_bench      03_tmatrix_mul_bench.cpp)
add_executable(03_tmatrix_mul_bench_omp  03_tmatrix_mul_bench_omp.cpp)
