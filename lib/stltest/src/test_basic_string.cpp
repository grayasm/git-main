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

void test_basic_string::correctness()
{
    try
    {
        //typedef stl::basic_string<char> string;
        //string s1("0123"), s2("0123");
        //string::iterator beg1 = s1.begin();
        //string::iterator beg2 = s2.begin();

        //bool iseq = (beg1 == beg2);
        //bool eq2 = iseq;
    }
    catch (...)
    {
        printf("\n\texception");
    }
}

// Don't shoot for performance yet. Get everything correct first!
void test_basic_string::ctor()
{
    typedef stl::basic_string<char> string;

    //  basic_string()
    string s0;

    //  basic_string(const container& str)
    string s1(s0);
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "") == 0 && s1.size() == 0 && s1.empty());

    char c2[] = "a string";
    string s2(c2, c2 + 8);
    string s3(s2);
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "a string") == 0);

    //  basic_string(const container& s, size_type pos, size_type sublen = npos)
    string s4(s0, 0, 0);
    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "") == 0 && s4.size() == 0 && s4.empty());

    string s5(s3, 2, -1);
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "string") == 0);

    //  basic_string(const value_type* ptr)
    string s6("");
    CPPUNIT_ASSERT(::strcmp(s6.c_str(), "") == 0 && s6.size() == 0 && s6.empty());

    string s7("a string");
    CPPUNIT_ASSERT(::strcmp(s7.c_str(), "a string") == 0);

    
    //  basic_string(const value_type* ptr, size_type n)
    string s8("", 0);
    CPPUNIT_ASSERT(::strcmp(s8.c_str(), "") == 0);

    string s9("a string", 5);
    CPPUNIT_ASSERT(::strcmp(s9.c_str(), "a str") == 0);

    //  basic_string(size_type n, value_type c)
    string s10((size_t)0, (char)'c');
    CPPUNIT_ASSERT(::strcmp(s10.c_str(), "") == 0 && s10.size() == 0 && s10.empty());

    string s11((size_t)10, '?');
    CPPUNIT_ASSERT(::strcmp(s11.c_str(), "??????????") == 0);


    //  basic_string(iterator first, iterator last)
    string s12(s0.begin(), s0.end());//(iterator,iterator)
    CPPUNIT_ASSERT(::strcmp(s12.c_str(), "") == 0);

    string s13("the string");
    string s14(s13.begin(), s13.end());
    CPPUNIT_ASSERT(::strcmp(s14.c_str(), "the string") == 0);

    //  basic_string(const_iterator first, const_iterator last)
    const string& s0c = s0;
    string s15(s0c.begin(), s0c.end());
    CPPUNIT_ASSERT(::strcmp(s15.c_str(), "") == 0);

    const string& s13c = s13;
    string s16(s13c.begin(), s13c.end());
    CPPUNIT_ASSERT(::strcmp(s16.c_str(), "the string") == 0);

    //  basic_string(char* first, char* last)
    char c17[] = "";
    string s17(c17, c17 + 0);
    CPPUNIT_ASSERT(::strcmp(s17.c_str(), "") == 0);

    char c18[] = "0123456789";
    string s18(c18, c18 + 10);
    CPPUNIT_ASSERT(::strcmp(s18.c_str(), "0123456789") == 0);

    //  basic_string(const char* first, const char* last)
    const char c19[] = "";
    string s19(c19, c19 + 0);
    CPPUNIT_ASSERT(::strcmp(s19.c_str(), "") == 0);

    const char c20[] = "0123456789";
    string s20(c20, c20 + 10);
    CPPUNIT_ASSERT(::strcmp(s20.c_str(), "0123456789") == 0);

    //  basic_string(reverse_iterator first, reverse_iterator last)
    string s21(s0.rbegin(), s0.rend());
    CPPUNIT_ASSERT(::strcmp(s21.c_str(), "") == 0);

    string s22(s20.rbegin() + 1, s20.rend() - 1);
    CPPUNIT_ASSERT(::strcmp(s22.c_str(), "87654321") == 0);

    //  basic_string(const_reverse_iterator first, ..);
    string s23(s0c.rbegin(), s0c.rend());
    CPPUNIT_ASSERT(::strcmp(s23.c_str(), "") == 0);

    const string& s20c = s20;
    string s24(s20c.rbegin() + 1, s20c.rend() - 1);
    CPPUNIT_ASSERT(::strcmp(s24.c_str(), "87654321") == 0);

    // basic_string(InputIterator n, InputIterator value)
    char n = 0;
    char c = '\0';
    string s25(n, c);
    CPPUNIT_ASSERT(::strcmp(s25.c_str(), "") == 0);

    n = 5;
    c = '?';
    string s26(n, c);
    CPPUNIT_ASSERT(::strcmp(s26.c_str(), "?????") == 0);
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
    for (size_t i = 0; i < s1.size(); ++i)
        CPPUNIT_ASSERT(s1[i] == c1[i]);
    CPPUNIT_ASSERT(s1.size() == 8);

    s1.resize(6, c1[0]); // resize to smaller size
    for (size_t i = 0; i < s1.size(); ++i)
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
    for (size_t i = 0; i < s1.size(); ++i)
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

    stl::basic_string<char> s4("0123456789"), s5("0123456789");
    s4.insert(5, s4);
    s5.insert(s5.size(), s5);

    CPPUNIT_ASSERT(::strcmp(s4.c_str(), "01234012345678956789") == 0);
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "01234567890123456789") == 0);


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

        // try to test as many as possible combinations
    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(1, 2, s3, 8, 4);         //A1234Defgh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "A1234Defgh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(1, 4, s3, 8, 2);         //A12fgh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "A12fgh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(2, 4, s3, 4, 6);         //ABefgh12gh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABefgh12gh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(2, 4, s3, 4, 2);         //ABefgh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABefgh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 4, 2);         //ABCDef1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDef1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 4, 4);         //ABCDefgh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDefgh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 4, 6);         //ABCDefgh121234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDefgh121234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 2, 8);         //ABCDCDefgh121234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDCDefgh121234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 2, 6);         //ABCDCDefgh1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDCDefgh1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 2, 4);         //ABCDCDef1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDCDef1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 2, 2);         //ABCDCD1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDCD1234") == 0);

    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(4, 4, s3, 1, 2);         //ABCDBC1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "ABCDBC1234") == 0);
    
    s3.assign("ABCDefgh1234");          //ABCDefgh1234
    s3.replace(0, 12, s3, 0, 0);        //ABCDBC1234
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "") == 0);



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

void test_basic_string::find()
{
    typedef stl::basic_string<char> string;

    // size_type find(const container& str, size_type pos = 0) const
    string s1("ABCefgh1234");
    size_t ret = s1.find(string(""), 2);
    CPPUNIT_ASSERT(ret == 2);

    ret = s1.find(string("ABC"), 1);
    CPPUNIT_ASSERT(ret == string::npos);

    ret = s1.find(string("efgh12"), 3);
    CPPUNIT_ASSERT(ret == 3);

    ret = s1.find(string("e"), 10);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s1a("");
    ret = s1a.find(string(""));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s1b("");
    ret = s1b.find(string("333"));
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find(const value_type* ptr, size_type pos = 0) const
    string s2("ABCefgh1234");
    ret = s2.find("", 2);
    CPPUNIT_ASSERT(ret == 2);

    ret = s2.find("ABC", 1);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s2.find("efgh12", 3);
    CPPUNIT_ASSERT(ret == 3);

    ret = s2.find("e", 10);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2a("");
    ret = s2a.find("");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2b("");
    ret = s2b.find("333");
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find(const value_type* ptr, size_type pos, size_type n) const
    string s3("ABCefgh1234");
    ret = s3.find("", 2, 0);
    CPPUNIT_ASSERT(ret == 2);

    ret = s3.find("ABC", 1, 3);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s3.find("efgh12", 3, 6);
    CPPUNIT_ASSERT(ret == 3);

    ret = s3.find("e", 10, 1);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s3a("");
    ret = s3a.find("", 0, 0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s3b("");
    ret = s3b.find("333", 0, 3);
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find(value_type ch, size_type pos = 0) const
    string s4("ABCefgh1234");
    ret = s4.find('A', 1);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.find('e', 3);
    CPPUNIT_ASSERT(ret == 3);

    ret = s4.find('e', 10);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s4a("");
    ret = s4a.find((char)0);
    CPPUNIT_ASSERT(ret == (size_t)-1);
}

void test_basic_string::rfind()
{
    typedef stl::basic_string<char> string;
    size_t ret = 0;

    //size_type rfind(const container& str, size_type pos = npos) const
    string s1("");
    ret = s1.rfind(string(""));
    CPPUNIT_ASSERT(ret == 0);

    ret = s1.rfind(string(""), 0);
    CPPUNIT_ASSERT(ret == 0);

    string s2("1234....1234....");
    ret = s2.rfind(string("...."), 8);
    CPPUNIT_ASSERT(ret == 4);

    ret = s2.rfind(string("...."), 14);
    CPPUNIT_ASSERT(ret == 12);

    ret = s2.rfind(string("...."), 3);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s2.rfind(string("e"));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    //size_type rfind(const value_type* ptr, size_type pos = npos) const
    string s3("");
    ret = s3.rfind("");
    CPPUNIT_ASSERT(ret == 0);

    ret = s3.rfind("", 0);
    CPPUNIT_ASSERT(ret == 0);

    string s4("1234....1234....");
    ret = s4.rfind("....", 8);
    CPPUNIT_ASSERT(ret == 4);

    ret = s4.rfind("....", 14);
    CPPUNIT_ASSERT(ret == 12);

    ret = s4.rfind("....", 3);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.rfind("e");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    //size_type rfind(const value_type* ptr, size_type pos, size_type n) const
    char c5[] = "rap\0" "rap";
    string s5;
    s5.append(c5, c5 + 8);
    s5.append(c5, c5 + 8);

    ret = s5.rfind(c5, -1, 7);  // ignore '\0' at [3] and [11]
    CPPUNIT_ASSERT(ret == 8);

    string s6("");
    ret = s6.rfind("", -1, 0);
    CPPUNIT_ASSERT(ret == 0);

    ret = s6.rfind("", -1, 0);
    CPPUNIT_ASSERT(ret == 0);

    string s7("1234....1234....");
    ret = s7.rfind("....", 8, 4);
    CPPUNIT_ASSERT(ret == 4);

    ret = s7.rfind("....", 14, 4);
    CPPUNIT_ASSERT(ret == 12);

    ret = s7.rfind("....", 3, 4);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s7.rfind("e", -1, 1);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type rfind(value_type c, size_type pos = npos) const
    string s8("");
    ret = s8.rfind((char)0, -1);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s9("1234....1234....");
    ret = s9.rfind('.', 8);
    CPPUNIT_ASSERT(ret == 7);

    ret = s9.rfind('.', 14);
    CPPUNIT_ASSERT(ret == 14);

    ret = s9.rfind('.', 3);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s9.rfind('e', -1);
    CPPUNIT_ASSERT(ret == (size_t)-1);
}

void test_basic_string::find_first_of()
{
    typedef stl::basic_string<char> string;
    size_t ret = 0;

    // size_type find_first_of(const container& str, size_type pos = 0) const
    string s1("remove all vowels");
    while ((ret = s1.find_first_of(string("aeiou"), ret)) != (size_t)-1)
        s1[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s2("");
    ret = s2.find_first_of(string(""));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2a("");
    ret = s2a.find_first_of(string("aeiou"));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_first_of(const value_type* ptr, size_type pos = 0) const
    string s3("remove all vowels");
    ret = 0;
    while ((ret = s3.find_first_of("aeiou", ret)) != (size_t)-1)
        s3[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s4("");
    ret = s4.find_first_of("");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.find_first_of("aeiou");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_first_of(const value_type* ptr, size_type pos, size_type n) const
    string s5("remove all vowels");
    ret = 0;
    while ((ret = s5.find_first_of("aeiou", ret, 5)) != (size_t)-1)
        s5[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s6("");
    ret = s6.find_first_of("", 0, 0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s6.find_first_of("aeiou", 0, 5);
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find_first_of(value_type c, size_type pos = 0) const
    string s7("");
    ret = s7.find_first_of((char)0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s7.find_first_of('c');
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s8("remove all vowels");
    ret = s8.find_first_of('s');
    CPPUNIT_ASSERT(ret == 16);
}

void test_basic_string::find_last_of()
{
    typedef stl::basic_string<char> string;
    size_t ret = (size_t)-1;

    // size_type find_last_of(const container& str, size_type pos = 0) const
    string s1("remove all vowels");
    while ((ret = s1.find_last_of(string("aeiou"), ret)) != (size_t)-1)
        s1[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s2("");
    ret = s2.find_last_of(string(""));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2a("");
    ret = s2a.find_last_of(string("aeiou"));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_last_of(const value_type* ptr, size_type pos = 0) const
    string s3("remove all vowels");
    ret = (size_t)-1;
    while ((ret = s3.find_last_of("aeiou", ret)) != (size_t)-1)
        s3[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s4("");
    ret = s4.find_last_of("");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.find_last_of("aeiou");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_last_of(const value_type* ptr, size_type pos, size_type n) const
    string s5("remove all vowels");
    ret = (size_t)-1;
    while ((ret = s5.find_last_of("aeiou", ret, 5)) != (size_t)-1)
        s5[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "r*m*v* *ll v*w*ls") == 0);

    string s6("");
    ret = s6.find_last_of("", -1, 0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s6.find_last_of("aeiou", -1, 5);
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find_last_of(value_type c, size_type pos = 0) const
    string s7("");
    ret = s7.find_last_of((char)0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s7.find_last_of('c');
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s8("remove all vowels");
    ret = s8.find_last_of('s');
    CPPUNIT_ASSERT(ret == 16);
}


void test_basic_string::find_first_not_of()
{
    typedef stl::basic_string<char> string;
    size_t ret = 0;

    // size_type find_first_not_of(const container& str, size_type pos = 0) const
    string s1("remove all vowels");
    while ((ret = s1.find_first_not_of(string("aeiou "), ret)) != (size_t)-1)
        s1[ret++] = '*';
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "*e*o*e a** *o*e**") == 0);

    string s2("");
    ret = s2.find_first_not_of(string(""));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2a("");
    ret = s2a.find_first_not_of(string("aeiou "));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_first_not_of(const value_type* ptr, size_type pos = 0) const
    string s3("remove all vowels");
    ret = 0;
    while ((ret = s3.find_first_not_of("aeiou ", ret)) != (size_t)-1)
        s3[ret++] = '*';
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "*e*o*e a** *o*e**") == 0);

    string s4("");
    ret = s4.find_first_not_of("");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.find_first_not_of("aeiou");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_first_not_of(const value_type* ptr, size_type pos, size_type n) const
    string s5("remove all vowels");
    ret = 0;
    while ((ret = s5.find_first_not_of("aeiou ", ret, 6)) != (size_t)-1)
        s5[ret++] = '*';
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "*e*o*e a** *o*e**") == 0);

    string s6("");
    ret = s6.find_first_not_of("", 0, 0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s6.find_first_not_of("aeiou ", 0, 6);
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find_first_not_of(value_type c, size_type pos = 0) const
    string s7("");
    ret = s7.find_first_not_of((char)0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s7.find_first_not_of('c');
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s8("remove all vowels");
    ret = s8.find_first_not_of('s');
    CPPUNIT_ASSERT(ret == 0);
}

void test_basic_string::find_last_not_of()
{
    typedef stl::basic_string<char> string;
    size_t ret = (size_t)-1;

    // size_type find_last_not_of(const container& str, size_type pos = 0) const
    string s1("remove all vowels");
    while ((ret = s1.find_last_not_of(string("aeiou *"), ret)) != (size_t)-1)
        s1[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s1.c_str(), "*e*o*e a** *o*e**") == 0);

    string s2("");
    ret = s2.find_last_not_of(string(""));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s2a("");
    ret = s2a.find_last_not_of(string("aeiou *"));
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_last_not_of(const value_type* ptr, size_type pos = 0) const
    string s3("remove all vowels");
    ret = (size_t)-1;
    while ((ret = s3.find_last_not_of("aeiou *", ret)) != (size_t)-1)
        s3[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s3.c_str(), "*e*o*e a** *o*e**") == 0);

    string s4("");
    ret = s4.find_last_not_of("");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s4.find_last_not_of("aeiou *");
    CPPUNIT_ASSERT(ret == (size_t)-1);

    // size_type find_last_not_of(const value_type* ptr, size_type pos, size_type n) const
    string s5("remove all vowels");
    ret = (size_t)-1;
    while ((ret = s5.find_last_not_of("aeiou *", ret, 7)) != (size_t)-1)
        s5[ret] = '*';
    CPPUNIT_ASSERT(::strcmp(s5.c_str(), "*e*o*e a** *o*e**") == 0);

    string s6("");
    ret = s6.find_last_not_of("", -1, 0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s6.find_last_not_of("aeiou *", -1, 7);
    CPPUNIT_ASSERT(ret == (size_t)-1);


    // size_type find_last_not_of(value_type c, size_type pos = 0) const
    string s7("");
    ret = s7.find_last_not_of((char)0);
    CPPUNIT_ASSERT(ret == (size_t)-1);

    ret = s7.find_last_not_of('c');
    CPPUNIT_ASSERT(ret == (size_t)-1);

    string s8("remove all vowels");
    ret = s8.find_last_not_of('s');
    CPPUNIT_ASSERT(ret == 15);
}


void test_basic_string::substr()
{
    typedef stl::basic_string<char> string;

    string s1;
    string subs1 = s1.substr(0);
    CPPUNIT_ASSERT(::strcmp(subs1.c_str(), "") == 0);

    string s2("Returns a newly constructed string object with its value"
              "initialized to a copy of a substring of this object."
              "The substring is the portion of the object that starts"
              "at character position pos and spans len characters"
              "(or until the end of the string, whichever comes first).");

    size_t ret = s2.find("The substring");
    string subs2 = s2.substr(ret, 13);
    CPPUNIT_ASSERT(::strcmp(subs2.c_str(), "The substring") == 0);
}


void test_basic_string::compare()
{
    typedef stl::basic_string<char> string;
    int ret = 0;

    //  int compare(const container& str) const
    string s1;
    ret = s1.compare(string(""));
    CPPUNIT_ASSERT(ret == 0);

    string s2;
    string s3("some");
    CPPUNIT_ASSERT(s2.compare(s3) == -1);
    CPPUNIT_ASSERT(s3.compare(s2) == 1);

    const char c4[] = "str\0";
    string s4(c4, c4 + 4);      // with extra '\0'
    string s5("str");           // w/o extra  '\0'
    ret = s4.compare(s5);
    CPPUNIT_ASSERT(ret == 1);

    string s6("apple");
    string s7("ppl");
    ret = s6.compare(s7);
    CPPUNIT_ASSERT(ret == -1);


    // int compare(size_type pos, size_type len, const container& str) const
    string s8;
    string s9;
    ret = s8.compare(0, 0, s9);
    CPPUNIT_ASSERT(ret == 0);

    string s10("ABCDefgh1234");
    string s11("efgh1234");
    ret = s10.compare(0, -1, s11);
    CPPUNIT_ASSERT(ret == -1);

    ret = s10.compare(4, 9, s11);
    CPPUNIT_ASSERT(ret == 0);

    ret = s10.compare(4, 8, s11);
    CPPUNIT_ASSERT(ret == 0);

    ret = s10.compare(4, 7, s11);
    CPPUNIT_ASSERT(ret == -1);


    // int compare(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen) const
    string s12;
    string s13;
    ret = s12.compare(0, 0, s13, 0, 0);
    CPPUNIT_ASSERT(ret == 0);

    string s14("ABCDefgh1234");
    string s15("efgh1234");
    ret = s14.compare(0, -1, s15, 0, 8);
    CPPUNIT_ASSERT(ret == -1);

    ret = s14.compare(4, 9, s15, 0, 9);
    CPPUNIT_ASSERT(ret == 0);

    ret = s14.compare(4, 8, s15, 0, 8);
    CPPUNIT_ASSERT(ret == 0);

    ret = s14.compare(4, 7, s15, 0, 7);
    CPPUNIT_ASSERT(ret == 0);

    // int compare(const value_type* ptr) const
    string s16;
    ret = s16.compare("");
    CPPUNIT_ASSERT(ret == 0);

    s16.assign("this string");
    ret = s16.compare("t");
    CPPUNIT_ASSERT(ret == 1);

    ret = s16.compare("this string");
    CPPUNIT_ASSERT(ret == 0);

    ret = s16.compare("this string is");
    CPPUNIT_ASSERT(ret == -1);

    // int compare(size_type pos, size_type len, const value_type* ptr) const
    string s17;
    ret = s17.compare(0, 0, "");
    CPPUNIT_ASSERT(ret == 0);

    s17.assign("ass");
    ret = s17.compare(0, -1, "asm");
    CPPUNIT_ASSERT(ret == 1);
    
    // int compare(size_type pos, size_type len, const value_type* ptr, size_type n) const
    ret = s17.compare(0, -1, "ass\0", 3);
    CPPUNIT_ASSERT(ret == 0);

    s17.append(1, '\0');
    ret = s17.compare(0, -1, "ass\0", 4);
    CPPUNIT_ASSERT(ret == 0);
}

void test_basic_string::perf1()
{
    typedef stl::basic_string<char> string;

    string s0(""
        "Text messaging, or texting, is the act of composing and sending electronic messages,"
        "typically consisting of alphabetic and numeric characters, between two or more users"
        "of mobile devices, desktops / laptops, or other type of compatible computer."
        "Text messages may be sent over a cellular network, or may also be sent via an Internet connection."
        "The term originally referred to messages sent using the Short Message Service(SMS)."
        "It has grown beyond alphanumeric text to include multimedia messages(known as MMS)"
        "containing digital images, videos, and sound content, as well as ideograms known as"
        "emoji(happy faces, sad faces, and other icons)."
        "As of 2017, text messages are used by youth and adults for personal, family, business"
        "and social purposes.Governmental and non - governmental organizations use text messaging"
        "for communication between colleagues.In the 2010s, the sending of short informal messages"
        "has become an accepted part of many cultures, as happened earlier with emailing.[1]"
        "This makes texting a quick and easy way to communicate with friends, family and colleagues,"
        "including in contexts where a call would be impolite or inappropriate(e.g., calling very"
        "late at night or when one knows the other person is busy with family or work activities)."
        "Like e - mail and voicemail, and unlike calls(in which the caller hopes to speak directly"
        "with the recipient), texting does not require the caller and recipient to both be free at"
        "the same moment; this permits communication even between busy individuals.Text messages"
        "can also be used to interact with automated systems, for example, to order products or"
        "services from e - commerce websites, or to participate in online contests.Advertisers and"
        "service providers use direct text marketing to send messages to mobile users about"
        "promotions, payment due dates, and other notifications instead of using postal mail, email,"
        "or voicemail."
        "Text messaging is most often used between private mobile phone users, as a substitute"
        "for voice calls in situations where voice communication is impossible or undesirable"
        "(e.g., during a school class or a work meeting).Texting is also used to communicate"
        "very brief messages, such as informing someone that you will be late or reminding a"
        "friend or colleague about a meeting.As with e - mail, informality and brevity have become"
        "an accepted part of text messaging.Some text messages such as SMS can also be used for"
        "the remote controlling of home appliances.It is widely used in domotics systems."
        "Some amateurs have also built own systems to control(some of) their appliances via SMS.[16][17]"
        "Other methods such as group messaging, which was patented in 2012 by the GM of Andrew Ferry,"
        "Devin Peterson, Justin Cowart, Ian Ainsworth, Patrick Messinger, Jacob Delk, Jack Grande,"
        "Austin Hughes, Brendan Blake, and Brooks Brasher are used to involve more than two people"
        "into a text messaging conversation[citation needed].A Flash SMS is a type[18] of"
        "text message that appears directly on the main screen without user interaction and"
        "is not automatically stored in the inbox.It can be useful in cases such as an emergency"
        "(e.g., fire alarm) or confidentiality(e.g., one - time password).[19]"
        "Short message services are developing very rapidly throughout the world.SMS is particularly"
        "popular in Europe, Asia(excluding Japan; see below), United States, Australia and New Zealand"
        "and is also gaining influence in Africa.Popularity has grown to a sufficient extent that the"
        "term texting(used as a verb meaning the act of mobile phone users sending short messages"
        "back and forth) has entered the common lexicon.Young Asians consider SMS as the most popular"
        "mobile phone application.[20] Fifty percent of American teens send fifty text messages or more"
        "per day, making it their most frequent form of communication.[21] In China, SMS is very popular"
        "and has brought service providers significant profit(18 billion short messages were sent"
        "in 2001).[22] It is a very influential and powerful tool in the Philippines, where the average"
        "user sends 10 - 12 text messages a day.The Philippines alone sends on average over 1 billion"
        "text messages a day, [23] more than the annual average SMS volume of the countries in Europe,"
        "and even China and India.SMS is hugely popular in India, where youngsters often exchange"
        "lots of text messages, and companies provide alerts, infotainment, news, cricket scores"
        "updates, railway / airline booking, mobile billing, and banking services on SMS.");

    const char* msg1 = "\nstl::string time=";
    const char* msg2 = "\nstd::string time=";
    const size_t ONEMIL = 1000000;

    // stl::string
    {
        typedef stl::basic_string<char> string;
        time_printer tp(msg1);
        
#if 0
        // basic_string()
        // -- stl worse 0.455482 vs 0.000000 sec
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1, s2, s3, s4, s5;
        }

        // basic_string(const container& str)
        // -- stl worse 1.196504 vs 0.629155 sec
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1);
            string s3(s2);
        }

        // basic_string(const container& str, size_type pos, size_type sublen = npos)
        // -- stl is worse 1.263095 vs 0.878505
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1, i % s0.size(), -1);
            string s3(s1, 0, i % s0.size());
            string s4(s1, 0, -1);
        }

        // basic_string(const value_type* ptr)
        // ++ stl is better 1.76 vs 2.78
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str());
        }

        // basic_string(const value_type* ptr, size_type n)
        // -- stl is worse 0.88 vs 0.44
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), s0.size());
        }

        // basic_string(size_type n, value_type c)
        // -- stl is worse 0.88 vs 0.44
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.size(), 'c');
            string s2(i % s0.size(), 'c');
            string s3(127, 'c');
        }

        // basic_string(InputIterator first, InputIterator last)
        // ++ stl is better 2.72 vs 6.53
        for (size_t i = 0; i < ONEMIL / 4; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1.begin(), s1.end());
            string s3(s1.rbegin(), s1.rend());

            const string& s4 = s1;
            string s5(s4.begin(), s4.end());
            string s6(s4.rbegin(), s4.rend());

            char* cs1 = const_cast<char*>(s1.c_str());
            string s7(cs1, cs1 + s1.size());
            
            const char* cs4 = s4.c_str();
            string s8(cs4, cs4 + s4.size());
        }

        // container& operator=(value_type c)
        // -- stl is worse 0.116314 vs 0.000281
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1;
            s1 = 'c';
        }

        /*  iterator begin()
            const_iterator begin() const
            iterator end()
            const_iterator end() const
            reverse_iterator rbegin()
            const_reverse_iterator rbegin() const

            -- stl is worse 0.41 vs 0.21
        */
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            const string& cs1 = s1;

            bool ret = (s1.begin() != s1.end());
            if (ret)
                ret = (s1.rbegin() != s1.rend());
            if (ret)
                ret = (cs1.begin() != cs1.end());
            if (ret)
                ret = (cs1.rbegin() != cs1.rend());            
        }

        // void resize(size_type n, value_type c = value_type())
        // -- stl is worse 0.58 vs 0.30
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1, s2;
            s1.resize(i % s0.size(), '?');
            s2.resize(s0.size() - i % s0.size(), '?');
        }

        // void reserve(size_type n)
        // -- stl is worse 1.28 vs 0.51
        for (size_t i = 0; i < ONEMIL * 5; ++i)
        {
            string s1, s2;
            s1.reserve(i % s0.size());
            s2.reserve(s0.size() - i % s0.size());
        }

        // void clear( )
        // -- stl is worse 0.38 vs 0.21
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            s1.clear();
            s1.clear();
            s1.clear();
            s1.clear();
        }

        // const_reference operator[] ( size_type n ) const
        // reference operator[] (size_type n)
        // const_reference at ( size_type n ) const
        // reference at ( size_type n )
        // -- stl is worse 0.82 vs 0.45
        for (size_t i = 0; i < ONEMIL * 2; ++i)
        {
            string s1(s0.c_str(), s0.size());
            const string& cs1 = s1;
            size_t ii = i % (s1.size() - 1);

            if (s1[ii] == cs1[ii] &&
                s1.at(ii) == cs1.at(ii))
                continue;
        }

        // container& operator+=(const container& str)
        // container& operator+=(const value_type* ptr)
        // container& operator+=(value_type ch)
        // -- stl is worse 0.95 vs 0.92
        for (size_t i = 0; i < ONEMIL / 4; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            s2 += s1;

            string s3(127, 'c');
            s3 += s2.c_str();

            string s4(127, 'c');
            s4 += 'c';
        }

        // container& append(const container& str)
        // -- stl is worse 1.82 vs 1.50
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            string s3(127, 'c');
            string s4(127, 'c');
            string s5(127, 'c');

            s2.append(s1);
            s3.append(s1);
            s4.append(s1);
            s5.append(s1);
        }

        // container& append(const container& str, size_type subpos, size_type sublen)
        // -- stl is worse 1.79 vs 1.19
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            string s3(127, 'c');
            string s4(127, 'c');
            string s5(127, 'c');

            s2.append(s1, 0, -1);
            s3.append(s1, 0, i % s1.size());
            s4.append(s1, i % s1.size(), -1);
            s5.append(s1, i % s1.size(), i % s1.size());
        }

        // container& append(const value_type* ptr, size_type n)
        // -- stl is worse 8.78 vs 0.87!!!!!
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            string s3(127, 'c');
            string s4(127, 'c');

            s2.append(s1.c_str(), (size_t)0);
            s3.append(s1.c_str(), s1.size());
            s4.append(s1.c_str(), i % s1.size());
        }

        // container& append(const value_type* ptr)
        // -- stl is worse 8.80 vs 8.72
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            string s3(127, 'c');
            string s4(127, 'c');

            s2.append(s1.c_str());
            s3.append(s1.c_str());
            s4.append(s1.c_str());
        }

        // container& append(size_type n, value_type value)
        // -- stl is worse 2.33 vs 1.60
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str(), s0.size());
            string s3(s0.c_str(), s0.size());

            s1.append(0, 'c');
            s2.append(s0.size(), 'c');
            s3.append(i % s0.size(), 'c');
        }

        // inline container& append_(iterator& first, iterator& last)
        // -- stl is worse 3.57 vs 2.47
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str(), s0.size());
            string s3(s0.c_str(), s0.size());
            string s4(s0.c_str(), s0.size()); 
            string s5(s0.c_str(), s0.size());

            s2.append(s1.begin(), s1.end());
            s3.append(s1.begin() + (long)i % s0.size(), s1.end());
            s4.append(s1.begin(), s1.end() - (long)i % s0.size());
            s5.append(s1.end(), s1.end());
        }

        // inline container& append_(const_iterator& first, const_iterator& last)
        // -- stl is worse 1.50 vs 1.21
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            const string s1(s0.c_str(), s0.size());
            string s2(127, 'c');
            string s3(127, 'c');
            string s4(127, 'c'); 
            string s5(127, 'c');

            s2.append(s1.begin(), s1.end());
            s3.append(s1.begin() + (long)i % s0.size(), s1.end());
            s4.append(s1.begin(), s1.end() - (long)i % s0.size());
            s5.append(s1.end(), s1.end());
        }

        // inline container& append_(value_type* first, value_type* last)
        // -- stl is worse 0.92 vs 0.67
        for (size_t i = 0; i < ONEMIL / 4; ++i)
        {
            string s1(s0.c_str(), s0.c_str() + s0.size());
            string s2(s0.c_str(), s0.c_str() + s0.size());
            string s3(s0.c_str(), s0.c_str() + s0.size());
            string s4(s0.c_str(), s0.c_str() + s0.size());
            string s5(s0.c_str(), s0.c_str() + s0.size());

            s2.append(&s1[0], &s1[s1.size() - 1] + 1);
            s3.append(&s1[0] + i % s0.size(), &s1[s1.size() - 1] + 1);
            s4.append(&s1[0], &s1[s1.size() - 1] + 1 - i % s0.size());
            s5.append(&s1[s1.size() - 1] + 1, &s1[s1.size() - 1] + 1);
        }

        // inline container& append_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        // ++ stl is better 1.04 vs 1.44
        for (size_t i = 0; i < ONEMIL / 20; ++i)
        {
            const string s1(s0.c_str(), s0.size());
            string s2(s0.c_str(), s0.c_str() + s0.size());
            string s3(s0.c_str(), s0.c_str() + s0.size());
            string s4(s0.c_str(), s0.c_str() + s0.size());
            string s5(s0.c_str(), s0.c_str() + s0.size());

            s2.append(s1.rbegin(), s1.rend());
            s3.append(s1.rbegin() + (long)i % s0.size(), s1.rend());
            s4.append(s1.rbegin(), s1.rend() - (long)i % s0.size());
            s5.append(s1.rend(), s1.rend());
        }

        // inline container& append_(InputIterator n, InputIterator value, stl::input_iterator_tag)
        // -- stl is worse 1.74 vs 0.42
        for (size_t i = 0; i < ONEMIL / 10; ++i)
        {
            string s1;
            for (size_t j = 0; j < 50; ++j)
            {
                s1.append((char)0, (char)'c');
                s1.append((char)j % 127, (char)'c');
                s1.append((char)127, (char)'c'); // 127
                s1.append((char)j % 127, (char)'c');
                s1.append((char)j % 127, (char)'c');
            }
        }

        // void push_back(const value_type& x)
        // ++ stl is better 0.99 vs 4.36
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1;
            for (size_t j = 0; j < s0.size(); ++j)
                s1.push_back(s0[j]);
        }

        // container& assign(const container& str)
        // -- stl is worse 1.61 vs 1.25
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1);
            s3.assign(s1);
            s4.assign(s1);
            s5.assign(s1);
        }

        // container& assign(const container& str, size_type subpos, size_type sublen)
        // -- stl is worse 1.58 vs 0.96
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1, (size_t)0, (size_t)-1);
            s3.assign(s1, (size_t)0, (size_t)i % s1.size());
            s4.assign(s1, (size_t)i % s1.size(), (size_t)-1);
            s5.assign(s1, (size_t)i % s1.size(), (size_t)i % s1.size());
        }

        // container& assign(const value_type* ptr, size_type n)
        // -- stl is worse 1.13 vs 0.62
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1.c_str(), (size_t)0);
            s3.assign(s1.c_str(), s1.size());
            s4.assign(s1.c_str(), (size_t)i % s1.size());
        }

        // container& assign(const value_type* ptr)
        // -- stl is worse 1.70 vs 1.69
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4;
            s2.assign(s1.c_str());
            s3.assign(s1.c_str());
            s4.assign(s1.c_str());
        }


        // container& assign(size_type n, const value_type& c)
        // -- stl is worse 0.80 vs 0.43
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1, s2, s3, s4, s5;
            s1.assign(0, 'c');
            s2.assign(s0.size(), 'c');
            s3.assign(i % s0.size(), 'c');
        }

        // inline container& assign_(iterator& first, iterator& last)
        // -- stl is worse 1.39 vs 0.85
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1.begin(), s1.end());
            s3.assign(s1.begin() + (long)i % s0.size(), s1.end());
            s4.assign(s1.begin(), s1.end() - (long)i % s0.size());
            s5.assign(s1.end(), s1.end());
        }

        // inline container& assign_(const_iterator& first, const_iterator& last)
        // -- stl is worse 1.34 vs 0.79
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            const string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1.begin(), s1.end());
            s3.assign(s1.begin() + (long)i % s0.size(), s1.end());
            s4.assign(s1.begin(), s1.end() - (long)i % s0.size());
            s5.assign(s1.end(), s1.end());
        }

        // inline container& assign_(value_type* first, value_type* last)
        // -- stl is worse 1.38 vs 0.80
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;

            s2.assign(&s1[0], &s1[s1.size() - 1] + 1);
            s3.assign(&s1[0] + i % s0.size(), &s1[s1.size() - 1] + 1);
            s4.assign(&s1[0], &s1[s1.size() - 1] + 1 - i % s0.size());
            s5.assign(&s1[s1.size() - 1] + 1, &s1[s1.size() - 1] + 1);
        }


        // inline container& assign_(const value_type* first, const value_type* last)
        // -- stl is worse 1.41 vs 0.80
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;

            s2.assign((const char*)&s1[0], (const char*)(&s1[s1.size() - 1] + 1));
            s3.assign((const char*)(&s1[0] + i % s0.size()), (const char*)(&s1[s1.size() - 1] + 1));
            s4.assign((const char*)&s1[0], (const char*)(&s1[s1.size() - 1] + 1 - i % s0.size()));
            s5.assign((const char*)(&s1[s1.size() - 1] + 1), (const char*)(&s1[s1.size() - 1] + 1));
        }

        // inline container& assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        // ++ stl is better 0.94 vs 1.46
        for (size_t i = 0; i < ONEMIL / 20; ++i)
        {
            const string s1(s0.c_str(), s0.size());
            string s2, s3, s4, s5;
            s2.assign(s1.rbegin(), s1.rend());
            s3.assign(s1.rbegin() + (long)i % s0.size(), s1.rend());
            s4.assign(s1.rbegin(), s1.rend() - (long)i % s0.size());
            s5.assign(s1.rend(), s1.rend());
        }

        // inline container& assign_(InputIterator count, InputIterator value, stl::input_iterator_tag)
        // -- stl is worse 0.60 vs 0.18
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1, s2, s3;
            for (size_t j = 0; j < 5; ++j)
            {
                s1.assign((char)0, (char)'c');
                s2.assign((char)127, (char)'c');
                s3.assign((char)j % 127, (char)'c');
            }
        }

        // container& insert(size_type pos, const container& str)
        // -- stl is worse 2.17 vs 1.62
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);
            s2.insert(0, s2);
            s3.insert(s3.size() / 2, s3);
            if (s4.size())
                s4.insert(s4.size() - 1, s4);                        
        }

        // container& insert(size_type pos, const container& str, size_type subpos, size_type sublen)
        // -- stl is worse 0.72 vs 0.54
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1);
            s2.insert(0, s2, i % s2.size(), -1);
            s3.insert(s3.size() / 2, s3, i % s3.size(), s3.size());
            s4.insert(s4.size() - 1, s4, 0, -1);            
        }

        // container& insert(size_type pos, const value_type* ptr)
        // ++ stl is better 2.24 vs 5.38
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);
            s2.insert(0, s2.c_str());
            s3.insert(s3.size() / 2, s3.c_str());
            if (s4.size())
                s4.insert(s4.size(), s4.c_str());
        }

        // container& insert(size_type pos, const value_type* ptr, size_type n)
        // -- stl is worse 2.21 vs 1.74
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);
            s2.insert(0, s2.c_str(), s2.size());
            s3.insert(s3.size() / 2, s3.c_str(), s3.size());
            if (s4.size())
                s4.insert(s4.size(), s4.c_str(), s4.size());
        }

        // container& insert(size_type pos, size_type n, value_type c)
        // -- stl is worse 2.20 vs 1.62
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);

            s2.insert(0, i % s0.size(), 'c');
            s3.insert(s3.size() / 2, i % s0.size(), 'c');
            if (s4.size())
                s4.insert(s4.size(), i % s0.size(), 'c');
        }

        // void insert(iterator position, size_type n, value_type c)
        // -- stl is worse 2.18 vs 1.62
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);

            s2.insert(s2.begin(), i % s0.size(), 'c');
            s3.insert(s3.begin() + (long)s3.size() / 2, i % s0.size(), 'c');
            if (s4.size())
                s4.insert(s4.end(), i % s0.size(), 'c');
        }

        // iterator insert(iterator position, value_type c)
        // -- stl is worse 1.74 vs 0.81
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s1), s3(s1), s4(s1);

            s2.insert(s2.begin(), 'c');
            s3.insert(s3.begin() + (long)s3.size() / 2, 'c');
            if (s4.size())
                s4.insert(s4.end(), 'c');
        }

        // inline void insert_(iterator& position, iterator& first, iterator& last)
        // -- stl is worse 0.82 vs 0.62
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.insert(s2.begin() + (long)i % s2.size(), s2.begin(), s2.end());
            s3.insert(s3.begin() + (long)i % s3.size(), s3.begin() + (long)i % s0.size(), s3.end());
            s4.insert(s4.begin() + (long)i % s4.size(), s4.begin(), s4.end() - (long)i % s0.size());
            s5.insert(s5.end(), s5.end(), s5.end());
        }

        // inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
        // -- stl is worse 0.81 vs 0.60
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);
            const string& cs2 = s2;
            const string& cs3 = s3;
            const string& cs4 = s4;
            const string& cs5 = s5;

            s2.insert(s2.begin() + (long)i % s0.size(), cs2.begin(), cs2.end());
            s3.insert(s3.begin() + (long)i % s0.size(), cs3.begin() + (long)i % s0.size(), cs3.end());
            s4.insert(s4.begin(), cs4.begin(), cs4.end() - (long)i % s0.size());
            s5.insert(s5.end(), cs5.end(), cs5.end());
        }

        // inline void insert_(iterator& position, value_type* first, value_type* last)
        // -- stl is worse 0.79 vs 0.58
        for (size_t i = 0; i < ONEMIL / 5; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.insert(s2.begin() + (long)i % s2.size(), &*s2.begin(), &*s2.begin() + s2.size());
            s3.insert(s3.begin() + (long)i % s3.size(), &*s3.begin() + (long)i % s0.size(), &*s3.begin() + s3.size());
            s4.insert(s4.begin() + (long)i % s4.size(), &*s4.begin(), &*s4.begin() + s4.size() - (long)i % s0.size());
            s5.insert(s5.end(), &*s5.begin() + s5.size(), &*s5.begin() + s5.size());
        }
#endif

        // inline void insert_(iterator& position, const value_type* first, const value_type* last)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.insert(s2.begin() + (long)i % s2.size(), (const char*)&*s2.begin(), (const char*)(&*s2.begin() + s2.size()));
            s3.insert(s3.begin() + (long)i % s3.size(), (const char*)(&*s3.begin() + (long)i % s0.size()), (const char*)(&*s3.begin() + s3.size()));
            s4.insert(s4.begin() + (long)i % s4.size(), (const char*)&*s4.begin(), (const char*)(&*s4.begin() + s4.size() - (long)i % s0.size()));
            s5.insert(s5.end(), (const char*)(&*s5.begin() + s5.size()), (const char*)(&*s5.begin() + s5.size()));
        }

#if 0
        // inline void insert_(iterator& position, InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.insert(s2.begin() + (long)i % s2.size(), s2.rbegin(), s2.rend());
            s3.insert(s3.begin() + (long)i % s3.size(), s3.rbegin() + (long)i % s0.size(), s3.rend());
            s4.insert(s4.begin() + (long)i % s4.size(), s4.rbegin(), s4.rend() - (long)i % s0.size());
            s5.insert(s5.end(), s5.rend(), s5.rend());
        }

        // inline void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);
            
            s2.insert(s2.begin() + (long)i % s2.size(), (char)127, (char)'c');
            s3.insert(s3.begin() + (long)i % s3.size(), (char)i % 127, (char)'c');
            s4.insert(s4.begin() + (long)i % s4.size(), (char)127, (char)'c');
            s5.insert(s5.end(), (char)0, (char)'c');
        }

        // container& erase(size_type pos = 0, size_type len = npos)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.erase((long)i % s2.size());
            s3.erase((long)i % s3.size(), s3.size() - i % s3.size());
            s4.erase((long)i % s4.size(), s4.size() - i % s4.size());
            s5.erase(s4.size() - 1);
        }

        // iterator erase(iterator position)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.erase(s2.begin() + (long)i % s2.size());
            s3.erase(s3.begin() + (long)i % s3.size());
            s4.erase(s4.begin() + (long)i % s4.size());
            s5.erase(s5.end());
        }

        // iterator erase(iterator first, iterator last)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.erase(s2.begin() + (long)i % s2.size(), s2.end());
            s3.erase(s3.begin() + (long)i % s3.size(), s3.end());
            s4.erase(s4.begin() + (long)i % s4.size(), s4.end() - (long)i % s0.size());
            s5.erase(s5.end(), s5.end());
        }

        // container& replace(size_type pos, size_type len, const container& str)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(i % s2.size(), s2.size() - i % s2.size(), s2);
            s3.replace(i % s3.size(), s3.size() - i % s3.size(), s3);
            s4.replace(i % s4.size(), s4.size() - i % s4.size(), s4);
        }

        // container& replace(iterator first, iterator last, const container& str)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin() + (long)i % s2.size(), s2.end(), s2);
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), s3);
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), s4);
            s5.replace(s5.end(), s5.end(), s5);
        }


        // container& replace(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(i % s2.size(), s2.size() - i % s2.size(), s2, 0, s2.size());
            s3.replace(0, i % s3.size(), s3, i % s3.size(), -1);
            s4.replace(i % s4.size(), i % s4.size(), s4, 0, i % s4.size());
            s5.replace(s5.size(), s5.size(), s5, 0, i % s5.size());
        }

        // container& replace(size_type pos, size_type len, const value_type* ptr)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(i % s2.size(), s2.size() - i % s2.size(), s2.c_str());
            s3.replace(0, i % s3.size(), s3.c_str());
            s4.replace(i % s4.size(), i % s4.size(), s4.c_str());
            s5.replace(s5.size(), s5.size(), s5.c_str());
        }

        // container& replace(iterator first, iterator last, const value_type* ptr)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin() + (long)i % s2.size(), s2.end(), s2.c_str());
            s3.replace(s3.begin(), s3.begin() + (long)i % s3.size(), s3.c_str());
            s4.replace(s4.begin() + (long)i % s4.size(), s4.end(), s4.c_str());
            s5.replace(s5.begin(), s5.begin(), s5.c_str());
        }

        // container& replace(size_type pos, size_type len, const value_type* ptr, size_type n)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(i % s2.size(), s2.size() - i % s2.size(), s2.c_str(), i % s2.size());
            s3.replace(0, i % s3.size(), s3.c_str(), i % s3.size());
            s4.replace(i % s4.size(), s4.size() - i % s4.size(), s4.c_str(), s4.size());
            s5.replace(0, i % s5.size(), s5.c_str(), s5.size());
        }

        // container& replace(iterator first, iterator last, const value_type* ptr, size_type n)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin() + (long)i % s2.size(), s2.end(), s2.c_str(), s2.size() - i % s2.size());
            s3.replace(s3.begin(), s3.begin() + (long)i % s3.size(), s3.c_str(), i % s3.size());
            s4.replace(s4.begin() + (long)i % s4.size(), s4.end(), s4.c_str(), s4.size() - i % s4.size());
            s5.replace(s5.end(), s5.end(), s5.c_str(), i % s5.size());
        }

        // container& replace(size_type pos, size_type len, size_type n, value_type c)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(0, (size_t)i % s2.size(), s2.size(), 'c');
            s3.replace((size_t)i % s3.size(), s3.size() - i % s3.size(), i % s3.size(), 'c');
            s4.replace(0, (size_t)i % s4.size(), s4.size(), 'c');
            s5.replace(0, (size_t)i % s5.size(), s5.size(), 'c');
        }

        // container& replace(iterator first, iterator last, size_type n, value_type c)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), s2.size() - i % s2.size(), 'c');
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), i % s3.size(), 'c');
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), s4.size(), 'c');
            s5.replace(s5.begin() + (long)i % s5.size(), s5.end(), s5.size() - i % s5.size(), 'c');
        }

        // inline container& replace_(iterator& first, iterator& last, iterator& first2, iterator& last2)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), s2.begin() + (long)i % s2.size(), s2.end());
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), s3.begin(), s3.end());
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), s4.begin() + (long)i % s4.size(), s4.end());
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), s5.begin(), s5.end() - (long)i % s5.size());
        }

        // inline container& replace_(iterator& first, iterator& last, const_iterator& first2, const_iterator& last2)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);
            const string& cs2 = s2;
            const string& cs3 = s3;
            const string& cs4 = s4;
            const string& cs5 = s5;

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), cs2.begin() + (long)i % s2.size(), cs2.end());
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), cs3.begin(), cs3.end());
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), cs4.begin() + (long)i % s4.size(), cs4.end());
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), cs5.begin(), cs5.end() - (long)i % s5.size());
        }

        // inline container& replace_(iterator& first, iterator& last, value_type* first2, value_type* last2)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), &*s2.begin() + i % s2.size(), &*s2.begin() + s2.size());
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), &*s3.begin(), &*s3.begin() + s3.size());
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), &*s4.begin() + i % s4.size(), &*s4.begin() + s4.size());
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), &*s5.begin(), &*s5.begin() + s5.size() - i % s5.size());
        }

        // inline container& replace_(iterator& first, iterator& last, const value_type* first2, const value_type* last2)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), (const char*)(&*s2.begin() + i % s2.size()), (const char*)(&*s2.begin() + s2.size()));
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), (const char*)&*s3.begin(), (const char*)(&*s3.begin() + s3.size()));
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), (const char*)(&*s4.begin() + i % s4.size()), (const char*)(&*s4.begin() + s4.size()));
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), (const char*)&*s5.begin(), (const char*)(&*s5.begin() + s5.size() - i % s5.size()));
        }

        // inline container& replace_(iterator& first, iterator& last, InputIterator& first2, InputIterator& last2, stl::forward_iterator_tag)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), s2.rbegin() + (long)i % s2.size(), s2.rend());
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), s3.rbegin(), s3.rend());
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), s4.rbegin() + (long)i % s4.size(), s4.rend());
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), s5.rbegin(), s5.rend() - (long)i % s5.size());
        }

        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);
            const string& cs2 = s2;
            const string& cs3 = s3;
            const string& cs4 = s4;
            const string& cs5 = s5;

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), cs2.rbegin() + (long)i % s2.size(), cs2.rend());
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), cs3.rbegin(), cs3.rend());
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), cs4.rbegin() + (long)i % s4.size(), cs4.rend());
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), cs5.rbegin(), cs5.rend() - (long)i % s5.size());
        }

        // inline container& replace_(iterator& first, iterator& last, InputIterator n, InputIterator value, stl::input_iterator_tag)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.replace(s2.begin(), s2.begin() + (long)i % s2.size(), (char)127, (char)'c');
            s3.replace(s3.begin() + (long)i % s3.size(), s3.end(), (char)127, (char)'c');
            s4.replace(s4.begin(), s4.begin() + (long)i % s4.size(), (char)127, (char)'c');
            s5.replace(s5.begin() + (long)i % s2.size(), s5.end(), (char)127, (char)'c');
        }

        // size_type copy(value_type* ptr, size_type len, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            char s2[1000];
            char s3[1000];
            char s4[1000];

            s1.copy(s2, i % s1.size(), 0);
            s1.copy(s3, i % s1.size(), (s1.size() - 1) - i % (s1.size() - 1));
            s1.copy(s4, s1.size() - i % s1.size(), i % (s1.size() - 1));
        }

        // void swap(container& str)
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            string s2, s3, s4, s5;
            s2.swap(s1);
            s3.swap(s2);
            s4.swap(s3);
            s5.swap(s4);
        }

        // size_type find(const container& str, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.find(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find(const value_type* ptr, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.find(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.find(s2.c_str(), 0, s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find(value_type ch, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.find('^', 0);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type rfind(const container& str, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.rfind(s2, s2.size() - i % s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type rfind(const value_type* ptr, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.rfind(s2.c_str(), s2.size() - i % s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type rfind(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s0.c_str() + i % s0.size());

            size_t pos = s1.rfind(s2.c_str(), s2.size() - i % s2.size(), s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type rfind(value_type ch, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.rfind('^', 0);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_of(const container& str, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_first_of(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_of(const value_type* ptr, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_first_of(s2.c_str());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_of(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_first_of(s2.c_str(), 0, s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_of(value_type c, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.find_first_of('^');
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_of(const container& str, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_last_of(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_of(const value_type* ptr, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_last_of(s2.c_str());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_of(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("%^(){}[]!~@#$%?:;<>");

            size_t pos = s1.find_last_of(s2.c_str(), 0, s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_of(value_type c, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.find_last_of('^');
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_not_of(const container& str, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_first_not_of(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_not_of(const value_type* ptr, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_first_not_of(s2.c_str());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_not_of(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_first_not_of(s2.c_str(), 0, s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_first_not_of(value_type c, size_type pos = 0) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.find_first_not_of('^');
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_not_of(const container& str, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_last_not_of(s2);
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_not_of(const value_type* ptr, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_last_not_of(s2.c_str());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_not_of(const value_type* ptr, size_type pos, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");

            size_t pos = s1.find_last_not_of(s2.c_str(), 0, s2.size());
            bool found = (pos != -1);
            bool _break = found;
        }

        // size_type find_last_not_of(value_type c, size_type pos = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());

            size_t pos = s1.find_last_not_of('^');
            bool found = (pos != -1);
            bool _break = found;
        }

        // container substr(size_type pos = 0, size_type len = npos) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2 = s1.substr(i % s1.size(), i % s1.size());
            string s3 = s2.substr(i % s2.size(), i % s2.size());
            
            size_t s3sz = s3.size();
            size_t _break = s3sz;
        }

        // int compare(const container& str) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(s2);
            int _break = ret;
        }
        
        // int compare(size_type pos, size_type len, const container& str) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(0, s1.size(), s2);
            int _break = ret;
        }

        // int compare(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(0, s1.size(), s2, 0, s2.size());
            int _break = ret;
        }

        // int compare(const value_type* ptr) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(s2.c_str());
            int _break = ret;
        }

        // int compare(size_type pos, size_type len, const value_type* ptr) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(0, s1.size(), s2.c_str());
            int _break = ret;
        }

        // int compare(size_type pos, size_type len, const value_type* ptr, size_type n) const
        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), i % s0.size());
            string s2(s0.c_str(), i % s0.size());

            if (s1.size()) s1[s1.size() - 1] = 'a';
            if (s2.size()) s2[s2.size() - 1] = 'b';

            int ret = s1.compare(0, s1.size(), s2.c_str(), s2.size());
            int _break = ret;
        }
#endif
    }

    // std::string
    {
        typedef std::basic_string<char> string;
        time_printer tp(msg2);

        for (size_t i = 0; i < ONEMIL; ++i)
        {
            string s1(s0.c_str(), s0.size());
            string s2(s1), s3(s1), s4(s1), s5(s1);

            s2.insert(s2.begin() + (long)i % s2.size(), (const char*)&*s2.begin(), (const char*)(&*s2.begin() + s2.size()));
            s3.insert(s3.begin() + (long)i % s3.size(), (const char*)(&*s3.begin() + (long)i % s0.size()), (const char*)(&*s3.begin() + s3.size()));
            s4.insert(s4.begin() + (long)i % s4.size(), (const char*)&*s4.begin(), (const char*)(&*s4.begin() + s4.size() - (long)i % s0.size()));
            s5.insert(s5.end(), (const char*)(&*s5.begin() + s5.size()), (const char*)(&*s5.begin() + s5.size()));
        }
    }
}
