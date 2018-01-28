# CMakeLists.txt file for misc library.

file(GLOB misc_SRC "src/*.hpp" "src/*.cpp")

add_library(misc STATIC ${misc_SRC})

target_include_directories(misc PUBLIC "src")

if(MSVC)
	target_compile_definitions(misc PUBLIC _CRT_SECURE_NO_WARNINGS)
	# for unistd.cpp: drop resolution of Sleep(ms) to 1ms with timeBeginPeriod/timeEndPeriod
	target_link_libraries(misc winmm.lib)
endif(MSVC)