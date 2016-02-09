all: slice_alloc1 slice_new1 memprofile timers

slice_alloc1: slice_alloc1.cpp
	g++ -g -o slice_alloc1 slice_alloc1.cpp `pkg-config --cflags gtk+-2.0` \
                                            `pkg-config --libs   gtk+-2.0`
slice_new1: slice_new1.cpp
	g++ -g -o slice_new1 slice_new1.cpp `pkg-config --cflags gtk+-2.0` \
                                        `pkg-config --libs   gtk+-2.0`

memprofile: memprofile.cpp
	g++ -g -o memprofile memprofile.cpp `pkg-config --cflags gtk+-2.0` \
                                        `pkg-config --libs   gtk+-2.0`

timers: timers.cpp
	g++ -g -o timers timers.cpp `pkg-config --cflags gtk+-2.0` \
                                `pkg-config --libs   gtk+-2.0`

clean:
	rm -v slice_alloc1 slice_new1 memprofile timers
