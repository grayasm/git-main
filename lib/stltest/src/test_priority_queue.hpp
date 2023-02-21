/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_priority_queue_hpp__
#define __test_priority_queue_hpp__


//c++
//....


class test_priority_queue
{
public:
	test_priority_queue() = default;
	~test_priority_queue() = default;
    void run();


	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;


    //test begin
	void ctor();
	void dtor();
	void empty();
	void size();
	void top();
	void push();
	void pop();
    //test end

    //////////////////////////////////////////////////////////////////////////
    //template version of test function
	template<typename Container, typename Compare>
	void ctor(const char* msg);
	template<typename Container, typename Compare>
	void dtor(const char* msg);
	template<typename Container, typename Compare>
	void empty(const char* msg);
	template<typename Container, typename Compare>
	void size(const char* msg);
	template<typename Container, typename Compare>
	void top(const char* msg);
	template<typename Container, typename Compare>
	void push(const char* msg);
	template<typename Container, typename Compare>
	void pop(const char* msg);
    //////////////////////////////////////////////////////////////////////////
};



#endif//__test_priority_queue_hpp__
