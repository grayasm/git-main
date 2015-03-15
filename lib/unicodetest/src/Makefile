all: unicodetest

includes = -I. -I../../unicode/src -I$(HOME)/local/include

sources = 

staticlib = -L/lib -lm -L$(HOME)/local/lib -lcppunit -L../../unicode/src -static -lunicode 
sharedlib = -L$(HOME)/local/lib -lunicode -lcppunit -L/lib -lm -ldl

unicodetest: $(sources)
	g++ -g -O0 $(includes) $(sources) $(staticlib) -o unicodetest_static
#	g++ -g -O0 $(includes) $(sources) $(sharedlib) -o unicodetest_dyn

clean:
	rm -v *.o unicodetest_static  unicodetest_dyn