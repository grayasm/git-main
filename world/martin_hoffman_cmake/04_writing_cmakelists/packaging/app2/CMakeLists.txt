# app2 should be packed into app2.tar.gz or similar
project (app2)
add_executable (app2 app2.cpp)


set (CPACK_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackConfig_app2.cmake")
install (TARGETS app2 RUNTIME DESTINATION bin COMPONENT app2)
install (FILES app2.cpp  DESTINATION src COMPONENT app2)
