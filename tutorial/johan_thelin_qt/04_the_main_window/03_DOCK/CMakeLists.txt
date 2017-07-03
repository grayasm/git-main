add_executable(dockwindow main.cpp
                          SdiWindow.cpp
                          SdiWindow.h
                          InfoWidget.cpp
                          InfoWidget.h
                          images.qrc)
target_link_libraries(dockwindow Qt5::Widgets)
