all: dialogs dialogs2 dialogs3

dialogs: dialogs.cpp
	g++ -o dialogs dialogs.cpp `pkg-config --cflags gtk+-2.0` \
                               `pkg-config --libs gtk+-2.0`

dialogs2: dialogs2.cpp
	g++ -o dialogs2 dialogs2.cpp `pkg-config --cflags gtk+-2.0` \
                                 `pkg-config --libs gtk+-2.0`

dialogs3: dialogs3.cpp
	g++ -o dialogs3 dialogs3.cpp `pkg-config --cflags gtk+-2.0` \
                                 `pkg-config --libs gtk+-2.0`

clean:
	rm -v dialogs dialogs2 dialogs3
