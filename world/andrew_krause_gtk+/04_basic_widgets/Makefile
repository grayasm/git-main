all: stockitems togglebuttons checkbuttons radiobuttons entries \
     spinbuttons scales colorbuttons filechooserbuttons

stockitems: stockitems.cpp
	g++ -g -o stockitems stockitems.cpp `pkg-config --cflags gtk+-2.0` \
                                        `pkg-config --libs gtk+-2.0`

togglebuttons: togglebuttons.cpp
	g++ -g -o togglebuttons togglebuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                              `pkg-config --libs gtk+-2.0`


checkbuttons: checkbuttons.cpp
	g++ -g -o checkbuttons checkbuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                            `pkg-config --libs gtk+-2.0`

radiobuttons: radiobuttons.cpp
	g++ -g -o radiobuttons radiobuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                            `pkg-config --libs gtk+-2.0`

entries: entries.cpp
	g++ -g -o entries entries.cpp `pkg-config --cflags gtk+-2.0` \
                                  `pkg-config --libs gtk+-2.0`

spinbuttons: spinbuttons.cpp
	g++ -g -o spinbuttons spinbuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                          `pkg-config --libs gtk+-2.0`

scales: scales.cpp
	g++ -g -o scales scales.cpp `pkg-config --cflags gtk+-2.0` \
                                `pkg-config --libs gtk+-2.0`

colorbuttons: colorbuttons.cpp
	g++ -g -o colorbuttons colorbuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                            `pkg-config --libs gtk+-2.0`

filechooserbuttons: filechooserbuttons.cpp
	g++ -g -o filechooserbuttons filechooserbuttons.cpp `pkg-config --cflags gtk+-2.0` \
                                                        `pkg-config --libs gtk+-2.0`

clean:
	rm -v *.o *~ stockitems togglebuttons checkbuttons radiobuttons entries \
          spinbuttons scales colorbuttons filechooserbuttons
