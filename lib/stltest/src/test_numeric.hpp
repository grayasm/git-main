/*
Copyright (C) 2012 Mihai Vasilian
*/




#ifndef __test_numeric_hpp__
#define __test_numeric_hpp__


//c++
//....
#include <stdlib.h>


class test_numeric
{
public:
	test_numeric() = default;
	~test_numeric() = default;
	void run();
    

	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;

	//////////////////////////////////////////////////////////////////////////	
    //test begin
    void accumulate();
	void adjacent_difference();
	void inner_product();
	void partial_sum();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
	void accumulate(const char* msg);
	template<typename Container>
	void adjacent_difference(const char* msg);
	template<typename Container>
	void inner_product(const char* msg);
	template<typename Container>
	void partial_sum(const char* msg);
    //////////////////////////////////////////////////////////////////////////
};


#endif//__test_numeric_hpp__
