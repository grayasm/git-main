all: popupmenus


popupmenus: popupmenus.cpp
	g++ -g -o popupmenus popupmenus.cpp    `pkg-config --cflags --libs gtk+-2.0`



clean:
	rm -v popupmenus
