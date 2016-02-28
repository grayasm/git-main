# CMake file

set (SRC resource1.png)
add_library (resource1 INTERFACE)
install (FILES resource1.png DESTINATION .)
