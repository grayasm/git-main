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



#ifndef __test_exception_hpp__
#define __test_exception_hpp__


//c
//c++

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//misc
#include "exception.hpp"


class test_exception : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_exception);
	CPPUNIT_TEST( ctor );
	CPPUNIT_TEST( dtor );    
	CPPUNIT_TEST_SUITE_END();


public:
	void setUp();
	void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;


	//////////////////////////////////////////////////////////////////////////
	//test begin
	void ctor();
	void dtor();
	//test end

	//////////////////////////////////////////////////////////////////////////
	//template version of test function
	template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	//////////////////////////////////////////////////////////////////////////

};//


#endif//__test_exception_hpp__
