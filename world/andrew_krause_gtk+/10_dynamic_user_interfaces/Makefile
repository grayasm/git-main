all: browser window button

browser: browser.cpp
	gcc -Wall -g -o browser browser.cpp `pkg-config --cflags --libs gtk+-2.0` \
                                       `pkg-config --cflags --libs libglade-2.0`

window: window.cpp
	g++ -Wall -g -o window window.cpp `pkg-config --cflags --libs gtk+-2.0` \
                                      `pkg-config --cflags --libs libglade-2.0`

button: button.cpp
	g++ -Wall -g -o button button.cpp `pkg-config --cflags --libs gtk+-2.0` \
                                      `pkg-config --cflags --libs libglade-2.0`

clean:
	rm -fv browser window button
