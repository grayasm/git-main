/*
Copyright (C) 2012 Mihai Vasilian
*/




#ifndef __test_numeric_hpp__
#define __test_numeric_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>





class test_numeric : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_numeric);
    CPPUNIT_TEST(accumulate);	
	CPPUNIT_TEST(adjacent_difference);
	CPPUNIT_TEST(inner_product);
	CPPUNIT_TEST(partial_sum);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;

	//////////////////////////////////////////////////////////////////////////	
    //test begin
    void accumulate();
	void adjacent_difference();
	void inner_product();
	void partial_sum();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
	void accumulate(const char* msg);
	template<typename Container>
	void adjacent_difference(const char* msg);
	template<typename Container>
	void inner_product(const char* msg);
	template<typename Container>
	void partial_sum(const char* msg);
    //////////////////////////////////////////////////////////////////////////
};



#endif//__test_numeric_hpp__
