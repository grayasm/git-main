/*
Copyright (C) 2012 Mihai Vasilian
*/


//this
#include "test_queue.hpp"

//c++ ...
#include <queue>

//acutest
#include "acutest.h"


//libraries ...
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"
#include "queue.hpp"
#include "stream.hpp"
#include "stltest_util.hpp"


//############################# BEGIN TEST #####################################
void test_queue::run()
{
    ctor();
    dtor();
    empty();
    size();
    front();
    back();
    push();
    pop();
    eq_op();
    neq_op();
    lt_op();
    gt_op();
    lte_op();
    gte_op();

    // new line before TEST RESULT OUTPUT
    stl::cout << "\n";
}

//##########################BEGIN TEST SUITE######################################
void test_queue::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: queue.hpp                           *";
    stl::cout <<   "\n\t*******************************************************";

    stl::cout << "\n\n\tctor---------------------------------------------------";
    ctor<std::queue<int> > ("\n\tctor<std::queue<int> >  ");
    ctor<stl::queue<int> >("\n\tctor<stl::queue<int> > ");
}

void test_queue::dtor()
{
    stl::cout << "\n\n\tdtor---------------------------------------------------";
    dtor<std::queue<int> > ("\n\tdtor<std::queue<int> >  ");
    dtor<stl::queue<int> >("\n\tdtor<stl::queue<int> > ");
}

void test_queue::empty()
{
    stl::cout << "\n\n\tempty--------------------------------------------------";
    empty<std::queue<int> > ("\n\tempty<std::queue<int> >  ");
    empty<stl::queue<int> >("\n\tempty<stl::queue<int> > ");
}

void test_queue::size()
{
    stl::cout << "\n\n\tsize---------------------------------------------------";
    size<std::queue<int> > ("\n\tsize<std::queue<int> >  ");
    size<stl::queue<int> >("\n\tsize<stl::queue<int> > ");
}

void test_queue::front()
{
    stl::cout << "\n\n\tfront--------------------------------------------------";
    front<std::queue<int> > ("\n\tfront<std::queue<int> >  ");
    front<stl::queue<int> >("\n\tfront<stl::queue<int> > ");
}

void test_queue::back()
{
    stl::cout << "\n\n\tback---------------------------------------------------";
    back<std::queue<int> > ("\n\tback<std::queue<int> >  ");
    back<stl::queue<int> >("\n\tback<stl::queue<int> > ");
}

void test_queue::push()
{
    stl::cout << "\n\n\tpush---------------------------------------------------";
    push<std::queue<int> > ("\n\tpush<std::queue<int> >  ");
    push<stl::queue<int> >("\n\tpush<stl::queue<int> > ");
}

void test_queue::pop()
{
    stl::cout << "\n\n\tpop----------------------------------------------------";
    pop<std::queue<int> > ("\n\tpop<std::queue<int> >  ");
    pop<stl::queue<int> >("\n\tpop<stl::queue<int> > ");
}

void test_queue::eq_op()
{
    stl::cout << "\n\n\teq_op--------------------------------------------------";
    eq_op<std::queue<int> > ("\n\teq_op<std::queue<int> >  ");
    eq_op<stl::queue<int> >("\n\teq_op<stl::queue<int> > ");
}

void test_queue::neq_op()
{
    stl::cout << "\n\n\tneq_op-------------------------------------------------";
    neq_op<std::queue<int> > ("\n\tneq_op<std::queue<int> >  ");
    neq_op<stl::queue<int> >("\n\tneq_op<stl::queue<int> > ");
}

void test_queue::lt_op()
{
    stl::cout << "\n\n\tlt_op--------------------------------------------------";
    lt_op<std::queue<int> > ("\n\tlt_op<std::queue<int> >  ");
    lt_op<stl::queue<int> >("\n\tlt_op<stl::queue<int> > ");
}

void test_queue::gt_op()
{
    stl::cout << "\n\n\tgt_op--------------------------------------------------";
    gt_op<std::queue<int> > ("\n\tgt_op<std::queue<int> >  ");
    gt_op<stl::queue<int> >("\n\tgt_op<stl::queue<int> > ");
}

void test_queue::lte_op()
{
    stl::cout << "\n\n\tlte_op-------------------------------------------------";
    lte_op<std::queue<int> > ("\n\tlte_op<std::queue<int> >  ");
    lte_op<stl::queue<int> >("\n\tlte_op<stl::queue<int> > ");
}

void test_queue::gte_op()
{
    stl::cout << "\n\n\tgte_op-------------------------------------------------";
    gte_op<std::queue<int> > ("\n\tgte_op<std::queue<int> >  ");
    gte_op<stl::queue<int> >("\n\tgte_op<stl::queue<int> > ");
}


//################################################################################
//template version of test function
template<typename Container>
void test_queue::ctor(const char* msg)
{
	typedef typename Container::value_type		Cval;
    typedef typename Container::container_type   TCont;

	// initialization data		
	Cval chtab[255]; /*NULL terminated*/ chtab[254]=0;
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
void test_queue::dtor(const char* msg)
{
    // preserving the code from ctor<Container>(...)
    // and measuring the destructor
	typedef typename Container::value_type Cval;
    typedef typename Container::container_type TCont;

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
void test_queue::empty(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(aux);

        TEST_CHECK(cont.empty() == false);

        while(!cont.empty())
            cont.pop();

        TEST_CHECK(cont.empty() == true);
    }
}

template<typename Container>
void test_queue::size(const char* msg)
{
    typedef typename Container::container_type   TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        TCont aux(m_container_size, CVal(0));
        Container cont(aux);

        TEST_CHECK(cont.size() == m_container_size);

        while(cont.size() > 0)
            cont.pop();

        TEST_CHECK(cont.empty() == true);
    }
}

template<typename Container>
void test_queue::front(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
            cont.push(i);

        TEST_CHECK(cont.size() == m_container_size);

		for(CVal i=0; i < m_container_size; ++i)
        {
            TEST_CHECK(cont.front() == i);
            TEST_CHECK(cont.size() == m_container_size-i);
            cont.pop();
        }

        TEST_CHECK(cont.empty() == true);
    }
}

template<typename Container>
void test_queue::back(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
        {
			TEST_CHECK(cont.size() == i);
            cont.push(i);
            TEST_CHECK(cont.back() == i);
        }
    }
}

template<typename Container>
void test_queue::push(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i < m_container_size; ++i)
        {
			TEST_CHECK(cont.size() == i);
            cont.push(i);
            TEST_CHECK(cont.back() == i);
        }
    }
}

template<typename Container>
void test_queue::pop(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);

        TEST_CHECK(cont.size() == m_container_size);

		for(CVal i=0; i < m_container_size; ++i)
        {
            TEST_CHECK(cont.front() == i);
            cont.pop();
        }

        TEST_CHECK(cont.empty() == true);
    }
}

template<typename Container>
void test_queue::eq_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        TEST_CHECK(cont == cont2);
    }
}

template<typename Container>
void test_queue::neq_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);
        cont2.pop();

        TEST_CHECK(cont != cont2);
    }
}

template<typename Container>
void test_queue::lt_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);
        cont2.pop();

        // lexicographical compared: cont[0,1,2..] & cont2[1,2,3...]
        TEST_CHECK(cont < cont2);
    }
}

template<typename Container>
void test_queue::gt_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);
        cont.pop();

        // lexicographical compared: cont[1,2,3..] & cont2[0,1,2...]
        TEST_CHECK(cont > cont2);
    }
}

template<typename Container>
void test_queue::lte_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type       CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        // equal
        TEST_CHECK(cont <= cont2);

        cont2.pop();

        // lexicographical compared: cont[0,1,2..] & cont2[1,2,3...]
        TEST_CHECK(cont <= cont2);
        TEST_CHECK(cont < cont2);
    }
}

template<typename Container>
void test_queue::gte_op(const char* msg)
{
	typedef typename Container::container_type	TCont;
    typedef typename Container::value_type     CVal;

    {
        time_printer tp(msg, m_print_time);

        Container cont;
		for(CVal i=0; i<m_container_size; ++i)
            cont.push(i);
        Container cont2(cont);

        // lexicographical compared: cont[1,2,3..] & cont2[0,1,2...]
        TEST_CHECK(cont >= cont2);

        cont.pop();

        TEST_CHECK(cont >= cont2);
        TEST_CHECK(cont > cont2);
    }
}

//////////////////////////////////////////////////////////////////////////
