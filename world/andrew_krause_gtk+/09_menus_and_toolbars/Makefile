all: popupmenus accelerators statusbarhints


popupmenus: popupmenus.cpp
	g++ -g -o popupmenus popupmenus.cpp     `pkg-config --cflags --libs gtk+-2.0`

accelerators: accelerators.cpp
	g++ -g -o accelerators accelerators.cpp `pkg-config --cflags --libs gtk+-2.0`

statusbarhints: statusbarhints.cpp
	g++ -g -o statusbarhints statusbarhints.cpp `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -v popupmenus accelerators statusbarhints
