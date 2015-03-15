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



#ifndef __test_deque_hpp__
#define __test_deque_hpp__


//c
//c++

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//misc
#include "exception.hpp"
#include "deque.hpp"
#include "string.hpp"



class test_deque : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_deque);
    CPPUNIT_TEST( ctor );
    CPPUNIT_TEST( dtor );
    CPPUNIT_TEST( op_assign );
    CPPUNIT_TEST( begin );
    CPPUNIT_TEST( end );
    CPPUNIT_TEST( rbegin );
    CPPUNIT_TEST( rend );
    CPPUNIT_TEST( size );
    CPPUNIT_TEST( max_size );
    CPPUNIT_TEST( resize );
    CPPUNIT_TEST( empty );
    CPPUNIT_TEST( op_acc );
    CPPUNIT_TEST( at );
    CPPUNIT_TEST( front );
    CPPUNIT_TEST( back );
    CPPUNIT_TEST( assign );
    CPPUNIT_TEST( push_back );
    CPPUNIT_TEST( push_front );
    CPPUNIT_TEST( pop_back );
    CPPUNIT_TEST( pop_front );
    CPPUNIT_TEST( insert );
    CPPUNIT_TEST( erase );
    CPPUNIT_TEST( swap_ambiguity );
    CPPUNIT_TEST( clear );
	CPPUNIT_TEST( g_swap );
	CPPUNIT_TEST( op_eq );
	CPPUNIT_TEST( op_neq );
	CPPUNIT_TEST( op_lt );
	CPPUNIT_TEST( op_lte );
	CPPUNIT_TEST( op_gt );
	CPPUNIT_TEST( op_gte );
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
    void op_assign();
    void begin();
    void end();
    void rbegin();
    void rend();
    void size();
    void max_size();
    void resize();
    void empty();
    void op_acc();
    void at();
    void front();
    void back();
    void assign();
    void push_back();
    void push_front();
    void pop_back();
    void pop_front();
    void insert();
    void erase();
    void swap_ambiguity();
    void clear();
	void g_swap();
	void op_eq();
	void op_neq();
	void op_lt();
	void op_lte();
	void op_gt();
	void op_gte();


    //test end
    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
    void ctor(const char* msg);
    template<typename Container>
    void dtor(const char* msg);
    template<typename Container>
    void op_assign(const char* msg);
    template<typename Container>
    void begin(const char* msg);
    template<typename Container>
    void end(const char* msg);
    template<typename Container>
    void rbegin(const char* msg);
    template<typename Container>
    void rend(const char* msg);
    template<typename Container>
    void size(const char* msg);
    template<typename Container>
    void max_size(const char* msg);
    template<typename Container>
    void resize(const char* msg);
    template<typename Container>
    void empty(const char* msg);
    template<typename Container>
    void op_acc(const char* msg);
    template<typename Container>
    void at(const char* msg);
    template<typename Container>
    void front(const char* msg);
    template<typename Container>
    void back(const char* msg);
    template<typename Container>
    void assign(const char* msg);
    template<typename Container>
    void push_back(const char* msg);
    template<typename Container>
    void push_front(const char* msg);
    template<typename Container>
    void pop_back(const char* msg);
    template<typename Container>
    void pop_front(const char* msg);
    template<typename Container, typename AssocContainer>
    void insert(const char* msg);
    template<typename Container>
    void erase(const char* msg);
    template<typename Container>
    void swap_ambiguity(const char* msg);
    template<typename Container>
    void clear(const char* msg);
	template<typename Container>
	void g_swap(const char* msg);
	template<typename Container>
	void op_eq(const char* msg);
	template<typename Container>
	void op_neq(const char* msg);
	template<typename Container>
	void op_lt(const char* msg);
	template<typename Container>
	void op_lte(const char* msg);
	template<typename Container>
	void op_gt(const char* msg);
	template<typename Container>
	void op_gte(const char* msg);

    //////////////////////////////////////////////////////////////////////////
};//class test_deque






#endif//__test_deque_hpp__
