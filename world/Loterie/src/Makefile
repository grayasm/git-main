all: loterie


debug = -g -O0

sources = main.cpp Aleator.cpp Combinatie.cpp Extrageri.cpp Filtru.cpp Rhino.cpp\
			Statistica.cpp Varianta.cpp

gccflags = -Wall

includes = -I. -I../../../lib/misc/src

libs = -lm -L. -L../../../lib/misc/src -static -lmisc

loterie: $(sources)
	g++ $(debug) $(gccflags) $(includes) $(sources) $(libs) -o loterie


clean:
	rm -v *.o loterie
