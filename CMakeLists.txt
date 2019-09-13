# CMakeLists.txt file for root directory.
cmake_minimum_required(VERSION 3.2)
project(git-main)

# Add -DDEBUG because cmake only adds -D_DEBUG on windows and -g on linux.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

if(UNIX)
# Fix gcc-4.8.5 strange error on enum.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif(UNIX)

# Add omp support
find_package(OpenMP REQUIRED)
if(WIN32)
	add_compile_options(${OpenMP_CXX_FLAGS})
elseif(UNIX)
	# fix: ld cannot resolve omp_get_thread_num() and similar
	set (CMAKE_C_FLAGS    "${CMAKE_C_FLAGS}    ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${OpenMP_CXX_FLAGS}")
endif(WIN32)


add_subdirectory(world/CppUnit/cppunit/src/cppunit)
add_subdirectory(lib/stl)
add_subdirectory(lib/sys)
#add_subdirectory(lib/stltest)
add_subdirectory(lib/misc)
#add_subdirectory(lib/misctest)
add_subdirectory(lib/fxcore)
add_subdirectory(lib/fxcmAdapter)
add_subdirectory(app/fxmon)
add_subdirectory(app/debugtest)