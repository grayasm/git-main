# CMakeLists.txt file for misc library.

file(GLOB misc_SRC "src/*.hpp" "src/*.cpp")

add_library(misc STATIC ${misc_SRC})

target_include_directories(misc PUBLIC "src")

if(MSVC)
	target_compile_definitions(misc PUBLIC _CRT_SECURE_NO_WARNINGS)
endif(MSVC)