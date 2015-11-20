# About variables scope.

cmake_minimum_required (VERSION 2.8)

set (FOO 1)
add_subdirectory (dir1)
include (file1.cmake)

set (BAR 2)
add_subdirectory (dir2)
include (file2.cmake)

message ("At the end FOO: " ${FOO})
message ("At the end BAR: " ${BAR})
