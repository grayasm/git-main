/*
Copyright (C) 2012 Mihai Vasilian
*/


#ifndef __test_vector_hpp__
#define __test_vector_hpp__


//c++
//....


class test_vector
{
public:
    test_vector() = default;
    ~test_vector() = default;
	void run();


    void ctor();
    void assign_op();
    void assign();
    void begin();
    void end();
    void rbegin();
    void rend();
    void resize();
    void capacity();
    void reserve();
    void at_and_op();
    void front();
    void back();
    void push_back();
    void pop_back();
    void insert();
    void erase();
    void swap();
    void clear();
    void get_allocator();
    void relational_op();
    void perf1();
};


#endif//__test_vector_hpp__
