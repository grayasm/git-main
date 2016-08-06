# Mastering CMake - cap 4.11 Installing Files
#
# Using CPack to create 2 packages from 1 build tree.

cmake_minimum_required (VERSION 3.4)
add_subdirectory (app1)
add_subdirectory (app2)


add_custom_target(
        package_app1
        COMMAND cmake -E remove_directory ${CMAKE_INSTALL_PREFIX}
        COMMAND cmake -DCOMPONENT="app1" -P cmake_install.cmake
        COMMAND cpack --config ${CMAKE_BINARY_DIR}/CPackConfig_app1.cmake)
add_custom_target(
        package_app2
        COMMAND cmake -E remove_directory ${CMAKE_INSTALL_PREFIX}
        COMMAND cmake -DCOMPONENT="app2" -P cmake_install.cmake
        COMMAND cpack --config ${CMAKE_BINARY_DIR}/CPackConfig_app2.cmake)

include (CPack)
