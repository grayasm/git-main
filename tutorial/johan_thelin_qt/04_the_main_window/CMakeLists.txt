cmake_minimum_required(VERSION 3.2)

project(the_main_window CXX)

# http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# https://cmake.org/cmake/help/v3.6/manual/cmake-qt.7.html#autouic
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)


add_executable(01_signal_trivial 01_signal_trivial.cpp
                                 01_signal_trivial.h)
target_link_libraries(01_signal_trivial Qt5::Widgets)

add_executable(02_signal_sender  02_signal_sender.cpp
                                 02_signal_sender.h)
target_link_libraries(02_signal_sender Qt5::Widgets)

add_executable(03_signal_subclass  03_signal_subclass.cpp
                                   03_signal_subclass.h)
target_link_libraries(03_signal_subclass Qt5::Widgets)

add_executable(04_signal_mapper  04_signal_mapper.cpp
                                 04_signal_mapper.h)
target_link_libraries(04_signal_mapper Qt5::Widgets)

add_subdirectory(01_SDI)
add_subdirectory(02_MDI)
add_subdirectory(03_DOCK)
