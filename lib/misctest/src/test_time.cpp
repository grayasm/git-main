/*
  Copyright (C) 2015 Mihai Vasilian

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
#include "test_time.hpp"

//c++
#include <iostream>

//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries
#include "exception.hpp"
#include "string.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"
#include "time.hpp"



void test_time::setUp()
{
}

void test_time::tearDown()
{
}

//########################################################################
// test suite

// -- main class --
void test_time::ctor()
{
	misc::cout << "\n\n\t******************************************************";
	misc::cout <<   "\n\t* TESTING HEADER: time.hpp                           *";
	misc::cout <<   "\n\t******************************************************";
	
	misc::cout << "\n\n\tctor -------------------------------------------------";

	misc::time t0;
	CPPUNIT_ASSERT( t0.tostring() == U("1970-JAN-1 0:0:0") );

	/*
		Time Changes in Berlin over the years
		Daylight Saving Time (DST) changes do not necessarily occur on the same 
		date every year.
		2014	Sun, 30 Mar, 02:00	CET -> CEST	+1 hour (DST start)	UTC+2h
				Sun, 26 Oct, 03:00	CEST -> CET	-1 hour (DST end)	UTC+1h
		2015	Sun, 29 Mar, 02:00	CET -> CEST	+1 hour (DST start)	UTC+2h
				Sun, 25 Oct, 03:00	CEST -> CET	-1 hour (DST end)	UTC+1h
		2016	Sun, 27 Mar, 02:00	CET -> CEST	+1 hour (DST start)	UTC+2h
				Sun, 30 Oct, 03:00	CEST -> CET	-1 hour (DST end)	UTC+1h
		2017	Sun, 26 Mar, 02:00	CET -> CEST	+1 hour (DST start)	UTC+2h
				Sun, 29 Oct, 03:00	CEST -> CET	-1 hour (DST end)	UTC+1h
		2018	Sun, 25 Mar, 02:00	CET -> CEST	+1 hour (DST start)	UTC+2h
				Sun, 28 Oct, 03:00	CEST -> CET	-1 hour (DST end)	UTC+1h
	*/
	misc::time t1(2014, misc::time::MAR, 30, 2, 0, 0);
	CPPUNIT_ASSERT( t1.tostring() == U("2014-MAR-30 2:0:0"));
	
	misc::time t2(2014, misc::time::OCT, 26, 3, 0, 0);
	CPPUNIT_ASSERT( t2.tostring() == U("2014-OCT-26 3:0:0"));
	
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	CPPUNIT_ASSERT( t3.tostring() == U("2015-MAR-29 2:0:0"));
	
	misc::time t4(2015, misc::time::OCT, 25, 3, 0, 0);
	CPPUNIT_ASSERT( t4.tostring() == U("2015-OCT-25 3:0:0"));
	
	misc::time t5(2016, misc::time::MAR, 27, 2, 0, 0);
	CPPUNIT_ASSERT( t5.tostring() == U("2016-MAR-27 2:0:0"));
	
	misc::time t6(2016, misc::time::OCT, 30, 3, 0, 0);
	CPPUNIT_ASSERT( t6.tostring() == U("2016-OCT-30 3:0:0"));
	
	misc::time t7(2017, misc::time::MAR, 26, 2, 0, 0);
	CPPUNIT_ASSERT( t7.tostring() == U("2017-MAR-26 2:0:0"));
	
	misc::time t8(2017, misc::time::OCT, 29, 3, 0, 0);
	CPPUNIT_ASSERT( t8.tostring() == U("2017-OCT-29 3:0:0"));
	
	misc::time t9(2018, misc::time::MAR, 25, 2, 0, 0);
	CPPUNIT_ASSERT( t9.tostring() == U("2018-MAR-25 2:0:0"));
	
	misc::time t10(2018, misc::time::OCT, 28, 3, 0, 0);
	CPPUNIT_ASSERT( t10.tostring() == U("2018-OCT-28 3:0:0"));	
}

void test_time::copy_ctor()
{
	misc::cout << "\n\n\tcopy_ctor --------------------------------------------";
	
	misc::time t0;
	misc::time t1(t0);
	CPPUNIT_ASSERT( t1.tostring() == U("1970-JAN-1 0:0:0") );
	
	misc::time t2(2015, misc::time::APR, 25, 16, 42, 38);
	misc::time t3 = t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2015-APR-25 16:42:38") );
}

void test_time::copy_op()
{
	misc::cout << "\n\n\tcopy_op ----------------------------------------------";
	misc::time t0, t1;
	t1 = t0;
	CPPUNIT_ASSERT( t1.tostring() == U("1970-JAN-1 0:0:0") );
	
	misc::time t2(2015, misc::time::APR, 25, 16, 42, 38), t3;
	t3 = t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2015-APR-25 16:42:38") );
}

void test_time::sub_op()
{
	misc::cout << "\n\n\tsub_op -----------------------------------------------";
	
	misc::time t1(2015, misc::time::APR, 25, 1, 0, 0);
	misc::time t2(2015, misc::time::APR, 24, 2, 10, 10);
	
	// cannot subtract from past the future; don't want to deal with negative
	// time in the class.
	bool illegalsub = false;
	try
	{
		misc::time t3 = t2 - t1;
	}catch(...){ illegalsub = true; }
	CPPUNIT_ASSERT ( illegalsub );
	
	misc::time t4 = t1 - t2;
	CPPUNIT_ASSERT( t4.tostring() == U("1970-JAN-1 22:49:50") );
}

void test_time::add_op()
{
	misc::cout << "\n\n\tadd_op -----------------------------------------------";
	
	misc::time t1(2014, misc::time::MAR, 29, 23, 49, 50);
	misc::time t2(1970, misc::time::JAN, 1,   2, 10, 10);
	misc::time t3 = t1 + t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2014-MAR-30 2:0:0") );
}

void test_time::lt_op()
{
	misc::cout << "\n\n\tlt_op ------------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t1 < t2 );
	CPPUNIT_ASSERT( !(t2 < t3) );
	CPPUNIT_ASSERT( t3 < t4 );
	CPPUNIT_ASSERT( t1 < t3 );
	CPPUNIT_ASSERT( t1 < t4 );
}

void test_time::gt_op()
{
	misc::cout << "\n\n\tgt_op ------------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t4 > t1 );
	CPPUNIT_ASSERT( t3 > t1 );
	CPPUNIT_ASSERT( t4 > t3 );
	CPPUNIT_ASSERT( !(t3 > t2) );
	CPPUNIT_ASSERT( t2 > t1 );	
}

void test_time::eq_op()
{
	misc::cout << "\n\n\teq_op ------------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t1 == t2) );
	CPPUNIT_ASSERT( t2 == t3 );
	CPPUNIT_ASSERT( !(t3 == t4) );
	CPPUNIT_ASSERT( !(t1 == t3) );
	CPPUNIT_ASSERT( !(t1 == t4) );	
}

void test_time::neq_op()
{
	misc::cout << "\n\n\tneq_op -----------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t1 != t2 );
	CPPUNIT_ASSERT( !(t2 != t3) );
	CPPUNIT_ASSERT( t3 != t4 );
	CPPUNIT_ASSERT( t1 != t3 );
	CPPUNIT_ASSERT( t1 != t4 );	
}

void test_time::lte_op()
{
	misc::cout << "\n\n\tlte_op -----------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t4 <= t3) );
	CPPUNIT_ASSERT( t3 <= t2 );
	CPPUNIT_ASSERT( !(t2 <= t1) );
	CPPUNIT_ASSERT( !(t4 <= t1) );
	CPPUNIT_ASSERT( !(t3 <= t1) );
}

void test_time::gte_op()
{
	misc::cout << "\n\n\tgte_op -----------------------------------------------";
	
	misc::time t1(2015, misc::time::MAR, 29, 1, 59, 59);
	misc::time t2(2015, misc::time::MAR, 29, 1, 60, 0);
	misc::time t3(2015, misc::time::MAR, 29, 2, 0, 0);
	misc::time t4(2015, misc::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t1 >= t2) );
	CPPUNIT_ASSERT( t2 >= t3 );
	CPPUNIT_ASSERT( !(t2 >= t4) );
	CPPUNIT_ASSERT( !(t3 >= t4) );
	CPPUNIT_ASSERT( t4 >= t1 );
}

void test_time::incr_op()
{
	misc::cout << "\n\n\tincr_op ----------------------------------------------";
	
	misc::time t1(2014, misc::time::DEC, 31, 23, 59, 59);
	misc::time t2(2015, misc::time::JAN, 1, 0, 0, 9);
	t1 += 10; //sec
	CPPUNIT_ASSERT( t1 == t2 );	
}

void test_time::decr_op()
{
	misc::cout << "\n\n\tdecr_op ----------------------------------------------";
	
	misc::time t1(2014, misc::time::DEC, 31, 23, 59, 59);
	misc::time t2(2015, misc::time::JAN, 1, 0, 0, 9);
	t2 -= 10; //sec
	CPPUNIT_ASSERT( t1 == t2 );	
	
	misc::time t3(1969, misc::time::DEC, 31, 23, 59, 50);
	misc::time t4;
	t4 -= 10;
	CPPUNIT_ASSERT( t3 == t4 );
}

void test_time::tostring()
{
	misc::cout << "\n\n\ttostring ---------------------------------------------";
	
	misc::time t0;
	CPPUNIT_ASSERT( t0.tostring() == U("1970-JAN-1 0:0:0") );
}

void test_time::tolocaltime()
{
	misc::cout << "\n\n\ttolocaltime ------------------------------------------";
	
	misc::time t0;
	CPPUNIT_ASSERT( t0.tolocaltime() != U("1970-JAN-1 0:0:0") );
}

void test_time::wday()
{
	misc::cout << "\n\n\twday -------------------------------------------------";
	
	misc::time t1(2015, misc::time::APR, 25, 17, 40, 53);
	CPPUNIT_ASSERT( misc::time::SAT == t1.wday() );
}

void test_time::yday()
{
	misc::cout << "\n\n\tyday -------------------------------------------------";
	
	misc::time t1(2015, misc::time::APR, 25, 17, 40, 53);
	CPPUNIT_ASSERT( 114 == t1.yday() );
}


