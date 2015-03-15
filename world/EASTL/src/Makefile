all: eastl

debug = -g -O0

gccflags = -Wall

includes = -I. -I../include

sources = main.cpp

libs = -L/usr/lib -lm


eastl: $(sources)
	g++ $(debug) $(gccflags) $(includes) $(sources) $(libs) -o eastl

clean:
	rm -v *.o eastl
