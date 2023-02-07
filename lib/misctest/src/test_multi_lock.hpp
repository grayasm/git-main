/*
Copyright (C) 2013 Mihai Vasilian
*/

#ifndef __test_multi_lock_hpp__
#define __test_multi_lock_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "multi_lock.hpp"


class test_multi_lock : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_multi_lock);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(lock);
	CPPUNIT_TEST(trylock);
	CPPUNIT_TEST(unlock);
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
};



#endif // __test_multi_lock_hpp__