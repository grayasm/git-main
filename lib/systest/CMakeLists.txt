# CMakeLists.txt file for systest application.

file(GLOB systest_SRC "src/*.hpp" "src/*.cpp")
add_executable(systest ${systest_SRC})

# --- compiling ---
if(MSVC)
	target_compile_options(systest PRIVATE /bigobj)
endif(MSVC)

if (UNIX)
	target_compile_options(systest PRIVATE -Wall -Wno-long-long -pedantic)
	target_compile_definitions(systest PRIVATE DEBUG _GLIBCXX_DEBUG)
endif(UNIX)


# --- linking ---
target_link_libraries(systest PRIVATE stl sys cppunit)

if (UNIX)
	target_link_libraries(systest PRIVATE pthread dl m)
endif (UNIX)
