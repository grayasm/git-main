all: part2

part2: part2-0.cpp part2-0.mk
	g++ -O3 -o part2 part2-0.cpp

clean:
	rm -v part2

# make DESTDIR=/opt/part2 install
install: part2
	install -D -m 0755 part2            $(DESTDIR)/bin/part2
	install -D -m 0644 part2-0.config   $(DESTDIR)/etc/config2.0

.PHONY: all clean install
