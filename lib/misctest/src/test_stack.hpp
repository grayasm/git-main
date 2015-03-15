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



#ifndef __test_stack_hpp__
#define __test_stack_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries




class test_stack : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_stack);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(empty);
	CPPUNIT_TEST(size);
	CPPUNIT_TEST(top);
	CPPUNIT_TEST(push);
	CPPUNIT_TEST(pop);	
	CPPUNIT_TEST(eq_op);
	CPPUNIT_TEST(neq_op);
	CPPUNIT_TEST(lt_op);
	CPPUNIT_TEST(gt_op);
	CPPUNIT_TEST(lte_op);
	CPPUNIT_TEST(gte_op);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //test begin
	void ctor();
	void dtor();
	void empty();
	void size();
	void top();
	void push();
	void pop();
	void eq_op();
	void neq_op();
	void lt_op();
	void gt_op();
	void lte_op();
	void gte_op();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	template<typename Container>
	void empty(const char* msg);
	template<typename Container>
	void size(const char* msg);
	template<typename Container>
	void top(const char* msg);
	template<typename Container>
	void push(const char* msg);
	template<typename Container>
	void pop(const char* msg);
	template<typename Container>
	void eq_op(const char* msg);
	template<typename Container>
	void neq_op(const char* msg);
	template<typename Container>
	void lt_op(const char* msg);
	template<typename Container>
	void gt_op(const char* msg);
	template<typename Container>
	void lte_op(const char* msg);
	template<typename Container>
	void gte_op(const char* msg);
    //////////////////////////////////////////////////////////////////////////
};




#endif//__test_stack_hpp__
