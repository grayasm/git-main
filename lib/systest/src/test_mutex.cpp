/*
Copyright (C) 2013 Mihai Vasilian
*/


//this
#include "test_mutex.hpp"


//c++
#include <iostream>

//acutest
#include "acutest.h"


//libraries
#include "string.hpp"
#include "exception.hpp"
#include "thread.hpp"
#include "unistd.hpp"
#include "time.hpp"
#include "stream.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_mutex::run()
{
	ctor();
	dtor();
	lock();
	trylock();
	unlock();
}

//##########################BEGIN TEST SUITE######################################
void test_mutex::ctor()
{
	stl::cout << "\n\n\t******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER mutex.hpp                           *";
	stl::cout <<   "\n\t******************************************************";	
	
	stl::cout << "\n\n\t ctor ------------------------------------------------";
	
	{
		sys::mutex m; // ctor
		TEST_CHECK( true );
	}
	{
		sys::mutex* m = new sys::mutex();
		delete m;
		TEST_CHECK( true );
	}
	{
		sys::mutex m[3];
		(m[0]);
		TEST_CHECK( true );			
	}
	{
		sys::mutex* m[3];
		for(int i=0; i < 3; ++i) m[i] = new sys::mutex();
		for(int i=0; i < 3; ++i) delete m[i];
		TEST_CHECK( true );
	}
}

void test_mutex::dtor()
{
	stl::cout << "\n\n\t dtor ------------------------------------------------";
	{
		sys::mutex m; // ctor
		TEST_CHECK( true );
	}
	{
		sys::mutex* m = new sys::mutex();
		delete m;
		TEST_CHECK( true );
	}
	{
		sys::mutex m[3];
		(m[0]);
		TEST_CHECK( true );			
	}
	{
		sys::mutex* m[3];
		for(int i=0; i < 3; ++i) m[i] = new sys::mutex();
		for(int i=0; i < 3; ++i) delete m[i];
		TEST_CHECK( true );
	}
}

// testing lock
class Mlthread : public sys::thread
{
public:
	Mlthread(sys::mutex* mtx, int sec)
		: m_mtx(mtx), m_sec(sec) { }
	~Mlthread() { }
	// --vtable--
	unsigned long run()
	{
		m_mtx->lock();
		printf("\n\t\tthread %d locked mutex", m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d unlocking", m_sec);
		m_mtx->unlock();
		return m_sec;
	}
	// -- end vtable --
private:
	sys::mutex* m_mtx;
	int m_sec;	
};

void test_mutex::lock()
{
	stl::cout << "\n\n\t lock ------------------------------------------------";
	{
		sys::mutex m;
		TEST_CHECK( m.lock() == 0 );
		// legit to destroy a locked mutex
	}
	{
		sys::mutex* m = new sys::mutex();
		TEST_CHECK (m->lock() == 0);
		delete m;
	}
	{
		sys::mutex m[3];
		for(int i=0; i < 3; ++i)
		{
			TEST_CHECK( m[i].lock() == 0 );
		}
		// destroy mutex array while in locked state.
	}
	{
		sys::mutex* m[3];
		for(int i=0; i < 3; ++i)
			m[i] = new sys::mutex();
		for(int i=0; i < 3; ++i)
			TEST_CHECK( m[i]->lock() == 0 );
		// destroy mutex array while in locked state
		for(int i=0; i < 3; ++i)
			delete m[i];
	}
	{
		// recursive lock on the same mutex
		sys::mutex m;
		for(int i=0; i < 100; ++i)
			TEST_CHECK( m.lock() == 0 );
		for(int i=0; i < 100; ++i)
			TEST_CHECK( m.unlock() == 0 );
	}
	{
		// lock mutex in a separate thread and unlock it in this thread (exception)
		sys::mutex m;
		Mlthread t(&m, 5);
		TEST_CHECK( t.resume() == 0 );
		sleep(2);
		bool cond = false;
		try 
		{
			m.unlock();
		}catch(stl::exception&)
		{
			cond = true;
		}
		TEST_CHECK( cond );
		TEST_CHECK( t.join() == 0 );
	}
	{
		// concurrent threads locking a mutex and waiting for a no of seconds.
		// assert total execution time which must be sum of threads time
		
		sys::time t1( time(0) );
		printf("\n\t start time       : %s", t1.tolocaltime().c_str());

		sys::mutex mtx;
		const int THNO = 7;
		Mlthread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new Mlthread(&mtx, i);
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		for(int i=0; i < THNO; ++i)
			t[i]->join(-1);
		for(int i=0; i < THNO; ++i)
			delete t[i];

		sys::time t2( time(0) );
		int minsec = (int) ((THNO-1)*THNO/2); // waiting time in total
		sys::time t3 = t1 + minsec - 1; // less one sec for the comparison below
		bool tcmp = (t2 >= t3);

		printf("\n\t calculated delay : %d", minsec);
		printf("\n\t calculated time  : %s", t3.tolocaltime().c_str());
		printf("\n\t real end   time  : %s", t2.tolocaltime().c_str());	

		TEST_CHECK( tcmp );
	}
}

// testing lock
class Mtrythread : public sys::thread
{
public:
	Mtrythread(sys::mutex* mtx, int sec)
		: m_mtx(mtx), m_sec(sec), m_count(0) { }
	~Mtrythread() { }
	// --vtable--
	unsigned long run()
	{
		while( m_mtx->trylock(1 * 1e3) != 0 )
			m_count++;
		printf("\n\t\tthread %d locked after %d attempts", m_sec, m_count);
		sleep(m_sec);
		printf("\n\t\tthread %d unlocking", m_sec);
		m_mtx->unlock();
		return m_sec;
	}
	// -- end vtable --
	int get_count() const { return m_count; }
private:
	sys::mutex* m_mtx;
	int m_sec;
	int m_count;
};

void test_mutex::trylock()
{
	stl::cout << "\n\n\t trylock ---------------------------------------------";
	{
		sys::mutex m;
		TEST_CHECK( m.trylock() == 0 );
		// legit to destroy a locked mutex
	}
	{
		sys::mutex* m = new sys::mutex();
		TEST_CHECK (m->trylock() == 0);
		delete m;
	}
	{
		sys::mutex m[3];
		for(int i=0; i < 3; ++i)
		{
			TEST_CHECK( m[i].trylock() == 0 );
		}
		// destroy mutex array while in locked state.
	}
	{
		sys::mutex* m[3];
		for(int i=0; i < 3; ++i) 
			m[i] = new sys::mutex();
		for(int i=0; i < 3; ++i)
			TEST_CHECK( m[i]->lock() == 0 );
		// destroy mutex array while in locked state
		for(int i=0; i < 3; ++i) 
			delete m[i];
	}
	{
		// execute a trylock in a separate thread and lock the mutex
		// then unlock it from main thread
		sys::mutex m;
		Mtrythread t(&m, 5);
		TEST_CHECK( t.resume() == 0 );
		sleep(2);
		bool cond = false;
		try
		{
			m.unlock();
		} catch( stl::exception& )
		{
			cond = true;
		}
		TEST_CHECK( cond );
		TEST_CHECK( t.join() == 0 );
		TEST_CHECK( t.get_count() == 0 );
	}
	{
		// concurrent threads will attempt to unsuccessfully trylock at least
		// one a locked mutex in the main thread.
		// mutex is later released and all threads are waited to finish their job
		sys::time t1( time(0) );
		printf("\n\t start time: %s", t1.tolocaltime().c_str());

		
		// lock mutex to get in each thread at least 1 trylock attempt
		sys::mutex mtx;
		mtx.lock();	
		
		const int THNO = 7;
		Mtrythread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new Mtrythread(&mtx, i);
		 // start all threads
		for(int i=0; i < THNO; ++i)
			t[i]->resume();
		
		// each thread tries at least 1 time the trylock
		sleep(3);	
		mtx.unlock();
		
		for(int i=0; i < THNO; ++i)
			t[i]->join(-1);

		sys::time t2( time(0) );
		int minsec = (int) ((THNO-1)*THNO/2);
		sys::time t3 = t1 + minsec - 1; // less one sec for the comparison below
		bool tcmp = (t2 >= t3);

		printf("\n\t calculated delay : %d", minsec);
		printf("\n\t calculated time  : %s", t3.tolocaltime().c_str());
		printf("\n\t real end   time  : %s", t2.tolocaltime().c_str());	
		
		TEST_CHECK( tcmp );

		// check each thread counter
		for(int i=0; i < THNO; ++i)
		{
			int cnt = t[i]->get_count();
			printf("\n\t thread %d tried %d times", i, cnt);
			TEST_CHECK(cnt > 0);
		}
	}
}

void test_mutex::unlock()
{
	stl::cout << "\n\n\t unlock ----------------------------------------------";
	{
		// lock + unlock mutex
		sys::mutex m;
		TEST_CHECK( m.lock() == 0 );
		TEST_CHECK( m.unlock() == 0 );
	}
	{
		// unlock a not owned mutex: error
		sys::mutex m;
		bool cond = false;
		try
		{
			m.unlock();
		} catch( stl::exception& )
		{
			cond = true;
		}
		TEST_CHECK( cond );
	}
	{
		// attempt to unlock a mutex not locked by this thread
		sys::mutex m;
		Mlthread t(&m, 5);
		TEST_CHECK( t.resume() == 0 );
		sleep(2);
		bool cond = false;
		try
		{
			m.unlock();
		} catch( stl::exception& )
		{
			cond = true;
		}
		TEST_CHECK( cond );
		TEST_CHECK( t.join() == 0 );
	}
}

//##########################END  TEST  SUITE######################################
