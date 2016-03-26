all: popupmenus accelerators statusbarhints menubars toolbars uimanager \
     iconfactory


popupmenus: popupmenus.cpp
	g++ -g -o popupmenus popupmenus.cpp `pkg-config --cflags --libs gtk+-2.0`

accelerators: accelerators.cpp
	g++ -g -o accelerators accelerators.cpp \
                                        `pkg-config --cflags --libs gtk+-2.0`

statusbarhints: statusbarhints.cpp
	g++ -g -o statusbarhints statusbarhints.cpp \
                                        `pkg-config --cflags --libs gtk+-2.0`

menubars: menubars.cpp
	g++ -g -o menubars menubars.cpp     `pkg-config --cflags --libs gtk+-2.0`

toolbars: toolbars.cpp
	g++ -g -o toolbars toolbars.cpp     `pkg-config --cflags --libs gtk+-2.0`

uimanager: uimanager.cpp
	g++ -g -o uimanager uimanager.cpp   `pkg-config --cflags --libs gtk+-2.0`

iconfactory: iconfactory.cpp
	g++ -g -o iconfactory iconfactory.cpp `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -v popupmenus accelerators statusbarhints menubars toolbars uimanager \
          iconfactory
