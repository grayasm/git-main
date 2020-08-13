# Sample NSIS plug-in DLL
# extDll.dll must match NSIS compiler (makensis.exe) platform - Win32 or x64.

cmake_minimum_required(VERSION 3.12)

project (extDll)
set (SRC extDll.cpp nsis_api.h)
add_library(extDll SHARED ${SRC})
target_include_directories(extDll PRIVATE .)

# 10_plugin.nsi looks for extDll.dll in the src dir.
add_custom_command(
    TARGET extDll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:extDll>/extDll.dll"
        ${PROJECT_SOURCE_DIR}
        )
