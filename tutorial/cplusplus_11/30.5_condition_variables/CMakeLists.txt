# This is CMakeLists.txt for 30.5_condition_variables

find_package (Threads REQUIRED)

add_executable(01_notify_all 01_notify_all.cpp)
add_executable(02_notify_one 02_notify_one.cpp)

target_link_libraries(01_notify_all ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(02_notify_one ${CMAKE_THREAD_LIBS_INIT})
