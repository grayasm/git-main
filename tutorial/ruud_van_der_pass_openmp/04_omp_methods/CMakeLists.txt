cmake_minimum_required(VERSION 3.2)


find_package(OpenMP REQUIRED)

# there is no OpenMP_CXX_LIBRARIES only OpenMP_CXX_FLAGS
# you may think only compiler needs it, but NO, the linker wants it also.

if(OPENMP_FOUND)
  set (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS}    ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${OpenMP_CXX_FLAGS}")
endif()


add_executable(01_omp_set_num_threads           01_omp_set_num_threads.cpp)
add_executable(02_omp_get_max_threads           02_omp_get_max_threads.cpp)
add_executable(03_omp_get_thread_num            03_omp_get_thread_num.cpp)
add_executable(04_omp_get_num_procs             04_omp_get_num_procs.cpp)
add_executable(05_omp_in_parallel               05_omp_in_parallel.cpp)
add_executable(06_omp_set_dynamic               06_omp_set_dynamic.cpp)
add_executable(07_omp_set_nested                07_omp_set_nested.cpp)
add_executable(08_omp_lock_t_methods            08_omp_lock_t_methods.cpp)
add_executable(09_omp_nest_lock_t_methods       09_omp_nest_lock_t_methods.cpp)
add_executable(10_omp_get_wtime                 10_omp_get_wtime.cpp)
add_executable(11_omp_get_wtick                 11_omp_get_wtick.cpp)
add_executable(12_omp_set_schedule              12_omp_set_schedule.cpp)
add_executable(13_omp_get_thread_limit          13_omp_get_thread_limit.cpp)
add_executable(14_omp_set_max_active_levels     14_omp_set_max_active_levels.cpp)
add_executable(15_omp_get_level                 15_omp_get_level.cpp)
add_executable(16_omp_get_anchestor_thread_num  16_omp_get_anchestor_thread_num.cpp)
add_executable(17_omp_get_team_size             17_omp_get_team_size.cpp)
add_executable(18_omp_get_active_level          18_omp_get_active_level.cpp)
add_executable(19_omp_in_final                  19_omp_in_final.cpp)
