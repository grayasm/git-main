qt5_add_resources(UI_RESOURCES_RCC images.qrc)

add_executable(sdiwindow main.cpp
                         SdiWindow.cpp
                         SdiWindow.h
                         ${UI_RESOURCES_RCC})

target_link_libraries(sdiwindow Qt5::Widgets)