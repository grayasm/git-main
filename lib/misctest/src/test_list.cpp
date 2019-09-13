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
#include "test_list.hpp"


//c++
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <math.h>
#include <string>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>



//libraries
#include "stream.hpp"
#include "utility.hpp"
#include "strconv.hpp"
#include "misctest_util.hpp"
#include "list.hpp"






//###########################FILENAME TEST CLASS ####################################
void test_list::setUp()
{
}

void test_list::tearDown()
{
}


#if defined DEBUG
const size_t iSize = 12000;      // speed up run-time (debug)
#else
const size_t iSize = 120000;
#endif



//test begin
void test_list::ctor()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: list.hpp                            *";
    stl::cout <<   "\n\t*******************************************************";

	
	
    typedef misc::list<int, misc::allocator<int> > list;

    srand(100);

    //const int iSize = 10000;
    // constructors used in the same order as described above:
    list misc_01;                            // empty list of ints
    CPPUNIT_ASSERT(misc_01.empty());

    list misc_02(iSize, 100);               // four ints with value 100
    CPPUNIT_ASSERT(misc_02.size() == iSize);

    for(list::iterator it = misc_02.begin(); it != misc_02.end(); ++it)
        CPPUNIT_ASSERT( *it == 100 );

    list misc_03(misc_02.begin(),misc_02.end());  // iterating through second
    CPPUNIT_ASSERT(misc_03.size() == iSize);

    for(list::iterator it = misc_03.begin(); it != misc_03.end(); ++it)
        CPPUNIT_ASSERT( *it == 100 );


    list misc_04 (misc_03);                       // a copy of misc_03
    CPPUNIT_ASSERT(misc_04.size() == iSize);

    for(list::iterator it = misc_04.begin(); it != misc_04.end(); ++it)
        CPPUNIT_ASSERT( *it == 100 );

    // the iterator constructor can also be used to construct from arrays:
    int myints[iSize];
    for(int i=0; i<(int)iSize; i++)
        myints[i] = rand()%iSize;

    list misc_05(myints, myints + sizeof(myints) / sizeof(int) );

    bool b_05 = misc_05.size() == iSize;
    CPPUNIT_ASSERT(b_05 == true);

    size_t pos = 0;
    for(list::iterator it = misc_05.begin(); it != misc_05.end(); ++it, ++pos)
        CPPUNIT_ASSERT( *it == myints[pos] );

    //TODO: In C++11 std::allocator::construct has a different signature.
    //      It will take some time to figure the whole new standard out.

    // different allocator
    typedef misc::list<int, std::allocator<int> > List0;
    List0 misc_06(100, 100, std::allocator<int>());
    for(List0::iterator it = misc_06.begin(); it != misc_06.end(); it++)
        CPPUNIT_ASSERT( *it == 100 );


    typedef std::list<int, misc::allocator<int> > List1;
    List1 misc_07(100, 100, misc::allocator<int>());
    for(List1::iterator it = misc_07.begin(); it != misc_07.end(); ++it)
        CPPUNIT_ASSERT( *it == 100 );

    misc::list<int, std::allocator<int> > misc_08(misc_06);
    for(List0::iterator it = misc_08.begin(); it != misc_08.end(); it++)
        CPPUNIT_ASSERT( *it == 100 );
    misc_08 = List0(misc_06.begin(), misc_06.end());
    for(List0::iterator it = misc_08.begin(); it != misc_08.end(); it++)
        CPPUNIT_ASSERT( *it == 100 );


    // different data types
    misc::list<float> misc_09(0, 10); // 'argument' : conversion from 'int' to 'const float', possible loss of data
    misc::list<bool> misc_10(0, 1); // 'int' : forcing value to bool 'true' or 'false'
    CPPUNIT_ASSERT( sizeof(misc_09) == sizeof(misc_10) );


    // construct from invalid iterators
    bool bmisc_11 = false;
    misc::list<float>::iterator it11b, it11e;
    try
    {
        misc::list<float, misc::allocator<float>,
                   misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING> misc_11(it11b, it11e);
    }
    catch(const stl::exception&)
    {
        bmisc_11 = true;
    }
    CPPUNIT_ASSERT(bmisc_11);

    // construct from invalid iterators
    bool bmisc_13=false;
    misc::list<float> misc_12, misc_13;
    misc::list<float>::iterator it12b = misc_12.begin();
    misc::list<float>::iterator it13e = misc_13.end();
    try
    {
        misc::list<float, misc::allocator<float>,
                   misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING> misc_12a(it12b, it13e);
    }
    catch(const stl::exception&)
    {
        bmisc_13 = true;
    }
    CPPUNIT_ASSERT(bmisc_13);


    // construct from invalid iterators
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING> list_debug;

    // misc::list<int>::iterator it14b, it14e;
    list_debug::iterator it14b, it14e;
    {
        // assign to a container that will be invalid later
        list_debug misc_14a(2, 10);
        it14b = misc_14a.begin();
        it14e = misc_14a.end();
    }
    bool bmisc_14 = false;
    try
    {
        // assign from container not valid anymore
        // here it14b, it14e inherit from debug container and have parent = 0;
        misc::list<int> misc_14b(it14b, it14e);
    }
    catch(const stl::exception&)
    {
        bmisc_14 = true;
    }
    CPPUNIT_ASSERT(bmisc_14);

    // malformed usage of copy-ctor
    misc::list<int> misc_15 = misc_15;
    misc_15.assign(2, -1);
    CPPUNIT_ASSERT(misc_15.size() == 2 &&
                   *(--misc_15.end()) == -1 &&
                   *(misc_15.begin()) == -1);


    // after list assignment, iterator of deleted node throws exception
    bool bmisc_16 = false;
    list_debug misc_16a(5, -1);
    list_debug::iterator it16ab = --misc_16a.end();
    int val16a = *it16ab;
    (void)val16a;
    list_debug misc_16b(1, -2);
    misc_16a = misc_16b;
    try
    {
        int val16b = *it16ab;
        (void)val16b;
    }
    catch(const stl::exception&)
    {
        bmisc_16 = true;
    }
    CPPUNIT_ASSERT(bmisc_16);


	
    stl::cout << "\n\n\tctor---------------------------------------------------";
    ctor<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    ctor<std::list<double> >                           ("\n\tstd::list    ");
    ctor<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::dtor()
{
    stl::cout << "\n\n\tdtor---------------------------------------------------";
    dtor<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    dtor<std::list<double> >                           ("\n\tstd::list    ");
    dtor<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::cpy_op()
{
    typedef misc::list<int> list;
    typedef misc::list
        <int,
         misc::allocator<int>,
         misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>    list_debug;

    list first(iSize);
    list second(iSize % 157);

    second=first;
    first=list();

    CPPUNIT_ASSERT( first.size() == 0 );
    CPPUNIT_ASSERT( second.size() == iSize );

    //iterators pointing to old elements are invalid
    bool b_01 = false;
    list_debug list_01(3, 10);
    list_debug list_02(1, -1);
    list_debug::iterator it_1 = --list_01.end();
    list_01 = list_02;
    try
    {
        int val01 = *it_1;
        (void)val01;
    }
    catch(const stl::exception&)
    {
        b_01 = true;
    }
    CPPUNIT_ASSERT(b_01 == true);

    //end iterator is still valid after assignment & points in the same list.
    bool b_03 = true;
    list_debug list_03(3, 10);
    list_debug list_04(1, -1);
    list_debug::iterator it_03e = list_03.end();
    list_03 = list_04;
    try
    {
        int val03 = *(--it_03e);
        (void)val03;
    }
    catch(const stl::exception&)
    {
        b_03 = false;
    }
    CPPUNIT_ASSERT(b_03 == true);

    stl::cout << "\n\n\tcpy_op-------------------------------------------------";
    cpy_op<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    cpy_op<std::list<double> >                           ("\n\tstd::list    ");
    cpy_op<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::begin()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>    list_debug;

    srand(200);
    //const int iSize = 10000;
    int myints[iSize];
    for(int i=0; i<(int)iSize; i++)
        myints[i] = rand()%iSize;

    list mylist (myints,myints+iSize);

    size_t pos = 0;
    for ( list::iterator it = mylist.begin() ; it != mylist.end(); it++, ++pos )
        CPPUNIT_ASSERT( *it == myints[pos] );

    //////////////////////////////////////////////////////////////////////////
    //where is begin after inserting in the list
    {
        //iterator (non-const)
        list_debug list_01 = list_debug(0, -2);
        CPPUNIT_ASSERT(list_01.size() == 0);

        list_debug::iterator it01 = list_01.begin();
        list_debug::iterator it02 = list_01.insert(it01, -1);
        CPPUNIT_ASSERT(it01 == list_01.end());
        CPPUNIT_ASSERT(it02 == list_01.begin());
        list_01.erase(list_01.begin());
        bool b_01 = false;
        try
        {
            int val = *it02;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_01 = true;
        }
        CPPUNIT_ASSERT(b_01 == true);
        CPPUNIT_ASSERT(list_01.size() == 0);
        CPPUNIT_ASSERT(list_01.empty() == true);

        //const_iterator
        list_01.push_back(-10);
        list_debug::const_iterator cit01 = list_01.begin();
        CPPUNIT_ASSERT(*cit01 == -10);
        list_01.erase(list_01.begin());
        bool b_02 = false;
        try
        {
            ++cit01;
        }
        catch(const stl::exception&)
        {
            b_02 = true;
        }
        CPPUNIT_ASSERT(b_02 == true);

        b_02 = false;
        try
        {
            int val = *cit01;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_02 = true;
        }
        CPPUNIT_ASSERT(b_02 == true);
    }
    //////////////////////////////////////////////////////////////////////////
    //begin points to an invalid list
    {
        list_debug::iterator it01;
        list_debug::const_iterator cit01;
        {
            list_debug list_1(1, -1);
            it01 = list_1.begin();
            cit01= list_1.begin();
        }
        bool b_b = false, b_b1 = false;
        try
        {
            int val = *it01;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_b = true;
        }
        CPPUNIT_ASSERT(b_b == true);
        try
        {
            int val = *cit01;
            (void)val;
        }
        catch(stl::exception&)
        {
            b_b1 = true;
        }
        CPPUNIT_ASSERT(b_b1 == true);
    }


    stl::cout << "\n\n\tbegin--------------------------------------------------";
    begin<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    begin<std::list<double> >                           ("\n\tstd::list    ");
    begin<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::end()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>    list_debug;

    srand(300);
    //const int iSize = 10000;
    int myints[iSize];
    for(int i=0; i<(int)iSize; i++)
        myints[i] = rand()%iSize;

    list mylist (myints,myints+iSize);

    size_t pos = 0;
    for ( list::iterator it = mylist.begin() ; it != mylist.end(); it++, ++pos )
        CPPUNIT_ASSERT( *it == myints[pos] );


    //////////////////////////////////////////////////////////////////////////
    {
        //dereferencing end iterator
        list list_1(1, -1);
        list::iterator ie0 = list_1.end();
        bool b_1=false;
        try
        {
            int val = *ie0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        bool b_2 = false;
        list_debug::iterator ie2;
        // end iterator of invalid list
        {
            list_debug list_2(1, -1);
            ie2 = list_2.end();
        }
        try
        {
            --ie2;// would work with a valid list
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
        //try to remove end iterator
        bool b_3 =  false;
        try
        {
            list list_3(10, -10);
            list_3.erase(list_3.end());
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
        //comparison + erase attempt
        list list_4(0, -1);
        CPPUNIT_ASSERT(list_4.begin() == list_4.end());
        bool b_4 = false;
        try
        {
            list_4.erase(list_4.begin());
        }
        catch(const stl::exception&)
        {
            b_4 = true;
            (void)b_4;
        }
        //clear does not invalidate end iterator
        list list_5(1, -10);
        list::const_iterator i5e = list_5.end();
        list_5.clear();
        CPPUNIT_ASSERT(i5e == list_5.end());
    }

    stl::cout << "\n\n\tend----------------------------------------------------";
    end<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    end<std::list<double> >                           ("\n\tstd::list    ");
    end<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::rbegin()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>    list_debug;


    list mylist;
    //const int iSize = 10000;
    for (int i=1; i <= (int)iSize; i++) mylist.push_back(i);

    list::reverse_iterator rit;
    size_t x = iSize;
    for ( rit=mylist.rbegin() ; rit != mylist.rend(); ++rit, --x )
        CPPUNIT_ASSERT( *rit == (int)x );

    //////////////////////////////////////////////////////////////////////////
    {
        //dereference iterator at removed node.
        int i1t[3]={-9,-8,-7};
        list_debug list_1(i1t, i1t+3);
        list_debug::reverse_iterator r0i = list_1.rbegin();
        list_1.erase( --list_1.end() );
        bool b_1 = false;
        try
        {
            int val = *r0i;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        //reverse iterator to invalid list
        list_debug ::reverse_iterator r2i;
        {
            list_debug  list_2(i1t, i1t+3);
            r2i = list_2.rbegin();
        }
        bool b_2 = false;
        try
        {
            ++r2i;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);

        //const_reverse_iterator
        list_debug  list_3(3, 10);
        list_debug::const_reverse_iterator cr3i = list_3.rbegin();
        list_3.clear();
        bool b_3 = false;
        try
        {
            int val = *cr3i;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);

        //const_reverse_iterator to invalid list
        list_debug::const_reverse_iterator cr4i;
        {
            list_debug list_4(2, 0);
            cr4i = list_4.rbegin();
        }
        bool b_4 = false;
        try
        {
            int val = *cr4i;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_4 = true;
        }
        CPPUNIT_ASSERT(b_4 == true);
    }

    stl::cout << "\n\n\trbegin-------------------------------------------------";
    rbegin<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    rbegin<std::list<double> >                           ("\n\tstd::list    ");
    rbegin<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::rend()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>    list_debug;



    list mylist;
    for (int i=1; i<=(int)iSize; i++) mylist.push_back(i);

    list::reverse_iterator rit;
    size_t x = iSize;
    for ( rit=mylist.rbegin() ; rit != mylist.rend(); ++rit, --x )
        CPPUNIT_ASSERT( *rit == (int)x );


    //////////////////////////////////////////////////////////////////////////
    {
        //dereferencing end reverse_iterator
        list list_1(1, -1);
        list::reverse_iterator ie0 = list_1.rend();
        bool b_1=false;
        try
        {
            int val = *ie0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        bool b_2 = false;
        list_debug::reverse_iterator ie2;
        // end reverse_iterator of invalid list
        {
            list_debug list_2(1, -1);
            ie2 = list_2.rend();
        }
        try
        {
            --ie2;// would work with a valid list
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
        //comparison + erase attempt
        list list_3(0, -1);
        CPPUNIT_ASSERT(list_3.rbegin() == list_3.rend());

        //clear does not invalidate end iterator
        list list_4(1, -10);
        list::const_reverse_iterator i4e = list_4.rend();
        list_4.clear();
        CPPUNIT_ASSERT(i4e == list_4.rend());
    }

    stl::cout << "\n\n\trend---------------------------------------------------";
    rend<misc::list<double, misc::allocator<double> > >("\n\tmisc::list   ");
    rend<std::list<double> >                           ("\n\tstd::list    ");
    rend<std::list<double, misc::allocator<double> > > ("\n\tstd::list<A> ");
}

void test_list::empty()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;

    list mylist;
    int sum (0);

    for (int i=1;i<=10;i++) mylist.push_back(i);

    while (!mylist.empty())
    {
        sum += mylist.front();
        mylist.pop_front();
    }

    CPPUNIT_ASSERT( sum == 55 );
    CPPUNIT_ASSERT( mylist.empty() == true );

    //////////////////////////////////////////////////////////////////////////
    {
        list_debug list_1(3, -10);
        list_debug::iterator it0 = list_1.begin();
        list_debug::const_iterator cit0 = list_1.begin();
        list_debug::reverse_iterator rit0 = list_1.rbegin();
        list_debug::const_reverse_iterator crit0 = list_1.rbegin();
        CPPUNIT_ASSERT( list_1.empty() == false );
        list_1.clear();
        CPPUNIT_ASSERT( list_1.empty() == true );
        bool bit0 = false, bcit0 = false, brit0 = false, bcrit0 = false;
        try
        {
            bool b_x = (it0 == list_1.end()); // access invalid iterator
            (void)b_x;
        }
        catch(const stl::exception&)
        {
            bit0 = true;
        }
        CPPUNIT_ASSERT(bit0 == true);
        try
        {
            bool b_x = (cit0 == list_1.end()); // access invalid iterator
            (void)b_x;
        }
        catch(const stl::exception&)
        {
            bcit0 = true;
        }
        CPPUNIT_ASSERT(bcit0 == true);
        try
        {
            bool bx = (rit0 == list_1.rbegin()); // access invalid iterator
            (void)bx;
        }
        catch(const stl::exception&)
        {
            brit0 = true;
        }
        CPPUNIT_ASSERT(brit0 == true);
        try
        {
            bool bx= (crit0 == list_1.rbegin()); // access invalid iterator
            (void)bx;
        }
        catch(const stl::exception&)
        {
            bcrit0 = true;
        }
        CPPUNIT_ASSERT(bcrit0 == true);
    }

    stl::cout << "\n\n\tempty--------------------------------------------------";
}

void test_list::size()
{
    typedef misc::list<int> list;

    list myints;
    CPPUNIT_ASSERT( myints.size() == 0 );

    for (int i=0; i < (int)iSize; i++) myints.push_back(i);
    CPPUNIT_ASSERT( myints.size() == iSize );

    myints.insert (myints.begin(), (size_t)iSize, 100);
    CPPUNIT_ASSERT( myints.size() == 2*iSize );

    myints.pop_back();
    CPPUNIT_ASSERT( myints.size() == (2*iSize - 1) );

    stl::cout << "\n\n\tsize---------------------------------------------------";
}

void test_list::max_size()
{
    typedef misc::list<int> list;
    list mylist;

    if(iSize < mylist.max_size())
        mylist.resize(iSize);

    CPPUNIT_ASSERT( mylist.size() == iSize );

    stl::cout << "\n\n\tmax_size-----------------------------------------------";
}

void test_list::resize()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;


    list perflist;
    perflist.resize(iSize);
    CPPUNIT_ASSERT( perflist.size() == iSize );
    //////////////////////////////////////////////////////////////////////////

    list mylist;

    unsigned int i;

    // set some initial content:
    for (i=1; i<10; i++) mylist.push_back(i);

    mylist.resize(5);
    mylist.resize(8,100);
    mylist.resize(12);

    int final[]={1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0};
    i=0;
    for (list::iterator it=mylist.begin();it!=mylist.end();++it, ++i)
        CPPUNIT_ASSERT( *it == final[i] );

    //////////////////////////////////////////////////////////////////////////
    //reverse_iterator
    {
        list_debug list_1(3, 10);
        list_debug::const_reverse_iterator cri0 = list_1.rbegin();
        list_debug::const_reverse_iterator cri1 = list_1.rend();
        list_1.resize(1, 9);
        CPPUNIT_ASSERT( cri1 == list_1.rend() );
        bool b_1 = false;
        try
        {
            int val = *cri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    //iterator
    {
        list_debug list_2(3, 10);
        list_debug::const_iterator ri2 = list_2.begin();
        list_debug::const_iterator ri3 = list_2.end();
        list_debug::const_iterator ri4 = --list_2.end();
        list_2.resize(1, 9);
        CPPUNIT_ASSERT( ri3 == list_2.end() );
        CPPUNIT_ASSERT( *ri2 == 10 );
        bool b_2 = false;
        try
        {
            int val = *ri4;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    stl::cout << "\n\n\tresize-------------------------------------------------";

    resize<misc::list<double> >                         ("\n\tmisc::list   ");
    resize<std::list<double> >                          ("\n\tstd::list    ");
    resize<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::front()
{
    typedef misc::list<int> list;


    list list_1;
    for(int i=0; i<(int)iSize; ++i)
    {
        list_1.push_front(i);
        CPPUNIT_ASSERT( list_1.front() == i );
    }

    list list_2;
    list_2.push_back(77);
    list_2.push_back(22);
    list_2.front() -= list_2.back();
    CPPUNIT_ASSERT( list_2.front() == 55 );


    //////////////////////////////////////////////////////////////////////////
    {
        list list_3;
        bool b_3 = false;
        try
        {
            int val = list_3.front();
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
    }

    stl::cout << "\n\n\tfront--------------------------------------------------";
}

void test_list::back()
{
    typedef misc::list<int> list;
    list perflist;
    for(int i=0; i<(int)iSize; ++i)
    {
        perflist.push_back(i);
        CPPUNIT_ASSERT( perflist.back() == i );
    }


    list mylist;
    mylist.push_back(10);
    while (mylist.back() != 0)
    {
        mylist.push_back ( mylist.back() -1 );
    }

    size_t i=10;
    for (list::iterator it=mylist.begin(); it!=mylist.end() ; ++it, --i)
        CPPUNIT_ASSERT( *it == (int)i );//10 9 8 7 6 5 4 3 2 1 0

    //////////////////////////////////////////////////////////////////////////
    {
        list list_1(3, -1);
        bool b_1 = false;
        CPPUNIT_ASSERT(list_1.back() == -1);
        list_1.clear();
        try
        {
            int val = list_1.back();
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tback---------------------------------------------------";
}

void test_list::assign()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    //const int iSize = 10000;
    list misc_01;
    list misc_02;

    misc_01.assign ((size_t)iSize, 100);         // iSize ints with value 100

    misc_02.assign (misc_01.begin(),misc_01.end()); // a copy of first

    int myints[]={1776,7,4};
    misc_01.assign (myints,myints+3);            // assigning from array


    CPPUNIT_ASSERT( misc_01.size() == 3 );
    CPPUNIT_ASSERT( misc_02.size() == iSize );

    size_t i = 0;
    for(list::iterator it = misc_01.begin(); it != misc_01.end(); ++it, ++i)
        CPPUNIT_ASSERT( *it == myints[i] );

    for(list::iterator it = misc_02.begin(); it != misc_02.end(); ++it)
        CPPUNIT_ASSERT( *it == 100 );


    //////////////////////////////////////////////////////////////////////////
    // after list assignment, iterator of deleted node throws exception
    {
        list_debug list_3(5, -1); // list_3 with 5 elements
        list_debug::iterator i3a = --list_3.end();
        int val_3 = *i3a;
        (void)val_3;
        list list_4(1, -2); // list_4 with 1 element
        list_3.assign(list_4.begin(), list_4.end()); // i3a invalidated
        bool b_3 = false;
        try
        {
            int val = *i3a; // debug_iterator :)
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
    }


    // after list assignment, iterator of deleted node throws exception
    {
        list_debug list_1(5, -1);
        list_debug::const_reverse_iterator cri0 = list_1.rbegin();
        CPPUNIT_ASSERT(*cri0 == -1);
        list_1.assign(1, -2); // i0 invalidated

        bool b_1 = false;
        try
        {
            int val = *cri0; // debug_iterator
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1);
    }

    //invalid assignment
    {
        list list_1(1, 1), list_2(1, 2), list_3;
        bool b_1 = false;
        try
        {
            // iterators belonging to different containers
            list_3.assign(list_1.begin(), list_2.end());
        }
        catch(const stl::exception& exc)
        {
            exc.what();
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    //invalid assignment
    {
        bool b_1 = false;
        try
        {
            list list_1(-1, 10);
        }
        catch(const stl::exception& exc)
        {
            exc.what();
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        list list_2;
        bool b_2 = false;
        try
        {
            list list_3;
            list_3.assign(-1, 10);
        }
        catch(const stl::exception& exc)
        {
            exc.what();
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    //invalid assignment
    {
        list_debug::iterator i0, i1;
        {
            list_debug list_1(10, -1);
            i0 = list_1.begin();
            i1 = list_1.end();
        }
        bool b_1 = false;
        try
        {
            // assign from invalid iterators
            list list_2(i0, i1); // uses debug_iterators
        }
        catch(const stl::exception& exc)
        {
            exc.what();
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tassign-------------------------------------------------";
    assign<misc::list<double> >                         ("\n\tmisc::list   ");
    assign<std::list<double> >                          ("\n\tstd::list    ");
    assign<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

////////////////////////////////////////////////////////////////////////////////
class A
{
public:
    A(){ m_val=0; }
    A(int val){ m_val=val; }
    A(const A& a){ *this = a; }
    A& operator=(const A& a){ m_val=a.m_val; return *this; }
    ~A(){}
    const int& eval() const{ return m_val; }
private:
    int m_val;
};


void test_list::push_front()
{
    typedef misc::list<int> list;

    //const int iSize = 10000;
    list mylist ((size_t)iSize,100);         // two ints with a value of 100
    mylist.push_front (200);
    mylist.push_front (300);


    list::iterator it = mylist.begin();
    CPPUNIT_ASSERT( *it == 300 );
    advance(it, 1);
    CPPUNIT_ASSERT( *it == 200 );
    advance(it, 1);

    for (; it!=mylist.end(); ++it)
        CPPUNIT_ASSERT( *it ==  100 );

    CPPUNIT_ASSERT( mylist.size() == (iSize+2) );

    //////////////////////////////////////////////////////////////////////////
    {
        misc::list<A> list_a;
        A ta[10];
        list_a.assign(ta, ta+10);
        ta[0]=A(-10);
        list_a.push_front(ta[0]);
        CPPUNIT_ASSERT(list_a.front().eval() == -10);
    }

    stl::cout << "\n\n\tpush_front---------------------------------------------";
    push_front<misc::list<double> >                         ("\n\tmisc::list   ");
    push_front<std::list<double> >                          ("\n\tstd::list    ");
    push_front<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::pop_front()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    list mylist;
    for(int i=0; i<(int)iSize; ++i)
        mylist.push_back(i);

    int i = 0;
    while (!mylist.empty())
    {
        CPPUNIT_ASSERT( mylist.front() == i++ );
        mylist.pop_front();
    }

    CPPUNIT_ASSERT( mylist.size() == 0 );

    //////////////////////////////////////////////////////////////////////////
    {
        // dereference invalid iterator
        list_debug list_1(1, 99);
        list_debug::reverse_iterator ri0 = list_1.rbegin();
        list_1.pop_front();
        bool b_1 = false;
        try
        {
            int val = *ri0; // debug_iterator
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }


    stl::cout << "\n\n\tpop_front----------------------------------------------";
    pop_front<misc::list<double> >                         ("\n\tmisc::list   ");
    pop_front<std::list<double> >                          ("\n\tstd::list    ");
    pop_front<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::push_back()
{
    typedef misc::list<int> list;

    srand(400);
    int myints[iSize];

    for(int i=0; i<(int)iSize; ++i)
        myints[i] = rand()%iSize;

    list mylist;

    size_t i = 0;
    do
    {
        mylist.push_back (myints[i]);

    } while (++i < sizeof(myints) / sizeof(myints[0]) );


    CPPUNIT_ASSERT( mylist.size() == sizeof(myints)/sizeof(myints[0]) );

    //////////////////////////////////////////////////////////////////////////
    {
        list list_1;
        list_1.push_back(-10);
        list::const_reverse_iterator cri0 = list_1.rend();
        CPPUNIT_ASSERT(*--cri0 == *list_1.begin());
        ++cri0; // move back on rend() position
        list_1.pop_front();
        CPPUNIT_ASSERT(cri0 == list_1.rbegin());
        bool b_1 = false;
        try
        {
            --cri0; // illegal on zero size container
        }
        catch(const stl::exception&)
        {
            b_1 =true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tpush_back----------------------------------------------";
    push_back<misc::list<double> >                         ("\n\tmisc::list   ");
    push_back<std::list<double> >                          ("\n\tstd::list    ");
    push_back<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::pop_back()
{
    typedef misc::list<int> list;

    list perflist((size_t) iSize);
    while( !perflist.empty() )
        perflist.pop_back();

    list mylist;
    int sum (0);
    mylist.push_back (100);
    mylist.push_back (200);
    mylist.push_back (300);

    while (!mylist.empty())
    {
        sum+=mylist.back();
        mylist.pop_back();
    }
    CPPUNIT_ASSERT( sum == 600 );

    //////////////////////////////////////////////////////////////////////////
    {
        list list_1;
        bool b_1=false;
        try
        {
            list_1.pop_back();
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }


    stl::cout << "\n\n\tpop_back-----------------------------------------------";
    pop_back<misc::list<double> >                         ("\n\tmisc::list   ");
    pop_back<std::list<double> >                          ("\n\tstd::list    ");
    pop_back<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::insert()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;


    list perflist;
    list copylist((size_t) 10);
    while(perflist.size() < iSize)
    {
        for(int i=0; i<10; i++)
            perflist.push_back(i);
        for(int i=0; i<10; i++)
        {
            perflist.insert(perflist.begin(), i);
        }
        list::iterator it = perflist.begin();
        advance(it, 10);
        for(int i=0; i<10; i++)
        {
            perflist.insert(it, (size_t)10, i);
            it = perflist.begin();
            advance(it, i+1);
        }
        it = perflist.begin();
        for(int i=0; i<10; i++)
        {
            perflist.insert(it, copylist.begin(), copylist.end());
            it = perflist.begin();
            advance(it, i+1);
        }
    }
    //////////////////////////////////////////////////////////////////////////


    list mylist;
    list::iterator it;

    // set some initial values:
    for (int i=1; i<=5; i++) mylist.push_back(i); // 1 2 3 4 5

    it = mylist.begin();
    ++it;       // it points now to number 2           ^

    mylist.insert (it,10);                        // 1 10 2 3 4 5


    // "it" still points to number 2                      ^
    mylist.insert (it,(size_t)2,20);                      // 1 10 20 20 2 3 4 5
    --it;       // it points now to the second 20            ^

    std::vector<int> myvector (2,30);
    mylist.insert (it,myvector.begin(),myvector.end());
    // 1 10 20 30 30 20 2 3 4 5
    //               ^

    size_t pos = 0;
    int myints[]={1, 10, 20, 30, 30, 20, 2, 3, 4, 5};

    for (it=mylist.begin(); it!=mylist.end(); it++, ++pos)
        CPPUNIT_ASSERT( *it == myints[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        //insert at invalid iterator position
        list_debug list_1;
        list_debug list_2;
        list_debug::iterator i0 = list_1.begin();
        bool b_1 = false;
        try
        {
            list_2.insert(i0, -10); // iterator of different container
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        list_2.push_back(-10);
        list_debug::iterator i2 = list_2.begin();
        list_2.erase(list_2.begin());
        bool b_2 = false;
        try
        {
            list_2.insert(i2, -10); // iterator of erased node
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }
    {
        //insert n == max_size number of elements
        list_debug list_1;
        bool b_1 = false;
        try
        {
            list_1.insert(list_1.end(), (size_t)-1, -1);
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        //insert with iterator from a different list
        list_debug list_2;
        bool b_2 = true;
        try
        {
            list_1.insert(list_2.begin(), (size_t)1, 1);
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
        //insert at deleted iterator from a different list
        list_debug::iterator i3;
        {
            list_debug list_3;
            i3 = list_3.end();
        }
        bool b_3 = false;
        try
        {
            list_1.insert(i3, (size_t)1, 1);
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
    }
    {
        //insert (1) at invalid position & (2) invalid first,last iterators
        list list_1, list_2(3, 10);
        bool b_1 = false;
        try
        {
            //position from different container
            list_1.insert(list_2.end(), list_2.begin(), list_2.end());
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        bool b_2 = false;
        try
        {
            //last iterator from different container
            list_1.insert(list_1.end(), list_2.begin(), list_1.end());
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }
    {
        //insert with invalid first or last iterators
        list_debug::iterator i0, i2;
        {
            list_debug list_1(3, -3);
            i0 = list_1.begin();
            i2 = list_1.end();
        }
        list list_1;
        bool b_1 = false;
        try
        {
            list_1.insert(list_1.end(), i0, i2);
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tinsert-------------------------------------------------";
    insert<misc::list<double> >                         ("\n\tmisc::list   ");
    insert<std::list<double> >                          ("\n\tstd::list    ");
    insert<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::erase()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;


    list perflist((size_t)iSize, iSize);
    while( !perflist.empty() )
    {
        perflist.erase(--perflist.end());
    }
    //////////////////////////////////////////////////////////////////////////

    unsigned int i;
    list mylist;
    list::iterator it1,it2;

    // set some values:
    for (i=1; i<10; i++) mylist.push_back(i*10);

    // 10 20 30 40 50 60 70 80 90

    it1 = it2 = mylist.begin(); // ^^
    advance (it2,6);            // ^                 ^
    ++it1;                      //    ^              ^

    it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
    //    ^           ^

    it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
    //    ^           ^

    ++it1;                      //       ^        ^
    --it2;                      //       ^     ^

    mylist.erase (it1,it2);     // 10 30 60 80 90
    //        ^

    int myints[] = {10, 30, 60, 80, 90};
    size_t pos = 0;
    for (it1=mylist.begin(); it1!=mylist.end(); ++it1, ++pos)
        CPPUNIT_ASSERT( *it1 == myints[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        //erase invalid iterator
        list list_1;
        bool b_1 = false;
        try
        {
            // attempt to erase begin==end invalid iterator
            list_1.erase(list_1.begin());
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        list_1.push_back(1);
        list list_2(1, 1);
        bool b_2 = false;
        try
        {
            list_1.erase(list_2.begin());
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
        //dereference erased iterator
        list_debug list_3(1, 1);
        list_debug::iterator i3 = list_3.begin();
        list_3.erase(list_3.begin());
        bool b_3 = false;
        try
        {
            int val = *i3;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
    }

    {
        // erase with invalid first, last iterators
        list_debug list_1(1, -10), list_2(1, -10);
        bool b_1 = false;
        try
        {
            list_1.erase(list_1.begin(), list_2.end());
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        list_debug::iterator i0, i2;
        {
            list_debug list_3(3, 3);
            i0 = list_3.begin();
            i2 = list_3.end();
        }
        bool b_2 = false;
        try
        {
            list_1.erase(i0, i2);
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    {
        //access an erased iterator
        list_debug list_1(3, 3);
        list_debug::const_reverse_iterator cri0 = list_1.rbegin();
        list_1.erase( --list_1.end() );
        bool b_1 = false;
        try
        {
            int val = *cri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        list_debug list_2(3, 3);
        list_debug::const_iterator ci20 = ++list_2.begin();
        list_2.erase(list_2.begin(), list_2.end());
        bool b_2 = false;
        try
        {
            int val = *ci20;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    stl::cout << "\n\n\terase--------------------------------------------------";
    erase<misc::list<double> >                         ("\n\tmisc::list   ");
    erase<std::list<double> >                          ("\n\tstd::list    ");
    erase<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::swap()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    list first ((size_t)iSize,100);   // iSize ints with a value of 100
    list second ((size_t)iSize/2 ,200);  // iSize/2 ints with a value of 200
    list::iterator it;

    first.swap(second);

    for (it=first.begin(); it!=first.end(); it++)
        CPPUNIT_ASSERT( *it == 200 );

    for (it=second.begin(); it!=second.end(); it++)
        CPPUNIT_ASSERT( *it == 100 );

    //////////////////////////////////////////////////////////////////////////
    {
        list_debug list_1(5, 1), list_2(1, 2);
        list_debug::const_reverse_iterator cri0 = list_1.rbegin();
        list_debug::const_reverse_iterator cri2 = list_1.rend();
        list_debug::const_iterator ci0 = list_2.begin();
        list_debug::const_iterator ci2 = list_2.end();
        list_1.swap(list_2);

        CPPUNIT_ASSERT(cri2 == list_2.rend());
        CPPUNIT_ASSERT(ci2 == list_1.end());

        for(; cri0 != cri2; ++cri0)
        {
            CPPUNIT_ASSERT(*cri0 == 1);
        }
        for(; ci0 != ci2; ++ci0)
        {
            CPPUNIT_ASSERT(*ci0 == 2);
        }
    }

    {
        list list_1(2, 1), list_2(5, 2);
        list::iterator i0 = list_1.begin();
        i0 = list_2.begin();
        list_1.clear();
        list_1.swap(list_2);
        CPPUNIT_ASSERT(*i0 == 2);
        for(; i0 != list_1.end(); ++i0)
            CPPUNIT_ASSERT(*i0 == 2);
    }

//TODO: "more tests can be performed here, valid/invalid iterators, etc"

    stl::cout << "\n\n\tswap---------------------------------------------------";
    swap<misc::list<double> >                         ("\n\tmisc::list   ");
    swap<std::list<double> >                          ("\n\tstd::list    ");
    swap<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::clear()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    list perflist(iSize);
    perflist.clear();
    //////////////////////////////////////////////////////////////////////////

    list mylist;
    list::iterator it;

    mylist.push_back (100);
    mylist.push_back (200);
    mylist.push_back (300);


    size_t val = 100;
    for (it=mylist.begin(); it!=mylist.end(); ++it, val += 100)
        CPPUNIT_ASSERT( *it == (int)val );

    mylist.clear();
    mylist.push_back (1101);
    mylist.push_back (2202);

    val = 1101;
    for (it=mylist.begin(); it!=mylist.end(); ++it, val += 1101)
        CPPUNIT_ASSERT( *it == (int)val );

    //////////////////////////////////////////////////////////////////////////
    {
        list_debug list_1(3, 1);
        list_debug::reverse_iterator ri0 = list_1.rbegin();
        for(size_t i=1; i<list_1.size(); ++i)
            ++ri0;
        list_1.clear();
        bool b_1 = false;
        try
        {
            int val = *ri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tclear--------------------------------------------------";
    clear<misc::list<double> >                         ("\n\tmisc::list   ");
    clear<std::list<double> >                          ("\n\tstd::list    ");
    clear<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::splice()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;




    list perflist1(iSize);
    list perflist2(iSize);
    perflist2.splice(perflist2.begin(), perflist1);
    perflist1.splice(perflist1.begin(), perflist2, --perflist2.end());
    perflist1.splice(perflist1.begin(), perflist2, perflist2.begin(), perflist2.end());
    list::iterator pit = perflist1.begin();
    misc::advance(pit, iSize/2);
    perflist1.splice(perflist1.begin(), perflist1, pit, perflist1.end());
    //////////////////////////////////////////////////////////////////////////

    list mylist1, mylist2;
    list::iterator it;

    // set some initial values:
    for (int i=1; i<=4; i++)
        mylist1.push_back(i);      // mylist1: 1 2 3 4

    for (int i=1; i<=3; i++)
        mylist2.push_back(i*10);   // mylist2: 10 20 30

    it = mylist1.begin();          // mylist1: 1 2 3 4
    ++it;                          //            ^

    mylist1.splice (it, mylist2);  // mylist1: 1 10 20 30 2 3 4
    // mylist2 (empty)
    // "it" still points to 2 (the 5th element)           ^

    mylist2.splice (mylist2.begin(),mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.
    it = mylist1.begin();
    advance(it,3);                // "it" points now to 30

    mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
    // mylist1: 30 3 4 1 10 20

    int myints1[]={30, 3, 4, 1, 10, 20};
    size_t pos = 0;
    for (it=mylist1.begin(); it!=mylist1.end(); it++, ++pos)
        CPPUNIT_ASSERT( *it == myints1[pos] );

    int myints2[]={2};
    pos = 0;
    for (it=mylist2.begin(); it!=mylist2.end(); it++, ++pos)
        CPPUNIT_ASSERT( *it == myints2[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        //splice using same container
        list_debug list_1(3, 3);
        list_1.splice(list_1.end(), list_1);
        CPPUNIT_ASSERT(list_1.size() == 3);
        for(list_debug::reverse_iterator rit = list_1.rbegin(); rit != list_1.rend(); ++rit)
        {
            CPPUNIT_ASSERT(*rit == 3);
        }
        //splice with invalid iterator (erased & invalid container)
        list_debug list_2;
        bool b_1 = false;
        try
        {
            list_1.splice(list_2.end(), list_2);
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        //iterators of x are invalid
        int tint[5]={-1, -2, -3, -4, -5};
        list_debug list_3;
        list_3.assign(tint, tint+5);
        list_debug::const_reverse_iterator crit3 = list_3.rbegin();
        ++crit3;
        CPPUNIT_ASSERT(*crit3 == -4);
        CPPUNIT_ASSERT(list_1.size() == 3); // all 3s
        list_1.splice(list_1.end(), list_3); // all iterators of list_3 gone.
        bool b_3 = false;
        try
        {
            int val = *crit3;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
    }

    {
        //splice with invalid position (erased & invalid/another container)
        list_debug list_1(1, -1), list_2(2, 2);
        bool b_1 = false;
        try
        {
            //1st iterator of different container
            list_1.splice(list_2.end(), list_2, list_2.begin());
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        list_debug::iterator i2 = list_1.begin();
        list_1.erase(list_1.begin());
        bool b_2 = false;
        try
        {
            list_1.splice(i2, list_2, --list_2.end()); // 1st iterator erased
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
        //splice with invalid 2nd iterator (erased & from different container)
        list_debug list_3(3, 3);
        list_debug::iterator it3 = list_3.begin();
        list_3.erase(list_3.begin());
        bool b_3 = false;
        try
        {
            //it3 erased iterator
            list_1.splice(list_1.begin(), list_3, it3);
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);
        bool b_4 = false;
        try
        {
            //2nd iterator from different container
            list_1.splice(list_1.begin(), list_3, list_1.begin());
        }
        catch(const stl::exception&)
        {
            b_4 = true;
        }
        CPPUNIT_ASSERT(b_4 == true);
        //splice with empty container
        list_debug list_5;
        bool b_5 = false;
        try
        {
            //x container is empty
            list_1.splice(list_1.begin(), list_5, list_5.begin());
        }
        catch(const stl::exception&)
        {
            b_5 = true;
        }
        CPPUNIT_ASSERT(b_5 == true);
        //slice with 2nd iterator as end position
        list_debug list_6(1, -1);
        bool b_6 = false;
        try
        {
            //2dn iterator as end position
            list_1.splice(list_1.begin(), list_6, list_6.end());
        }
        catch(const stl::exception&)
        {
            b_6 = true;
        }
        CPPUNIT_ASSERT(b_6 == true);
        //splice with 1st iterator the same with 2nd iterator (no change)
        int i7tab[5]={-1, -2, -3, -4, -5};
        list_debug list_7(i7tab, i7tab+5);
        list_7.splice(++list_7.begin(), list_7, ++list_7.begin());
        CPPUNIT_ASSERT(list_7.size() == 5);
        int j=0;
        list_debug::iterator i7 = list_7.begin();
        for(; i7 != list_7.end(); ++i7, ++j)
            CPPUNIT_ASSERT(*i7 == i7tab[j]);

        //splice with 1st iterator == ++2nd iterator (no change)
        list_7.splice(++(++list_7.begin()), list_7, ++list_7.begin());
        j=0;
        i7 = list_7.begin();
        for(; i7 != list_7.end(); ++i7, ++j)
            CPPUNIT_ASSERT(*i7 == i7tab[j]);


        //iterators of x pointing to i get invalid
        list_debug list_8(3, -3);
        list_debug::iterator i8 = --list_8.end();
        list_7.splice(list_7.begin(), list_8, --list_8.end());
        CPPUNIT_ASSERT(list_8.size() == 2);
        bool b_8 = false;
        try
        {
            i8++;
        }
        catch(const stl::exception&)
        {
            b_8 = true;
        }
        CPPUNIT_ASSERT(b_8 == true);
    }

    {
        //splice with invalid position
        list_debug list_1(3, -3), list_2(2, -2);
        bool b_1 = false;
        try
        {
            //1st iterator from different container
            list_1.splice(list_2.begin(), list_2, list_2.begin(), list_2.end());
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        //splice with first, last from different container than x
        bool b_2 = false;
        try
        {
            //first , last from different container
            list_1.splice(list_1.begin(), list_2, list_1.begin(), list_2.end());
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);

        //splice with invalid first, last container
        list_debug::iterator i3b, i3e;
        {
            list_debug list_3(3, -3);
            i3b = list_3.begin();
            i3e = list_3.end();
        }
        bool b_3 = false;
        try
        {
            //first, last invalid and also not of list_2 iterators
            list_1.splice(list_1.begin(), list_2, i3b, i3e);
        }
        catch(const stl::exception&)
        {
            b_3 = true;
        }
        CPPUNIT_ASSERT(b_3 == true);

        //splice with x == this, but with first, last invalid
        list_debug list_4(5, -5);
        list_debug::iterator i4f = list_4.begin();
        list_debug::iterator i4l = --list_4.end();
        list_4.erase(list_4.begin());
        list_4.erase(--list_4.end());
        bool b_4 = false;
        try
        {
            //first, last already erased from their container
            list_4.splice(list_4.begin(), list_4, i4f, i4l);
        }
        catch(const stl::exception&)
        {
            b_4 = true;
        }
        CPPUNIT_ASSERT(b_4 == true);

        //splice with x == this, and insert position iterator == ++first
        int i5t[5]={-1, -2, -3, -4, -5};
        list list_5(i5t, i5t+5);
        list::iterator i5pos = ++(++list_5.begin()); // -3
        list::iterator i5first = ++list_5.begin(); // -2
        list::iterator i5last = list_5.end();
        list_5.splice(i5pos, list_5, i5first, i5last); // no action required
        size_t j5 = 0;
        for(list::iterator i5beg = list_5.begin(); i5beg != list_5.end(); ++i5beg, ++j5)
            CPPUNIT_ASSERT(i5t[j5] == *i5beg);


        //splice with x == this, and lst iterator in [first, last) range by a bigger margin
        int i5t2[10] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};
        list list_5v2(i5t2, i5t2+10);
        list::iterator i5v2pos = ++(++(++(++list_5v2.begin()))); // -5
        list::iterator i5v2first = ++list_5v2.begin(); // -2
        list::iterator i5v2last = list_5v2.end();
        bool b_5v2 = false;
        try
        {
            list_5v2.splice(i5v2pos, list_5v2, i5v2first, i5v2last);
        }
        catch(const stl::exception& exc)
        {
            exc.what();
            b_5v2 = true;
        }
        CPPUNIT_ASSERT(b_5v2 == true);


        //position < first
        int i6t[5]={-1, -2, -3, -4, -5};
        list list_6(i6t, i6t+5);
        list::iterator i6pos = list_6.begin(); // -1
        list::iterator i6first = ++(++list_6.begin()); // -3
        list::iterator i6last = list_6.end();
        list_6.splice(i6pos, list_6, i6first, i6last);
        int i6t2[5]={-3, -4, -5, -1, -2};
        int j=0;
        for(list::iterator i6b = list_6.begin(); i6b != list_6.end(); ++i6b, ++j)
            CPPUNIT_ASSERT(*i6b == i6t2[j]);

        //position > last
        int i7t[5]={-1, -2, -3, -4, -5};
        list list_7(i7t, i7t+5);
        list::iterator i7pos = list_7.end();
        list::iterator i7first = ++(++list_7.begin()); // -3
        list::iterator i7last = --list_7.end(); // -5
        list_7.splice(i7pos, list_7, i7first, i7last);
        int i7t2[5]= {-1, -2, -5, -3, -4};
        j=0;
        for(list::iterator i7b = list_7.begin(); i7b != list_7.end(); ++i7b, ++j)
            CPPUNIT_ASSERT(*i7b == i7t2[j]);


        //position == last
        int i8t[5]={-1, -2, -3, -4, -5};
        list list_8(i8t, i8t+5);
        list::iterator i8pos = list_8.end();
        list::iterator i8first = ++(++list_8.begin()); // -3
        list::iterator i8last = list_8.end();
        bool b_8 = false;
        try
        {
            list_8.splice(i8pos, list_8, i8first, i8last);
        }
        catch(const stl::exception&)
        {
            b_8 = true;
        }
        CPPUNIT_ASSERT(b_8 == true);


        //iterators of x pointing in range [first,last) are invalid
        list_debug list_9(5, -5), list_9_1;
        list_debug::iterator i9first = list_9.begin();
        list_debug::iterator i9last = list_9.end();
        list_9_1.splice(list_9_1.end(), list_9, i9first, i9last);
        bool b_9 = false;
        try
        {
            int val = *i9first;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_9 = true;
        }
        CPPUNIT_ASSERT(b_9 == true);
    }

    stl::cout << "\n\n\tsplice-------------------------------------------------";
    splice<misc::list<double> >                         ("\n\tmisc::list   ");
    splice<std::list<double> >                          ("\n\tstd::list    ");
    splice<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::remove()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;


    list perflist;
    for(int i=0; i<(int)iSize; i++)
        perflist.push_back(i%2);
    perflist.remove(1);
    //////////////////////////////////////////////////////////////////////////

    int myints[]= {17,89,7,14};
    list mylist (myints,myints+4);

    mylist.remove(89);

    int myval[]={17, 7, 14};
    int pos = 0;
    for (list::iterator it=mylist.begin(); it!=mylist.end(); ++it, ++pos)
        CPPUNIT_ASSERT( *it == myval[pos] );


    //////////////////////////////////////////////////////////////////////////
    {
        // remove invalidates all iterators of the erased node
        int i0t[5]={-1, -2, -3, -4, -5};
        list_debug list_1(i0t, i0t+5);
        list_debug::const_reverse_iterator cri0 = ++(++(list_1.rbegin()));
        list_debug::const_reverse_iterator cri2 = cri0;
        CPPUNIT_ASSERT( *cri0 == -3);
        list_1.remove(-3);
        bool b_1 = false;
        try
        {
            int val = *cri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        bool b_2 = false;
        try
        {
            int val = *cri2;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    stl::cout << "\n\n\tremove-------------------------------------------------";
    remove<misc::list<double> >                         ("\n\tmisc::list   ");
    remove<std::list<double> >                          ("\n\tstd::list    ");
    remove<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

//////////////////////////////////////////////////////////////////////////

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
class is_odd
{
public:
    bool operator() (const int& value) {return (value%2)==1; }
};

//////////////////////////////////////////////////////////////////////////


void test_list::remove_if()
{
    typedef misc::list<int> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    list perflist;
    for(int i=0; i<(int)iSize; ++i)
        perflist.push_back(i%20);
    perflist.remove_if(single_digit);
    perflist.remove_if(is_odd());
    //////////////////////////////////////////////////////////////////////////

    int myints[]= {15,36,7,17,20,39,4,1};
    list mylist (myints,myints+8);   // 15 36 7 17 20 39 4 1

    mylist.remove_if (single_digit);      // 15 36 17 20 39

    mylist.remove_if (is_odd());          // 36 20

    int myval[]={36, 20};
    size_t pos = 0;
    for (list::iterator it=mylist.begin(); it!=mylist.end(); ++it, ++pos)
        CPPUNIT_ASSERT( *it == myval[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        // remove_if invalidates all iterators of the erased node
        int i0t[5]={1, 2, 3, 4, 5};
        list_debug list_1(i0t, i0t+5);
        list_debug::const_reverse_iterator cri0 = ++(++(list_1.rbegin()));
        list_debug::const_reverse_iterator cri2 = cri0;
        CPPUNIT_ASSERT( *cri0 == 3);
        list_1.remove_if(is_odd());
        bool b_1 = false;
        try
        {
            int val = *cri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
        bool b_2 = false;
        try
        {
            int val = *cri2;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    stl::cout << "\n\n\tremove_if----------------------------------------------";
    remove_if<misc::list<int> >                      ("\n\tmisc::list   ");
    remove_if<std::list<int> >                       ("\n\tstd::list    ");
    remove_if<std::list<int, misc::allocator<int> > >("\n\tstd::list<A> ");
}


//////////////////////////////////////////////////////////////////////////

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{
    return ( int(first)==int(second) );
}

// a binary predicate implemented as a class:
class is_near
{
public:
    bool operator() (double first, double second)
    {
        return (fabs(first-second) < 5.0);
    }
};

//////////////////////////////////////////////////////////////////////////

void test_list::unique()
{
    typedef misc::list<double> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    srand(500);
    //const int iSize = 10000;
    list perflist;
    for(int i=0; i<(int)iSize; ++i)
        perflist.push_back( (int)(rand() % (iSize/2)) );
    perflist.sort();
    perflist.unique();
    perflist.unique( same_integral_part );
    perflist.unique( is_near() );
    //////////////////////////////////////////////////////////////////////////

    double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14, 12.77, 73.35, 72.25, 15.3,  72.25 };
    list mylist(mydoubles, mydoubles+10);

    mylist.sort();        //  2.72,  3.14, 12.15, 12.77, 12.77, 15.3,  72.25, 72.25, 73.0, 73.35

    mylist.unique();      //  2.72,  3.14, 12.15, 12.77, 15.3,  72.25, 73.0,  73.35

    mylist.unique (same_integral_part);
    //  2.72,  3.14, 12.15, 15.3,  72.25, 73.0

    mylist.unique (is_near());
    //  2.72, 12.15, 72.25

    double myval[] = {2.72, 12.15, 72.25};
    size_t pos = 0;
    for (list::iterator it=mylist.begin(); it!=mylist.end(); ++it, ++pos)
        CPPUNIT_ASSERT( *it == myval[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        // unique should invalidate iterators of erased elements
        int i0t[5]={-1, 2, 3, 3, 5};
        list_debug list_1(i0t, i0t+5);
        list_debug::reverse_iterator ri0 = ++list_1.rbegin();
        list_1.unique();
        bool b_1 = false;
        try
        {
            int val = (int)*ri0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tunique-------------------------------------------------";
    unique<misc::list<double> >                         ("\n\tmisc::list   ");
    unique<std::list<double> >                          ("\n\tstd::list    ");
    unique<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}


//////////////////////////////////////////////////////////////////////////

// this compares equal two doubles if
//  their integer equivalents are equal
bool mycomparison (double first, double second)
{
    return (int) first < (int) second ;
}

//////////////////////////////////////////////////////////////////////////


void test_list::merge()
{
    typedef misc::list<double> list;
    typedef misc::list<
        int,
        misc::allocator<int>,
        misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;



    //const int iSize = 10000;
    list perflist1, perflist2;
    for(int i=0; i<(int)iSize; i+=2)
    {
        perflist1.push_back( i );
        perflist2.push_back( i+1 );
    }
    //sadly msvc requires sorted list in debug to do merge.
    perflist1.merge(perflist2);
    //////////////////////////////////////////////////////////////////////////


    list first, second;

    first.push_back (3.1);
    first.push_back (2.2);
    first.push_back (2.9);

    second.push_back (3.7);
    second.push_back (7.1);
    second.push_back (1.4);

    first.sort();
    second.sort();
    first.merge(second);
    second.push_back (2.1);
    first.merge(second,mycomparison);

    double myval[]={1.4, 2.2, 2.9, 2.1, 3.1, 3.7, 7.1};
    size_t pos = 0;
    for (list::iterator it=first.begin(); it!=first.end(); ++it, ++pos)
        CPPUNIT_ASSERT( *it == myval[pos] );

    //////////////////////////////////////////////////////////////////////////
    {
        int i0t[5]={1, 3, 5, 7, 9};
        list_debug list_1(i0t, i0t+5);

        int i2t[5]={2, 4, 6, 8, 10};
        list_debug list_2(i2t, i2t+5);

        list_debug::const_iterator ci0 = list_1.begin();
        list_debug::reverse_iterator ri2 = ++list_2.rbegin(); // 8
        list_1.merge(list_2);

        bool b_1 = false;
        try
        {
            int val = (int)*ci0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        bool b_2 = false;
        try
        {
            int val = (int)*ri2;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    // merge version with a predicate
    {
        int i0t[5]={1, 3, 5, 7, 9};
        list_debug list_1(i0t, i0t+5);

        int i2t[5]={2, 4, 6, 8, 10};
        list_debug list_2(i2t, i2t+5);

        list_debug::const_iterator ci0 = list_1.begin();
        list_debug::reverse_iterator ri2 = ++list_2.rbegin(); // 8
        list_1.merge(list_2, misc::less<double>());

        bool b_1 = false;
        try
        {
            int val = (int)*ci0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);

        bool b_2 = false;
        try
        {
            int val = (int)*ri2;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_2 = true;
        }
        CPPUNIT_ASSERT(b_2 == true);
    }

    stl::cout << "\n\n\tmerge--------------------------------------------------";
    merge<misc::list<double> >                         ("\n\tmisc::list   ");
    merge<std::list<double> >                          ("\n\tstd::list    ");
    merge<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}


//////////////////////////////////////////////////////////////////////////
// comparison, not case sensitive.

//TODO: "check this upon debugging if alright"

bool compare_nocase (stl::string first, stl::string second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    if (first.length()<second.length()) return true;
    else return false;
}


void test_list::sort()
{
//TODO: "poate merge si wchar_t sau altceva"

    typedef misc::list<stl::string> list;


    srand(700);

    //const int iSize = 10000;
    list perflist1;
    for(int i=0; i<(int)iSize; ++i)
    {
        perflist1.push_back( stl::from_value((int)(rand() % iSize)).c_str() );
    }
    perflist1.sort();
    //////////////////////////////////////////////////////////////////////////


    list mylist;
    list::iterator it;
    mylist.push_back("one");
    mylist.push_back("two");
    mylist.push_back("Three");

    mylist.sort();
    size_t pos = 0;
    for(it = mylist.begin(); it != mylist.end(); ++it, ++pos)
    {
        if(pos == 0) CPPUNIT_ASSERT( *it == "Three" );
        else if(pos == 1) CPPUNIT_ASSERT( *it == "one" );
        else if(pos == 2) CPPUNIT_ASSERT( *it == "two" );
        else CPPUNIT_ASSERT(false);
    }

    mylist.sort(compare_nocase);
    pos = 0;
    for(it = mylist.begin(); it != mylist.end(); ++it, ++pos)
    {
        if(pos == 0) CPPUNIT_ASSERT( *it == "one" );
        else if(pos == 1) CPPUNIT_ASSERT( *it == "Three" );
        else if(pos == 2) CPPUNIT_ASSERT( *it == "two" );
        else CPPUNIT_ASSERT(false);
    }

    //////////////////////////////////////////////////////////////////////////
    {
        typedef misc::list<
            int,
            misc::allocator<int>,
            misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;

        int i0t[5]={9, 3, 7, 5, 1};
        list_debug list_1(i0t, i0t+5);

        list_debug::const_iterator ci0 = list_1.begin(); // 9
        list_1.sort();

        bool b_1 = false;
        try
        {
            int val = *ci0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    // sort with predicate
    {
        typedef misc::list<
            int,
            misc::allocator<int>,
            misc::GENERIC_LIST_HAS_ITERATOR_DEBUGGING>  list_debug;


        int i0t[5]={9, 3, 7, 5, 1};
        list_debug list_1(i0t, i0t+5);

        list_debug::const_iterator ci0 = list_1.begin(); // 9
        list_1.sort(misc::less<int>());

        bool b_1 = false;
        try
        {
            int val = *ci0;
            (void)val;
        }
        catch(const stl::exception&)
        {
            b_1 = true;
        }
        CPPUNIT_ASSERT(b_1 == true);
    }

    stl::cout << "\n\n\tsort---------------------------------------------------";
    sort<misc::list<double> >                         ("\n\tmisc::list   ");
    sort<std::list<double> >                          ("\n\tstd::list    ");
    sort<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}

void test_list::reverse()
{
    typedef misc::list<int> list;

    srand(800);

    //const int iSize = 10000;
    list perflist1;
    for(int i=0; i<(int)iSize; ++i)
    {
        perflist1.push_back( rand() % iSize );
    }
    perflist1.reverse();
    //////////////////////////////////////////////////////////////////////////
    list mylist;
    list::iterator it;

    for (int i=1; i<10; i++) mylist.push_back(i);

    mylist.reverse();

    size_t val = 9;
    for (it=mylist.begin(); it!=mylist.end(); ++it, --val)
        CPPUNIT_ASSERT( *it == (int)val );

    val=1;
    for(it=--mylist.end(); ; --it, val++)
    {
        CPPUNIT_ASSERT(*it == (int)val);
        if(it == mylist.begin())
            break;
    }

    //////////////////////////////////////////////////////////////////////////
    {
        int i0t[5]={-1, -2, -3, -4, -5};
        list list_1(i0t, i0t+5);

        list::reverse_iterator ri0 = list_1.rbegin();
        list_1.reverse();
        CPPUNIT_ASSERT( *ri0 == -5 );
    }

    stl::cout << "\n\n\treverse------------------------------------------------";
    reverse<misc::list<double> >                         ("\n\tmisc::list   ");
    reverse<std::list<double> >                          ("\n\tstd::list    ");
    reverse<std::list<double, misc::allocator<double> > >("\n\tstd::list<A> ");
}
//test end



template<typename Container>
void test_list::ctor(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container* list;
    //  TEST
    {
        time_printer tp(msg, m_print_time);


        list = new Container(m_container_size, Cval(22.0));
    }
    delete list;
}


template<typename Container>
void test_list::dtor(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container* list = new Container(m_container_size, Cval(0));
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        delete list;
    }
}

template<typename Container>
void test_list::cpy_op(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0, list_2;
    for(size_t i=0; i < m_container_size; ++i)
    {
        list_0.push_back( Cval(::rand()) );
    }

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_2 = list_0;
    }
}

template<typename Container>
void test_list::begin(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list_0(m_container_size, Cval(0));
    It it_0[m_container_size];

    // requesting always begin() wouldn't be a problem.
    // retaining copies of all iterators would be interesting to see how much
    // slowdown we get by creating this iterators.

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i0 = 0; i0 < m_container_size; ++i0)
            it_0[i0] = list_0.begin();
    }
}

template<typename Container>
void test_list::end(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list_0(m_container_size, Cval(0));
    It it_0[m_container_size];

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i0 = 0; i0 < list_0.size(); ++i0)
            it_0[i0] = list_0.end();
    }
}

template<typename Container>
void test_list::rbegin(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::reverse_iterator Rit;

    Container list_0(m_container_size, Cval(0));
    Rit it_0[m_container_size];

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i0 = 0; i0 < list_0.size(); ++i0)
            it_0[i0] = list_0.rbegin();
    }
}

template<typename Container>
void test_list::rend(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::reverse_iterator Rit;

    Container list_0(m_container_size, Cval(0));
    Rit it_0[m_container_size];

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i0 = 0; i0 < list_0.size(); ++i0)
            it_0[i0] = list_0.rend();
    }
}

template<typename Container>
void test_list::resize(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list_0(m_container_size, Cval(0));
    It it_0[m_container_size];

    // resize a list with a lot of iterators retained
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.resize(1, Cval(-1));
    }
}

template<typename Container>
void test_list::assign(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0, list_2;
    for(size_t i=0; i < m_container_size; ++i)
    {
        list_0.push_back( Cval(::rand()) );
    }

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_2.assign(list_0.begin(), list_0.end());
    }
}

template<typename Container>
void test_list::push_front(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0;
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i = 0; i < m_container_size; ++i)
            list_0.push_front(Cval(i));
    }
}

template<typename Container>
void test_list::pop_front(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0(m_container_size, Cval(0));

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        while( !list_0.empty() )
            list_0.pop_front();
    }
}

template<typename Container>
void test_list::push_back(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0;
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i=0; i < m_container_size; ++i)
            list_0.push_back(Cval(i));
    }
}

template<typename Container>
void test_list::pop_back(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0(m_container_size, Cval(0));
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        while( !list_0.empty() )
            list_0.pop_back();
    }
}

template<typename Container>
void test_list::insert(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0;
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        for(size_t i=0; i < m_container_size/4; ++i)
            list_0.insert(list_0.end(), Cval(::rand()) );

        list_0.insert(list_0.begin(), ++list_0.begin(), list_0.end());
        list_0.insert(list_0.begin(), m_container_size/4, Cval(::rand()) );
    }
}

template<typename Container>
void test_list::erase(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list_0(m_container_size/4, Cval(-1));
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.erase(list_0.begin(), list_0.end());
    }
}

template<typename Container>
void test_list::swap(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    Container list_sw0;


    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_sw0.swap(list_0);
    }
}

template<typename Container>
void test_list::clear(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.clear();
    }
}

template<typename Container>
void test_list::splice(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    Container list_sw0;
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_sw0.splice(list_sw0.end(), list_0, list_0.begin());
        list_sw0.splice(list_sw0.end(), list_0, list_0.begin(), list_0.end());
    }
}


template<typename Container>
void test_list::remove(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;


    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.remove(Cval(3));
    }
}

template<typename Container>
void test_list::remove_if(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;


    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.remove_if(is_odd());
    }
}

template<typename Container>
void test_list::unique(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    // will test how much slowdown will bring the iterators when swapping
    Container list_0(m_container_size, Cval(3));
    It it_0[m_container_size];
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;


    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.unique();
    }
}

template<typename Container>
void test_list::merge(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;


    Container list_0, list_0_0;

    // fill the containers
    for(size_t i=0; i < m_container_size; ++i)
    {
        if(i%2==1) // odd
        {
            list_0.push_back(i);
        }
        else // even
        {
            list_0_0.push_back(i);
        }
    }

    It it_0[m_container_size/2+1];

    // retain iterators of container that is to be merged into the other one.
    It i0b = list_0_0.begin();
    for(size_t i0 = 0; i0b != list_0_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    // merge 2nd container into 1st one.
    // test how the iterators influence the performance of merge

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.merge(list_0_0, misc::less<Cval>());
    }

}

template<typename Container>
void test_list::sort(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list_0;

    // fill the containers
    for(size_t i=0; i < m_container_size; ++i)
        list_0.push_back( Cval(::rand()) );

    It it_0[m_container_size];

    // retain iterators of container that is to be merged into the other one.
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    // merge 2nd container into 1st one.
    // test how the iterators influence the performance of merge

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.sort(misc::less<double>());
    }
}

template<typename Container>
void test_list::reverse(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list_0;

    // fill the containers
    for(size_t i=0; i < m_container_size; ++i)
        list_0.push_back( Cval(::rand()) );

    It it_0[m_container_size];

    // retain iterators of container that is to be merged into the other one.
    It i0b = list_0.begin();
    for(size_t i0 = 0; i0b != list_0.end(); ++i0b, ++i0)
        it_0[i0] = i0b;

    // merge 2nd container into 1st one.
    // test how the iterators influence the performance of merge

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        list_0.reverse();
    }
}


//////////////////////////////////////////////////////////////////////////
