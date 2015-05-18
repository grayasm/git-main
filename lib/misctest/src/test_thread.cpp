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
#include "test_thread.hpp"


//c++
#include <iostream>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


//libraries
#include "string.hpp"
#include "vector.hpp"
#include "exception.hpp"
#include "unistd.hpp"
#include "stream.hpp"




//###########################BEGIN TEST CLASS ####################################
void test_thread::setUp()
{
}

void test_thread::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
class Ttthread : public misc::thread
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
	misc::cout << "\n\n\t******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER thread.hpp                          *";
	misc::cout <<   "\n\t******************************************************";	

	misc::cout << "\n\n\t ctor ------------------------------------------------";
	
	
	{
		// default ctor - thread is not running.
		Ttthread t0, t1, t2;
		CPPUNIT_ASSERT(t0.geta() == -1);
		CPPUNIT_ASSERT(t0.getstarted() == false);
		CPPUNIT_ASSERT(t1.geta() == -1);
		CPPUNIT_ASSERT(t1.getstarted() == false);
		CPPUNIT_ASSERT(t2.geta() == -1);
		CPPUNIT_ASSERT(t2.getstarted() == false);
		// no join for not started thread
	}
	{
		// parameterized ctor - thread is not running.
		Ttthread t0(0), t1(1), t2(2);
		CPPUNIT_ASSERT(t0.geta() == 0);
		CPPUNIT_ASSERT(t0.getstarted() == false);
		CPPUNIT_ASSERT(t1.geta() == 1);
		CPPUNIT_ASSERT(t1.getstarted() == false);
		CPPUNIT_ASSERT(t2.geta() == 2);
		CPPUNIT_ASSERT(t2.getstarted() == false);
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
			CPPUNIT_ASSERT( t[i]->geta() == i );
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
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
	misc::cout << "\n\n\t dtor ------------------------------------------------";

	{
		// on the stack
		Ttthread t0, t1, t2;
		CPPUNIT_ASSERT(t0.geta() == -1);
		CPPUNIT_ASSERT(t0.getstarted() == false);
		CPPUNIT_ASSERT(t1.geta() == -1);
		CPPUNIT_ASSERT(t1.getstarted() == false);
		CPPUNIT_ASSERT(t2.geta() == -1);
		CPPUNIT_ASSERT(t2.getstarted() == false);
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
			CPPUNIT_ASSERT( t[i]->geta() == i );
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
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
	misc::cout << "\n\n\t run -------------------------------------------------";
	
	{
		Ttthread t0, t1, t2;
		CPPUNIT_ASSERT( t0.resume() == 0 );
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		
		sleep(2);//wait for threads to resume
		
		CPPUNIT_ASSERT(t0.geta() == -1);
		CPPUNIT_ASSERT(t0.getstarted() == true);
		CPPUNIT_ASSERT(t1.geta() == -1);
		CPPUNIT_ASSERT(t1.getstarted() == true);
		CPPUNIT_ASSERT(t2.geta() == -1);
		CPPUNIT_ASSERT(t2.getstarted() == true);

		CPPUNIT_ASSERT( t0.join() == 0 );
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
	}
	{
		// dynamic allocated
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i%6);
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->geta() == i%6 );
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
		}
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}
		
		printf("\n\t\t\tsleep(3)");
		sleep(3); // wait for threads to resume
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT(t[i]->geta() == i%6);
			CPPUNIT_ASSERT(t[i]->getstarted() == true);
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT(t[i]->join() == 0);
			delete t[i];
			printf("\n\t\t\tjoined thread %d", i);
		}
	}
}

void test_thread::resume()
{
	misc::cout << "\n\n\t resume ----------------------------------------------";
	{
		Ttthread t0(0), t1(1), t2(2);
		CPPUNIT_ASSERT( t0.resume() == 0 );
		CPPUNIT_ASSERT( t1.resume() == 0 );
		CPPUNIT_ASSERT( t2.resume() == 0 );
		
		printf("\n\t\t\tsleep(1)");
		sleep(1); // wait for threads to resume		

		CPPUNIT_ASSERT( t0.join() == 0 );
		CPPUNIT_ASSERT( t1.join() == 0 );
		CPPUNIT_ASSERT( t2.join() == 0 );
		
		CPPUNIT_ASSERT(t0.geta() == 0);
		CPPUNIT_ASSERT(t0.getstarted() == true);
		CPPUNIT_ASSERT(t1.geta() == 1);
		CPPUNIT_ASSERT(t1.getstarted() == true);
		CPPUNIT_ASSERT(t2.geta() == 2);
		CPPUNIT_ASSERT(t2.getstarted() == true);
	}
	{
		// dynamic allocated
		static const int THMAX=600;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i%6);
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->geta() == i%6 );
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
		}
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}
		
		printf("\n\t\t\tsleep(3)");
		sleep(3); // wait for threads to resume
		
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT(t[i]->geta() == i%6);
			CPPUNIT_ASSERT(t[i]->getstarted() == true);
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			delete t[i];
			printf("\n\t\t\tjoined thread %d", i);
		}
	}
	printf("\n\t\t test: join thread and resume again");
	{
		const int THNO = 600;
		misc::vector<Ttthread*> thvec;
		for(int i=0; i < THNO; ++i)
			thvec.push_back(new Ttthread(i%5));
		for(int i=0; i < THNO; ++i)
			CPPUNIT_ASSERT( thvec[i]->resume() == 0 );

		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( thvec[i]->join() == 0 );
			CPPUNIT_ASSERT( thvec[i]->geta() == i%5 );
			printf("\n\t\t\tjoined thread %d", i);
		}

		for(int i=0; i < THNO; ++i)
		{
			thvec[i]->seta(i%5+6);
			CPPUNIT_ASSERT( thvec[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
		}

		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( thvec[i]->join() == 0 );
			CPPUNIT_ASSERT( thvec[i]->geta() == i%5+6 );
			printf("\n\t\t\tjoined thread %d", i);
		}		
	}

	printf("\n\t\t test: resume thread and resume again while running");
	{
		const int THNO = 600;
		misc::vector<Ttthread*> thvec;
		for(int i=0; i < THNO; ++i)
			thvec.push_back(new Ttthread(i%3+5));
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( thvec[i]->resume() == 0 );
			printf("\n\t\t\tresumed thread %d", i);
			bool _2ndresume_fail = false;
			try
			{
				thvec[i]->resume();
			}
			catch(misc::exception&)
			{
				_2ndresume_fail = true;
			}
			CPPUNIT_ASSERT( _2ndresume_fail == true );
		}
		for(int i=0; i < THNO; ++i)
		{
			CPPUNIT_ASSERT( thvec[i]->join() == 0 );
			CPPUNIT_ASSERT( thvec[i]->geta() == i%3+5 );
			printf("\n\t\t\tjoined thread %d", i);
		}		
	}
}

void test_thread::join()
{
	misc::cout << "\n\n\t join ------------------------------------------------";
	
	{
		// sleep 10 sec and join TIMEOUT
		Ttthread t(5);
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join(1000) != 0 ); // TIMEOUT
		CPPUNIT_ASSERT( t.join() == 0 );
		CPPUNIT_ASSERT( t.geta() == 5 );
		CPPUNIT_ASSERT( t.getstarted() == true );		
	}
	misc::cout << "\n\t\t join TIMEOUT (ok)";
	{
		// sleep 5 sec and join @20 sec ok
		Ttthread t(5);
		CPPUNIT_ASSERT( t.resume() == 0 );
		sleep(2); // let it be scheduled
		CPPUNIT_ASSERT( t.join(20000) == 0 ); // OK
		CPPUNIT_ASSERT( t.geta() == 5 );
		CPPUNIT_ASSERT( t.getstarted() == true );
	}
	misc::cout << "\n\t\t join @20sec (ok)";
	{
		// sleep 5 sec and join INFINITE ok
		Ttthread t(5);
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join(-1) == 0 ); // OK
		CPPUNIT_ASSERT( t.geta() == 5 );
		CPPUNIT_ASSERT( t.getstarted() == true );
	}
	misc::cout << "\n\t\t join @INFINITE (ok)";
	
	{
		// dynamic allocated
		static const int THMAX=5;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		// check thread is not running
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->geta() == i ); // 5 sec space to run
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
		}
		
		// check start all threads
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
			if(i > 3)
			{
				msleep(500);
				CPPUNIT_ASSERT( t[i]->join(0) != 0 );
				misc::cout << "\n\t\t th: " << i << " join timeout";
			}
		}
		
		// check finished threads
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join( (THMAX+10) * 1e3 ) == 0 );
			misc::cout << "\n\t\t th: " << i << " joined";
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
			delete t[i];
	}
}

void test_thread::get_exit_code()
{
	misc::cout << "\n\n\t get_exit_code ---------------------------------------";
	
	{
		// sleep 10 sec and join TIMEOUT
		Ttthread t(10);
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join(3 * 1e3) != 0 ); // TIMEOUT
		CPPUNIT_ASSERT( t.get_exit_code(&retval) != 0 ); // STILL RUNNING
		CPPUNIT_ASSERT( t.geta() == 10 );
		CPPUNIT_ASSERT( t.getstarted() == true );
		CPPUNIT_ASSERT( t.join() == 0 );
	}
	misc::cout << "\n\t\t exitcode @TIMEOUT (ok)";
	{
		// sleep 5 sec and join @20 sec ok
		Ttthread t(5);
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join(20*1e3) == 0 ); // OK
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 ); // OK
		CPPUNIT_ASSERT( retval == 5 ); // OK
		CPPUNIT_ASSERT( t.geta() == 5 );
		CPPUNIT_ASSERT( t.getstarted() == true );
	}
	misc::cout << "\n\t\t exitcode @20sec (ok)";
	{
		// sleep 5 sec and join INFINITE ok
		Ttthread t(5);
		unsigned long retval = 0;
		CPPUNIT_ASSERT( t.resume() == 0 );
		CPPUNIT_ASSERT( t.join(-1) == 0 ); // OK
		CPPUNIT_ASSERT( t.get_exit_code(&retval) == 0 ); // OK
		CPPUNIT_ASSERT( retval == 5 ); // OK
		CPPUNIT_ASSERT( t.geta() == 5 );
		CPPUNIT_ASSERT( t.getstarted() == true );
	}
	misc::cout << "\n\t\t exitcode @INFINITE (ok)";
	
	{
		// dynamic allocated
		static const int THMAX=10;
		Ttthread* t[THMAX];
		for(int i=0; i < THMAX; ++i)
			t[i] = new Ttthread(i);
		
		// check thread is not running
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->geta() == i );
			CPPUNIT_ASSERT( t[i]->getstarted() == false );
		}
		
		// check start all threads
		for(int i=0; i < THMAX; ++i)
		{
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
			unsigned long retval = 0;
			if(i > 2)
			{
				CPPUNIT_ASSERT( t[i]->join(0) != 0 );
				CPPUNIT_ASSERT( t[i]->get_exit_code(&retval) != 0 );
				misc::cout << "\n\t\t th: " << i << " no exit code";
			}
		}
		
		// check finished threads
		for(int i=0; i < THMAX; ++i)
		{
			unsigned long retval = 0;
			CPPUNIT_ASSERT( t[i]->join((THMAX+20)*1e3) == 0 );
			CPPUNIT_ASSERT( t[i]->get_exit_code(&retval) == 0 );
			CPPUNIT_ASSERT( retval == (unsigned long) i );
			misc::cout << "\n\t\t th: " << i << " exit code: " << retval;
		}
		
		// call destructor
		for(int i=0; i < THMAX; ++i)
			delete t[i];
	}
}
//##########################END  TEST  SUITE######################################

