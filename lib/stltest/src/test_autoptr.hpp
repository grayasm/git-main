/*
Copyright (C) 2009 Mihai Vasilian
*/


#ifndef __autoptr_t_hpp__
#define __autoptr_t_hpp__


//libraries
#include "autoptr.hpp"



class test_autoptr
{

public:
    test_autoptr() = default;
    ~test_autoptr() = default;
    void run();

	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //begin test suite
    void test_assignment_with_different_type();
    void test_assignment_with_different_type1();
    void test_assignment_with_different_type3();
    void test_operator_less();
    void test_operator_great();
    void test_sort();
    void test_derived_operator_less();
    void test_derived_operator_great();
    void test_self_assignament();
    void test_child_assignament();
    //end test suite
};


#endif//__autoptr_t_hpp__
