all: unicode

debug = -g -O0

gccflags = -Wall

includes = -I. -I../../misc/src/

sources = e42bit.cpp utf8.cpp
objects = e42bit.o utf8.o

unicode: $(sources)
	g++ $(includes) -c $(sources)
	ar rcs libunicode.a $(objects)

	g++ $(includes) -c -fPIC $(sources)
	g++ -shared -Wl,-soname,libunicode.so.1 -o libunicode.so.1.0.1 $(objects)

clean:
	rm -v *.o libunicode.a libunicode.so.1.0.1
