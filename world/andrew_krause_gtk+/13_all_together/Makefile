all: gtk2-styles

gtk2-styles: gtk2-styles.cpp gtk2-styles.glade
	g++ -Wall -g -o gtk2-styles gtk2-styles.cpp \
                    `pkg-config --cflags --libs gtk+-2.0 libglade-2.0`

clean:
	rm -fv gtk2-styles
