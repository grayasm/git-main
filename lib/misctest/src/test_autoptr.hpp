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







#ifndef __autoptr_t_hpp__
#define __autoptr_t_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "autoptr.hpp"



class test_autoptr : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_autoptr);
    CPPUNIT_TEST(test_assignment_with_different_type);
    CPPUNIT_TEST(test_assignment_with_different_type1);
    CPPUNIT_TEST(test_assignment_with_different_type3);
    CPPUNIT_TEST(test_operator_less);
    CPPUNIT_TEST(test_operator_great);
    CPPUNIT_TEST(test_sort);
    CPPUNIT_TEST(test_derived_operator_less);
    CPPUNIT_TEST(test_derived_operator_great);
    CPPUNIT_TEST(test_self_assignament);
    CPPUNIT_TEST(test_child_assignament);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //begin test suite
    void test_assignment_with_different_type();
    void test_assignment_with_different_type1();
    void test_assignment_with_different_type3();
    void test_operator_less();
    void test_operator_great();
    void test_sort();
    void test_derived_operator_less();
    void test_derived_operator_great();
    void test_self_assignament();
    void test_child_assignament();
    //end test suite
};




#endif//__autoptr_t_hpp__
