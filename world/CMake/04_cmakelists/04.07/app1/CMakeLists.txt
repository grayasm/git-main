# CMake file

set (SRC app1.cpp)
add_executable (app1 ${SRC})
target_include_directories (app1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../headers1
    ${CMAKE_CURRENT_SOURCE_DIR}/../static1
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared1)
target_link_libraries (app1 PRIVATE static1 shared1)
