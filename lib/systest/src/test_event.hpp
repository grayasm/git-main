/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_event_hpp__
#define __test_event_hpp__

//libraries
#include "event.hpp"


class test_event
{
public:
	test_event() = default;
	~test_event() = default;
	void run();

	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
	void setevent();
};

#endif // __test_event_hpp__
