# CMakeLists.txt file for stl library.

file(GLOB stl_SRC "src/*.hpp" "src/*.cpp")

add_library(stl STATIC ${stl_SRC})

target_include_directories(stl PUBLIC "src")

set_target_properties(stl PROPERTIES LINKER_LANGUAGE CXX)

if(MSVC)
	target_compile_definitions(stl PUBLIC _CRT_SECURE_NO_WARNINGS)
endif(MSVC)