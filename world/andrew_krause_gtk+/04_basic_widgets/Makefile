all: stockitems togglebuttons checkbuttons

stockitems: stockitems.cpp
	g++ -g -o stockitems stockitems.cpp `pkg-config --cflags gtk+-2.0` \
                                        `pkg-config --libs gtk+-2.0`

togglebuttons: togglebuttons.cpp
	g++ -g -o togglebuttons togglebuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                              `pkg-config --libs gtk+-2.0`


checkbuttons: checkbuttons.cpp
	g++ -g -o checkbuttons checkbuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                            `pkg-config --libs gtk+-2.0`

clean:
	rm -v *.o *~ stockitems togglebuttons checkbuttons
