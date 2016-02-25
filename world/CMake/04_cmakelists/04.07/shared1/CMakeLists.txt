# CMake file

set (SRC  shared1.hpp
          shared1.cpp )

add_library (shared1 SHARED ${SRC})
target_include_directories (shared1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../headers1)
