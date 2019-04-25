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
    //stl::basic_string<char> s2(s1, 0, 0); -- does not make sense!
    // it can happen only if s1 is not empty


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
    s2.assign(s1);      // from other
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), c1) == 0);

    s2.assign(s2);      // from self
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "0123456789") == 0);
    
    //  container& assign(const container& str, size_type off, size_type n)
    char c3[] = "0123456789";
    stl::basic_string<char> s3(c3, c3 + 10);
    stl::basic_string<char> s4;
    s4.assign(s3, 0, 0);
    CPPUNIT_ASSERT(s4.size() == 0);
    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "") == 0);

    s4.assign(s3, 0, 10);
    CPPUNIT_ASSERT(::strcmp(s4.c_str(), c3) == 0);

    stl::basic_string<char> s5;
    s5.assign(s3, 0, -1);
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), c3) == 0);

    stl::basic_string<char> s6;
    s6.assign(s3, 4, 6);
    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "456789") == 0);

//TODO: check the returned type if not void for all in test_basic_string and test_vector
    s6.assign(s6, 0, 4);    // from self
    s6.assign(s6, 2, 2);
    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "67") == 0);

    //  container& assign(const value_type* ptr, size_type n)
    char c7[] = "0123456789";
    stl::basic_string<char> s7;
    s7.assign(c7, 10);

    CPPUNIT_ASSERT(::strcmp(s7.c_str(), c7) == 0);

    s7.assign(s7.c_str() + 3, s7.size() - 3);   // from self
    CPPUNIT_ASSERT(::strcmp(s7.c_str(), "3456789") == 0);
    
    //  container& assign(const value_type* ptr)
    char c8[] = "0123456789";
    stl::basic_string<char> s8;
    s8.assign(c8);
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), c8) == 0);
    
    s8.assign(s8.c_str());
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), c8) == 0);

    s8.assign(s8.c_str() + 5);
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "56789") == 0);

    //  container& assign(size_type n, const value_type& c)
    stl::basic_string<char> s9;
    s9.assign(3, '3');
    s9.assign(4, '4').c_str();
    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "4444") == 0);
    
    //  container& assign(InputIterator first, InputIterator last)
    //  inline container& assign_(iterator& first, iterator& last)
    char c10[] = "0123456789";
    stl::basic_string<char> s10(c10, c10 + 10);
    stl::basic_string<char> s11;
    s11.assign(s10.begin(), s10.end());     // from other
    CPPUNIT_ASSERT(::strcmp(s10.c_str(), c10) == 0);

    s11.assign(s11.begin() + 1, s11.end() - 1); // from self
    CPPUNIT_ASSERT(::strcmp(s11.c_str(), "12345678") == 0);
    
    //  inline container& assign_(const_iterator& first, const_iterator& last)
    const stl::basic_string<char>& s11c = s11;
    stl::basic_string<char> s12;
    s12.assign(s11c.begin(), s11c.end());   // from other
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "12345678") == 0);
    
    const stl::basic_string<char>& s12c = s12;
    s12.assign(s12c.begin() + 1, s12c.end() - 1); // from self
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "234567") == 0);

    //  inline container& assign_(value_type* first, value_type* last)
    char c13[] = "0123456789";
    stl::basic_string<char> s13;
    s13.assign(c13, c13 + 10);  // from other
    s13.assign(c13, c13 + 10).c_str();  // check the return type
    CPPUNIT_ASSERT(::strcmp(s13.c_str(), c13) == 0);

    s13.assign(&s13[0], &s13[0] + 10);  // from self
    CPPUNIT_ASSERT(::strcmp(s13.c_str(), c13) == 0);

    //  inline container& assign_(const value_type* first, const value_type* last)
    const char c14[] = "0123456789";
    stl::basic_string<char> s14;
    s14.assign(c14, c14 + 8);   // from other
    s14.assign(c14, c14 + 10).c_str();
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), c14) == 0);

    const stl::basic_string<char>& s14c = s14;
    s14.assign(&s14c[0], &s14c[0] + 10);    // from self
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), c14) == 0);

    //  inline container& assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    char c15[] = "0123456789";
    stl::basic_string<char> s15(c15, c15 + 10);
    stl::basic_string<char> s16;
    s16.assign(s15.rbegin() + 1, s15.rend() - 1);   // from other
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "87654321") == 0);

    s16.assign(s16.rbegin() + 1, s16.rend() - 1).c_str(); // from self
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "234567") == 0);

    //  inline container& assign_(InputIterator count, InputIterator value, stl::input_iterator_tag)
    stl::basic_string<char> s17;
    char count = 5;
    char value = '5';
    s17.assign(count, value).c_str();
    CPPUNIT_ASSERT(::strcmp(s17.c_str(), "55555") == 0);
}

void test_basic_string::insert()
{
    //  container& insert(size_type pos, const container& str)
    stl::basic_string<char> s1("ABCabc");

    stl::basic_string<char> s2(s1), s3(s1);
    s2.insert(2, s1);                       // in 2
    s3.insert(s3.size(), s1).c_str();       // in end() + test the return type
    
    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "ABABCabcCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCabcABCabc") == 0);

    stl::basic_string<char> s4(s1), s5(s1);
    s4.insert(2, s4);
    s5.insert(s5.size(), s5);

    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "ABABCabcCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCabcABCabc") == 0);


    //  container& insert(size_type pos, const container& str, size_type off, size_type n)
    stl::basic_string<char> s6("ABCabc");

    stl::basic_string<char> s7(s6), s8(s6), s9(s6);
    s7.insert(0, s6, 0, 0);                 // no action
    s8.insert(2, s6, 1, -1);                // n = npos
    s9.insert(s9.size(), s6, 3, 3).c_str(); // in end() position + return type

    CPPUNIT_ASSERT(::strcmp(s7.c_str(), "ABCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "ABBCabcCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "ABCabcabc") == 0);


    char c10[] = "ABCDefgh";
    stl::basic_string<char> s10(c10), s11(c10), s12(c10);
    s10.insert(2, s10, 0, 4);           // from self w/ overlapping
    s11.insert(2, s11, 2, 4);           // from self w/ overlapping
    s12.insert(2, s12, 4, 4).c_str();   // from self testing return type

    CPPUNIT_ASSERT(::strcmp(s10.c_str(), "ABABCDCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s11.c_str(), "ABCDefCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "ABefghCDefgh") == 0);


    //  container& insert(size_type pos, const value_type* ptr)
    stl::basic_string<char> s13("ABCDefgh");

    stl::basic_string<char> s14(s13), s15(s13), s16(s13);
    s14.insert(0, "01234").c_str();     // in 0 position + return type
    s15.insert(5, "01234");             // in middle
    s16.insert(s16.size(), "01234");    // in end() position

    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "01234ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s15.c_str(), "ABCDe01234fgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "ABCDefgh01234") == 0);


    size_t sz13 = s13.size();
    stl::basic_string<char> s17(s13), s18(s13), s19(s13);
    s17.insert(2, s17.c_str() + sz13 - 2);
    s18.insert(4, s18.c_str() + sz13 - 4);
    s19.insert(6, s19.c_str() + sz13 - 6);

    CPPUNIT_ASSERT(::strcmp(s17.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s18.c_str(), "ABCDefghefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s19.c_str(), "ABCDefCDefghgh") == 0);

    //  container& insert(size_type pos, const value_type* ptr, size_type n)
    stl::basic_string<char> s20("ABCDefgh"), s21("ABCDefgh"), s22("ABCDefgh");

    s20.insert(0, "", 0);
    s20.insert(0, "01234", 5);
    s21.insert(4, "01234", 2);
    s22.insert(s22.size(), "012345", 3);

    CPPUNIT_ASSERT(::strcmp(s20.c_str(), "01234ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s21.c_str(), "ABCD01efgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s22.c_str(), "ABCDefgh012") == 0);

    stl::basic_string<char> s23("ABCDefgh"), s24("ABCDefgh"), s25("ABCDefgh");

    s23.insert(2, s23.c_str() + 6, 2);
    s24.insert(7, s24.c_str() + 2, 2);
    s25.insert(1, s25.c_str() + 5, 2);

    CPPUNIT_ASSERT(::strcmp(s23.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s24.c_str(), "ABCDefgCDh") == 0);
    CPPUNIT_ASSERT(::strcmp(s25.c_str(), "AfgBCDefgh") == 0);

    //  container& insert(size_type pos, size_type n, value_type c)
    stl::basic_string<char> s26("ABCabc"), s27("ABCabc"), s28("ABCabc");
    s26.insert(0, 0, '0');
    s26.insert(0, 3, '0');                  // in 0 position
    s27.insert(3, 3, '0');                  // in middle position
    s28.insert(s28.size(), 3, '0').c_str(); // in end() position

    CPPUNIT_ASSERT(::strcmp(s26.c_str(), "000ABCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s27.c_str(), "ABC000abc") == 0);
    CPPUNIT_ASSERT(::strcmp(s28.c_str(), "ABCabc000") == 0);

    stl::basic_string<char> s29, s30, s31;
    s29.insert(0, 5, '5');
    s30.insert(s30.size(), 5, '5');
    for (int i = 0; i < 5; ++i)
        s31.insert(0, 1, '0' + i);

    CPPUNIT_ASSERT(::strcmp(s29.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s30.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s31.c_str(), "43210") == 0);

    //  void insert(iterator position, size_type n, value_type c)
    stl::basic_string<char> s32("ABCabc"), s33("ABCabc"), s34("ABCabc");
    s32.insert(s32.begin(), 0, '0');
    s32.insert(s32.begin(), 3, '0');        // in 0 position
    s33.insert(s33.begin() + 3, 3, '0');    // in middle position
    s34.insert(s34.end(), 3, '0');          // in end() position

    CPPUNIT_ASSERT(::strcmp(s32.c_str(), "000ABCabc") == 0);
    CPPUNIT_ASSERT(::strcmp(s33.c_str(), "ABC000abc") == 0);
    CPPUNIT_ASSERT(::strcmp(s34.c_str(), "ABCabc000") == 0);

    stl::basic_string<char> s35, s36, s37;      // repeat but with empty strings
    s35.insert(s35.begin(), 5, '5');
    s36.insert(s36.end(), 5, '5');
    for (int i = 0; i < 5; ++i)
        s37.insert(s37.begin(), (size_t)1, (char)'0' + i);

    CPPUNIT_ASSERT(::strcmp(s35.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s36.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s37.c_str(), "43210") == 0);


    //  iterator insert(iterator position, value_type c)
    stl::basic_string<char> s38;
    s38.insert(s38.begin(), 'b');
    s38.insert(s38.end(), 'c');
    s38.insert(s38.begin(), 'a');

    CPPUNIT_ASSERT(::strcmp(s38.c_str(), "abc") == 0);

    //  inline void insert_(iterator& position, iterator& first, iterator& last)
    stl::basic_string<char> s39("ABCDefgh");
    stl::basic_string<char> s40(s39), s41(s39), s42(s39);
            
            // insert from other container
    s40.insert(s40.begin() + 2, s39.end() - 2, s39.end());          // ABghCDefgh
    s41.insert(s41.begin() + 6, s39.begin() + 2, s39.begin() + 4);  // ABCDefCDgh
    s42.insert(s42.begin() + 4, s39.begin() + 3, s39.begin() + 5);  // ABCDDeefgh

    CPPUNIT_ASSERT(::strcmp(s40.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s41.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s42.c_str(), "ABCDDeefgh") == 0);


            // insert from self
    stl::basic_string<char> s43(s39), s44(s39), s45(s39);
    s43.insert(s43.begin() + 2, s43.end() - 2, s43.end());
    s44.insert(s44.begin() + 6, s44.begin() + 2, s44.begin() + 4);
    s45.insert(s45.begin() + 4, s45.begin() + 3, s45.begin() + 5);

    CPPUNIT_ASSERT(::strcmp(s43.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s44.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s45.c_str(), "ABCDDeefgh") == 0);
    
    //  inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
    const stl::basic_string<char> s46("ABCDefgh");
    stl::basic_string<char> s47(s46), s48(s46), s49(s46);

            // insert from other container
    s47.insert(s47.begin() + 2, s46.end() - 2, s46.end());          // ABghCDefgh
    s48.insert(s48.begin() + 6, s46.begin() + 2, s46.begin() + 4);  // ABCDefCDgh
    s49.insert(s49.begin() + 4, s46.begin() + 3, s46.begin() + 5);  // ABCDDeefgh

    CPPUNIT_ASSERT(::strcmp(s47.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s48.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s49.c_str(), "ABCDDeefgh") == 0);

            // insert from self
    stl::basic_string<char> s50(s46), s51(s46), s52(s46);
    const stl::basic_string<char>& s50a = s50;
    const stl::basic_string<char>& s51a = s51;
    const stl::basic_string<char>& s52a = s52;
    s50.insert(s50.begin() + 2, s50a.end() - 2, s50a.end());
    s51.insert(s51.begin() + 6, s51a.begin() + 2, s51a.begin() + 4);
    s52.insert(s52.begin() + 4, s52a.begin() + 3, s52a.begin() + 5);

    CPPUNIT_ASSERT(::strcmp(s50.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s51.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s52.c_str(), "ABCDDeefgh") == 0);

    //  inline void insert_(iterator& position, value_type* first, value_type* last)
    char c53[] = "ABCDefgh";
    stl::basic_string<char> s53, s54, s55(c53);
    s53.insert(s53.begin(), c53, c53 + 8);
    s54.insert(s54.end(), c53, c53 + 8);
    s55.insert(s55.begin() + 4, c53, c53 + 8);

    CPPUNIT_ASSERT(::strcmp(s53.c_str(), "ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s54.c_str(), "ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s55.c_str(), "ABCDABCDefghefgh") == 0);

    stl::basic_string<char> s56("ABCDefgh"), s57("ABCDefgh"), s58("ABCDefgh");
    s56.insert(s56.begin() + 2, &*s56.begin() + 6, &*s56.begin() + 8);
    s57.insert(s57.begin() + 6, &*s57.begin() + 2, &*s57.begin() + 4);
    s58.insert(s58.begin() + 4, &*s58.begin() + 3, &*s58.begin() + 5);

    CPPUNIT_ASSERT(::strcmp(s56.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s57.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s58.c_str(), "ABCDDeefgh") == 0);

    //  inline void insert_(iterator& position, const value_type* first, const value_type* last)
    const char c60[] = "ABCDefgh";
    stl::basic_string<char> s60, s61, s62(c60);
    s60.insert(s60.begin(), c60, c60 + 8);
    s61.insert(s61.end(), c60, c60 + 8);
    s62.insert(s62.begin() + 4, c60, c60 + 8);

    CPPUNIT_ASSERT(::strcmp(s60.c_str(), "ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s61.c_str(), "ABCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s62.c_str(), "ABCDABCDefghefgh") == 0);

    stl::basic_string<char> s63("ABCDefgh"), s64("ABCDefgh"), s65("ABCDefgh");
    const stl::basic_string<char>& s63a = s63;
    const stl::basic_string<char>& s64a = s64;
    const stl::basic_string<char>& s65a = s65;

    s63.insert(s63.begin() + 2, &*s63a.begin() + 6, &*s63a.begin() + 8);
    s64.insert(s64.begin() + 6, &*s64a.begin() + 2, &*s64a.begin() + 4);
    s65.insert(s65.begin() + 4, &*s65a.begin() + 3, &*s65a.begin() + 5);

    CPPUNIT_ASSERT(::strcmp(s63.c_str(), "ABghCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s64.c_str(), "ABCDefCDgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s65.c_str(), "ABCDDeefgh") == 0);

    //  inline void insert_(iterator& position, InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
    char c66[] = "ABCDefgh";
    stl::basic_string<char> s66(c66);
    stl::basic_string<char> s67(c66), s68(c66), s69(c66);
    s67.insert(s67.begin() + 2, s66.rbegin(), s66.rbegin() + 2);
    s68.insert(s68.begin() + 6, s66.rbegin() + 4, s66.rbegin() + 6);
    s69.insert(s69.begin() + 4, s66.rbegin() + 3, s66.rbegin() + 5);

    CPPUNIT_ASSERT(::strcmp(s67.c_str(), "ABhgCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s68.c_str(), "ABCDefDCgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s69.c_str(), "ABCDeDefgh") == 0);

    stl::basic_string<char> s70(c66), s71(c66), s72(c66);
    s70.insert(s70.begin() + 2, s70.rbegin(), s70.rbegin() + 2);
    s71.insert(s71.begin() + 6, s71.rbegin() + 4, s71.rbegin() + 6);
    s72.insert(s72.begin() + 4, s72.rbegin() + 3, s72.rbegin() + 5);

    CPPUNIT_ASSERT(::strcmp(s70.c_str(), "ABhgCDefgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s71.c_str(), "ABCDefDCgh") == 0);
    CPPUNIT_ASSERT(::strcmp(s72.c_str(), "ABCDeDefgh") == 0);

    //  inline void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
    char c73[] = "ABCDefgh";
    stl::basic_string<char> s73, s74, s75(c73);

    s73.insert(s73.begin(), 5, 0 + '5');        // in 0 position
    s74.insert(s74.end(), 5, 0 + '5');          // in end() position
    s75.insert(s75.begin() + 4, 5, 0 + '5');    // in middle position

    CPPUNIT_ASSERT(::strcmp(s73.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s74.c_str(), "55555") == 0);
    CPPUNIT_ASSERT(::strcmp(s75.c_str(), "ABCD55555efgh") == 0);

    //  Trying to persuade an insert from self, with both char& arguments.
    stl::basic_string<char> s76("!start:");
    char& n76 = s76[0]; // '!' is 33
    char& c76 = s76[0]; // '!'
    s76.insert(s76.begin() + 3, n76, c76);
    CPPUNIT_ASSERT(::strcmp(s76.c_str(), "!st!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!art:") == 0);
}


void test_basic_string::erase()
{
    //  container& erase(size_type pos = 0, size_type len = npos)
    stl::basic_string<char> s1("ABCD----efgh----01234");
    s1.erase(4, 4);
    s1.erase(8, 4);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "ABCDefgh01234") == 0);
    
    s1.erase(8, -1);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "ABCDefgh") == 0);

    s1.erase(0, 4);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "efgh") == 0);

    //  iterator erase(iterator position)
    stl::basic_string<char> s2("ABCD----efgh----01234");
    for (int i = 0; i < 4; ++i)
        s2.erase(s2.begin() + 12);
    for (int i = 0; i < 4; ++i)
        s2.erase(s2.begin() + 4);

    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "ABCDefgh01234") == 0);

    // iterator erase(iterator first, iterator last)
    stl::basic_string<char> s3("ABCD----efgh----01234");
    s3.erase(s3.begin() + 4, s3.begin() + 8);
    s3.erase(s3.begin() + 8, s3.begin() + 12);
    s3.erase(s3.begin() + 8, s3.end());

    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDefgh") == 0);
}

void test_basic_string::replace()
{
    typedef stl::basic_string<char> string; // getting tired of typing

    //  container& replace(size_type pos, size_type len, const container& str)
    string s1("ABCD1234efgh");
    s1.replace(0, 4, string("abcd"));  //[abcd]12345efgh    // from other
    s1.replace(4, 4, string("0"));     //abcd[0]efgh
    s1.replace(0, 9, s1);              //abcd0efgh          // from self
    s1.replace(0, 8, s1);              //abcd0efghh
    s1.replace(0, 4, string(""));      //0efghh
    s1.replace(5, -1, string("1234")); //0efgh1234

    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "0efgh1234") == 0);

    //  inline container& replace(iterator first, iterator last, const container& str)
    typedef stl::basic_string<char> string;
    string s2("ABCD1234efgh");
    s2.replace(s2.begin(), s2.begin() + 4, string("abcd")); //[abcd]1234efgh    - from other
    s2.replace(s2.begin() + 4, s2.begin() + 8, string("0"));//abcd[0]efgh
    s2.replace(s2.begin(), s2.begin() + 9, s2);             //abcd0efgh         - from self
    s2.replace(s2.begin(), s2.begin() + 8, s2);             //abcd0efghh
    s2.replace(s2.begin(), s2.begin() + 4, string(""));     //0efghh
    s2.replace(s2.begin() + 5, s2.end(), string("1234"));   //0efgh1234

    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "0efgh1234") == 0);

    //  container& replace(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen)
    string s3("ABCDefghijk123456789");
    s3.replace(0, 4, string("abcd"), 0, 4);             //abcdefghijk123456789
    s3.replace(11, 100/*not -1*/, string("."), 0, 0);   //abcdefghijk
    s3.replace(10, -1, string("k0"), 0, 2);             //abcdefghijk0
    s3.replace(11, -1, string("???"), 1, -1);           //abcdefghijk??
    s3.replace(4, 7, string("EFGHIJK"), 0, 20);         //abcdEFGHIJK??
    s3.replace(8, -1, string("1234?"), 0, -1);          //abcdEFGH1234?

    s3.replace(12, 4, s3, 8, 0);                        //abcdEFGH1234
    s3.replace(8, 0, s3, 0, 4);                         //abcdEFGHabcd1234
    s3.replace(0, 4, s3, 0, 0);                         //EFGHabcd1234

    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "EFGHabcd1234") == 0);

    //  container& replace(size_type pos, size_type len, const char* ptr)
    string s4("ABCDefgh1234");                          //ABCDefgh1234
    s4.replace(8, 100, "1234x");                        //ABCDefgh1234x
    s4.replace(0, 0, "");                               //ABCDefgh1234x
    s4.replace(0, 4, "abcd");                           //abcdefgh1234x
    s4.replace(4, 4, "EFGH");                           //abcdEFGH1234x
    s4.replace(8, -1, "");                              //abcdEFGH
    s4.replace(7, 1, "H1234xyzw");                      //abcdEFGH1234xyzw

    s4.replace(0, 4, s4.c_str() + 12);                  //xyzwEFGH1234xyzw
    s4.replace(12, 4, s4.c_str() + 8);                  //xyzwEFGH12341234xyzw
    s4.replace(0, 4, s4.c_str() + 20);                  //EFGH12341234xyzw
    s4.replace(8, -1, s4.c_str() + 12);                 //EFGH1234xyzw

    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "EFGH1234xyzw") == 0);

    // container& replace(iterator first, iterator last, const value_type* ptr)
    string s5("abcd1234");
    s5.replace(s5.begin(), s5.begin() + 4, "xyzwABCD");     //xyzwABCD1234
    s5.replace(s5.begin() + 8, s5.end(), "5678");           //xyzwABCD5678

    s5.replace(s5.begin() + 4, s5.begin() + 8, s5.c_str() + 4); //xyzwABCD56785678
    s5.replace(s5.begin() + 8, s5.end(), s5.c_str() + 12);      //xyzwABCD5678

    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "xyzwABCD5678") == 0);

    // container& replace(size_type pos, size_type len, const value_type* ptr, size_type n)
    string s6("....xxxx????");                  //....xxxx????
    s6.replace(0, 4, "123456", 4);              //1234xxxx????
    s6.replace(4, 4, "abcd", -1);               //1234abcd????
    s6.replace(8, -1, "EFGH", 4);               //1234abcdEFGH

    s6.replace(4, 4, s6.c_str() + 8);           //1234EFGHEFGH
    s6.replace(8, -1, s6.c_str() + 8);          //1234EFGHEFGH
    s6.replace(8, 5, s6.c_str() + 12);          //1234EFGH

    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "1234EFGH") == 0);

    //  container& replace(iterator first, iterator last, const value_type* ptr, size_type n)
    string s7("abcd1234");                                  //abcd1234
    s7.replace(s7.begin(), s7.begin() + 4, "xyzwABCD", 8);  //xyzwABCD1234
    s7.replace(s7.begin() + 8, s7.end(), "5678", 10);       //xyzwABCD5678

    s7.replace(s7.begin() + 4, s7.begin() + 8, s7.c_str() + 4, s7.size() - 4);  //xyzwABCD56785678
    s7.replace(s7.begin() + 8, s7.end(), s7.c_str() + 12, -1);                  //xyzwABCD5678

    CPPUNIT_ASSERT(::strcmp(s7.c_str(), "xyzwABCD5678") == 0);

    //  container& replace(size_type pos, size_type len, size_type n, value_type c)
    string s8("ABCDefgh1234");
    s8.replace(0, 4, 0, '0');       //efgh1234
    s8.replace(4, -1, 4, '!');      //efgh!!!!

    s8.replace(0, 4, 4, s8.c_str()[0]);     //eeee!!!!
    s8.replace(4, -1, 4, s8.c_str()[0]);    //eeeeeeee

    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "eeeeeeee") == 0);

    // container& replace(iterator first, iterator last, size_type n, value_type c)
    string s9("ABCDefgh1234");
    s9.replace(s9.begin(), s9.begin() + 4, 0, '0');     //efgh1234
    s9.replace(s9.begin() + 4, s9.end(), 4, '!');       //efgh!!!!

    s9.replace(s9.begin(), s9.begin() + 4, 4, s9.c_str()[0]);   //eeee!!!!
    s9.replace(s9.begin() + 4, s9.end(), 4, s9.c_str()[0]);     //eeeeeeee

    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "eeeeeeee") == 0);


    // inline container& replace_(iterator& first, iterator& last, iterator& first2, iterator& last2)
    string s10("abcd....1234....efgh");
    string s11("....EFGH....ABCD");

    s10.replace(s10.begin(), s10.begin() + 8, s11.begin() + 12, s11.end());     //ABCD1234....efgh
    s10.replace(s10.begin() + 8, s10.end(), s11.begin() + 4, s11.begin() + 8);  //ABCD1234EFGH

    s10.replace(s10.begin(), s10.begin() + 8, s10.begin() + 4, s10.end());  //1234EFGHEFGH
    s10.replace(s10.begin() + 4, s10.end(), s10.begin() + 8, s10.end());    //1234EFGH

    s10.replace(s10.begin(), s10.begin(), s10.begin() + 4, s10.begin() + 4);//1234EFGH

    CPPUNIT_ASSERT(::strcmp(s10.c_str(), "1234EFGH") == 0);

    // inline container& replace_(iterator& first, iterator& last, const_iterator& first2, const_iterator& last2)
    string s12("abcd....1234....efgh");
    const string s13("....EFGH....ABCD");
    const string& s12a = s12;

    s12.replace(s12.begin(), s12.begin() + 8, s13.begin() + 12, s13.end());     //ABCD1234....efgh
    s12.replace(s12.begin() + 8, s12.end(), s13.begin() + 4, s13.begin() + 8);  //ABCD1234EFGH

    s12.replace(s12.begin(), s12.begin() + 8, s12a.begin() + 4, s12a.end());  //1234EFGHEFGH
    s12.replace(s12.begin() + 4, s12.end(), s12a.begin() + 8, s12a.end());    //1234EFGH

    s12.replace(s12.begin(), s12.begin(), s12a.begin() + 4, s12a.begin() + 4);//1234EFGH

    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "1234EFGH") == 0);

    // inline container& replace_(iterator& first, iterator& last, value_type* first2, value_type* last2)
    string s14("abcd....1234....efgh");
    string s15("....EFGH....ABCD");

    s14.replace(s14.begin(), s14.begin() + 8, s15.c_str() + 12, s15.c_str() + 16);  //ABCD1234....efgh
    s14.replace(s14.begin() + 8, s14.end(), s15.c_str() + 4, s15.c_str() + 8);      //ABCD1234EFGH

    s14.replace(s14.begin(), s14.begin() + 8, s14.c_str() + 4, s14.c_str() + 12);   //1234EFGHEFGH
    s14.replace(s14.begin() + 4, s14.end(), s14.c_str() + 8, s14.c_str() + 12);     //1234EFGH

    s14.replace(s14.begin(), s14.begin(), s14.c_str() + 4, s14.c_str() + 4);        //1234EFGH

    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "1234EFGH") == 0);

    // inline container& replace_(iterator& first, iterator& last, const value_type* first2, const value_type* last2)
    string s16("abcd....1234....efgh");
    const string s17("....EFGH....ABCD");
    const string & s16a = s16;

    s16.replace(s16.begin(), s16.begin() + 8, s17.c_str() + 12, s17.c_str() + 16);  //ABCD1234....efgh
    s16.replace(s16.begin() + 8, s16.end(), s17.c_str() + 4, s17.c_str() + 8);      //ABCD1234EFGH

    s16.replace(s16.begin(), s16.begin() + 8, s16a.c_str() + 4, s16a.c_str() + 12);   //1234EFGHEFGH
    s16.replace(s16.begin() + 4, s16.end(), s16a.c_str() + 8, s16a.c_str() + 12);     //1234EFGH

    s16.replace(s16.begin(), s16.begin(), s16a.c_str() + 4, s16a.c_str() + 4);        //1234EFGH

    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "1234EFGH") == 0);

    // inline container& replace_(iterator& first, iterator& last, InputIterator& first2, InputIterator& last2, stl::forward_iterator_tag)
    string s18("ABCD....efgh....1234....");
    string s19("1234....abcd....EFGH");

    s18.replace(s18.begin(), s18.begin() + 8, s19.rbegin() + 8, s19.rbegin() + 12); //dcbaefgh....1234....
    s18.replace(s18.begin() + 12, s18.end(), s19.rbegin() + 16, s19.rend());        //dcbaefgh....4321

    s18.replace(s18.begin(), s18.begin() + 4, s18.rbegin() + 12, s18.rend());       //abcdefgh....4321
    s18.replace(s18.begin() + 8, s18.end(), s18.rbegin(), s18.rbegin() + 4);        //abcdefgh1234

    CPPUNIT_ASSERT(::strcmp(s18.c_str(), "abcdefgh1234") == 0);

    // inline container& replace_(iterator& first, iterator& last, InputIterator n, InputIterator value, stl::input_iterator_tag)
    string s20("abcd....efgh....1234....");                 //abcd....efgh....1234....
    s20.replace(s20.begin(), s20.begin() + 8, 4, 0 + 'A');  //AAAAefgh....1234....
    s20.replace(s20.begin() + 16, s20.end(), 4, 0 + 'Z');   //AAAAefgh....1234ZZZZ
    
    s20.replace(s20.begin() + 8, s20.begin() + 12, 0, 0 + '0'); //AAAAefgh1234ZZZZ

    CPPUNIT_ASSERT(::strcmp(s20.c_str(), "AAAAefgh1234ZZZZ") == 0);
}

void test_basic_string::copy()
{
    typedef stl::basic_string<char> string;
    string s1("abcdEFGH5678");
    char c1[] = "ABCDefgh1234";

    s1.copy(c1, 4, 0);      // c1="abcdefgh1234"
    s1.copy(c1 + 4, 4, 4);  // c1="abcdEFGH1234"
    s1.copy(c1 + 8, -1, 8); // c1="abcdEFGH5678"

    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "abcdEFGH5678") == 0);

    string s2("0123456789");
    s2.copy((char*)s2.c_str(), 2, 8);           //8923456789
    s2.copy((char*)s2.c_str() + 2, 4, 6);       //8967896789
    s2.copy((char*)s2.c_str() + 2, -1, 8);      //8989896789

    CPPUNIT_ASSERT(::strcmp(s2.c_str(), "8989896789") == 0);
}

void test_basic_string::swap()
{
    typedef stl::basic_string<char> string;

    string s1("....1234....abcd....efgh");
    char c1[] = "....1234....abcd....efgh";
    size_t c1sz = s1.size();
    size_t c1cap = s1.capacity();


    string s2;
    for (int i = 0; i < 22; ++i)
        s2.push_back('0' + i);
    char c2[23];
    ::strcpy(c2, s2.c_str());
    size_t c2sz = s2.size();
    size_t c2cap = s2.capacity();
    
    s1.swap(s2);

    CPPUNIT_ASSERT(::strcmp(s1.c_str(), c2) == 0 &&
                   s1.capacity() == c2cap &&
                   s1.size() == c2sz);

    CPPUNIT_ASSERT(::strcmp(s2.c_str(), c1) == 0 &&
                   s2.capacity() == c1cap &&
                   s2.size() == c1sz);
}