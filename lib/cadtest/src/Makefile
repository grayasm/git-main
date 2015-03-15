all: cadtest

includes = -I. -I../../cad/src -I$(HOME)/local/include

sources = 

staticlib = -L/lib -lm -L$(HOME)/local/lib -lcppunit -L../../cad/src -static -lcad 
sharedlib = -L$(HOME)/local/lib -lcad -lcppunit -L/lib -lm -ldl

cadtest: $(sources)
	g++ -g -O0 $(includes) $(sources) $(staticlib) -o cadtest_static
#	g++ -g -O0 $(includes) $(sources) $(sharedlib) -o cadtest_dyn

clean:
	rm -v *.o cadtest_static  cadtest_dyn