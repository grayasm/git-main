/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_mutex_hpp__
#define __test_mutex_hpp__


//libraries
#include "mutex.hpp"


class test_mutex
{
public:
	test_mutex() = default;
	~test_mutex() = default;
	void run();


	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
};

#endif // __test_mutex_hpp__
