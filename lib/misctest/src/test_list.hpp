/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __test_list_hpp__
#define __test_list_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>





class test_list : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_list);     
    CPPUNIT_TEST( ctor );
    CPPUNIT_TEST( dtor );
    CPPUNIT_TEST( cpy_op );
    CPPUNIT_TEST( begin );
    CPPUNIT_TEST( end );
    CPPUNIT_TEST( rbegin );
    CPPUNIT_TEST( rend );
    CPPUNIT_TEST( empty );
    CPPUNIT_TEST( size );
    CPPUNIT_TEST( max_size );
    CPPUNIT_TEST( resize );
    CPPUNIT_TEST( front );
    CPPUNIT_TEST( back );
    CPPUNIT_TEST( assign );
    CPPUNIT_TEST( push_front );
    CPPUNIT_TEST( pop_front );
    CPPUNIT_TEST( push_back );
    CPPUNIT_TEST( pop_back );
    CPPUNIT_TEST( insert );
    CPPUNIT_TEST( erase );
    CPPUNIT_TEST( swap );
    CPPUNIT_TEST( clear );
    CPPUNIT_TEST( splice );
    CPPUNIT_TEST( remove );
    CPPUNIT_TEST( remove_if );
    CPPUNIT_TEST( unique );
    CPPUNIT_TEST( merge );
    CPPUNIT_TEST( sort );
    CPPUNIT_TEST( reverse );
    CPPUNIT_TEST_SUITE_END();
    

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 200;


    //test begin
    void ctor();
    void dtor();
    void cpy_op();
    void begin();
    void end();
    void rbegin();
    void rend();
    void empty();
    void size();
    void max_size();
    void resize();
    void front();
    void back();
    void assign();
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
    void remove_if();
    void unique();
    void merge();
    void sort();
    void reverse();
    //test end

    //performance test for constructor and destructor    
	template<typename Container>
	void ctor(const char* msg);
	template<typename Container>
	void dtor(const char* msg);
	template<typename Container>
	void cpy_op(const char* msg);
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
	void front(const char* msg);
	template<typename Container>
	void back(const char* msg);
	template<typename Container>
	void assign(const char* msg);
	template<typename Container>
	void push_front(const char* msg);
	template<typename Container>
	void pop_front(const char* msg);
	template<typename Container>
	void push_back(const char* msg);
	template<typename Container>
	void pop_back(const char* msg);
	template<typename Container>
	void insert(const char* msg);
	template<typename Container>
	void erase(const char* msg);
	template<typename Container>
	void swap(const char* msg);
	template<typename Container>
	void clear(const char* msg);
	template<typename Container>
	void splice(const char* msg);
	template<typename Container>	
	void remove(const char* msg);
	template<typename Container>
	void remove_if(const char* msg);
	template<typename Container>
	void unique(const char* msg);
	template<typename Container>
	void merge(const char* msg);
	template<typename Container>
	void sort(const char* msg);
	template<typename Container>
	void reverse(const char* msg);

    
};//class test_list


#endif//__test_list_hpp__
