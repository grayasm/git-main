/*
  Copyright (C) 2013 Mihai Vasilian

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
