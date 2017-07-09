# CMakeLists.txt file for fxmon application.

file(GLOB fxmon_SRC "src/*.hpp" "src/*.cpp")

add_executable(fxmon ${fxmon_SRC})

target_include_directories(fxmon PRIVATE "src")


# Import FXCM libraries
add_library(ForexConnect SHARED IMPORTED)
add_library(sample_tools SHARED IMPORTED)

if(MSVC)
set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/bin/ForexConnect.dll")
set_property(TARGET ForexConnect PROPERTY IMPORTED_IMPLIB   "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/lib/ForexConnect.lib")
set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/samples/cpp/sample_tools/bin/sample_tools.dll")
set_property(TARGET sample_tools PROPERTY IMPORTED_IMPLIB   "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/samples/cpp/sample_tools/lib/sample_tools.lib")
endif(MSVC)

if(UNIX)
set_property(TARGET ForexConnect PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux-x86_64/lib/libForexConnect.so")
set_property(TARGET sample_tools PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux-x86_64/samples/cpp/sample_tools/lib/libsample_tools.so")
endif(UNIX)


# Linking
target_link_libraries(fxmon PRIVATE fxcmAdapter ForexConnect sample_tools)

if(UNIX)
target_link_libraries(fxmon PRIVATE pthread dl m)
endif(UNIX)



# Postbuild copy
if(MSVC)
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
					"${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/bin"
					"${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
					"${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/win64/samples/cpp/sample_tools/bin"
					"${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
					"${CMAKE_CURRENT_SOURCE_DIR}/monitor.ini"
					"${CMAKE_CURRENT_BINARY_DIR}")
endif(MSVC)

if(UNIX)
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
					"${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux-x86_64/lib"
					"${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
					"${CMAKE_SOURCE_DIR}/world/ForexConnectAPI/linux-x86_64/samples/cpp/sample_tools/lib"
					"${CMAKE_CURRENT_BINARY_DIR}")
add_custom_command( TARGET fxmon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
					"${CMAKE_CURRENT_SOURCE_DIR}/monitor.ini"
					"${CMAKE_CURRENT_BINARY_DIR}")
endif(UNIX)
