# CMakeLists.txt file for fxmon application.

file(GLOB fxmon_SRC "src/*.hpp" "src/*.cpp")

add_executable(fxmon ${fxmon_SRC})

target_include_directories(fxmon PRIVATE "src")

# Import FXCM libraries; It didnt' work from fxcmAdapter; Maybe it is worth another try.
add_library(ForexConnect SHARED IMPORTED)
add_library(sample_tools SHARED IMPORTED)

if(MSVC)
set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win32/bin/ForexConnect.dll")
set_property(TARGET ForexConnect PROPERTY IMPORTED_IMPLIB   "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win32/lib/ForexConnect.lib")
set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win32/samples/cpp/sample_tools/bin/sample_tools.dll")
set_property(TARGET sample_tools PROPERTY IMPORTED_IMPLIB   "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win32/samples/cpp/sample_tools/lib/sample_tools.lib")
endif(MSVC)

if(UNIX)
set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux/lib/libForexConnect.so")
set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux/samples/cpp/sample_tools/lib/libsample_tools.so")
endif(UNIX)

 
target_link_libraries(fxmon PRIVATE fxcmAdapter ForexConnect sample_tools)