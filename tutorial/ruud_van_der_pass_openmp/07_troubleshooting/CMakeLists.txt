cmake_minimum_required(VERSION 3.2)


find_package(OpenMP REQUIRED)

# there is no OpenMP_CXX_LIBRARIES only OpenMP_CXX_FLAGS
# you may think only compiler needs it, but NO, the linker wants it also.

if(OPENMP_FOUND)
  set (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS}    ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${OpenMP_CXX_FLAGS}")
endif()



add_executable(01_data_race_condition           01_data_race_condition.cpp)
add_executable(02_implied_sharing               02_implied_sharing.cpp)
add_executable(03_missing_private               03_missing_private.cpp)
add_executable(04_implicitly_shared             04_implicitly_shared.cpp)
add_executable(05_incorrect_use_of_private      05_incorrect_use_of_private.cpp)
add_executable(06_incorrect_use_of_master       06_incorrect_use_of_master.cpp)
add_executable(07_assumptions_scheduling        07_assumptions_scheduling.cpp)
add_executable(08_incorrect_nested              08_incorrect_nested.cpp)
add_executable(09_illegal_barrier               09_illegal_barrier.cpp)
add_executable(10_error_curly_brackets          10_error_curly_brackets.cpp)
add_executable(11_not_thread_safe               11_not_thread_safe.cpp)
add_executable(12_unsafe_cpp_object             12_unsafe_cpp_object.cpp)
add_executable(13_deadlock                      13_deadlock.cpp)
