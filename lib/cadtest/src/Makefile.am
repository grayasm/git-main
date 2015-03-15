
bin_PROGRAMS=cadtest

cadtest_SOURCES= cadtest.cpp 

cadtest_CXXFLAGS=-g -O0
cadtest_CPPFLAGS=-I./ -I../../cad/src -I${HOME}/local/include
cadtest_LDFLAGS=-L${HOME}/local/lib -L../../cad/src -lcppunit -lcad -ldl

check-syntax:
	g++ -o nul -Wall -S $(CHK_SOURCES) $(CPPFLAGS) 

