/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_single_lock_hpp__
#define __test_single_lock_hpp__


//libraries
#include "single_lock.hpp"

class test_single_lock
{
public:
	test_single_lock() = default;
	~test_single_lock() = default;
	void run();

	// begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
};


#endif // __test_single_lock_hpp__
