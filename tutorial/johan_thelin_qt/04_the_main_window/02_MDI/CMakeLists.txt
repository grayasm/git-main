add_executable(mdiwindow main.cpp
                         MdiWindow.cpp
                         MdiWindow.h
                         DocumentWindow.cpp
                         DocumentWindow.h
                         images.qrc)
target_link_libraries(mdiwindow Qt5::Widgets)
