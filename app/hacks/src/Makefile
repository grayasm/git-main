
#CC=mingw32-g++.exe - MinGW compiler.
CC=g++
SRC= main.cpp \
	../../../lib/misc/src/thread.cpp
OBJ=$(SRC:.cpp=.o)
INCLUDE= -I./ -I../../../lib/misc/src -I$(HOME)/local/cppunit/include
CXXFLAGS= -c -std=c++98 -g -O0 -Wall -Wno-long-long -pedantic -D_GLIBCXX_DEBUG -m64
LDFLAGS= -L../../../lib/misc/src -lmisc -lpthread
TARGET=hacks



all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC)  $(OBJ) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(INCLUDE) $(CXXFLAGS) $< -o $@

clean:
	rm -vf hacks *.o

