/*
  Copyright (C) 2013 Mihai Vasilian

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
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: critical_section.hpp                *";
    misc::cout <<   "\n\t*******************************************************";

	misc::cout << "\n\n\tctor---------------------------------------------------";
	{
		misc::critical_section cs;
		CPPUNIT_ASSERT( true );
	}
	{
		misc::critical_section* cs;
		cs = new misc::critical_section();
		CPPUNIT_ASSERT( cs != 0 );
		delete cs;
	}
	{
		const int CSNO=6;
		misc::critical_section cs[CSNO];
		(cs[0]);
		CPPUNIT_ASSERT( true );
	}
	{
		const int CSNO=6;
		misc::critical_section* cs[CSNO];
		for(int i=0; i < CSNO; ++i)
			cs[i] = new misc::critical_section();
		for(int i=0; i < CSNO; ++i)
			CPPUNIT_ASSERT( cs[i] != 0 );
		for(int i=0; i < CSNO; ++i)
			delete cs[i];
	}
}

void test_critical_section::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";
}


// testing lock
class CSLockThread : public misc::thread
{
public:
	CSLockThread(misc::critical_section* cs, int sec)
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
	misc::critical_section*		m_cs;
	int							m_sec;	
};

void test_critical_section::lock()
{
	misc::cout << "\n\n\tlock---------------------------------------------------";
	{
		misc::critical_section cs;
		CPPUNIT_ASSERT( cs.lock() == 0 );
		// destroy a locked critical section
	}
	{
		misc::critical_section* cs = new misc::critical_section();
		CPPUNIT_ASSERT (cs->lock() == 0);
		delete cs;
	}
	{
		misc::critical_section cs[3];
		for(int i=0; i < 3; ++i)
		{
			CPPUNIT_ASSERT( cs[i].lock() == 0 );
		}
		// destroy critical_section array while in locked state.
	}
	{
		misc::critical_section* cs[3];
		for(int i=0; i < 3; ++i)
			cs[i] = new misc::critical_section();
		for(int i=0; i < 3; ++i)
			CPPUNIT_ASSERT( cs[i]->lock() == 0 );
		// destroy critical_section array while in locked state
		for(int i=0; i < 3; ++i)
			delete cs[i];
	}
	{
		// concurrent threads locking a critical_section and waiting for a no of seconds.
		// assert total execution time which must be sum of threads time
		misc::time t1( time(0) );
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());

		misc::critical_section cs;
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

		misc::time t2( time(0) );
		int minsec = (int) ((THNO-1)*THNO/2); // waiting time in total
		misc::time t3 = t1 + minsec;
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