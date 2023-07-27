/*
Copyright (C) 2009 Mihai Vasilian
*/



//this
#include "test_algorithm.hpp"

//c++ ...
#include <vector>
#include <time.h>
#include <limits.h>
#include <algorithm>

//libraries ...
#include "algorithm.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "stream.hpp"
#include "stltest_util.hpp"

//testing framework
#include "acutest.h"



//############################# BEGIN TEST #####################################

void test_algorithm::run()
{
	for_each();
	find();
	find_if();
	find_end();
	find_first_of();
	adjacent_find();
	count();
	count_if();
	mismatch();
	equal();
	search();
	search_n();
	copy();
	copy_backward();
	swap();
	swap_ranges();
	iter_swap();
	transform();
	replace();
	replace_if();
	replace_copy();
	replace_copy_if();
	fill();
	fill_n();
	generate();
	generate_n();
	remove();
	remove_if();
	remove_copy();
	remove_copy_if();
	unique();
	unique_copy();
	reverse();
	reverse_copy();
	rotate();
	rotate_copy();
	random_shuffle();
	partition();
	stable_partition();
	sort();
	stable_sort();
	partial_sort();
	partial_sort_copy();
	nth_element();
	upper_bound();
	lower_bound();
	equal_range();
	binary_search();
	merge();
	inplace_merge();
	includes();
	set_union();
	set_intersection();
	set_difference();
	set_symmetric_difference();
	push_heap();
	pop_heap();
	make_heap();
	sort_heap();
	min2();
	max2();
	min_element();
	max_element();
	lexicographical_compare();
	next_permutation();
	prev_permutation();

	// new line before TEST RESULT OUTPUT
	stl::cout << "\n";
}

//////////////////////////////////////////////////////////////////////////
//test begin
//Non-modifying sequence operations:
void test_algorithm::for_each()
{	
    stl::cout << "\n\n\t*******************************************************";
    stl::cout <<   "\n\t* TESTING HEADER: algorithm.hpp                       *";
    stl::cout <<   "\n\t*******************************************************";

	stl::cout << "\n\n\tfor_each-----------------------------------------------";
	for_each<std::vector<int> >							("\n\tstd::vector      ");
	for_each<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	for_each<stl::vector<int> >							("\n\tstl::vector      ");
//test does not work with std::allocator
#if !defined(_WIN32)
	for_each<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::find()
{
	stl::cout << "\n\n\tfind---------------------------------------------------";
	find2<std::vector<int> >							("\n\tstd::vector      ");
	find2<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	find<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	find<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::find_if()
{
	stl::cout << "\n\n\tfind_if------------------------------------------------";
	find_if2<std::vector<int> >							("\n\tstd::vector      ");
	find_if2<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	find_if<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	find_if<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::find_end()
{
	stl::cout << "\n\n\tfind_end-----------------------------------------------";
	find_end2<std::vector<int> >						("\n\tstd::vector      ");
	find_end2<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	find_end<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	find_end<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::find_first_of()
{
	stl::cout << "\n\n\tfind_first_of------------------------------------------";
	find_first_of<std::vector<char> >							("\n\tstd::vector      ");
	find_first_of<std::vector<char, stl::allocator<char> > >	("\n\tstd::vector<A>   ");
	find_first_of<stl::vector<char> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	find_first_of<stl::vector<char, std::allocator<char> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::adjacent_find()
{
	stl::cout << "\n\n\tadjacent_find------------------------------------------";
	adjacent_find<std::vector<int> >							("\n\tstd::vector      ");
	adjacent_find<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	adjacent_find<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	adjacent_find<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::count()
{
	stl::cout << "\n\n\tcount--------------------------------------------------";
	count<std::vector<int> >							("\n\tstd::vector      ");
	count<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	count<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	count<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::count_if()
{
	stl::cout << "\n\n\tcount_if-----------------------------------------------";
	count_if<std::vector<int> >							("\n\tstd::vector      ");
	count_if<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	count_if<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	count_if<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::mismatch()
{
	stl::cout << "\n\n\tmismatch-----------------------------------------------";
	mismatch<std::vector<int> >								("\n\tstd::vector      ");
	mismatch<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	mismatch<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	mismatch<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::equal()
{
	stl::cout << "\n\n\tequal--------------------------------------------------";
	equal<std::vector<int> >							("\n\tstd::vector      ");
	equal<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	equal<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	equal<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::search()
{
	stl::cout << "\n\n\tsearch-------------------------------------------------";
	search<std::vector<int> >							("\n\tstd::vector      ");
	search<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	search2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	search2<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::search_n()
{
	stl::cout << "\n\n\tsearch_n-----------------------------------------------";
	search_n<std::vector<int> >							("\n\tstd::vector      ");
	search_n<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	search_n2<stl::vector<int> >						("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	search_n2<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

//Modifying sequence operations:
void test_algorithm::copy()
{
	stl::cout << "\n\n\tcopy---------------------------------------------------";
	copy<std::vector<int> >								("\n\tstd::vector      ");
	copy<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	copy<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	copy<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::copy_backward()
{
	stl::cout << "\n\n\tcopy_backward------------------------------------------";
	copy_backward<std::vector<int> >							("\n\tstd::vector      ");
	copy_backward<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	copy_backward<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	copy_backward<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::swap()
{
	stl::cout << "\n\n\tswap---------------------------------------------------";
	swap<std::vector<int> >										("\n\tstd::vector      ");
	swap<std::vector<int, stl::allocator<int> > >				("\n\tstd::vector<A>   ");
	swap<stl::vector<int> >										("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	swap<stl::vector<int, std::allocator<int> > >				("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::swap_ranges()
{
	stl::cout << "\n\n\tswap_ranges--------------------------------------------";
	swap_ranges<std::vector<int> >								("\n\tstd::vector      ");
	swap_ranges<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	swap_ranges<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	swap_ranges<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::iter_swap()
{
	stl::cout << "\n\n\titer_swap----------------------------------------------";
	iter_swap<std::vector<int> >								("\n\tstd::vector      ");
	iter_swap<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	iter_swap<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	iter_swap<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::transform()
{
	stl::cout << "\n\n\ttransform----------------------------------------------";
	transform<std::vector<int> >								("\n\tstd::vector      ");
	transform<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	transform<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	transform<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::replace()
{
	stl::cout << "\n\n\treplace------------------------------------------------";
	replace<std::vector<int> >									("\n\tstd::vector      ");
	replace<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	replace<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	replace<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::replace_if()
{
	stl::cout << "\n\n\treplace_if---------------------------------------------";
	replace_if<std::vector<int> >								("\n\tstd::vector      ");
	replace_if<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	replace_if<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	replace_if<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::replace_copy()
{
	stl::cout << "\n\n\treplace_copy-------------------------------------------";
	replace_copy<std::vector<int> >								("\n\tstd::vector      ");
	replace_copy<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	replace_copy<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	replace_copy<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::replace_copy_if()
{
	stl::cout << "\n\n\treplace_copy_if----------------------------------------";
	replace_copy_if<std::vector<int> >							("\n\tstd::vector      ");
	replace_copy_if<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	replace_copy_if<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	replace_copy_if<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::fill()
{
	stl::cout << "\n\n\tfill---------------------------------------------------";
	fill<std::vector<int> >										("\n\tstd::vector      ");
	fill<std::vector<int, stl::allocator<int> > >				("\n\tstd::vector<A>   ");
	fill<stl::vector<int> >										("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	fill<stl::vector<int, std::allocator<int> > >				("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::fill_n()
{
	stl::cout << "\n\n\tfill_n-------------------------------------------------";
	fill_n<std::vector<int> >									("\n\tstd::vector      ");
	fill_n<std::vector<int, stl::allocator<int> > >				("\n\tstd::vector<A>   ");
	fill_n<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	fill_n<stl::vector<int, std::allocator<int> > >				("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::generate()
{
	stl::cout << "\n\n\tgenerate-----------------------------------------------";
	generate<std::vector<int> >									("\n\tstd::vector      ");
	generate<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	generate<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	generate<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::generate_n()
{
	stl::cout << "\n\n\tgenerate_n---------------------------------------------";
	generate_n<std::vector<int> >								("\n\tstd::vector      ");
	generate_n<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	generate_n<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	generate_n<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::remove()
{
	stl::cout << "\n\n\tremove-------------------------------------------------";
	remove<std::vector<int> >									("\n\tstd::vector      ");
	remove<std::vector<int, stl::allocator<int> > >				("\n\tstd::vector<A>   ");
	remove<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	remove<stl::vector<int, std::allocator<int> > >				("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::remove_if()
{
	stl::cout << "\n\n\tremove_if----------------------------------------------";
	remove_if2<std::vector<int> >								("\n\tstd::vector      ");
	remove_if2<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	remove_if<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	remove_if<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::remove_copy()
{
	stl::cout << "\n\n\tremove_copy--------------------------------------------";
	remove_copy<std::vector<int> >								("\n\tstd::vector      ");
	remove_copy<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	remove_copy<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	remove_copy<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::remove_copy_if()
{
	stl::cout << "\n\n\tremove_copy_if-----------------------------------------";
	remove_copy_if<std::vector<int> >							("\n\tstd::vector      ");
	remove_copy_if<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	remove_copy_if<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	remove_copy_if<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::unique()
{
	stl::cout << "\n\n\tunique-------------------------------------------------";
	unique<std::vector<int> >								("\n\tstd::vector      ");
	unique<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	unique<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	unique<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::unique_copy()
{
	stl::cout << "\n\n\tunique_copy--------------------------------------------";
	unique_copy<std::vector<int> >							("\n\tstd::vector      ");
	unique_copy<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	unique_copy<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	unique_copy<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::reverse()
{
	stl::cout << "\n\n\treverse------------------------------------------------";
	reverse<std::vector<int> >								("\n\tstd::vector      ");
	reverse<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	reverse<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	reverse<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::reverse_copy()
{
	stl::cout << "\n\n\treverse_copy-------------------------------------------";
	reverse_copy<std::vector<int> >							("\n\tstd::vector      ");
	reverse_copy<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	reverse_copy<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	reverse_copy<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::rotate()
{
	stl::cout << "\n\n\trotate-------------------------------------------------";
	rotate<std::vector<int> >								("\n\tstd::vector      ");
	rotate<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	rotate<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	rotate<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::rotate_copy()
{
	stl::cout << "\n\n\trotate_copy--------------------------------------------";
	rotate_copy<std::vector<int> >							("\n\tstd::vector      ");
	rotate_copy<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	rotate_copy<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	rotate_copy<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::random_shuffle()
{
	stl::cout << "\n\n\trandom_shuffle-----------------------------------------";
	random_shuffle<std::vector<int> >							("\n\tstd::vector      ");
	random_shuffle<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	random_shuffle<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	random_shuffle<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::partition()
{
	stl::cout << "\n\n\tpartition----------------------------------------------";
	partition2<std::vector<int> >								("\n\tstd::vector      ");
	partition2<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	partition<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	partition<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::stable_partition()
{
	stl::cout << "\n\n\tstable_partition---------------------------------------";	
	stable_partition<std::vector<int> >							("\n\tstd::vector      ");
	stable_partition<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	stable_partition2<stl::vector<int> >						("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	stable_partition2<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

//Sorting:
void test_algorithm::sort()
{
	stl::cout << "\n\n\tsort---------------------------------------------------";
	sort<std::vector<int> >							("\n\tstd::vector      ");
	sort<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	sort<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	sort<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::stable_sort()
{
	stl::cout << "\n\n\tstable_sort--------------------------------------------";	
	stable_sort<std::vector<double> >								("\n\tstd::vector      ");
	stable_sort2<stl::vector<double> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	stable_sort2<stl::vector<double, std::allocator<double> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::partial_sort()
{
	stl::cout << "\n\n\tpartial_sort-------------------------------------------";
	partial_sort<std::vector<int> >									("\n\tstd::vector      ");
	partial_sort<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	partial_sort<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	partial_sort<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::partial_sort_copy()
{
	stl::cout << "\n\n\tpartial_sort_copy--------------------------------------";
	partial_sort_copy<std::vector<int> >							("\n\tstd::vector      ");
	partial_sort_copy<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	partial_sort_copy<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	partial_sort_copy<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::nth_element()
{
	stl::cout << "\n\n\tnth_element--------------------------------------------";
	nth_element<std::vector<int> >									("\n\tstd::vector      ");
	nth_element<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	nth_element<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	nth_element<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

//Binary search (operating on sorted ranges):
void test_algorithm::lower_bound()
{
	stl::cout << "\n\n\tlower_bound--------------------------------------------";
	lower_bound2<std::vector<int> >									("\n\tstd::vector      ");
	lower_bound2<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	lower_bound<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	lower_bound<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::upper_bound()
{
	stl::cout << "\n\n\tupper_bound--------------------------------------------";
	upper_bound<std::vector<int> >							("\n\tstd::vector      ");
	upper_bound<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	upper_bound<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	upper_bound<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::equal_range()
{
	stl::cout << "\n\n\tequal_range--------------------------------------------";	
	equal_range2<std::vector<int> >							("\n\tstd::vector      ");
	equal_range<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	equal_range<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::binary_search()
{
	stl::cout << "\n\n\tbinary_search------------------------------------------";
	binary_search<std::vector<int> >							("\n\tstd::vector      ");
	binary_search<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	binary_search2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	binary_search2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

//Merge (operating on sorted ranges):
void test_algorithm::merge()
{
	stl::cout << "\n\n\tmerge--------------------------------------------------";
	merge<std::vector<int> >							("\n\tstd::vector      ");
	merge<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	merge2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	merge2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::inplace_merge()
{
	stl::cout << "\n\n\tinplace_merge------------------------------------------";
	inplace_merge<std::vector<int> >							("\n\tstd::vector      ");
	inplace_merge<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	inplace_merge2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	inplace_merge2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::includes()
{
	stl::cout << "\n\n\tincludes-----------------------------------------------";
	includes<std::vector<int> >								("\n\tstd::vector      ");
	includes<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	includes2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	includes2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::set_union()
{
	stl::cout << "\n\n\tset_union----------------------------------------------";
	set_union<std::vector<int> >							("\n\tstd::vector      ");
	set_union<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	set_union2<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	set_union2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::set_intersection()
{
	stl::cout << "\n\n\tset_intersection---------------------------------------";
	set_intersection<std::vector<int> >							("\n\tstd::vector      ");
	set_intersection<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	set_intersection2<stl::vector<int> >						("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	set_intersection2<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::set_difference()
{
	stl::cout << "\n\n\tset_difference-----------------------------------------";
	set_difference<std::vector<int> >							("\n\tstd::vector      ");
	set_difference<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	set_difference<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	set_difference<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::set_symmetric_difference()
{
	stl::cout << "\n\n\tset_symmetric_difference-------------------------------";
	set_symmetric_difference<std::vector<int> >							("\n\tstd::vector      ");
	set_symmetric_difference<std::vector<int, stl::allocator<int> > >	("\n\tstd::vector<A>   ");
	set_symmetric_difference2<stl::vector<int> >						("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	set_symmetric_difference2<stl::vector<int, std::allocator<int> > >	("\n\tstl::vector<A>   ");
#endif
}

//Heap:
void test_algorithm::push_heap()
{
	stl::cout << "\n\n\tpush_heap----------------------------------------------";
	push_heap<std::vector<int> >								("\n\tstd::vector      ");
	push_heap<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	push_heap2<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	push_heap2<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::pop_heap()
{
	stl::cout << "\n\n\tpop_heap-----------------------------------------------";
	pop_heap<std::vector<int> >								("\n\tstd::vector      ");
	pop_heap<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	pop_heap<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	pop_heap<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::make_heap()
{
	stl::cout << "\n\n\tmake_heap----------------------------------------------";
	make_heap<std::vector<int> >							("\n\tstd::vector      ");
	make_heap<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	make_heap<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	make_heap<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::sort_heap()
{
	stl::cout << "\n\n\tsort_heap----------------------------------------------";
	sort_heap<std::vector<int> >							("\n\tstd::vector      ");
	sort_heap<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	sort_heap<stl::vector<int> >							("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	sort_heap<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

//Min/max:
void test_algorithm::min2()
{
	stl::cout << "\n\n\tmin----------------------------------------------------";
	min2<std::vector<int> >								("\n\tstd::vector      ");
	min2<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	min2<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	min2<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::max2()
{
	stl::cout << "\n\n\tmax----------------------------------------------------";
	max2<std::vector<int> >									("\n\tstd::vector      ");
	max2<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	max2<stl::vector<int> >									("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	max2<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::min_element()
{
	stl::cout << "\n\n\tmin_element--------------------------------------------";
	min_element<std::vector<int> >								("\n\tstd::vector      ");
	min_element<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	min_element<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	min_element<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::max_element()
{
	stl::cout << "\n\n\tmax_element--------------------------------------------";
	max_element<std::vector<int> >								("\n\tstd::vector      ");
	max_element<std::vector<int, stl::allocator<int> > >		("\n\tstd::vector<A>   ");
	max_element<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	max_element<stl::vector<int, std::allocator<int> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::lexicographical_compare()
{
	stl::cout << "\n\n\tlexicographical_compare--------------------------------";
	lexicographical_compare<std::vector<char> >								("\n\tstd::vector      ");
	lexicographical_compare<std::vector<char, stl::allocator<char> > >		("\n\tstd::vector<A>   ");
	lexicographical_compare<stl::vector<char> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	lexicographical_compare<stl::vector<char, std::allocator<char> > >		("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::next_permutation()
{
	stl::cout << "\n\n\tnext_permutation---------------------------------------";
	next_permutation<std::vector<int> >									("\n\tstd::vector      ");
	next_permutation<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	next_permutation2<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	next_permutation2<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

void test_algorithm::prev_permutation()
{
	stl::cout << "\n\n\tprev_permutation---------------------------------------";
	prev_permutation<std::vector<int> >									("\n\tstd::vector      ");
	prev_permutation<std::vector<int, stl::allocator<int> > >			("\n\tstd::vector<A>   ");
	prev_permutation2<stl::vector<int> >								("\n\tstl::vector      ");
	//test does not work with std::allocator
#if !defined(_WIN32)
	prev_permutation2<stl::vector<int, std::allocator<int> > >			("\n\tstl::vector<A>   ");
#endif
}

//test end

//////////////////////////////////////////////////////////////////////////
//template version of test function

//Non-modifying sequence operations:
int myfunction_for_each_integer = 10;
void myfunction_for_each (int i)
{
	TEST_CHECK(i == myfunction_for_each_integer);
	myfunction_for_each_integer += 10;
}

struct myclass_for_each
{
	myclass_for_each():m_count(10){}
	void operator() (int i)
	{
		TEST_CHECK(i == m_count);
		m_count += 10;
	}
	int m_count;
} ;

template<typename Container>
void test_algorithm::for_each(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	typedef void (*Function)(int);

	Container myvector;
	for(Cval j=10; j < 100000; j+=10)
		myvector.push_back(j);
	

	//	TEST
	{
		//	STL
		time_printer tm(msg, m_print_time);

		// for_each(InputIterator first, InputIterator last, Function f)
		myfunction_for_each_integer = 10;
		stl::for_each<It, Function>(myvector.begin(), myvector.end(), myfunction_for_each);

		myclass_for_each myobject_for_each;
		stl::for_each (myvector.begin(), myvector.end(), myobject_for_each);


		//	STD
#if !defined(DEBUG) // fails with MS debug iterator
		// testing Container with STD namespace
		myfunction_for_each_integer = 10;
		std::for_each<It, Function>(myvector.begin(), myvector.end(), myfunction_for_each);

		myclass_for_each myobject_for_each2;
		std::for_each (myvector.begin(), myvector.end(), myobject_for_each2);
#endif
	}
}

template<typename Container>
void test_algorithm::find(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval* mytable = new Cval[m_container_size];
	size_t i=0;
	for(Cval j(0); j < (Cval)m_container_size; ++j, ++i)	mytable[i] = j;

	Container myvector(mytable, mytable + m_container_size);

	// TEST
	{
		time_printer tp(msg, m_print_time);

		Cval* p = 0;

		// STL
		// pointer to array element:
		p = stl::find(mytable, mytable + m_container_size, Cval(m_container_size - 2));
		++p;
		TEST_CHECK(*p == (m_container_size - 1));


		It it;
		// iterator to vector element:
		it = stl::find(myvector.begin(), myvector.end(), Cval(m_container_size - 2));
		it++;

		TEST_CHECK(*it == (m_container_size - 1));
		
		// STD - see find2(...)
	}

	delete[] mytable;
}


template<typename Container>
void test_algorithm::find2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval* mytable = new Cval[m_container_size];
	size_t i=0;
	for(Cval j(0); j < (Cval)m_container_size; ++j, ++i)	mytable[i] = j;

	Container myvector(mytable, mytable + m_container_size);

	// TEST
	{
		time_printer tp(msg, m_print_time);

		Cval* p = 0;

		// STD
		// pointer to array element:
		p = std::find(mytable, mytable + m_container_size, m_container_size - 2);
		++p;
		TEST_CHECK(*p == (m_container_size - 1));


		It it;
		// iterator to vector element:
		it = std::find(myvector.begin(), myvector.end(), Cval(m_container_size - 2));
		it++;

		TEST_CHECK(*it == (m_container_size - 1));
	}

	delete[] mytable;
}


bool IsOdd_find_if (int i) {
	return ((i%2)==1);
}

template<typename T>
struct Struct_find_if {
	T m_val;
	Struct_find_if(const T& val)
		: m_val(val){}

	bool operator()(const T& val){
		return m_val == val;
	}
};

template<typename Container>
void test_algorithm::find_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	
	
	
	It it;
	Cval mydata[] = {10, 25, 40, 55};
	// prepare data
	Container v1(mydata, mydata + 4);
	Container v2;
	
	// v2
	for(Cval i = 0; i < (Cval)m_container_size; ++i)	v2.push_back(i);

	// TEST
	{
		time_printer tm(msg, m_print_time);

		//STL
		// technical
		it = stl::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( *it == 25 );

		v1.erase(it);
		it = stl::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( *it == 55 );

		v1.erase(it);
		it = stl::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( it == v1.end() );

		// performance
		Struct_find_if<Cval> sfif1(m_container_size - 2);
		it = stl::find_if(v2.begin(), v2.end(), sfif1);

		TEST_CHECK( *(++it) == (m_container_size - 1 ));
		
		// STD - see find_if2(...)
	}
}

template<typename Container>
void test_algorithm::find_if2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	
	
	
	It it;
	Cval mydata[] = {10, 25, 40, 55};
	// prepare data
	Container v1(mydata, mydata + 4);
	Container v2;
	
	// v2
	for(Cval i = 0; i < (Cval)m_container_size; ++i)
		v2.push_back(i);

	// TEST
	{
		time_printer tm(msg, m_print_time);

		// STD
		// technical
		it = std::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( *it == 25 );

		v1.erase(it);
		it = std::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( *it == 55 );

		v1.erase(it);
		it = std::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		TEST_CHECK( it == v1.end() );

		// performance
		Struct_find_if<Cval> sfif1(m_container_size - 2);
		it = std::find_if(v2.begin(), v2.end(), sfif1);

		TEST_CHECK( *(++it) == (m_container_size - 1 ));
	}
}


bool myfunction_find_end(int i, int j) 
{
	return (i == j);
}

template<typename Container>
void test_algorithm::find_end(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3,4,5,1,2,3,4,5};
	
	Container v1(myints, myints + 10);
	Container v2(m_container_size, 0);
	
	for(size_t i=0; i < m_container_size; ++i)	v2[i] = Cval(i);	


	//TEST
	{
		time_printer tm(msg, m_print_time);


		//STL
		It it;
		Cval mycheck1[] = {1,2,3};

		/*	Looks in a range for the last subsequence that is identical 
			to a specified sequence or that is equivalent in a sense specified 
			by a binary predicate.

			using default comparison:
		*/
		it = stl::find_end(v1.begin(), v1.end(), mycheck1, mycheck1 + 3);		
		//Match found at position 5
		TEST_CHECK( (it-v1.begin()) == 5 );


		Cval mycheck2[] = {4,5,1};
		// using predicate comparison:
		it = stl::find_end(v1.begin(), v1.end(), mycheck2, mycheck2 + 3, myfunction_find_end);
		//Match last found at position 3
		TEST_CHECK( (it-v1.begin()) == 3 );



		Cval mycheck3[] = { m_container_size - 3, m_container_size - 2, m_container_size - 1 };
		//v2: 0,1,2,3,4,5
		//ck: 3,4,5
		it = stl::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);

		it = stl::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3, myfunction_find_end);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);
		
		// STD - see find_end2(...)
	}
}

template<typename Container>
void test_algorithm::find_end2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3,4,5,1,2,3,4,5};
	
	Container v1(myints, myints + 10);
	Container v2(m_container_size, 0);
	
	for(size_t i=0; i < m_container_size; ++i)	v2[i] = Cval(i);	


	//TEST
	{
		time_printer tm(msg, m_print_time);


		//STL
		It it;
		Cval mycheck1[] = {1,2,3};

		/*	Looks in a range for the last subsequence that is identical 
			to a specified sequence or that is equivalent in a sense specified 
			by a binary predicate.

			using default comparison:
		*/
		
		it = std::find_end(v1.begin(), v1.end(), mycheck1, mycheck1 + 3);		
		//Match found at position 5
		TEST_CHECK( (it-v1.begin()) == 5 );


		Cval mycheck2[] = {4,5,1};
		// using predicate comparison:
		it = std::find_end(v1.begin(), v1.end(), mycheck2, mycheck2 + 3, myfunction_find_end);
		//Match last found at position 3
		TEST_CHECK( (it-v1.begin()) == 3 );



		Cval mycheck3[] = { m_container_size - 3, m_container_size - 2, m_container_size - 1 };
		//v2: 0,1,2,3,4,5
		//ck: 3,4,5
		it = std::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);

		it = std::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3, myfunction_find_end);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);		
	}
}
//////////////////////////////////////////////////////////////////////////
bool comp_case_insensitive_find_first_of(char c1, char c2) 
{
	return (::tolower(c1) == ::tolower(c2));
}

template<typename Container>
void test_algorithm::find_first_of(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval mychars[] = {'a','b','c','A','B','C'};
	Container v1(mychars, mychars+6);

	It it;
	Cval mycheck[] = {'A','B','C'};

	Container v2(m_container_size - 3, 'a');
	for(size_t i = 0; i < 3; ++i)	v2.push_back(mycheck[i]);


	// TEST
	{
		time_printer tm(msg, m_print_time);

		//STL
		// using default comparison:
		it = stl::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3);
		TEST_CHECK(*it == 'A');

		// using predicate comparison:
		it = stl::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		TEST_CHECK(*it == 'a');

		it = stl::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3);
		TEST_CHECK(*it == 'A');

		it = stl::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		TEST_CHECK(*it == 'a');

#if !defined(DEBUG)
		//STD
		it = std::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3);
		TEST_CHECK(*it == 'A');

		it = std::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		TEST_CHECK(*it == 'a');

		it = std::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3);
		TEST_CHECK(*it == 'A');

		it = std::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		TEST_CHECK(*it == 'a');
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_adjacent_find(int i, int j) 
{
	return (i == j);
}

template<typename Container>
void test_algorithm::adjacent_find(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {10,20,30,30,20,10,10,20};
	Container v1(myints, myints+8);
	Container v2(m_container_size, 0);
	for(size_t i = 0; i < m_container_size; ++i)	v2[i] = Cval(i);

	
	// TEST
	{
		time_printer tp(msg, m_print_time);
		
		It it;

		// STL
		//Searches for two adjacent elements that are either equal or satisfy a specified condition.
		// using default comparison:
		it = stl::adjacent_find (v1.begin(), v1.end());
		TEST_CHECK(*it == 30);
		
		//"the first consecutive repeated elements are: 30"
		//using predicate comparison:
		it = stl::adjacent_find (++it, v1.end(), myfunction_adjacent_find);
		TEST_CHECK( *it == 10 );		
		//"the second consecutive repeated elements are: 10"

#if !defined(DEBUG)  //std::_Debug_range2
		// STD
		it = std::adjacent_find (v1.begin(), v1.end());
		TEST_CHECK(*it == 30);

		it = std::adjacent_find (++it, v1.end(), myfunction_adjacent_find);
		TEST_CHECK( *it == 10 );
#endif
	}
}

template<typename Container>
void test_algorithm::count(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::difference_type Diff;

	Cval myints[] = {10,20,30,30,20,10,10,20};   // 8 elements
	
	Container v1(myints, myints + 8);
	Container v2;
	for(size_t i=0; i < m_container_size; ++i)
		v2.push_back( (Cval) i);

	//TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		Diff mycount = 0;
		// counting elements in array:		
		mycount = stl::count (myints, myints+8, 10);

		//cout << "10 appears " << mycount << " times.\n";
		TEST_CHECK(mycount == 3);

		// counting elements in container:
		mycount = stl::count (v1.begin(), v1.end(), 20);
		//cout << "20 appears " << mycount  << " times.\n";
		TEST_CHECK(mycount == 3);

		mycount = stl::count (v2.begin(), v2.end(), Cval(m_container_size -1));
		TEST_CHECK(mycount == 1);

#if !defined(DEBUG)
		// STD
		mycount = std::count (myints, myints+8, 10);
		TEST_CHECK(mycount == 3);

		mycount = std::count (v1.begin(), v1.end(), 20);
		//cout << "20 appears " << mycount  << " times.\n";
		TEST_CHECK(mycount == 3);

		mycount = std::count (v2.begin(), v2.end(), CVal(m_container_size -1));
		TEST_CHECK(mycount == 1);
#endif
	}	

}

//////////////////////////////////////////////////////////////////////////
bool IsOdd_count_if(int i) 
{ 
	return ((i%2)==1); 
}

template<typename Container>
void test_algorithm::count_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::difference_type Diff;


	Diff mycount;
	Container v1, v2;
	for (size_t i=1; i < 10; i++) v1.push_back ((Cval) i); // v1: 1 2 3 4 5 6 7 8 9
	for (size_t i=0; i < m_container_size; ++i) v2.push_back ((Cval)i);


	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		mycount = stl::count_if (v1.begin(), v1.end(), IsOdd_count_if);
		//cout << "v1 contains " << mycount  << " odd values.\n";
		TEST_CHECK(mycount == 5);

		mycount = stl::count_if (v2.begin(), v2.end(), IsOdd_count_if);
		TEST_CHECK(mycount == m_container_size/2);

#if !defined(DEBUG)
		// STD
		mycount = std::count_if (v1.begin(), v1.end(), IsOdd_count_if);
		//cout << "v1 contains " << mycount  << " odd values.\n";
		TEST_CHECK(mycount == 5);

		mycount = std::count_if (v2.begin(), v2.end(), IsOdd_count_if);
		TEST_CHECK(mycount == m_container_size/2);
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool mypredicate_mismatch (int i, int j)
{
	return (i==j);
}


template<typename Container>
void test_algorithm::mismatch(const char* msg)
{
	typedef typename Container::value_type Cval;

	Container v1(5, Cval(0));
	Container v2(m_container_size-1, Cval(0));
	Container v3(m_container_size / 5 - 1, Cval(0));

	for (size_t i=1; i < 6; i++) v1[i-1] = (Cval)i*10; // v1: 10 20 30 40 50
	for (size_t i=1; i < m_container_size; ++i) v2[i-1] = (Cval)i*10;
	for (size_t i=1; i < m_container_size / 5; ++i) v3[i-1] = (Cval)i*10;



	Cval myints[] = {10,20,80,320,1024};                //   myints: 10 20 80 320 1024

	stl::pair<typename Container::iterator, Cval*>		pair1;
	stl::pair<typename Container::iterator, typename Container::iterator> pair2;
	std::pair<typename Container::iterator, Cval*>		pair3;
	std::pair<typename Container::iterator, typename Container::iterator> pair4;





	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		// Compares two ranges element by element either for equality or
		// equivalent in a sense specified by a binary predicate and locates
		// the first position where a difference occurs.
		// Condition: first container.size() <= second container.size();

		// using default comparison:
		pair1 = stl::mismatch (v1.begin(), v1.end(), myints);
		//cout << "First mismatching elements: " << *pair1.first;
		TEST_CHECK(*pair1.first == 30);

		//cout << " and " << *pair1.second << endl;;
		TEST_CHECK(*pair1.second == 80);

		pair1.first++;
		pair1.second++;

		// using predicate comparison:
		pair1 = stl::mismatch (pair1.first, v1.end(), pair1.second, mypredicate_mismatch);
		//cout << "Second mismatching elements: " << *pair1.first;
		TEST_CHECK(*pair1.first == 40);
		//cout << " and " << *pair1.second << endl;;
		TEST_CHECK(*pair1.second == 320);


		pair1 = stl::mismatch (v2.begin(), v2.end(), myints);
		TEST_CHECK(*pair1.first == 30);
		TEST_CHECK(*pair1.second == 80);

		// condition: first container.size() < second container.size()
		pair2 = stl::mismatch (v3.begin(), v3.end(), v2.begin());
		TEST_CHECK(pair2.first == v3.end());
		TEST_CHECK(*pair2.second == (m_container_size/5) * 10);

#if !defined(DEBUG)
		// STD
		// the only test that compiles with _WIN32
		pair4 = std::mismatch (v3.begin(), v3.end(), v2.begin());
		TEST_CHECK(pair4.first == v3.end());
		TEST_CHECK(*pair4.second == (m_container_size/5) * 10);
#endif
	}
}


//////////////////////////////////////////////////////////////////////////
bool mypredicate_equal (int i, int j)
{
	return (i==j);
}

template<typename Container>
void test_algorithm::equal(const char* msg)
{
	typedef typename Container::value_type Cval;

	Cval myints[] = {20,40,60,80,100};          //   myints: 20 40 60 80 100
	Container  v1(myints,myints+5);             //       v1: 20 40 60 80 100
	Container v2;
	for(size_t i = 0; i < m_container_size; ++i)
		v2.push_back ((Cval)i);
	Container v3(v2.begin(), v2.end());


	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		// using default comparison:
		bool res = stl::equal(v1.begin(), v1.end(), myints);
		TEST_CHECK(res);

		v1[3]=81;                            // v1: 20 40 60 81 100
		// using predicate comparison:
		res = stl::equal(v1.begin(), v1.end(), myints, mypredicate_equal);
		TEST_CHECK( !res );

		res = stl::equal(v2.begin(), v2.end(), v3.begin());
		TEST_CHECK( res );

		res = stl::equal(v2.begin(), v2.end(), v3.begin(), mypredicate_equal);
		TEST_CHECK(res);

		// STD
		// update equal2(..)
	}
}


template<typename Container>
void test_algorithm::equal2(const char* msg)
{
	typedef typename Container::value_type Cval;

	Cval myints[] = {20,40,60,80,100};          //   myints: 20 40 60 80 100
	Container  v1(myints,myints+5);             //       v1: 20 40 60 80 100
	Container v2;
	for(size_t i = 0; i < m_container_size; ++i)
		v2.push_back ((Cval)i);
	Container v3(v2.begin(), v2.end());


	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		// using default comparison:
		bool res = std::equal(v1.begin(), v1.end(), myints);
		TEST_CHECK(res);

		v1[3]=81;                            // v1: 20 40 60 81 100
		// using predicate comparison:
		res = std::equal(v1.begin(), v1.end(), myints, mypredicate_equal);
		TEST_CHECK( !res );

		res = std::equal(v2.begin(), v2.end(), v3.begin());
		TEST_CHECK( res );

		res = std::equal(v2.begin(), v2.end(), v3.begin(), mypredicate_equal);
		TEST_CHECK(res);
	}	
}


//////////////////////////////////////////////////////////////////////////
bool mypredicate_search (int i, int j)
{
	return (i==j);
}

template<typename Container>
void test_algorithm::search(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1, v2, v3;
	It it;

	// set some values:        v1: 10 20 30 40 50 60 70 80 90
	for (size_t i=1; i < 10; i++) v1.push_back ((Cval)i*10);
	Cval match1[] = {40,50,60,70};
	Cval match2[] = {20,30,50};

	for(size_t i=0; i < m_container_size; ++i)	v2.push_back ((Cval)i);
	for(size_t i=m_container_size/2; i < m_container_size; ++i)	v3.push_back ((Cval)i);
	Cval match4[] = {m_container_size-3, m_container_size-2, m_container_size-1};


	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STD
		// using default comparison:
		it = std::search (v1.begin(), v1.end(), match1, match1+4);	
		TEST_CHECK( (int)(it - v1.begin()) == 3 );
		// using predicate comparison:
		it = std::search (v1.begin(), v1.end(), match2, match2+3, mypredicate_search);
		TEST_CHECK( it == v1.end() );

		it = std::search (v2.begin(), v2.end(), v3.begin(), v3.end());	
		TEST_CHECK( (it - v2.begin()) == m_container_size / 2);

		it = std::search (v2.begin(), v2.end(), match4, match4+3, mypredicate_search);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);
	}
}

template<typename Container>
void test_algorithm::search2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1, v2, v3;
	It it;

	// set some values:        v1: 10 20 30 40 50 60 70 80 90
	for (size_t i=1; i < 10; i++) v1.push_back ((Cval)i*10);
	Cval match1[] = {40,50,60,70};
	Cval match2[] = {20,30,50};

	for(size_t i=0; i < m_container_size; ++i)	v2.push_back ((Cval)i);
	for(size_t i=m_container_size/2; i < m_container_size; ++i)	v3.push_back ((Cval)i);
	Cval match4[] = {m_container_size-3, m_container_size-2, m_container_size-1};


	// TEST
	{
		time_printer tp(msg, m_print_time);

		// STL
		// using default comparison:
		it = stl::search (v1.begin(), v1.end(), match1, match1+4);	
		TEST_CHECK( (int)(it - v1.begin()) == 3 );
		// using predicate comparison:
		it = stl::search (v1.begin(), v1.end(), match2, match2+3, mypredicate_search);
		TEST_CHECK( it == v1.end() );

		it = stl::search (v2.begin(), v2.end(), v3.begin(), v3.end());	
		TEST_CHECK( (it - v2.begin()) == m_container_size / 2);

		it = stl::search (v2.begin(), v2.end(), match4, match4+3, mypredicate_search);
		TEST_CHECK( (it - v2.begin()) == m_container_size - 3);
	}
}
//////////////////////////////////////////////////////////////////////////
bool mypredicate_search_n (int i, int j){ return (i==j); }

template<typename Container>
void test_algorithm::search_n(const char* msg)
{
	typedef typename Container::iterator It;
	typedef typename Container::value_type Cval;

	Cval myints[]={10,20,30,30,20,10,10,20};

	Container v1(myints,myints+8);
	Container v2;
	for(size_t i=0; i < m_container_size-1; ++i)	v2.push_back ((Cval)i);
	v2.push_back (v2.back());
		
	It it;


	// TEST
	{
		time_printer tp(msg, m_print_time);


		// STD
		/*	search_n(begin, end, how_many_consecutive, having_value)
			Searches for the first subsequence in a range that of a 
			specified number of elements having a particular value or 
			a relation to that value as specified by a binary predicate.
		*/
		// using default comparison:
		it = std::search_n (v1.begin(), v1.end(), 2, 30);
		//cout << "two 30s found at position 2" << int(it-v1.begin()) << endl;
		TEST_CHECK((int)(it-v1.begin()) == 2);

		// using predicate comparison:
		it = std::search_n (v1.begin(), v1.end(), 2, 10, mypredicate_search_n);
		//cout << "two 10s found at position 5" << int(it-v1.begin()) << endl;
		TEST_CHECK((int)(it-v1.begin()) == 5);
		//Two 30s found at position 2
		//Two 10s found at position 5

		it = std::search_n (v2.begin(), v2.end(), 2, m_container_size - 2);		
		TEST_CHECK((int)(it-v2.begin()) == m_container_size - 2);

		it = std::search_n (v2.begin(), v2.end(), 2, m_container_size - 2, mypredicate_search_n);
		TEST_CHECK((int)(it-v2.begin()) == m_container_size - 2);
	}
}


template<typename Container>
void test_algorithm::search_n2(const char* msg)
{
	typedef typename Container::iterator It;
	typedef typename Container::value_type Cval;

	Cval myints[]={10,20,30,30,20,10,10,20};

	Container v1(myints,myints+8);
	Container v2;
	for(size_t i=0; i < m_container_size-1; ++i)	v2.push_back ((Cval)i);
	v2.push_back (v2.back());
		
	It it;


	// TEST
	{
		time_printer tp(msg, m_print_time);


		// STL
		/*	search_n(begin, end, how_many_consecutive, having_value)
			Searches for the first subsequence in a range that of a 
			specified number of elements having a particular value or 
			a relation to that value as specified by a binary predicate.
		*/
		// using default comparison:
		it = stl::search_n (v1.begin(), v1.end(), 2, 30);
		//cout << "two 30s found at position 2" << int(it-v1.begin()) << endl;
		TEST_CHECK((int)(it-v1.begin()) == 2);

		// using predicate comparison:
		it = stl::search_n (v1.begin(), v1.end(), 2, 10, mypredicate_search_n);
		//cout << "two 10s found at position 5" << int(it-v1.begin()) << endl;
		TEST_CHECK((int)(it-v1.begin()) == 5);
		//Two 30s found at position 2
		//Two 10s found at position 5

		it = stl::search_n (v2.begin(), v2.end(), 2, Cval(m_container_size - 2));
		TEST_CHECK((int)(it-v2.begin()) == m_container_size - 2);

		it = stl::search_n (v2.begin(), v2.end(), 2, m_container_size - 2, mypredicate_search_n);
		TEST_CHECK((int)(it-v2.begin()) == m_container_size - 2);
	}
}

//Modifying sequence operations:
template<typename Container>
void test_algorithm::copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[]={10,20,30,40,50,60,70};
	Container v1, v2, v3, v4, v5;
	It it;

	for(size_t i=0; i < m_container_size; ++i)	v2.push_back ((Cval)i);
	v3.resize (v2.size());
	v5.resize (v2.size());


	//	TEST
	{
		time_printer tp(msg, m_print_time);


		//	STL
		// allocate space for 7 elements
		v1.resize(7);
		/*	Assigns the values of elements from a source range to a 
			destination range, iterating through the source sequence of 
			elements and assigning them new positions in a forward direction.
		*/
		stl::copy ( myints, myints+7, v1.begin() );

		//cout << "v1 contains:";
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(myints[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//myvector contains: 10 20 30 40 50 60 70

		stl::copy (v2.begin(), v2.end(), v3.begin());
		TEST_CHECK(v3.size() == v2.size());
		for(size_t i = 0; i < v3.size(); ++i)
		{
			TEST_CHECK(v3[i] == (int)i);
		}


#if !defined(DEBUG)		// std::_Debug_range
		//	STD
		v4.resize(7);
		/*	Assigns the values of elements from a source range to a 
			destination range, iterating through the source sequence of 
			elements and assigning them new positions in a forward direction.
		*/
		std::copy ( myints, myints+7, v4.begin() );

		//cout << "v1 contains:";
		for (it=v4.begin(); it!=v4.end(); ++it)
		{
			TEST_CHECK(myints[it-v4.begin()] == *it);
			//cout << " " << *it;
		}
		//myvector contains: 10 20 30 40 50 60 70

		std::copy (v2.begin(), v2.end(), v5.begin());
		TEST_CHECK(v5.size() == v2.size());
		for(size_t i = 0; i < v5.size(); ++i)
		{
			TEST_CHECK((int)v5[i] == i);
		}
#endif
	}	
}

template<typename Container>
void test_algorithm::copy_backward(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1(5, Cval(0));
	Container v2(m_container_size, Cval(0));
	for(size_t i=0; i < m_container_size; ++i)		v2[i] = Cval(i);
	
	It it;

	// set some values:
	for (size_t i = 1; i <= 5; i++)	v1[i-1] = Cval(i*10); // v1: 10 20 30 40 50
	v1.resize (v1.size() + 3);	// allocate space for 3 more elements
	Cval myints[]={10, 20, 30, 10, 20, 30, 40, 50};


	//	TEST
	{
		time_printer tp(msg, m_print_time);


		//	STL
		/*	Assigns the values of elements from a source range to a 
			destination range, iterating through the source sequence of 
			elements and assigning them new positions in a backward direction.
		*/
		stl::copy_backward (v1.begin(), v1.begin()+5, v1.end());
				
		//cout << "v1 contains:";
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(myints[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//v1 contains: 10 20 30 10 20 30 40 50

		Container vv2(v2);
		vv2.resize(vv2.size()+m_container_size/2);		
		stl::copy_backward(vv2.begin(), vv2.begin() + m_container_size/2, vv2.end());
		it = vv2.begin();
		for(size_t i=0; i < m_container_size; ++i, ++it)
		{
			TEST_CHECK(*it == Cval(i));
		}
		for(size_t i=0; i < m_container_size/2; ++i, ++it)
		{
			TEST_CHECK(*it == Cval(i));
		}

#if !defined(DEBUG)		//std::_Debug_range2 debug iterator _WIN32
		//	STD		
		Container vv3(v2);
		vv3.resize(vv3.size()+m_container_size/2);		
		std::copy_backward(vv3.begin(), vv3.begin() + m_container_size/2, vv3.end());
		it = vv3.begin();
		for(size_t i=0; i < m_container_size; ++i, ++it)
		{
			TEST_CHECK(*it == Cval(i));
		}
		for(size_t i=0; i < m_container_size/2; ++i, ++it)
		{
			TEST_CHECK(*it == Cval(i));
		}
#endif
	}
}

template<typename Container>
void test_algorithm::swap(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval x=10, y=20;
	Container v1 ((size_t)4, x);
	Container v2 ((size_t)6, y);
	Container v3 (m_container_size, Cval(0));
	Container v4 (m_container_size/2, Cval(1));



	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL		
		stl::swap<Cval>(x,y);
		TEST_CHECK(x == Cval(20));
		TEST_CHECK(y == Cval(10));
		
		stl::swap(v1,v2);		
		for (It it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(*it == Cval(20));
		}

		for (It it=v2.begin(); it!=v2.end(); ++it)
		{
			TEST_CHECK(*it == Cval(10));
		}

		stl::swap (v3, v4);
		for(It it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK(*it == Cval(1));
		}
		for(It it = v4.begin(); it != v4.end(); ++it)
		{
			TEST_CHECK(*it == Cval(0));
		}

		//	STD
		std::swap(x,y);
		TEST_CHECK(x == Cval(10));
		TEST_CHECK(y == Cval(20));
		
		std::swap(v1,v2);		
		for (It it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(*it == Cval(10));
		}
		for (It it=v2.begin(); it!=v2.end(); ++it)
		{
			TEST_CHECK(*it == Cval(20));
		}

		std::swap (v3, v4);
		for(It it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK(*it == Cval(0));
		}
		for(It it = v4.begin(); it != v4.end(); ++it)
		{
			TEST_CHECK(*it == Cval(1));
		}
	}

}

template<typename Container>
void test_algorithm::swap_ranges(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1((size_t)5, (Cval)10);		//  v1: 10 10 10 10 10
	Container v2((size_t)5, (Cval)33);		//  v2: 33 33 33 33 33
	
	It it;
	int myints1[]={10, 33, 33, 33, 10};
	int myints2[]={10, 10, 10, 33, 33};

	Container v3(m_container_size, 0);
	Container v4(m_container_size, 1);
		

	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		stl::swap_ranges(v1.begin()+1, v1.end()-1, v2.begin());

		// print out results of swap:
		// v1 contains: 10 33 33 33 10		
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(myints1[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
				
		// v2 contains: 10 10 10 33 33
		for (it=v2.begin(); it!=v2.end(); ++it)
		{
			TEST_CHECK(myints2[it-v2.begin()] == *it);
			//cout << " " << *it;
		}

		stl::swap_ranges(v3.begin()+1, v3.end()-1, v4.begin());
		for(it = v3.begin(); it != v3.end(); ++it)
		{
			if(it == v3.begin()) TEST_CHECK(*it == 0);
			else if(it == v3.end()-1) TEST_CHECK(*it == 0);
			else TEST_CHECK(*it == 1);
		}


#if !defined(DEBUG)
		//	STD
		std::swap_ranges(v2.begin(), v2.begin()+3, v1.begin()+1);
		for(it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(*it == 10);
		}
		for(it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it == 33);
		}

		std::swap_ranges(v3.begin()+1, v3.end()-1, v4.begin());
		for(it = v4.begin(); it != v4.end(); ++it)
		{
			TEST_CHECK(*it == 1);
		}
#endif
	}
	
}

template<typename Container>
void test_algorithm::iter_swap(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1 ((size_t)4, Cval(99));     //       v1:  99  99  99  99
	Cval myints[]= {10, 20, 30, 40, 50 };   //   myints:  10  20  30  40  50
	Cval mycheck[]={10, 99, 40, 99};

	Container v2 (m_container_size, Cval(0));
	Container v3 (m_container_size, Cval(1));

	It it;

	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		stl::iter_swap(myints, v1.begin());      
		// myints: [99] 20  30  40  50
		//     v1: [10] 99  99  99
		stl::iter_swap(myints + 3, v1.begin() + 2);  
		// myints:  99  20  30 [99]
		//     v1:  10  99 [40] 99		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		It it2 = v2.begin();
		It it3 = v3.begin();
		for (; it2 != v2.end(); ++it2, ++it3)
		{
			It it_2 = it2;
			It it_3 = it3;
			stl::iter_swap (it_2, it_3);
		}
		
		for (It it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it == Cval(1));
		}
		


		//	STD
		it2 = v2.begin();
		it3 = v3.begin();
		for (; it2 != v2.end(); ++it2, ++it3)
		{
			It it_2 = it2;
			It it_3 = it3;
			std::iter_swap (it_2, it_3);
		}

		for (It it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it == Cval(0));
		}
	}	
}


//////////////////////////////////////////////////////////////////////////
int op_increase_transform (int i) { return ++i; }
int op_sum_transform (int i, int j) { return i+j; }
int op_decrease_transform (int i) { return --i; }
int op_sub_transform (int i, int j) { return i-j; }

template<typename Container>
void test_algorithm::transform(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1 (5, Cval(0));
	//  v1: 10 20 30 40 50
	for (size_t i=1; i<6; i++)	v1[i-1] = Cval(i*10);

	Container v2;
	v2.resize(v1.size());	// allocate space
	
	It it;

	Container v3 (m_container_size, Cval(-1));
	Container v4 (m_container_size, Cval(1));

	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL	
		/*	Applies a specified function object to each element in 
			a source range or to a pair of elements from two source ranges 
			and copies the return values of the function object into 
			a destination range.
		*/
		stl::transform (v1.begin(), v1.end(), v2.begin(), op_increase_transform);
		// v2: 11 21 31 41 51

		stl::transform (v1.begin(), v1.end(), v2.begin(), v1.begin(), op_sum_transform);
		//  v1: 21 41 61 81 101		
		int mycheck[]={21, 41, 61, 81, 101};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}		

		stl::transform (v3.begin(), v3.end(), v3.begin(), op_decrease_transform);//v3:-2
		stl::transform (v3.begin(), v3.end(), v4.begin(), v3.begin(), op_sub_transform);//v3:-3
		for (It it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK(*it == Cval(-3));
		}


#if !defined(DEBUG)
		//	STD
		std::transform (v1.begin(), v1.end(), v2.begin(), v1.begin(), op_sub_transform);
		std::transform (v1.begin(), v1.end(), v2.begin(), op_decrease_transform);

		size_t stdck = 10;
		for (It it = v1.begin(); it != v1.end(); ++it, stdck += 10)
		{
			TEST_CHECK(*it == stdck);			
		}

		std::transform (v3.begin(), v3.end(), v3.begin(), op_increase_transform);//v3:-2
		std::transform (v3.begin(), v3.end(), v4.begin(), v3.begin(), op_sum_transform);//v3:-1
		for (It it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK(*it == Cval(-1));
		}
#endif
	}
}

template<typename Container>
void test_algorithm::replace(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	Cval myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	Cval mycheck[]= { 10, 99, 30, 30, 99, 10, 10, 99 };
	Container v1 (myints, myints+8); // 10 20 30 30 20 10 10 20
	
	Container v2(m_container_size, 0);
	size_t i0 = 0;
	for(it = v2.begin(); it != v2.end(); ++it, ++i0)
		if(i0%2) *it = Cval(1);

	
	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		stl::replace (v1.begin(), v1.end(), 20, 99);
		// v1: 10 99 30 30 99 10 10 99				
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		stl::replace (v2.begin(), v2.end(), 1, 2);
		size_t i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
		{
			if(i2%2)
				TEST_CHECK(*it == Cval(2));
			else
				TEST_CHECK(*it == Cval(0));
		}

#if !defined(DEBUG)
		//	STD
		std::replace (v1.begin(), v1.end(), 99, 20);
		// v1: 10 20 30 30 20 10 10 20
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(myints[it-v1.begin()] == *it);			
		}

		stl::replace (v2.begin(), v2.end(), 2, 3);
		size_t i3 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i3)
		{
			if(i3%2)
				TEST_CHECK(*it == Cval(3));
			else
				TEST_CHECK(*it == Cval(0));
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool IsOdd_replace_if(int i) { return ((i%2) != 0); }
bool IsNull_replace_if(int i){ return i == 0; }

template<typename Container>
void test_algorithm::replace_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	Container v1;	
	for (size_t i = 1; i < 10; i++)	v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9

	Container v2(m_container_size, Cval(0));
	size_t i0 = 0;
	for (it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);
		
	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL		
		/*	Examines each element in a range and replaces it 
			if it satisfies a specified predicate.
		*/
		stl::replace_if (v1.begin(), v1.end(), IsOdd_replace_if, 0); 
		// v1: 0 2 0 4 0 6 0 8 0

		Cval mycheck[]={0, 2, 0, 4, 0, 6, 0, 8, 0};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		stl::replace_if (v2.begin(), v2.end(), IsOdd_replace_if, -5);
		size_t i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
			if( IsOdd_replace_if((int) i2))
				TEST_CHECK(*it == Cval(-5));
			else
				TEST_CHECK(*it == Cval(i2));		
		
#if !defined(DEBUG)
		//	STD
		std::replace_if (v1.begin(), v1.end(), IsNull_replace_if, -1); 
		// v1: -1 2 -1 4 -1 6 -1 8 -1

		Cval mycheck2[]={-1, 2, -1, 4, -1, 6, -1, 8, -1};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck2[it-v1.begin()] == *it);			
		}

		stl::replace_if (v2.begin(), v2.end(), IsOdd_replace_if, -1);
		i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
			if( IsOdd_replace_if((int) i2))
				TEST_CHECK(*it == Cval(-1));
			else
				TEST_CHECK(*it == Cval(i2));
#endif
	}	
}

template<typename Container>
void test_algorithm::replace_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
	int mycheck[]= { 10, 99, 30, 30, 99, 10, 10, 99 };
	
	Container v1(8);
	It it;

	Container v2(m_container_size); // v2: 0, 1, 0, 3, ...
	Container v3(m_container_size); // v3: 0, 0, 0, 0, ...
	size_t i0 = 0;
	for (it = v2.begin(); it != v2.end(); ++it, ++i0)
	{
		if(i0%2)	*it = Cval(i0);
		else		*it = Cval(0);
	}

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Examines each element in a source range and replaces it 
			if it matches a specified value while copying the result 
			into a new destination range.
		*/
		stl::replace_copy (myints, myints+8, v1.begin(), 20, 99);		
		//v1: 10 99 30 30 99 10 10 99		
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		//v2: 0, 1, 0, 3, 0, 5
		//v3:-1, 1,-1, 3,-1, 5
		stl::replace_copy (v2.begin(), v2.end(), v3.begin(), 0, -1);
		i0 = 0;
		for (it = v3.begin(); it != v3.end(); ++it, ++i0)
		{
			if(i0%2)	TEST_CHECK(*it == Cval(i0));
			else		TEST_CHECK(*it == Cval(-1));
		}		

#if !defined(DEBUG)
		//	STD
		std::replace_copy (myints, myints+8, v1.begin(), 99, 20);		
		//v1: 10 20 30 30 20 10 10 20
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(myints[it-v1.begin()] == *it);			
		}

		//v3:-1, 1,-1, 3,-1, 5
		//v2:-3, 1,-3, 3,-3, 5
		std::replace_copy (v3.begin(), v3.end(), v2.begin(), -1, -3);
		i0 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i0)
		{
			if(i0%2)	TEST_CHECK(*it == Cval(i0));
			else		TEST_CHECK(*it == Cval(-3));
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool IsOdd_replace_copy_if (int i) { return ((i%2) != 0); }
bool IsNull_replace_copy_if (int i) { return (i == 0); }

template<typename Container>
void test_algorithm::replace_copy_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Cval mycheck[]= { 0, 2, 0, 4, 0, 6, 0, 8, 0};

	Container v1(myints, myints + 9);	
	Container v2;
	v2.resize(v1.size());

	It it;
	size_t i0;

	Container v3(m_container_size);
	for (it = v3.begin(), i0 = 0; it != v3.end(); ++it, ++i0)	*it = Cval(i0);
	Container v4(m_container_size);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Examines each element in a source range and replaces it 
			if it satisfies a specified predicate while copying the result 
			into a new destination range.
		*/
		stl::replace_copy_if (v1.begin(), v1.end(), v2.begin(), IsOdd_replace_copy_if, Cval(0));
		//v2: 0 2 0 4 0 6 0 8 0		
		
		for (it=v2.begin(); it!=v2.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v2.begin()] == *it);			
		}

		stl::replace_copy_if (v3.begin(), v3.end(), v4.begin(), IsOdd_replace_copy_if, Cval(-5));
		for (it = v4.begin(), i0=0; it != v4.end(); ++it, ++i0)
		{
			if(i0%2 != 0)	TEST_CHECK(*it == Cval(-5));
			else			TEST_CHECK(*it == Cval(i0));
		}
		
#if !defined(DEBUG)
		//	STD
		std::replace_copy_if (v2.begin(), v2.end(), v1.begin(), IsNull_replace_copy_if, Cval(-1));
		//v1: -1 2 -1 4 -1 6 -1 8 -1				
		for (it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			if(i0%2 == 0)	TEST_CHECK(*it == Cval(i0));
			else			TEST_CHECK(*it == Cval(-1));
		}

		std::replace_copy_if (v4.begin(), v4.end(), v3.begin(), IsOdd_replace_copy_if, Cval(-1));
		for (it = v3.begin(), i0=0; it != v3.end(); ++it, ++i0)
		{
			if(i0%2 != 0)	TEST_CHECK(*it == Cval(-1));
			else			TEST_CHECK(*it == Cval(i0));
		}
#endif
	}
}


template<typename Container>
void test_algorithm::fill(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1 (8); // v1: 0 0 0 0 0 0 0 0
	It it;
//	size_t i0;

	Container v2(m_container_size);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Assigns the same new value to every element in a specified range.
		*/
		stl::fill (v1.begin(), v1.begin() + 4, Cval(5));   // v1: 5 5 5 5 0 0 0 0
		stl::fill (v1.begin() + 3, v1.end() - 2, Cval(8)); // v1: 5 5 5 8 8 8 0 0

		//cout << "v1 contains:";
		Cval mycheck[]={5, 5, 5, 8, 8, 8, 0, 0};
		for ( it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}
		
		stl::fill (v2.begin(), v2.end(), Cval(-1));
		for (it = v2.begin(); it != v2.end(); ++it)
			TEST_CHECK (*it == Cval(-1));


#if !defined(DEBUG)
		//	STD
		std::fill (v1.begin(), v1.begin() + 4, Cval(-5));    // v1: -5 -5 -5 -5  0  0 0 0
		std::fill (v1.begin() + 3, v1.end() - 2, Cval(-8));  // v1: -5 -5 -5 -8 -8 -8 0 0
				
		for ( it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(-1 * mycheck[it-v1.begin()] == *it);			
		}

		std::fill (v2.begin(), v2.end(), Cval(-2));
		for (it = v2.begin(); it != v2.end(); ++it)
			TEST_CHECK (*it == Cval(-2));
#endif
	}
}

template<typename Container>
void test_algorithm::fill_n(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	It it;
	size_t i0;

	Container v1 ((size_t)8, Cval(10));		// v1: 10 10 10 10 10 10 10 10
	Container v2 (m_container_size);		// v2: 0  1  2  3  4  5  6  7  ...
	for (it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)	*it = Cval(i0);
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Assigns a new value to a specified number of elements 
			in a range beginning with a particular element.
		*/
		stl::fill_n (v1.begin(), 4, Cval(20));   // v1: 20 20 20 20 10 10 10 10
		stl::fill_n (v1.begin()+3, 3, Cval(33)); // v1: 20 20 20 33 33 33 10 10

		Cval mycheck[]={20, 20, 20, 33, 33, 33, 10, 10};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
		}

		stl::fill_n (v2.begin(), m_container_size, Cval(-1));
		for (it = v2.begin(); it != v2.end(); ++it)
			TEST_CHECK(*it == Cval(-1));

#if !defined(DEBUG)
		//	STD
		std::fill_n (v1.begin(), 4, Cval(2));   // v1: 2 2 2 2 10 10 10 10
		std::fill_n (v1.begin()+3, 3, Cval(3)); // v1: 2 2 2 3  3  3 10 10

		Cval mycheck2[]={2, 2, 2, 3, 3, 3, 10, 10};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck2[it-v1.begin()] == *it);
		}

		std::fill_n (v2.begin(), m_container_size, Cval(-6));
		for (it = v2.begin(); it != v2.end(); ++it)
			TEST_CHECK(*it == Cval(-6));
#endif
	}
}


//////////////////////////////////////////////////////////////////////////

// function generator:
int RandomNumber_generate () { return (::rand()%100 + 1); }

// class generator:
struct c_unique_generate {    
	c_unique_generate() {}
	int operator()() {return (::rand()%100 + 1); }
} UniqueNumber_generate;



template<typename Container>
void test_algorithm::generate(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1 ((size_t)8, Cval(-INT_MAX));	
	Container v2 (m_container_size);

	It it;
//	size_t i0;	

	::srand ( unsigned ( ::time(NULL) ) );

	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		stl::generate (v1.begin(), v1.end(), RandomNumber_generate);		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);	// weak check, cannot predict the value			
		}

		stl::generate (v1.begin(), v1.end(), UniqueNumber_generate);		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);			
		}

		stl::generate (v2.begin(), v2.end(), RandomNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);
		}

		stl::generate (v2.begin(), v2.end(), UniqueNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);
		}
		
#if !defined(DEBUG)
		//	STD
		std::generate (v2.begin(), v2.end(), RandomNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);
		}

		std::generate (v2.begin(), v2.end(), UniqueNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(*it > 0 && *it <= 100);
		}
#endif
	}
}


//////////////////////////////////////////////////////////////////////////

int current_generate_n(0);
int UniqueNumber_generate_n() { return ++current_generate_n; }

template<typename Container>
void test_algorithm::generate_n(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	int myarray[9];
	Container v1(m_container_size);

	It it;
	size_t i0;


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		// reset the number generator
		current_generate_n = 0;
		stl::generate_n (myarray, 9, UniqueNumber_generate_n);
		
		for (i0 = 0; i0 < 9; ++i0)
		{
			TEST_CHECK(myarray[i0] == Cval(i0+1));
		}

		current_generate_n = 0;	// reset the number generator
		stl::generate_n (v1.begin(), m_container_size, UniqueNumber_generate_n);

		for (i0 = 0, it = v1.begin(); it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0+1));
		}
		

#if !defined(DEBUG)
		//	STD
		current_generate_n = 0;
		std::generate_n (myarray, 9, UniqueNumber_generate_n);

		for (i0 = 0; i0 < 9; ++i0)
		{
			TEST_CHECK(myarray[i0] == Cval(i0+1));
		}

		current_generate_n = 0;	// reset the number generator
		std::generate_n (v1.begin(), m_container_size, UniqueNumber_generate_n);

		for (i0 = 0, it = v1.begin(); it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0+1));
		}
#endif
	}
}

template<typename Container>
void test_algorithm::remove(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {10, 20, 30, 30, 20, 10, 10, 20}; // 10 20 30 30 20 10 10 20
	// bounds of range:
	Cval* pbegin = myints;                            // ^
	Cval* pend = myints+sizeof(myints)/sizeof(Cval);  // ^                       ^


	It it;
//	size_t i0;

	Container v1(m_container_size, Cval(-1));
	Container v2(m_container_size, Cval(-2));
	
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Eliminates a specified value from a given range without disturbing
			the order of the remaining elements and returning the end of a new
			range free of the specified value.
		*/
		pend = stl::remove (pbegin, pend, 20);       // 10 30 30 10 10 ?  ?  ?
		                                              // ^              ^		
		
		int mycheck[]={10, 30, 30, 10, 10};
		for (int* p=pbegin; p!=pend; ++p)
		{
			TEST_CHECK(mycheck[p-pbegin] == *p);			
		}

		It end1 = stl::remove (v1.begin(), v1.end(), Cval(-1));
		TEST_CHECK( v1.begin() == end1);		



		//	STD
/*		error C2668: 'std::find' : ambiguous call to overloaded function
		Cannot decide which function to call:
		_InIt std::find<_FwdIt,_Ty>(_InIt,_InIt,const _Ty &)  or:
		InputIterator stl::find<_FwdIt,_Ty>(InputIterator,InputIterator,const T &)	
		
		when using std::remove with iterators belonging to stl::generic_array;
*/

//		It end2 = std::remove (v2.begin(), v2.end(), Cval(-2));
//		TEST_CHECK( v2.begin() == end2);
	}
}


//////////////////////////////////////////////////////////////////////////
bool IsOdd_remove_if (int i) { return ((i%2)==1); }

template<typename Container>
void test_algorithm::remove_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {1,2,3,4,5,6,7,8,9};               // 1 2 3 4 5 6 7 8 9
	// bounds of range:
	Cval* pbegin = myints;                             // ^
	Cval* pend = myints+sizeof(myints)/sizeof(Cval);   // ^                 ^


	Container v1 (m_container_size, Cval(1)); // odd
	Container v2 (m_container_size, Cval(1)); // odd too for std:: algorithm

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		/*	Eliminates elements that satisfy a predicate from a given range 
			without disturbing the order of the remaining elements and 
			returning the end of a new range free of the specified value.
		*/
		pend = stl::remove_if (pbegin, pend, IsOdd_remove_if);  // 2 4 6 8 ? ? ? ? ?
																 // ^       ^

		// the range contains:
		Cval mycheck[]={2, 4, 6, 8};
		for (Cval* p = pbegin; p != pend; ++p)
		{
			TEST_CHECK(mycheck[p-pbegin] = *p);			
		}

		It end1 = stl::remove_if (v1.begin(), v1.end(), IsOdd_remove_if);
		TEST_CHECK(v1.begin() == end1);

		// STD - see remove_if2(...)
	}
}


template<typename Container>
void test_algorithm::remove_if2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {1,2,3,4,5,6,7,8,9};               // 1 2 3 4 5 6 7 8 9
	// bounds of range:
	Cval* pbegin = myints;                             // ^
	Cval* pend = myints+sizeof(myints)/sizeof(Cval);   // ^                 ^


	Container v1 (m_container_size, Cval(1)); // odd
	Container v2 (m_container_size, Cval(1)); // odd too for std:: algorithm

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		/*	Eliminates elements that satisfy a predicate from a given range 
			without disturbing the order of the remaining elements and 
			returning the end of a new range free of the specified value.
		*/
		pend = std::remove_if (pbegin, pend, IsOdd_remove_if);  // 2 4 6 8 ? ? ? ? ?
																 // ^       ^

		// the range contains:
		Cval mycheck[]={2, 4, 6, 8};
		for (Cval* p = pbegin; p != pend; ++p)
		{
			TEST_CHECK(mycheck[p-pbegin] = *p);			
		}

		It end1 = std::remove_if (v1.begin(), v1.end(), IsOdd_remove_if);
		TEST_CHECK(v1.begin() == end1);
	}
}

template<typename Container>
void test_algorithm::remove_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {10,20,30,30,20,10,10,20}; // 10 20 30 30 20 10 10 20
	Container myvector (8);
	
	It it;
//	size_t i0;

	Container v2(m_container_size, Cval(1));
	Container v3(m_container_size, Cval(-1));


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		/*	Copies elements from a source range to a destination range, 
			except that elements of a specified value are not copied, 
			without disturbing the order of the remaining elements and 
			returning the end of a new destination range.
		*/
		stl::remove_copy (myints, myints + 8, myvector.begin(), 20); // 10 30 30 10 10 0 0 0

		//cout << "myvector contains:";
		int mycheck[]={10, 30, 30, 10, 10, 0, 0, 0};
		for (it=myvector.begin(); it!=myvector.end(); ++it)
		{
			TEST_CHECK(mycheck[it-myvector.begin()] == *it);			
		}

		stl::remove_copy (v2.begin(), v2.end(), v3.begin(), Cval(1));
		for (it = v3.begin(); it != v3.end(); ++it)
			TEST_CHECK(*it == Cval(-1));

#if !defined (DEBUG) // std::_Debug_range2
		//	STD
		std::remove_copy (v2.begin(), v2.end(), v3.begin(), Cval(1));
		for (it = v3.begin(); it != v3.end(); ++it)
			TEST_CHECK(*it == Cval(-1));
#endif
	}
}

//////////////////////////////////////////////////////////////////////////

bool IsOdd_remove_copy_if (int i) { return ((i%2)==1); }

template<typename Container>
void test_algorithm::remove_copy_if(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {1,2,3,4,5,6,7,8,9};
	Container v1 (9); //0 0 0 0 0 0 0 0 0
	
	It it;
//	size_t i0;

	Container v2(m_container_size, Cval(1));
	Container v3(m_container_size, Cval(-1));


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		/*	Copies elements from a source range to a destination range, 
			except that satisfying a predicate are not copied,
			without disturbing the order of the remaining elements 
			and returning the end of a new destination range.
		*/
		stl::remove_copy_if (myints, myints+9, v1.begin(), IsOdd_remove_copy_if);

		//cout << "v1 contains:";
		Cval check[]={2, 4, 6, 8, 0, 0, 0, 0, 0};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(check[it-v1.begin()] == *it);			
		}

		stl::remove_copy_if (v2.begin(), v2.end(), v3.begin(), IsOdd_remove_copy_if);
		for (it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK (*it == Cval(-1));
		}
		
#if !defined (DEBUG)
		//	STD
		std::remove_copy_if (v2.begin(), v2.end(), v3.begin(), IsOdd_remove_copy_if);
		for (it = v3.begin(); it != v3.end(); ++it)
		{
			TEST_CHECK (*it == Cval(-1));
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_unique (int i, int j) {
	return (i==j);
}

template<typename Container>
void test_algorithm::unique(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {10,20,20,20,30,30,20,20,10};
	Container v1(myints, myints + 9);
	Container v2(v1);

	It it;
//	size_t i0;

	Container v3(m_container_size, Cval(-1));
	Container v4(m_container_size, Cval(-1));


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		/*	Removes duplicate elements that are adjacent to each other
			in a specified range.
		*/
		// using default comparison:
		it = stl::unique (v1.begin(), v1.end()); // 10 20 30 20 10 ?  ?  ?  ?		
		v1.resize(it - v1.begin());               // 10 20 30 20 10

		// using predicate comparison:
		it = stl::unique (v2.begin(), v2.end(), myfunction_unique);
		v2.resize (it - v2.begin());

		//cout << "v1 contains:";
		Cval mycheck[]={10, 20, 30, 20, 10};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v2.begin()] == *it);			
		}

		It end3 = stl::unique (v3.begin(), v3.end());
		TEST_CHECK(++v3.begin() == end3);
		v3.resize(m_container_size, Cval(-1));
		end3 = stl::unique (v3.begin(), v3.end(), myfunction_unique);
		TEST_CHECK(++v3.begin() == end3);


		//	STD
#if !defined (DEBUG)
		It end4 = std::unique (v4.begin(), v4.end());
		TEST_CHECK(++v4.begin() == end4);
		v4.resize(m_container_size, Cval(-1));
		end4 = std::unique (v4.begin(), v4.end(), myfunction_unique);
		TEST_CHECK(++v4.begin() == end4);
#endif
	}	
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_unique_copy (int i, int j) {
	return (i == j);
}

template<typename Container>
void test_algorithm::unique_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {10,20,20,20,30,30,20,20,10};
	Container v1 (9);
	
	It it;
//	size_t i0;

	Container v2 (m_container_size, Cval(-1));
	Container v3 (m_container_size, Cval(-1));

	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Copies elements from a source range into a destination range
			except for the duplicate elements that are adjacent to each other.
		*/
		// using default comparison:
		// v1: 10 20 30 20 10 0  0  0  0
		it = stl::unique_copy (myints, myints + 9, v1.begin());
				
		// v1: 10 10 20 20 30 0  0  0  0
		stl::sort (v1.begin(),it);

		// using predicate comparison:
		it = stl::unique_copy (v1.begin(), it, v1.begin(), myfunction_unique_copy);
		
		// 10 20 30 20 30 0  0  0  0
		//          ^

		v1.resize( it - v1.begin() );
		// 10 20 30


		//cout << "v1 contains:";
		int mycheck[]={10, 20, 30};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}		
		
		it = stl::unique_copy (v2.begin(), v2.end(), v3.begin());
		TEST_CHECK(++v3.begin() == it);


		//	STD
		// cannot deduce the iterator category
		// std::_Unique_copy : none of the 4 overloads could convert all the argument types
//		it = std::unique_copy (v2.begin(), v2.end(), v3.begin());
//		TEST_CHECK(++v3.begin() == it);
	}
}

template<typename Container>
void test_algorithm::reverse(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1;
	for (size_t i = 1; i < 10; ++i) v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9
		
	It it;
	size_t i0;

	Container v2(m_container_size);
	for (i0 = 0, it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);
	
	Container v3(v2);
	
	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		//	Reverses the order of the elements within a range.
		stl::reverse(v1.begin(), v1.end()); // 9 8 7 6 5 4 3 2 1

		//cout << "v1 contains:";
		Cval mycheck[]={9, 8, 7, 6, 5, 4, 3, 2, 1};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
		}		

		stl::reverse (v2.begin(), v2.end());
		for (i0 = m_container_size-1, it = v2.begin(); it != v2.end(); ++it, --i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}


		//	STD
		// cannot deduce iterator category in:
		// void std::_Reverse<stl::generic_array_iterator<container>>(_BidIt,_BidIt,std::bidirectional_iterator_tag)
//		std::reverse (v3.begin(), v3.end());
//		for (i0 = m_container_size-1, it = v3.begin(); it != v3.end(); ++it, --i0)
//		{
//			TEST_CHECK(*it == Cval(i0));
//		}
	}
}

template<typename Container>
void test_algorithm::reverse_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] ={1,2,3,4,5,6,7,8,9};
	Container v1;
	v1.resize(9);
	
	It it;
	size_t i0;

	Container v2(m_container_size);
	for (it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)	*it = Cval(i0);
	
	Container v3(m_container_size);



	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		/*	Reverses the order of the elements within a source range 
			while copying them into a destination range.
		*/
		stl::reverse_copy (myints, myints+9, v1.begin());

		//cout << "v1 contains:";
		int mycheck[]={9, 8, 7, 6, 5, 4, 3, 2, 1};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
		}

		stl::reverse_copy (v2.begin(), v2.end(), v3.begin());
		for (it = v3.begin(), i0 = m_container_size-1; it != v3.end(); ++it, --i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}

#if !defined (DEBUG)	// std::_Debug_range2
		//	STD
		std::reverse_copy (v2.begin(), v2.end(), v3.begin());
		for (it = v3.begin(), i0 = m_container_size-1; it != v3.end(); ++it, --i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}
#endif
	}	
}

template<typename Container>
void test_algorithm::rotate(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1;
	// v1: 1 2 3 4 5 6 7 8 9
	for (int i=1; i<10; ++i) v1.push_back(i);
	
	It it;
	size_t i0;

	Container v2(m_container_size);
	for (it = v2.begin(), i0=0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	Container v3(v2);
	


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL

		//Exchanges the elements in two adjacent ranges.
		stl::rotate(v1.begin(), v1.begin() + 3, v1.end()); // 4 5 6 7 8 9 1 2 3

		// v1: 4 5 6 7 8 9 1 2 3
		Cval mycheck[]={4, 5, 6, 7, 8, 9, 1, 2, 3};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		It mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		stl::rotate(v2.begin(), mid, v2.end()); //
		
		for(it = v2.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0 - m_container_size/2));
		}

		
		//	STD
		// Cannot deduce the iterator category.
	/*
		std::rotate(v3.begin(), ++v3.begin(), v3.end()); // 199999 1 2 3 4 ... 
		it = v3.begin();
		TEST_CHECK(*it = Cval(m_container_size-1));
		for(i0 = 0; it != v3.end(); ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}
	*/
	}
}

template<typename Container>
void test_algorithm::rotate_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {10,20,30,40,50,60,70}; //10 20 30 40 50 60 70

	Container v1;
	v1.resize(7);
	
	It it;
	size_t i0;

	Container v2(m_container_size); // 0 1 2 3 4 5 ...
	for (it = v2.begin(), i0=0; it != v2.end(); ++it, ++i0) *it = Cval(i0);
	Container v3(m_container_size); // 0 0 0 0 0 0 ...


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		/*	Exchanges the elements in two adjacent ranges within 
			a source range and copies the result to a destination range.
		*/
		// v1: 40 50 60 70 10 20 30
		stl::rotate_copy(myints, myints + 3, myints + 7, v1.begin()); 

		// v1: 40 50 60 70 10 20 30
		Cval mycheck[]={40, 50, 60, 70, 10, 20, 30};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		It mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		stl::rotate_copy(v2.begin(), mid, v2.end(), v3.begin()); //

		for(it = v3.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0 - m_container_size/2));
		}
		

#if !defined(DEBUG)
		//	STD		
		mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		std::rotate_copy(v2.begin(), mid, v2.end(), v3.begin()); //

		for(it = v3.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0 - m_container_size/2));
		}
#endif
	}	
}

//////////////////////////////////////////////////////////////////////////

// random generator function:
ptrdiff_t myrandom_random_shuffle(ptrdiff_t i) { return ::rand()%i;}

// pointer object to it:
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom_random_shuffle;


template<typename Container>
void test_algorithm::random_shuffle(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	
	Container v1;
	for (size_t i=1; i < 500; ++i) 
		v1.push_back((Cval)i); // 1 2 3 4 5 6 7 8 9 ....	

	It it;
	size_t i0;

	Container v2(v1);	

	::srand (unsigned(::time (NULL)));


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Rearranges a sequence of N elements in a range into one of N! 
			possible arrangements selected at random.
		*/
		
		// using built-in random generator:
		stl::random_shuffle(v1.begin(), v1.end());

		// using myrandom:
		stl::random_shuffle(v1.begin(), v1.end(), p_myrandom);
		// v1: 3 4 1 6 8 9 2 7 5 .. random sequence

		/*	It's good enough to check if each entry is unique, 
			which means that probably the shuffle is ok.
		*/
		for(i0 = 1; i0 < v1.size(); ++i0)
		{
			TEST_CHECK(stl::count(v1.begin(), v1.end(), Cval(i0)) == 1);
		}

#if !defined(DEBUG)
		//	STD
		std::random_shuffle(v2.begin(), v2.end());
		std::random_shuffle(v2.begin(), v2.end(), p_myrandom);

		for(i0 = 1; i0 < v1.size(); ++i0)
		{
			TEST_CHECK(stl::count(v2.begin(), v2.end(), Cval(i0)) == 1);
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool IsOdd_partition (int i) { return (i%2)==1; }

template<typename Container>
void test_algorithm::partition(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1;
	for (size_t i=1; i < 10; ++i)
		v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9

	It it, bound;
	size_t i0;

	Container v2(m_container_size);	 // v2: 1 2 3 4 .... 200000
	for (i0=1, it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it.
		*/
		bound = stl::partition(v1.begin(), v1.end(), IsOdd_partition);

		//cout << "odd members:";
		Cval mycheck_odd[]={1, 9, 3, 7, 5};
		for(it = v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			TEST_CHECK(mycheck_odd[i0] == *it);			
		}

		//cout << "\neven members:";
		Cval mycheck_even[]={6, 4, 8, 2};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck_even[i0] == *it);			
		}
		//odd members: 1 9 3 7 5
		//even members: 6 4 8 2

		bound = stl::partition(v2.begin(), v2.end(), IsOdd_partition);
		//odd members: 1 199999 3 199997 5 199995
		for (it = v2.begin(), i0 = 1; it != bound; ++it, ++i0)
		{
			if(i0%2)
			{
				TEST_CHECK(*it == Cval(i0));				
			}
			else
			{
				TEST_CHECK(*it == Cval(m_container_size - i0 + 1));
			}
		}

		//even members: ... 199994 6 199996 4 199998 2 200000
		for (it = --v2.end(), i0 = 1; it != bound; --it, ++i0)
		{
			if(i0%2)
			{
				TEST_CHECK(*it == Cval(m_container_size - i0 + 1));
			}
			else
			{
				TEST_CHECK(*it == Cval(i0));
			}
		}
		// STD - see partition2(...)
	}
}


template<typename Container>
void test_algorithm::partition2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1;
	for (size_t i=1; i < 10; ++i)
		v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9

	It it, bound;
	size_t i0;

	Container v2(m_container_size);	 // v2: 1 2 3 4 .... 200000
	for (i0=1, it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it.
		*/
		bound = std::partition(v1.begin(), v1.end(), IsOdd_partition);

		//cout << "odd members:";
		Cval mycheck_odd[]={1, 9, 3, 7, 5};
		for(it = v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			TEST_CHECK(mycheck_odd[i0] == *it);			
		}

		//cout << "\neven members:";
		Cval mycheck_even[]={6, 4, 8, 2};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck_even[i0] == *it);			
		}
		//odd members: 1 9 3 7 5
		//even members: 6 4 8 2

		bound = std::partition(v2.begin(), v2.end(), IsOdd_partition);
		//odd members: 1 199999 3 199997 5 199995
		for (it = v2.begin(), i0 = 1; it != bound; ++it, ++i0)
		{
			if(i0%2)
			{
				TEST_CHECK(*it == Cval(i0));				
			}
			else
			{
				TEST_CHECK(*it == Cval(m_container_size - i0 + 1));
			}
		}

		//even members: ... 199994 6 199996 4 199998 2 200000
		for (it = --v2.end(), i0 = 1; it != bound; --it, ++i0)
		{
			if(i0%2)
			{
				TEST_CHECK(*it == Cval(m_container_size - i0 + 1));
			}
			else
			{
				TEST_CHECK(*it == Cval(i0));
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
bool IsOdd_stable_partition (int i) { return (i%2)==1; }

template<typename Container>
void test_algorithm::stable_partition(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1;
	// set some values:
	for (size_t i = 1; i < 10; ++i) v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9
	
	It it, bound;
	size_t i0;

	Container v2(m_container_size); //v2: 1 2 3 4 5 .... 199999 200000
	for(i0 = 1, it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STD (the entire method)
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it, preserving the relative order of equivalent elements.
		*/
		bound = std::stable_partition(v1.begin(), v1.end(), IsOdd_stable_partition);

		//odd members: 1 3 5 7 9
		//even members: 2 4 6 8

		//odd members:
		Cval mycheck_odd[]={1, 3, 5, 7, 9};
		for (it=v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			TEST_CHECK(mycheck_odd[i0] == *it);
		}

		//even members:
		Cval mycheck_even[]={2, 4, 6, 8};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck_even[i0] == *it);			
		}
		
		//odd members: 1 3 5 7 9 ... 199999
		bound = std::stable_partition(v2.begin(), v2.end(), IsOdd_stable_partition);
		for(it = v2.begin(), i0 = 1; it != bound; ++it, i0+=2)
		{
			TEST_CHECK(*it == Cval(i0));
		}
		//even members: 2 4 6 8 ... 200000
		for(it = bound, i0 = 2; it != v2.end(); ++it, i0+=2)
		{
			TEST_CHECK(*it == Cval(i0));
		}
	}
}

template<typename Container>
void test_algorithm::stable_partition2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Container v1;
	// set some values:
	for (size_t i = 1; i < 10; ++i) v1.push_back(Cval(i)); // 1 2 3 4 5 6 7 8 9
	
	It it, bound;
	size_t i0;

	Container v2(m_container_size); //v2: 1 2 3 4 5 .... 199999 200000
	for(i0 = 1, it = v2.begin(); it != v2.end(); ++it, ++i0) *it = Cval(i0);

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL (the entire method)
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it, preserving the relative order of equivalent elements.
		*/
		bound = stl::stable_partition(v1.begin(), v1.end(), IsOdd_stable_partition);

		//odd members: 1 3 5 7 9
		//even members: 2 4 6 8

		//odd members:
		Cval mycheck_odd[]={1, 3, 5, 7, 9};
		for (it=v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			TEST_CHECK(mycheck_odd[i0] == *it);
		}

		//even members:
		Cval mycheck_even[]={2, 4, 6, 8};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck_even[i0] == *it);			
		}
		
		//odd members: 1 3 5 7 9 ... 199999
		bound = stl::stable_partition(v2.begin(), v2.end(), IsOdd_stable_partition);
		for(it = v2.begin(), i0 = 1; it != bound; ++it, i0+=2)
		{
			TEST_CHECK(*it == Cval(i0));
		}
		//even members: 2 4 6 8 ... 200000
		for(it = bound, i0 = 2; it != v2.end(); ++it, i0+=2)
		{
			TEST_CHECK(*it == Cval(i0));
		}
	}
}


//Sorting:

//////////////////////////////////////////////////////////////////////////
bool myfunction_sort (int i,int j) { return (i<j); }

struct myclass_sort {
	bool operator() (int i,int j) { return (i<j);}
} myobject_sort;


template<typename Container>
void test_algorithm::sort(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {32,71,12,45,26,80,53,33};
	It it;
//	size_t i0;

	//v1: 32 71 12 45 26 80 53 33
	Container v1(myints, myints + 8);
	Container v2(m_container_size);
	::srand((unsigned)::time(NULL));
	for(it = v2.begin(); it != v2.end(); ++it)
		*it = Cval(::rand() % m_container_size + 1); //>=1 && <= 200000;

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		// using default comparison (operator <):
		stl::sort(v1.begin(), v1.begin() + 4);
		//v1: (12 32 45 71)26 80 53 33

		// using function as comp
		stl::sort(v1.begin() + 4, v1.end(), myfunction_sort);
		//v1: 12 32 45 71(26 33 53 80)

		// using object as comp
		stl::sort(v1.begin(), v1.end(), myobject_sort);
		//v1: (12 26 32 33 45 53 71 80)

		//v1: 12 26 32 33 45 53 71 80
		int mycheck[]={12, 26, 32, 33, 45, 53, 71, 80};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
		}

		stl::sort(v2.begin() + m_container_size/2, v2.end(), myfunction_sort);
		stl::sort(v2.begin(), v2.end());
		for(it = v2.begin() + 1; it != v2.end(); ++it)
			TEST_CHECK(*it >= *(it - 1)); // used ::rand() so equal may exist.

#if !defined (DEBUG)
		//	STD
		std::sort(v3.begin() + m_container_size/2, v3.end(), myfunction_sort);
		std::sort(v3.begin(), v3.end());		
		for(it = v3.begin() + 1; it != v3.end(); ++it)
			TEST_CHECK(*it >= *(it - 1));
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool compare_as_ints_stable_sort (double i, double j)
{
	return (int(i)<int(j));
}

template<typename Container>
void test_algorithm::stable_sort(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval mydoubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};

	Container v1(8);
	v1.assign(mydoubles,mydoubles+8);
	
	It it;
	size_t i0;	

	Container v2(m_container_size);
	::srand((unsigned)::time(NULL));
	for(it = v2.begin(); it != v2.end(); ++it)
		*it = Cval( ::rand() % m_container_size + 1); // 1 to 200000;



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STD  (the entire method)
		/*	Arranges the elements in a specified range 
			into a non-descending order or according to an ordering criterion
			specified by a binary predicate and preserves the relative ordering
			of equivalent elements.
		*/
		
		// using default comparison:
		std::stable_sort(v1.begin(), v1.end());
		Cval mycheck[]={1.32, 1.41, 1.62, 1.73, 2.58, 2.72, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck[i0] == *it);			
		}

		// reset to initial vaues
		v1.assign(mydoubles, mydoubles + 8);		

		// using 'compare_as_ints':
		std::stable_sort(v1.begin(), v1.end(), compare_as_ints_stable_sort);

		Cval mycheck2[]={1.41, 1.73, 1.32, 1.62, 2.72, 2.58, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck2[it-v1.begin()] == *it);			
		}

		std::stable_sort(v2.begin(), v2.end());
		for(it = v2.begin()+1; it != v2.end(); ++it)
			TEST_CHECK(*it >= *(it-1)); // ::rand may have created duplicates;
	}	
}

template<typename Container>
void test_algorithm::stable_sort2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval mydoubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};

	Container v1(8);
	v1.assign(mydoubles,mydoubles+8);
	
	It it;
	size_t i0;	

	Container v2(m_container_size);
	::srand((unsigned)::time(NULL));
	for(it = v2.begin(); it != v2.end(); ++it)
		*it = Cval( ::rand() % m_container_size + 1); // 1 to 200000;



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL  (the entire method)
		/*	Arranges the elements in a specified range 
			into a non-descending order or according to an ordering criterion
			specified by a binary predicate and preserves the relative ordering
			of equivalent elements.
		*/
		
		// using default comparison:
		stl::stable_sort(v1.begin(), v1.end());
		Cval mycheck[]={1.32, 1.41, 1.62, 1.73, 2.58, 2.72, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck[i0] == *it);			
		}

		// reset to initial values
		v1.assign(mydoubles, mydoubles + 8);		

		// using 'compare_as_ints':
		stl::stable_sort(v1.begin(), v1.end(), compare_as_ints_stable_sort);

		Cval mycheck2[]={1.41, 1.73, 1.32, 1.62, 2.72, 2.58, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck2[it-v1.begin()] == *it);			
		}

		stl::stable_sort(v2.begin(), v2.end());
		for(it = v2.begin()+1; it != v2.end(); ++it)
			TEST_CHECK(*it >= *(it-1)); // ::rand may have created duplicates;
	}	
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_partial_sort (int i,int j) { return (i<j); }

template<typename Container>
void test_algorithm::partial_sort(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {9,8,7,6,5,4,3,2,1};
	It it;
	size_t i0;

	Container v1(myints, myints+9);
	Container v2;
	for(i0 = m_container_size; i0 > 0; --i0) v2.push_back ((Cval)i0);
	Container v3(v2.begin(), v2.end());	


	// TEST
	{
		time_printer tm(msg, m_print_time);

		// STL
		/*	Arranges a specified number of the smaller elements in a range 
			into a non-descending order or according to an ordering criterion 
			specified by a binary predicate.
		*/

		// using default comparison (operator <):
		stl::partial_sort(v1.begin(), v1.begin() + 5, v1.end());
		for(it = v1.begin(), i0=1; it != v1.begin()+5; ++it, ++i0)
		{		
			TEST_CHECK(*it == Cval(i0));
		}

		// using function as comp
		stl::partial_sort(v1.begin(), v1.begin() + 5, v1.end(), myfunction_partial_sort);

		//cout << "v1 contains:";
		Cval mycheck[]={1, 2, 3, 4, 5, 9, 8, 7, 6};
		for (it=v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck[i0] == *it);			
		}
		//v1 contains: 1 2 3 4 5 9 8 7 6

		stl::partial_sort(v2.begin(), v2.begin() + m_container_size - 10, v2.end());		
		for(it = v2.begin(), i0 = 1; it != v2.begin() + m_container_size - 10; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}

#if !defined(DEBUG)
		// STD
		std::partial_sort(v3.begin(), v3.begin() + m_container_size - 10, v3.end());		
		for(it = v3.begin(), i0 = 1; it != v3.begin() + m_container_size - 10; ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}
#endif
	}
}


//////////////////////////////////////////////////////////////////////////
bool myfunction_partial_sort_copy (int i,int j) { return (i<j); }

template<typename Container>
void test_algorithm::partial_sort_copy(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {9,8,7,6,5,4,3,2,1};
	Container v1(5); //0 0 0 0 0
	
	It it;
	size_t i0;

	Container v2(m_container_size); // 200000 199999 199998 199997 ... 1
	for(it = v2.begin(), i0 = m_container_size; it != v2.end(); ++it, --i0)
		*it = Cval(i0);

	Container v3(m_container_size/2); // 0 0 0 0 ...

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Copies elements from a source range into a destination range 
			where the source elements are ordered by either less than or 
			another specified binary predicate.
		*/

		// using default comparison (operator <):
		stl::partial_sort_copy (myints, myints + 9, v1.begin(), v1.end());

		// using function as comp
		stl::partial_sort_copy (myints, myints + 9, v1.begin(), v1.end(), myfunction_partial_sort_copy);

		//v1 : 1 2 3 4 5
		Cval mycheck[]={1, 2, 3, 4, 5};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);			
		}

		stl::partial_sort_copy(v2.begin(), v2.end(), v3.begin(), v3.end());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}

#if !defined(DEBUG)
		//	STD
		std::partial_sort_copy(v2.begin(), v2.end(), v3.begin(), v3.end());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
		{
			TEST_CHECK(*it == Cval(i0));
		}
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_nth_element (int i,int j) { return (i<j); }

template<typename Container>
void test_algorithm::nth_element(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Container v1;	
	for (int i=1; i<10; i++) v1.push_back(Cval(i));   // 1 2 3 4 5 6 7 8 9

	It it;
	size_t i0;
	Cval i2;
	
	::srand((unsigned)::time(NULL));

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);
	stl::random_shuffle(v2.begin(), v2.end());

	Container v3(v2);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		/*	Rearranges a sequence of N elements in a range into one of N! 
			possible arrangements selected at random. 
			Obs: thereis no ::seed(..) call, the sequence is always the 
				same in all implementations.
		*/
		stl::random_shuffle(v1.begin(), v1.end());

		//	nth_element
		/*	Partitions a range of elements, correctly locating the nth 
			element of the sequence in the range so that all the elements
			in front of it are less than or equal to it and all the elements
			that follow it in the sequence are greater than or equal to it.
		*/

		// using default comparison (operator <):
		stl::nth_element(v1.begin(), v1.begin() + 5, v1.end());
 
		// using function as comp
		stl::nth_element(v1.begin(), v1.begin() + 5, v1.end(), myfunction_nth_element);

		i2 = *(v1.begin() + 5);
		for(it = v1.begin(); it != v1.begin() + 5; ++it)
		{
			TEST_CHECK(*it < i2);
		}
		for(it = v1.begin() + 5; it != v1.end(); ++it)
		{
			TEST_CHECK(*it >= i2);
		}

		stl::nth_element(v2.begin(), v2.begin()+m_container_size/2, v2.end());
		i2 = *(v2.begin() + m_container_size/2);
		It mid =  v2.begin() + m_container_size/2;
		for(it = v2.begin(); it != mid; ++it)
		{
			TEST_CHECK(*it < i2);
		}
		for(it = mid; it != v2.end(); ++it)
		{
			TEST_CHECK(*it >= i2);
		}

#if !defined(DEBUG)
		//	STD
		// using default comparison (operator <):
		std::nth_element(v3.begin(), v3.begin()+m_container_size/2, v3.end());
		i2 = *(v3.begin() + m_container_size/2);
		mid = v3.begin() + m_container_size/2;
		for(it = v3.begin(); it != mid; ++it)
		{
			TEST_CHECK(*it < i2);
		}
		for(it = mid; it != v3.end(); ++it)
		{
			TEST_CHECK(*it >= i2);
		}
#endif
	}
}


//Binary search (operating on sorted ranges):
template<typename Container>
void test_algorithm::lower_bound(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	typedef typename Container::difference_type Diff;


	Cval myints[] = {10,20,30,30,20,10,10,20};

	Container v1(myints, myints + 8); // 10 20 30 30 20 10 10 20

	It low, up, it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		stl::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		low = stl::lower_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //4th element
		up  = stl::upper_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //7th element

		TEST_CHECK((low - v1.begin()) == 3);
		TEST_CHECK(( up - v1.begin()) == 6);

		low = stl::lower_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));
		up = stl::upper_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));


		Diff d0v2 = low - v2.begin();
		Diff d2v2 = up - v2.begin();
		TEST_CHECK( d0v2 == m_container_size/2 - 1 );
		TEST_CHECK( d2v2 == m_container_size/2 );

		// STD - see lower_bound2(...)
	}
}


//Binary search (operating on sorted ranges):
template<typename Container>
void test_algorithm::lower_bound2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	typedef typename Container::difference_type Diff;


	Cval myints[] = {10,20,30,30,20,10,10,20};

	Container v1(myints, myints + 8); // 10 20 30 30 20 10 10 20

	It low, up, it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL
		stl::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		low = std::lower_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //4th element
		up  = std::upper_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //7th element

		TEST_CHECK((low - v1.begin()) == 3);
		TEST_CHECK(( up - v1.begin()) == 6);

		low = std::lower_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));
		up = std::upper_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));


		Diff d0v2 = low - v2.begin();
		Diff d2v2 = up - v2.begin();
		TEST_CHECK( d0v2 == m_container_size/2 - 1 );
		TEST_CHECK( d2v2 == m_container_size/2 );
	}
}

template<typename Container>
void test_algorithm::upper_bound(const char* msg)
{
	// see lower_bound
}

//////////////////////////////////////////////////////////////////////////
bool mygreater_equal_range (int i, int j) { return (i > j); }

template<typename Container>
void test_algorithm::equal_range(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	typedef typename stl::pair<It, It> MPair;
	

	Cval myints[] = {10,20,30,30,20,10,10,20};
	Container v1(myints, myints + 8); // 10 20 30 30 20 10 10 20
	
	MPair bounds;
	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		//	using default comparison:
		stl::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		/*	Finds a pair of positions in an ordered range, the first less
			than or equivalent to the position of a specified element and 
			the second greater than the element's position, where the sense 
			of equivalence or ordering used to establish the positions 
			in the sequence may be specified by a binary predicate.
		*/
		bounds = stl::equal_range<It, Cval>(v1.begin(), v1.end(), 20);

		// using "mygreater_equal_range" as comp:
		stl::sort (v1.begin(), v1.end(), mygreater_equal_range);                                 // 30 30 20 20 20 10 10 10
		bounds = stl::equal_range<It, Cval>(v1.begin(), v1.end(), 20, mygreater_equal_range);    //       ^        ^

		TEST_CHECK((int)(bounds.first - v1.begin()) == 2);
		TEST_CHECK((int)(bounds.second - v1.begin()) == 5);


		bounds = stl::equal_range<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		TEST_CHECK(bounds.first - v2.begin() == m_container_size/2);
		TEST_CHECK(bounds.second - v2.begin() == m_container_size/2+1);
		// STD - see equal_range2(...)
	}
}

template<typename Container>
void test_algorithm::equal_range2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;
	typedef typename std::pair<It, It> MPair;
	

	Cval myints[] = {10,20,30,30,20,10,10,20};
	Container v1(myints, myints + 8); // 10 20 30 30 20 10 10 20
	
	MPair bounds;
	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		//	using default comparison:
		std::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		/*	Finds a pair of positions in an ordered range, the first less
			than or equivalent to the position of a specified element and 
			the second greater than the element's position, where the sense 
			of equivalence or ordering used to establish the positions 
			in the sequence may be specified by a binary predicate.
		*/
		bounds = std::equal_range<It, Cval>(v1.begin(), v1.end(), 20);

		// using "mygreater_equal_range" as comp:
		stl::sort (v1.begin(), v1.end(), mygreater_equal_range);                                 // 30 30 20 20 20 10 10 10
		bounds = std::equal_range<It, Cval>(v1.begin(), v1.end(), 20, mygreater_equal_range);    //       ^        ^

		TEST_CHECK((int)(bounds.first - v1.begin()) == 2);
		TEST_CHECK((int)(bounds.second - v1.begin()) == 5);


		bounds = std::equal_range<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		TEST_CHECK(bounds.first - v2.begin() == m_container_size/2);
		TEST_CHECK(bounds.second - v2.begin() == m_container_size/2+1);
	}
}

//////////////////////////////////////////////////////////////////////////

bool myfunction_binary_search (int i,int j) { return (i<j); }


template<typename Container>
void test_algorithm::binary_search(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {1,2,3,4,5,4,3,2,1};
	Container v1(myints, myints + 9); // 1 2 3 4 5 4 3 2 1

	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STD (the entire method)
		// using default comparison:
		std::sort(v1.begin(), v1.end());

		//cout << "looking for a 3... ";
		bool res = std::binary_search<It, Cval>(v1.begin(), v1.end(), 3);
		TEST_CHECK(res);

		// using myfunction as comp:
		std::sort(v1.begin(), v1.end(), myfunction_binary_search);

		//cout << "looking for a 6... ";
		res = std::binary_search<It, Cval>(v1.begin(), v1.end(), 6, myfunction_binary_search);
		TEST_CHECK(!res);

		res = std::binary_search<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		TEST_CHECK(res);
		res = std::binary_search<It, Cval>(v2.begin(), v2.end(), 2*m_container_size, myfunction_binary_search);
		TEST_CHECK(!res);
	}
}

template<typename Container>
void test_algorithm::binary_search2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {1,2,3,4,5,4,3,2,1};
	Container v1(myints, myints + 9); // 1 2 3 4 5 4 3 2 1

	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 1; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL (the entire method)
		// using default comparison:
		stl::sort(v1.begin(), v1.end());

		//cout << "looking for a 3... ";
		bool res = stl::binary_search<It, Cval>(v1.begin(), v1.end(), 3);
		TEST_CHECK(res);

		// using myfunction as comp:
		stl::sort(v1.begin(), v1.end(), myfunction_binary_search);

		//cout << "looking for a 6... ";
		res = stl::binary_search<It, Cval>(v1.begin(), v1.end(), 6, myfunction_binary_search);
		TEST_CHECK(!res);

		res = stl::binary_search<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		TEST_CHECK(res);
		res = stl::binary_search<It, Cval>(v2.begin(), v2.end(), 2*m_container_size, myfunction_binary_search);
		TEST_CHECK(!res);
	}
}

//Merge (operating on sorted ranges):
template<typename Container>
void test_algorithm::merge(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	
	Container v1(10);

	It it;
	size_t i0;

	Container v2(m_container_size/2); // 0 1 2 3 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(m_container_size/2); // 100000 100001 100002 ...
	for(it = v3.begin(); it != v3.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v4(m_container_size);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STD
		std::sort(first, first + 5);
		std::sort(second, second + 5);

		/*	Combines all the elements from two sorted source ranges 
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		std::merge (first, first + 5, second, second + 5, v1.begin());

		//cout << "The resulting vector contains:";
		Cval mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck[i0] == *it);
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50

		std::sort(v2.begin(), v2.end());
		std::sort(v3.begin(), v3.end());
		std::merge(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
	}
}

template<typename Container>
void test_algorithm::merge2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	
	Container v1(10);

	It it;
	size_t i0;

	Container v2(m_container_size/2); // 0 1 2 3 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(m_container_size/2); // 100000 100001 100002 ...
	for(it = v3.begin(); it != v3.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v4(m_container_size);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL
		stl::sort(first, first + 5);
		stl::sort(second, second + 5);

		/*	Combines all the elements from two sorted source ranges 
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		stl::merge (first, first + 5, second, second + 5, v1.begin());

		//cout << "The resulting vector contains:";
		Cval mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			TEST_CHECK(mycheck[i0] == *it);
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50

		stl::sort(v2.begin(), v2.end());
		stl::sort(v3.begin(), v3.end());
		stl::merge(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
	}
}

template<typename Container>
void test_algorithm::inplace_merge(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval first[] = {5,10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10);
	
	It it;
	size_t i0;

	Container v2(m_container_size/2); //0 2 4 6 8 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0+=2)
		*it = Cval(i0);

	Container v3(m_container_size/2); //1 3 5 7 9 ...
	for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, i0+=2)
		*it = Cval(i0);

	Container v4(m_container_size);


	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STD  (the entire method)
		std::sort(first, first + 5);
		std::sort(second, second + 5);

		std::copy(first, first + 5, v1.begin());
		std::copy(second, second + 5, v1.begin() + 5);

		/*	Combines the elements from two consecutive sorted ranges 
			into a single sorted range, where the ordering criterion 
			may be specified by a binary predicate.
		*/
		std::inplace_merge(v1.begin(), v1.begin() + 5, v1.end());

		//cout << "The resulting vector contains:";
		int mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50


		std::copy(v2.begin(), v2.end(), v4.begin());
		std::copy(v3.begin(), v3.end(), v4.begin() + v2.size());
		std::inplace_merge(v4.begin(), v4.begin() + m_container_size/2, v4.end());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::inplace_merge2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval first[] = {5,10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10);
	
	It it;
	size_t i0;

	Container v2(m_container_size/2); //0 2 4 6 8 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0+=2)
		*it = Cval(i0);

	Container v3(m_container_size/2); //1 3 5 7 9 ...
	for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, i0+=2)
		*it = Cval(i0);

	Container v4(m_container_size);

	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL (the entire method)
		stl::sort(first, first + 5);
		stl::sort(second, second + 5);

		stl::copy(first, first + 5, v1.begin());
		stl::copy(second, second + 5, v1.begin() + 5);

		/*	Combines the elements from two consecutive sorted ranges 
			into a single sorted range, where the ordering criterion 
			may be specified by a binary predicate.
		*/
		stl::inplace_merge(v1.begin(), v1.begin() + 5, v1.end());

		//cout << "The resulting vector contains:";
		int mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			TEST_CHECK(mycheck[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50


		stl::copy(v2.begin(), v2.end(), v4.begin());
		stl::copy(v3.begin(), v3.end(), v4.begin() + v2.size());
		stl::inplace_merge(v4.begin(), v4.begin() + m_container_size/2, v4.end());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

//////////////////////////////////////////////////////////////////////////
bool myfunction_includes(int i, int j) { return i < j; }

template<typename Container>
void test_algorithm::includes(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval c1[] = {5,10,15,20,25,30,35,40,45,50};
	Cval c2[] = {40,30,20,10};

	It it;
	size_t i0;
	bool res;

	Container v1(m_container_size);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v2(m_container_size/4);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0+=2)
		*it = Cval(i0);
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STD (the entire method)
		std::sort(c1, c1 + 10);       //5,10,15,20,25,30,35,40,45,50,
		std::sort(c2, c2 + 4);        //  10,   20,   30,   40

		/*	Tests whether one sorted range contains all the elements contained
			in a second sorted range, where the ordering or equivalence 
			criterion between elements may be specified by a binary predicate.
		*/
		// using default comparison:
		res = std::includes(c1, c1+10, c2, c2+4);
		TEST_CHECK( res );
		//cout << "c1 includes c2!" << endl;
		
		// using myfunction as comp:
		res = std::includes(c1, c1+10, c2, c2+4, myfunction_includes);
		TEST_CHECK( res );

		//c1 includes c2!
		//c1 includes c2!

		res = std::includes(v1.begin(), v1.end(), v2.begin(), v2.end());
		TEST_CHECK( res );
	}
}

template<typename Container>
void test_algorithm::includes2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval c1[] = {5,10,15,20,25,30,35,40,45,50};
	Cval c2[] = {40,30,20,10};

	It it;
	size_t i0;
	bool res;

	Container v1(m_container_size);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v2(m_container_size/4);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0+=2)
		*it = Cval(i0);
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL (the entire method)
		stl::sort(c1, c1 + 10);       //5,10,15,20,25,30,35,40,45,50,
		stl::sort(c2, c2 + 4);        //  10,   20,   30,   40

		/*	Tests whether one sorted range contains all the elements contained
			in a second sorted range, where the ordering or equivalence 
			criterion between elements may be specified by a binary predicate.
		*/
		// using default comparison:
		res = stl::includes(c1, c1+10, c2, c2+4);
		TEST_CHECK( res );
		//cout << "c1 includes c2!" << endl;
		
		// using myfunction as comp:
		res = stl::includes(c1, c1+10, c2, c2+4, myfunction_includes);
		TEST_CHECK( res );

		//c1 includes c2!
		//c1 includes c2!

		res = stl::includes(v1.begin(), v1.end(), v2.begin(), v2.end());
		TEST_CHECK( res );
	}
}

template<typename Container>
void test_algorithm::set_union(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it;
	size_t i0;

	Container v2(m_container_size/2); // 0 2 4 6 8 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0 += 2)
		*it = Cval(i0);

	Container v3(m_container_size/2); // 1 3 5 7 9 ...
	for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, i0 += 2)
		*it = Cval(i0);
	
	Container v4(m_container_size); // 0 0 0 0 ...



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STD (the entire method)
		std::sort(first, first + 5);                //  5 10 15 20 25
		std::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to at least one of two 
			sorted source ranges into a single, sorted destination range, 
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = std::set_union (first, first+5, second, second+5, v1.begin());
		// 5 10 15 20 25 30 40 50  0  0

		Cval mycheck[]={5, 10, 15, 20, 25, 30, 40, 50,  0,  0};
		for(size_t i=0; i < v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "union has " << int(it - v1.begin()) << " elements.\n";
		TEST_CHECK((it-v1.begin()) == 8);
		//union has 8 elements

		std::set_union(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::set_union2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it;
	size_t i0;

	Container v2(m_container_size/2); // 0 2 4 6 8 ...
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, i0 += 2)
		*it = Cval(i0);

	Container v3(m_container_size/2); // 1 3 5 7 9 ...
	for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, i0 += 2)
		*it = Cval(i0);
	
	Container v4(m_container_size); // 0 0 0 0 ...



	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL (the entire method)
		stl::sort(first, first + 5);                //  5 10 15 20 25
		stl::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to at least one of two 
			sorted source ranges into a single, sorted destination range, 
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = stl::set_union (first, first+5, second, second+5, v1.begin());
		// 5 10 15 20 25 30 40 50  0  0

		Cval mycheck[]={5, 10, 15, 20, 25, 30, 40, 50,  0,  0};
		for(size_t i=0; i < v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "union has " << int(it - v1.begin()) << " elements.\n";
		TEST_CHECK((it-v1.begin()) == 8);
		//union has 8 elements

		stl::set_union(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::set_intersection(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(v2);
	Container v4(v2);
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STD (the entire method)
		std::sort(first, first + 5);                //  5 10 15 20 25
		std::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to both sorted source ranges
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		it = std::set_intersection (first, first+5, second, second+5, v1.begin());
		// 10 20 0  0  0  0  0  0  0  0

		Cval mycheck[]={10, 20, 0,  0,  0,  0,  0,  0,  0,  0};

		for(size_t i=0; i < v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "intersection has " << int(it - v1.begin()) << " elements.\n";
		TEST_CHECK((int)(it-v1.begin()) == 2);
		//intersection has 2 elements
		
		it = std::set_intersection(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		TEST_CHECK(it - v4.begin() == m_container_size);
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::set_intersection2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = {5, 10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(v2);
	Container v4(v2);
	

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		
		//	STL (the entire method)
		stl::sort(first, first + 5);                //  5 10 15 20 25
		stl::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to both sorted source ranges
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		it = stl::set_intersection (first, first+5, second, second+5, v1.begin());
		// 10 20 0  0  0  0  0  0  0  0

		Cval mycheck[]={10, 20, 0,  0,  0,  0,  0,  0,  0,  0};

		for(size_t i=0; i < v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "intersection has " << int(it - v1.begin()) << " elements.\n";
		TEST_CHECK((int)(it-v1.begin()) == 2);
		//intersection has 2 elements
		
		it = stl::set_intersection(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		TEST_CHECK(it - v4.begin() == m_container_size);
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			TEST_CHECK(*it == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::set_difference(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[]  = { 5,10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it, it2;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);
	
	Container v3(m_container_size / 2);
	for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, i0 += 2)
		*it = Cval(i0);

	Container v4(m_container_size);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		stl::sort (first,first+5);                //  5 10 15 20 25
		stl::sort (second,second+5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to one sorted source range,
			but not to a second sorted source range, into a single, sorted 
			destination range, where the ordering criterion may be specified 
			by a binary predicate.
		*/

		it = stl::set_difference (first, first+5, second, second+5, v1.begin());
		// 5 15 25  0  0  0  0  0  0  0

		Cval mycheck[]={5, 15, 25,  0,  0,  0,  0,  0,  0,  0};
		for(size_t i=0; i<v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}
		//cout << "difference has " << int(it - v1.begin()) << " elements.\n";
		TEST_CHECK((int)(it-v1.begin()) == 3);
		//difference has 3 elements


		it = stl::set_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), stl::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			TEST_CHECK(*it2 == Cval(i0));

		//	STD
		it = stl::set_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), std::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			TEST_CHECK(*it2 == Cval(i0));		
	}
}

template<typename Container>
void test_algorithm::set_symmetric_difference(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[] =  { 5,10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it, it2;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(m_container_size / 2);
	for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, i0 += 2)
		*it = Cval(i0);

	Container v4(m_container_size);



	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STD (the entire method)
		std::sort (first, first + 5);    //  5 10 15 20 25
		std::sort (second, second + 5);  // 10 20 30 40 50


		/*	Unites all of the elements that belong to one, but not both, 
			of the sorted source ranges into a single, sorted destination range,
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = std::set_symmetric_difference (first, first+5, second, second+5, v1.begin());
		// 5 15 25 30 40 50  0  0  0  0

		Cval mycheck[]={5, 15, 25, 30, 40, 50,  0,  0,  0,  0};
		for(size_t i=0; i<v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "symmetric difference has " << int(it - v1.begin()) << " elements.\n";

		TEST_CHECK((int)(it-v1.begin()) == 6);
		//symmetric difference has 6 elements

		it = std::set_symmetric_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), std::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			TEST_CHECK(*it2 == Cval(i0));
	}
}

template<typename Container>
void test_algorithm::set_symmetric_difference2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval first[] =  { 5,10,15,20,25};
	Cval second[] = {50,40,30,20,10};
	Container v1(10); // 0  0  0  0  0  0  0  0  0  0
	
	It it, it2;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v3(m_container_size / 2);
	for(it = v3.begin(), i0 = 0; it != v3.end(); ++it, i0 += 2)
		*it = Cval(i0);

	Container v4(m_container_size);



	//	TEST
	{
		time_printer tp(msg, m_print_time);

		//	STL (the entire method)
		stl::sort (first, first + 5);    //  5 10 15 20 25
		stl::sort (second, second + 5);  // 10 20 30 40 50


		/*	Unites all of the elements that belong to one, but not both, 
			of the sorted source ranges into a single, sorted destination range,
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = stl::set_symmetric_difference (first, first+5, second, second+5, v1.begin());
		// 5 15 25 30 40 50  0  0  0  0

		Cval mycheck[]={5, 15, 25, 30, 40, 50,  0,  0,  0,  0};
		for(size_t i=0; i<v1.size(); ++i)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
		}

		//cout << "symmetric difference has " << int(it - v1.begin()) << " elements.\n";

		TEST_CHECK((int)(it-v1.begin()) == 6);
		//symmetric difference has 6 elements

		it = stl::set_symmetric_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), stl::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			TEST_CHECK(*it2 == Cval(i0));
	}
}


//Heap:
template<typename Container>
void test_algorithm::push_heap(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {10,20,30,5,15};

	Container v1(myints, myints + 5);

	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);
	
	::srand((unsigned)::time(NULL));
	std::random_shuffle(v2.begin(), v2.end());

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STD (entire method)
		/*	make_heap
			Converts elements from a specified range into a heap in which 
			the first element is the largest and for which a sorting criterion 
			may be specified with a binary predicate.
		*/

		std::make_heap (v1.begin(), v1.end());
		//initial max heap : 30 (10 20 5 15)
		TEST_CHECK(v1.front() == 30);

		/*	pop_heap
			Removes the largest element from the front of a heap to 
			the next-to-last position in the range and then forms a new heap 
			from the remaining elements.
		*/
		std::pop_heap (v1.begin(), v1.end());
		// v1: 20 (10 5 15 30)
		v1.pop_back();
		// v1: 20 (10 5 15)

		//cout << "max heap after pop : " << v1.front() << endl;
		TEST_CHECK(v1.front() == 20);


		/*	push_heap
			Adds an element that is at the end of a range to an existing heap 
			consisting of the prior elements in the range.
		*/
		v1.push_back(99);
		std::push_heap (v1.begin(), v1.end());
		// v1: 99 (20 10 5 15)

		//cout << "max heap after push: " << v1.front() << endl;
		TEST_CHECK(v1.front() == 99);

		//Converts a heap into a sorted range.
		std::sort_heap (v1.begin(), v1.end());

		//cout << "final sorted range :";
		int mycheck[]={5, 10, 15, 20, 99};
		for (unsigned i=0; i<v1.size(); i++)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
			//cout << " " << v[i];
		}


		//v2: 0 1 2 3 ... 199999
		std::make_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 199999 (0 1 2 3 ... 199998)
		TEST_CHECK(*v2.begin() == Cval(m_container_size-1));

		std::pop_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 199998 (0 1 2 3 ... 199999)
		TEST_CHECK(*v2.begin() == m_container_size-2);
		TEST_CHECK(*v2.rbegin() == m_container_size-1);

		v2.pop_back();
		//v2: 199998 (0 1 2 3 ... 199997)
		v2.push_back(m_container_size);
		std::push_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 200000 (199998 0 1 2 3 ... 199997)
		TEST_CHECK(v2.front() == Cval(m_container_size));

		std::sort_heap(v2.begin(), v2.end());
		//v2: 0 1 2 3 ...
		for(it = v2.begin()+1; it != v2.end(); ++it)
			TEST_CHECK(*it > *(it-1));

		//v3: 0 1 2 3 ... 199999
		std::make_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 199999 (0 1 2 3 ... 199998)
		TEST_CHECK(*v3.begin() == Cval(m_container_size-1));

		std::pop_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 199998 (0 1 2 3 ... 199999)
		TEST_CHECK(*v3.begin() == m_container_size-2);
		TEST_CHECK(*v3.rbegin() == m_container_size-1);

		v3.pop_back();
		//v3: 199998 (0 1 2 3 ... 199997)
		v3.push_back(m_container_size);
		std::push_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 200000 (199998 0 1 2 3 ... 199997)
		TEST_CHECK(v3.front() == Cval(m_container_size));

		std::sort_heap(v3.begin(), v3.end());
		//v3: 0 1 2 3 ...
		for(it = v3.begin()+1; it != v3.end(); ++it)
			TEST_CHECK(*it > *(it-1));
	}
}

template<typename Container>
void test_algorithm::push_heap2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;


	Cval myints[] = {10,20,30,5,15};

	Container v1(myints, myints + 5);

	It it;
	size_t i0;

	Container v2(m_container_size);
	for(it = v2.begin(), i0 = 0; it != v2.end(); ++it, ++i0)
		*it = Cval(i0);
	
	::srand((unsigned)::time(NULL));
	stl::random_shuffle(v2.begin(), v2.end());

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL (the entire method)
		/*	make_heap
			Converts elements from a specified range into a heap in which 
			the first element is the largest and for which a sorting criterion 
			may be specified with a binary predicate.
		*/

		stl::make_heap (v1.begin(), v1.end());
		//initial max heap : 30 (10 20 5 15)
		TEST_CHECK(v1.front() == 30);

		/*	pop_heap
			Removes the largest element from the front of a heap to 
			the next-to-last position in the range and then forms a new heap 
			from the remaining elements.
		*/
		stl::pop_heap (v1.begin(), v1.end());
		// v1: 20 (10 5 15 30)
		v1.pop_back();
		// v1: 20 (10 5 15)

		//cout << "max heap after pop : " << v1.front() << endl;
		TEST_CHECK(v1.front() == 20);


		/*	push_heap
			Adds an element that is at the end of a range to an existing heap 
			consisting of the prior elements in the range.
		*/
		v1.push_back(99);
		stl::push_heap (v1.begin(), v1.end());
		// v1: 99 (20 10 5 15)

		//cout << "max heap after push: " << v1.front() << endl;
		TEST_CHECK(v1.front() == 99);

		//Converts a heap into a sorted range.
		stl::sort_heap (v1.begin(), v1.end());

		//cout << "final sorted range :";
		int mycheck[]={5, 10, 15, 20, 99};
		for (unsigned i=0; i<v1.size(); i++)
		{
			TEST_CHECK(mycheck[i] == v1[i]);
			//cout << " " << v[i];
		}


		//v2: 0 1 2 3 ... 199999
		stl::make_heap(v2.begin(), v2.end(), stl::less<Cval>());
		//v2: 199999 (0 1 2 3 ... 199998)
		TEST_CHECK(*v2.begin() == Cval(m_container_size-1));

		stl::pop_heap(v2.begin(), v2.end(), stl::less<Cval>());
		//v2: 199998 (0 1 2 3 ... 199999)
		TEST_CHECK(*v2.begin() == m_container_size-2);
		TEST_CHECK(*v2.rbegin() == m_container_size-1);

		v2.pop_back();
		//v2: 199998 (0 1 2 3 ... 199997)
		v2.push_back(m_container_size);
		stl::push_heap(v2.begin(), v2.end(), stl::less<Cval>());
		//v2: 200000 (199998 0 1 2 3 ... 199997)
		TEST_CHECK(v2.front() == Cval(m_container_size));

		stl::sort_heap(v2.begin(), v2.end());
		//v2: 0 1 2 3 ...
		for(it = v2.begin()+1; it != v2.end(); ++it)
			TEST_CHECK(*it > *(it-1));
		
		//v3: 0 1 2 3 ... 199999
		stl::make_heap(v3.begin(), v3.end(), stl::less<Cval>());
		//v3: 199999 (0 1 2 3 ... 199998)
		TEST_CHECK(*v3.begin() == Cval(m_container_size-1));

		stl::pop_heap(v3.begin(), v3.end(), stl::less<Cval>());
		//v3: 199998 (0 1 2 3 ... 199999)
		TEST_CHECK(*v3.begin() == m_container_size-2);
		TEST_CHECK(*v3.rbegin() == m_container_size-1);

		v3.pop_back();
		//v3: 199998 (0 1 2 3 ... 199997)
		v3.push_back(m_container_size);
		stl::push_heap(v3.begin(), v3.end(), stl::less<Cval>());
		//v3: 200000 (199998 0 1 2 3 ... 199997)
		TEST_CHECK(v3.front() == Cval(m_container_size));

		stl::sort_heap(v3.begin(), v3.end());
		//v3: 0 1 2 3 ...
		for(it = v3.begin()+1; it != v3.end(); ++it)
			TEST_CHECK(*it > *(it-1));
	}
}

template<typename Container>
void test_algorithm::pop_heap(const char* msg)
{
	// see push_heap
}



template<typename Container>
void test_algorithm::make_heap(const char* msg)
{
	// see push_heap
}

template<typename Container>
void test_algorithm::sort_heap(const char* msg)
{
	// see push_heap
}

//Min/max:
template<typename Container>
void test_algorithm::min2(const char* msg)
{
	typedef typename Container::value_type Cval;

	/*	Obs:
		stl::min( will not prevent MS compiler from expanding min to its macro.
		stl::min(2, 1) : error.
		stl::min< will however DO prevent macro expanding due to template arg.
		stl::min<int>(2, 1) : OK.
	*/


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	STL
		TEST_CHECK( stl::min<Cval>(1,2) == 1 );
		TEST_CHECK( stl::min<int>(1,2) == 1 );
		TEST_CHECK( stl::min<int>(2,1) == 1 );
		TEST_CHECK( stl::min<char>('a','z') == 'a' );
		TEST_CHECK( stl::min<double>(3.14,2.72) == 2.72 );   


		//	STD
		TEST_CHECK( std::min<Cval>(1,2) == 1 );
		TEST_CHECK( std::min<int>(1,2) == 1 );
		TEST_CHECK( std::min<int>(2,1) == 1 );
		TEST_CHECK( std::min<char>('a','z') == 'a' );
		TEST_CHECK( std::min<double>(3.14,2.72) == 2.72 ); 
	}	
}

template<typename Container>
void test_algorithm::max2(const char* msg)
{
	typedef typename Container::value_type Cval;


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		TEST_CHECK( stl::max<Cval>(1,2) == 2 );
		TEST_CHECK( stl::max<int>(1,2) == 2 );
		TEST_CHECK( stl::max<long>(2,1) == 2 );
		TEST_CHECK( stl::max<char>('a','z') == 'z' );
		TEST_CHECK( stl::max<double>(3.14,2.72) == 3.14 );

		//	STD
		TEST_CHECK( std::max<Cval>(1,2) == 2 );
		TEST_CHECK( std::max<int>(1,2) == 2 );
		TEST_CHECK( std::max<long>(2,1) == 2 );
		TEST_CHECK( std::max<char>('a','z') == 'z' );
		TEST_CHECK( std::max<double>(3.14,2.72) == 3.14 );
	} 
}

//////////////////////////////////////////////////////////////////////////
bool myfn_min_element(int i, int j) { return i<j; }

struct myclass_min_element {
	bool operator() (int i,int j) { return i<j; }
} myobj_min_element;

template<typename Container>
void test_algorithm::min_element(const char* msg)
{
	typedef typename Container::value_type Cval;

	Cval myints[] = {3,7,2,5,6,4,9};


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL
		
		/*	min_element:
			Finds the first occurrence of smallest element in a specified 
			range where the ordering criterion may be specified by a 
			binary predicate.

			max_element:
			Finds the first occurrence of largest element in a specified 
			range where the ordering criterion may be specified by a 
			binary predicate.
		*/

		//default
		TEST_CHECK(*stl::min_element(myints,myints+7) == 2);
		TEST_CHECK(*stl::max_element(myints,myints+7) == 9);


		// using function myfn as comp:
		TEST_CHECK(*stl::min_element(myints,myints+7,myfn_min_element) == 2);
		TEST_CHECK(*stl::max_element(myints,myints+7,myfn_min_element) == 9);


		// using object myobj as comp:
		TEST_CHECK(*stl::min_element(myints,myints+7,myobj_min_element) == 2);
		TEST_CHECK(*stl::max_element(myints,myints+7,myobj_min_element) == 9);


		//	STD
		//default
		TEST_CHECK(*std::min_element(myints,myints+7) == 2);
		TEST_CHECK(*std::max_element(myints,myints+7) == 9);


		// using function myfn as comp:
		TEST_CHECK(*std::min_element(myints,myints+7,myfn_min_element) == 2);
		TEST_CHECK(*std::max_element(myints,myints+7,myfn_min_element) == 9);


		// using object myobj as comp:
		TEST_CHECK(*std::min_element(myints,myints+7,myobj_min_element) == 2);
		TEST_CHECK(*std::max_element(myints,myints+7,myobj_min_element) == 9);
	}
}


//////////////////////////////////////////////////////////////////////////
bool myfn_max_element(int i, int j) { return i<j; }

struct myclass_max_element {
	bool operator() (int i,int j) { return i<j; }
} myobj_max_element;

template<typename Container>
void test_algorithm::max_element(const char* msg)
{
	// see min_element
}


//////////////////////////////////////////////////////////////////////////
// a case-insensitive comparison function:
bool mycomp_lexicographical_compare (char c1, char c2)
{ return tolower(c1)<tolower(c2); }

template<typename Container>
void test_algorithm::lexicographical_compare(const char* msg)
{
	typedef typename Container::value_type Cval;

	Cval first[] = "Apple";        // 5 letters
	Cval second[]= "apartment";    // 9 letters


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	STL

		//cout << "Using default comparison (operator<): ";
		// first is less then
		TEST_CHECK(stl::lexicographical_compare(first,first+5,second,second+9));
		// second is not less then
		TEST_CHECK(stl::lexicographical_compare(second,second+9,first,first+5) == false);


		//cout << "Using mycomp as comparison object: ";
		// first is not less then (when using mycomp... comparison)
		TEST_CHECK(stl::lexicographical_compare(first,first+5,second,second+9,mycomp_lexicographical_compare) == false);
		// second is less then when using mycomp... comparison
		TEST_CHECK(stl::lexicographical_compare(second,second+9,first,first+5,mycomp_lexicographical_compare));
		/*
		  Using default comparison (operator<): Apple is less than apartment
		  Using mycomp as comparison object: Apple is greater than apartment
		*/

		//	STD
		TEST_CHECK(std::lexicographical_compare(first,first+5,second,second+9));
		TEST_CHECK(std::lexicographical_compare(second,second+9,first,first+5) == false);
		TEST_CHECK(std::lexicographical_compare(first,first+5,second,second+9,mycomp_lexicographical_compare) == false);
		TEST_CHECK(std::lexicographical_compare(second,second+9,first,first+5,mycomp_lexicographical_compare));
	}
}

template<typename Container>
void test_algorithm::next_permutation(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3};
	Cval mycheck[6][3] = {{1, 2, 3}, {1, 3, 2,}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

	It it;
	size_t i0;

	Container v1(5);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v2(v1);


	//	TEST
	{
		// STD (the entire method)
		time_printer tp(msg, m_print_time);
					
		//cout << "The 3! possible permutations with 3 elements:\n";
		std::sort(myints, myints + 3);

		/*	next_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified 
			with a binary predicate.
		*/
		i0 = 0;
		do
		{
			TEST_CHECK(mycheck[i0][0] == myints[0]);
			TEST_CHECK(mycheck[i0][1] == myints[1]);
			TEST_CHECK(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while(std::next_permutation(myints, myints + 3));


		/*
		  The 3! possible permutations with 3 elements:
		  1 2 3
		  1 3 2
		  2 1 3
		  2 3 1
		  3 1 2
		  3 2 1
		*/

		//	STD
		while(std::next_permutation(v1.begin(), v1.end()) &&
			  std::next_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				TEST_CHECK(*it1 == *it2);
		}
	}
}

template<typename Container>
void test_algorithm::next_permutation2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3};
	Cval mycheck[6][3] = {{1, 2, 3}, {1, 3, 2,}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

	It it;
	size_t i0;

	Container v1(5);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);

	Container v2(v1);


	//	TEST
	{
		//	STL (the entire method)
		time_printer tp(msg, m_print_time);
		
			
		//cout << "The 3! possible permutations with 3 elements:\n";
		stl::sort(myints, myints + 3);

		/*	next_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified 
			with a binary predicate.
		*/
		i0 = 0;
		do
		{
			TEST_CHECK(mycheck[i0][0] == myints[0]);
			TEST_CHECK(mycheck[i0][1] == myints[1]);
			TEST_CHECK(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while(stl::next_permutation(myints, myints + 3));


		/*
		  The 3! possible permutations with 3 elements:
		  1 2 3
		  1 3 2
		  2 1 3
		  2 3 1
		  3 1 2
		  3 2 1
		*/

		//	STD
		while(stl::next_permutation(v1.begin(), v1.end()) &&
			  stl::next_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				TEST_CHECK(*it1 == *it2);
		}
	}
}

template<typename Container>
void test_algorithm::prev_permutation(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3};
	Cval mycheck[6][3]={{3,2,1},{3,1,2},{2,3,1},{2,1,3},{1,3,2},{1,2,3}};	
	
	It it;
	size_t i0;

	Container v1(5);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);
	Container v2(v1);


	//	TEST
	{
		//	STD (the entire method)
		time_printer tp(msg, m_print_time);		

		//cout << "The 3! possible permutations with 3 elements:\n";
		std::sort(myints, myints + 3);
		std::reverse(myints, myints + 3);

		/*	prev_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified with 
			a binary predicate.
		*/
		i0 = 0;
		do
		{
			TEST_CHECK(mycheck[i0][0] == myints[0]);
			TEST_CHECK(mycheck[i0][1] == myints[1]);
			TEST_CHECK(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while ( std::prev_permutation(myints, myints+3) );

		/*
		  3 2 1
		  3 1 2
		  2 3 1
		  2 1 3
		  1 3 2
		  1 2 3
		*/
		
		while(std::prev_permutation(v1.begin(), v1.end()) && 
			  std::prev_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				TEST_CHECK(*it1 == *it2);
		}
	}
}

template<typename Container>
void test_algorithm::prev_permutation2(const char* msg)
{
	typedef typename Container::value_type Cval;
	typedef typename Container::iterator It;

	Cval myints[] = {1,2,3};
	Cval mycheck[6][3]={{3,2,1},{3,1,2},{2,3,1},{2,1,3},{1,3,2},{1,2,3}};	
	
	It it;
	size_t i0;

	Container v1(5);
	for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		*it = Cval(i0);
	Container v2(v1);


	//	TEST
	{
		//	STL (the entire method)
		time_printer tp(msg, m_print_time);
		
		//cout << "The 3! possible permutations with 3 elements:\n";
		stl::sort(myints, myints + 3);
		stl::reverse(myints, myints + 3);

		/*	prev_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified with 
			a binary predicate.
		*/
		i0 = 0;
		do
		{
			TEST_CHECK(mycheck[i0][0] == myints[0]);
			TEST_CHECK(mycheck[i0][1] == myints[1]);
			TEST_CHECK(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while ( stl::prev_permutation(myints,myints+3) );

		/*
		  3 2 1
		  3 1 2
		  2 3 1
		  2 1 3
		  1 3 2
		  1 2 3
		*/

		while(stl::prev_permutation(v1.begin(), v1.end()) && 
			  stl::prev_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				TEST_CHECK(*it1 == *it2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

















