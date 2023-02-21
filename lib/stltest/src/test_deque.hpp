/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_deque_hpp__
#define __test_deque_hpp__


//c
//c++


//misc
#include "exception.hpp"
#include "deque.hpp"
#include "string.hpp"



class test_deque
{
public:
    test_deque() = default;
    ~test_deque() = default;
    void run();


	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;


	//////////////////////////////////////////////////////////////////////////
	//test begin
    void ctor();
    void dtor();
    void op_assign();
    void begin();
    void end();
    void rbegin();
    void rend();
    void size();
    void max_size();
    void resize();
    void empty();
    void op_acc();
    void at();
    void front();
    void back();
    void assign();
    void push_back();
    void push_front();
    void pop_back();
    void pop_front();
    void insert();
    void erase();
    void swap_ambiguity();
    void clear();
	void g_swap();
	void op_eq();
	void op_neq();
	void op_lt();
	void op_lte();
	void op_gt();
	void op_gte();


    //test end
    //////////////////////////////////////////////////////////////////////////
    //template version of test function
    template<typename Container>
    void ctor(const char* msg);
    template<typename Container>
    void dtor(const char* msg);
    template<typename Container>
    void op_assign(const char* msg);
    template<typename Container>
    void begin(const char* msg);
    template<typename Container>
    void end(const char* msg);
    template<typename Container>
    void rbegin(const char* msg);
    template<typename Container>
    void rend(const char* msg);
    template<typename Container>
    void size(const char* msg);
    template<typename Container>
    void max_size(const char* msg);
    template<typename Container>
    void resize(const char* msg);
    template<typename Container>
    void empty(const char* msg);
    template<typename Container>
    void op_acc(const char* msg);
    template<typename Container>
    void at(const char* msg);
    template<typename Container>
    void front(const char* msg);
    template<typename Container>
    void back(const char* msg);
    template<typename Container>
    void assign(const char* msg);
    template<typename Container>
    void push_back(const char* msg);
    template<typename Container>
    void push_front(const char* msg);
    template<typename Container>
    void pop_back(const char* msg);
    template<typename Container>
    void pop_front(const char* msg);
    template<typename Container, typename AssocContainer>
    void insert(const char* msg);
    template<typename Container>
    void erase(const char* msg);
    template<typename Container>
    void swap_ambiguity(const char* msg);
    template<typename Container>
    void clear(const char* msg);
	template<typename Container>
	void g_swap(const char* msg);
	template<typename Container>
	void op_eq(const char* msg);
	template<typename Container>
	void op_neq(const char* msg);
	template<typename Container>
	void op_lt(const char* msg);
	template<typename Container>
	void op_lte(const char* msg);
	template<typename Container>
	void op_gt(const char* msg);
	template<typename Container>
	void op_gte(const char* msg);

    //////////////////////////////////////////////////////////////////////////
};//class test_deque


#endif//__test_deque_hpp__
