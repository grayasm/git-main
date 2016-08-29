cmake_minimum_required(VERSION 3.2)
project(introduction CXX)

add_executable(01_initialize_winsock 01_initialize_winsock.cpp)
target_link_libraries(01_initialize_winsock PRIVATE Ws2_32.lib)

add_executable(02_error_checking 02_error_checking.cpp)
target_link_libraries(02_error_checking PRIVATE Ws2_32.lib)

add_executable(03_protocol_server 03_protocol_server.cpp)
target_link_libraries(03_protocol_server PRIVATE Ws2_32.lib)

add_executable(03_protocol_client 03_protocol_client.cpp)
target_link_libraries(03_protocol_client PRIVATE Ws2_32.lib)

add_executable(04_create_a_socket 04_create_a_socket.cpp)
target_link_libraries(04_create_a_socket PRIVATE Ws2_32.lib)

add_executable(05_client_send 05_client_send.cpp)
target_link_libraries(05_client_send PRIVATE Ws2_32.lib)

add_executable(05_server_recv 05_server_recv.cpp)
target_link_libraries(05_server_recv PRIVATE Ws2_32.lib)

add_executable(06_client_send_chunks 06_client_send_chunks.cpp)
target_link_libraries(06_client_send_chunks PRIVATE Ws2_32.lib)

add_executable(06_server_recv_chunks 06_server_recv_chunks.cpp)
target_link_libraries(06_server_recv_chunks PRIVATE Ws2_32.lib)

add_executable(07_client_sendto_udp 07_client_sendto_udp.cpp)
target_link_libraries(07_client_sendto_udp PRIVATE Ws2_32.lib)

add_executable(07_server_recvfrom_udp 07_server_recvfrom_udp.cpp)
target_link_libraries(07_server_recvfrom_udp PRIVATE Ws2_32.lib)
