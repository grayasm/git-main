# CMakeLists.txt file for debugtest application.

file(GLOB debugtest_SRC "src/*.hpp" "src/*.cpp")

add_executable(debugtest ${debugtest_SRC})

target_include_directories(debugtest PRIVATE "src")

# Linking
target_link_libraries(debugtest PRIVATE stl sys misc)
