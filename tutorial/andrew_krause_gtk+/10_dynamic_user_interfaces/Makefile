all: browser window button boxes treeview

# -export-dynamic is required by GModule to connect the signals

browser: browser.cpp
	gcc -export-dynamic -Wall -g -o browser browser.cpp \
                           `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

window: window.cpp
	g++ -export-dynamic -Wall -g -o window window.cpp \
                           `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

button: button.cpp
	g++ -export-dynamic -Wall -g -o button button.cpp \
                           `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

boxes: boxes.cpp
	g++ -export-dynamic -Wall -g -o boxes boxes.cpp \
                           `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

treeview: treeview.cpp
	g++ -export-dynamic -Wall -g -o treeview treeview.cpp \
                           `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

clean:
	rm -fv browser window button boxes treeview
