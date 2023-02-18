# CMakeLists.txt file for test application
# Playground for testing, compiling, linking, debugging anything.

file(GLOB test_SRC "src/*.hpp" "src/*.cpp")

add_executable(test ${test_SRC})

target_include_directories(test PRIVATE "src")
