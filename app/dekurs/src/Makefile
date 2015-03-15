all: dekurs

includes = -I. -I../../../lib/misc/src

sources = main.cpp lang.cpp

staticlib = -L../../../lib/misc/src -lmisc

dekurs: $(sources)
	g++ -g -O0 $(includes) $(sources) $(staticlib) -o dekurs

clean:
	rm -v *.o dekurs
