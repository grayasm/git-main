all: scrolledwindows textview textview2 textview3 textview4 iterators \
     cutcopypaste find texttags images childwidgets

scrolledwindows: scrolledwindows.cpp
	g++ -g -o scrolledwindows scrolledwindows.cpp \
                                      `pkg-config --cflags --libs gtk+-2.0`

textview: textview.cpp
	g++ -g -o textview textview.cpp   `pkg-config --cflags --libs gtk+-2.0`

textview2: textview2.cpp
	g++ -g -o textview2 textview2.cpp `pkg-config --cflags --libs gtk+-2.0`

textview3: textview3.cpp
	g++ -g -o textview3 textview3.cpp `pkg-config --cflags --libs gtk+-2.0`

textview4: textview4.cpp
	g++ -g -o textview4 textview4.cpp `pkg-config --cflags --libs gtk+-2.0`

iterators: iterators.cpp
	g++ -g -o iterators iterators.cpp `pkg-config --cflags --libs gtk+-2.0`

cutcopypaste: cutcopypaste.cpp
	g++ -g -o cutcopypaste cutcopypaste.cpp \
                                      `pkg-config --cflags --libs gtk+-2.0`

find: find.cpp
	g++ -g -o find find.cpp           `pkg-config --cflags --libs gtk+-2.0`

texttags: texttags.cpp
	g++ -g -o texttags texttags.cpp   `pkg-config --cflags --libs gtk+-2.0`

images: images.cpp
	g++ -g -o images images.cpp       `pkg-config --cflags --libs gtk+-2.0`

childwidgets: childwidgets.cpp
	g++ -g -o childwidgets childwidgets.cpp \
                                      `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -v scrolledwindows textview textview2 textview3 textview4 iterators \
          cutcopypaste find texttags images childwidgets
