# CMakeLists.txt file for CppUnit library.

file(GLOB cppunit_SRC "*.cpp" "*.h")

if(UNIX)
list(REMOVE_ITEM cppunit_SRC ${CMAKE_CURRENT_SOURCE_DIR}/DllMain.cpp)
endif(UNIX)

if(MSVC)
list(REMOVE_ITEM cppunit_SRC ${CMAKE_CURRENT_SOURCE_DIR}/DllMain.cpp)
endif(MSVC)


add_library(cppunit STATIC ${cppunit_SRC})
target_include_directories(cppunit PUBLIC "../../include")
