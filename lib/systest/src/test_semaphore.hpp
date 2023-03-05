/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_semaphore_hpp__
#define __test_semaphore_hpp__

//libraries
#include "semaphore.hpp"


class test_semaphore
{
public:
	test_semaphore() = default;
	~test_semaphore() = default;
	void run();


	// begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
	
};


#endif // __test_semaphore_hpp__
