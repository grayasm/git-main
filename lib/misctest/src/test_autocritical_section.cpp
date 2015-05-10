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


//this
#include "test_autocritical_section.hpp"


//c++
#include <iostream>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "stream.hpp"
#include "exception.hpp"
#include "thread.hpp"
#include "unistd.hpp"
#include "time.hpp"



//###########################BEGIN TEST CLASS ####################################
void test_autocritical_section::setUp()
{
}

void test_autocritical_section::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_autocritical_section::ctor()
{
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: autocritical_section.hpp            *";
    misc::cout <<   "\n\t*******************************************************";

	misc::cout << "\n\n\tctor---------------------------------------------------";
	{
		misc::critical_section cs;
		misc::autocritical_section acs(cs);
		CPPUNIT_ASSERT( true );
	}
	{
		misc::critical_section cs;
		misc::autocritical_section* acs;
		acs = new misc::autocritical_section(cs);
		CPPUNIT_ASSERT( acs != 0 );
		delete acs;
	}
	{
		const int CSNO=6;
		misc::critical_section cs[CSNO];
		misc::autocritical_section* acs[CSNO];
		for(int i=0; i < CSNO; ++i)
			acs[i] = new misc::autocritical_section(cs[i]);
		for(int i=0; i < CSNO; ++i)
			CPPUNIT_ASSERT( acs[i] != 0 );
		for(int i=0; i < CSNO; ++i)
			delete acs[i];
	}
}

void test_autocritical_section::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";
}



//##########################END  TEST  SUITE######################################