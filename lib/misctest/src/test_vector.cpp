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


//this
#include "test_vector.hpp"



//c/c++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iomanip>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "vector.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"
#include "math.hpp"
#include "list.hpp"




//////////////////////////////////////////////////////////////////////////
// begin test class
void test_vector::setUp()
{
}

void test_vector::tearDown()
{
}

//////////////////////////////////////////////////////////////////////////
// different data types
class nonpod_v2
{
public:
	nonpod_v2():m_p(0){}
	nonpod_v2(const nonpod_v2& np){ *this = np; }
	nonpod_v2(int p):m_p(p){}
	~nonpod_v2(){}
	nonpod_v2& operator=(const nonpod_v2& np)
	{
		if(this!=&np) m_p = np.m_p;
		return *this;
	}
private:
	int m_p;
};

// data type not detected as POD
struct non_pod_v2
{
	int val;
	float fval;
	unsigned char ucval;
	void (*f)(int argc, ...);
};
void non_pod_f_v2(int, ...){}


struct s_data_v2
{
	char* empty;
	double darray[10];
	float* farray;
};


// begin test suite
void test_vector::ctor()
{
	stl::cout << "\n\n\t*******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER: vector.hpp                          *";
	stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tctor---------------------------------------------------";
	ctor<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	ctor<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	ctor<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	ctor<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::copy_op()
{
	stl::cout << "\n\n\tcopy_op------------------------------------------------";
	copy_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	copy_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	copy_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	copy_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::assign()
{
	stl::cout << "\n\n\tassign-------------------------------------------------";
	assign<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	assign<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	assign<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	assign<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::begin()
{
	stl::cout << "\n\n\tbegin--------------------------------------------------";
	begin<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	begin<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	begin<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	begin<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::end()
{
	stl::cout << "\n\n\tend----------------------------------------------------";
	end<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	end<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	end<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	end<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::rbegin()
{
	stl::cout << "\n\n\trbegin-------------------------------------------------";
	rbegin<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	rbegin<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	rbegin<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	rbegin<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::rend()
{
	stl::cout << "\n\n\trend---------------------------------------------------";
	rend<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	rend<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	rend<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	rend<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::size()
{
	stl::cout << "\n\n\tsize---------------------------------------------------";
	size<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	size<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	size<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	size<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::resize()
{
	stl::cout << "\n\n\tresize-------------------------------------------------";
	resize<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	resize<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	resize<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	resize<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::empty()
{
	stl::cout << "\n\n\tempty--------------------------------------------------";
	empty<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	empty<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	empty<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	empty<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::reserve()
{
	stl::cout << "\n\n\treserve------------------------------------------------";
	reserve<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	reserve<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	reserve<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	reserve<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::access_element()
{
	stl::cout << "\n\n\toperator[](size_type)----------------------------------";
	access_element<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	access_element<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	access_element<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	access_element<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::at()
{
	stl::cout << "\n\n\tat-----------------------------------------------------";
	at<stl::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	at<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	at<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	at<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::front()
{
	stl::cout << "\n\n\tfront--------------------------------------------------";
	front<stl::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	front<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	front<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	front<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::back()
{
	stl::cout << "\n\n\tback---------------------------------------------------";
	back<stl::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	back<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	back<stl::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	back<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::push_back()
{
	stl::cout << "\n\n\tpush_back----------------------------------------------";
	push_back<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	push_back<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	push_back<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	push_back<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::pop_back()
{
	stl::cout << "\n\n\tpop_back-----------------------------------------------";
	pop_back<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	pop_back<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	pop_back<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	pop_back<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::insert()
{
	stl::cout << "\n\n\tinsert-------------------------------------------------";
	insert<stl::vector<s_data_v2> >                                                                                                           ("\n\tmisc::vector<s_data_v2>            ");
	insert<stl::vector<s_data_v2, misc::allocator<s_data_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<s_data_v2,POD>        ");
	insert<stl::vector<s_data_v2, misc::allocator<s_data_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<s_data_v2,POD|DBG_IT> ");
	insert<std::vector<s_data_v2> >                                                                                                            ("\n\tstd::vector<s_data_v2>             ");
}

void test_vector::erase()
{
	stl::cout << "\n\n\terase--------------------------------------------------";
	erase<stl::vector<non_pod_v2> >                                                                                                            ("\n\tmisc::vector<non_pod_v2>            ");
	erase<stl::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<non_pod_v2,POD>        ");
	erase<stl::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<non_pod_v2,POD|DBG_IT> ");
	erase<std::vector<non_pod_v2> >                                                                                                             ("\n\tstd::vector<non_pod_v2>             ");
}

void test_vector::swap()
{
	stl::cout << "\n\n\tswap---------------------------------------------------";
	swap<stl::vector<non_pod_v2> >                                                                                                            ("\n\tmisc::vector<non_pod_v2>            ");
	swap<stl::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<non_pod_v2,POD>        ");
	swap<stl::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<non_pod_v2,POD|DBG_IT> ");
	swap<std::vector<non_pod_v2> >                                                                                                             ("\n\tstd::vector<non_pod_v2>             ");
}

void test_vector::clear()
{
	stl::cout << "\n\n\tclear--------------------------------------------------";
	clear<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	clear<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	clear<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	clear<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::eq_op()
{
	stl::cout << "\n\n\teq_op--------------------------------------------------";
	eq_op<std::vector<double> >																											("\n\tstd::vector<double>             ");
	eq_op<stl::vector<double> >																										("\n\tmisc::vector<double>            ");
	eq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >												("\n\tmisc::vector<double,POD>        ");
	eq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	eq_op<std::vector<double> >																											("\n\tstd::vector<double>             ");
}

void test_vector::less_op()
{
	stl::cout << "\n\n\tless_op------------------------------------------------";
	less_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	less_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	less_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	less_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::noteq_op()
{
	stl::cout << "\n\n\tnoteq_op-----------------------------------------------";
	noteq_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	noteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	noteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	noteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::gt_op()
{
	stl::cout << "\n\n\tgt_op--------------------------------------------------";
	gt_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	gt_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	gt_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	gt_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::qteq_op()
{
	stl::cout << "\n\n\tgteq_op------------------------------------------------";
	gteq_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	gteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	gteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	gteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::lteq_op()
{
	stl::cout << "\n\n\tlteq_op------------------------------------------------";
	lteq_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	lteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	lteq_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	lteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::swap_op()
{
	stl::cout << "\n\n\tswap_op------------------------------------------------";
	swap_op<stl::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	swap_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	swap_op<stl::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	swap_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

//////////////////////////////////////////////////////////////////////////
// template section
template<typename Container>
void test_vector::ctor(const char* msg)
{
	typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

	Cval val = 9.34e120;
	//  TEST
	{
		time_printer tp(msg, m_print_time);

		Container vec0(m_container_size, val);
		Container vec2(vec0.begin(), vec0.end());
		Container vec3(vec2);

		CPPUNIT_ASSERT(
			vec0.size() == m_container_size &&
			vec2.size() == m_container_size &&
			vec3.size() == m_container_size
			);

		for(size_t j=0; j < m_container_size; ++j)
		{
			CPPUNIT_ASSERT(
				math::is_eq(vec0[j], val) &&
				math::is_eq(vec2[j], val) &&
				math::is_eq(vec3[j], val)
				);
		}
	}
}

template<typename Container>
void test_vector::copy_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = -22./7.;
	Container vec0(m_container_size, val);
	Container vec2;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		vec2 = vec0;

		CPPUNIT_ASSERT(
			vec0.size() == m_container_size &&
			vec2.size() == m_container_size
			);

		for(size_t j = 0; j < m_container_size; ++j)
		{
			CPPUNIT_ASSERT(
				math::is_eq(vec0[j], val) &&
				math::is_eq(vec2[j], val)
				);
		}
	}
}

template<typename Container>
void test_vector::assign(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval val0 = -22./7.;
	Cval val3 = -1*val0;
	Container vec0(m_container_size, val0);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		Container vec2;
		vec2.assign(vec0.begin(), vec0.end());

		Container vec3;
		vec3.assign(m_container_size, val3);
	}
}

template<typename Container>
void test_vector::begin(const char* msg)
{
	typedef typename Container::value_type Cval;	
	typedef typename Container::iterator   It;

	typedef misc::list<It> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.begin() + i);
		} // for
	}
}

template<typename Container>
void test_vector::end(const char* msg)
{
	typedef typename Container::value_type Cval;	
	typedef typename Container::iterator   It;

	typedef misc::list<It> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.end() - i);
		} // for
	}
}

template<typename Container>
void test_vector::rbegin(const char* msg)
{
	typedef typename Container::value_type Cval;	
	typedef typename Container::reverse_iterator RIt;

	typedef misc::list<RIt> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.rbegin() + i);
		} // for
	}
}

template<typename Container>
void test_vector::rend(const char* msg)
{
	typedef typename Container::value_type Cval;	
	typedef typename Container::reverse_iterator RIt;

	typedef misc::list<RIt> chitlist;
	chitlist itlist0;
	Container array0;
	array0.resize(m_container_size);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i<m_container_size; ++i)
		{
			itlist0.push_back(array0.rend() - i);
		} // for
	}
}

template<typename Container>
void test_vector::size(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = -22./7.;
	Container vec0(m_container_size, val);
	Container vec2(m_container_size, -1 * val);


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(
			vec0.size() == vec2.size() &&
			vec0.size() == m_container_size &&
			vec2.size() == m_container_size
			);
	}
}

template<typename Container>
void test_vector::resize(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = -22./7.;
	Container vec0(1, val);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		vec0.resize(m_container_size, val);

		CPPUNIT_ASSERT(vec0.size() == m_container_size);
		for(size_t j = 0; j < m_container_size; ++j)
		{
			CPPUNIT_ASSERT(math::is_eq(vec0[j], val));
		}
	}
}

template<typename Container>
void test_vector::empty(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = 9.34e120;
	Container vec0(m_container_size, val);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		vec0.erase(vec0.begin(), vec0.end());
		CPPUNIT_ASSERT(vec0.empty());
	}
}

template<typename Container>
void test_vector::reserve(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = -22./7.;
	Container vec0(100, val);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		vec0.reserve(m_container_size);

		CPPUNIT_ASSERT(vec0.capacity() == m_container_size);
	}
}

template<typename Container>
void test_vector::access_element(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = -22./7.;
	Container vec0(m_container_size, val);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < vec0.size(); ++i)
		{
			Cval tmp = vec0[i];
			CPPUNIT_ASSERT(math::is_eq(tmp, val));
		}
	}
}

template<typename Container>
void test_vector::at(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			Cval& obj = array0[0]; // validate address
			for(size_t i=0; i < m_container_size/10; ++i)
			{
				obj = array0.at(i);
			}
		}
	}
}

template<typename Container>
void test_vector::front(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			Cval& obj = array0[0]; // validate address
			for(size_t i=0; i < m_container_size/10; ++i)
			{
				obj = array0.front();
			}
		}
	}
}

template<typename Container>
void test_vector::back(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			Cval& obj = array0[0]; // validate address
			for(size_t i=0; i < m_container_size/10; ++i)
			{
				obj = array0.back();
			}
		}
	}
}

template<typename Container>
void test_vector::push_back(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container vec0;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t j=0; j < m_container_size; ++j)
			vec0.push_back(Cval(j));
	}
}

template<typename Container>
void test_vector::pop_back(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container vec0(m_container_size, Cval(-1e3));

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		while( !vec0.empty() )
		{
			vec0.pop_back();
		}
	}
}

template<typename Container>
void test_vector::insert(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	s_data_v2 obj;
	for(size_t i=0;i<10;i++)
	{
		obj.darray[i] = i * (22./7.);
	}


	//  TEST
	{
		time_printer tp(msg, m_print_time);

		Container vec0;
		for(size_t i=0; i < m_container_size; ++i)
		{
			vec0.insert(vec0.begin(), obj);
		}
	}
}

template<typename Container>
void test_vector::erase(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		// initialization data
		non_pod_v2 np;
		np.val=-100;
		np.fval=-1e3;
		np.ucval = 100;
		np.f = non_pod_f_v2;

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container charr0(10, np);
			Container charr2(10, np);
			Container charr3(10, np);
			// charr0.erase(1, 1);
			charr2.erase(charr2.begin());
			charr3.erase(charr3.begin(), ++charr3.begin());
		}

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container varr0(10, np);
			Container varr2(10, np);
			varr0.erase(varr0.begin()+1);
			varr2.erase(varr2.begin(), ++varr2.begin());
		}
	}
}

template<typename Container>
void test_vector::swap(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	non_pod_v2 np1, np2;
	np1.fval = -1e-2f;
	np1.ucval= 'c';
	np1.val = 100;
	np1.f = non_pod_f_v2;
	np2 = np1;


	Container nparr0(m_container_size, np1);
	Container nparr2(m_container_size, np2);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			nparr0.swap(nparr2);
		}
	}
}

template<typename Container>
void test_vector::clear(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		for(size_t i=0; i < m_container_size; ++i)
		{
			Container array0(m_container_size, -2);
			array0.clear();

			CPPUNIT_ASSERT(array0.begin() == array0.end());
			CPPUNIT_ASSERT(array0.size() == 0);
			CPPUNIT_ASSERT(array0.empty());
		}
	}
}

template<typename Container>
void test_vector::eq_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val = Cval(-3);//(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(m_container_size, val);

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 == vec2);
	}
}
template<typename Container>
void test_vector::less_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec2.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 < vec2);
	}
}
template<typename Container>
void test_vector::noteq_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec2.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 != vec2);
	}
}
template<typename Container>
void test_vector::gt_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec0.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 > vec2);
	}
}
template<typename Container>
void test_vector::gteq_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec0.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 >= vec2);
	}
}
template<typename Container>
void test_vector::lteq_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec2.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		CPPUNIT_ASSERT(vec0 <= vec2);
	}
}
template<typename Container>
void test_vector::swap_op(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval val(-22./7.);
	Container vec0(m_container_size, val);
	Container vec2(vec0);
	vec2.back() *= -1;

	//  TEST
	{
		time_printer tp(msg, m_print_time);

		misc::swap(vec0, vec2);

		CPPUNIT_ASSERT(vec0 > vec2);
	}
}
// end template section
//////////////////////////////////////////////////////////////////////////
