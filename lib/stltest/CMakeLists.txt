# CMakeLists.txt file for stltest application.

file(GLOB stltest_SRC "src/*.hpp" "src/*.cpp")
add_executable(stltest ${stltest_SRC})

# --- compiling ---
if(MSVC)
	target_compile_options(stltest PRIVATE /bigobj)
endif(MSVC)

if (UNIX)
	target_compile_options(stltest PRIVATE -Wall -Wno-long-long -pedantic)
	target_compile_definitions(stltest PRIVATE DEBUG _GLIBCXX_DEBUG)
endif(UNIX)


# --- linking ---
target_link_libraries(stltest PRIVATE stl sys cppunit)

if (UNIX)
	target_link_libraries(stltest PRIVATE pthread dl m)
endif (UNIX)
