/*
Copyright (C) 2012 Mihai Vasilian
*/

//this
#include "test_stack.hpp"

//c++ ...
#include <stack>


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
#include "stack.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_stack::setUp()
{
}

void test_stack::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_stack::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: stack.hpp                           *";
    stl::cout <<   "\n\t*******************************************************";

    stl::cout << "\n\n\tctor---------------------------------------------------";

    ctor<std::stack<int> > ("\n\tctor<std::stack<int> >  ");
    ctor<misc::stack<int> >("\n\tctor<misc::stack<int> > ");
}

void test_stack::dtor()
{
    stl::cout << "\n\n\tdtor---------------------------------------------------";
    dtor<std::stack<int> > ("\n\tdtor<std::stack<int> >  ");
    dtor<misc::stack<int> >("\n\tdtor<misc::stack<int> > ");
}

void test_stack::empty()
{
    stl::cout << "\n\n\tempty--------------------------------------------------";
    empty<std::stack<int> > ("\n\tempty<std::stack<int> >  ");
    empty<misc::stack<int> >("\n\tempty<misc::stack<int> > ");
}

void test_stack::size()
{
    stl::cout << "\n\n\tsize---------------------------------------------------";

    size<std::stack<int> > ("\n\tsize<std::stack<int> >  ");
    size<misc::stack<int> >("\n\tsize<misc::stack<int> > ");
}

void test_stack::top()
{
    stl::cout << "\n\n\ttop----------------------------------------------------";

    top<std::stack<int> > ("\n\ttop<std::stack<int> >  ");
    top<misc::stack<int> >("\n\ttop<misc::stack<int> > ");
}

void test_stack::push()
{
    stl::cout << "\n\n\tpush---------------------------------------------------";

    push<std::stack<int> > ("\n\tpush<std::stack<int> >  ");
    push<misc::stack<int> >("\n\tpush<misc::stack<int> > ");
}

void test_stack::pop()
{
    stl::cout << "\n\n\tpop----------------------------------------------------";

    pop<std::stack<int> > ("\n\tpop<std::stack<int> >  ");
    pop<misc::stack<int> >("\n\tpop<misc::stack<int> > ");
}

void test_stack::eq_op()
{
    stl::cout << "\n\n\teq_op--------------------------------------------------";

    eq_op<std::stack<int> > ("\n\teq_op<std::stack<int> >  ");
    eq_op<misc::stack<int> >("\n\teq_op<misc::stack<int> > ");
}

void test_stack::neq_op()
{
    stl::cout << "\n\n\tneq_op-------------------------------------------------";

    neq_op<std::stack<int> > ("\n\tneq_op<std::stack<int> >  ");
    neq_op<misc::stack<int> >("\n\tneq_op<misc::stack<int> > ");
}

void test_stack::lt_op()
{
    stl::cout << "\n\n\tlt_op--------------------------------------------------";

    lt_op<std::stack<int> > ("\n\tlt_op<std::stack<int> >  ");
    lt_op<misc::stack<int> >("\n\tlt_op<misc::stack<int> > ");
}

void test_stack::gt_op()
{
    stl::cout << "\n\n\tgt_op--------------------------------------------------";

    gt_op<std::stack<int> > ("\n\tgt_op<std::stack<int> >  ");
    gt_op<misc::stack<int> >("\n\tgt_op<misc::stack<int> > ");
}

void test_stack::lte_op()
{
    stl::cout << "\n\n\tlte_op-------------------------------------------------";

    lte_op<std::stack<int> > ("\n\tlte_op<std::stack<int> >  ");
    lte_op<misc::stack<int> >("\n\tlte_op<misc::stack<int> > ");
}

void test_stack::gte_op()
{
    stl::cout << "\n\n\tgte_op-------------------------------------------------";

    gte_op<std::stack<int> > ("\n\tgte_op<std::stack<int> >  ");
    gte_op<misc::stack<int> >("\n\tgte_op<misc::stack<int> > ");
}


//################################################################################
//template version of test function
template<typename Container>
void test_stack::ctor(const char* msg)
{
    typedef typename Container::container_type   TCont;

    // measure only the time for constructors
    stl::vector<Container*> store;

    //  TEST
    {
        time_printer tp(msg, m_print_time);


        for(size_t i=0; i < m_container_size; ++i)
        {
            Container* array0 = new Container(TCont());
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

template<typename Container>
void test_stack::dtor(const char* msg)
{
    // preserving the code from ctor<Container>(...)
    // and measuring the destructor
    typedef typename Container::container_type TCont;


    stl::vector<Container*> store;

    //  Create containers, will take the time of ~dtor()
    for(size_t i=0; i < m_container_size; ++i)
    {
        Container* array0 = new Container(TCont());
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

template<typename Container>
void test_stack::empty(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(aux);

        CPPUNIT_ASSERT(cont.empty() == false);

        while(!cont.empty())
            cont.pop();

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container>
void test_stack::size(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(aux);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        while(cont.size() > 0)
            cont.pop();

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container>
void test_stack::top(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
            cont.push(i);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        for(CVal i=m_container_size; i>0; --i)
        {
            CPPUNIT_ASSERT(cont.top() == (i-1));
			CPPUNIT_ASSERT(cont.size() == i);
            cont.pop();
        }

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container>
void test_stack::push(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        for(CVal i=m_container_size; i>0; --i)
        {
            CPPUNIT_ASSERT(cont.top() == (i-1));
			CPPUNIT_ASSERT(cont.size() == i);
            cont.pop();
        }

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container>
void test_stack::pop(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);

        CPPUNIT_ASSERT(cont.size() == m_container_size);

        for(CVal i=m_container_size; i>0; --i)
        {
            CPPUNIT_ASSERT(cont.top() == (i-1));
			CPPUNIT_ASSERT(cont.size() == i);
            cont.pop();
        }

        CPPUNIT_ASSERT(cont.empty() == true);
    }
}

template<typename Container>
void test_stack::eq_op(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        CPPUNIT_ASSERT(cont == cont2);
    }
}

template<typename Container>
void test_stack::neq_op(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);
        cont2.pop();

        CPPUNIT_ASSERT(cont != cont2);
    }
}

template<typename Container>
void test_stack::lt_op(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        cont.pop();

        CPPUNIT_ASSERT(cont < cont2);
    }
}

template<typename Container>
void test_stack::gt_op(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);
        cont2.pop();

        CPPUNIT_ASSERT(cont > cont2);
    }
}

template<typename Container>
void test_stack::lte_op(const char* msg)
{
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        CPPUNIT_ASSERT(cont <= cont2);

        cont.pop();

        CPPUNIT_ASSERT(cont < cont2);
    }
}

template<typename Container>
void test_stack::gte_op(const char* msg)
{
    typedef typename Container::value_type     CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        CPPUNIT_ASSERT(cont >= cont2);

        cont2.pop();

        CPPUNIT_ASSERT(cont > cont2);
    }
}


//////////////////////////////////////////////////////////////////////////
