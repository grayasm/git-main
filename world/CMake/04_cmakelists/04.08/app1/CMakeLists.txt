# app1 should be packed into app1.tar.gz or similar

add_executable (app1 app1.cpp)

set (CPACK_OUTPUT_CONFIG_FILE "${PROJECT_BINARY_DIR}/CPackConfig_app1.cmake")
install (TARGETS app1 RUNTIME DESTINATION "bin" COMPONENT "app1")
install (FILES app1.cpp  DESTINATION "src" COMPONENT "app1")
