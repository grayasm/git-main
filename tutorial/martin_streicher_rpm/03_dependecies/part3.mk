all: part3

part3: part3.cpp part3.mk
	g++ -O3 `pkg-config --cflags --libs zlib` -o part3 part3.cpp

clean:
	rm -v part3

# make DESTDIR=/opt/part3 install
install: part3
	install -D -m 0755 part3    $(DESTDIR)/bin/part3

.PHONY: all clean install
