all: slice_alloc1 slice_new1 memprofile timers files directories \
     timeouts files2 iochannels modules-plugin modules

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

files: files.cpp
	g++ -g -o files files.cpp `pkg-config --cflags gtk+-2.0` \
                              `pkg-config --libs   gtk+-2.0`

directories: directories.cpp
	g++ -g -o directories directories.cpp `pkg-config --cflags gtk+-2.0` \
                                          `pkg-config --libs   gtk+-2.0`

timeouts: timeouts.cpp
	g++ -g -o timeouts timeouts.cpp `pkg-config --cflags gtk+-2.0` \
                                    `pkg-config --libs   gtk+-2.0`

files2: files2.cpp
	g++ -g -o files2 files2.cpp `pkg-config --cflags gtk+-2.0` \
                                `pkg-config --libs   gtk+-2.0`

iochannels: iochannels.cpp
	g++ -g -o iochannels iochannels.cpp `pkg-config --cflags gtk+-2.0` \
                                        `pkg-config --libs   gtk+-2.0`


modules-plugin: modules-plugin.cpp
	g++ -g -shared -fPIC -o modules-plugin.so modules-plugin.cpp \
                                             `pkg-config --cflags gtk+-2.0` \
                                             `pkg-config --libs   gtk+-2.0`

modules: modules-plugin modules.cpp
	g++ -g -o modules modules.cpp \
             `pkg-config --cflags --libs   gtk+-2.0` \
             `pkg-config --cflags --libs   gmodule-2.0`


clean:
	rm -v slice_alloc1 slice_new1 memprofile timers files directories \
          timeouts files2 iochannels modules-plugin.so modules
