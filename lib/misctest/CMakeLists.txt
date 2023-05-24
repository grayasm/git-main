# CMakeLists.txt file for misctest application.

file(GLOB misctest_SRC "src/*.hpp" "src/*.cpp")
add_executable(misctest ${misctest_SRC})

# --- compiling ---
target_include_directories(misctest PRIVATE "../../world/acutest/include")

if(MSVC)
	target_compile_options(misctest PRIVATE /bigobj)
endif(MSVC)

if (UNIX)
	target_compile_options(misctest PRIVATE -Wall -Wno-long-long -pedantic)
	target_compile_definitions(misctest PRIVATE DEBUG _GLIBCXX_DEBUG)
endif(UNIX)


# --- linking ---
target_link_libraries(misctest PRIVATE misc stl sys)

if (UNIX)
	target_link_libraries(misctest PRIVATE pthread dl m)
endif (UNIX)
