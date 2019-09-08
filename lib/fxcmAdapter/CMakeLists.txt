# CMakeLists.txt file for fxcmAdapter library.

file(GLOB fxcmAdapter_SRC "src/*.hpp" "src/*.cpp")

add_library(fxcmAdapter STATIC ${fxcmAdapter_SRC})

target_include_directories(fxcmAdapter PUBLIC "src")

if(MSVC)
	target_include_directories( fxcmAdapter PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win64/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win64/include/forexconnect
		${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win64/samples/cpp/sample_tools/include)
endif(MSVC)

if(UNIX)
	target_include_directories( fxcmAdapter PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux-x86_64/include
		${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux-x86_64/include/forexconnect
		${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux-x86_64/samples/cpp/sample_tools/include)
endif(UNIX)

target_link_libraries(fxcmAdapter PUBLIC stl sys misc fxcore)
