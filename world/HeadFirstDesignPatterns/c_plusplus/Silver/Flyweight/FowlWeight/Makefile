target = fowlweight

all: $(target)

debug = -g -O0
gccflags = -Wall -std=c++98 -pedantic-errors
includes = -I./
sources = FowlWeight.cpp
libs = -lm -L./

$(target): $(sources)
	g++ $(debug) $(includes) $(gccflags) $(sources) -o $(target)

clean:
	rm -v *.o $(target)

.PHONY: all clean
