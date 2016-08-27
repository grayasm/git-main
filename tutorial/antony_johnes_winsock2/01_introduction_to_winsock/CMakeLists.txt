cmake_minimum_required(VERSION 3.2)
project(introduction CXX)

add_executable(01_initialize_winsock 01_initialize_winsock.cpp)
target_link_libraries(01_initialize_winsock PRIVATE Ws2_32.lib)

add_executable(02_error_checking 02_error_checking.cpp)
target_link_libraries(02_error_checking PRIVATE Ws2_32.lib)

add_executable(03_address_aprotocol 03_address_aprotocol.cpp)
target_link_libraries(03_address_aprotocol PRIVATE Ws2_32.lib)