qt5_add_resources(UI_RESOURCE_RCC images.qrc)

add_executable(dockwindow main.cpp
                          SdiWindow.cpp
                          SdiWindow.h
                          InfoWidget.cpp
                          InfoWidget.h
                          ${UI_RESOURCE_RCC})

target_link_libraries(dockwindow Qt5::Widgets)
