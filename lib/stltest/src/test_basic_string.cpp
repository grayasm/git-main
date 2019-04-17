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


    stl::basic_string<char> s8(0, 'c');
    stl::basic_string<char> s9(5, '5');

    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "") == 0);
    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "55555") == 0);
    

    char c10[] = "0123456789"; // size=10
    stl::basic_string<char> s10(c10, c10 + 10); //(char*,char*)
    CPPUNIT_ASSERT(::strcmp(s10.c_str(), "0123456789") == 0);


    const char c11[] = "0123456789"; // size=10
    stl::basic_string<char> s11(c11, c11 + 10); // (const char*,const char*)
    CPPUNIT_ASSERT(::strcmp(s11.c_str(), "0123456789") == 0);


    stl::basic_string<char> s12(s11.begin(), s11.end());//(iterator,iterator)
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "0123456789") == 0);


    const stl::basic_string<char>& s13 = s12;
    stl::basic_string<char> s14(s13.begin(), s13.end());//(const_iterator,const_iterator)
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "0123456789") == 0);


    stl::basic_string<char> s15(s14.rbegin(), s14.rend()); // (reverse_iterator,reverse_iterator)
    CPPUNIT_ASSERT(::strcmp(s15.c_str(), "9876543210") == 0);


    stl::basic_string<char> s16(s13.rbegin(), s13.rend());// (const_reverse_iterator, const_reverse_iterator)
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "9876543210") == 0);
}

void test_basic_string::assign_op()
{
    //  container& operator=(const container& str)
    stl::basic_string<char> s1, s2;
    s2 = s1;

    for (char c = '0'; c <= '9'; ++c)
        s1.push_back(c);
    s2 = s1;

    for (size_t i = 0; i < s1.size(); ++i)
    {
        if (s1[i] != s2[i])
            CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(s2.size() == s1.size());

    s2 = s2; //self

    //  container& operator=(const value_type* ptr)
    const char c3[] = "0123456789";
    stl::basic_string<char> s3;
    s3 = c3;
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "0123456789") == 0);

    const char c4 = 'c';
    stl::basic_string<char> s4;
    s4 = c4;
    CPPUNIT_ASSERT(s4.size() == 1 && s4[0] == 'c');
}

void test_basic_string::size()
{
    stl::basic_string<char> s1;
    CPPUNIT_ASSERT(s1.size() == 0);
    CPPUNIT_ASSERT(s1.length() == 0);
    CPPUNIT_ASSERT(s1.capacity() == 1);

    const char c2[] = "0123456789";
    stl::basic_string<char> s2(c2);
    CPPUNIT_ASSERT(s2.size() == 10);
    CPPUNIT_ASSERT(s2.length() == 10);
    CPPUNIT_ASSERT(s2.capacity() == 11);
}

void test_basic_string::resize()
{
    // resize(size_type sz, value_type c = value_type())
    const char c1[] = "0123456789";
    stl::basic_string<char> s1;
    s1.assign(c1, c1 + 10);

    s1.resize(8);  // resize to smaller size
    for (int i = 0; i < s1.size(); ++i)
        CPPUNIT_ASSERT(s1[i] == c1[i]);
    CPPUNIT_ASSERT(s1.size() == 8);

    s1.resize(6, c1[0]); // resize to smaller size
    for (int i = 0; i < s1.size(); ++i)
        CPPUNIT_ASSERT(s1[i] == c1[i]);
    CPPUNIT_ASSERT(s1.size() == 6);


    s1.assign(c1, c1 + 3);
    s1.resize(8, c1[0]); // resize to bigger size (default 2nd param)

    for (int i = 0; i < 3; ++i)
        CPPUNIT_ASSERT(s1[i] == c1[i]);
    for (int i = 4; i < 8; ++i)
        CPPUNIT_ASSERT(s1[i] == c1[0]);
    CPPUNIT_ASSERT(s1.size() == 8);

    s1.assign(c1, c1 + 5);
    s1.resize(5, s1[0]); // self assignment
    for (int i = 0; i < s1.size(); ++i)
        CPPUNIT_ASSERT(s1[i] == c1[i]);
    CPPUNIT_ASSERT(s1.size() == 5);
}

void test_basic_string::reserve()
{
    char c1[] = "0123456789";
    stl::basic_string<char> s1;
    s1.reserve(10);
    s1.assign(c1, c1 + 10);
    CPPUNIT_ASSERT(s1.capacity() == 11);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "0123456789") == 0);
}

void test_basic_string::clear()
{
    char c1[] = "0123456789";
    stl::basic_string<char> s1(c1);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), c1) == 0);

    s1.clear();
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "") == 0);
    CPPUNIT_ASSERT(s1.size() == 0);
    CPPUNIT_ASSERT(s1.capacity() == 11);
    CPPUNIT_ASSERT(s1.empty());
}

void test_basic_string::append_op()
{
    char c1[] = "0123456789";
    stl::basic_string<char> s1(c1);

    //  container& operator+=(const container& str)
    stl::basic_string<char> s2;
    s2 += s1;
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), s1.c_str()) == 0);

    //  container& operator+=(const value_type* ptr)
    stl::basic_string<char> s3;
    s3 += c1;
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), c1) == 0);

    //  container& operator+=(value_type ch)
    stl::basic_string<char> s4;
    for (size_t i = 0; i < 10; ++i)
        s4 += c1[i];

    CPPUNIT_ASSERT(::strcmp(s4.c_str(), c1) == 0);
}

void test_basic_string::append()
{
    //  container& append(const container& str)
    //  container& append(const container& str, size_type p2, size_type n2)
    //  container& append(const value_type* ptr, size_type n2)
    //  container& append(const value_type* ptr)
    //  container& append(size_type n, value_type value)
    //  inline container& append_(iterator& first, iterator& last)
//  inline container& append_(const iterator& first, const iterator& last) !!! see if it works
    //  inline container& append_(const_iterator& first, const_iterator& last)
    //  inline container& append_(value_type* first, value_type* last)
    //  inline container& append_(const value_type* first, const value_type* last)
    //  inline container& append_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    //  inline container& append_(InputIterator n, InputIterator value, stl::input_iterator_tag)
}