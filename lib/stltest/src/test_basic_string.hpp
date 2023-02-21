/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_basic_string_hpp__
#define __test_basic_string_hpp__


//c++
//....


class test_basic_string
{
   


public:
    test_basic_string() = default;
    ~test_basic_string() = default;
    void run();

    void correctness(); // detect allowed types at compile time and trigger error
    void ctor();
    void assign_op();
    void size();    // + length + capacity
    void resize();
    void reserve();
    void clear();   // + empty
    void append_op();
    void append();
    void push_back();
    void assign();
    void insert();
    void erase();
    void replace();
    void copy();
    void swap();
    void find();
    void rfind();
    void find_first_of();
    void find_last_of();
    void find_first_not_of();
    void find_last_not_of();
    void substr();
    void compare();
    void perf1();       // performance test    
};



#endif//__test_basic_string_hpp__
