qt5_add_resources(UI_RESOURCE_RCC images.qrc)

add_executable(mdiwindow main.cpp
                         MdiWindow.cpp
                         MdiWindow.h
                         DocumentWindow.cpp
                         DocumentWindow.h
                         ${UI_RESOURCE_RCC})

target_link_libraries(mdiwindow Qt5::Widgets)
