# CMake file for app1.
# What is specific here:
# a) must include header1.hpp from INTERFACE target (easy)
# b) app1 links with static1 and shared1
# c) NEW: installation commands
#         I saw that app1 executable is linked against full path libshared.so
#         in its build directory (e.g. 04.07.b/shared1/libshared1.so)
#         app1 can run from build location or when installed it will load
#         libshared.so from the system or LD_LIBRARY_PATH.

set (SRC app1.cpp)
add_executable (app1 ${SRC})
target_include_directories (app1 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../headers1
    ${CMAKE_CURRENT_SOURCE_DIR}/../static1
    ${CMAKE_CURRENT_SOURCE_DIR}/../shared1)
target_link_libraries (app1 PRIVATE static1 shared1)

set(target app1)
include(${CMA KE_SOURCE_DIR}/packageDefinition/myPackage.cmake)

#install (TARGETS app1 RUNTIME DESTINATION .)
