all: helloworld2

helloworld: helloworld.cpp
	g++ -Wall -g helloworld.cpp -o helloworld \
        `pkg-config --cflags gtk+-2.0` \
        `pkg-config --libs gtk+-2.0`

helloworld2: helloworld2.cpp
	g++ -Wall -g helloworld2.cpp -o helloworld2 \
        `pkg-config --cflags gtk+-2.0` \
        `pkg-config --libs gtk+-2.0`


clean:
	rm -v *.o helloworld helloworld2

