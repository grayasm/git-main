#
#
cmake_minimum_required (VERSION 2.8)

message ("--------------------------------------------------------")

# 4.5 Checking versions of CMake
if (${CMAKE_VERSION} VERSION_GREATER 1.6.1)
  message ("CMake ${CMAKE_VERSION} > 1.6.1")
else ()
  message ("CMake ${CMAKE_VERSION} <= 1.6.1")
endif ()

# 4.6 Using Modules  /usr/share/cmake/Modules/FindTCL.cmake
include (FindTCL)
add_library (foo STATIC foo.c)

if (TCL_LIBRARY)
  target_link_libraries(foo ${TCL_LIBRARY})
elseif (TCL_LIBRARY-NOTFOUND)
  message ("foo will not link with TCL_LIBRARY, too bad")
endif ()


# 4.6 - ZLIB package  /usr/share/cmake/Modules/FindZLIB.cmake
include (FindZLIB)

if (ZLIB_FOUND)
  message ("ZLIB found")
else ()
  message ("ZLIB cannot be found")
endif ()


# 4.6 - QT4 package
# load settings for an external project
# variable <package>_FOUND will be set to
# indicate whether the package was found.

find_package (Qt4)
if (QT4_FOUND)
  message ("Qt4 found")
else ()
  message ("Qt4 package cannot be found")
endif ()



message ("--------------------------------------------------------")
