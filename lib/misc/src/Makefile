all: misc

#On Windows with codeblocks and mingw g++ compiler
#CC=mingw32-g++.exe
CC=g++
AR=ar
SRC = cpu_timer.cpp exception.cpp filename.cpp strconv.cpp unistd.cpp time.cpp	\
	thread.cpp sync_base.cpp mutex.cpp semaphore.cpp event.cpp
	
OBJ = cpu_timer.o exception.o filename.o strconv.o unistd.o time.o \
	thread.o sync_base.o mutex.o semaphore.o event.o
	
CXXFLAGS= -g -O0 -Wall -Wno-long-long -std=c++98 -pedantic -DDEBUG -D_GLIBCXX_DEBUG -m64
# -pedantic-errors

misc: $(SRC)
	$(CC)  -c $(CXXFLAGS) $(SRC)
	$(AR)  rcs libmisc.a $(OBJ)

	$(CC)  -c $(CXXFLAGS) -fPIC $(SRC)
	$(CC)  $(CXXFLAGS) -shared -Wl,-soname,libmisc.so.1 -o libmisc.so.1.0.1 $(OBJ)
	ln -sf libmisc.so.1.0.1  libmisc.so.1

clean:
	rm *.o libmisc.a libmisc.so*
