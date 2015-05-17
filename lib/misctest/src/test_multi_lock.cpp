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
		sleep(m_sec);
		m_ml->unlock();
		printf("\n\t\tthread %d: unlocked", m_sec);
		return m_sec;
	}
private:
	misc::multi_lock*	m_ml;
	int					m_sec;
};

void test_multi_lock::ctor()
{
    misc::cout << "\n\n\t*******************************************************";
    misc::cout <<   "\n\t* TESTING HEADER: multi_lock.hpp                      *";
    misc::cout <<   "\n\t*******************************************************";
	
	misc::cout << "\n\n\tctor---------------------------------------------------";
	
	misc::mutex m1,m2;
	CPPUNIT_ASSERT( m1.lock() == 0 );
	CPPUNIT_ASSERT( m2.lock() == 0 );
	misc::sync_base* so[2];
	so[0] = &m1;
	so[1] = &m2;
	
	misc::multi_lock multi(so, 2);

	MLLockThread t(&multi, 2);
	CPPUNIT_ASSERT( t.resume() == 0 );
	printf("\n\tmain: thread resumed, wait 2 sec");
	sleep(2);
	CPPUNIT_ASSERT( m1.unlock() == 0 );
	CPPUNIT_ASSERT( m2.unlock() == 0 );
	CPPUNIT_ASSERT( t.join() == 0 );
	printf("\n\tmain: thread joined");
}
//##########################END  TEST  SUITE######################################

