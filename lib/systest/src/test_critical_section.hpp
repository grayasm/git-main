/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_critical_section_hpp__
#define __test_critical_section_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "critical_section.hpp"


class test_critical_section : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_critical_section);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(lock);
	CPPUNIT_TEST(unlock);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void unlock();

};


#endif // __test_critical_section_hpp__

