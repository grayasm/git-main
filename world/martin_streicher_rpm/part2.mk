all: part2

part2: part2.cpp part2.mk
	g++ -O3 -o part2 part2.cpp

clean:
	rm -v part2

# make DESTDIR=/opt/part2 install
install: part2
	install -D -m 0755 part2      $(DESTDIR)/bin/part2
	install -D -m 0644 part2.png  $(DESTDIR)/share/icons/part2.png

.PHONY: all clean install
