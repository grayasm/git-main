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
#include "test_multi_lock.hpp"

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
#include "mutex.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include "thread.hpp"
#include "time.hpp"
#include "unistd.hpp"




//###########################BEGIN TEST CLASS ####################################
void test_multi_lock::setUp()
{
}

void test_multi_lock::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_multi_lock::ctor()
{
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: multi_lock.hpp                      *";
    misc::cout <<   "\n\t*******************************************************";
	
    misc::cout << "\n\n\tctor---------------------------------------------------";
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock ml(so, 6);
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock* ml = new misc::multi_lock(so, 6);
		delete ml;
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock ml6(so, 6), ml5(so, 5), ml4(so, 4);
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock* ml[6];
		for(size_t i=0; i < 6; ++i)
			ml[i] = new misc::multi_lock(so, i+1);
		for(size_t i=0; i < 6; ++i)
			delete ml[i];
	}
}

void test_multi_lock::dtor()
{
	misc::cout << "\n\n\tdtor---------------------------------------------------";
	
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock ml(so, 6);
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock* ml = new misc::multi_lock(so, 6);
		delete ml;
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock ml6(so, 6), ml5(so, 5), ml4(so, 4);
	}
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;
		misc::multi_lock* ml[6];
		for(size_t i=0; i < 6; ++i)
			ml[i] = new misc::multi_lock(so, i+1);
		for(size_t i=0; i < 6; ++i)
			delete ml[i];
	}
}

class MLLockThread : public misc::thread
{
public:
	MLLockThread(misc::multi_lock* ml, int sec)
	: m_ml(ml), m_sec(sec) {}
	~MLLockThread() {}
	unsigned long run()
	{
		m_ml->lock();
		printf("\n\t\tthread %d: locked, sleeping %d sec", m_sec, m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d: unlocking", m_sec);
		m_ml->unlock();		
		return m_sec;
	}
private:
	misc::multi_lock*	m_ml;
	int					m_sec;
};

void test_multi_lock::lock()
{
	misc::cout << "\n\n\tlock --------------------------------------------------";
	
	{
		misc::cout << "\n\n\t main:2 locked mutex";
		misc::mutex m1, m2;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		CPPUNIT_ASSERT( m2.lock() == 0 );
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &m2;
		misc::multi_lock ml(so, 2);
		MLLockThread t(&ml, 1);
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		printf("\n\t main: sleep(2) before releasing objects");
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( m2.unlock() == 0 );	
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main:1 mutex, 1 event";
		misc::mutex m1;
		misc::event e1;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &e1;
		misc::multi_lock ml(so, 2);
		MLLockThread t(&ml, 1);
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		printf("\n\t main: sleep(2) before releasing objects");
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( e1.setevent() == 0 );	
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main: more objects";
		misc::mutex m1, m2, m3, m4, m5;
		misc::event e1, e2, e3, e4, e5;
		misc::semaphore s1(1), s2(2), s3(3), s4(4), s5(5);
				
		CPPUNIT_ASSERT( m1.lock() == 0 );
		CPPUNIT_ASSERT( m2.lock() == 0 );
		CPPUNIT_ASSERT( m3.lock() == 0 );
		CPPUNIT_ASSERT( m4.lock() == 0 );
		CPPUNIT_ASSERT( m5.lock() == 0 );
		
		CPPUNIT_ASSERT( s1.lock() == 0 );
		
		misc::sync_base* so[15];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		
		so[5] = &e1;
		so[6] = &e2;
		so[7] = &e3;
		so[8] = &e4;
		so[9] = &e5;
		
		so[10] = &s1;
		so[11] = &s2;
		so[12] = &s3;
		so[13] = &s4;
		so[14] = &s5;
		
		misc::multi_lock ml(so, 15);
		MLLockThread t(&ml, 2);
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		printf("\n\t main: sleep(2) before releasing objects");
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( m2.unlock() == 0 );
		CPPUNIT_ASSERT( m3.unlock() == 0 );
		CPPUNIT_ASSERT( m4.unlock() == 0 );
		CPPUNIT_ASSERT( m5.unlock() == 0 );
		
		CPPUNIT_ASSERT( e1.unlock() == 0 );
		CPPUNIT_ASSERT( e2.unlock() == 0 );
		CPPUNIT_ASSERT( e3.unlock() == 0 );
		CPPUNIT_ASSERT( e4.unlock() == 0 );
		CPPUNIT_ASSERT( e5.unlock() == 0 );
		
		CPPUNIT_ASSERT( s1.unlock() == 0 );
		
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main: concurent multi-lock";
		
	}
}

class MLTimedLockThread : public misc::thread
{
public:
	MLTimedLockThread(misc::multi_lock* ml, int sec)
	: m_ml(ml), m_sec(sec) {}
	~MLTimedLockThread() {}
	unsigned long run()
	{
		if( m_ml->trylock(m_sec * 1e3) == 0 )
		{
			printf("\n\t\tthread %d: locked", m_sec);
			for(int i=0; i < m_sec; ++i)
			{
				printf("\n\t\tthread %d: sleep(1)", m_sec);
				sleep(1);
			}
			printf("\n\t\tthread %d: unlocking", m_sec);
			m_ml->unlock();
		}
		else
		{
			printf("\n\t\tthread %d: failed to lock the multi_lock", m_sec);
		}		
		return m_sec;
	}
private:
	misc::multi_lock*	m_ml;
	int					m_sec;
};

void test_multi_lock::trylock()
{
	misc::cout << "\n\n\ttrylock -----------------------------------------------";
	
	{
		misc::mutex m1,m2;
		misc::semaphore s1(1), s2(2);
		misc::event e1, e2;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		CPPUNIT_ASSERT( m2.lock() == 0 );
		CPPUNIT_ASSERT( s1.lock() == 0 );
		CPPUNIT_ASSERT( s2.lock() == 0 );
		
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &s1;
		so[3] = &s2;
		so[4] = &e1;
		so[5] = &e2;

		misc::multi_lock multi(so, 6);

		MLTimedLockThread t(&multi, 5);
		CPPUNIT_ASSERT( t.resume() == 0 );
		printf("\n\tmain: thread resumed, wait 2 sec");
		msleep(2521);
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( m2.unlock() == 0 );
		CPPUNIT_ASSERT( s1.unlock() == 0 );
		CPPUNIT_ASSERT( s2.unlock() == 0 );
		CPPUNIT_ASSERT( e1.setevent() == 0 );
		CPPUNIT_ASSERT( e2.setevent() == 0 );
		printf("\n\tmain: all signaled");
		
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: thread joined");
	}
}

void test_multi_lock::unlock()
{
	misc::cout << "\n\n\tunlock ------------------------------------------------";
	
	
}
//##########################END  TEST  SUITE######################################

