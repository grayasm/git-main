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
	MLLockThread(misc::multi_lock* ml, int sec, int thID)
	: m_ml(ml), m_sec(sec), m_thID(thID) {}
	~MLLockThread() {}
	unsigned long run()
	{
		m_ml->lock();
		printf("\n\t\tthread %d: locked, sleeping %d sec", m_thID, m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d: unlocking", m_thID);
		m_ml->unlock();		
		return m_sec;
	}
private:
	misc::multi_lock*	m_ml;
	int					m_sec;
	int					m_thID;
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
		MLLockThread t(&ml, 1, 1);
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
		MLLockThread t(&ml, 1, 1);
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		printf("\n\t main: sleep(2) before releasing objects");
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( e1.setevent() == 0 );	
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main: 15 objects";
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
		MLLockThread t(&ml, 2, 1);
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
		// start 2 concurent multi_lock objects
		misc::cout << "\n\n\t main: 2 concurent multi_lock with same 2 objects";
		misc::mutex m1, m2;
		misc::sync_base* sb[2];
		sb[0] = &m1;
		sb[1] = &m2;
		misc::multi_lock ml1(sb, 2);
		misc::multi_lock ml2(sb, 2);
		MLLockThread t1(&ml1, 1, 1);
		MLLockThread t2(&ml2, 1, 2);
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
	}
	{
		misc::cout << "\n\n\t main: 3 concurent multilocks on 6,2,2, non-overlapping objects";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 6);
		MLLockThread t1(&ml1, 2, 1);
		
		misc::multi_lock ml2(&so[2], 2);
		MLLockThread t2(&ml2, 2, 2);
		
		misc::multi_lock ml3(&so[4], 2);
		MLLockThread t3(&ml3, 2, 3);
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
	}
 	{
		misc::cout << "\n\n\t main: 4 concurent multi_lock on 3 objects with 2 overlapped";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 3);
		MLLockThread t1(&ml1, 2, 1);
		
		misc::multi_lock ml2(&so[1], 3);
		MLLockThread t2(&ml2, 2, 2);
		
		misc::multi_lock ml3(&so[2], 3);
		MLLockThread t3(&ml3, 2, 3);
		
		misc::multi_lock ml4(&so[3], 3);
		MLLockThread t4(&ml4, 2, 4);
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
	}
	{
		misc::cout << "\n\n\t main: concurent multi_lock with 4 overlapped objects";
		misc::sync_base* so[50];
		misc::mutex m1, m2, m3, m4, m5;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		
		misc::event ev[40];
		for(int i=5; i < 40 + 5; ++i)
			so[i] = &ev[i-5];
		
		misc::semaphore s1(1), s2(1), s3(1), s4(1), s5(1);
		so[45] = &s1;
		so[46] = &s2;
		so[47] = &s3;
		so[48] = &s4;
		so[49] = &s5;
		
		// create multi_lock with overlapped ranges	
		misc::multi_lock ml1(so, 5 + 40 + 2); // 5 mutex, 40 events, 2 sem
		MLLockThread t1(&ml1, 3, 1);
		
		misc::multi_lock ml2(&so[2], 3 + 40 + 1); // 3 mutex, 40 events, 1 sem
		MLLockThread t2(&ml2, 2, 2);
		
		misc::multi_lock ml3(&so[3], 2 + 40 + 5); // 2 mutex, 40 events, 5 sem
		MLLockThread t3(&ml3, 4, 3);
		
		misc::multi_lock ml4(&so[5], 0 + 40 + 3); // 0 mutex, 40 events, 3 sem
		MLLockThread t4(&ml4, 5, 4);
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		misc::cout << "\n\n\t main: wait 3 seconds for multi_lock cocktail";
		sleep(3);
		
		for(int i=0; i < 40; ++i)
			CPPUNIT_ASSERT( ev[i].setevent() == 0 );
			
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
	}
	{
		misc::cout << "\n\n\t main: concurent multi_lock on 10 objects";
		// use 1 event to create the cocktail
		misc::sync_base* so[11];
		misc::mutex m1, m2, m3, m4, m5;
		misc::semaphore s1(1), s2(2), s3(1), s4(2), s5(1);
		misc::event ev;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &s1;
		so[6] = &s2;
		so[7] = &s3;
		so[8] = &s4;
		so[9] = &s5;
		so[10] = &ev;
		
		misc::multi_lock ml1(so, 11);
		MLLockThread t1(&ml1, 3, 1);
		
		misc::multi_lock ml2(so, 11);
		MLLockThread t2(&ml2, 3, 2);
		
		misc::multi_lock ml3(so, 11);
		MLLockThread t3(&ml3, 3, 3);
		
		misc::multi_lock ml4(so, 11);
		MLLockThread t4(&ml4, 3, 4);
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		misc::cout << "\n\t main: resummed 4 threads, in 2 sec comes the event";
		sleep(2);
		CPPUNIT_ASSERT( ev.setevent() == 0 );		
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );		
	}
}

class MLTimedLockThread : public misc::thread
{
public:
	MLTimedLockThread(misc::multi_lock* ml, int sec, int thID)
	: m_ml(ml), m_sec(sec), m_thID(thID) {}
	~MLTimedLockThread() {}
	unsigned long run()
	{
		unsigned long ret = m_ml->trylock(m_sec * 1e3);
		if(ret == 0)
		{
			printf("\n\t\tthread %d: locked", m_thID);
			sleep(1);
			printf("\n\t\tthread %d: unlocking", m_thID);
			m_ml->unlock();
		}
		else
		{
			printf("\n\t\tthread %d: timeout", m_thID);
		}
		return ret;
	}
private:
	misc::multi_lock*	m_ml;
	int					m_sec;
	int					m_thID;
};

void test_multi_lock::trylock()
{
	misc::cout << "\n\n\ttrylock -----------------------------------------------";
	
	// warming up with some simple tests
	{
		// 10 mutexes successful
		misc::cout << "\n\n\t main(1): 3 timewait multi_lock all on 10 mutex objects.";
		const int MUTNO=10;
		misc::mutex m[ MUTNO ];
		for(int i=0; i < MUTNO; ++i)
			CPPUNIT_ASSERT( m[i].lock() == 0 );
		
		misc::sync_base* sb[MUTNO];
		for(int i=0; i < MUTNO; ++i)
			sb[i] = &m[i];
		
		misc::multi_lock ml1(sb, MUTNO);
		MLTimedLockThread t1(&ml1, 10*60, 1); // 10min timeout
		
		misc::multi_lock ml2(sb, MUTNO);
		MLTimedLockThread t2(&ml2, 10*60, 2); // 10min timeout
		
		misc::multi_lock ml3(sb, MUTNO);
		MLTimedLockThread t3(&ml3, 10*60, 3); // 10min timeout
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		
		misc::cout << "\n\t main: all threads running, good luck!";
		sleep(2);
		
		for(int i=0; i < MUTNO; ++i)
			CPPUNIT_ASSERT( m[i].unlock() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		
		unsigned long retval = 0;
		t1.get_exit_code(&retval); CPPUNIT_ASSERT( retval == 0 );
		t2.get_exit_code(&retval); CPPUNIT_ASSERT( retval == 0 );
		t3.get_exit_code(&retval); CPPUNIT_ASSERT( retval == 0 );		
	}
	{
		// 5 mutexes, 5 semaphores, 1 not-signaled event => multi_lock timeout
		misc::cout << "\n\n\t main(2): concurent multi_lock running until timeout";
		misc::mutex mt1, mt2, mt3, mt4, mt5;
		misc::event ev1;
		misc::semaphore sm1(1), sm2(1), sm3(1), sm4(1), sm5(1);
		
		misc::sync_base* so[11];
		so[0] = &mt1;
		so[1] = &mt2;
		so[2] = &mt3;
		so[3] = &mt4;
		so[4] = &mt5;
		so[5] = &ev1;
		so[6] = &sm1;
		so[7] = &sm2;
		so[8] = &sm3;
		so[9] = &sm4;
		so[10] = &sm5;
		
		misc::multi_lock ml1(so, 11);
		MLTimedLockThread t1(&ml1, 5, 1);
		
		misc::multi_lock ml2(so, 11);
		MLTimedLockThread t2(&ml2, 5, 2);
		
		misc::multi_lock ml3(so, 11);
		MLTimedLockThread t3(&ml3, 5, 3);
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		
		unsigned long retval=0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );
		CPPUNIT_ASSERT( retval == 1 );
		
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );
		CPPUNIT_ASSERT( retval == 1 );
		
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );
		CPPUNIT_ASSERT( retval == 1 );
	}
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	// we repeat test_multi_lock::lock tests with result 0; successful locks.
	{
		misc::cout << "\n\n\t main(3):2 locked mutex";
		misc::mutex m1, m2;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		CPPUNIT_ASSERT( m2.lock() == 0 );
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &m2;
		misc::multi_lock ml(so, 2);
		MLTimedLockThread t(&ml, 60, 1); //1min
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( m2.unlock() == 0 );	
		CPPUNIT_ASSERT( t.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						// trylock succeeded
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main(4):1 mutex, 1 event";
		misc::mutex m1;
		misc::event e1;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &e1;
		misc::multi_lock ml(so, 2);
		MLTimedLockThread t(&ml, 60, 1);	// 1min
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		printf("\n\t main: sleep(2) before releasing objects");
		sleep(2);
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( e1.setevent() == 0 );	
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						// trylock succeeded
	}
	{
		misc::cout << "\n\n\t main(5): 15 objects";
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
		MLTimedLockThread t(&ml, 60, 1); // 1min
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
		
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		printf("\n\t main: thread joined");
	}
	{
		// start 2 concurent multi_lock objects
		misc::cout << "\n\n\t main(6): 2 concurent multi_lock with same 2 objects";
		misc::mutex m1, m2;
		misc::sync_base* sb[2];
		sb[0] = &m1;
		sb[1] = &m2;
		misc::multi_lock ml1(sb, 2);
		misc::multi_lock ml2(sb, 2);
		MLTimedLockThread t1(&ml1, 60, 1);	//1min
		MLTimedLockThread t2(&ml2, 60, 2);	//1min
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						// trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						// trylock succeeded
		
	}
	{
		misc::cout << "\n\n\t main(7): 3 concurent multilocks on 6,2,2, non-overlapping objects";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 6);
		MLTimedLockThread t1(&ml1, 120, 1); //2min
		
		misc::multi_lock ml2(&so[2], 2);
		MLTimedLockThread t2(&ml2, 120, 2); //2min
		
		misc::multi_lock ml3(&so[4], 2);
		MLTimedLockThread t3(&ml3, 120, 3); //2min
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
	}
 	{
		misc::cout << "\n\n\t main(8): 4 concurent multi_lock on 3 objects with 2 overlapped";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 3);
		MLTimedLockThread t1(&ml1, 300, 1); //5min
		
		misc::multi_lock ml2(&so[1], 3);
		MLTimedLockThread t2(&ml2, 300, 2); //5min
		
		misc::multi_lock ml3(&so[2], 3);
		MLTimedLockThread t3(&ml3, 300, 3); //5min
		
		misc::multi_lock ml4(&so[3], 3);
		MLTimedLockThread t4(&ml4, 300, 4); //5min
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		
	}
	{
		misc::cout << "\n\n\t main(9): concurent multi_lock with 4 overlapped objects";
		misc::sync_base* so[50];
		misc::mutex m1, m2, m3, m4, m5;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		
		misc::event ev[40];
		for(int i=5; i < 40 + 5; ++i)
			so[i] = &ev[i-5];
		
		misc::semaphore s1(1), s2(1), s3(1), s4(1), s5(1);
		so[45] = &s1;
		so[46] = &s2;
		so[47] = &s3;
		so[48] = &s4;
		so[49] = &s5;
		
		// create multi_lock with overlapped ranges	
		misc::multi_lock ml1(so, 5 + 40 + 2); // 5 mutex, 40 events, 2 sem
		MLTimedLockThread t1(&ml1, 300, 1); //5min
		
		misc::multi_lock ml2(&so[2], 3 + 40 + 1); // 3 mutex, 40 events, 1 sem
		MLTimedLockThread t2(&ml2, 300, 2); //5min
		
		misc::multi_lock ml3(&so[3], 2 + 40 + 5); // 2 mutex, 40 events, 5 sem
		MLTimedLockThread t3(&ml3, 300, 3); //5min
		
		misc::multi_lock ml4(&so[5], 0 + 40 + 3); // 0 mutex, 40 events, 3 sem
		MLTimedLockThread t4(&ml4, 300, 4); //5min
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		misc::cout << "\n\n\t main: wait 3 seconds for multi_lock cocktail";
		sleep(3);
		
		for(int i=0; i < 40; ++i)
			CPPUNIT_ASSERT( ev[i].setevent() == 0 );
			
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
	}
	{
		misc::cout << "\n\n\t main(10): concurent multi_lock on 10 objects";
		// use 1 event to create the cocktail
		misc::sync_base* so[11];
		misc::mutex m1, m2, m3, m4, m5;
		misc::semaphore s1(1), s2(2), s3(1), s4(2), s5(1);
		misc::event ev;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &s1;
		so[6] = &s2;
		so[7] = &s3;
		so[8] = &s4;
		so[9] = &s5;
		so[10] = &ev;
		
		misc::multi_lock ml1(so, 11);
		MLTimedLockThread t1(&ml1, 300, 1); //5min
		
		misc::multi_lock ml2(so, 11);
		MLTimedLockThread t2(&ml2, 300, 2); //5min
		
		misc::multi_lock ml3(so, 11);
		MLTimedLockThread t3(&ml3, 300, 3); //5min
		
		misc::multi_lock ml4(so, 11);
		MLTimedLockThread t4(&ml4, 300, 4); //5min
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		misc::cout << "\n\t main: resumed 4 threads, in 2 sec comes the event";
		sleep(2);
		CPPUNIT_ASSERT( ev.setevent() == 0 );		
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );	
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 0 );						//trylock succeeded
	}
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	// we repeat test_multi_lock::lock tests with result 1; failed with timeout.
	{
		misc::cout << "\n\n\t main(11):2 locked mutex";
		misc::mutex m1, m2;
		CPPUNIT_ASSERT( m1.lock() == 0 );
		CPPUNIT_ASSERT( m2.lock() == 0 );
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &m2;
		misc::multi_lock ml(so, 2);
		MLTimedLockThread t(&ml, 5, 1); //5sec and timeout
		
		
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		
		m1.unlock();
		m2.unlock();		
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		printf("\n\t main: thread joined");
	}
	{
		misc::cout << "\n\n\t main(12):1 mutex, 1 event";
		misc::mutex m1;
		misc::event e1;
				
		misc::sync_base* so[2];
		so[0] = &m1;
		so[1] = &e1;
		misc::multi_lock ml(so, 2);
		MLTimedLockThread t(&ml, 3, 1);	// 3sec and timeout
		
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		// CPPUNIT_ASSERT( e1.setevent() == 0 ); - get timeout
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\t main: thread joined");
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// trylock succeeded
	}
	{
		misc::cout << "\n\n\t main(13): 15 objects";
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
		MLTimedLockThread t(&ml, 5, 1); // 5sec and timeout
		CPPUNIT_ASSERT( t.resume() == 0 );
		
		CPPUNIT_ASSERT( m1.unlock() == 0 );
		CPPUNIT_ASSERT( m2.unlock() == 0 );
		CPPUNIT_ASSERT( m3.unlock() == 0 );
		CPPUNIT_ASSERT( m4.unlock() == 0 );
		CPPUNIT_ASSERT( m5.unlock() == 0 );
		
		// CPPUNIT_ASSERT( e1.unlock() == 0 ); - get timeout
		CPPUNIT_ASSERT( e2.unlock() == 0 );
		CPPUNIT_ASSERT( e3.unlock() == 0 );
		CPPUNIT_ASSERT( e4.unlock() == 0 );
		CPPUNIT_ASSERT( e5.unlock() == 0 );
		
		CPPUNIT_ASSERT( s1.unlock() == 0 );
		
		CPPUNIT_ASSERT( t.join() == 0 );

		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		printf("\n\t main: thread joined");
	}
	{
		// start 2 concurent multi_lock objects
		misc::cout << "\n\n\t main(14): 2 concurent multi_lock with same 2 objects";
		misc::mutex m1, m2;
		misc::sync_base* sb[2];
		sb[0] = &m1;
		sb[1] = &m2;
		misc::multi_lock ml1(sb, 2);
		misc::multi_lock ml2(sb, 2);
		MLTimedLockThread t1(&ml1, 5, 1);	//5sec and timeout
		MLTimedLockThread t2(&ml2, 5, 2);	//5sec and timeout
		
		CPPUNIT_ASSERT( m2.lock() == 0 );	// - get timeout
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		
		m2.unlock();
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// trylock succeeded
		
	}
	{
		misc::cout << "\n\n\t main(15): 3 concurent multilocks on 6,2,2, non-overlapping objects";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 6);
		MLTimedLockThread t1(&ml1, 5, 1); //5sec and timeout
		
		misc::multi_lock ml2(&so[2], 2);
		MLTimedLockThread t2(&ml2, 5, 2); //5sec and timeout
		
		misc::multi_lock ml3(&so[4], 2);
		MLTimedLockThread t3(&ml3, 5, 3); //5sec and timeout
		
		CPPUNIT_ASSERT( so[0]->lock() == 0 ); // get timeout
		CPPUNIT_ASSERT( so[2]->lock() == 0 ); // get timeout
		CPPUNIT_ASSERT( so[4]->lock() == 0 ); // get timeout
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		
		CPPUNIT_ASSERT( so[0]->unlock() == 0 );
		CPPUNIT_ASSERT( so[2]->unlock() == 0 );
		CPPUNIT_ASSERT( so[4]->unlock() == 0 );	
		
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						//trylock succeeded
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						//trylock succeeded
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						//trylock succeeded
	}
 	{
		misc::cout << "\n\n\t main(16): 4 concurent multi_lock on 3 objects with 2 overlapped";
		misc::mutex m1, m2, m3, m4, m5, m6;
		misc::sync_base* so[6];
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &m6;
		
		misc::multi_lock ml1(so, 3);
		MLTimedLockThread t1(&ml1, 5, 1);	//5sec and timeout
		
		misc::multi_lock ml2(&so[1], 3);
		MLTimedLockThread t2(&ml2, 5, 2);	//5sec and timeout
		
		misc::multi_lock ml3(&so[2], 3);
		MLTimedLockThread t3(&ml3, 5, 3);	//5sec and timeout
		
		misc::multi_lock ml4(&so[3], 3);
		MLTimedLockThread t4(&ml4, 5, 4);	//5sec and timeout
		
		CPPUNIT_ASSERT( so[2]->lock() == 0 ); // get timeout
		CPPUNIT_ASSERT( so[5]->lock() == 0 ); // get timeout
		
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
		
		CPPUNIT_ASSERT( so[2]->unlock() == 0 );
		CPPUNIT_ASSERT( so[5]->unlock() == 0 );

		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		
	}
	{
		misc::cout << "\n\n\t main(17): concurent multi_lock with 4 overlapped objects";
		misc::sync_base* so[50];
		misc::mutex m1, m2, m3, m4, m5;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		
		misc::event ev[40];
		for(int i=5; i < 40 + 5; ++i)
			so[i] = &ev[i-5];
		
		misc::semaphore s1(1), s2(1), s3(1), s4(1), s5(1);
		so[45] = &s1;
		so[46] = &s2;
		so[47] = &s3;
		so[48] = &s4;
		so[49] = &s5;
		
		// create multi_lock with overlapped ranges	
		misc::multi_lock ml1(so, 5 + 40 + 2); // 5 mutex, 40 events, 2 sem
		MLTimedLockThread t1(&ml1, 5, 1); //5sec and timeout
		
		misc::multi_lock ml2(&so[2], 3 + 40 + 1); // 3 mutex, 40 events, 1 sem
		MLTimedLockThread t2(&ml2, 5, 2); //5sec and timeout
		
		misc::multi_lock ml3(&so[3], 2 + 40 + 5); // 2 mutex, 40 events, 5 sem
		MLTimedLockThread t3(&ml3, 5, 3);  //5sec and timeout
		
		misc::multi_lock ml4(&so[5], 0 + 40 + 3); // 0 mutex, 40 events, 3 sem
		MLTimedLockThread t4(&ml4, 5, 4);  //5sec and timeout
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		for(int i=0; i < 39; ++i)			// one event less - get timeout
			CPPUNIT_ASSERT( ev[i].setevent() == 0 );
			
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
	}
	{
		misc::cout << "\n\n\t main(18): concurent multi_lock on 10 objects";
		// use 1 event to create the cocktail
		misc::sync_base* so[11];
		misc::mutex m1, m2, m3, m4, m5;
		misc::semaphore s1(1), s2(2), s3(1), s4(2), s5(1);
		misc::event ev;
		so[0] = &m1;
		so[1] = &m2;
		so[2] = &m3;
		so[3] = &m4;
		so[4] = &m5;
		so[5] = &s1;
		so[6] = &s2;
		so[7] = &s3;
		so[8] = &s4;
		so[9] = &s5;
		so[10] = &ev;
		
		misc::multi_lock ml1(so, 11);
		MLTimedLockThread t1(&ml1, 5, 1); // 5sec and timeout
		
		misc::multi_lock ml2(so, 11);
		MLTimedLockThread t2(&ml2, 5, 2); // 5sec and timeout
		
		misc::multi_lock ml3(so, 11);
		MLTimedLockThread t3(&ml3, 5, 3); // 5sec and timeout
		
		misc::multi_lock ml4(so, 11);
		MLTimedLockThread t4(&ml4, 5, 4); // 5sec and timeout
		
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		CPPUNIT_ASSERT( t3.resume() == 0 );
		CPPUNIT_ASSERT( t4.resume() == 0 );
		
		// CPPUNIT_ASSERT( ev.setevent() == 0 ); - get timeout
		
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		CPPUNIT_ASSERT( t3.join() == 0 );
		CPPUNIT_ASSERT( t4.join() == 0 );	
		
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t1.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t2.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t3.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
		CPPUNIT_ASSERT( t4.get_exit_code(&retval) == 0 );	// finished
		CPPUNIT_ASSERT( retval == 1 );						// failed, timeout
	}
}

void test_multi_lock::unlock()
{
	misc::cout << "\n\n\tunlock ------------------------------------------------";
}
//##########################END  TEST  SUITE######################################

