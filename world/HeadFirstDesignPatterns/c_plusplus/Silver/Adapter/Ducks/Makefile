all: ducks

debug = -g -O0
gccflags = -Wall -std=c++98 -pedantic-errors
includes = -I./
sources = Ducks.cpp
libs = -lm -L./

ducks: $(sources)
	g++ $(debug) $(includes) $(gccflags) $(sources) -o ducks

clean:
	rm -v *.o ducks

.PHONY: all clean
