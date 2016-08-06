#
# in the top directory execute
# mkdir common
# cp ../04.06/lib1/file1.hpp ./common/
# cp ../04.06/lib2/file2.hpp ./common/
# cp lib1/liblib1.a          ./common/
# cp lib2/liblib2.a          ./common/


add_library (lib1 STATIC IMPORTED)
add_library (lib2 STATIC IMPORTED)
set_property (TARGET lib1 PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/../common/liblib1.a")
set_property (TARGET lib2 PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/../common")

add_executable (app file3.cpp)
target_include_directories (app PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/../common")
target_link_libraries (app lib1 lib2)
