/*
Copyright (C) 2015 Mihai Vasilian
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
#include "systest_util.hpp"
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
	stl::cout << "\n\n\t******************************************************";
	stl::cout <<   "\n\t* TESTING HEADER: time.hpp                           *";
	stl::cout <<   "\n\t******************************************************";
	
	stl::cout << "\n\n\tctor -------------------------------------------------";

	sys::time t0;
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
	sys::time t1(2014, sys::time::MAR, 30, 2, 0, 0);
	CPPUNIT_ASSERT( t1.tostring() == U("2014-MAR-30 2:0:0"));
	
	sys::time t2(2014, sys::time::OCT, 26, 3, 0, 0);
	CPPUNIT_ASSERT( t2.tostring() == U("2014-OCT-26 3:0:0"));
	
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	CPPUNIT_ASSERT( t3.tostring() == U("2015-MAR-29 2:0:0"));
	
	sys::time t4(2015, sys::time::OCT, 25, 3, 0, 0);
	CPPUNIT_ASSERT( t4.tostring() == U("2015-OCT-25 3:0:0"));
	
	sys::time t5(2016, sys::time::MAR, 27, 2, 0, 0);
	CPPUNIT_ASSERT( t5.tostring() == U("2016-MAR-27 2:0:0"));
	
	sys::time t6(2016, sys::time::OCT, 30, 3, 0, 0);
	CPPUNIT_ASSERT( t6.tostring() == U("2016-OCT-30 3:0:0"));
	
	sys::time t7(2017, sys::time::MAR, 26, 2, 0, 0);
	CPPUNIT_ASSERT( t7.tostring() == U("2017-MAR-26 2:0:0"));
	
	sys::time t8(2017, sys::time::OCT, 29, 3, 0, 0);
	CPPUNIT_ASSERT( t8.tostring() == U("2017-OCT-29 3:0:0"));
	
	sys::time t9(2018, sys::time::MAR, 25, 2, 0, 0);
	CPPUNIT_ASSERT( t9.tostring() == U("2018-MAR-25 2:0:0"));
	
	sys::time t10(2018, sys::time::OCT, 28, 3, 0, 0);
	CPPUNIT_ASSERT( t10.tostring() == U("2018-OCT-28 3:0:0"));

	sys::time ts1("03.30.2014 02:00:00");
	CPPUNIT_ASSERT(ts1 == t1);

	sys::time ts2("10.26.2014 03:00:00");
	CPPUNIT_ASSERT(ts2 == t2);

	sys::time ts3("03.29.2015 02:00:00");
	CPPUNIT_ASSERT(ts3 == t3);

	sys::time ts4("10.25.2015  3:0:0");
	CPPUNIT_ASSERT(ts4 == t4);

	sys::time ts5("3.27.2016 2:0:0");
	CPPUNIT_ASSERT(ts5 == t5);

	sys::time ts6("10.30.2016 03:00:00");
	CPPUNIT_ASSERT(ts6 == t6);

	sys::time ts7("3.26.2017 2:0:0");
	CPPUNIT_ASSERT(ts7 == t7);

	sys::time ts8("10.29.2017 3:0:0");
	CPPUNIT_ASSERT(ts8 == t8);

	sys::time ts9("3.25.2018 02:00:00");
	CPPUNIT_ASSERT(ts9 == t9);

	sys::time ts10("10.28.2018 03:00:00");
	CPPUNIT_ASSERT(ts10 == t10);
}

void test_time::copy_ctor()
{
	stl::cout << "\n\n\tcopy_ctor --------------------------------------------";
	
	sys::time t0;
	sys::time t1(t0);
	CPPUNIT_ASSERT( t1.tostring() == U("1970-JAN-1 0:0:0") );
	
	sys::time t2(2015, sys::time::APR, 25, 16, 42, 38);
	sys::time t3 = t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2015-APR-25 16:42:38") );
}

void test_time::copy_op()
{
	stl::cout << "\n\n\tcopy_op ----------------------------------------------";
	sys::time t0, t1;
	t1 = t0;
	CPPUNIT_ASSERT( t1.tostring() == U("1970-JAN-1 0:0:0") );
	
	sys::time t2(2015, sys::time::APR, 25, 16, 42, 38), t3;
	t3 = t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2015-APR-25 16:42:38") );
}

void test_time::sub_op()
{
	stl::cout << "\n\n\tsub_op -----------------------------------------------";
	
	sys::time t1(2015, sys::time::APR, 25, 1, 0, 0);
	sys::time t2(2015, sys::time::APR, 24, 2, 10, 10);
	
	// cannot subtract from past the future; don't want to deal with negative
	// time in the class.
	bool illegalsub = false;
	try
	{
		sys::time t3 = t2 - t1;
	}catch(...){ illegalsub = true; }
	CPPUNIT_ASSERT ( illegalsub );
	
	sys::time t4 = t1 - t2;
	CPPUNIT_ASSERT( t4.tostring() == U("1970-JAN-1 22:49:50") );
}

void test_time::add_op()
{
	stl::cout << "\n\n\tadd_op -----------------------------------------------";
	
	sys::time t1(2014, sys::time::MAR, 29, 23, 49, 50);
	sys::time t2(1970, sys::time::JAN, 1,   2, 10, 10);
	sys::time t3 = t1 + t2;
	CPPUNIT_ASSERT( t3.tostring() == U("2014-MAR-30 2:0:0") );
}

void test_time::lt_op()
{
	stl::cout << "\n\n\tlt_op ------------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t1 < t2 );
	CPPUNIT_ASSERT( !(t2 < t3) );
	CPPUNIT_ASSERT( t3 < t4 );
	CPPUNIT_ASSERT( t1 < t3 );
	CPPUNIT_ASSERT( t1 < t4 );
}

void test_time::gt_op()
{
	stl::cout << "\n\n\tgt_op ------------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t4 > t1 );
	CPPUNIT_ASSERT( t3 > t1 );
	CPPUNIT_ASSERT( t4 > t3 );
	CPPUNIT_ASSERT( !(t3 > t2) );
	CPPUNIT_ASSERT( t2 > t1 );	
}

void test_time::eq_op()
{
	stl::cout << "\n\n\teq_op ------------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t1 == t2) );
	CPPUNIT_ASSERT( t2 == t3 );
	CPPUNIT_ASSERT( !(t3 == t4) );
	CPPUNIT_ASSERT( !(t1 == t3) );
	CPPUNIT_ASSERT( !(t1 == t4) );	
}

void test_time::neq_op()
{
	stl::cout << "\n\n\tneq_op -----------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( t1 != t2 );
	CPPUNIT_ASSERT( !(t2 != t3) );
	CPPUNIT_ASSERT( t3 != t4 );
	CPPUNIT_ASSERT( t1 != t3 );
	CPPUNIT_ASSERT( t1 != t4 );	
}

void test_time::lte_op()
{
	stl::cout << "\n\n\tlte_op -----------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t4 <= t3) );
	CPPUNIT_ASSERT( t3 <= t2 );
	CPPUNIT_ASSERT( !(t2 <= t1) );
	CPPUNIT_ASSERT( !(t4 <= t1) );
	CPPUNIT_ASSERT( !(t3 <= t1) );
}

void test_time::gte_op()
{
	stl::cout << "\n\n\tgte_op -----------------------------------------------";
	
	sys::time t1(2015, sys::time::MAR, 29, 1, 59, 59);
	sys::time t2(2015, sys::time::MAR, 29, 1, 60, 0);
	sys::time t3(2015, sys::time::MAR, 29, 2, 0, 0);
	sys::time t4(2015, sys::time::MAR, 29, 2, 1, 1);
	
	CPPUNIT_ASSERT( !(t1 >= t2) );
	CPPUNIT_ASSERT( t2 >= t3 );
	CPPUNIT_ASSERT( !(t2 >= t4) );
	CPPUNIT_ASSERT( !(t3 >= t4) );
	CPPUNIT_ASSERT( t4 >= t1 );
}

void test_time::incr_op()
{
	stl::cout << "\n\n\tincr_op ----------------------------------------------";
	
	sys::time t1(2014, sys::time::DEC, 31, 23, 59, 59);
	sys::time t2(2015, sys::time::JAN, 1, 0, 0, 9);
	t1 += 10; //sec
	CPPUNIT_ASSERT( t1 == t2 );	
}

void test_time::decr_op()
{
	stl::cout << "\n\n\tdecr_op ----------------------------------------------";
	
	sys::time t1(2014, sys::time::DEC, 31, 23, 59, 59);
	sys::time t2(2015, sys::time::JAN, 1, 0, 0, 9);
	t2 -= 10; //sec
	CPPUNIT_ASSERT( t1 == t2 );	
}

void test_time::tostring()
{
	stl::cout << "\n\n\ttostring ---------------------------------------------";
	
	sys::time t0;
	CPPUNIT_ASSERT( t0.tostring() == U("1970-JAN-1 0:0:0") );
}

void test_time::tolocaltime()
{
	stl::cout << "\n\n\ttolocaltime ------------------------------------------";
	
	sys::time t0;
	CPPUNIT_ASSERT( t0.tolocaltime() != U("1970-JAN-1 0:0:0") );
}

void test_time::totime_t()
{
	stl::cout << "\n\n\ttotime_t ---------------------------------------------";

	time_t tm = 1393725600; // 2-mar-2014 02:00:00

	sys::time t0("3.2.2014 2:0:0");
	CPPUNIT_ASSERT(t0.totime_t() == tm);
}

void test_time::sec_()
{
	stl::cout << "\n\n\tsec_ -------------------------------------------------";

	sys::time t0("3.2.2014 2:0:59");
	CPPUNIT_ASSERT(t0.sec_() == 59);
}

void test_time::min_()
{
	stl::cout << "\n\n\tmin_ -------------------------------------------------";

	sys::time t0("3.2.2014 2:59:00");
	CPPUNIT_ASSERT(t0.min_() == 59);
}

void test_time::hour_()
{
	stl::cout << "\n\n\thour_ ------------------------------------------------";

	sys::time t0("3.2.2014 23:0:0");
	CPPUNIT_ASSERT(t0.hour_() == 23);
}

void test_time::mday_()
{
	stl::cout << "\n\n\tmday_ ------------------------------------------------";

	sys::time t0("3.29.2014 02:0:0");
	CPPUNIT_ASSERT(t0.mday_() == 29);
}

void test_time::mon_()
{
	stl::cout << "\n\n\tmon_ -------------------------------------------------";

	sys::time t0("11.2.2014 03:0:0");
	CPPUNIT_ASSERT(t0.mon_() == 11);
}

void test_time::year_()
{
	stl::cout << "\n\n\tyear_ ------------------------------------------------";

	sys::time t0("11.2.2014 03:0:0");
	CPPUNIT_ASSERT(t0.year_() == 2014);

	/*	https://msdn.microsoft.com/en-us/library/d1y53h2a.aspx
		When using _mktime32 and if timeptr references a date after
		23:59:59 January 18, 2038, Coordinated Universal Time (UTC), 
		it will return –1 cast to type time_t.

		_mktime64 will return –1 cast to type __time64_t if timeptr
		references a date after
		23:59:59, December 31, 3000, UTC.
	*/
	sys::time t1("1.18.2038 23:59:59");
	CPPUNIT_ASSERT(t1.tostring() == U("2038-JAN-18 23:59:59"));
	t1 += sys::time::hourSEC;
	stl::string t1str = t1.tostring();
	CPPUNIT_ASSERT(t1str == U("2038-JAN-19 0:59:59"));
}


void test_time::wday()
{
	stl::cout << "\n\n\twday -------------------------------------------------";
	
	sys::time t1(2015, sys::time::APR, 25, 17, 40, 53);
	CPPUNIT_ASSERT( sys::time::SAT == t1.wday() );
}

void test_time::yday()
{
	stl::cout << "\n\n\tyday -------------------------------------------------";
	
	sys::time t1(2015, sys::time::APR, 25, 17, 40, 53);
	CPPUNIT_ASSERT( 114 == t1.yday() );
}

void test_time::isdst()
{
	stl::cout << "\n\n\tisdst ------------------------------------------------";
	// EST (Eastern Standard Time) -> 11.MAR.2018 02:00
	// EDT (Eastern Daylight Time) 11.MAR.2018 (+1h) -> 4.NOV.2018 (-1h)
	// EST is -0500 UTC
	sys::time t1("3.09.2018 0:0:0"); // no DST
	sys::time t2("3.15.2018 0:0:0"); // DST may be active
	
	CPPUNIT_ASSERT(t1.isdst() == 0);
	CPPUNIT_ASSERT(t2.isdst() == 0); // should be zero, DST not set.
}
