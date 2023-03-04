/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_thread_hpp__
#define __test_thread_hpp__

//libraries
#include "thread.hpp"


class test_thread
{
public:
	test_thread() = default;
	~test_thread() = default;
	void run_();


	//begin test suite
	void ctor();
	void dtor();
	void run();
	void resume();
	void join();
	void get_exit_code();
};


#endif // __test_thread_hpp__
