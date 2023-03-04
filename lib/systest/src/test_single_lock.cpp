/*
Copyright (C) 2013 Mihai Vasilian
*/


//this
#include "test_single_lock.hpp"


//c++
#include <iostream>

//acutest
#include "acutest.h"


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
void test_single_lock::run()
{
	ctor();
	dtor();
	lock();
	trylock();
	unlock();
}


//##########################BEGIN TEST SUITE######################################
void test_single_lock::ctor()
{
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: single_lock.hpp                     *";
    stl::cout <<   "\n\t*******************************************************";
    
    stl::cout << "\n\n\tctor---------------------------------------------------";
	{
		sys::event ev;
		sys::single_lock sl(&ev);
	}
	{
		sys::mutex mt;
		sys::single_lock sl(&mt);
	}
	{
		sys::semaphore sem(1);
		sys::single_lock sl(&sem);
	}
}

void test_single_lock::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
	{
		sys::event ev;
		sys::single_lock sl(&ev);
	}
	{
		sys::mutex mt;
		sys::single_lock sl(&mt);
	}
	{
		sys::semaphore sem(1);
		sys::single_lock sl(&sem);
	}
}

class SLLockThread : public sys::thread
{
public:
	SLLockThread(sys::single_lock* sl, int sec)
	: m_sl(sl), m_sec(sec) {} 
	~SLLockThread() {}
	unsigned long run()
	{
		TEST_CHECK( m_sl->lock() == 0 );
		printf("\n\t\tthread %d: locked", m_sec);
		sleep(m_sec);
		TEST_CHECK( m_sl->unlock() == 0 );
		printf("\n\t\tthread %d: unlocked", m_sec);
		return m_sec;
	}
private:
	sys::single_lock*	m_sl;
	int					m_sec;
};

void test_single_lock::lock()
{
	stl::cout << "\n\n\tlock---------------------------------------------------";
	{
		sys::mutex mt;
		sys::single_lock sl(&mt);
		SLLockThread t(&sl, 1);
		TEST_CHECK( sl.lock() == 0 );
		TEST_CHECK( t.resume() == 0 );
		printf("\n\tmain: resumed thread");
		sleep(1);
		TEST_CHECK( sl.unlock() == 0 );
		TEST_CHECK( t.join() == 0 );
		printf("\n\tmain: joined thread");
	}
	{
		printf("\n\tmain: single_lock(&mutex)");
		sys::mutex mt;
		sys::single_lock sl(&mt);
		const int THNO = 10;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		TEST_CHECK( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		TEST_CHECK( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&semaphore)");
		sys::semaphore sem(10);
		sys::single_lock sl(&sem);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		TEST_CHECK( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		TEST_CHECK( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&event)");
		sys::event ev;
		sys::single_lock sl(&ev);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, i%2);
		
		printf("\n\tmain: resuming threads");
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		sleep(2);
		TEST_CHECK( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
}

class SLTrylockThread : public sys::thread
{
public:
	SLTrylockThread(sys::single_lock* sl, int sec)
	: m_sl(sl), m_sec(sec) {} 
	~SLTrylockThread() {}
	unsigned long run()
	{
		if( m_sl->trylock(m_sec * 1e3) == 0 )
		{
			printf("\n\t\tthread %d: (try)locked-working", m_sec);
			sleep(1);
			TEST_CHECK( m_sl->unlock() == 0 );
			printf("\n\t\tthread %d: unlocked", m_sec);
		}
		else
		{
			printf("\n\t\tthread %d: failed-return", m_sec);
		}
		return m_sec;
	}
private:
	sys::single_lock*	m_sl;
	int					m_sec;
};

void test_single_lock::trylock()
{
	stl::cout << "\n\n\ttrylock------------------------------------------------";
	{
		printf("\n\tmain: single_lock(&mutex)");
		sys::mutex mt;
		sys::single_lock sl(&mt);
		const int THNO = 40;
		SLTrylockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLTrylockThread(&sl, 50);
		TEST_CHECK( sl.lock() == 0 );
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		TEST_CHECK( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&semaphore)");
		sys::semaphore sem(10);
		sys::single_lock sl(&sem);
		const int THNO = 100;
		SLTrylockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLTrylockThread(&sl, 14);
		
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
	{
		printf("\n\tmain: single_lock(&event)");
		sys::event ev;
		sys::single_lock sl(&ev);
		const int THNO = 100;
		SLLockThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new SLLockThread(&sl, 5);
		
		printf("\n\tmain: resuming threads");
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( t[i]->resume() == 0 );
		sleep(2);
		TEST_CHECK( sl.unlock() == 0 );
		printf("\n\tmain: unlocked single_lock");
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
			delete t[i];
		}		
	}
}

void test_single_lock::unlock()
{
	stl::cout << "\n\n\tunlock-------------------------------------------------";
	// based on lock + trylock tests.
}
	
//##########################END  TEST  SUITE######################################
