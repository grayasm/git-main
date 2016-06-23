cmake_minimum_required(VERSION 2.8)

# ----------------------------------------
add_executable(01_matrix_vec_mul_book
               01_matrix_vec_mul_book.cpp)

# ----------------------------------------
find_package(OpenMP REQUIRED)
add_executable(01_matrix_vec_mul_book_omp
               01_matrix_vec_mul_book_omp.cpp)
target_compile_options(01_matrix_vec_mul_book_omp
               PRIVATE ${OpenMP_CXX_FLAGS})
