/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_autocritical_section_hpp__
#define __test_autocritical_section_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "autocritical_section.hpp"


class test_autocritical_section : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_autocritical_section);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//begin test suite
	void ctor();
	void dtor();	
};


#endif // __test_autocritical_section_hpp__

