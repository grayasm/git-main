/*
Copyright (C) 2012 Mihai Vasilian
*/



//this
#include "test_numeric.hpp"

//c++ ...
#include <list>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries ...
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"
#include "numeric.hpp"
#include "functional.hpp"
#include "list.hpp"



//###########################BEGIN TEST CLASS ####################################
void test_numeric::setUp()
{
}

void test_numeric::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_numeric::accumulate()
{

    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: numeric.hpp                         *";
    stl::cout <<   "\n\t*******************************************************";

    stl::cout << "\n\n\taccumulate---------------------------------------------";

    accumulate<misc::list<int> >                      ("\n\tmisc::list<int> ");
    accumulate<std::list<int> >                       ("\n\tmisc::list<int> ");
    accumulate<std::list<int, misc::allocator<int> > >("\n\tstd::list<int,A>");
}

void test_numeric::adjacent_difference()
{
    stl::cout << "\n\n\tadjacent_difference------------------------------------";

    adjacent_difference<misc::list<int> >                      ("\n\tmisc::list<int> ");
    adjacent_difference<std::list<int> >                       ("\n\tmisc::list<int> ");
    adjacent_difference<std::list<int, misc::allocator<int> > >("\n\tstd::list<int,A>");

}

void test_numeric::inner_product()
{
    stl::cout << "\n\n\tinner_product------------------------------------------";

    inner_product<misc::list<int> >                      ("\n\tmisc::list<int> ");
    inner_product<std::list<int> >                       ("\n\tmisc::list<int> ");
    inner_product<std::list<int, misc::allocator<int> > >("\n\tstd::list<int,A>");
}

void test_numeric::partial_sum()
{
    stl::cout << "\n\n\tpartial_sum--------------------------------------------";

    partial_sum<misc::list<int> >                      ("\n\tmisc::list<int> ");
    partial_sum<std::list<int> >                       ("\n\tmisc::list<int> ");
    partial_sum<std::list<int, misc::allocator<int> > >("\n\tstd::list<int,A>");
}

//test end

//////////////////////////////////////////////////////////////////////////
//template version of test function
template<typename Container>
void test_numeric::accumulate(const char* msg)
{
    typedef typename Container::value_type Cval;

    Container list;
    for(size_t i=1; i <= m_container_size; ++i)
        list.push_back(Cval(i));

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Cval sum1 = misc::accumulate(list.begin(), list.end(), 5);
        Cval sum2 = misc::accumulate(list.begin(), list.end(), 5, misc::plus<Cval>());

        Cval sum0 = m_container_size * (m_container_size + 1)/2;
        CPPUNIT_ASSERT(sum1 == sum0+5);
        CPPUNIT_ASSERT(sum2 == sum0+5);
    }
}

template<typename Container>
void test_numeric::adjacent_difference(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;


    Container list_0;
    for(size_t i=1; i <= m_container_size; ++i)
        list_0.push_back(Cval(i));
    Container list_2(m_container_size, Cval(0));
    Container list_3(m_container_size, Cval(-1));

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        misc::adjacent_difference(list_0.begin(), list_0.end(), list_2.begin());
        misc::adjacent_difference(list_0.begin(), list_0.end(), list_3.begin(), misc::minus<Cval>());

        for(It it2 = list_2.begin(), it3 = list_3.begin();
            it2 != list_2.end(); ++it2, ++it3)
        {
            CPPUNIT_ASSERT(*it2 == Cval(1) && *it3 == Cval(1));
        }
    }
}

template<typename Container>
void test_numeric::inner_product(const char* msg)
{
    typedef typename Container::value_type Cval;
	
    Container list0, list2;
    for(size_t j=1; j <= m_container_size; ++j)
    {
        list0.push_back(Cval(j));
        list2.push_back(Cval(2));
    }

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        Cval iprod0 = misc::inner_product(list0.begin(), list0.end(), list2.begin(), 0);
        Cval iprod2 = misc::inner_product(list0.begin(), list0.end(), list2.begin(),
                                          0, misc::plus<Cval>(), misc::multiplies<Cval>());

        Cval sum0 = m_container_size * (m_container_size + 1)/2;
        CPPUNIT_ASSERT(iprod0 == sum0 * 2);
        CPPUNIT_ASSERT(iprod2 == sum0 * 2);
    }
}

template<typename Container>
void test_numeric::partial_sum(const char* msg)
{
    typedef typename Container::value_type Cval;
    typedef typename Container::iterator It;

    Container list;
    for(size_t j=1; j <= m_container_size; ++j)
        list.push_back(Cval(j));

    Container test0(m_container_size, Cval(0));
    Container test2(m_container_size, Cval(0));

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        misc::partial_sum(list.begin(), list.end(), test0.begin());
        misc::partial_sum(list.begin(), list.end(), test2.begin(), misc::plus<Cval>());

        for(It it = list.begin(), it0 = test0.begin(), it2 = test2.begin();
            it0 != test0.end(); ++it, ++it0, ++it2)
        {
            Cval n = *it;
            Cval sum = n*(n+1)/2;
            CPPUNIT_ASSERT(*it0 == sum);
            CPPUNIT_ASSERT(*it2 == sum);
        }
    }
}

//################################################################################
