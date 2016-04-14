all: drawingareas entrycompletion printing

drawingareas: drawingareas.cpp
	g++ -Wall -g drawingareas.cpp -o drawingareas \
                 `pkg-config --cflags --libs gtk+-2.0`

entrycompletion: entrycompletion.cpp
	g++ -Wall -g entrycompletion.cpp -o entrycompletion \
                 `pkg-config --cflags --libs gtk+-2.0`

printing: printing.cpp
	g++ -Wall -g printing.cpp -o printing \
                 `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -fv drawingareas entrycompletion printing
