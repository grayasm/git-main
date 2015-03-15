/*
  Copyright (C) 2009 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
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


