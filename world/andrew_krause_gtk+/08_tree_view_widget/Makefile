all: liststore treestore selections


liststore: liststore.cpp
	g++ -g -o liststore liststore.cpp `pkg-config --cflags --libs gtk+-2.0`

treestore: treestore.cpp
	g++ -g -o treestore treestore.cpp `pkg-config --cflags --libs gtk+-2.0`

selections: selections.cpp
	g++ -g -o selections selections.cpp `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -v liststore treestore selections
