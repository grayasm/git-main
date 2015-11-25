cmake_minimum_required (VERSION 2.8)

add_subdirectory (lib1) # static
add_subdirectory (lib2) # static, depends on lib1
                        # on pre-build app: copy all headers and libs to common
# add_subdirectory (app)  # depends on lib1, lib2 and headers
