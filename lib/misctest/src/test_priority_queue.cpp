/*
Copyright (C) 2012 Mihai Vasilian
*/




//this
#include "test_priority_queue.hpp"

//c++ ...
#include <queue>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "functional.hpp"
#include "queue.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"



//###########################BEGIN TEST CLASS ####################################
void test_priority_queue::setUp()
{
}

void test_priority_queue::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_priority_queue::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: priority_queue.hpp                  *";
    stl::cout <<   "\n\t*******************************************************";

    stl::cout << "\n\n\tctor---------------------------------------------------";
    ctor<std::priority_queue<int>, std::less<int> >   ("\n\tctor<std::priority_queue<int>,less<int> >  ");
    ctor<misc::priority_queue<int>, misc::less<int> > ("\n\tctor<misc::priority_queue<int>,less<int> > ");
}

void test_priority_queue::dtor()
{
    stl::cout << "\n\n\tdtor---------------------------------------------------";
    dtor<std::priority_queue<int>, std::less<int> >  ("\n\tdtor<std::priority_queue<int>,less<int> >  ");
    dtor<misc::priority_queue<int>, misc::less<int> >("\n\tdtor<misc::priority_queue<int> >,less<int> ");
}

void test_priority_queue::empty()
{
    stl::cout << "\n\n\tempty--------------------------------------------------";
    empty<std::priority_queue<int>, std::less<int> >  ("\n\tempty<std::priority_queue<int>,less<int> >  ");
    empty<misc::priority_queue<int>, misc::less<int> >("\n\tempty<misc::priority_queue<int>,less<int> > ");
}

void test_priority_queue::size()
{
    stl::cout << "\n\n\tsize---------------------------------------------------";
    size<std::priority_queue<int>, std::less<int> >  ("\n\tsize<std::priority_queue<int>,less<int> >  ");
    size<misc::priority_queue<int>, misc::less<int> >("\n\tsize<misc::priority_queue<int>,less<int> > ");
}

void test_priority_queue::top()
{
    stl::cout << "\n\n\ttop----------------------------------------------------";
    top<std::priority_queue<int>, std::less<int> >  ("\n\ttop<std::priority_queue<int>,less<int> >  ");
    top<misc::priority_queue<int>, misc::less<int> >("\n\ttop<misc::priority_queue<int>,less<int> > ");
}

void test_priority_queue::push()
{
    stl::cout << "\n\n\tpush---------------------------------------------------";
    push<std::priority_queue<int>, std::less<int> >  ("\n\tpush<std::priority_queue<int>,less<int> >  ");
    push<misc::priority_queue<int>, misc::less<int> >("\n\tpush<misc::priority_queue<int>,less<int> > ");
}

void test_priority_queue::pop()
{
    stl::cout << "\n\n\tpop----------------------------------------------------";
    pop<std::priority_queue<int>, std::less<int> >  ("\n\tpop<std::priority_queue<int>,less<int> >  ");
    pop<misc::priority_queue<int>, misc::less<int> >("\n\tpop<misc::priority_queue<int>,less<int> > ");
}

//################################################################################
//template version of test function
template<typename Container, typename Compare>
void test_priority_queue::ctor(const char* msg)
{
	typedef typename Container::value_type		Cval;
    typedef typename Container::container_type TCont;
    typedef Compare                     TCmp;

	
	// initialization data		
	Cval chtab[255];
	chtab[254]=0;
	for(size_t i = 0; i < 254; ++i)
	{
		chtab[i] = Cval(i+1); // we iterate also with float,double,etc			
	}

    // measure only the time for constructors
    stl::vector<Container*> store;

    //  TEST
    {
        time_printer tp(msg, m_print_time);


        for(size_t i=0; i < m_container_size; ++i)
        {
            Container* array0 = new Container(TCmp(), TCont());
            store.push_back(array0);

            const Container& array2 = *array0;
            const Container* array3 = new Container(array2);//copy-ctor
            store.push_back(const_cast<Container*>(array3));
        }
    }


    // calling ~dtor()
    for(size_t i=0; i < store.size(); ++i)
    {
        delete store[i];
    }
}

template<typename Container, typename Compare>
void test_priority_queue::dtor(const char* msg)
{
    // preserving the code from ctor<Container>(...)
    // and measuring the destructor
	typedef typename Container::value_type Cval;
    typedef typename Container::container_type TCont;
    typedef Compare                     TCmp;

	// initialization data		
	Cval chtab[255]; /*NULL terminated*/ chtab[254]=0;
	for(size_t i = 0; i < 254; ++i)
	{
		chtab[i] = Cval(i+1); // we iterate also with float,double,etc			
	}

    stl::vector<Container*> store;

    //  Create containers, will take the time of ~dtor()
    for(size_t i=0; i < m_container_size; ++i)
    {
        Container* array0 = new Container(TCmp(), TCont());
        store.push_back(array0);

        const Container& array2 = *array0;
        const Container* array3 = new Container(array2);//copy-ctor
        store.push_back(const_cast<Container*>(array3));
    }

    //  TEST
    {
        time_printer tp(msg, m_print_time);

        // calling ~dtor()
        for(size_t i=0; i < store.size(); ++i)
        {
            delete store[i];
        }
    }
}

template<typename Container, typename Compare>
void test_priority_queue::empty(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;
    typedef Compare                     TCmp;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(TCmp(), aux);

        CPPUNIT_ASSERT(cont.empty() == false);

        size_t sz = 0;
        do
        {
            cont.pop();
            sz = cont.size();

        } while (sz > 0);

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container, typename Compare>
void test_priority_queue::size(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;
    typedef Compare                     TCmp;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(TCmp(), aux);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        while(cont.size() > 0)
            cont.pop();

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container, typename Compare>
void test_priority_queue::top(const char* msg)
{
    typedef typename Container::value_type CVal;
    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
        {
			CPPUNIT_ASSERT(cont.size() == i);
            cont.push(i);
            CPPUNIT_ASSERT(cont.top() == i);
        }
    }
}

template<typename Container, typename Compare>
void test_priority_queue::push(const char* msg)
{
    typedef typename Container::value_type       CVal;
	{
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
        {
			CPPUNIT_ASSERT(cont.size() == i);
            cont.push(i);
            CPPUNIT_ASSERT(cont.top() == i);
        }
    }
}

template<typename Container, typename Compare>
void test_priority_queue::pop(const char* msg)
{
    typedef typename Container::value_type     CVal;
    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        size_t i=m_container_size-1;
        while(!cont.empty())
        {
			CPPUNIT_ASSERT(cont.top() == i);			
            cont.pop();
            CPPUNIT_ASSERT(cont.size() == i--);
        }

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}


//################################################################################
