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
	misc::cout << "\n\n\t*******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER: vector.hpp                          *";
	misc::cout <<   "\n\t*******************************************************";

	misc::cout << "\n\n\tctor---------------------------------------------------";
	ctor<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	ctor<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	ctor<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	ctor<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::copy_op()
{
	misc::cout << "\n\n\tcopy_op------------------------------------------------";
	copy_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	copy_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	copy_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	copy_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::assign()
{
	misc::cout << "\n\n\tassign-------------------------------------------------";
	assign<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	assign<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	assign<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	assign<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::begin()
{
	misc::cout << "\n\n\tbegin--------------------------------------------------";
	begin<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	begin<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	begin<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	begin<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::end()
{
	misc::cout << "\n\n\tend----------------------------------------------------";
	end<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	end<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	end<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	end<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::rbegin()
{
	misc::cout << "\n\n\trbegin-------------------------------------------------";
	rbegin<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	rbegin<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	rbegin<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	rbegin<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::rend()
{
	misc::cout << "\n\n\trend---------------------------------------------------";
	rend<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	rend<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	rend<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	rend<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::size()
{
	misc::cout << "\n\n\tsize---------------------------------------------------";
	size<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	size<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	size<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	size<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::resize()
{
	misc::cout << "\n\n\tresize-------------------------------------------------";
	resize<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	resize<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	resize<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	resize<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::empty()
{
	misc::cout << "\n\n\tempty--------------------------------------------------";
	empty<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	empty<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	empty<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	empty<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::reserve()
{
	misc::cout << "\n\n\treserve------------------------------------------------";
	reserve<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	reserve<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	reserve<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	reserve<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::access_element()
{
	misc::cout << "\n\n\toperator[](size_type)----------------------------------";
	access_element<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	access_element<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	access_element<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	access_element<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::at()
{
	misc::cout << "\n\n\tat-----------------------------------------------------";
	at<misc::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	at<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	at<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	at<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::front()
{
	misc::cout << "\n\n\tfront--------------------------------------------------";
	front<misc::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	front<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	front<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	front<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::back()
{
	misc::cout << "\n\n\tback---------------------------------------------------";
	back<misc::vector<nonpod_v2> >                                                                                                           ("\n\tmisc::vector<nonpod_v2>            ");
	back<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<nonpod_v2,POD>        ");
	back<misc::vector<nonpod_v2, misc::allocator<nonpod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<nonpod_v2,POD|DBG_IT> ");
	back<std::vector<nonpod_v2> >                                                                                                            ("\n\tstd::vector<nonpod_v2>             ");
}

void test_vector::push_back()
{
	misc::cout << "\n\n\tpush_back----------------------------------------------";
	push_back<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	push_back<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	push_back<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	push_back<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::pop_back()
{
	misc::cout << "\n\n\tpop_back-----------------------------------------------";
	pop_back<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	pop_back<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	pop_back<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	pop_back<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::insert()
{
	misc::cout << "\n\n\tinsert-------------------------------------------------";
	insert<misc::vector<s_data_v2> >                                                                                                           ("\n\tmisc::vector<s_data_v2>            ");
	insert<misc::vector<s_data_v2, misc::allocator<s_data_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<s_data_v2,POD>        ");
	insert<misc::vector<s_data_v2, misc::allocator<s_data_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<s_data_v2,POD|DBG_IT> ");
	insert<std::vector<s_data_v2> >                                                                                                            ("\n\tstd::vector<s_data_v2>             ");
}

void test_vector::erase()
{
	misc::cout << "\n\n\terase--------------------------------------------------";
	erase<misc::vector<non_pod_v2> >                                                                                                            ("\n\tmisc::vector<non_pod_v2>            ");
	erase<misc::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<non_pod_v2,POD>        ");
	erase<misc::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<non_pod_v2,POD|DBG_IT> ");
	erase<std::vector<non_pod_v2> >                                                                                                             ("\n\tstd::vector<non_pod_v2>             ");
}

void test_vector::swap()
{
	misc::cout << "\n\n\tswap---------------------------------------------------";
	swap<misc::vector<non_pod_v2> >                                                                                                            ("\n\tmisc::vector<non_pod_v2>            ");
	swap<misc::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<non_pod_v2,POD>        ");
	swap<misc::vector<non_pod_v2, misc::allocator<non_pod_v2>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<non_pod_v2,POD|DBG_IT> ");
	swap<std::vector<non_pod_v2> >                                                                                                             ("\n\tstd::vector<non_pod_v2>             ");
}

void test_vector::clear()
{
	misc::cout << "\n\n\tclear--------------------------------------------------";
	clear<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	clear<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	clear<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	clear<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::eq_op()
{
	misc::cout << "\n\n\teq_op--------------------------------------------------";
	eq_op<std::vector<double> >																											("\n\tstd::vector<double>             ");
	eq_op<misc::vector<double> >																										("\n\tmisc::vector<double>            ");
	eq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >												("\n\tmisc::vector<double,POD>        ");
	eq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	eq_op<std::vector<double> >																											("\n\tstd::vector<double>             ");
}

void test_vector::less_op()
{
	misc::cout << "\n\n\tless_op------------------------------------------------";
	less_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	less_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	less_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	less_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::noteq_op()
{
	misc::cout << "\n\n\tnoteq_op-----------------------------------------------";
	noteq_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	noteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	noteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	noteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::gt_op()
{
	misc::cout << "\n\n\tgt_op--------------------------------------------------";
	gt_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	gt_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	gt_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	gt_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::qteq_op()
{
	misc::cout << "\n\n\tgteq_op------------------------------------------------";
	gteq_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	gteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	gteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	gteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::lteq_op()
{
	misc::cout << "\n\n\tlteq_op------------------------------------------------";
	lteq_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	lteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	lteq_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
	lteq_op<std::vector<double> >                                                                                                         ("\n\tstd::vector<double>             ");
}

void test_vector::swap_op()
{
	misc::cout << "\n\n\tswap_op------------------------------------------------";
	swap_op<misc::vector<double> >                                                                                                        ("\n\tmisc::vector<double>            ");
	swap_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >                                             ("\n\tmisc::vector<double,POD>        ");
	swap_op<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >("\n\tmisc::vector<double,POD|DBG_IT> ");
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
