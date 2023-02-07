/*
Copyright (C) 2012 Mihai Vasilian
*/



#ifndef __tree_t_hpp__
#define __tree_t_hpp__




//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>

//libraries




class test_tree : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(test_tree);
    CPPUNIT_TEST(test_00);
	CPPUNIT_TEST(preorder_it);
	CPPUNIT_TEST(preorder_const_it);
	CPPUNIT_TEST(postorder_it);
	CPPUNIT_TEST(postorder_const_it);
	CPPUNIT_TEST(first_branch_it);
	CPPUNIT_TEST(first_branch_const_it);
	CPPUNIT_TEST(child_it);
	CPPUNIT_TEST(child_const_it);

	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST(dtor);
	CPPUNIT_TEST(copy_ctor);
	CPPUNIT_TEST(copy_op);
	CPPUNIT_TEST(get_it);
	CPPUNIT_TEST(push_back_val);
	CPPUNIT_TEST(push_front_val);
	CPPUNIT_TEST(insert_sibling_before_val);
	CPPUNIT_TEST(insert_sibling_after_val);
	CPPUNIT_TEST(push_back_child_val);
	CPPUNIT_TEST(push_front_child_val);
	CPPUNIT_TEST(push_back_tree);
	CPPUNIT_TEST(push_front_tree);
	CPPUNIT_TEST(insert_sibling_before_tree);
	CPPUNIT_TEST(insert_sibling_after_tree);
	CPPUNIT_TEST(push_back_child_tree);
	CPPUNIT_TEST(push_front_child_tree);
	CPPUNIT_TEST(preorder_begin);
	CPPUNIT_TEST(preorder_end);
	CPPUNIT_TEST(preorder_begin_it);
	CPPUNIT_TEST(preorder_end_it);

	CPPUNIT_TEST(postorder_begin);
	CPPUNIT_TEST(postorder_end);
	CPPUNIT_TEST(postorder_begin_it);
	CPPUNIT_TEST(postorder_end_it);

	CPPUNIT_TEST(first_branch_begin);
	CPPUNIT_TEST(first_branch_end);
	CPPUNIT_TEST(first_branch_begin_it);
	CPPUNIT_TEST(first_branch_end_it);

	CPPUNIT_TEST(child_begin);
	CPPUNIT_TEST(child_end);
	CPPUNIT_TEST(child_begin_it);
	CPPUNIT_TEST(child_end_it);

	CPPUNIT_TEST(siblings_begin);
	CPPUNIT_TEST(siblings_end);
	CPPUNIT_TEST(siblings_begin_it);
	CPPUNIT_TEST(siblings_end_it);	

	CPPUNIT_TEST(empty);
	CPPUNIT_TEST(size);
	CPPUNIT_TEST(clear);
	CPPUNIT_TEST(erase);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 2000;

    //test suite begin
    void test_00();
	// -- iterators --
	void preorder_it();
	void preorder_const_it();
	void postorder_it();
	void postorder_const_it();
	void first_branch_it();
	void first_branch_const_it();
	void child_it();
	void child_const_it();
	

	// -- main class --
	void ctor();
	void dtor();
	void copy_ctor();
	void copy_op();
	void get_it();
	void push_back_val();
	void push_front_val();
	void insert_sibling_before_val();
	void insert_sibling_after_val();
	void push_back_child_val();
	void push_front_child_val();
	void push_back_tree();
	void push_front_tree();
	void insert_sibling_before_tree();
	void insert_sibling_after_tree();
	void push_back_child_tree();
	void push_front_child_tree();
	void preorder_begin();
	void preorder_end();
	void preorder_begin_it();
	void preorder_end_it();

	void postorder_begin();
	void postorder_end();
	void postorder_begin_it();
	void postorder_end_it();

	void first_branch_begin();
	void first_branch_end();
	void first_branch_begin_it();
	void first_branch_end_it();

	void child_begin();
	void child_end();
	void child_begin_it();
	void child_end_it();

	void siblings_begin();
	void siblings_end();
	void siblings_begin_it();
	void siblings_end_it();	

	void empty();
	void size();
	void clear();
	void erase();

    //test suite end
	//template version

	//////////////////////////////////////////////////////////////////////////
	template<typename container>
	void preorder_it(const char* msg);
	template<typename container>
	void preorder_const_it(const char* msg);
	template<typename container>
	void postorder_it(const char* msg);
	template<typename container>
	void postorder_const_it(const char* msg);
	template<typename container>
	void first_branch_it(const char* msg);
	template<typename container>
	void first_branch_const_it(const char* msg);
	template<typename container>
	void child_it(const char* msg);
	template<typename container>
	void child_const_it(const char* msg);
	

	// -- main class --
	template<typename container>
	void ctor(const char* msg);
	template<typename container>
	void dtor(const char* msg);
	template<typename container>
	void copy_ctor(const char* msg);
	template<typename container>
	void copy_op(const char* msg);
	template<typename container>
	void get_it(const char* msg);
	template<typename container>
	void push_back_val(const char* msg);
	template<typename container>
	void push_front_val(const char* msg);
	template<typename container>
	void insert_sibling_before_val(const char* msg);
	template<typename container>
	void insert_sibling_after_val(const char* msg);
	template<typename container>
	void push_back_child_val(const char* msg);
	template<typename container>
	void push_front_child_val(const char* msg);
	template<typename container>
	void push_back_tree(const char* msg);
	template<typename container>
	void push_front_tree(const char* msg);
	template<typename container>
	void insert_sibling_before_tree(const char* msg);
	template<typename container>
	void insert_sibling_after_tree(const char* msg);
	template<typename container>
	void push_back_child_tree(const char* msg);
	template<typename container>
	void push_front_child_tree(const char* msg);
	template<typename container>
	void preorder_begin(const char* msg);
	template<typename container>
	void preorder_end(const char* msg);
	template<typename container>
	void preorder_begin_it(const char* msg);
	template<typename container>
	void preorder_end_it(const char* msg);

	template<typename container>
	void postorder_begin(const char* msg);
	template<typename container>
	void postorder_end(const char* msg);
	template<typename container>
	void postorder_begin_it(const char* msg);
	template<typename container>
	void postorder_end_it(const char* msg);

	template<typename container>
	void first_branch_begin(const char* msg);
	template<typename container>
	void first_branch_end(const char* msg);
	template<typename container>
	void first_branch_begin_it(const char* msg);
	template<typename container>
	void first_branch_end_it(const char* msg);

	template<typename container>
	void child_begin(const char* msg);
	template<typename container>
	void child_end(const char* msg);
	template<typename container>
	void child_begin_it(const char* msg);
	template<typename container>
	void child_end_it(const char* msg);

	template<typename container>
	void siblings_begin(const char* msg);
	template<typename container>
	void siblings_end(const char* msg);
	template<typename container>
	void siblings_begin_it(const char* msg);
	template<typename container>
	void siblings_end_it(const char* msg);	

	template<typename container>
	void empty(const char* msg);
	template<typename container>
	void size(const char* msg);
	template<typename container>
	void clear(const char* msg);
	template<typename container>
	void erase(const char* msg);

};


#endif//__tree_t_hpp__
