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
    char c1[] = "0123456789";
    stl::basic_string<char> s1(c1, c1 + 10);
    s1.append(s1);  // from self
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "01234567890123456789") == 0);

    stl::basic_string<char> s2;
    s2.append(s1);  // from other
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "01234567890123456789") == 0);

    //  container& append(const container& str, size_type p2, size_type n2)
    stl::basic_string<char> s3;
    s3.append(s2, 10, 10);  // from other
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "0123456789") == 0);
    s3.append(s3, 0, 10);   // from self
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "01234567890123456789") == 0);
    
    stl::basic_string<char> s4;
    s4.append(s3, 10, -1);  // with npos
    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "0123456789") == 0);

    //  container& append(const value_type* ptr, size_type n2)
    char c5[] = "0123456789";
    stl::basic_string<char> s5;
    s5.append(c5, 10);
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "0123456789") == 0);

    s5.append(s5.c_str(), s5.size());   // from self
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "01234567890123456789") == 0);

    //  container& append(const value_type* ptr)
    s5.resize(10);
    s5.append(s5.c_str());
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "01234567890123456789") == 0);

    //  container& append(size_type n, value_type value)
    stl::basic_string<char> s6;
    s6.append(5, '9');
    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "99999") == 0);
    s6.append(5, s6[0]);
    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "9999999999") == 0);

    //  inline container& append_(iterator& first, iterator& last)
    char c7[] = "0123456789";
    stl::basic_string<char> s7(c7, c7 + 10);
    stl::basic_string<char> s8;
    s8.append(s7.begin(), s7.end());
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "0123456789") == 0);
    
    const stl::basic_string<char>::iterator& s7b = s7.begin();
    const stl::basic_string<char>::iterator& s7e = s7.end();
    stl::basic_string<char> s9;
    s9.append(s7b, s7e);
    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "0123456789") == 0);

    //  inline container& append_(const_iterator& first, const_iterator& last)
    char c10[] = "0123456789";
    stl::basic_string<char> s10(c10, c10 + 10);
    const stl::basic_string<char>::const_iterator& s10b = s10.begin();
    const stl::basic_string<char>::const_iterator& s10e = s10.end();
    stl::basic_string<char> s11;
    s11.append(s10b, s10e);
    CPPUNIT_ASSERT(::strcmp(s11.c_str(), "0123456789") == 0);
    
    //  inline container& append_(value_type* first, value_type* last)
    char c12[] = "0123456789";
    stl::basic_string<char> s12;
    s12.append(c12, c12 + 10);      // from C array
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "0123456789") == 0);

    stl::basic_string<char> s13;
    s13.append(s12.c_str(), s12.c_str() + 10);  // from other
    CPPUNIT_ASSERT(::strcmp(s13.c_str(), "0123456789") == 0);

    s13.append(s13.c_str(), s13.c_str() + 10);  // from self
    CPPUNIT_ASSERT(::strcmp(s13.c_str(), "01234567890123456789") == 0);

    //  inline container& append_(const value_type* first, const value_type* last)
    const char c14[] = "0123456789";
    stl::basic_string<char> s14;
    s14.append(c14, c14 + 10);
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "0123456789") == 0);

    const stl::basic_string<char>& s14a = s14;
    s14.append(s14a.c_str(), s14a.c_str() + 8);
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "012345678901234567") == 0);

    //  inline container& append_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    char c15[] = "0123456789";
    stl::basic_string<char> s15(c15, c15 + 10);
    stl::basic_string<char> s16;
    s16.append(s15.rbegin() + 2, s15.rend() - 2);   // reverse_iterator -- from other
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "765432") == 0);

//TODO: search again in this file and maybe in test_vector, and run additional
//      tests where for .begin() add also .begin() + 2 or
//      or where for .rbegin() add also .rbegin() + 2, .rend() - 2 or so.

    s16.append(s16.rbegin() + 2, s16.rend() - 2);   // reverse_iterator -- from self
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "76543245") == 0);

    stl::basic_string<char> s17(c15, c15 + 10);
    const stl::basic_string<char>& s17a = s17;
    stl::basic_string<char> s18;
    s18.append(s17a.rbegin() + 1, s17a.rend() - 1); // reverse_iterator -- from other
    CPPUNIT_ASSERT(::strcmp(s18.c_str(), "87654321") == 0);

    const stl::basic_string<char>& s18a = s18;
    s18.append(s18a.rbegin() + 1, s18a.rend() - 1); // reverse_iterator -- from self
    CPPUNIT_ASSERT(::strcmp(s18.c_str(), "87654321234567") == 0);

    //  inline container& append_(InputIterator n, InputIterator value, stl::input_iterator_tag)
    stl::basic_string<char> s19;
    s19.append(1, '0');
    s19.append(2, '2');
    s19.append(3, '3');
    s19.append(5, s19[0]);
    CPPUNIT_ASSERT(::strcmp(s19.c_str(), "02233300000") == 0);
}

void test_basic_string::push_back()
{
    stl::basic_string<char> s1;

    for (int i = 0; i < 10; ++i)
        s1.push_back('0' + i);
        
    for (int i = 0; i < 10; ++i)
        s1.push_back(s1[i]);

    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "01234567890123456789") == 0);
}

void test_basic_string::assign()
{
    //  container& assign(const container& tc)
    char c1[] = "0123456789";
    stl::basic_string<char> s1(c1, c1 + 10);
    stl::basic_string<char> s2;
    s2.assign(s1);
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), c1) == 0);
    
    //  container& assign(const container& str, size_type off, size_type n)
    //  container& assign(const value_type* ptr, size_type n)
    //  container& assign(const value_type* ptr)
    //  container& assign(size_type n, const value_type& c)
    //  container& assign(InputIterator first, InputIterator last)
    //  inline container& assign_(iterator& first, iterator& last)
    //  inline container& assign_(const_iterator& first, const_iterator& last)
    //  inline container& assign_(value_type* first, value_type* last)
    //  inline container& assign_(const value_type* first, const value_type* last)
    //  inline container& assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    //  inline container& assign_(InputIterator count, InputIterator value, stl::input_iterator_tag)

}