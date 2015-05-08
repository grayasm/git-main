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

//###########################BEGIN TEST CLASS ####################################
void test_event::setUp()
{
}

void test_event::tearDown()
{
}

//##########################BEGIN TEST SUITE######################################
class thread0 : public misc::thread
{
public:
	thread0(misc::event* ev, int sec)
	: m_ev(ev) , m_sec(sec) {}
	~thread0(){}
	int run()
	{
		printf("\n\t\tthread %d: sleep", m_sec);
		sleep(m_sec);
		printf("\n\t\tthread %d: setevent", m_sec);
		m_ev->setevent();
		return m_sec;
	}
private:
	misc::event*	m_ev;
	int				m_sec;
};

class thread2 : public misc::thread
{
public:
	thread2(misc::event* ev, int sec)
	: m_ev(ev), m_sec(sec) {}
	~thread2() {}
	int run()
	{
		printf("\n\t\tthread %d: wait", m_sec);
		m_ev->lock();
		printf("\n\t\tthread %d: woke up", m_sec);
		printf("\n\t\tthread %d: working", m_sec);
		sleep(m_sec);
		return m_sec;
	}
private:
	misc::event*	m_ev;
	int				m_sec;
	
};
void test_event::ctor()
{
	// waiting in the main thread + signaling the event from a separate thread.
	// waiting in a thread and signaling the event from main thread
	{
		misc::event ev;
		thread2* t[2];
		for(int i=0; i < 2; ++i)
			t[i] = new thread2(&ev, i+1);

		for(int i=0; i < 2; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		
		printf("\n\tmain: sleep 4");
		sleep(4);
		
		CPPUNIT_ASSERT( ev.setevent() == 0 );

		for(int i=0; i < 2; ++i)
			CPPUNIT_ASSERT( t[i]->join() == 0 );

		for(int i=0; i < 2; ++i)
			CPPUNIT_ASSERT( t[i]->resume() == 0 );
		
		printf("\n\tmain: sleep 4");
		sleep(4);
		

		CPPUNIT_ASSERT( ev.setevent() == 0 );

		for(int i=0; i < 2; ++i)
		{
			CPPUNIT_ASSERT( t[i]->join() == 0 );
			delete t[i];
		}
	}
}

void test_event::dtor()
{
	
}

void test_event::lock()
{
	
}

void test_event::trylock()
{
	
}

void test_event::unlock()
{
	
}
// maybe one of the 2 needed only
void test_event::setevent()
{
	
}

void test_event::pulseevent()
{
	
}

void test_event::resetevent()
{
	
}
//##########################END  TEST  SUITE######################################