#
#
cmake_minimum_required (VERSION 2.6)

# so we should use our own math functions?
option (USE_MYMATH "Use tutorial provided math implementation" ON)

project (Tutorial)
add_subdirectory (mathfunc)
add_subdirectory (tutorial)


# to install use:
# cd build && mkdir ../install
# make && make install DESTDIR=../install
