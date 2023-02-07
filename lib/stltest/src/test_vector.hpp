/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_vector_hpp__
#define __test_vector_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>



class test_vector : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_vector);
	CPPUNIT_TEST(ctor);
    CPPUNIT_TEST(assign_op);
    CPPUNIT_TEST(assign);
    CPPUNIT_TEST(begin);
    CPPUNIT_TEST(end);
    CPPUNIT_TEST(rbegin);
    CPPUNIT_TEST(rend);
    CPPUNIT_TEST(resize);
    CPPUNIT_TEST(capacity);
    CPPUNIT_TEST(reserve);
    CPPUNIT_TEST(at_and_op);
    CPPUNIT_TEST(front);
    CPPUNIT_TEST(back);
    CPPUNIT_TEST(push_back);
    CPPUNIT_TEST(pop_back);
    CPPUNIT_TEST(insert);
    CPPUNIT_TEST(erase);
    CPPUNIT_TEST(swap);
    CPPUNIT_TEST(clear);
    CPPUNIT_TEST(get_allocator);
    CPPUNIT_TEST(relational_op);
    CPPUNIT_TEST(perf1);
    CPPUNIT_TEST_SUITE_END();


public:
	void setUp();
	void tearDown();

    void ctor();
    void assign_op();
    void assign();
    void begin();
    void end();
    void rbegin();
    void rend();
    void resize();
    void capacity();
    void reserve();
    void at_and_op();
    void front();
    void back();
    void push_back();
    void pop_back();
    void insert();
    void erase();
    void swap();
    void clear();
    void get_allocator();
    void relational_op();
    void perf1();
};



#endif//__test_vector_hpp__
