cmake_minimum_required(VERSION 3.2)

project(widgets_and_layouts CXX)

# http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# https://cmake.org/cmake/help/v3.6/manual/cmake-qt.7.html#autouic
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)


add_executable(x x)
target_link_libraries(x Qt5::Widgets)
