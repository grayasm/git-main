/*
Copyright (C) 2013 Mihai Vasilian
*/


//this
#include "test_thread.hpp"


//c++
#include <iostream>

//acutest
#include "acutest.h"


//libraries
#include "string.hpp"
#include "vector.hpp"
#include "exception.hpp"
#include "unistd.hpp"
#include "stream.hpp"




//###########################BEGIN TEST CLASS ####################################
void test_thread::run_()
{
	ctor();
	dtor();
	run();
	resume();
	join();
	get_exit_code();
}


//##########################BEGIN TEST SUITE######################################
class Ttthread : public sys::thread
{
public:
	Ttthread()
		: m_a(-1)
		, m_started(false) 
	{
		m_wait = new int;
		*m_wait = 0;
	}
	Ttthread(int a)
		: m_a(a)
		, m_started(false)
	{
		m_wait = new int;
		*m_wait = 0;
	}
	~Ttthread() 
	{
		delete m_wait;
	}
	unsigned long run()
	{
		m_started = true;
		if(m_a > 0) // max sleep time
		{
			if(*m_wait < m_a)
			{
				// sleep(1) is breaking testing because it introduces big delay.
				// if the thread is scheduled for running, sleep the entire value 1 time.
				sleep(m_a);
				*m_wait += m_a;
			}
		}
		return *m_wait;
	}//run
	void seta(int a){ m_a = a; }
	int geta() const { return m_a; }
	bool getstarted() const { return m_started; }
private:
	int		m_a;
	int*	m_wait;
	bool	m_started;
};

void test_thread::ctor()
{
	stl::cout << "\n\n\t******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER thread.hpp                          *";
	stl::cout <<   "\n\t******************************************************";	

	stl::cout << "\n\n\t ctor ------------------------------------------------";
	
	
	{
		// default ctor - thread is not running.
		Ttthread t0, t1, t2;
		TEST_CHECK(t0.geta() == -1);
		TEST_CHECK(t0.getstarted() == false);
		TEST_CHECK(t1.geta() == -1);
		TEST_CHECK(t1.getstarted() == false);
		TEST_CHECK(t2.geta() == -1);
		TEST_CHECK(t2.getstarted() == false);
		// no join for not started thread
	}
	{
		// parameterized ctor - thread is not running.
		Ttthread t0(0), t1(1), t2(2);
		TEST_CHECK(t0.geta() == 0);
		TEST_CHECK(t0.getstarted() == false);
		TEST_CHECK(t1.geta() == 1);
		TEST_CHECK(t1.getstarted() == false);
		TEST_CHECK(t2.geta() == 2);
		TEST_CHECK(t2.getstarted() == false);
		// no join for not started thread
	}
	{
		// parameterized ctor - thread is not running.
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i );
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		// deallocate the memory
		for(int i=0; i < THMAX; ++i)
		{
			// no join for not started thread
			delete t[i];
		}
	}
}

void test_thread::dtor()
{
	stl::cout << "\n\n\t dtor ------------------------------------------------";

	{
		// on the stack
		Ttthread t0, t1, t2;
		TEST_CHECK(t0.geta() == -1);
		TEST_CHECK(t0.getstarted() == false);
		TEST_CHECK(t1.geta() == -1);
		TEST_CHECK(t1.getstarted() == false);
		TEST_CHECK(t2.geta() == -1);
		TEST_CHECK(t2.getstarted() == false);
		// no join for not started thread
	}
	{
		// dynamic allocated
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i );
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
		{
			// no join for not started thread
			delete t[i];
		}
	}
	{
		// destructor throws		
	}
}

void test_thread::run()
{
	stl::cout << "\n\n\t run -------------------------------------------------";
	
	{
		Ttthread t0, t1, t2;
		TEST_CHECK( t0.resume() == 0 );
		TEST_CHECK( t1.resume() == 0 );
		TEST_CHECK( t2.resume() == 0 );
		
		sleep(2);//wait for threads to resume
		
		TEST_CHECK(t0.geta() == -1);
		TEST_CHECK(t0.getstarted() == true);
		TEST_CHECK(t1.geta() == -1);
		TEST_CHECK(t1.getstarted() == true);
		TEST_CHECK(t2.geta() == -1);
		TEST_CHECK(t2.getstarted() == true);

		TEST_CHECK( t0.join() == 0 );
		TEST_CHECK( t1.join() == 0 );
		TEST_CHECK( t2.join() == 0 );
	}
	{
		// dynamic allocated
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i%6);
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i%6 );
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}
		
		printf("\n\t\t\tsleep(3)");
		sleep(3); // wait for threads to resume
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK(t[i]->geta() == i%6);
			TEST_CHECK(t[i]->getstarted() == true);
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK(t[i]->join() == 0);
			delete t[i];
			printf("\n\t\t\tjoined thread %d", i);
		}
	}
}

void test_thread::resume()
{
	stl::cout << "\n\n\t resume ----------------------------------------------";
	{
		Ttthread t0(0), t1(1), t2(2);
		TEST_CHECK( t0.resume() == 0 );
		TEST_CHECK( t1.resume() == 0 );
		TEST_CHECK( t2.resume() == 0 );
		
		printf("\n\t\t\tsleep(1)");
		sleep(1); // wait for threads to resume		

		TEST_CHECK( t0.join() == 0 );
		TEST_CHECK( t1.join() == 0 );
		TEST_CHECK( t2.join() == 0 );
		
		TEST_CHECK(t0.geta() == 0);
		TEST_CHECK(t0.getstarted() == true);
		TEST_CHECK(t1.geta() == 1);
		TEST_CHECK(t1.getstarted() == true);
		TEST_CHECK(t2.geta() == 2);
		TEST_CHECK(t2.getstarted() == true);
	}
	{
		// dynamic allocated
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i%6);
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i%6 );
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}
		
		printf("\n\t\t\tsleep(3)");
		sleep(3); // wait for threads to resume
		
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK(t[i]->geta() == i%6);
			TEST_CHECK(t[i]->getstarted() == true);
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->join() == 0 );
			delete t[i];
			printf("\n\t\t\tjoined thread %d", i);
		}
	}
	printf("\n\t\t test: join thread and resume again");
	{
		const int THNO = 600;
		stl::vector<Ttthread*> thvec;
		for(int i=0; i < THNO; ++i)
			thvec.push_back(new Ttthread(i%5));
		for(int i=0; i < THNO; ++i)
			TEST_CHECK( thvec[i]->resume() == 0 );

		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( thvec[i]->join() == 0 );
			TEST_CHECK( thvec[i]->geta() == i%5 );
			printf("\n\t\t\tjoined thread %d", i);
		}

		for(int i=0; i < THNO; ++i)
		{
			thvec[i]->seta(i%5+6);
			TEST_CHECK( thvec[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}

		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( thvec[i]->join() == 0 );
			TEST_CHECK( thvec[i]->geta() == i%5+6 );
			printf("\n\t\t\tjoined thread %d", i);
		}		
	}

	printf("\n\t\t test: resume thread and resume again while running");
	{
		const int THNO = 600;
		stl::vector<Ttthread*> thvec;
		for(int i=0; i < THNO; ++i)
			thvec.push_back(new Ttthread(i%3+5));
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( thvec[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
			bool _2ndresume_fail = false;
			try
			{
				thvec[i]->resume();
			}
			catch(stl::exception&)
			{
				_2ndresume_fail = true;
			}
			TEST_CHECK( _2ndresume_fail == true );
		}
		for(int i=0; i < THNO; ++i)
		{
			TEST_CHECK( thvec[i]->join() == 0 );
			TEST_CHECK( thvec[i]->geta() == i%3+5 );
			printf("\n\t\t\tjoined thread %d", i);
		}		
	}
}

void test_thread::join()
{
	stl::cout << "\n\n\t join ------------------------------------------------";
	
	{
		// sleep 10 sec and join TIMEOUT
		Ttthread t(5);
		TEST_CHECK( t.resume() == 0 );
		TEST_CHECK( t.join(1000) != 0 ); // TIMEOUT
		TEST_CHECK( t.join() == 0 );
		TEST_CHECK( t.geta() == 5 );
		TEST_CHECK( t.getstarted() == true );		
	}
	stl::cout << "\n\t\t join TIMEOUT (ok)";
	{
		// sleep 5 sec and join @20 sec ok
		Ttthread t(5);
		TEST_CHECK( t.resume() == 0 );
		sleep(2); // let it be scheduled
		TEST_CHECK( t.join(20000) == 0 ); // OK
		TEST_CHECK( t.geta() == 5 );
		TEST_CHECK( t.getstarted() == true );
	}
	stl::cout << "\n\t\t join @20sec (ok)";
	{
		// sleep 5 sec and join INFINITE ok
		Ttthread t(5);
		TEST_CHECK( t.resume() == 0 );
		TEST_CHECK( t.join(-1) == 0 ); // OK
		TEST_CHECK( t.geta() == 5 );
		TEST_CHECK( t.getstarted() == true );
	}
	stl::cout << "\n\t\t join @INFINITE (ok)";
	
	{
		// dynamic allocated
		static const int THMAX=5;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		// check thread is not running
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i ); // 5 sec space to run
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		// check start all threads
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->resume() == 0 );
			if(i > 3)
			{
				msleep(500);
				TEST_CHECK( t[i]->join(0) != 0 );
				stl::cout << "\n\t\t th: " << i << " join timeout";
			}
		}
		
		// check finished threads
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->join( (THMAX+10) * 1e3 ) == 0 );
			stl::cout << "\n\t\t th: " << i << " joined";
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
			delete t[i];
	}
}

void test_thread::get_exit_code()
{
	stl::cout << "\n\n\t get_exit_code ---------------------------------------";
	
	{
		// sleep 10 sec and join TIMEOUT
		Ttthread t(10);
		unsigned long retval = 0;
		TEST_CHECK( t.resume() == 0 );
		TEST_CHECK( t.join(3 * 1e3) != 0 ); // TIMEOUT
		TEST_CHECK( t.get_exit_code(&retval) != 0 ); // STILL RUNNING
		TEST_CHECK( t.geta() == 10 );
		TEST_CHECK( t.getstarted() == true );
		TEST_CHECK( t.join() == 0 );
	}
	stl::cout << "\n\t\t exitcode @TIMEOUT (ok)";
	{
		// sleep 5 sec and join @20 sec ok
		Ttthread t(5);
		unsigned long retval = 0;
		TEST_CHECK( t.resume() == 0 );
		TEST_CHECK( t.join(20*1e3) == 0 ); // OK
		TEST_CHECK( t.get_exit_code(&retval) == 0 ); // OK
		TEST_CHECK( retval == 5 ); // OK
		TEST_CHECK( t.geta() == 5 );
		TEST_CHECK( t.getstarted() == true );
	}
	stl::cout << "\n\t\t exitcode @20sec (ok)";
	{
		// sleep 5 sec and join INFINITE ok
		Ttthread t(5);
		unsigned long retval = 0;
		TEST_CHECK( t.resume() == 0 );
		TEST_CHECK( t.join(-1) == 0 ); // OK
		TEST_CHECK( t.get_exit_code(&retval) == 0 ); // OK
		TEST_CHECK( retval == 5 ); // OK
		TEST_CHECK( t.geta() == 5 );
		TEST_CHECK( t.getstarted() == true );
	}
	stl::cout << "\n\t\t exitcode @INFINITE (ok)";
	
	{
		// dynamic allocated
		static const int THMAX=10;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		// check thread is not running
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->geta() == i );
			TEST_CHECK( t[i]->getstarted() == false );
		}
		
		// check start all threads
		for(int i=0; i < THMAX; ++i)
		{
			TEST_CHECK( t[i]->resume() == 0 );
			unsigned long retval = 0;
			if(i > 2)
			{
				TEST_CHECK( t[i]->join(0) != 0 );
				TEST_CHECK( t[i]->get_exit_code(&retval) != 0 );
				stl::cout << "\n\t\t th: " << i << " no exit code";
			}
		}
		
		// check finished threads
		for(int i=0; i < THMAX; ++i)
		{
			unsigned long retval = 0;
			TEST_CHECK( t[i]->join((THMAX+20)*1e3) == 0 );
			TEST_CHECK( t[i]->get_exit_code(&retval) == 0 );
			TEST_CHECK( retval == (unsigned long) i );
			stl::cout << "\n\t\t th: " << i << " exit code: " << retval;
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
			delete t[i];
	}
}
//##########################END  TEST  SUITE######################################
