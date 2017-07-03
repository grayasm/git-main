add_executable(sdiwindow main.cpp
                         SdiWindow.cpp
                         SdiWindow.h
                         images.qrc)
target_link_libraries(sdiwindow Qt5::Widgets)