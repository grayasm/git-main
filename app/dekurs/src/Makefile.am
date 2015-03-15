bin_PROGRAMS=dekurs

dekurs_SOURCES=main.cpp xerces_main.cpp lang.cpp
dekurs_CXXFLAGS=-I../../../lib/misc/src
dekurs_CPPFLAGS=-g -O0
dekurs_LDFLAGS=-L${HOME}/local/lib -L../../../lib/misc/src  -lm -lxerces-c -lmisc


check-syntax:
	g++ -o nul -Wall -S $(CHK_SOURCES)
