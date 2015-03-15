
bin_PROGRAMS=misctest

misctest_SOURCES= misctest.cpp \
test_algorithm.cpp	\
test_autoptr.cpp	\
test_deque.cpp		\
test_filename.cpp	\
test_forward_list.cpp	\
test_functional.cpp		\
test_list.cpp			\
test_numeric.cpp		\
test_podstring.cpp		\
test_podvector.cpp		\
test_priority_queue.cpp	\
test_queue.cpp			\
test_stack.cpp			\
test_tree.cpp			\
test_utility.cpp		\
test_vector.cpp			


misctest_CXXFLAGS=-g -O0
misctest_CPPFLAGS=-I./ -I../../misc/src -I${HOME}/local/include
misctest_LDFLAGS=-L${HOME}/local/lib -L../../misc/src -lcppunit -lmisc -ldl




check-syntax:
	g++ -o nul -Wall -S $(CHK_SOURCES) $(CPPFLAGS) 

