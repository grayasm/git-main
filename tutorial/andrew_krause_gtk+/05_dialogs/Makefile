all: dialogs dialogs2 dialogs3 messagedialogs aboutdialogs savefile \
     createfolder multiplefiles colorselection fontselection assistant \
     assistant2

dialogs: dialogs.cpp
	g++ -o dialogs dialogs.cpp `pkg-config --cflags gtk+-2.0` \
                               `pkg-config --libs gtk+-2.0`

dialogs2: dialogs2.cpp
	g++ -o dialogs2 dialogs2.cpp `pkg-config --cflags gtk+-2.0` \
                                 `pkg-config --libs gtk+-2.0`

dialogs3: dialogs3.cpp
	g++ -o dialogs3 dialogs3.cpp `pkg-config --cflags gtk+-2.0` \
                                 `pkg-config --libs gtk+-2.0`

messagedialogs: messagedialogs.cpp
	g++ -o messagedialogs messagedialogs.cpp `pkg-config --cflags gtk+-2.0` \
                                             `pkg-config --libs gtk+-2.0`

aboutdialogs: aboutdialogs.cpp
	g++ -o aboutdialogs aboutdialogs.cpp `pkg-config --cflags gtk+-2.0` \
                                         `pkg-config --libs gtk+-2.0`

savefile: savefile.cpp
	g++ -o savefile savefile.cpp `pkg-config --cflags gtk+-2.0` \
                                 `pkg-config --libs gtk+-2.0`

createfolder: createfolder.cpp
	g++ -o createfolder createfolder.cpp `pkg-config --cflags gtk+-2.0` \
                                         `pkg-config --libs gtk+-2.0`

multiplefiles: multiplefiles.cpp
	g++ -o multiplefiles multiplefiles.cpp `pkg-config --cflags gtk+-2.0` \
                                           `pkg-config --libs gtk+-2.0`

colorselection: colorselection.cpp
	g++ -o colorselection colorselection.cpp `pkg-config --cflags gtk+-2.0` \
                                             `pkg-config --libs gtk+-2.0`

fontselection: fontselection.cpp
	g++ -o fontselection fontselection.cpp `pkg-config --cflags gtk+-2.0` \
                                           `pkg-config --libs gtk+-2.0`

assistant: assistant.cpp
	g++ -o assistant assistant.cpp `pkg-config --cflags gtk+-2.0` \
                                   `pkg-config --libs gtk+-2.0`

assistant2: assistant2.cpp
	g++ -o assistant2 assistant2.cpp `pkg-config --cflags gtk+-2.0` \
                                     `pkg-config --libs gtk+-2.0`


clean:
	rm -v dialogs dialogs2 dialogs3 messagedialogs aboutdialogs savefile \
          createfolder multiplefiles colorselection fontselection assistant \
          assistant2
