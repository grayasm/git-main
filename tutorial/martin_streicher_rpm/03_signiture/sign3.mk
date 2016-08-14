all: sign3

sign3: sign3.cpp sign3.mk
	g++ -O3 -fopenmp -o sign3 sign3.cpp

clean:
	rm -v sign3

# make DESTDIR=/opt/sign3 install
install: sign3
	install -D -m 0755 sign3    $(DESTDIR)/bin/sign3

.PHONY: all clean install
