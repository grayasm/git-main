/*
  Copyright (C) 2015 Mihai Vasilian

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

#ifndef __test_time_hpp__
#define __test_time_hpp__



//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries



class test_time : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_time);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(copy_ctor);
	CPPUNIT_TEST(copy_op);
	CPPUNIT_TEST(sub_op);
	CPPUNIT_TEST(add_op);
	CPPUNIT_TEST(lt_op);
	CPPUNIT_TEST(gt_op);
	CPPUNIT_TEST(eq_op);
	CPPUNIT_TEST(neq_op);
	CPPUNIT_TEST(lte_op);
	CPPUNIT_TEST(gte_op);
	CPPUNIT_TEST(incr_op);
	CPPUNIT_TEST(decr_op);
	CPPUNIT_TEST(tostring);
	CPPUNIT_TEST(tolocaltime);
	CPPUNIT_TEST(wday);
	CPPUNIT_TEST(yday);	
	CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;
		
	
	// -- main class --
	void ctor();
	void copy_ctor();
	void copy_op();
	void sub_op();
	void add_op();
	void lt_op();
	void gt_op();
	void eq_op();
	void neq_op();
	void lte_op();
	void gte_op();
	void incr_op();
	void decr_op();
	void tostring();
	void tolocaltime();
	void wday();
	void yday();	
	
};

#endif // __test_time_hpp__

