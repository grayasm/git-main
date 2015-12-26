all: helloworld

helloworld: helloworld.cpp
	g++ -Wall -g helloworld.cpp -o helloworld \
        `pkg-config --cflags gtk+-2.0` \
        `pkg-config --libs gtk+-2.0`

clean:
	rm -v *.o helloworld

