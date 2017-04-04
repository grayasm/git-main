# CMakeLists.txt file for misctest application.

file(GLOB misctest_SRC "src/*.hpp" "src/*.cpp")
add_executable(misctest ${misctest_SRC})

# --- compiling ---
if (UNIX)
target_compile_options(misctest PRIVATE -Wall -Wno-long-long -pedantic)
target_compile_definitions(misctest PRIVATE DEBUG _GLIBCXX_DEBUG)
endif(UNIX)

# --- linking ---
target_link_libraries(misctest misc)

if (UNIX)
target_link_libraries(misctest pthread dl m)
endif (UNIX)
