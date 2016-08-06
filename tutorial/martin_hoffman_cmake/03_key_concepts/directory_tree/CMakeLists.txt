# First test for building an application with a STATIC dependency.
project (app)

add_library (lib1 STATIC lib1/File1.c)

add_executable (Hello app/Hello.c)
target_link_libraries (Hello lib1)
