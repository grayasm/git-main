/*
Copyright (C) 2015 Mihai Vasilian
*/

#ifndef __test_time_hpp__
#define __test_time_hpp__



class test_time
{
public:
	void run();

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

