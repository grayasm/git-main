/*
Copyright (C) 2012 Mihai Vasilian
*/



//this
#include "test_utility.hpp"

//c++ ...
#include <utility>
#include <list>
#include <vector>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries ...
#include "utility.hpp"
#include "vector.hpp"
#include "list.hpp"
#include "deque.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_utility::setUp()
{
}

void test_utility::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_utility::pair_ctor()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: utility.hpp                         *";
    stl::cout <<   "\n\t*******************************************************";

	
	
    typedef stl::pair<int,int> Pair;
    typedef stl::vector<Pair> Vec;
    typedef misc::list<Pair> Lst;

    
    stl::cout << "\n\n\tmisc::pair ctor----------------------------------------";

    pair_ctor<Vec,Pair>("\n\tpair_ctor<stl::vector<stl::pair> >   ");
    pair_ctor<Lst,Pair>("\n\tpair_ctor<misc::list<stl::pair> >     ");
}

void test_utility::make_pair()
{
    typedef stl::pair<int,int> Pair;
    typedef stl::vector<Pair> Vec;
    typedef misc::list<Pair> Lst;

    stl::cout << "\n\n\tmisc::make_pair----------------------------------------";

    make_pair<Vec,Pair>("\n\tmake_pair<stl::vector<stl::pair> >   ");
    make_pair<Lst,Pair>("\n\tmake_pair<misc::list<stl::pair> >     ");
}

void test_utility::rel_ops()
{
    typedef stl::pair<int,int> Pair;
    typedef stl::vector<Pair> Vec;
    typedef misc::list<Pair> Lst;

    stl::cout << "\n\n\tmisc::rel_ops------------------------------------------";

    rel_ops<Vec,Pair>("\n\tmake_pair<stl::vector<stl::pair> >   ");
    rel_ops<Lst,Pair>("\n\tmake_pair<misc::list<stl::pair> >     ");
}

void test_utility::it_traits()
{
    stl::cout << "\n\n\tmisc::iterator_traits<Iterator>------------------------";

    it_traits<stl::vector<bool> >          ("\n\ttraits<stl::vector<bool>>          ");
    it_traits<stl::vector<char> >          ("\n\ttraits<stl::vector<char>>          ");
    it_traits<stl::vector<signed char> >   ("\n\ttraits<stl::vector<signed char>>   ");
    it_traits<stl::vector<unsigned char> > ("\n\ttraits<stl::vector<unsigned char>> ");
    it_traits<stl::vector<wchar_t> >       ("\n\ttraits<stl::vector<wchar_t>>       ");
    it_traits<stl::vector<short> >         ("\n\ttraits<stl::vector<short>>         ");
    it_traits<stl::vector<unsigned short> >("\n\ttraits<stl::vector<unsigned short> ");
    it_traits<stl::vector<int> >           ("\n\ttraits<stl::vector<int>>           ");
    it_traits<stl::vector<unsigned int> >  ("\n\ttraits<stl::vector<unsigned int>>  ");
    it_traits<stl::vector<long> >          ("\n\ttraits<stl::vector<long>>          ");
    it_traits<stl::vector<unsigned long> > ("\n\ttraits<stl::vector<unsigned long>> ");
    it_traits<stl::vector<double> >        ("\n\ttraits<stl::vector<double>>        ");
    it_traits<stl::vector<float> >         ("\n\ttraits<stl::vector<float>>         ");
    it_traits<stl::vector<long long> >     ("\n\ttraits<stl::vector<long long>L     ");
}

void test_utility::if_class()
{
    stl::cout << "\n\n\tmisc::If<bool,T1,T2>-----------------------------------";

    if_class<int, long>("\n\tif_class <int,long>   ");
}

void test_utility::advance()
{
    stl::cout << "\n\n\tmisc::advance------------------------------------------";

    advance<stl::vector<int> >("\n\tadvance<stl::vector<int> >   ");
    advance<misc::list<int> >  ("\n\tadvance<misc::list<int> >     ");
}

void test_utility::distance()
{
    stl::cout << "\n\n\tmisc::distance-----------------------------------------";

    distance<stl::vector<int> >("\n\tdistance<stl::vector<int> > ");
    distance<misc::list<int> >  ("\n\tdistance<misc::list<int> >   ");
}

void test_utility::back_insert_it()
{
    stl::cout << "\n\n\tmisc::back_insert_iterator<Container>------------------";

    back_insert_it<stl::vector<int> >("\n\tback_insert_it<stl::vector<int> > ");
    back_insert_it<misc::list<int> >  ("\n\tback_insert_it<misc::list<int> >   ");
}

void test_utility::front_insert_it()
{
    stl::cout << "\n\n\tmisc::front_insert_iterator<Container>-----------------";

    front_insert_it<misc::deque<int> > ("\n\tfront_insert_it<stl::vector<int> > ");
    front_insert_it<misc::list<int> >  ("\n\tfront_insert_it<misc::list<int> >   ");
}

void test_utility::insert_it()
{
    stl::cout << "\n\n\tmisc::insert_iterator<Container>-----------------------";

    insert_it<stl::vector<int> >("\n\tinsert_it<stl::vector<int> > ");
    insert_it<misc::list<int> >  ("\n\tinsert_it<misc::list<int> >   ");
}


//################################################################################
//template version of test function
template<typename Container, typename Pair>
void test_utility::pair_ctor(const char* msg)
{
    typedef typename Pair::first_type FVal;
    typedef typename Pair::second_type SVal;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Pair(FVal(0),SVal(0)));
        size_t i(0);
        for(It it = v0.begin(); it != v0.end(); ++it, ++i)
        {
            *it = Pair(FVal(i), SVal(v0.size()-i-1));
        }

        Container v2(v0);

        CPPUNIT_ASSERT(v0.size() == v2.size());

        for(It it=v0.begin(), it2=v2.begin() ; it != v0.end(); ++it, ++it2)
        {
            CPPUNIT_ASSERT(it->first == it2->first);
            CPPUNIT_ASSERT(it->second == it2->second);
        }
    }
}

template<typename Container, typename Pair>
void test_utility::make_pair(const char* msg)
{
    typedef typename Pair::first_type FVal;
    typedef typename Pair::second_type SVal;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Pair(FVal(0),SVal(0)));
        size_t i(0);
        for(It it = v0.begin(); it != v0.end(); ++it, ++i)
        {
            *it = misc::make_pair(FVal(i), SVal(v0.size()-i-1));
        }

        Container v2(v0);

        CPPUNIT_ASSERT(v0.size() == v2.size());

        for(It it=v0.begin(), it2=v2.begin() ; it != v0.end(); ++it, ++it2)
        {
            CPPUNIT_ASSERT(it->first == it2->first);
            CPPUNIT_ASSERT(it->second == it2->second);
        }
    }
}

template<typename Container, typename Pair>
void test_utility::rel_ops(const char* msg)
{
    typedef typename Pair::first_type FVal;
    typedef typename Pair::second_type SVal;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Pair(FVal(0),SVal(0)));
        size_t i(0);
        for(It it = v0.begin(); it != v0.end(); ++it, ++i)
        {
            *it = misc::make_pair(FVal(i), SVal(v0.size()-i-1));
        }

        Container v2(v0);

        CPPUNIT_ASSERT(v0.size() == v2.size());

        for(It it=v0.begin(), it2=v2.begin() ; it != v0.end(); ++it, ++it2)
        {
            using namespace misc::rel_ops;

            CPPUNIT_ASSERT(!(it->first != it2->first));
            CPPUNIT_ASSERT(!(it->second > it2->second));
            CPPUNIT_ASSERT(it->first <= it2->first);
            CPPUNIT_ASSERT(it->first >= it2->first);
        }
    }
}

template<typename Container>
void test_utility::it_traits(const char* msg)
{
	typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Cval(0));

        It it = v0.begin();
        typename misc::iterator_traits<It>::value_type val = *it;
        typename misc::iterator_traits<It>::iterator_category cat, cat2;
        typename misc::iterator_traits<It>::difference_type diff = &val - &(*it);
        typename misc::iterator_traits<It>::pointer ptr = &val;
        typename misc::iterator_traits<It>::reference ref = val;
        // check compilation
        cat2 = cat;
        CPPUNIT_ASSERT(val == 0);
        CPPUNIT_ASSERT(diff != 0);
        CPPUNIT_ASSERT(*ptr == 0);
        CPPUNIT_ASSERT(ref == 0);
        CPPUNIT_ASSERT(true);
    }
}

template<typename T0, typename T2>
void test_utility::if_class(const char* msg)
{
    //  TEST
    {
        time_printer tp(msg, m_print_time);
        T0 t0 = (T0)::rand();
        T2 t2 = (T2)::rand();
        typename misc::If<1 == 1, T0, T2>::result final = t0;
        // result evaluates to T0
        // solve compiler warnings
        t0++;
        t2++;
        final++;

        CPPUNIT_ASSERT(true);
    }
}

template<typename Container>
void test_utility::advance(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Cval(0));

        It it = v0.begin();
        misc::advance(it, m_container_size, typename misc::iterator_traits<It>::iterator_category());

        CPPUNIT_ASSERT(it == v0.end());
    }
}

template<typename Container>
void test_utility::distance(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0(m_container_size, Cval(0));

        typename misc::iterator_traits<It>::difference_type diff =
            misc::distance(v0.begin(), v0.end(), typename misc::iterator_traits<It>::iterator_category());

        CPPUNIT_ASSERT(diff == m_container_size);
    }
}

template<typename Container>
void test_utility::back_insert_it(const char* msg)
{
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0;

        misc::back_insert_iterator<Container> biIt =
            misc::back_inserter(v0);

        for(size_t i=0; i < m_container_size; ++i, ++biIt)
        {
            biIt = i;
        }

        CPPUNIT_ASSERT(v0.size() == m_container_size);
    }
}

template<typename Container>
void test_utility::front_insert_it(const char* msg)
{
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0;

        misc::front_insert_iterator<Container> fiIt =
            misc::front_inserter(v0);

        for(size_t i=0; i < m_container_size; ++i, ++fiIt)
        {
            fiIt = i;
        }

        CPPUNIT_ASSERT(v0.size() == m_container_size);
    }
}

template<typename Container>
void test_utility::insert_it(const char* msg)
{
    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Container v0;

        misc::insert_iterator<Container> fiIt =
            misc::inserter(v0, v0.begin());

        for(size_t i=0; i < m_container_size; ++i, ++fiIt)
        {
            fiIt = i;
        }

        CPPUNIT_ASSERT(v0.size() == m_container_size);
    }
}

//////////////////////////////////////////////////////////////////////////
