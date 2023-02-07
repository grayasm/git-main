/*
Copyright (C) 2013 Mihai Vasilian
*/



#ifndef __test_exception_hpp__
#define __test_exception_hpp__


//c
//c++

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//misc
#include "exception.hpp"


class test_exception : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_exception);
	CPPUNIT_TEST( ctor );
	CPPUNIT_TEST( dtor );    
	CPPUNIT_TEST_SUITE_END();


public:
	void setUp();
	void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;


	//////////////////////////////////////////////////////////////////////////
	//test begin
	void ctor();
	void dtor();
	//test end

	//////////////////////////////////////////////////////////////////////////
	//template version of test function
	template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	//////////////////////////////////////////////////////////////////////////

};//


#endif//__test_exception_hpp__
