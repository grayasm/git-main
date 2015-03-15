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






#ifndef __test_functional_hpp__
#define __test_functional_hpp__


//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "functional.hpp"



class test_functional : public CppUnit::TestFixture
{

    CPPUNIT_TEST_SUITE(test_functional);
	CPPUNIT_TEST(unary_function);
	CPPUNIT_TEST(binary_function);
	CPPUNIT_TEST(plus);
	CPPUNIT_TEST(minus);
	CPPUNIT_TEST(multiplies);
	CPPUNIT_TEST(devides);
	CPPUNIT_TEST(modulus);
	CPPUNIT_TEST(negate);	
	CPPUNIT_TEST(equal_to);
	CPPUNIT_TEST(not_equal_to);
	CPPUNIT_TEST(greater);
	CPPUNIT_TEST(less);
	CPPUNIT_TEST(greater_equal);
	CPPUNIT_TEST(less_equal);
	CPPUNIT_TEST(logical_and);
	CPPUNIT_TEST(logical_or);
	CPPUNIT_TEST(logical_not);
	CPPUNIT_TEST(unary_negate);
	CPPUNIT_TEST(binary_negate);
	CPPUNIT_TEST(binder1st);
	CPPUNIT_TEST(binder2nd);
	CPPUNIT_TEST(pointer_to_unary_function);
	CPPUNIT_TEST(pointer_to_binary_function);
	CPPUNIT_TEST(mem_fun_t);
	CPPUNIT_TEST(mem_fun1_t);
	CPPUNIT_TEST(const_mem_fun_t);
	CPPUNIT_TEST(const_mem_fun1_t);
	CPPUNIT_TEST(mem_fun_ref_t);
	CPPUNIT_TEST(mem_fun1_ref_t);
	CPPUNIT_TEST(const_mem_fun_ref_t);
	CPPUNIT_TEST(const_mem_fun1_ref_t);
	CPPUNIT_TEST(not1);
	CPPUNIT_TEST(not2);
	CPPUNIT_TEST(bind1st);
	CPPUNIT_TEST(bind2nd);
	CPPUNIT_TEST(ptr_fun);
	CPPUNIT_TEST(mem_fun);
	CPPUNIT_TEST(mem_fun_ref);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time; // = 1;
	static const size_t		m_container_size; // = 2000;

	//////////////////////////////////////////////////////////////////////////	
    //test begin
	//	Base classes
    void unary_function();
	void binary_function();
	//	Operator classes
	void plus();
	void minus();
	void multiplies();
	void devides();
	void modulus();
	void negate();
	//	Comparison operations
	void equal_to();
	void not_equal_to();
	void greater();
	void less();
	void greater_equal();
	void less_equal();
	//	Logical operations
	void logical_and();
	void logical_or();
	void logical_not();
	//	Instrumental types
	void unary_negate();
	void binary_negate();
	void binder1st();
	void binder2nd();
	void pointer_to_unary_function();
	void pointer_to_binary_function();
	void mem_fun_t();
	void mem_fun1_t();
	void const_mem_fun_t();
	void const_mem_fun1_t();
	void mem_fun_ref_t();
	void mem_fun1_ref_t();
	void const_mem_fun_ref_t();
	void const_mem_fun1_ref_t();
	//	Negators
	void not1();
	void not2();
	//	Parameter binders
	void bind1st();
	void bind2nd();
	//	Converters
	void ptr_fun();
	void mem_fun();
	void mem_fun_ref();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
	template<typename Container>
	void unary_function(const char* msg);
	template<typename Container>
	void binary_function(const char* msg);
	template<typename Container>
	void plus(const char* msg);
	template<typename Container>
	void minus(const char* msg);
	template<typename Container>
	void multiplies(const char* msg);
	template<typename Container>
	void devides(const char* msg);
	template<typename Container>
	void modulus(const char* msg);
	template<typename Container>
	void negate(const char* msg);
	template<typename Container>
	void equal_to(const char* msg);
	template<typename Container>
	void not_equal_to(const char* msg);
	template<typename Container>
	void greater(const char* msg);
	template<typename Container>
	void less(const char* msg);
	template<typename Container>
	void greater_equal(const char* msg);
	template<typename Container>
	void less_equal(const char* msg);
	template<typename Container>
	void logical_and(const char* msg);
	template<typename Container>
	void logical_or(const char* msg);
	template<typename Container>
	void logical_not(const char* msg);
	template<typename Container>
	void unary_negate(const char* msg);
	template<typename Container>
	void binary_negate(const char* msg);
	template<typename Container>
	void binder1st(const char* msg);
	template<typename Container>
	void binder2nd(const char* msg);
	template<typename Container>
	void pointer_to_unary_function(const char* msg);
	template<typename Container>
	void pointer_to_binary_function(const char* msg);
	template<typename Container>
	void mem_fun_t(const char* msg);
	template<typename Container>
	void mem_fun1_t(const char* msg);
	template<typename Container>
	void const_mem_fun_t(const char* msg);
	template<typename Container>
	void const_mem_fun1_t(const char* msg);
	template<typename Container>
	void mem_fun_ref_t(const char* msg);
	template<typename Container>
	void mem_fun1_ref_t(const char* msg);
	template<typename Container>
	void const_mem_fun_ref_t(const char* msg);
	template<typename Container>
	void const_mem_fun1_ref_t(const char* msg);
	template<typename Container>
	void not1(const char* msg);
	template<typename Container>
	void not2(const char* msg);
	template<typename Container>
	void bind1st(const char* msg);
	template<typename Container>
	void bind2nd(const char* msg);
	template<typename Container>
	void ptr_fun(const char* msg);
	template<typename Container>
	void mem_fun(const char* msg);
	template<typename Container>
	void mem_fun_ref(const char* msg);

    //////////////////////////////////////////////////////////////////////////
};



#endif//__test_functional_hpp__


