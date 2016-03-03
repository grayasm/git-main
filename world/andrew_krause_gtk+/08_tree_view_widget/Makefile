all: liststore treestore selections editable celldatafunctions


liststore: liststore.cpp
	g++ -g -o liststore liststore.cpp   `pkg-config --cflags --libs gtk+-2.0`

treestore: treestore.cpp
	g++ -g -o treestore treestore.cpp   `pkg-config --cflags --libs gtk+-2.0`

selections: selections.cpp
	g++ -g -o selections selections.cpp `pkg-config --cflags --libs gtk+-2.0`

editable: editable.cpp
	g++ -g -o editable editable.cpp     `pkg-config --cflags --libs gtk+-2.0`

celldatafunctions: celldatafunctions.cpp
	g++ -g -o celldatafunctions celldatafunctions.cpp \
                                        `pkg-config --cflags --libs gtk+-2.0`


clean:
	rm -v liststore treestore selections editable celldatafunctions
