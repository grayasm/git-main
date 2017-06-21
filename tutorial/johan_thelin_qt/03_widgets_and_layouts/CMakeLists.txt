cmake_minimum_required(VERSION 3.2)

project(widgets_and_layouts CXX)

# http://doc.qt.io/qt-5/cmake-manual.html
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
# https://cmake.org/cmake/help/v3.6/manual/cmake-qt.7.html#autouic
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)


add_executable(01_project 01_size_policies_designer.cpp
                          01_designerdlg.cpp
                          01_designerdlg.h
                          01_designerdlg.ui)
target_link_libraries(01_project Qt5::Widgets)

add_executable(02_project 02_size_policies_coding.cpp)
target_link_libraries(02_project  Qt5::Widgets)

add_executable(03_project  03_buttons_with_stretch_factors.cpp)
target_link_libraries(03_project  Qt5::Widgets)

add_executable(04_project  04_horizontal_box_layout.cpp)
target_link_libraries(04_project  Qt5::Widgets)

add_executable(05_project  05_vertical_box_layout.cpp)
target_link_libraries(05_project  Qt5::Widgets)

add_executable(06_project  06_grid_layout.cpp)
target_link_libraries(06_project  Qt5::Widgets)

add_executable(07_project  07_QPushButton.cpp 07_QPushButton.h)
target_link_libraries(07_project  Qt5::Widgets)

add_executable(08_project  08_QLabel.cpp)
target_link_libraries(08_project  Qt5::Widgets)

add_executable(09_project  09_QLineEdit.cpp
                           09_Form.cpp
                           09_Form.h
                           09_Form.ui)
target_link_libraries(09_project  Qt5::Widgets)

add_executable(10_project  10_QCheckBox.cpp 10_QCheckBox.h)
target_link_libraries(10_project  Qt5::Widgets)

add_executable(11_project  11_QRadioButton.cpp)
target_link_libraries(11_project  Qt5::Widgets)

add_executable(12_project  12_QGroupBox.cpp)
target_link_libraries(12_project  Qt5::Widgets)

add_executable(13_project  13_QListWidget.cpp 13_QListWidget.h)
target_link_libraries(13_project  Qt5::Widgets)

add_executable(14_project  14_QComboBox.cpp)
target_link_libraries(14_project  Qt5::Widgets)

add_executable(15_project  15_QSpinBox.cpp)
target_link_libraries(15_project  Qt5::Widgets)

add_executable(16_project  16_QTimeEdit.cpp)
target_link_libraries(16_project  Qt5::Widgets)

add_executable(17_project  17_QDateEdit.cpp)
target_link_libraries(17_project  Qt5::Widgets)

add_executable(18_project  18_QDateTimeEdit.cpp)
target_link_libraries(18_project  Qt5::Widgets)

add_executable(19_project  19_QCalendarWidget.cpp)
target_link_libraries(19_project  Qt5::Widgets)

add_executable(20_project  20_QSlider.cpp)
target_link_libraries(20_project  Qt5::Widgets)

add_executable(21_project  21_QProgressBar.cpp
                           21_Form.cpp
                           21_Form.h
                           21_Form.ui)
target_link_libraries(21_project  Qt5::Widgets)

add_executable(22_project  22_QFileDialog_open.cpp 22_QFileDialog_open.h)
target_link_libraries(22_project  Qt5::Widgets)

add_executable(23_project  23_QFileDialog_save.cpp 23_QFileDialog_save.h)
target_link_libraries(23_project  Qt5::Widgets)

add_executable(24_project  24_QFileDialog_opendir.cpp 24_QFileDialog_opendir.h)
target_link_libraries(24_project  Qt5::Widgets)

add_executable(25_project  25_QMessageBox.cpp)
target_link_libraries(25_project  Qt5::Widgets)

add_executable(26_project  26_QInputDialog.cpp)
target_link_libraries(26_project  Qt5::Widgets)

add_executable(27_project  27_QColorDialog.cpp)
target_link_libraries(27_project  Qt5::Widgets)

add_executable(28_project  28_QFontDialog.cpp)
target_link_libraries(28_project  Qt5::Widgets)

add_executable(29_project  29_QValidator.cpp)
target_link_libraries(29_project  Qt5::Widgets)

add_executable(30_project  30_QRegExp.cpp)
target_link_libraries(30_project  Qt5::Widgets)

add_executable(31_project  31_QRegExpValidator.cpp)
target_link_libraries(31_project  Qt5::Widgets)