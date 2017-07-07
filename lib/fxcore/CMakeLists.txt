# CMakeLists.txt file for fxcore library.

file(GLOB fxcore_SRC "src/*.hpp" "src/*.cpp")

add_library(fxcore STATIC ${fxcore_SRC})

target_include_directories(fxcore PUBLIC "src")

target_link_libraries(fxcore PUBLIC misc)