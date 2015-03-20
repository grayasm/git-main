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





//this
#include "test_functional.hpp"

//c++ ...
#include <vector>
#include <list>
#include <algorithm>
#include <functional>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries ...
#include "stream.hpp"
#include "misctest_util.hpp"
#include "vector.hpp"
#include "list.hpp"


const int test_functional::m_print_time = 1;
const size_t test_functional::m_container_size = 2000;

//###########################BEGIN TEST CLASS ####################################
void test_functional::setUp()
{
}

void test_functional::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
//////////////////////////////////////////////////////////////////////////
//test begin
void test_functional::unary_function()
{
	misc::cout << "\n\n\t*******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER \"functional.hpp\"                   *";
	misc::cout <<   "\n\t*******************************************************";
	misc::cout << "\n\n\tunary_function-----------------------------------------";
	unary_function<std::vector<int> > ("\n\tstd::vector       ");
	unary_function2<misc::vector<int> >("\n\tmisc::vector      ");
	unary_function<std::list<int> >   ("\n\tstd::list         ");
	unary_function2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::binary_function()
{
	misc::cout << "\n\n\tbinary_function----------------------------------------";
	binary_function<std::vector<int> > ("\n\tstd::vector       ");
	binary_function<misc::vector<int> >("\n\tmisc::vector      ");
	binary_function<std::list<int> >   ("\n\tstd::list         ");
	binary_function<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::plus()
{
	misc::cout << "\n\n\tplus---------------------------------------------------";
	plus<std::vector<int> > ("\n\tstd::vector       ");
	plus2<misc::vector<int> >("\n\tmisc::vector      ");
	plus<std::list<int> >   ("\n\tstd::list         ");
	plus2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::minus()
{
	misc::cout << "\n\n\tminus--------------------------------------------------";
	minus<std::vector<int> > ("\n\tstd::vector       ");
	minus2<misc::vector<int> >("\n\tmisc::vector      ");
	minus<std::list<int> >   ("\n\tstd::list         ");
	minus2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::multiplies()
{
	misc::cout << "\n\n\tmultiplies---------------------------------------------";
	multiplies<std::vector<int> > ("\n\tstd::vector       ");
	multiplies2<misc::vector<int> >("\n\tmisc::vector      ");
	multiplies<std::list<int> >   ("\n\tstd::list         ");
	multiplies2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::devides()
{
	misc::cout << "\n\n\tdevides------------------------------------------------";
	devides<std::vector<int> > ("\n\tstd::vector       ");
	devides2<misc::vector<int> >("\n\tmisc::vector      ");
	devides<std::list<int> >   ("\n\tstd::list         ");
	devides2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::modulus()
{
	misc::cout << "\n\n\tmodulus------------------------------------------------";
	modulus<std::vector<int> > ("\n\tstd::vector       ");
	modulus2<misc::vector<int> >("\n\tmisc::vector      ");
	modulus<std::list<int> >   ("\n\tstd::list         ");
	modulus2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::negate()
{
	misc::cout << "\n\n\tnegate-------------------------------------------------";
	negate<std::vector<int> > ("\n\tstd::vector       ");
	negate2<misc::vector<int> >("\n\tmisc::vector      ");
	negate<std::list<int> >   ("\n\tstd::list         ");
	negate2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::equal_to()
{
	misc::cout << "\n\n\tequal_to-----------------------------------------------";
	equal_to<std::vector<int> > ("\n\tstd::vector       ");
	equal_to<misc::vector<int> >("\n\tmisc::vector      ");
	equal_to<std::list<int> >   ("\n\tstd::list         ");
	equal_to<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::not_equal_to()
{
	misc::cout << "\n\n\tnot_equal_to-------------------------------------------";
	not_equal_to<std::vector<int> > ("\n\tstd::vector       ");
	not_equal_to<misc::vector<int> >("\n\tmisc::vector      ");
	not_equal_to<std::list<int> >   ("\n\tstd::list         ");
	not_equal_to<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::greater()
{
	misc::cout << "\n\n\tgreater------------------------------------------------";
	greater<std::vector<int> > ("\n\tstd::vector       ");
	greater2<misc::vector<int> >("\n\tmisc::vector      ");
	greater<std::list<int> >   ("\n\tstd::list         ");
	greater2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::less()
{
	misc::cout << "\n\n\tless---------------------------------------------------";
	less<std::vector<int> > ("\n\tstd::vector       ");
	less2<misc::vector<int> >("\n\tmisc::vector      ");
	less<std::list<int> >   ("\n\tstd::list         ");
	less2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::greater_equal()
{
	misc::cout << "\n\n\tgreater_equal------------------------------------------";
	greater_equal<std::vector<int> > ("\n\tstd::vector       ");
	greater_equal2<misc::vector<int> >("\n\tmisc::vector      ");
	greater_equal<std::list<int> >   ("\n\tstd::list         ");
	greater_equal2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::less_equal()
{
	misc::cout << "\n\n\tless_equal---------------------------------------------";
	less_equal<std::vector<int> > ("\n\tstd::vector       ");
	less_equal2<misc::vector<int> >("\n\tmisc::vector      ");
	less_equal<std::list<int> >   ("\n\tstd::list         ");
	less_equal2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::logical_and()
{
	misc::cout << "\n\n\tlogical_and--------------------------------------------";
	logical_and<std::vector<int> > ("\n\tstd::vector       ");
	logical_and2<misc::vector<int> >("\n\tmisc::vector      ");
	logical_and<std::list<int> >   ("\n\tstd::list         ");
	logical_and2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::logical_or()
{
	misc::cout << "\n\n\tlogical_or---------------------------------------------";
	logical_or<std::vector<int> > ("\n\tstd::vector       ");
	logical_or2<misc::vector<int> >("\n\tmisc::vector      ");
	logical_or<std::list<int> >   ("\n\tstd::list         ");
	logical_or2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::logical_not()
{
	misc::cout << "\n\n\tlogical_not--------------------------------------------";
	logical_not<std::vector<int> > ("\n\tstd::vector       ");
	logical_not2<misc::vector<int> >("\n\tmisc::vector      ");
	logical_not<std::list<int> >   ("\n\tstd::list         ");
	logical_not2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::unary_negate()
{
	misc::cout << "\n\n\tunary_negate-------------------------------------------";
	unary_negate<std::vector<int> > ("\n\tstd::vector       ");
	unary_negate2<misc::vector<int> >("\n\tmisc::vector      ");
	unary_negate<std::list<int> >   ("\n\tstd::list         ");
	unary_negate2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::binary_negate()
{
	misc::cout << "\n\n\tunary_function-----------------------------------------";
	binary_negate<std::vector<int> > ("\n\tstd::vector       ");
	binary_negate2<misc::vector<int> >("\n\tmisc::vector      ");
	binary_negate<std::list<int> >   ("\n\tstd::list         ");
	binary_negate2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::binder1st()
{
	misc::cout << "\n\n\tbinder1st----------------------------------------------";
	binder1st<std::vector<int> > ("\n\tstd::vector       ");
	binder1st<misc::vector<int> >("\n\tmisc::vector      ");
	binder1st<std::list<int> >   ("\n\tstd::list         ");
	binder1st<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::binder2nd()
{
	misc::cout << "\n\n\tbinder2nd----------------------------------------------";
	binder2nd<std::vector<int> > ("\n\tstd::vector       ");
	binder2nd_2<misc::vector<int> >("\n\tmisc::vector      ");
	binder2nd<std::list<int> >   ("\n\tstd::list         ");
	binder2nd_2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::pointer_to_unary_function()
{
	misc::cout << "\n\n\tpointer_to_unary_function------------------------------";
	pointer_to_unary_function<std::vector<double> > ("\n\tstd::vector       ");
	pointer_to_unary_function2<misc::vector<double> >("\n\tmisc::vector      ");
	pointer_to_unary_function<std::list<double> >   ("\n\tstd::list         ");
	pointer_to_unary_function2<misc::list<double> >  ("\n\tmisc::list        ");
}

void test_functional::pointer_to_binary_function()
{
	misc::cout << "\n\n\tpointer_to_binary_function-----------------------------";
	pointer_to_binary_function<std::vector<double> > ("\n\tstd::vector       ");
	pointer_to_binary_function2<misc::vector<double> >("\n\tmisc::vector      ");
	pointer_to_binary_function<std::list<double> >   ("\n\tstd::list         ");
	pointer_to_binary_function2<misc::list<double> >  ("\n\tmisc::list        ");
}

struct MemFunT
{
	MemFunT() : m_val(0) {}
	MemFunT(int val) : m_val(val){}
	int method(){ return m_val; }
	int m_val;
};

void test_functional::mem_fun_t()
{
	misc::cout << "\n\n\tmem_fun_t----------------------------------------------";
	mem_fun_t<std::vector<MemFunT> > ("\n\tstd::vector       ");
	mem_fun_t<misc::vector<MemFunT> >("\n\tmisc::vector      ");
	mem_fun_t<std::list<MemFunT> >   ("\n\tstd::list         ");
	mem_fun_t<misc::list<MemFunT> >  ("\n\tmisc::list        ");
}

struct MemFun1T
{
	MemFun1T() {};
	MemFun1T(int val) : m_val(val) {}
	int method(int val) { return val * m_val; }
	int m_val;
};

void test_functional::mem_fun1_t()
{
	misc::cout << "\n\n\tmem_fun1_t---------------------------------------------";
	mem_fun1_t<std::vector<MemFun1T> > ("\n\tstd::vector       ");
	mem_fun1_t<misc::vector<MemFun1T> >("\n\tmisc::vector      ");
	mem_fun1_t<std::list<MemFun1T> >   ("\n\tstd::list         ");
	mem_fun1_t<misc::list<MemFun1T> >  ("\n\tmisc::list        ");
}

struct ConstMemFunT
{
	ConstMemFunT() : m_val(0) {}
	ConstMemFunT(int val) : m_val(val){}
	int method() const { return m_val; }
	int m_val;
};

void test_functional::const_mem_fun_t()
{
	misc::cout << "\n\n\tconst_mem_fun_t----------------------------------------";
	const_mem_fun_t<std::vector<ConstMemFunT> > ("\n\tstd::vector       ");
	const_mem_fun_t<misc::vector<ConstMemFunT> >("\n\tmisc::vector      ");
	const_mem_fun_t<std::list<ConstMemFunT> >   ("\n\tstd::list         ");
	const_mem_fun_t<misc::list<ConstMemFunT> >  ("\n\tmisc::list        ");
}


struct ConstMemFun1T
{
	ConstMemFun1T() {};
	ConstMemFun1T(int val) : m_val(val) {}
	int method(int val) const { return val * m_val; }
	int m_val;
};

void test_functional::const_mem_fun1_t()
{
	misc::cout << "\n\n\tconst_mem_fun1_t---------------------------------------";
	const_mem_fun1_t<std::vector<ConstMemFun1T> > ("\n\tstd::vector       ");
	const_mem_fun1_t<misc::vector<ConstMemFun1T> >("\n\tmisc::vector      ");
	const_mem_fun1_t<std::list<ConstMemFun1T> >   ("\n\tstd::list         ");
	const_mem_fun1_t<misc::list<ConstMemFun1T> >  ("\n\tmisc::list        ");
}


struct MemFunRefT
{
	MemFunRefT() : m_val(0) {}
	MemFunRefT(int val) : m_val(val){}
	int method(){ return m_val; }
	int m_val;
};

void test_functional::mem_fun_ref_t()
{
	misc::cout << "\n\n\tmem_fun_ref_t------------------------------------------";
	mem_fun_ref_t<std::vector<MemFunRefT> > ("\n\tstd::vector       ");
	mem_fun_ref_t<misc::vector<MemFunRefT> >("\n\tmisc::vector      ");
	mem_fun_ref_t<std::list<MemFunRefT> >   ("\n\tstd::list         ");
	mem_fun_ref_t<misc::list<MemFunRefT> >  ("\n\tmisc::list        ");
}

struct MemFun1RefT
{
	MemFun1RefT() {};
	MemFun1RefT(int val) : m_val(val) {}
	int method(int val) { return val * m_val; }
	int m_val;
};

void test_functional::mem_fun1_ref_t()
{
	misc::cout << "\n\n\tmem_fun1_ref_t-----------------------------------------";
	mem_fun1_ref_t<std::vector<MemFun1RefT> > ("\n\tstd::vector       ");
	mem_fun1_ref_t<misc::vector<MemFun1RefT> >("\n\tmisc::vector      ");
	mem_fun1_ref_t<std::list<MemFun1RefT> >   ("\n\tstd::list         ");
	mem_fun1_ref_t<misc::list<MemFun1RefT> >  ("\n\tmisc::list        ");
}

struct ConstMemRefFunT
{
	ConstMemRefFunT() : m_val(0) {}
	ConstMemRefFunT(int val) : m_val(val){}
	int method() const { return m_val; }
	int m_val;
};


void test_functional::const_mem_fun_ref_t()
{
	misc::cout << "\n\n\tconst_mem_fun_ref_t------------------------------------";
	const_mem_fun_ref_t<std::vector<ConstMemRefFunT> > ("\n\tstd::vector       ");
	const_mem_fun_ref_t<misc::vector<ConstMemRefFunT> >("\n\tmisc::vector      ");
	const_mem_fun_ref_t<std::list<ConstMemRefFunT> >   ("\n\tstd::list         ");
	const_mem_fun_ref_t<misc::list<ConstMemRefFunT> >  ("\n\tmisc::list        ");
}

struct ConstMemFun1RefT
{
	ConstMemFun1RefT() {};
	ConstMemFun1RefT(int val) : m_val(val) {}
	int method(int val) const { return val * m_val; }
	int m_val;
};

void test_functional::const_mem_fun1_ref_t()
{
	misc::cout << "\n\n\tconst_mem_fun1_ref_t-----------------------------------";
	const_mem_fun1_ref_t<std::vector<ConstMemFun1RefT> > ("\n\tstd::vector       ");
	const_mem_fun1_ref_t<misc::vector<ConstMemFun1RefT> >("\n\tmisc::vector      ");
	const_mem_fun1_ref_t<std::list<ConstMemFun1RefT> >   ("\n\tstd::list         ");
	const_mem_fun1_ref_t<misc::list<ConstMemFun1RefT> >  ("\n\tmisc::list        ");
}

void test_functional::not1()
{
	misc::cout << "\n\n\tnot1---------------------------------------------------";
	not1<std::vector<int> > ("\n\tstd::vector       ");
	not1_2<misc::vector<int> >("\n\tmisc::vector      ");
	not1<std::list<int> >   ("\n\tstd::list         ");
	not1_2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::not2()
{
	misc::cout << "\n\n\tnot2---------------------------------------------------";
	not2<std::vector<int> > ("\n\tstd::vector       ");
	not2_2<misc::vector<int> >("\n\tmisc::vector      ");
	not2<std::list<int> >   ("\n\tstd::list         ");
	not2_2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::bind1st()
{
	misc::cout << "\n\n\tbind1st------------------------------------------------";
	bind1st<std::vector<int> > ("\n\tstd::vector       ");
	bind1st_2<misc::vector<int> >("\n\tmisc::vector      ");
	bind1st<std::list<int> >   ("\n\tstd::list         ");
	bind1st_2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::bind2nd()
{
	misc::cout << "\n\n\tbind2nd------------------------------------------------";
	bind2nd<std::vector<int> > ("\n\tstd::vector       ");
	bind2nd_2<misc::vector<int> >("\n\tmisc::vector      ");
	bind2nd<std::list<int> >   ("\n\tstd::list         ");
	bind2nd_2<misc::list<int> >  ("\n\tmisc::list        ");
}

void test_functional::ptr_fun()
{
	misc::cout << "\n\n\tptr_fun------------------------------------------------";
	ptr_fun<std::vector<double> > ("\n\tstd::vector       ");
	ptr_fun_2<misc::vector<double> >("\n\tmisc::vector      ");
	ptr_fun<std::list<double> >   ("\n\tstd::list         ");
	ptr_fun_2<misc::list<double> >  ("\n\tmisc::list        ");
}

struct MemFunS1{
	double m_val;
	MemFunS1() : m_val(0){}
	MemFunS1(double val) : m_val(val){}
	double Sqrt() const{ return ::sqrt(m_val); }
};

void test_functional::mem_fun()
{
	misc::cout << "\n\n\tmem_fun------------------------------------------------";
	mem_fun<std::vector<MemFunS1*> > ("\n\tstd::vector       ");
	mem_fun_2<misc::vector<MemFunS1*> >("\n\tmisc::vector      ");
	mem_fun<std::list<MemFunS1*> >   ("\n\tstd::list         ");
	mem_fun_2<misc::list<MemFunS1*> >  ("\n\tmisc::list        ");
}

void test_functional::mem_fun_ref()
{
	misc::cout << "\n\n\tmem_fun_ref--------------------------------------------";
	mem_fun_ref<std::vector<MemFunS1> > ("\n\tstd::vector       ");
	mem_fun_ref_2<misc::vector<MemFunS1> >("\n\tmisc::vector      ");
	mem_fun_ref<std::list<MemFunS1> >   ("\n\tstd::list         ");
	mem_fun_ref_2<misc::list<MemFunS1> >  ("\n\tmisc::list        ");
}

//test end

//////////////////////////////////////////////////////////////////////////
//GNU(-std=c++98): take definitions outside test_functional::unary_function
template<typename T>
struct IsOdd_0 : public misc::unary_function<T,bool>
{
	bool operator() (T n){ return (n%2 != 0); }
};

template<typename T>
struct IsOdd_2 : public std::unary_function<T,bool>
{
	bool operator() (T n){ return (n%2 != 0); }
};


//template version of test function
template<typename Container>
void test_functional::unary_function(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD (the entire method)
		std::for_each(v1.begin(), v1.end(), IsOdd_0<Cval>());
		std::for_each(v1.begin(), v1.end(), IsOdd_2<Cval>());
	}
}

template<typename Container>
void test_functional::unary_function2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC (entire method)
		misc::for_each(v1.begin(), v1.end(), IsOdd_0<Cval>());
		misc::for_each(v1.begin(), v1.end(), IsOdd_2<Cval>());
	}
}


//GNU(-std=c++98): take the definitions outside test_functional::binary_function
template<typename T>
struct Compare_0 : public misc::binary_function<T,T,bool>
{
	bool operator() (T a, T b) {return (a==b);}
};

template<typename T>
struct Compare_2 : public std::binary_function<T,T,bool>
{
	bool operator() (T a, T b) {return (a==b);}
};


template<typename Container>
void test_functional::binary_function(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1);


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		bool r1 = misc::equal<typename Container::iterator, typename Container::iterator, Compare_0<int> > (v1.begin(), v1.end(), v2.begin(), Compare_0<Cval>());
		bool r2 = misc::equal<typename Container::iterator, typename Container::iterator, Compare_2<int> > (v1.begin(), v1.end(), v2.begin(), Compare_2<Cval>());
		CPPUNIT_ASSERT(r1 == true && r2 == true);

		//  STD
		bool sr1 = std::equal(v1.begin(), v1.end(), v2.begin(), Compare_2<Cval>());
		bool sr2 = std::equal(v1.begin(), v1.end(), v2.begin(), Compare_0<Cval>());
		CPPUNIT_ASSERT(sr1 == true && sr2 == true);
	}
}

template<typename Container>
void test_functional::plus(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
	}
}

template<typename Container>
void test_functional::plus2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::plus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(2*i0));
	}
}

template<typename Container>
void test_functional::minus(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size, Cval(-1));

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
	}
}

template<typename Container>
void test_functional::minus2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size, Cval(-1));

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));


		//  STD
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::minus<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(0));
	}
}

template<typename Container>
void test_functional::multiplies(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
	}
}

template<typename Container>
void test_functional::multiplies2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::multiplies<Cval>());
		for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0*i0));
	}
}

template<typename Container>
void test_functional::devides(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
	}
}

template<typename Container>
void test_functional::devides2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::divides<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0/i0));
	}
}

template<typename Container>
void test_functional::modulus(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
	}
}


template<typename Container>
void test_functional::modulus2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1), v3(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::modulus<Cval>());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0%i0));
	}
}

template<typename Container>
void test_functional::negate(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), std::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), std::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
	}
}


template<typename Container>
void test_functional::negate2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::negate<Cval>());
		for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(-1*i0));
	}
}

template<typename Container>
void test_functional::equal_to(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		bool r1 = misc::equal(v1.begin(), v1.end(), v2.begin(), misc::equal_to<Cval>());
		bool r2 = misc::equal(v1.begin(), v1.end(), v2.begin(), std::equal_to<Cval>());
		CPPUNIT_ASSERT(r1 == true && r2 == true);

		//  STD
		bool sr1 = std::equal(v1.begin(), v1.end(), v2.begin(), std::equal_to<Cval>());
		bool sr2 = std::equal(v1.begin(), v1.end(), v2.begin(), misc::equal_to<Cval>());
		CPPUNIT_ASSERT(sr1 == true && sr2 == true);
	}
}

template<typename Container>
void test_functional::not_equal_to(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, i0 += 2) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, i0 += 2) *it = Cval(i0);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		bool r1 = misc::equal(v1.begin(), v1.end(), v2.begin(), misc::not_equal_to<Cval>());
		bool r2 = misc::equal(v1.begin(), v1.end(), v2.begin(), std::not_equal_to<Cval>());
		CPPUNIT_ASSERT(r1 == true && r2 == true);

		//  STD
		bool sr1 = std::equal(v1.begin(), v1.end(), v2.begin(), std::not_equal_to<Cval>());
		bool sr2 = std::equal(v1.begin(), v1.end(), v2.begin(), misc::not_equal_to<Cval>());
		CPPUNIT_ASSERT(sr1 == true && sr2 == true);
	}
}

template<typename Container>
void test_functional::greater(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::greater<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::greater<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::greater2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::greater<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::greater<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::less(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	misc::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::less<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::less<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::less2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	misc::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::less<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::less<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::greater_equal(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::greater_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::greater_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::greater_equal2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::greater_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::greater_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::less_equal(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::less_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::less_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::less_equal2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::less_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::less_equal<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::logical_and(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::logical_and<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::logical_and<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::logical_and2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::logical_and<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::logical_and<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::logical_or(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::logical_or<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::logical_or<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::logical_or2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	std::vector<bool> v3(m_container_size, false);



	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), misc::logical_or<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);


		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::logical_or<Cval>());
		for(size_t j=0; j < v3.size(); ++j)
			CPPUNIT_ASSERT(v3[j] == true);
	}
}

template<typename Container>
void test_functional::logical_not(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0%2);
	std::vector<bool> v2(m_container_size, false);


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::logical_not<Cval>());
		for(size_t j=0; j < v2.size(); ++j)
			CPPUNIT_ASSERT(v2[j] == (j%2 != 0));

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), std::logical_not<Cval>());
		for(size_t j=0; j < v2.size(); ++j)
			CPPUNIT_ASSERT(v2[j] == (j%2 != 0));
	}
}

template<typename Container>
void test_functional::logical_not2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0%2);
	std::vector<bool> v2(m_container_size, false);


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::logical_not<Cval>());
		for(size_t j=0; j < v2.size(); ++j)
			CPPUNIT_ASSERT(v2[j] == (j%2 != 0));

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::logical_not<Cval>());
		for(size_t j=0; j < v2.size(); ++j)
			CPPUNIT_ASSERT(v2[j] == (j%2 != 0));
	}
}



// GNU(-std=c++98): had to take IsOdd_class definition outside test_functional::unary_negate
template<typename T>
struct IsOdd_class
{
	typedef T argument_type;
	bool operator() (const T& x) const {return x%2 == 1;}
};

template<typename Container>
void test_functional::unary_negate(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	IsOdd_class<Cval> IsOdd_object;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		misc::unary_negate<IsOdd_class<Cval> > IsEven_m(IsOdd_object);
		i0 = std::count_if(v1.begin(), v1.end(), IsEven_m );
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		std::unary_negate<IsOdd_class<Cval> > IsEven_s(IsOdd_object);
		i0 = std::count_if(v1.begin(), v1.end(), IsEven_s);
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), IsEven_s);
		CPPUNIT_ASSERT(i0 == m_container_size/2);
		i0 = std::count_if(v1.begin(), v1.end(), IsEven_m );
		CPPUNIT_ASSERT(i0 == m_container_size/2);
	}
}

template<typename Container>
void test_functional::unary_negate2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);

	IsOdd_class<Cval> IsOdd_object;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::unary_negate<IsOdd_class<Cval> > IsEven_m(IsOdd_object);
		i0 = misc::count_if(v1.begin(), v1.end(), IsEven_m );
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		std::unary_negate<IsOdd_class<Cval> > IsEven_s(IsOdd_object);
		i0 = misc::count_if(v1.begin(), v1.end(), IsEven_s);
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		//  STD
		i0 = misc::count_if(v1.begin(), v1.end(), IsEven_s);
		CPPUNIT_ASSERT(i0 == m_container_size/2);
		i0 = misc::count_if(v1.begin(), v1.end(), IsEven_m );
		CPPUNIT_ASSERT(i0 == m_container_size/2);
	}
}

template<typename Container>
void test_functional::binary_negate(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	Cval i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = -1*(Cval)m_container_size + 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		misc::equal_to<Cval> equal_m;
		misc::binary_negate<misc::equal_to<Cval> > nonequal_m(equal_m);
		std::pair<It,It> firstmatch_m, firstmismatch_m;
		firstmatch_m = std::mismatch(v1.begin(), v1.end(), v2.begin(), nonequal_m);
		firstmismatch_m = std::mismatch(v1.begin(), v1.end(), v2.begin(), equal_m);
		CPPUNIT_ASSERT(firstmatch_m.first == v1.end());
		CPPUNIT_ASSERT(firstmismatch_m.first== v1.begin());


		//  STD
		std::equal_to<Cval> equal_s;
		std::binary_negate<std::equal_to<Cval> > nonequal_s(equal_s);
		std::pair<It,It> firstmatch_s, firstmismatch_s;
		firstmatch_s = std::mismatch(v1.begin(), v1.end(), v2.begin(), nonequal_s);
		firstmismatch_s = std::mismatch(v1.begin(), v1.end(), v2.begin(), equal_s);
		CPPUNIT_ASSERT(firstmatch_s.first== v1.end());
		CPPUNIT_ASSERT(firstmismatch_s.first == v1.begin());
	}
}

template<typename Container>
void test_functional::binary_negate2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	Cval i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = -1*(Cval)m_container_size + 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	for( it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::equal_to<Cval> equal_m;
		misc::binary_negate<misc::equal_to<Cval> > nonequal_m(equal_m);
		misc::pair<It,It> firstmatch_m, firstmismatch_m;
		firstmatch_m = misc::mismatch(v1.begin(), v1.end(), v2.begin(), nonequal_m);
		firstmismatch_m = misc::mismatch(v1.begin(), v1.end(), v2.begin(), equal_m);
		CPPUNIT_ASSERT(firstmatch_m.first == v1.end());
		CPPUNIT_ASSERT(firstmismatch_m.first== v1.begin());


		//  MISC
		std::equal_to<Cval> equal_s;
		std::binary_negate<std::equal_to<Cval> > nonequal_s(equal_s);
		misc::pair<It,It> firstmatch_s, firstmismatch_s;
		firstmatch_s = misc::mismatch(v1.begin(), v1.end(), v2.begin(), nonequal_s);
		firstmismatch_s = misc::mismatch(v1.begin(), v1.end(), v2.begin(), equal_s);
		CPPUNIT_ASSERT(firstmatch_s.first== v1.end());
		CPPUNIT_ASSERT(firstmismatch_s.first == v1.begin());
	}
}

template<typename Container>
void test_functional::binder1st(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::binder1st<misc::equal_to<Cval> > equal_to_0(misc::equal_to<Cval>(), m_container_size);
		i0 = misc::count_if(v1.begin(), v1.end(), equal_to_0);
		CPPUNIT_ASSERT(i0 == 1);

		misc::binder1st<std::equal_to<Cval> > equal_to_2(std::equal_to<Cval>(), m_container_size);
		i0 = misc::count_if(v1.begin(), v1.end(), equal_to_2);
		CPPUNIT_ASSERT(i0 == 1);

		//  STD
		std::binder1st<std::equal_to<Cval> > equal_to_3(std::equal_to<Cval>(), m_container_size);
		i0 = misc::count_if(v1.begin(), v1.end(), equal_to_3);
		CPPUNIT_ASSERT(i0 == 1);

		std::binder1st<misc::equal_to<Cval> > equal_to_4(misc::equal_to<Cval>(), m_container_size);
		i0 = misc::count_if(v1.begin(), v1.end(), equal_to_4);
		CPPUNIT_ASSERT(i0 == 1);
	}
}

template<typename Container>
void test_functional::binder2nd(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::bind2nd(misc::less<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::bind2nd(std::less<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);
	}
}

template<typename Container>
void test_functional::binder2nd_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::bind2nd(misc::less<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::bind2nd(std::less<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);
	}
}

template<typename Container>
void test_functional::pointer_to_unary_function(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		misc::pointer_to_unary_function<double,double> ptrfn(log);
		std::transform(v1.begin(), v1.end(), v2.begin(), ptrfn);
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, log(*it1)) );

		//  STD
		std::pointer_to_unary_function<double,double> ptrfn2(log);
		std::transform(v1.begin(), v1.end(), v2.begin(), ptrfn2);
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, log(*it1)) );
	}
}

template<typename Container>
void test_functional::pointer_to_unary_function2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::pointer_to_unary_function<double,double> ptrfn(log);
		misc::transform(v1.begin(), v1.end(), v2.begin(), ptrfn);
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, log(*it1)) );

		//  MISC
		std::pointer_to_unary_function<double,double> ptrfn2(log);
		misc::transform(v1.begin(), v1.end(), v2.begin(), ptrfn2);
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, log(*it1)) );
	}
}

template<typename Container>
void test_functional::pointer_to_binary_function(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		misc::pointer_to_binary_function<double,double,double> powfn(pow);
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::bind2nd(powfn,2) );
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, pow(*it1, 2.)) );

		//  STD
		misc::pointer_to_binary_function<double,double,double> powfn2(pow);
		std::transform(v1.begin(), v1.end(), v2.begin(), std::bind2nd(powfn2,2) );
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, pow(*it1, 2)) );
	}
}

template<typename Container>
void test_functional::pointer_to_binary_function2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::pointer_to_binary_function<double,double,double> powfn(pow);
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::bind2nd(powfn,2) );
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, pow(*it1, 2.)) );

		//  STD
		misc::pointer_to_binary_function<double,double,double> powfn2(pow);
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::bind2nd(powfn2,2) );
		for(It it1 = v1.begin(), it2 = v2.begin(); it1 != v1.end(); ++it1, ++it2)
			CPPUNIT_ASSERT( math::is_eq(*it2, pow(*it1, 2)) );
	}
}

template<typename Container>
void test_functional::mem_fun_t(const char* msg)
{
	//  MemFuncT { int method() { return x; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back (Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::mem_fun_t<int,Cval> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj0(&*it) == (int)i0);

		//  STD
		std::mem_fun_t<int,Cval> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj2(&*it) == (int)i0);
	}
}

template<typename Container>
void test_functional::mem_fun1_t(const char* msg)
{
	//  MemFunc1T { int method(int val) { return val*m_val; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back(Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::mem_fun1_t<int,Cval,int> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj0(&*it, i0) == square );
		}

		//  STD
		std::mem_fun1_t<int,Cval,int> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj2(&*it, i0) == square );
		}
	}
}

template<typename Container>
void test_functional::const_mem_fun_t(const char* msg)
{
	//  ConstMemFuncT { int method() const { return x; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back (Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::const_mem_fun_t<int,Cval> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj0(&*it) == (int)i0);

		//  STD
		std::const_mem_fun_t<int,Cval> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj2(&*it) == (int)i0);
	}
}

template<typename Container>
void test_functional::const_mem_fun1_t(const char* msg)
{
	//  ConstMemFunc1T { int method(int val) const { return val*m_val; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back(Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::const_mem_fun1_t<int,Cval,int> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj0(&*it, i0) == square );
		}

		//  STD
		std::const_mem_fun1_t<int,Cval,int> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj2(&*it, i0) == square );
		}
	}
}

template<typename Container>
void test_functional::mem_fun_ref_t(const char* msg)
{
	//  MemFuncRefT { int method() { return x; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back (Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::mem_fun_ref_t<int,Cval> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj0(*it) == (int)i0);

		//  STD
		std::mem_fun_ref_t<int,Cval> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj2(*it) == (int)i0);
	}
}

template<typename Container>
void test_functional::mem_fun1_ref_t(const char* msg)
{
	//  MemFunc1RefT { int method(int val) { return val*m_val; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back(Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::mem_fun1_ref_t<int,Cval,int> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj0(*it, i0) == square );
		}

		//  STD
		std::mem_fun1_ref_t<int,Cval,int> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj2(*it, i0) == square );
		}
	}
}

template<typename Container>
void test_functional::const_mem_fun_ref_t(const char* msg)
{
	//  ConstMemFuncRefT { int method() const { return x; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back (Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::const_mem_fun_ref_t<int,Cval> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj0(*it) == (int)i0);

		//  STD
		std::const_mem_fun_ref_t<int,Cval> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
			CPPUNIT_ASSERT(obj2(*it) == (int)i0);
	}
}

template<typename Container>
void test_functional::const_mem_fun1_ref_t(const char* msg)
{
	//  ConstMemFunc1RefT { int method(int val) const { return val*m_val; } }
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1;
	for(i0 = 1; i0 < m_container_size; ++i0)
		v1.push_back(Cval(i0));


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::const_mem_fun1_ref_t<int,Cval,int> obj0(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj0(*it, i0) == square );
		}

		//  STD
		std::const_mem_fun1_ref_t<int,Cval,int> obj2(&Cval::method);
		for(it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			int square = i0*i0;
			CPPUNIT_ASSERT( obj2(*it, i0) == square );
		}
	}
}


// GNU(-std=c++98): to take the definition outside test_functional::not1
template<typename T>
struct IsOdd_not1
{
	typedef T argument_type;
	bool operator() (const T& x) const {return x%2 == 1;}
};

template<typename Container>
void test_functional::not1(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::not1(IsOdd_not1<Cval>()));
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::not1(IsOdd_not1<Cval>()));
		CPPUNIT_ASSERT(i0 == m_container_size/2);
	}
}

template<typename Container>
void test_functional::not1_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::not1(IsOdd_not1<Cval>()));
		CPPUNIT_ASSERT(i0 == m_container_size/2);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::not1(IsOdd_not1<Cval>()));
		CPPUNIT_ASSERT(i0 == m_container_size/2);
	}
}

template<typename Container>
void test_functional::not2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1);



	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		std::pair<It,It> firstmatch =
			std::mismatch(v1.begin(), v1.end(), v2.begin(), std::not2(misc::equal_to<int>()));
		CPPUNIT_ASSERT(firstmatch.first == v1.begin() && firstmatch.second == v2.begin());

		//  STD
		std::pair<It,It> firstmatch2 =
			std::mismatch(v1.begin(), v1.end(), v2.begin(), std::not2(std::equal_to<int>()));
		CPPUNIT_ASSERT(firstmatch2.first == v1.begin() && firstmatch2.second == v2.begin());
	}
}

template<typename Container>
void test_functional::not2_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	Container v2(v1);



	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::pair<It,It> firstmatch =
			misc::mismatch(v1.begin(), v1.end(), v2.begin(), std::not2(misc::equal_to<int>()));
		CPPUNIT_ASSERT(firstmatch.first == v1.begin() && firstmatch.second == v2.begin());

		//  MISC
		misc::pair<It,It> firstmatch2 =
			misc::mismatch(v1.begin(), v1.end(), v2.begin(), misc::not2(std::equal_to<int>()));
		CPPUNIT_ASSERT(firstmatch2.first == v1.begin() && firstmatch2.second == v2.begin());
	}
}

template<typename Container>
void test_functional::bind1st(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::bind1st(misc::equal_to<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == 1);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), misc::bind1st(std::equal_to<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == 1);
	}
}

template<typename Container>
void test_functional::bind1st_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), std::bind1st(misc::equal_to<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == 1);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::bind1st(std::equal_to<Cval>(), m_container_size));
		CPPUNIT_ASSERT(i0 == 1);
	}
}

template<typename Container>
void test_functional::bind2nd(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), std::bind2nd(misc::less<int>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);

		//  STD
		i0 = std::count_if(v1.begin(), v1.end(), misc::bind2nd(std::less<int>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);
	}
}

template<typename Container>
void test_functional::bind2nd_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), std::bind2nd(misc::less<int>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);

		//  MISC
		i0 = misc::count_if(v1.begin(), v1.end(), misc::bind2nd(std::less<int>(), m_container_size));
		CPPUNIT_ASSERT(i0 == m_container_size);
	}
}

template<typename Container>
void test_functional::ptr_fun(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	int i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = -1; it != v1.end(); ++it, --i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), std::ptr_fun<Cval,Cval>(fabs));
		for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::ptr_fun<Cval,Cval>(fabs));
		for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
	}
}

template<typename Container>
void test_functional::ptr_fun_2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	int i0;

	Container v1(m_container_size), v2(m_container_size);
	for( it = v1.begin(), i0 = -1; it != v1.end(); ++it, --i0) *it = Cval(i0);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::ptr_fun<Cval,Cval>(fabs));
		for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::ptr_fun<Cval,Cval>(fabs));
		for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
	}
}

template<typename Container>
void test_functional::mem_fun(const char* msg)
{
	// Container::value_type -> MemFunS1* class
	typedef typename Container::value_type	Cval;	//MemFunS1*
	typedef typename Container::iterator It;

	It it;
	size_t i0, i1;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = new MemFunS1(i0);
	misc::vector<double> v2(m_container_size); // result


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), std::mem_fun<double,MemFunS1>(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it)->m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::mem_fun<double,MemFunS1>(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it)->m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}
	}
}

template<typename Container>
void test_functional::mem_fun_2(const char* msg)
{
	// Container::value_type -> MemFunS1* class
	typedef typename Container::value_type	Cval;	//MemFunS1*
	typedef typename Container::iterator It;

	It it;
	size_t i0, i1;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0) *it = new MemFunS1(i0);
	misc::vector<double> v2(m_container_size); // result


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::mem_fun<double,MemFunS1>(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it)->m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::mem_fun<double,MemFunS1>(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it)->m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}
	}
}

template<typename Container>
void test_functional::mem_fun_ref(const char* msg)
{
	typedef typename Container::value_type Cval;    // MemFunRefS1
	typedef typename Container::iterator It;

	It it;
	size_t i0, i1;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	misc::vector<double> v2(m_container_size);// store the results of Cval::Sqrt(double)


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), std::mem_fun_ref(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it).m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}

		//  STD
		std::transform(v1.begin(), v1.end(), v2.begin(), misc::mem_fun_ref(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it).m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}
	}
}

template<typename Container>
void test_functional::mem_fun_ref_2(const char* msg)
{
	typedef typename Container::value_type Cval;    // MemFunRefS1
	typedef typename Container::iterator It;

	It it;
	size_t i0, i1;

	Container v1(m_container_size);
	for( it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0) *it = Cval(i0);
	misc::vector<double> v2(m_container_size);// store the results of Cval::Sqrt(double)


	//  TEST
	{
		time_printer tp(msg, m_print_time);
		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), std::mem_fun_ref(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it).m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}

		//  MISC
		misc::transform(v1.begin(), v1.end(), v2.begin(), misc::mem_fun_ref(&MemFunS1::Sqrt));
		for(it = v1.begin(), i0 = 0, i1 = 1; it != v1.end(); ++it, ++i0, ++i1)
		{
			double v1val = sqrt((*it).m_val);
			double v2val = v2[i0];
			CPPUNIT_ASSERT( math::is_eq(v1val, v2val) );
		}
	}
}

//////////////////////////////////////////////////////////////////////////
