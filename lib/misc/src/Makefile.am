

lib_LTLIBRARIES=libmisc.la
libmisc_la_CXXFLAGS=-g -O0 -I./
libmisc_la_SOURCES = filename.cpp strconv.cpp exception.cpp


check-syntax:
	g++ -o nul -Wall -S $(CHK_SOURCES)
