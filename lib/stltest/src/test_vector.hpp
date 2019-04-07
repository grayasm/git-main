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



#ifndef __test_podvector_hpp__
#define __test_podvector_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>



class test_vector : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_vector);	
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(copy_op);
	CPPUNIT_TEST(assign);
	CPPUNIT_TEST(begin);
	CPPUNIT_TEST(end);
	CPPUNIT_TEST(rbegin);
	CPPUNIT_TEST(rend);
	CPPUNIT_TEST(size);	
	CPPUNIT_TEST(resize);
	CPPUNIT_TEST(empty);
	CPPUNIT_TEST(reserve);
	CPPUNIT_TEST(access_element);
	CPPUNIT_TEST(at);
	CPPUNIT_TEST(front);
	CPPUNIT_TEST(back);
	CPPUNIT_TEST(push_back);
	CPPUNIT_TEST(pop_back);
	CPPUNIT_TEST(insert);
	CPPUNIT_TEST(erase);
	CPPUNIT_TEST(swap);
	CPPUNIT_TEST(clear);
	CPPUNIT_TEST(eq_op);
	CPPUNIT_TEST(less_op);
	CPPUNIT_TEST(noteq_op);
	CPPUNIT_TEST(gt_op);
	CPPUNIT_TEST(qteq_op);
	CPPUNIT_TEST(lteq_op);
	CPPUNIT_TEST(swap_op);	
    CPPUNIT_TEST_SUITE_END();


public:
	void setUp();
	void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;


    //begin test suite
    void ctor();
    void copy_op();
	void assign();
	void begin();
	void end();
	void rbegin();
	void rend();
	void size();
	//max_size() not compatible with std::
    void resize();
	//capacity() not compatible with std::
	void empty();
    void reserve();
    void access_element();
	void at();
	void front();
	void back();
    void push_back();
    void pop_back();
    void insert();
	void erase();
	void swap();
	void clear();
	// global operator
	void eq_op();
	void less_op();
	void noteq_op();
	void gt_op();
	void qteq_op();
	void lteq_op();
	void swap_op();
    //end test suite
	
	// template section
	template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void copy_op(const char* msg);
	template<typename Container>
	void assign(const char* msg);
	template<typename Container>
	void begin(const char* msg);//new
	template<typename Container>
	void end(const char* msg);//new
	template<typename Container>
	void rbegin(const char* msg);//new
	template<typename Container>
	void rend(const char* msg);//new
	template<typename Container>
	void size(const char* msg);//new
	//max_size() not compatible with std::
	template<typename Container>
	void resize(const char* msg);
	//capacity() not compatible with std::
	template<typename Container>
	void empty(const char* msg);//new
	template<typename Container>
	void reserve(const char* msg);
	template<typename Container>
	void access_element(const char* msg);
	template<typename Container>
	void at(const char* msg);//new
	template<typename Container>
	void front(const char* msg);//new
	template<typename Container>
	void back(const char* msg);//new
	template<typename Container>
	void push_back(const char* msg);
	template<typename Container>
	void pop_back(const char* msg);
	template<typename Container>
	void insert(const char* msg);
	template<typename Container>
	void erase(const char* msg);//new
	template<typename Container>
	void swap(const char* msg);//new
	template<typename Container>
	void clear(const char* msg);//new
	// global operator
	template<typename Container>
	void eq_op(const char* msg);//new
	template<typename Container>
	void less_op(const char* msg);//new
	template<typename Container>
	void noteq_op(const char* msg);//new
	template<typename Container>
	void gt_op(const char* msg);//new
	template<typename Container>
	void gteq_op(const char* msg);//new
	template<typename Container>
	void lteq_op(const char* msg);//new
	template<typename Container>
	void swap_op(const char* msg);//new

	// end template section	
};



#endif//__test_podvector_hpp__
