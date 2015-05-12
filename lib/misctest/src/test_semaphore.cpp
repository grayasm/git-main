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
#include "test_semaphore.hpp"



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
#include "unistd.hpp"
#include "thread.hpp"
#include "time.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_semaphore::setUp()
{
}

void test_semaphore::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_semaphore::ctor()
{
	misc::cout << "\n\n\t******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER semaphore.hpp                       *";
	misc::cout <<   "\n\t******************************************************";	
	
	misc::cout << "\n\n\t ctor ------------------------------------------------";
	
	{
		misc::semaphore s(1);
		CPPUNIT_ASSERT( true );
	}
	{
		misc::semaphore* s = new misc::semaphore(1);
		delete s;
		CPPUNIT_ASSERT( true );
	}
}

void test_semaphore::dtor()
{
	misc::cout << "\n\n\t dtor ------------------------------------------------";
	
	{
		misc::semaphore s(1);
		CPPUNIT_ASSERT( s.lock() == 0 );
		// destroy a locked semaphore
	}
	{
		misc::semaphore* s = new misc::semaphore(1);
		CPPUNIT_ASSERT( s->lock() == 0 );
		delete s;
		// destroy a locked semaphore
	}
}

class slthread : public misc::thread
{
public:
	slthread(misc::semaphore* sem, int sec)
		: m_sem(sem), m_sec(sec) {}
	~slthread() {}
	// --vtable--
	unsigned long run()
	{
		m_sem->lock();
		printf("\n\t\tthread %d locked semaphore", m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d unlocking", m_sec);
		m_sem->unlock();
		return m_sec;
	}
	// --end vtable--
private:
	misc::semaphore*	m_sem;
	int					m_sec;	
};

void test_semaphore::lock()
{
	misc::cout << "\n\n\t lock ------------------------------------------------";
	
	{
		// semaphore with 0 maxlocks as error
		bool cond = false;
		try
		{
			misc::semaphore s(0);
		} catch( misc::exception& )
		{
			cond = true;
		}
		CPPUNIT_ASSERT( cond );
	}
	{
		// concurrent threads locking a semaphore and waiting for a no of seconds.
		// assert total execution time which must be sum of threads time
		
		misc::time t1( time(0) );
		printf("\n\t semaphore with 1 max locks");
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());

		misc::semaphore sem(1);
		const int THNO = 7;
		slthread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new slthread(&sem, i);
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
	{
		// concurrent threads locking a semaphore with large locks number
		// the maxim wait time should be of the thread with max sec number.
		
		misc::time t1( time(0) );
		printf("\n\n\t semaphore with more max locks");
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());

		const int THNO = 7;
		misc::semaphore sem( THNO );		
		slthread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new slthread(&sem, i);
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		for(int i=0; i < THNO; ++i)
			t[i]->join(-1);
		for(int i=0; i < THNO; ++i)
			delete t[i];

		misc::time t2( time(0) );
		int minsec = (int) THNO + 1;// allow an extra sec for synchronization
		misc::time t3 = t1 + minsec;
		bool tcmp = (t2 <= t3);

		printf("\n\t calculated delay : %d", minsec);
		printf("\n\t calculated time  : %s", t3.tolocaltime().c_str());
		printf("\n\t real end   time  : %s", t2.tolocaltime().c_str());	

		CPPUNIT_ASSERT( tcmp );
	}
}

class stthread : public misc::thread
{
public:
	stthread(misc::semaphore* sem, int sec)
		: m_sem(sem), m_sec(sec), m_count(0) {}
	~stthread() {}
	// --vtable--
	unsigned long run()
	{
		while(m_sem->trylock(1 * 1e3) != 0)
			m_count++;
		
		printf("\n\t\tthread %d locked after %d attempts", m_sec, m_count);
		sleep(m_sec);
		printf("\n\t\tthread %d unlocking", m_sec);
		m_sem->unlock();
		return m_sec;
	}
	// --end vtable--
	int get_count() const { return m_count ; }
private:
	misc::semaphore*	m_sem;
	int					m_sec;
	int					m_count;
};


void test_semaphore::trylock()
{
	misc::cout << "\n\n\t trylock ---------------------------------------------";
	{
		misc::semaphore sem(1);
		CPPUNIT_ASSERT( sem.trylock(2 * 1e3) == 0 );
		CPPUNIT_ASSERT( sem.trylock(2 * 1e3) == 1 );
	}
	{
		misc::semaphore sem(2);
		CPPUNIT_ASSERT( sem.trylock(2 * 1e3) == 0 );
		CPPUNIT_ASSERT( sem.trylock(2 * 1e3) == 0 );
		CPPUNIT_ASSERT( sem.trylock(2 * 1e3) == 1 );
	}
	{
		misc::time t1( time(0) );
		printf("\n\n\t semaphore with 1 lock");
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());
		
		const int THNO = 7;
		misc::semaphore sem(1);
		stthread*  t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new stthread(&sem, i);
		
		
		CPPUNIT_ASSERT( sem.lock() == 0 );// get at least 1 trylock in each thread
		
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		
		sleep(2);		
		CPPUNIT_ASSERT( sem.unlock() == 0 ); // let threads run now
		
		for(int i=0; i < THNO; ++i)
			t[i]->join();
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->get_count() > 0 );
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
	{
		// semaphore with more locks will allow multiple threads to run
		misc::time t1( time(0) );
		printf("\n\n\t semaphore with more locks");
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());
		
		const int THNO = 7;
		misc::semaphore sem(THNO);
		stthread*  t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new stthread(&sem, i);// max 6 sec for i=6
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		for(int i=0; i < THNO; ++i)
			t[i]->join();
		for(int i=0; i < THNO; ++i)
			delete t[i];
		
		misc::time t2( time(0) );
		int minsec = (int) THNO-1; // waiting time in total
		misc::time t3 = t1 + minsec;
		misc::time t4 = t3 + 2; // more with 2 sec maximum
		
		bool tcmp = (t2 >= t3) && (t2 <= t4);

		printf("\n\t minimum    delay : %d", minsec);
		printf("\n\t minimum    time  : %s", t3.tolocaltime().c_str());
		printf("\n\t maximum    time  : %s", t4.tolocaltime().c_str());
		printf("\n\t real end   time  : %s", t2.tolocaltime().c_str());	

		CPPUNIT_ASSERT( tcmp );		
	}
}

void test_semaphore::unlock()
{
	misc::cout << "\n\n\t unlock ----------------------------------------------";
	{
		// releasing an unlocked semaphore
		misc::semaphore sem(1);
		CPPUNIT_ASSERT(sem.trylock() == 0);
		CPPUNIT_ASSERT(sem.unlock() == 0);
		CPPUNIT_ASSERT(sem.lock() == 0);
		CPPUNIT_ASSERT(sem.trylock(2*1e3) == 1);
		CPPUNIT_ASSERT(sem.unlock() == 0);
		/*
		This is a pretty strange behavior for sem_t (linux sempahore)
		look inside sem.unlock() -- linux section.
		
		CPPUNIT_ASSERT( sem.unlock() == 0 ); // sem value=2
		CPPUNIT_ASSERT( sem.unlock() == 0 ); // sem value=3
		CPPUNIT_ASSERT( sem.trylock() == 0 );// sem value=2
		CPPUNIT_ASSERT( sem.lock() == 0 );	// sem value=1
		CPPUNIT_ASSERT( sem.lock() == 0 ); // sem value =0
		CPPUNIT_ASSERT( sem.trylock(2*1e3) == 1); // sem locked		
		*/

	}
}


//##########################END  TEST  SUITE######################################

