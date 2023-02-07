/*
Copyright (C) 2013 Mihai Vasilian
*/

//this
#include "test_event.hpp"


//c++
#include <iostream>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "exception.hpp"
#include "thread.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "vector.hpp"


//###########################BEGIN TEST CLASS ####################################
void test_event::setUp()
{
}

void test_event::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
void test_event::ctor()
{
	stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: event.hpp                           *";
    stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tctor---------------------------------------------------";
	// simple test for calling class constructor
	{
		sys::event ev;
		CPPUNIT_ASSERT( true );
	}
	{
		sys::event* ev = new sys::event();
		delete ev;
		CPPUNIT_ASSERT( true );
	}
	{
		const int EVNO=10;
		sys::event ev[EVNO];
		for(int i=0; i < EVNO; ++i)
			(ev[i]);
		CPPUNIT_ASSERT( true );
	}
	{
		const int EVNO=10;
		sys::event* ev[EVNO];
		for(int i=0; i < EVNO; ++i)
			ev[i] = new sys::event();
		for(int i=0; i < EVNO; ++i)
			delete ev[i];
	}
}

void test_event::dtor()
{
	stl::cout << "\n\n\tdtor---------------------------------------------------";
	// copy of ::ctor() test function
	{
		sys::event ev;
		CPPUNIT_ASSERT( true );
	}
	{
		sys::event* ev = new sys::event();
		delete ev;
		CPPUNIT_ASSERT( true );
	}
	{
		const int EVNO=10;
		sys::event ev[EVNO];
		for(int i=0; i < EVNO; ++i)
			(ev[i]);
		CPPUNIT_ASSERT( true );
	}
	{
		const int EVNO=10;
		sys::event* ev[EVNO];
		for(int i=0; i < EVNO; ++i)
			ev[i] = new sys::event();
		for(int i=0; i < EVNO; ++i)
			delete ev[i];
	}
}

//! Class: A thread waiting for the event to be signaled
class EWaitForEventThread : public sys::thread
{
public:
	EWaitForEventThread(sys::event* ev, int sec)
	: m_ev(ev), m_sec(sec){}
	~EWaitForEventThread() {}
	unsigned long run()
	{
		printf("\n\t\tthread %d: wait event", m_sec);
		CPPUNIT_ASSERT( m_ev->lock() == 0 );
		printf("\n\t\tthread %d: woke up-working", m_sec);
		sleep(m_sec);
		return m_sec;
	}
private:
	sys::event*	m_ev;
	int				m_sec;
};

//! Class: A thread signaling an event.
class ESignalEventThread : public sys::thread
{
public:
	ESignalEventThread(sys::event* ev, int sec)
	: m_ev(ev), m_sec(sec){}
	~ESignalEventThread(){}
	unsigned long run()
	{
		printf("\n\t\tthread %d: wait", m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d: setevent", m_sec);
		CPPUNIT_ASSERT( m_ev->setevent() == 0 );
		return m_sec;		
	}
private:
	sys::event*	m_ev;
	int				m_sec;
};
void test_event::lock()
{
	stl::cout << "\n\n\tlock---------------------------------------------------";
	stl::cout << "\n\n";
	{
		// 1 thread wait for signal
		sys::event ev;
		EWaitForEventThread t(&ev, 1);
		CPPUNIT_ASSERT( t.resume() == 0 );
		printf("\n\tmain: wait for thread to resume");
		sleep(1);
		CPPUNIT_ASSERT( ev.unlock() == 0 );
		
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
	}
	stl::cout << "\n\n";
	{
		// more threads waiting for signal
		sys::event ev;
		const int THNO = 400;				// ulimits enforced proc limit
		stl::vector<EWaitForEventThread*> t;
		for(size_t i=0; i < THNO; ++i)
			t.push_back(new EWaitForEventThread(&ev, i%6));
		
		for(size_t i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		printf("\n\tmain: resumed %d threads", THNO);

		sleep(5);							// hope all threads are scheduled
		CPPUNIT_ASSERT( ev.unlock() == 0 ); // are all threads listening ?
		
		unsigned long retval = 0;
		for(size_t i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			CPPUNIT_ASSERT( t[i]->get_exit_code(&retval) == 0 );
			CPPUNIT_ASSERT( retval == i%6 );
			printf("\n\tmain: joined thread %lu", i);
		}
		for(size_t i=0; i < THNO; ++i)
			delete t[i];
	}
	stl::cout << "\n\n";
	{
		sys::event ev;
		ESignalEventThread t(&ev, 5);
		printf("\n\tmain: wait for signal");
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( ev.lock() == 0 );
		printf("\n\tmain: signaled");
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
	}
	stl::cout << "\n\n";
	{
		sys::event ev;
		const int THNO=6;
		ESignalEventThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new ESignalEventThread(&ev, i*2+5);
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		printf("\n\tmain: waiting for %d signals", THNO);
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT(ev.lock() == 0);
			printf("\n\tmain: signal");
		}
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
		}
		for(int i=0; i < THNO; ++i)
			delete t[i];
	}
}

//! Class: A thread waiting with timeout for an event;
class ETimedWaitForEventThread : public sys::thread
{
public:
	ETimedWaitForEventThread(sys::event* ev, int sec)
	: m_ev(ev), m_sec(sec), m_signaled(false) {}
	~ETimedWaitForEventThread() {}
	unsigned long run()
	{
		printf("\n\t\tthread %d: timedwait", m_sec);
		if( m_ev->trylock(m_sec*1e3) == 0 )
		{
			printf("\n\t\tthread %d: woke up", m_sec);
			m_signaled = true;
		}
		else
		{
			printf("\n\t\tthread %d: failed to wake up", m_sec);
		}
		return m_sec;
	}
	bool get_signaled() const { return m_signaled; }	
private:
	sys::event*	m_ev;
	int				m_sec;
	bool			m_signaled;
};

void test_event::trylock()
{
	stl::cout << "\n\n\ttrylock------------------------------------------------";	
	stl::cout << "\n\n";
	{
		/*	Thread will wait for an event that is not signaled from main thread
			ever. */
		sys::event ev;
		ETimedWaitForEventThread t(&ev, 0);
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		CPPUNIT_ASSERT( t.get_signaled() == false );
	}
	stl::cout << "\n\n";
	{
		/*	Thread will wait for an event that is signaled from main thread. */
		sys::event ev;
		ETimedWaitForEventThread t(&ev, 10);
		CPPUNIT_ASSERT( t.resume() == 0 );
		sleep(2);
		printf("\n\tmain: signaling");
		CPPUNIT_ASSERT( ev.setevent() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		CPPUNIT_ASSERT( t.get_signaled() == true );
		printf("\n\tmain: joined thread");
	}
	stl::cout << "\n\n";
	{
		/* Few threads will wait for an event that will not get signaled. */
		sys::event ev;
		const int THNO=400;				// ulimits enforced proc limit
		ETimedWaitForEventThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new ETimedWaitForEventThread(&ev, i%6);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		printf("\n\tmain: threads resumed, no event will be signaled");
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			CPPUNIT_ASSERT( t[i]->get_signaled() == false );
			printf("\n\tmain: joined thread %d", i);
		}
		for(int i=0; i < THNO; ++i)
			delete t[i];
	}
	stl::cout << "\n\n";
	{
		/* Few threads will wait for an event that will get signaled from main. */
		sys::event ev;
		const int THNO=400;						// ulimits enforced proc limit
		ETimedWaitForEventThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new ETimedWaitForEventThread(&ev, 60); // wait reasonable time
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		printf("\n\tmain: resumed %d threads", THNO);
		sleep(5);								// hope all are scheduled
		printf("\n\tmain: signaling");
		CPPUNIT_ASSERT( ev.setevent() == 0 );	// are all threads listening ? if not, bad luck.
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			CPPUNIT_ASSERT( t[i]->get_signaled() == true );
			printf("\n\tmain: joined thread %d", i);
		}
		for(int i=0; i < THNO; ++i)
			delete t[i];
	}
	stl::cout << "\n\n";
	{
		sys::event ev;
		ESignalEventThread t(&ev, 2);
		printf("\n\tmain: wait for event");
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( ev.trylock(120*1e3) == 0 );
		printf("\n\tmain: got the signal");
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
	}
	stl::cout << "\n\n";
	{
		/*	Starting THNO threads and will get in main a signal from each of them. */
		sys::event ev;
		const int THNO=6;
		ESignalEventThread* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new ESignalEventThread(&ev, i*2+3);// 2 sec interval
		printf("\n\tmain: resuming %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		printf("\n\tmain: waiting for %d signals", THNO);
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT(ev.trylock(180*1e3) == 0);
			printf("\n\tmain: signal");
		}
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
		}
		for(int i=0; i < THNO; ++i)
			delete t[i];
	}
}

class EWaitForEventThread2 : public sys::thread
{
public:
	EWaitForEventThread2(sys::event* ev, int sec)
	: m_ev(ev), m_sec(sec) {}
	~EWaitForEventThread2() {}
	sys::event* get_event() const { return m_ev; }
	unsigned long run()
	{
		printf("\n\t\tthread %d: waiting", m_sec);
		CPPUNIT_ASSERT( m_ev->lock() == 0 );
		printf("\n\t\tthread %d: signaled, working", m_sec);
		sleep(m_sec);
		return m_sec;
	}
private:
	sys::event*	m_ev;
	int				m_sec;
};

void test_event::unlock()
{
	stl::cout << "\n\n\tunlock-------------------------------------------------";
	stl::cout << "\n\n";
	{
		/* No thread locked on the event. */
		sys::event ev;
		ETimedWaitForEventThread t(&ev, 0);
		printf("\n\tmain: thread resume");
		CPPUNIT_ASSERT( t.resume() == 0 );
		sleep(5);
		CPPUNIT_ASSERT( ev.unlock() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
		CPPUNIT_ASSERT( t.get_signaled() == false );		
	}
	stl::cout << "\n\n";
	{
		/* 1 thread locked on the event. */
		sys::event ev;
		ETimedWaitForEventThread t(&ev, 10);
		printf("\n\tmain: thread resume");
		CPPUNIT_ASSERT( t.resume() == 0 );
		sleep(5);		
		CPPUNIT_ASSERT( ev.unlock() == 0 );
		CPPUNIT_ASSERT( t.join() == 0 );
		printf("\n\tmain: joined thread");
		CPPUNIT_ASSERT( t.get_signaled() == true );	
	}
	stl::cout << "\n\n";
	{
		const int THNO=400;						// ulimits enforced proc limit
		EWaitForEventThread2* t[THNO];
		for(int i=0; i < THNO; ++i)
			t[i] = new EWaitForEventThread2(new sys::event(), 2);
		printf("\n\tmain: starting %d threads", THNO);
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		sleep(5);								// hope all are scheduled
		printf("\n\tmain: signaling");
		for(int i=0; i < THNO; ++i)
		{
			sys::event* ev = t[i]->get_event();
			CPPUNIT_ASSERT( ev->unlock() == 0 ); // is the thread listening ? if not, bad luck.
		}
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			printf("\n\tmain: joined thread %d", i);
		}
		for(int i=0; i < THNO; ++i)
		{
			sys::event* ev = t[i]->get_event();
			delete ev;
			delete t[i];
		}
	}
}
// maybe one of the 2 needed only
void test_event::setevent()
{
	stl::cout << "\n\n\tsetevent-----------------------------------------------";
	CPPUNIT_ASSERT( true ); // all similar with unlock
}


//##########################END  TEST  SUITE######################################