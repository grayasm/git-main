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



#include "test_exception.hpp"

//c
#include <string.h>
#include <time.h>
//c++

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "stream.hpp"
#include "misctest_util.hpp"



//###########################DEQUE TEST CLASS ####################################
void test_exception::setUp()
{
}

void test_exception::tearDown()
{
}


//test begin
void test_exception::ctor()
{
	misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: exception.hpp                       *";
    misc::cout <<   "\n\t*******************************************************";

	
	misc::cout << "\n\n\tctor---------------------------------------------------";
	ctor<misc::exception>("\n\tmisc::exception");
	ctor<std::bad_alloc>("\n\tstd::bad_alloc");
}



void test_exception::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";
	dtor<misc::exception>("\n\tmisc::exception");
	dtor<std::bad_alloc>("\n\tstd::bad_alloc");
}


// test end 

//////////////////////////////////////////////////////////////////////////
//template version of test function

template<typename Container>
void test_exception::ctor(const char* msg)
{
	{
		time_printer tp(msg, m_print_time);

		Container exc;
		try
		{
			throw exc;
		}
		catch(const Container& mexc)
		{
			mexc.what();
		}
	}
}

template<typename Container>
void test_exception::dtor(const char* msg)
{
	{
		time_printer tp(msg, m_print_time);

		Container exc;
	}	
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////