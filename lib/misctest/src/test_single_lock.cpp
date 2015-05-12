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
#include "test_single_lock.hpp"


//c++
#include <iostream>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "exception.hpp"
#include "stream.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include "unistd.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_single_lock::setUp()
{
}

void test_single_lock::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_single_lock::ctor()
{
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: single_lock.hpp                     *";
    misc::cout <<   "\n\t*******************************************************";
    
    misc::cout << "\n\n\tctor---------------------------------------------------";
	{
		misc::event ev;
		misc::single_lock sl(&ev);
	}
	{
		misc::mutex mt;
		misc::single_lock sl(&mt);
	}
	{
		misc::semaphore sem(1);
		misc::single_lock sl(&sem);
	}
}

void test_single_lock::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";
	{
		misc::event ev;
		misc::single_lock sl(&ev);
	}
	{
		misc::mutex mt;
		misc::single_lock sl(&mt);
	}
	{
		misc::semaphore sem(1);
		misc::single_lock sl(&sem);
	}
}

class SLLockThread : public misc::thread
{
public:
	SLLockThread(misc::single_lock* sl, int sec)
	: m_sl(sl), m_sec(sec) {} 
	~SLLockThread() {}
	unsigned long run()
	{
		CPPUNIT_ASSERT( m_sl->lock() == 0 );
		printf("\n\t\tthread %d: locked", m_sec);
		sleep(m_sec);
		CPPUNIT_ASSERT( m_sl->unlock() == 0 );
		printf("\n\t\tthread %d: unlocked", m_sec);
		return m_sec;
	}
private:
	misc::single_lock*	m_sl;
	int					m_sec;
};

void test_single_lock::lock()
{
	misc::cout << "\n\n\tlock---------------------------------------------------";
	{
		misc::mutex mt;
		misc::single_lock sl(&mt);
		SLLockThread t(&sl, 1);
		CPPUNIT_ASSERT( sl.lock() == 0 );
		CPPUNIT_ASSERT( t.resume() == 0 );
		printf("\n\tmain: resumed thread");
		sleep(1);
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
	}
	{
		printf("\n\tmain: single_lock(&mutex)");
		misc::mutex mt;
		misc::single_lock sl(&mt);
		const int THNO = 10;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		CPPUNIT_ASSERT( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&semaphore)");
		misc::semaphore sem(10);
		misc::single_lock sl(&sem);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		CPPUNIT_ASSERT( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&event)");
		misc::event ev;
		misc::single_lock sl(&ev);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		
		printf("\n\tmain: resuming threads");
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		sleep(2);
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
}

class SLTrylockThread : public misc::thread
{
public:
	SLTrylockThread(misc::single_lock* sl, int sec)
	: m_sl(sl), m_sec(sec) {} 
	~SLTrylockThread() {}
	unsigned long run()
	{
		if( m_sl->trylock(m_sec * 1e3) == 0 )
		{
			printf("\n\t\tthread %d: (try)locked-working", m_sec);
			sleep(1);
			CPPUNIT_ASSERT( m_sl->unlock() == 0 );
			printf("\n\t\tthread %d: unlocked", m_sec);
		}
		else
		{
			printf("\n\t\tthread %d: failed-return", m_sec);
		}
		return m_sec;
	}
private:
	misc::single_lock*	m_sl;
	int					m_sec;
};

void test_single_lock::trylock()
{
	misc::cout << "\n\n\ttrylock------------------------------------------------";
	{
		printf("\n\tmain: single_lock(&mutex)");
		misc::mutex mt;
		misc::single_lock sl(&mt);
		const int THNO = 40;
		SLTrylockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLTrylockThread(&sl, 50);
		CPPUNIT_ASSERT( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&semaphore)");
		misc::semaphore sem(10);
		misc::single_lock sl(&sem);
		const int THNO = 100;
		SLTrylockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLTrylockThread(&sl, 14);
		
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&event)");
		misc::event ev;
		misc::single_lock sl(&ev);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, 5);
		
		printf("\n\tmain: resuming threads");
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		sleep(2);
		CPPUNIT_ASSERT( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
}

void test_single_lock::unlock()
{
	misc::cout << "\n\n\tunlock-------------------------------------------------";
	// based on lock + trylock tests.
}
	
//##########################END  TEST  SUITE######################################


