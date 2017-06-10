# CMakeLists.txt file for CppUnit library.

file(GLOB cppunit_SRC "*.cpp" "*.h")
add_library(cppunit STATIC ${cppunit_SRC})
include_directories(../../include)
