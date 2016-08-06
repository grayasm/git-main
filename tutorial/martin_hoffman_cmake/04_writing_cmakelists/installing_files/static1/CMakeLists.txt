# CMake file

set (SRC static1.hpp
         static1.cpp )

add_library (static1 STATIC ${SRC})
target_include_directories (static1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../headers1)
