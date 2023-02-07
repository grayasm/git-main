/*
Copyright (C) 2013 Mihai Vasilian
*/



#include "test_exception.hpp"

//c
#include <string.h>
#include <time.h>
//c++

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "stream.hpp"
#include "misctest_util.hpp"



//###########################DEQUE TEST CLASS ####################################
void test_exception::setUp()
{
}

void test_exception::tearDown()
{
}


//test begin
void test_exception::ctor()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: exception.hpp                       *";
    stl::cout <<   "\n\t*******************************************************";

	
	stl::cout << "\n\n\tctor---------------------------------------------------";
	ctor<stl::exception>("\n\tmisc::exception");
	ctor<std::bad_alloc>("\n\tstd::bad_alloc");
}



void test_exception::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
	dtor<stl::exception>("\n\tmisc::exception");
	dtor<std::bad_alloc>("\n\tstd::bad_alloc");
}


// test end 

//////////////////////////////////////////////////////////////////////////
//template version of test function

template<typename Container>
void test_exception::ctor(const char* msg)
{
	{
		time_printer tp(msg, m_print_time);

		Container exc;
		try
		{
			throw exc;
		}
		catch(const Container& mexc)
		{
			mexc.what();
		}
	}
}

template<typename Container>
void test_exception::dtor(const char* msg)
{
	{
		time_printer tp(msg, m_print_time);

		Container exc;
	}	
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////