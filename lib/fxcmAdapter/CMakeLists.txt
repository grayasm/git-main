# CMakeLists.txt file for fxcmAdapter library.

file(GLOB fxcmAdapter_SRC "src/*.hpp" "src/*.cpp")
list(REMOVE_ITEM fxcmAdapter_SRC	"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmHistory.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmIniParams.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmMarketPlugin.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmOrderMonitor.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmPermission.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmPipCost.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmResponseListener.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmSession.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmSessionHelper.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmSessionListener.cpp"
									"${CMAKE_CURRENT_SOURCE_DIR}/src/fxcmTradingSettings.cpp")

add_library(fxcmAdapter STATIC ${fxcmAdapter_SRC})

target_include_directories(fxcmAdapter PUBLIC "src")

if(MSVC)
	target_include_directories( fxcmAdapter PUBLIC
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win64/include
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/win64/samples/cpp/sample_tools/include)
endif(MSVC)

if(UNIX)
	target_include_directories( fxcmAdapter PUBLIC
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux-x86_64/include
								${CMAKE_CURRENT_SOURCE_DIR}/../../world/ForexConnectAPI/linux-x86_64/samples/cpp/sample_tools/include)
endif(UNIX)

target_link_libraries(fxcmAdapter PUBLIC misc fxcore)
