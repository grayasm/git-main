/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_autocritical_section_hpp__
#define __test_autocritical_section_hpp__


//libraries
#include "autocritical_section.hpp"


class test_autocritical_section
{
public:
	test_autocritical_section() = default;
	~test_autocritical_section() = default;

	void run();

	//begin test suite
	void ctor();
	void dtor();	
};


#endif // __test_autocritical_section_hpp__

