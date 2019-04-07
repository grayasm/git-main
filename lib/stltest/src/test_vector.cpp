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


#include "test_vector.hpp"

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include <vector>
#include "vector.hpp"
#include "time_printer.hpp"


void test_vector::setUp()
{
}

void test_vector::tearDown()
{
}

template<typename T>
bool is_eq(const T& x, const T& y, const T& tol)
{
    return (x < y + tol && x > y - tol);
}


// Don't shoot for performance yet. Get the everything correct first!
void test_vector::ctor()
{
    // vector()
    stl::vector<char> v1;
    
    // vector(size_t, const T&);
    stl::vector<short> v2((size_t)5, (short)-1);
    for (int i = 0; i < 5; ++i)
    {
        if (v2[i] != -1)
            CPPUNIT_ASSERT(false);
    }
    
    
    // vector<InputIterator>(InputIterator first, InputIterator last);
    signed char sc1[5] = { 'a', 'b', 'c', 'd', 'e' };
    stl::vector<signed char> v3(sc1, sc1 + 5);
    for (int i = 0; i < 5; ++i)
    {
        if (v3[i] != sc1[i])
            CPPUNIT_ASSERT(false);
    }

    // vector(const vector&)
    stl::vector<float> v4;
    for (float f = 1.1f; f < 6; f += 1.1f)
        v4.push_back(f);
    stl::vector<float> v5(v4);
    for (int i = 0; i < v4.size(); ++i)
    {
        if (!is_eq(v4[i], v5[i], 1e-4f))
            CPPUNIT_ASSERT(false);
    }
}

