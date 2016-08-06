
set (SRC Hello.c)

add_executable (Hello ${SRC})
target_link_libraries (Hello lib1)