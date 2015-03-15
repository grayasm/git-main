

CC=g++
SRC=misctest.cpp \
    test_algorithm.cpp \
    test_autoptr.cpp \
    test_critical_section.cpp \
    test_deque.cpp \
    test_event.cpp \
    test_exception.cpp \
    test_filename.cpp \
    test_functional.cpp \
    test_generic_array.cpp \
    test_generic_string.cpp \
    test_list.cpp \
    test_multi_lock.cpp \
    test_mutex.cpp \
    test_numeric.cpp \
    test_priority_queue.cpp \
    test_queue.cpp \
    test_semaphore.cpp \
    test_single_lock.cpp \
    test_stack.cpp \
    test_thread.cpp \
    test_tree.cpp \
    test_utility.cpp \
    test_vector.cpp

OBJ=$(SRC:.cpp=.o)
INCLUDE= -I. -I../../misc/src -I$(HOME)/local/cppunit/include
# -g -O0 ... -DDEBUG -D_GLIBCXX_DEBUG
CXXFLAGS= -c -std=c++98 -O2 -Wall -Wno-long-long -pedantic -m64
LDFLAGS= -L$(HOME)/local/cppunit/lib -l:libcppunit.a -L../../misc/src -l:libmisc.a -lm -ldl
TARGET=misctest

all: $(SRC) $(TARGET)

.cpp.o:
	$(CC) $(INCLUDE) $(CXXFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -v *.o misctest

# test individual cpp file
compile_file: test_algorithm.cpp
	g++ -c test_algorithm.cpp $(INCLUDE) $(CXXFLAGS) 
