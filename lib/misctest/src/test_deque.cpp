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
#include "test_deque.hpp"


//c++
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <math.h>
#include <string>
#include <time.h>//for clock_t but should be removed soon

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//misc
#include "stream.hpp"
#include "utility.hpp"//misc::advance
#include "misctest_util.hpp"
#include "strconv.hpp"//from_value



//###########################DEQUE TEST CLASS ####################################
void test_deque::setUp()
{
}

void test_deque::tearDown()
{
}


//test begin
void test_deque::ctor()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: deque.hpp                           *";
    stl::cout <<   "\n\t*******************************************************";

	
	stl::cout << "\n\n\tctor---------------------------------------------------";
	ctor<misc::deque<int> >("\n\tmisc::deque ");
	ctor<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
	dtor<misc::deque<int> >("\n\tmisc::deque ");
	dtor<misc::deque<int> >("\n\tstd::deque  ");
}

void test_deque::op_assign()
{
	stl::cout << "\n\n\top_assign----------------------------------------------";
	op_assign<misc::deque<int> >("\n\tmisc::deque ");
	op_assign<std::deque<int> > ("\n\tstd::deque  ");	
}

void test_deque::begin()
{
	stl::cout << "\n\n\tbegin--------------------------------------------------";
	begin<misc::deque<int> >("\n\tmisc::deque ");
	begin<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::end()
{
	stl::cout << "\n\n\tend----------------------------------------------------";
	end<misc::deque<int> >("\n\tmisc::deque ");
	end<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::rbegin()
{
	stl::cout << "\n\n\trbegin-------------------------------------------------";
	rbegin<misc::deque<int> >("\n\tmisc::deque ");
	rbegin<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::rend()
{
	stl::cout << "\n\n\trend---------------------------------------------------";
	rend<misc::deque<int> >("\n\tmisc::deque ");
	rend<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::size()
{
	stl::cout << "\n\n\tsize---------------------------------------------------";
	size<misc::deque<int> >("\n\tmisc::deque ");
	size<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::max_size()
{
	stl::cout << "\n\n\tmax_size-----------------------------------------------";
	max_size<misc::deque<int> >("\n\tmisc::deque ");
	max_size<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::resize()
{
	stl::cout << "\n\n\tresize-------------------------------------------------";
	resize<misc::deque<unsigned int> >("\n\tmisc::deque ");
	resize<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::empty()
{
	stl::cout << "\n\n\tempty--------------------------------------------------";
	empty<misc::deque<int> >("\n\tmisc::deque ");
	empty<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::op_acc()
{
	stl::cout << "\n\n\top_acc-------------------------------------------------";
	op_acc<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_acc<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::at()
{
	stl::cout << "\n\n\tat-----------------------------------------------------";
	at<misc::deque<unsigned int> >("\n\tmisc::deque ");
	at<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::front()
{
	stl::cout << "\n\n\tfront--------------------------------------------------";
	front<misc::deque<int> >("\n\tmisc::deque ");
	front<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::back()
{
	stl::cout << "\n\n\tback---------------------------------------------------";
	back<misc::deque<int> >("\n\tmisc::deque ");
	back<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::assign()
{
	stl::cout << "\n\n\tassign-------------------------------------------------";
	assign<misc::deque<int> >("\n\tmisc::deque ");
	assign<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::push_back()
{
	stl::cout << "\n\n\tpush_back----------------------------------------------";
	push_back<misc::deque<int> >("\n\tmisc::deque ");
	push_back<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::push_front()
{
	stl::cout << "\n\n\tpush_front---------------------------------------------";
	push_front<misc::deque<int> >("\n\tmisc::deque ");
	push_front<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::pop_back()
{
	stl::cout << "\n\n\tpop_back-----------------------------------------------";
	pop_back<misc::deque<int> >("\n\tmisc::deque ");
	pop_back<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::pop_front()
{
	stl::cout << "\n\n\tpop_front----------------------------------------------";
	pop_front<misc::deque<int> >("\n\tmisc::deque ");
	pop_front<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::insert()
{
	stl::cout << "\n\n\tinsert-------------------------------------------------";
	insert<misc::deque<int>, stl::vector<int> >("\n\tmisc::deque ");
	insert<std::deque<int>, std::vector<int> > ("\n\tstd::deque  ");
}

void test_deque::erase()
{
	stl::cout << "\n\n\terase--------------------------------------------------";
	erase<misc::deque<unsigned int> >("\n\tmisc::deque ");
	erase<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::swap_ambiguity()
{
	stl::cout << "\n\n\tswap---------------------------------------------------";
	swap_ambiguity<misc::deque<int> >("\n\tmisc::deque ");
	swap_ambiguity<std::deque<int> > ("\n\tstd::deque  ");
}

void test_deque::clear()
{
	stl::cout << "\n\n\tclear--------------------------------------------------";
	clear<misc::deque<unsigned int> >("\n\tmisc::deque ");
	clear<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::g_swap()
{
	stl::cout << "\n\n\tg_swap-------------------------------------------------";
	g_swap<misc::deque<int> >("\n\tmisc::deque ");
	g_swap<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_eq()
{
	stl::cout << "\n\n\top_eq--------------------------------------------------";
	op_eq<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_eq<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_neq()
{
	stl::cout << "\n\n\top_neq-------------------------------------------------";
	op_neq<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_neq<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_lt()
{
	stl::cout << "\n\n\top_lt--------------------------------------------------";
	op_lt<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_lt<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_lte()
{
	stl::cout << "\n\n\top_lte-------------------------------------------------";
	op_lte<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_lte<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_gt()
{
	stl::cout << "\n\n\top_gt--------------------------------------------------";
	op_gt<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_gt<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

void test_deque::op_gte()
{
	stl::cout << "\n\n\top_gte-------------------------------------------------";
	op_gte<misc::deque<unsigned int> >("\n\tmisc::deque ");
	op_gte<std::deque<unsigned int> > ("\n\tstd::deque  ");
}

//////////////////////////////////////////////////////////////////////////
//template version of test function

template<typename Container>
void test_deque::ctor(const char* msg)
{

	//TEST
	{
		time_printer tm(msg, m_print_time);


		unsigned int i;
		// constructors used in the same order as described above:
		Container first;                                // empty Container of ints
		Container second ((size_t)4,100);               // four ints with value 100
		Container third (second.begin(),second.end());  // iterating through second
		Container fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		Container fifth (myints, myints + sizeof(myints) / sizeof(int) );

		for (i=0; i < fifth.size(); i++)
		{
			CPPUNIT_ASSERT(fifth[i] == myints[i]);
		}
	}
}


template<typename Container>
void test_deque::dtor(const char* msg)
{
}


template<typename Container>
void test_deque::op_assign(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);
	
		Container first (3);      // Container with 3 zero-initialized ints
		Container second (5);     // Container with 5 zero-initialized ints

		second=first;
		first=Container();

		CPPUNIT_ASSERT(first.size() == 0);
		CPPUNIT_ASSERT(second.size() == 3);
	}	
}


template<typename Container>
void test_deque::begin(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);
		

		Container mydeque;
		typename Container::iterator it;

		int i=1;
		for (; i<=5; i++)
		{
			mydeque.push_back(i);
		}

		it = mydeque.begin();
		i = 1;
		while (it != mydeque.end())
		{
			CPPUNIT_ASSERT(*it++ == i++);
		}
	}
}

template<typename Container>
void test_deque::end(const char* msg)
{
	//	TIME
	{
		//	TEST
		time_printer tp(msg, m_print_time);

		Container mydeque;
		typename Container::iterator it;

		int i=1;
		for (; i<=5; i++) mydeque.insert(mydeque.end(),i);

		it = mydeque.begin();

		i = 1;
		while (it != mydeque.end() )
		{
			CPPUNIT_ASSERT(*it++ == i++);
		}
	}	
}

template<typename Container>
void test_deque::rbegin(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);


		Container mydeque;
		typename Container::reverse_iterator rit;

		int i = 1;
		for (; i<=5; i++)
			mydeque.push_back(i);

		rit = mydeque.rbegin();

		i = 5;
		while ( rit < mydeque.rend() )
		{
			CPPUNIT_ASSERT(*rit == i);
			++rit;
			--i;
		}
	}
}

template<typename Container>
void test_deque::rend(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		typename Container::reverse_iterator rit;

		int i=1;
		for (; i<=5; i++)
			mydeque.push_back(i);

		rit = mydeque.rbegin();

		i = 5;
		while ( rit < mydeque.rend() )
		{
			CPPUNIT_ASSERT(*rit == i);

			++rit;
			--i;
		}
	}
}

template<typename Container>
void test_deque::size(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container myints;
		CPPUNIT_ASSERT(myints.size() == 0);

		for (int i=0; i<5; i++) myints.push_back(i);
		CPPUNIT_ASSERT(myints.size() == 5);

		myints.insert (myints.begin(), (size_t)5,100);
		CPPUNIT_ASSERT(myints.size() == 10);

		myints.pop_back();
		CPPUNIT_ASSERT(myints.size() == 9);
	}
}

template<typename Container>
void test_deque::max_size(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		mydeque.resize(10);

		CPPUNIT_ASSERT( mydeque.size() <  mydeque.max_size());
	}
}

template<typename Container>
void test_deque::resize(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		typename Container::iterator it;

		unsigned int i;

		// set some initial content:
		for (i=1;i<10;i++)
		{
			mydeque.push_back(i);
		}

		mydeque.resize(5);
		mydeque.resize(8,100);
		mydeque.resize(12);

		unsigned int myints[]={ 1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0 };
		i = 0;
		for (it=mydeque.begin(); it<mydeque.end(); ++it, ++i)
		{
			CPPUNIT_ASSERT(*it == myints[i]);
		}
	}
}

template<typename Container>
void test_deque::empty(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		int sum (0);

		for (int i=1;i<=10;i++) mydeque.push_back(i);

		while (!mydeque.empty())
		{
			sum += mydeque.front();
			mydeque.pop_front();
		}

		CPPUNIT_ASSERT(sum == 55);
	}
}

template<typename Container>
void test_deque::op_acc(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque (10);   // 10 zero-initialized elements
		unsigned int i;

		typename Container::size_type sz = mydeque.size();

		// assign some values:
		for (i=0; i<sz; i++)
			mydeque[i]=i;

		// reverse order of elements using operator[]:
		for (i=0; i<sz/2; i++)
		{
			int temp;
			temp = mydeque[sz-1-i];
			mydeque[sz-1-i]=mydeque[i];
			mydeque[i]=temp;
		}

		unsigned int myints[]={ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

		for (i=0; i<sz; i++)
		{
			CPPUNIT_ASSERT(mydeque[i] == myints[i]);
		}
	}
}

template<typename Container>
void test_deque::at(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque (10);   // 10 zero-initialized ints
		unsigned int i;

		// assign some values:
		for (i=0; i<mydeque.size(); i++)
			mydeque.at(i)=i;

		unsigned int myints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		for (i=0; i<mydeque.size(); i++)
		{
			CPPUNIT_ASSERT(mydeque.at(i) == myints[i]);
		}
	}
}

template<typename Container>
void test_deque::front(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;

		mydeque.push_front(77);
		mydeque.push_back(16);

		mydeque.front() -= mydeque.back();

		CPPUNIT_ASSERT(mydeque.front() == 61);
	}
}

template<typename Container>
void test_deque::back(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;

		mydeque.push_back(10);

		while (mydeque.back() != 0)
		{
			mydeque.push_back ( mydeque.back() -1 );
		}

		int myints[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

		for (unsigned i=0; i<mydeque.size() ; i++)
			CPPUNIT_ASSERT(mydeque[i] == myints[i]);
	}
}

template<typename Container>
void test_deque::assign(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container first;
		Container second;
		Container third;

		first.assign ((size_t)7,100);             // a repetition 7 times of value 100

		typename Container::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		CPPUNIT_ASSERT(first.size() == 7);
		CPPUNIT_ASSERT(second.size() == 5);
		CPPUNIT_ASSERT(third.size() == 3);
	}
}

template<typename Container>
void test_deque::push_back(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		for(int i=0; i<10; i++)
			mydeque.push_back(i);

		for(int i=0; i<10; i++)
			CPPUNIT_ASSERT(mydeque[i] == i);

		CPPUNIT_ASSERT(mydeque.size() == 10);
	}
}

template<typename Container>
void test_deque::push_front(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque ((size_t)2,100);     // two ints with a value of 100
		mydeque.push_front (200);
		mydeque.push_front (300);

		CPPUNIT_ASSERT(mydeque[0] == 300);
		CPPUNIT_ASSERT(mydeque[1] == 200);
		CPPUNIT_ASSERT(mydeque[2] == 100);
		CPPUNIT_ASSERT(mydeque[3] == 100);
	}
}

template<typename Container>
void test_deque::pop_back(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;
		int sum (0);
		mydeque.push_back (10);
		mydeque.push_back (20);
		mydeque.push_back (30);

		while (!mydeque.empty())
		{
			sum+=mydeque.back();
			mydeque.pop_back();
		}

		CPPUNIT_ASSERT(sum == 60);
	}
}

template<typename Container>
void test_deque::pop_front(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		Container mydeque;    
		mydeque.push_back (100);
		mydeque.push_back (200);
		mydeque.push_back (300);

		int myints[] = { 100, 200, 300 };

		int i = 0;
		while (!mydeque.empty())
		{
			CPPUNIT_ASSERT(mydeque.front() == myints[i++]);
			mydeque.pop_front();
		}
	}
}

template<typename Container, typename AssocContainer>
void test_deque::insert(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);


		Container mydeque;
		typename Container::iterator it;

		// set some initial values:
		for (int i=1; i<6; i++) mydeque.push_back(i); // 1 2 3 4 5

		it = mydeque.begin();
		++it;

		it = mydeque.insert (it,10);                  // 1 10 2 3 4 5
		// "it" now points to the newly inserted 10

		mydeque.insert (it,(size_t)2,20);             // 1 20 20 10 2 3 4 5
		// "it" no longer valid!

		it = mydeque.begin()+2;
				
		AssocContainer myvector (2,30);
		mydeque.insert(it, myvector.begin(), myvector.end());
		// 1 20 30 30 20 10 2 3 4 5

		int myints[] = {1, 20, 30, 30, 20, 10, 2, 3, 4, 5 };
		int i = 0;
		for (it=mydeque.begin(); it<mydeque.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == myints[i++]);
		}
	}
}

template<typename Container>
void test_deque::erase(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		unsigned int i;
		Container mydeque;

		// set some values (from 1 to 10)
		for (i=1; i<=10; i++) mydeque.push_back(i);

		// erase the 6th element
		mydeque.erase (mydeque.begin()+5);

		// erase the first 3 elements:
		mydeque.erase (mydeque.begin(),mydeque.begin()+3);

		unsigned int myints[] = {4, 5, 7, 8, 9, 10};
		for (i=0; i<mydeque.size(); i++)
		{
			CPPUNIT_ASSERT(mydeque[i] == myints[i]);
		}
	}
}

template<typename Container>
void test_deque::swap_ambiguity(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		unsigned int i;
		Container first ((size_t)3,100);   // three ints with a value of 100
		Container second ((size_t)5,200);  // five ints with a value of 200

		first.swap(second);


		for (i=0; i<first.size(); i++)
			CPPUNIT_ASSERT(first[i] == 200);

		for (i=0; i<second.size(); i++)
			CPPUNIT_ASSERT(second[i] == 100);
	}
}


template<typename Container>
void test_deque::clear(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);

		unsigned int i;
		Container mydeque;
		mydeque.push_back (100);
		mydeque.push_back (200);
		mydeque.push_back (300);


		for (i=0; i<mydeque.size(); i++)
		{
			CPPUNIT_ASSERT(mydeque[i] == (i+1)*100);
		}

		mydeque.clear();
		mydeque.push_back (1101);
		mydeque.push_back (2202);


		for (i=0; i<mydeque.size(); i++)
		{
			CPPUNIT_ASSERT(mydeque[i] == (i+1)*1101);
		}
	}
}

template<typename Container>
void test_deque::g_swap(const char* msg)
{
	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		unsigned int i;
		Container first ((size_t)3,100);   // three ints with a value of 100
		Container second ((size_t)5,200);  // five ints with a value of 200

		swap(first, second);

		for (i=0; i<first.size(); i++)
			CPPUNIT_ASSERT(first[i] == 200);

		for (i=0; i<second.size(); i++)
			CPPUNIT_ASSERT(second[i] == 100);
	}
}

template<typename Container>
void test_deque::op_eq(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);
		CPPUNIT_ASSERT(c0 == c2);
	}
}

template<typename Container>
void test_deque::op_neq(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);
		c2.pop_back();
		CPPUNIT_ASSERT(c0 != c2);
	}
}

template<typename Container>
void test_deque::op_lt(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);
		c0.pop_back();
		CPPUNIT_ASSERT(c0 < c2);
	}
}

template<typename Container>
void test_deque::op_lte(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);

		CPPUNIT_ASSERT(c0 <= c2);

		c0.pop_back();

		CPPUNIT_ASSERT(c0 < c2);
	}
}

template<typename Container>
void test_deque::op_gt(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);
		c2.pop_back();
		CPPUNIT_ASSERT(c0 > c2);
	}
}

template<typename Container>
void test_deque::op_gte(const char* msg)
{
	typedef typename Container::value_type Cval;

	{
		time_printer tp(msg, m_print_time);

		Container c0;
		for(Cval i=0; i<Cval(m_container_size); ++i)
		{
			if(i%2)
			{
				c0.push_front(i); 
			}
			else
			{
				c0.push_back(i);
			}
		}

		Container c2(c0);

		CPPUNIT_ASSERT(c0 >= c2);

		c2.pop_back();

		CPPUNIT_ASSERT(c0 > c2);
	}
}
