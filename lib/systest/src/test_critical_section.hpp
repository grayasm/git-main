/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_critical_section_hpp__
#define __test_critical_section_hpp__


//libraries
#include "critical_section.hpp"


class test_critical_section
{
public:
	test_critical_section() = default;
	~test_critical_section() = default;
	void run();

	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void unlock();
};


#endif // __test_critical_section_hpp__

