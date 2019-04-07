# CMakeLists.txt file for sys library.

file(GLOB sys_SRC "src/*.hpp" "src/*.cpp")

add_library(sys STATIC ${sys_SRC})

target_include_directories(sys PUBLIC "src")

target_link_libraries(sys stl)

if(MSVC)
	target_compile_definitions(sys PUBLIC _CRT_SECURE_NO_WARNINGS)
	# for unistd.cpp: drop resolution of Sleep(ms) to 1ms with timeBeginPeriod/timeEndPeriod
	target_link_libraries(sys winmm.lib)
endif(MSVC)