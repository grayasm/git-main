/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __test_thread_hpp__
#define __test_thread_hpp__


//c++
//...
//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries
#include "thread.hpp"


class test_thread : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_thread);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(run);
	CPPUNIT_TEST(resume);
	CPPUNIT_TEST(join);
	CPPUNIT_TEST(get_exit_code);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//begin test suite
	void ctor();
	void dtor();
	void run();
	void resume();
	void join();
	void get_exit_code();
};


#endif // __test_thread_hpp__
