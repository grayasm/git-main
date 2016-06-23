cmake_minimum_required(VERSION 3.2)

# ----------------------------------------
add_executable(01_matrix_vec_mul_book
               01_matrix_vec_mul_book.cpp)

# ----------------------------------------
find_package(OpenMP REQUIRED)
add_executable(01_matrix_vec_mul_book_omp
               01_matrix_vec_mul_book_omp.cpp)

target_compile_options(01_matrix_vec_mul_book_omp PRIVATE ${OpenMP_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")

#if(OPENMP_FOUND)
#  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()
