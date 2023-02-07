/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_stack_hpp__
#define __test_stack_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries




class test_stack : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_stack);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(empty);
	CPPUNIT_TEST(size);
	CPPUNIT_TEST(top);
	CPPUNIT_TEST(push);
	CPPUNIT_TEST(pop);	
	CPPUNIT_TEST(eq_op);
	CPPUNIT_TEST(neq_op);
	CPPUNIT_TEST(lt_op);
	CPPUNIT_TEST(gt_op);
	CPPUNIT_TEST(lte_op);
	CPPUNIT_TEST(gte_op);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //test begin
	void ctor();
	void dtor();
	void empty();
	void size();
	void top();
	void push();
	void pop();
	void eq_op();
	void neq_op();
	void lt_op();
	void gt_op();
	void lte_op();
	void gte_op();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	template<typename Container>
	void empty(const char* msg);
	template<typename Container>
	void size(const char* msg);
	template<typename Container>
	void top(const char* msg);
	template<typename Container>
	void push(const char* msg);
	template<typename Container>
	void pop(const char* msg);
	template<typename Container>
	void eq_op(const char* msg);
	template<typename Container>
	void neq_op(const char* msg);
	template<typename Container>
	void lt_op(const char* msg);
	template<typename Container>
	void gt_op(const char* msg);
	template<typename Container>
	void lte_op(const char* msg);
	template<typename Container>
	void gte_op(const char* msg);
    //////////////////////////////////////////////////////////////////////////
};




#endif//__test_stack_hpp__
