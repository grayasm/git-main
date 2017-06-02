cmake_minimum_required(VERSION 3.2)

project(the_qt_way_of_cpp CXX)

add_executable(01_simple_cpp 01_simple_cpp.cpp)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(02_dynamic_memory_without_qt 02_dynamic_memory_without_qt.cpp)
target_link_libraries(02_dynamic_memory_without_qt Qt5::Core)

add_executable(03_dynamic_memory_with_qt 03_dynamic_memory_with_qt.cpp)
target_link_libraries(03_dynamic_memory_with_qt Qt5::Core)

add_executable(04_using_qstring 04_using_qstring.cpp)
target_link_libraries(04_using_qstring Qt5::Core)
