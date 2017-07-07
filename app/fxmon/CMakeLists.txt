# CMakeLists.txt file for fxmon application.

file(GLOB fxmon_SRC "src/*.hpp" "src/*.cpp")

add_executable(fxmon ${fxmon_SRC})

target_include_directories(fxcmAdapter PUBLIC "src")

if(MSVC)
	target_include_directories( fxcmAdapter PUBLIC
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win32/include
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win32/samples/cpp/sample_tools/include)
endif(MSVC)

if(UNIX)
	target_include_directories( fxcmAdapter PUBLIC
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux/include
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux/samples/cpp/sample_tools/include)
endif(UNIX)

target_link_libraries(fxcmAdapter PUBLIC misc fxcore)

#
# Import FXCM shared objects. This is the broker adapter so it's good to isolate the import here.
#
add_library(ForexConnect SHARED IMPORTED)
add_library(sample_tools SHARED IMPORTED)

if(MSVC)
	set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win32/lib/ForexConnect.lib)
	set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win32/samples/cpp/sample_tools/lib/sample_tools.lib)
endif(MSVC)

if(UNIX)
	set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux/lib/libForexConnect.so)
	set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux/samples/cpp/sample_tools/lib/libsample_tools.so)
endif(UNIX)

target_link_libraries(fxcmAdapter PUBLIC ForexConnect sample_tools)


