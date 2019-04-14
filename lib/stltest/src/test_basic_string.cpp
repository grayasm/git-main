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


#include "test_basic_string.hpp"

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include <string>
#include "basic_string.hpp"
#include "time_printer.hpp"


void test_basic_string::setUp()
{
}

void test_basic_string::tearDown()
{
}

// Don't shoot for performance yet. Get everything correct first!
void test_basic_string::ctor()
{
    stl::basic_string<char> s0;
    stl::basic_string<char> s1(s0);
    stl::basic_string<char> s2(s1, 0, 0);

    stl::basic_string<char> s3("a string", 8);
    stl::basic_string<char> s4(s3);
    stl::basic_string<char> s5(s4, 2, 6);

    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "a string") == 0);
    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "a string") == 0);
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "string") == 0);

    stl::basic_string<char> s6("Mike is a great guy!");
    stl::basic_string<char> s7(s6, 8, 12);

    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "Mike is a great guy!") == 0);
    CPPUNIT_ASSERT(::strcmp(s7.c_str(), "a great guy!") == 0);
        
}
