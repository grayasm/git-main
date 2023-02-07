/*
Copyright (C) 2013 Mihai Vasilian
*/


//this
#include "test_critical_section.hpp"


//c++
#include <iostream>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "stream.hpp"
#include "exception.hpp"
#include "thread.hpp"
#include "unistd.hpp"
#include "time.hpp"



//###########################BEGIN TEST CLASS ####################################
void test_critical_section::setUp()
{
}

void test_critical_section::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_critical_section::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: critical_section.hpp                *";
    stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tctor---------------------------------------------------";
	{
		sys::critical_section cs;
		CPPUNIT_ASSERT( true );
	}
	{
		sys::critical_section* cs;
		cs = new sys::critical_section();
		CPPUNIT_ASSERT( cs != 0 );
		delete cs;
	}
	{
		const int CSNO=6;
		sys::critical_section cs[CSNO];
		(cs[0]);
		CPPUNIT_ASSERT( true );
	}
	{
		const int CSNO=6;
		sys::critical_section* cs[CSNO];
		for(int i=0; i < CSNO; ++i)
			cs[i] = new sys::critical_section();
		for(int i=0; i < CSNO; ++i)
			CPPUNIT_ASSERT( cs[i] != 0 );
		for(int i=0; i < CSNO; ++i)
			delete cs[i];
	}
}

void test_critical_section::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
}


// testing lock
class CSLockThread : public sys::thread
{
public:
	CSLockThread(sys::critical_section* cs, int sec)
		: m_cs(cs), m_sec(sec) { }
	~CSLockThread() { }
	unsigned long run()
	{
		m_cs->lock();
		printf("\n\t\tthread %d: locked critical_section", m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d: unlocking", m_sec);
		m_cs->unlock();
		return m_sec;
	}
private:
	sys::critical_section*		m_cs;
	int							m_sec;	
};

void test_critical_section::lock()
{
	stl::cout << "\n\n\tlock---------------------------------------------------";
	{
		sys::critical_section cs;
		CPPUNIT_ASSERT( cs.lock() == 0 );
		// destroy a locked critical section
	}
	{
		sys::critical_section* cs = new sys::critical_section();
		CPPUNIT_ASSERT (cs->lock() == 0);
		delete cs;
	}
	{
		sys::critical_section cs[3];
		for(int i=0; i < 3; ++i)
		{
			CPPUNIT_ASSERT( cs[i].lock() == 0 );
		}
		// destroy critical_section array while in locked state.
	}
	{
		sys::critical_section* cs[3];
		for(int i=0; i < 3; ++i)
			cs[i] = new sys::critical_section();
		for(int i=0; i < 3; ++i)
			CPPUNIT_ASSERT( cs[i]->lock() == 0 );
		// destroy critical_section array while in locked state
		for(int i=0; i < 3; ++i)
			delete cs[i];
	}
	{
		// concurrent threads locking a critical_section and waiting for a no of seconds.
		// assert total execution time which must be sum of threads time
		sys::time t1( time(0) );
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());

		sys::critical_section cs;
		const int THNO = 7;
		CSLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new CSLockThread(&cs, i);
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		for(int i=0; i < THNO; ++i)
			t[i]->join(-1);
		for(int i=0; i < THNO; ++i)
			delete t[i];

		sys::time t2( time(0) );
		int minsec = (int) ((THNO-1)*THNO/2); // waiting time in total
		sys::time t3 = t1 + minsec;
		bool tcmp = (t2 >= t3);

		printf("\n\t calculated delay : %d", minsec);
		printf("\n\t calculated time  : %s", t3.tolocaltime().c_str());
		printf("\n\t real end   time  : %s", t2.tolocaltime().c_str());	

		CPPUNIT_ASSERT( tcmp );
	}
}

void test_critical_section::unlock()
{
	
}


//##########################END  TEST  SUITE######################################