all: scrolledwindows textview textview2 textview3

scrolledwindows: scrolledwindows.cpp
	g++ -g -o scrolledwindows scrolledwindows.cpp \
                                      `pkg-config --cflags --libs gtk+-2.0`

textview: textview.cpp
	g++ -g -o textview textview.cpp   `pkg-config --cflags --libs gtk+-2.0`

textview2: textview2.cpp
	g++ -g -o textview2 textview2.cpp `pkg-config --cflags --libs gtk+-2.0`

textview3: textview3.cpp
	g++ -g -o textview3 textview3.cpp `pkg-config --cflags --libs gtk+-2.0`


clean:
	rm -v scrolledwindows textview textview2 textview3
