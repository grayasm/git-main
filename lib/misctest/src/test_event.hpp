/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_event_hpp__
#define __test_event_hpp__



//c++
//...
//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries
#include "event.hpp"


class test_event : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_event);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(lock);
	CPPUNIT_TEST(trylock);
	CPPUNIT_TEST(unlock);
	CPPUNIT_TEST(setevent);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//begin test suite
	void ctor();
	void dtor();
	void lock();
	void trylock();
	void unlock();
	void setevent();
};

#endif // __test_event_hpp__
