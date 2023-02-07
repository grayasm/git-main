/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_list_hpp__
#define __test_list_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>



class test_list : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_list);
    CPPUNIT_TEST(ctor);
    CPPUNIT_TEST(assign_op);
    CPPUNIT_TEST(assign);
    CPPUNIT_TEST(get_allocator);
    CPPUNIT_TEST(begin);
    CPPUNIT_TEST(end);
    CPPUNIT_TEST(rbegin);
    CPPUNIT_TEST(rend);
    CPPUNIT_TEST(resize);
    CPPUNIT_TEST(front);
    CPPUNIT_TEST(back);
    CPPUNIT_TEST(push_front);
    CPPUNIT_TEST(pop_front);
    CPPUNIT_TEST(push_back);
    CPPUNIT_TEST(pop_back);
    CPPUNIT_TEST(insert);
    CPPUNIT_TEST(erase);
    CPPUNIT_TEST(swap);
    CPPUNIT_TEST(clear);
    CPPUNIT_TEST(splice);
    CPPUNIT_TEST(remove);
    CPPUNIT_TEST(unique);
    CPPUNIT_TEST(merge);
    CPPUNIT_TEST(sort);
    CPPUNIT_TEST(reverse);
    CPPUNIT_TEST(perf1);
    CPPUNIT_TEST_SUITE_END();


public:
    void setUp();
    void tearDown();

    void ctor();
    void assign_op();
    void assign();
    void get_allocator();
    void begin();
    void end();
    void rbegin();
    void rend();
    void resize();
    void front();
    void back();
    void push_front();
    void pop_front();
    void push_back();
    void pop_back();
    void insert();
    void erase();
    void swap();
    void clear();
    void splice();
    void remove();
    void unique();
    void merge();
    void sort();
    void reverse();
    void perf1();
};



#endif//__test_vector_hpp__
