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




#ifndef __test_utility_hpp__
#define __test_utility_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries



class test_utility : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_utility);
    CPPUNIT_TEST(pair_ctor);
	CPPUNIT_TEST(make_pair);
	CPPUNIT_TEST(rel_ops);
	CPPUNIT_TEST(it_traits);
	CPPUNIT_TEST(if_class);
	CPPUNIT_TEST(advance);
	CPPUNIT_TEST(distance);
	CPPUNIT_TEST(back_insert_it);
	CPPUNIT_TEST(front_insert_it);
	CPPUNIT_TEST(insert_it);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;

    //test begin
    void pair_ctor();
	void make_pair();
	void rel_ops();
	void it_traits();
	void if_class();
	void advance();
	void distance();
	void back_insert_it();
	void front_insert_it();
	void insert_it();

    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container, typename Pair>
	void pair_ctor(const char* msg);
	template<typename Container, typename Pair>
	void make_pair(const char* msg);
	template<typename Container, typename Pair>
	void rel_ops(const char* msg);
	template<typename Container>
	void it_traits(const char* msg);
	template<typename T0, typename T2>
	void if_class(const char* msg);
	template<typename Container>
	void advance(const char* msg);
	template<typename Container>
	void distance(const char* msg);
	template<typename Container>
	void back_insert_it(const char* msg);
	template<typename Container>
	void front_insert_it(const char* msg);
	template<typename Container>
	void insert_it(const char* msg);

	//////////////////////////////////////////////////////////////////////////
};




#endif//__test_utility_hpp__
