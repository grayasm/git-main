/*
Copyright (C) 2012 Mihai Vasilian
*/


#ifndef __test_functional_hpp__
#define __test_functional_hpp__


//c++
//....

//libraries
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "functional.hpp"



class test_functional
{
public:
	test_functional() = default;
	~test_functional() = default;
	void run();


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
	void unary_function2(const char* msg);
	template<typename Container>
	void binary_function(const char* msg);
	template<typename Container>
	void binary_function2(const char* msg);
	template<typename Container>
	void plus(const char* msg);
	template<typename Container>
	void plus2(const char* msg);
	template<typename Container>
	void minus(const char* msg);
	template<typename Container>
	void minus2(const char* msg);
	template<typename Container>
	void multiplies(const char* msg);
	template<typename Container>
	void multiplies2(const char* msg);
	template<typename Container>
	void devides(const char* msg);
	template<typename Container>
	void devides2(const char* msg);
	template<typename Container>
	void modulus(const char* msg);
	template<typename Container>
	void modulus2(const char* msg);
	template<typename Container>
	void negate(const char* msg);
	template<typename Container>
	void negate2(const char* msg);
	template<typename Container>
	void equal_to(const char* msg);
	template<typename Container>
	void equal_to2(const char* msg);
	template<typename Container>
	void not_equal_to(const char* msg);
	template<typename Container>
	void not_equal_to2(const char* msg);
	template<typename Container>
	void greater(const char* msg);
	template<typename Container>
	void greater2(const char* msg);
	template<typename Container>
	void less(const char* msg);
	template<typename Container>
	void less2(const char* msg);
	template<typename Container>
	void greater_equal(const char* msg);
	template<typename Container>
	void greater_equal2(const char* msg);
	template<typename Container>
	void less_equal(const char* msg);
	template<typename Container>
	void less_equal2(const char* msg);
	template<typename Container>
	void logical_and(const char* msg);
	template<typename Container>
	void logical_and2(const char* msg);
	template<typename Container>
	void logical_or(const char* msg);
	template<typename Container>
	void logical_or2(const char* msg);
	template<typename Container>
	void logical_not(const char* msg);
	template<typename Container>
	void logical_not2(const char* msg);
	template<typename Container>
	void unary_negate(const char* msg);
	template<typename Container>
	void unary_negate2(const char* msg);
	template<typename Container>
	void binary_negate(const char* msg);
	template<typename Container>
	void binary_negate2(const char* msg);
	template<typename Container>
	void binder1st(const char* msg);
	template<typename Container>
	void binder2nd(const char* msg);
	template<typename Container>
	void binder2nd_2(const char* msg);
	template<typename Container>
	void pointer_to_unary_function(const char* msg);
	template<typename Container>
	void pointer_to_unary_function2(const char* msg);
	template<typename Container>
	void pointer_to_binary_function(const char* msg);
	template<typename Container>
	void pointer_to_binary_function2(const char* msg);
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
	void not1_2(const char* msg);
	template<typename Container>
	void not2(const char* msg);
	template<typename Container>
	void not2_2(const char* msg);
	template<typename Container>
	void bind1st(const char* msg);
	template<typename Container>
	void bind1st_2(const char* msg);
	template<typename Container>
	void bind2nd(const char* msg);
	template<typename Container>
	void bind2nd_2(const char* msg);
	template<typename Container>
	void ptr_fun(const char* msg);
	template<typename Container>
	void ptr_fun_2(const char* msg);
	template<typename Container>
	void mem_fun(const char* msg);
	template<typename Container>
	void mem_fun_2(const char* msg);
	template<typename Container>
	void mem_fun_ref(const char* msg);
	template<typename Container>
	void mem_fun_ref_2(const char* msg);

    //////////////////////////////////////////////////////////////////////////
};


#endif//__test_functional_hpp__
