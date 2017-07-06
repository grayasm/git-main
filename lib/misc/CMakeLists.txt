# CMakeLists.txt file for misc library.
project(misc)
file(GLOB misc_SRC "src/*.hpp" "src/*.cpp")
add_library(misc STATIC ${misc_SRC})
target_include_directories(misc PUBLIC "src")