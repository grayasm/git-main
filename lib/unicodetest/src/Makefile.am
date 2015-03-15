
bin_PROGRAMS=unicodetest

unicodetest_SOURCES= unicodetest.cpp 

unicodetest_CXXFLAGS=-g -O0
unicodetest_CPPFLAGS=-I./ -I../../unicode/src -I${HOME}/local/include
unicodetest_LDFLAGS=-L${HOME}/local/lib -L../../unicode/src -lcppunit -lunicode -ldl

check-syntax:
	g++ -o nul -Wall -S $(CHK_SOURCES) $(CPPFLAGS) 

