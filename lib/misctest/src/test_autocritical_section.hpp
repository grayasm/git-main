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


#ifndef __test_autocritical_section_hpp__
#define __test_autocritical_section_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "autocritical_section.hpp"


class test_autocritical_section : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_autocritical_section);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//begin test suite
	void ctor();
	void dtor();	
};


#endif // __test_autocritical_section_hpp__

