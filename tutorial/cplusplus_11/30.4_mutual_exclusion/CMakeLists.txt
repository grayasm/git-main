# This is CMakeLists.txt for 30.4_mutual_exclusion

find_package (Threads REQUIRED)

add_executable(01_race_condition 01_race_condition.cpp)
add_executable(02_race_avoided 02_race_avoided.cpp)
add_executable(03_lock_guard 03_lock_guard.cpp)

target_link_libraries(01_race_condition ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(02_race_avoided ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(03_lock_guard ${CMAKE_THREAD_LIBS_INIT})
