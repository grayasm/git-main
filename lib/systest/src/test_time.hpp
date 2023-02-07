/*
Copyright (C) 2015 Mihai Vasilian
*/

#ifndef __test_time_hpp__
#define __test_time_hpp__



//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries



class test_time : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_time);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(copy_ctor);
	CPPUNIT_TEST(copy_op);
	CPPUNIT_TEST(sub_op);
	CPPUNIT_TEST(add_op);
	CPPUNIT_TEST(lt_op);
	CPPUNIT_TEST(gt_op);
	CPPUNIT_TEST(eq_op);
	CPPUNIT_TEST(neq_op);
	CPPUNIT_TEST(lte_op);
	CPPUNIT_TEST(gte_op);
	CPPUNIT_TEST(incr_op);
	CPPUNIT_TEST(decr_op);
	CPPUNIT_TEST(tostring);
	CPPUNIT_TEST(tolocaltime);
	CPPUNIT_TEST(totime_t);
	CPPUNIT_TEST(sec_);
	CPPUNIT_TEST(min_);
	CPPUNIT_TEST(hour_);
	CPPUNIT_TEST(mday_);
	CPPUNIT_TEST(mon_);
	CPPUNIT_TEST(year_);
	CPPUNIT_TEST(wday);
	CPPUNIT_TEST(yday);
	CPPUNIT_TEST(isdst);
	CPPUNIT_TEST_SUITE_END();
	
public:
	void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;
		
	
	// -- main class --
	void ctor();
	void copy_ctor();
	void copy_op();
	void sub_op();
	void add_op();
	void lt_op();
	void gt_op();
	void eq_op();
	void neq_op();
	void lte_op();
	void gte_op();
	void incr_op();
	void decr_op();
	void tostring();
	void tolocaltime();
	void totime_t();
	void sec_();
	void min_();
	void hour_();
	void mday_();
	void mon_();
	void year_();
	void wday();
	void yday();
	void isdst();	
};

#endif // __test_time_hpp__

