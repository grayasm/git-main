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
		printf("\n\t\tthread %d: locked", m_sec);
		for(int i=0; i < m_sec; ++i)
		{
			printf("\n\t\tthread %d: sleep(1)", m_sec);
			sleep(1);
		}
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

		MLLockThread t(&multi, 5);
		CPPUNIT_ASSERT( t.resume() == 0 );
		printf("\n\tmain: thread resumed, wait 2 sec");
		msleep(2521);
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		msleep(1521);
		CPPUNIT_ASSERT( m2.unlock() == 0 );
		msleep(1521);
		CPPUNIT_ASSERT( s1.unlock() == 0 );
		msleep(1521);
		CPPUNIT_ASSERT( s2.unlock() == 0 );
		msleep(1521);
		CPPUNIT_ASSERT( e1.setevent() == 0 );
		msleep(1521);
		CPPUNIT_ASSERT( e2.setevent() == 0 );
		printf("\n\tmain: all signaled");
		
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: thread joined");
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
	
}
//##########################END  TEST  SUITE######################################

