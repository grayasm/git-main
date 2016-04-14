all: drawingareas

drawingareas: drawingareas.cpp
	g++ -Wall -g drawingareas.cpp -o drawingareas \
                 `pkg-config --cflags --libs gtk+-2.0`


clean:
	rm -fv drawingareas
