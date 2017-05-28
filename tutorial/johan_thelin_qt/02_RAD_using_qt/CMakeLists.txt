cmake_minimum_required(VERSION 3.2)

project(RAD_using_qt CXX)

# http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# https://cmake.org/cmake/help/v3.6/manual/cmake-qt.7.html#autouic
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

set(SRC main.cpp
        listdialog.cpp
		listdialog.h
		listdialog.ui
		editdialog.cpp
		editdialog.h
		editdialog.ui)

add_executable(addressbook ${SRC})
target_link_libraries(addressbook Qt5::Widgets)
