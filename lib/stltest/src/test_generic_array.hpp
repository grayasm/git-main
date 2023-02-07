/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_generic_array_hpp__
#define __test_generic_array_hpp__



//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries
#include "generic_array.hpp"




class test_generic_array : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(test_generic_array);

	// Integrity checks
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(assignament_op);
	CPPUNIT_TEST(begin);
	CPPUNIT_TEST(end);
	CPPUNIT_TEST(rbegin);
	CPPUNIT_TEST(rend);
	CPPUNIT_TEST(size);
	CPPUNIT_TEST(length);
	CPPUNIT_TEST(max_size);
	CPPUNIT_TEST(resize);
	CPPUNIT_TEST(capacity);
	CPPUNIT_TEST(reserve);
	CPPUNIT_TEST(clear);
	CPPUNIT_TEST(empty);
	CPPUNIT_TEST(operator_access_element);
	CPPUNIT_TEST(at);
	CPPUNIT_TEST(operator_plus_equal);
	CPPUNIT_TEST(append);
	CPPUNIT_TEST(push_back);
	CPPUNIT_TEST(assign);
	CPPUNIT_TEST(insert);
	CPPUNIT_TEST(erase);
	CPPUNIT_TEST(replace);
	CPPUNIT_TEST(swap);
	CPPUNIT_TEST(c_str);
	CPPUNIT_TEST(data);
	CPPUNIT_TEST(get_allocator);
	CPPUNIT_TEST(copy);
	CPPUNIT_TEST(find);
	CPPUNIT_TEST(rfind);
	CPPUNIT_TEST(find_first_of);
	CPPUNIT_TEST(find_last_of);
	CPPUNIT_TEST(find_first_not_of);
	CPPUNIT_TEST(find_last_not_of);
	CPPUNIT_TEST(substr);
	CPPUNIT_TEST(compare);    

	// finalize	
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
		static const int		m_print_time = 1;
		static const size_t		m_container_size = 2000;


	//////////////////////////////////////////////////////////////////////////
	// Integrity checks
	void ctor();
	void dtor();
	void assignament_op();
	void begin();
	void end();
	void rbegin();
	void rend();
	void size();
	void length();
	void max_size();
	void resize();
	void capacity();
	void reserve();
	void clear();
	void empty();
	void operator_access_element();
	void at();
	void operator_plus_equal();
	void append();
	void push_back();
	void assign();
	void insert();
	void erase();
	void replace();
	void swap();
	void c_str();
	void data();
	void get_allocator();
	void copy();
	void find();
	void rfind();
	void find_first_of();
	void find_last_of();
	void find_first_not_of();
	void find_last_not_of();
	void substr();
	void compare();

	//////////////////////////////////////////////////////////////////////////
	template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	template<typename Container>
	void assignament_op(const char* msg);
	template<typename Container>
	void begin(const char* msg);
	template<typename Container>
	void end(const char* msg);
	template<typename Container>
	void rbegin(const char* msg);
	template<typename Container>
	void rend(const char* msg);
	template<typename Container>
	void resize(const char* msg);
	template<typename Container>
	void reserve(const char* msg);
	template<typename Container>
	void clear(const char* msg);
	template<typename Container>	
	void operator_access_element(const char* msg);
	template<typename Container>
	void at(const char* msg);
	template<typename Container>
	void operator_plus_equal(const char* msg);
	template<typename Container>
	void append(const char* msg);
	template<typename Container>
	void push_back(const char* msg);
	template<typename Container>
	void assign(const char* msg);
	template<typename Container>
	void insert(const char* msg);
	template<typename Container>
	void erase(const char* msg);
	template<typename Container>
	void replace(const char* msg);
	template<typename Container>
	void swap(const char* msg);
	template<typename Container>
	void copy(const char* msg);
	template<typename Container>
	void find(const char* msg);
	template<typename Container>
	void rfind(const char* msg);
	template<typename Container>
	void find_first_of(const char* msg);
	template<typename Container>
	void find_last_of(const char* msg);
	template<typename Container>
	void find_first_not_of(const char* msg);
	template<typename Container>
	void find_last_not_of(const char* msg);
	template<typename Container>
	void substr(const char* msg);
	template<typename Container>
	void compare(const char* msg);
	//////////////////////////////////////////////////////////////////////////
};




#endif//__test_generic_array_hpp__
