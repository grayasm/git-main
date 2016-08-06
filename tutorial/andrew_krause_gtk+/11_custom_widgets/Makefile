all: ipaddresstest

ipaddresstest: myipaddress.cpp ipaddresstest.cpp myipaddress.hpp
	g++ -Wall -g ipaddresstest.cpp myipaddress.cpp -o ipaddresstest \
                 `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -fv ipaddresstest
