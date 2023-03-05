/*
Copyright (C) 2013 Mihai Vasilian
*/


//this
#include "test_autocritical_section.hpp"


//c++
#include <iostream>

//acutest
#include "acutest.h"

//libraries
#include "string.hpp"
#include "stream.hpp"
#include "exception.hpp"
#include "thread.hpp"
#include "unistd.hpp"
#include "time.hpp"



//########################### BEGIN TEST #######################################
void test_autocritical_section::run()
{
	ctor();
	dtor();
}

//############################ BEGIN TEST ######################################
void test_autocritical_section::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: autocritical_section.hpp            *";
    stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tctor---------------------------------------------------";
	{
		sys::critical_section cs;
		sys::autocritical_section acs(cs);
		TEST_CHECK( true );
	}
	{
		sys::critical_section cs;
		sys::autocritical_section* acs;
		acs = new sys::autocritical_section(cs);
		TEST_CHECK( acs != 0 );
		delete acs;
	}
	{
		const int CSNO=6;
		sys::critical_section cs[CSNO];
		sys::autocritical_section* acs[CSNO];
		for(int i=0; i < CSNO; ++i)
			acs[i] = new sys::autocritical_section(cs[i]);
		for(int i=0; i < CSNO; ++i)
			TEST_CHECK( acs[i] != 0 );
		for(int i=0; i < CSNO; ++i)
			delete acs[i];
	}
}

void test_autocritical_section::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
}



//############################ END  TEST  ######################################
