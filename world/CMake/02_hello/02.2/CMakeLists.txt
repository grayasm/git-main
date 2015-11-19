# a more complex example then the first one.
cmake_minimum_required (VERSION 2.6)
project (HELLO)

set (HELLO_SRCS Hello.c File2.c File3.c)

if (WIN32)
	set (HELLO_SRCS ${HELLO_SRCS} WinSupport.c)
else ()
	set (HELLO_SRCS ${HELLO_SRCS} UnixSupport.c)
endif ()

add_executable (Hello ${HELLO_SRCS})

# look for the Tcl library
find_library (TCL_LIBRARY
	NAMES tcl tcl84 tcl83 tcl82 tcl80
	PATHS /usr/lib /usr/local/lib
	)
	
if (TCL_LIBRARY)
	target_link_libraries (Hello ${TCL_LIBRARY})
endif ()