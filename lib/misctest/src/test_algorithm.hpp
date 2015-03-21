/*
  Copyright (C) 2012 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/


#ifndef __test_algorithm_hpp__
#define __test_algorithm_hpp__

//c++
//....

//CppUnit
#include <cppunit/extensions/HelperMacros.h>


//libraries
#include "exception.hpp"
#include "autoptr.hpp"
#include "string.hpp"



class test_algorithm : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(test_algorithm);
	CPPUNIT_TEST(for_each);
	CPPUNIT_TEST(find);
	CPPUNIT_TEST(find_if);
	CPPUNIT_TEST(find_end);
	CPPUNIT_TEST(find_first_of);
	CPPUNIT_TEST(adjacent_find);
	CPPUNIT_TEST(count);
	CPPUNIT_TEST(count_if);
	CPPUNIT_TEST(mismatch);
	CPPUNIT_TEST(equal);
	CPPUNIT_TEST(search);
	CPPUNIT_TEST(search_n);
	CPPUNIT_TEST(copy);
	CPPUNIT_TEST(copy_backward);
	CPPUNIT_TEST(swap);
	CPPUNIT_TEST(swap_ranges);
	CPPUNIT_TEST(iter_swap);
	CPPUNIT_TEST(transform);
	CPPUNIT_TEST(replace);
	CPPUNIT_TEST(replace_if);
	CPPUNIT_TEST(replace_copy);
	CPPUNIT_TEST(replace_copy_if);
	CPPUNIT_TEST(fill);
	CPPUNIT_TEST(fill_n);
	CPPUNIT_TEST(generate);
	CPPUNIT_TEST(generate_n);
	CPPUNIT_TEST(remove);
	CPPUNIT_TEST(remove_if);
	CPPUNIT_TEST(remove_copy);
	CPPUNIT_TEST(remove_copy_if);
	CPPUNIT_TEST(unique);
	CPPUNIT_TEST(unique_copy);
	CPPUNIT_TEST(reverse);
	CPPUNIT_TEST(reverse_copy);
	CPPUNIT_TEST(rotate);
	CPPUNIT_TEST(rotate_copy);
	CPPUNIT_TEST(random_shuffle);
	CPPUNIT_TEST(partition);
	CPPUNIT_TEST(stable_partition);
	CPPUNIT_TEST(sort);
	CPPUNIT_TEST(stable_sort);
	CPPUNIT_TEST(partial_sort);
	CPPUNIT_TEST(partial_sort_copy);
	CPPUNIT_TEST(nth_element);
	CPPUNIT_TEST(upper_bound);
	CPPUNIT_TEST(lower_bound);
	CPPUNIT_TEST(equal_range);
	CPPUNIT_TEST(binary_search);
	CPPUNIT_TEST(merge);
	CPPUNIT_TEST(inplace_merge);
	CPPUNIT_TEST(includes);
	CPPUNIT_TEST(set_union);
	CPPUNIT_TEST(set_intersection);
	CPPUNIT_TEST(set_difference);
	CPPUNIT_TEST(set_symmetric_difference);
	CPPUNIT_TEST(push_heap);
	CPPUNIT_TEST(pop_heap);
	CPPUNIT_TEST(make_heap);
	CPPUNIT_TEST(sort_heap);
	CPPUNIT_TEST(min2);
	CPPUNIT_TEST(max2);
	CPPUNIT_TEST(min_element);
	CPPUNIT_TEST(max_element);
	CPPUNIT_TEST(lexicographical_compare);
	CPPUNIT_TEST(next_permutation);
	CPPUNIT_TEST(prev_permutation);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	static const int		m_print_time = 1;
	static const size_t		m_container_size = 40000;

	//////////////////////////////////////////////////////////////////////////
	//test begin
	//Non-modifying sequence operations:
	void for_each();
	void find();
	void find_if();
	void find_end();
	void find_first_of();
	void adjacent_find();
	void count();
	void count_if();
	void mismatch();
	void equal();
	void search();
	void search_n();
	//Modifying sequence operations:
	void copy();
	void copy_backward();
	void swap();
	void swap_ranges();
	void iter_swap();
	void transform();
	void replace();
	void replace_if();
	void replace_copy();
	void replace_copy_if();
	void fill();
	void fill_n();
	void generate();
	void generate_n();
	void remove();
	void remove_if();
	void remove_copy();
	void remove_copy_if();
	void unique();
	void unique_copy();
	void reverse();
	void reverse_copy();
	void rotate();
	void rotate_copy();
	void random_shuffle();
	void partition();
	void stable_partition();
	//Sorting:
	void sort();
	void stable_sort();
	void partial_sort();
	void partial_sort_copy();
	void nth_element();
	//Binary search (operating on sorted ranges):
	void lower_bound();
	void upper_bound();
	void equal_range();
	void binary_search();
	//Merge (operating on sorted ranges):
	void merge();
	void inplace_merge();
	void includes();
	void set_union();
	void set_intersection();
	void set_difference();
	void set_symmetric_difference();
	//Heap:
	void push_heap();
	void pop_heap();
	void make_heap();
	void sort_heap();
	//Min/max:
	void min2();
	void max2();
	void min_element();
	void max_element();
	void lexicographical_compare();
	void next_permutation();
	void prev_permutation();
	//test end

	//////////////////////////////////////////////////////////////////////////
	//template version of test function

	//Non-modifying sequence operations:
	template<typename Container>
	void for_each(const char* msg);
	template<typename Container>
	void find(const char* msg);
	template<typename Container>
	void find2(const char* msg);
	template<typename Container>
	void find_if(const char* msg);
	template<typename Container>
	void find_if2(const char* msg);
	template<typename Container>
	void find_end(const char* msg);
	template<typename Container>
	void find_end2(const char* msg);
	template<typename Container>
	void find_first_of(const char* msg);
	template<typename Container>
	void adjacent_find(const char* msg);
	template<typename Container>
	void count(const char* msg);
	template<typename Container>
	void count_if(const char* msg);
	template<typename Container>
	void mismatch(const char* msg);
	template<typename Container>
	void equal(const char* msg);
	template<typename Container>
	void equal2(const char* msg);
	template<typename Container>
	void search(const char* msg);
	template<typename Container>
	void search2(const char* msg);
	template<typename Container>
	void search_n(const char* msg);
	template<typename Container>
	void search_n2(const char* msg);
	//Modifying sequence operations:
	template<typename Container>
	void copy(const char* msg);
	template<typename Container>
	void copy_backward(const char* msg);
	template<typename Container>
	void swap(const char* msg);
	template<typename Container>
	void swap_ranges(const char* msg);
	template<typename Container>
	void iter_swap(const char* msg);
	template<typename Container>
	void transform(const char* msg);
	template<typename Container>
	void replace(const char* msg);
	template<typename Container>
	void replace_if(const char* msg);
	template<typename Container>
	void replace_copy(const char* msg);
	template<typename Container>
	void replace_copy_if(const char* msg);
	template<typename Container>
	void fill(const char* msg);
	template<typename Container>
	void fill_n(const char* msg);
	template<typename Container>
	void generate(const char* msg);
	template<typename Container>
	void generate_n(const char* msg);
	template<typename Container>
	void remove(const char* msg);
	template<typename Container>
	void remove_if(const char* msg);
	template<typename Container>
	void remove_if2(const char* msg);
	template<typename Container>
	void remove_copy(const char* msg);
	template<typename Container>
	void remove_copy_if(const char* msg);
	template<typename Container>
	void unique(const char* msg);
	template<typename Container>
	void unique_copy(const char* msg);
	template<typename Container>
	void reverse(const char* msg);
	template<typename Container>
	void reverse_copy(const char* msg);
	template<typename Container>
	void rotate(const char* msg);
	template<typename Container>
	void rotate_copy(const char* msg);
	template<typename Container>
	void random_shuffle(const char* msg);
	template<typename Container>
	void partition(const char* msg);
	template<typename Container>
	void partition2(const char* msg);
	template<typename Container>
	void stable_partition(const char* msg);
	template<typename Container>
	void stable_partition2(const char* msg);
	//Sorting:
	template<typename Container>
	void sort(const char* msg);
	template<typename Container>
	void stable_sort(const char* msg);
	template<typename Container>
	void stable_sort2(const char* msg);
	template<typename Container>
	void partial_sort(const char* msg);
	template<typename Container>
	void partial_sort_copy(const char* msg);
	template<typename Container>
	void nth_element(const char* msg);
	//Binary search (operating on sorted ranges):
	template<typename Container>
	void lower_bound(const char* msg);
	template<typename Container>
	void lower_bound2(const char* msg);
	template<typename Container>
	void upper_bound(const char* msg);
	template<typename Container>
	void equal_range(const char* msg);
	template<typename Container>
	void equal_range2(const char* msg);
	template<typename Container>
	void binary_search(const char* msg);
	template<typename Container>
	void binary_search2(const char* msg);
	//Merge (operating on sorted ranges):
	template<typename Container>
	void merge(const char* msg);
	template<typename Container>
	void merge2(const char* msg);
	template<typename Container>
	void inplace_merge(const char* msg);
	template<typename Container>
	void inplace_merge2(const char* msg);
	template<typename Container>
	void includes(const char* msg);
	template<typename Container>
	void includes2(const char* msg);
	template<typename Container>
	void set_union(const char* msg);
	template<typename Container>
	void set_union2(const char* msg);
	template<typename Container>
	void set_intersection(const char* msg);
	template<typename Container>
	void set_intersection2(const char* msg);
	template<typename Container>
	void set_difference(const char* msg);
	template<typename Container>
	void set_symmetric_difference(const char* msg);
	template<typename Container>
	void set_symmetric_difference2(const char* msg);
	//Heap:
	template<typename Container>
	void push_heap(const char* msg);
	template<typename Container>
	void push_heap2(const char* msg);
	template<typename Container>
	void pop_heap(const char* msg);
	template<typename Container>
	void make_heap(const char* msg);
	template<typename Container>
	void sort_heap(const char* msg);
	//Min/max:
	template<typename Container>
	void min2(const char* msg);
	template<typename Container>
	void max2(const char* msg);
	template<typename Container>
	void min_element(const char* msg);
	template<typename Container>
	void max_element(const char* msg);
	template<typename Container>
	void lexicographical_compare(const char* msg);
	template<typename Container>
	void next_permutation(const char* msg);
	template<typename Container>
	void next_permutation2(const char* msg);
	template<typename Container>
	void prev_permutation(const char* msg);
	template<typename Container>
	void prev_permutation2(const char* msg);
	//////////////////////////////////////////////////////////////////////////
};


#endif//__test_algorithm_hpp__
