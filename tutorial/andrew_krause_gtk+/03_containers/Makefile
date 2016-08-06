all: boxes boxes2 panes tables fixed expanders \
     handleboxes notebooks eventboxes

boxes: boxes.cpp
	g++ -g -o boxes boxes.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

boxes2: boxes2.cpp
	g++ -g -o boxes2 boxes2.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

panes: panes.cpp
	g++ -g -o panes panes.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

tables: tables.cpp
	g++ -g -o tables tables.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

fixed: fixed.cpp
	g++ -g -o fixed fixed.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

expanders: expanders.cpp
	g++ -g -o expanders expanders.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

handleboxes: handleboxes.cpp
	g++ -g -o handleboxes handleboxes.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

notebooks: notebooks.cpp
	g++ -g -o notebooks notebooks.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

eventboxes: eventboxes.cpp
	g++ -g -o eventboxes eventboxes.cpp `pkg-config --cflags gtk+-2.0` \
              `pkg-config --libs gtk+-2.0`

clean:
	rm -v boxes boxes2 panes tables fixed expanders \
    handleboxes notebooks eventboxes *.o
