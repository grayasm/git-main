/*
  Copyright (C) 2012 Mihai Vasilian

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



#ifndef __test_podstring_hpp__
#define __test_podstring_hpp__


//CppUnit
#include <cppunit/extensions/HelperMacros.h>






class test_generic_string : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_generic_string);
    CPPUNIT_TEST(ctor);
    CPPUNIT_TEST(assignament_op);
    CPPUNIT_TEST(begin);
    CPPUNIT_TEST(end);
    CPPUNIT_TEST(rbegin);
    CPPUNIT_TEST(rend);
    CPPUNIT_TEST(size);
    CPPUNIT_TEST(length);
    CPPUNIT_TEST(max_size);
    CPPUNIT_TEST(resize);
    CPPUNIT_TEST(capacity);
    CPPUNIT_TEST(reserve);
    CPPUNIT_TEST(clear);
    CPPUNIT_TEST(empty);
    CPPUNIT_TEST(operator_access_element);
    CPPUNIT_TEST(at);
    CPPUNIT_TEST(operator_plus_equal);
    CPPUNIT_TEST(append);
    CPPUNIT_TEST(push_back);
    CPPUNIT_TEST(assign);
    CPPUNIT_TEST(insert);
    CPPUNIT_TEST(erase);
    CPPUNIT_TEST(replace);
    CPPUNIT_TEST(swap);
    CPPUNIT_TEST(c_str);
    CPPUNIT_TEST(data);
    CPPUNIT_TEST(get_allocator);
    CPPUNIT_TEST(copy);
    CPPUNIT_TEST(find);
    CPPUNIT_TEST(rfind);
    CPPUNIT_TEST(find_first_of);
    CPPUNIT_TEST(find_last_of);
    CPPUNIT_TEST(find_first_not_of);
    CPPUNIT_TEST(find_last_not_of);
    CPPUNIT_TEST(substr);
    CPPUNIT_TEST(compare);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //////////////////////////////////////////////////////////////////////////
    //test begin
    //Member functions
    void ctor();
    void assignament_op();
    //Iterators
    void begin();
    void end();
    void rbegin();
    void rend();
    //Capacity
    void size();
    void length();
    void max_size();
    void resize();
    void capacity();
    void reserve();
    void clear();
    void empty();
    //Element access
    void operator_access_element();
    void at();
    //Modifiers
    void operator_plus_equal();
    void append();
    void push_back();
    void assign();
    void insert();
    void erase();
    void replace();
    void swap();
    //String operations
    void c_str();
    void data();
    void get_allocator();
    void copy();
    void find();
    void rfind();
    void find_first_of();
    void find_last_of();
    void find_first_not_of();
    void find_last_not_of();
    void substr();
    void compare();
    //test end    
    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    //Member functions
    template<typename Container>
    void ctor(const char* msg);
    template<typename Container>
    void assignament_op(const char* msg);
    //Iterators
    template<typename Container>
    void begin(const char* msg);
    template<typename Container>
    void end(const char* msg);
    template<typename Container>
    void rbegin(const char* msg);
    template<typename Container>
    void rend(const char* msg);
    //Capacity
    template<typename Container>
    void size(const char* msg);
    template<typename Container>
    void length(const char* msg);
    template<typename Container>
    void max_size(const char* msg);
    template<typename Container>
    void resize(const char* msg);
    template<typename Container>
    void capacity(const char* msg);
    template<typename Container>
    void reserve(const char* msg);
    template<typename Container>
    void clear(const char* msg);
    template<typename Container>
    void empty(const char* msg);
    //Element access
    template<typename Container>
    void operator_access_element(const char* msg);
    template<typename Container>
    void at(const char* msg);
    //Modifiers
    template<typename Container>
    void operator_plus_equal(const char* msg);
    template<typename Container>
    void append(const char* msg);
    template<typename Container>
    void push_back(const char* msg);
    template<typename Container>
    void assign(const char* msg);
    template<typename Container>
    void insert(const char* msg);
    template<typename Container>
    void erase(const char* msg);
    template<typename Container>
    void replace(const char* msg);
    template<typename Container>
    void swap(const char* msg);
    //String operations
    template<typename Container>
    void c_str(const char* msg);
    template<typename Container>
    void data(const char* msg);
    template<typename Container>
    void get_allocator(const char* msg);
    template<typename Container>
    void copy(const char* msg);
    template<typename Container>
    void find(const char* msg);
    template<typename Container>
    void rfind(const char* msg);
    template<typename Container>
    void find_first_of(const char* msg);
    template<typename Container>
    void find_last_of(const char* msg);
    template<typename Container>
    void find_first_not_of(const char* msg);
    template<typename Container>
    void find_last_not_of(const char* msg);
    template<typename Container>
    void substr(const char* msg);
    template<typename Container>
    void compare(const char* msg);
    //end of template version of test function
    //////////////////////////////////////////////////////////////////////////


};




#endif//__test_podstring_hpp__

