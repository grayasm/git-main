/*
Copyright (C) 2013 Mihai Vasilian
*/

#ifndef __test_multi_lock_hpp__
#define __test_multi_lock_hpp__

//libraries
#include "multi_lock.hpp"


class test_multi_lock
{
public:
	test_multi_lock() = default;
	~test_multi_lock() = default;
	void run();


	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
};



#endif // __test_multi_lock_hpp__