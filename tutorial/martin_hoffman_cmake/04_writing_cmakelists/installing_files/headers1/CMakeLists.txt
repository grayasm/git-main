# CMake file

set (SRC header1.hpp)
add_library (header1 INTERFACE)
install (FILES ${SRC} DESTINATION .)
