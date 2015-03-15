target = dinermerger

all: $(target)

debug = -g -O0
gccflags = -Wall -std=c++98 -pedantic
includes = -I./
sources = DinerMerger.cpp
libs = -lm -L./

$(target): $(sources)
	g++ $(debug) $(includes) $(gccflags) $(sources) -o $(target)

clean:
	rm -v *.o $(target)

.PHONY: all clean
