/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_list_hpp__
#define __test_list_hpp__


//c++
//....


class test_list
{
public:
    test_list() = default;
    ~test_list() = default;
    void run();
    

    void ctor();
    void assign_op();
    void assign();
    void get_allocator();
    void begin();
    void end();
    void rbegin();
    void rend();
    void resize();
    void front();
    void back();
    void push_front();
    void pop_front();
    void push_back();
    void pop_back();
    void insert();
    void erase();
    void swap();
    void clear();
    void splice();
    void remove();
    void unique();
    void merge();
    void sort();
    void reverse();
    void perf1();
};



#endif//__test_vector_hpp__
