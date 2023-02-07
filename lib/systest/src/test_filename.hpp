/*
Copyright (C) 2009 Mihai Vasilian
*/



#ifndef __test_filename_hpp__
#define __test_filename_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries
#include "exception.hpp"
#include "filename.hpp"
#include "string.hpp"




class test_filename : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_filename);
    CPPUNIT_TEST(test0);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST(test2);
    CPPUNIT_TEST(test3);
    CPPUNIT_TEST(test4);
    CPPUNIT_TEST(test5);
    CPPUNIT_TEST(test6);
    CPPUNIT_TEST(test7);
    CPPUNIT_TEST(test8);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    void test0();
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
    void test8();
};//class test_filename



#endif//__test_filename_hpp__


