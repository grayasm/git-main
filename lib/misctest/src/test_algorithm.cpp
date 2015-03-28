/*
  Copyright (C) 2009 Mihai Vasilian

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



//this
#include "test_algorithm.hpp"

//c++ ...
#include <vector>
#include <time.h>
#include <limits.h>
#include <algorithm>


//CppUnit
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//libraries ...
#include "algorithm.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "stream.hpp"
#include "misctest_util.hpp"



//###########################BEGIN TEST CLASS ####################################
void test_algorithm::setUp()
{	
}

void test_algorithm::tearDown()
{	
}

//##########################BEGIN TEST SUITE######################################

//////////////////////////////////////////////////////////////////////////
//test begin
//Non-modifying sequence operations:
void test_algorithm::for_each()
{	
	misc::cout << "\n\n\tfor_each-----------------------------------------------";
	for_each<std::vector<int> >																		("\n\tstd::vector       ");
	for_each<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	for_each<misc::vector<int> >																	("\n\tmisc::vector      ");
	for_each<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	for_each<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	for_each<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	for_each<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::find()
{
	misc::cout << "\n\n\tfind---------------------------------------------------";
	find2<std::vector<int> >																	("\n\tstd::vector       ");
	find2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	find<misc::vector<int> >																	("\n\tmisc::vector      ");
	find<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::find_if()
{
	misc::cout << "\n\n\tfind_if------------------------------------------------";
	find_if2<std::vector<int> >																		("\n\tstd::vector       ");
	find_if2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	find_if<misc::vector<int> >																		("\n\tmisc::vector      ");
	find_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	find_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	find_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	find_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::find_end()
{
	misc::cout << "\n\n\tfind_end-----------------------------------------------";
	find_end2<std::vector<int> >																	("\n\tstd::vector      ");
	find_end2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>   ");
	find_end<misc::vector<int> >																	("\n\tmisc::vector      ");
	find_end<misc::vector<int, std::allocator<int> > >												("\n\tmisc::vector<A>   ");
	find_end<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	find_end<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	find_end<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");		
}

void test_algorithm::find_first_of()
{
	misc::cout << "\n\n\tfind_first_of------------------------------------------";
	find_first_of<std::vector<char> >																		("\n\tstd::vector       ");
	find_first_of<std::vector<char, misc::allocator<char> > >												("\n\tstd::vector<A>    ");
	find_first_of<misc::vector<char> >																		("\n\tmisc::vector      ");
	find_first_of<misc::vector<char, std::allocator<char> > >												("\n\tstd::vector       ");
	find_first_of<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	find_first_of<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	find_first_of<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");	
}

void test_algorithm::adjacent_find()
{
	misc::cout << "\n\n\tadjacent_find------------------------------------------";
	adjacent_find<std::vector<int> >																	("\n\tstd::vector       ");
	adjacent_find<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	adjacent_find<misc::vector<int> >																	("\n\tmisc::vector      ");
	adjacent_find<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	adjacent_find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	adjacent_find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	adjacent_find<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");	

}

void test_algorithm::count()
{
	misc::cout << "\n\n\tcount--------------------------------------------------";
	count<std::vector<int> >																	("\n\tstd::vector       ");
	count<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	count<misc::vector<int> >																	("\n\tmisc::vector      ");
	count<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	count<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	count<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	count<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::count_if()
{
	misc::cout << "\n\n\tcount_if-----------------------------------------------";
	count_if<std::vector<int> >																		("\n\tstd::vector       ");
	count_if<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	count_if<misc::vector<int> >																	("\n\tmisc::vector      ");
	count_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	count_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	count_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	count_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::mismatch()
{
	misc::cout << "\n\n\tmismatch-----------------------------------------------";
	mismatch<std::vector<int> >																		("\n\tstd::vector       ");
	mismatch<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	mismatch<misc::vector<int> >																	("\n\tmisc::vector      ");
	mismatch<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	mismatch<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	mismatch<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	mismatch<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::equal()
{
	misc::cout << "\n\n\tequal--------------------------------------------------";
	equal<std::vector<int> >																	("\n\tstd::vector       ");
	equal<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	equal<misc::vector<int> >																	("\n\tmisc::vector      ");
	equal<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	equal<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	equal<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	equal<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::search()
{
	misc::cout << "\n\n\tsearch-------------------------------------------------";
	search<std::vector<int> >																		("\n\tstd::vector       ");
	search<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	search2<misc::vector<int> >																		("\n\tmisc::vector      ");
	search2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::search_n()
{
	misc::cout << "\n\n\tsearch_n-----------------------------------------------";
	search_n<std::vector<int> >																	("\n\tstd::vector       ");
	search_n<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	search_n2<misc::vector<int> >																	("\n\tmisc::vector      ");
	search_n2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	search_n2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	search_n2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	search_n2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Modifying sequence operations:
void test_algorithm::copy()
{
	misc::cout << "\n\n\tcopy---------------------------------------------------";
	copy<std::vector<int> >																		("\n\tstd::vector       ");
	copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	copy<misc::vector<int> >																	("\n\tmisc::vector      ");
	copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::copy_backward()
{
	misc::cout << "\n\n\tcopy_backward------------------------------------------";
	copy_backward<std::vector<int> >																	("\n\tstd::vector       ");
	copy_backward<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	copy_backward<misc::vector<int> >																	("\n\tmisc::vector      ");
	copy_backward<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	copy_backward<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	copy_backward<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	copy_backward<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::swap()
{
	misc::cout << "\n\n\tswap---------------------------------------------------";
	swap<std::vector<int> >																		("\n\tstd::vector       ");
	swap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	swap<misc::vector<int> >																	("\n\tmisc::vector      ");
	swap<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::swap_ranges()
{
	misc::cout << "\n\n\tswap_ranges--------------------------------------------";
	swap_ranges<std::vector<int> >																		("\n\tstd::vector       ");
	swap_ranges<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	swap_ranges<misc::vector<int> >																		("\n\tmisc::vector      ");
	swap_ranges<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	swap_ranges<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	swap_ranges<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	swap_ranges<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::iter_swap()
{
	misc::cout << "\n\n\titer_swap----------------------------------------------";
	iter_swap<std::vector<int> >																	("\n\tstd::vector       ");
	iter_swap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	iter_swap<misc::vector<int> >																	("\n\tmisc::vector      ");
	iter_swap<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	iter_swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	iter_swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	iter_swap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::transform()
{
	misc::cout << "\n\n\ttransform----------------------------------------------";
	transform<std::vector<int> >																	("\n\tstd::vector       ");
	transform<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	transform<misc::vector<int> >																	("\n\tmisc::vector      ");
	transform<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	transform<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	transform<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	transform<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::replace()
{
	misc::cout << "\n\n\treplace------------------------------------------------";
	replace<std::vector<int> >																		("\n\tstd::vector       ");
	replace<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	replace<misc::vector<int> >																		("\n\tmisc::vector      ");
	replace<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	replace<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	replace<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	replace<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::replace_if()
{
	misc::cout << "\n\n\treplace_if---------------------------------------------";
	replace_if<std::vector<int> >																		("\n\tstd::vector       ");
	replace_if<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	replace_if<misc::vector<int> >																		("\n\tmisc::vector      ");
	replace_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	replace_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	replace_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	replace_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::replace_copy()
{
	misc::cout << "\n\n\treplace_copy-------------------------------------------";
	replace_copy<std::vector<int> >																		("\n\tstd::vector       ");
	replace_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	replace_copy<misc::vector<int> >																	("\n\tmisc::vector      ");
	replace_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	replace_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	replace_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	replace_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::replace_copy_if()
{
	misc::cout << "\n\n\treplace_copy_if----------------------------------------";
	replace_copy_if<std::vector<int> >																		("\n\tstd::vector       ");
	replace_copy_if<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	replace_copy_if<misc::vector<int> >																		("\n\tmisc::vector      ");
	replace_copy_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	replace_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	replace_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	replace_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::fill()
{
	misc::cout << "\n\n\tfill---------------------------------------------------";
	fill<std::vector<int> >																		("\n\tstd::vector       ");
	fill<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	fill<misc::vector<int> >																	("\n\tmisc::vector      ");
	fill<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	fill<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	fill<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	fill<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::fill_n()
{
	misc::cout << "\n\n\tfill_n-------------------------------------------------";
	fill_n<std::vector<int> >																		("\n\tstd::vector       ");
	fill_n<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	fill_n<misc::vector<int> >																		("\n\tmisc::vector      ");
	fill_n<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	fill_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	fill_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	fill_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::generate()
{
	misc::cout << "\n\n\tgenerate-----------------------------------------------";
	generate<std::vector<int> >																		("\n\tstd::vector       ");
	generate<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	generate<misc::vector<int> >																	("\n\tmisc::vector      ");
	generate<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	generate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	generate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	generate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::generate_n()
{
	misc::cout << "\n\n\tgenerate_n---------------------------------------------";
	generate_n<std::vector<int> >																		("\n\tstd::vector       ");
	generate_n<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	generate_n<misc::vector<int> >																		("\n\tmisc::vector      ");
	generate_n<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	generate_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	generate_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	generate_n<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::remove()
{
	misc::cout << "\n\n\tremove-------------------------------------------------";
	remove<std::vector<int> >																		("\n\tstd::vector       ");
	remove<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	remove<misc::vector<int> >																		("\n\tmisc::vector      ");
	remove<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	remove<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	remove<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	remove<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::remove_if()
{
	misc::cout << "\n\n\tremove_if----------------------------------------------";
	remove_if2<std::vector<int> >																	("\n\tstd::vector       ");
	remove_if2<std::vector<int, misc::allocator<int> > >											("\n\tstd::vector<A>    ");
	remove_if<misc::vector<int> >																	("\n\tmisc::vector      ");
	remove_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	remove_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	remove_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	remove_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::remove_copy()
{
	misc::cout << "\n\n\tremove_copy--------------------------------------------";
	remove_copy<std::vector<int> >																		("\n\tstd::vector       ");
	remove_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	remove_copy<misc::vector<int> >																		("\n\tmisc::vector      ");
	remove_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	remove_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	remove_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	remove_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::remove_copy_if()
{
	misc::cout << "\n\n\tremove_copy_if-----------------------------------------";
	remove_copy_if<std::vector<int> >																		("\n\tstd::vector       ");
	remove_copy_if<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	remove_copy_if<misc::vector<int> >																		("\n\tmisc::vector      ");
	remove_copy_if<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	remove_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	remove_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	remove_copy_if<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::unique()
{
	misc::cout << "\n\n\tunique-------------------------------------------------";
	unique<std::vector<int> >																		("\n\tstd::vector       ");
	unique<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	unique<misc::vector<int> >																		("\n\tmisc::vector      ");
	unique<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	unique<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	unique<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	unique<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::unique_copy()
{
	misc::cout << "\n\n\tunique_copy--------------------------------------------";
	unique_copy<std::vector<int> >																		("\n\tstd::vector       ");
	unique_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	unique_copy<misc::vector<int> >																		("\n\tmisc::vector      ");
	unique_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	unique_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	unique_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	unique_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::reverse()
{
	misc::cout << "\n\n\treverse------------------------------------------------";
	reverse<std::vector<int> >																		("\n\tstd::vector       ");
	reverse<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	reverse<misc::vector<int> >																		("\n\tmisc::vector      ");
	reverse<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	reverse<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	reverse<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	reverse<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::reverse_copy()
{
	misc::cout << "\n\n\treverse_copy-------------------------------------------";
	reverse_copy<std::vector<int> >																		("\n\tstd::vector       ");
	reverse_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	reverse_copy<misc::vector<int> >																	("\n\tmisc::vector      ");
	reverse_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	reverse_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	reverse_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	reverse_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::rotate()
{
	misc::cout << "\n\n\trotate-------------------------------------------------";
	rotate<std::vector<int> >																		("\n\tstd::vector       ");
	rotate<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	rotate<misc::vector<int> >																		("\n\tmisc::vector      ");
	rotate<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	rotate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	rotate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	rotate<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::rotate_copy()
{
	misc::cout << "\n\n\trotate_copy--------------------------------------------";
	rotate_copy<std::vector<int> >																		("\n\tstd::vector       ");
	rotate_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	rotate_copy<misc::vector<int> >																		("\n\tmisc::vector      ");
	rotate_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	rotate_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	rotate_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	rotate_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::random_shuffle()
{
	misc::cout << "\n\n\trandom_shuffle-----------------------------------------";
	random_shuffle<std::vector<int> >																		("\n\tstd::vector       ");
	random_shuffle<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	random_shuffle<misc::vector<int> >																		("\n\tmisc::vector      ");
	random_shuffle<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	random_shuffle<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	random_shuffle<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	random_shuffle<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::partition()
{
	misc::cout << "\n\n\tpartition----------------------------------------------";
	partition2<std::vector<int> >																	("\n\tstd::vector       ");
	partition2<std::vector<int, misc::allocator<int> > >											("\n\tstd::vector<A>    ");
	partition<misc::vector<int> >																	("\n\tmisc::vector      ");
	partition<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	partition<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	partition<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	partition<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::stable_partition()
{
	misc::cout << "\n\n\tstable_partition---------------------------------------";	
	stable_partition<std::vector<int> >																		("\n\tstd::vector       ");
	stable_partition<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	stable_partition2<misc::vector<int> >																	("\n\tmisc::vector      ");
	stable_partition2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	stable_partition2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	stable_partition2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	stable_partition2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Sorting:
void test_algorithm::sort()
{
	misc::cout << "\n\n\tsort---------------------------------------------------";
	sort<std::vector<int> >																		("\n\tstd::vector       ");
	sort<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	sort<misc::vector<int> >																	("\n\tmisc::vector      ");
	sort<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::stable_sort()
{
	misc::cout << "\n\n\tstable_sort--------------------------------------------";	
	stable_sort<std::vector<double> >																		("\n\tstd::vector       ");
	stable_sort2<misc::vector<double> >																		("\n\tmisc::vector      ");
	stable_sort2<misc::vector<double, std::allocator<double> > >												("\n\tstd::vector       ");
	stable_sort2<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	stable_sort2<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	stable_sort2<misc::vector<double, misc::allocator<double>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::partial_sort()
{
	misc::cout << "\n\n\tpartial_sort-------------------------------------------";
	partial_sort<std::vector<int> >																		("\n\tstd::vector       ");
	partial_sort<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	partial_sort<misc::vector<int> >																	("\n\tmisc::vector      ");
	partial_sort<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	partial_sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	partial_sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	partial_sort<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::partial_sort_copy()
{
	misc::cout << "\n\n\tpartial_sort_copy--------------------------------------";
	partial_sort_copy<std::vector<int> >																	("\n\tstd::vector       ");
	partial_sort_copy<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	partial_sort_copy<misc::vector<int> >																	("\n\tmisc::vector      ");
	partial_sort_copy<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	partial_sort_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	partial_sort_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	partial_sort_copy<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::nth_element()
{
	misc::cout << "\n\n\tnth_element--------------------------------------------";
	nth_element<std::vector<int> >																		("\n\tstd::vector       ");
	nth_element<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	nth_element<misc::vector<int> >																		("\n\tmisc::vector      ");
	nth_element<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	nth_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	nth_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	nth_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Binary search (operating on sorted ranges):
void test_algorithm::lower_bound()
{
	misc::cout << "\n\n\tlower_bound--------------------------------------------";
	lower_bound2<std::vector<int> >																		("\n\tstd::vector       ");
	lower_bound2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	lower_bound<misc::vector<int> >																		("\n\tmisc::vector      ");
	lower_bound<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	lower_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	lower_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	lower_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::upper_bound()
{
	misc::cout << "\n\n\tupper_bound--------------------------------------------";
	upper_bound<std::vector<int> >																		("\n\tstd::vector       ");
	upper_bound<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	upper_bound<misc::vector<int> >																		("\n\tmisc::vector      ");
	upper_bound<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	upper_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	upper_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	upper_bound<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::equal_range()
{
	misc::cout << "\n\n\tequal_range--------------------------------------------";	
	equal_range2<std::vector<int> >																		("\n\tstd::vector       ");
	equal_range<misc::vector<int> >																		("\n\tmisc::vector      ");
	equal_range<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	equal_range<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	equal_range<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	equal_range<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::binary_search()
{
	misc::cout << "\n\n\tbinary_search------------------------------------------";
	binary_search<std::vector<int> >																	("\n\tstd::vector       ");
	binary_search<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	binary_search2<misc::vector<int> >																	("\n\tmisc::vector      ");
	binary_search2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	binary_search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	binary_search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	binary_search2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Merge (operating on sorted ranges):
void test_algorithm::merge()
{
	misc::cout << "\n\n\tmerge--------------------------------------------------";
	merge<std::vector<int> >																	("\n\tstd::vector       ");
	merge<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	merge2<misc::vector<int> >																	("\n\tmisc::vector      ");
	merge2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::inplace_merge()
{
	misc::cout << "\n\n\tinplace_merge------------------------------------------";
	inplace_merge<std::vector<int> >																	("\n\tstd::vector       ");
	inplace_merge<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	inplace_merge2<misc::vector<int> >																	("\n\tmisc::vector      ");
	inplace_merge2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	inplace_merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	inplace_merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	inplace_merge2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::includes()
{
	misc::cout << "\n\n\tincludes-----------------------------------------------";
	includes<std::vector<int> >																		("\n\tstd::vector       ");
	includes<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	includes2<misc::vector<int> >																	("\n\tmisc::vector      ");
	includes2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	includes2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	includes2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	includes2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::set_union()
{
	misc::cout << "\n\n\tset_union----------------------------------------------";
	set_union<std::vector<int> >																	("\n\tstd::vector       ");
	set_union<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	set_union2<misc::vector<int> >																	("\n\tmisc::vector      ");
	set_union2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	set_union2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	set_union2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	set_union2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::set_intersection()
{
	misc::cout << "\n\n\tset_intersection---------------------------------------";
	set_intersection<std::vector<int> >																		("\n\tstd::vector       ");
	set_intersection<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	set_intersection2<misc::vector<int> >																	("\n\tmisc::vector      ");
	set_intersection2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	set_intersection2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	set_intersection2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	set_intersection2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::set_difference()
{
	misc::cout << "\n\n\tset_difference-----------------------------------------";
	set_difference<std::vector<int> >																		("\n\tstd::vector       ");
	set_difference<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	set_difference<misc::vector<int> >																		("\n\tmisc::vector      ");
	set_difference<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	set_difference<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	set_difference<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	set_difference<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::set_symmetric_difference()
{
	misc::cout << "\n\n\tset_symmetric_difference-------------------------------";
	set_symmetric_difference<std::vector<int> >																		("\n\tstd::vector       ");
	set_symmetric_difference<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	set_symmetric_difference2<misc::vector<int> >																	("\n\tmisc::vector      ");
	set_symmetric_difference2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	set_symmetric_difference2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	set_symmetric_difference2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	set_symmetric_difference2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Heap:
void test_algorithm::push_heap()
{
	misc::cout << "\n\n\tpush_heap----------------------------------------------";
	push_heap<std::vector<int> >																	("\n\tstd::vector       ");
	push_heap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	push_heap2<misc::vector<int> >																	("\n\tmisc::vector      ");
	push_heap2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	push_heap2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	push_heap2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	push_heap2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::pop_heap()
{
	misc::cout << "\n\n\tpop_heap-----------------------------------------------";
	pop_heap<std::vector<int> >																		("\n\tstd::vector       ");
	pop_heap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	pop_heap<misc::vector<int> >																	("\n\tmisc::vector      ");
	pop_heap<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	pop_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	pop_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	pop_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::make_heap()
{
	misc::cout << "\n\n\tmake_heap----------------------------------------------";
	make_heap<std::vector<int> >																	("\n\tstd::vector       ");
	make_heap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	make_heap<misc::vector<int> >																	("\n\tmisc::vector      ");
	make_heap<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	make_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	make_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	make_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::sort_heap()
{
	misc::cout << "\n\n\tsort_heap----------------------------------------------";
	sort_heap<std::vector<int> >																	("\n\tstd::vector       ");
	sort_heap<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	sort_heap<misc::vector<int> >																	("\n\tmisc::vector      ");
	sort_heap<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	sort_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	sort_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	sort_heap<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//Min/max:
void test_algorithm::min2()
{
	misc::cout << "\n\n\tmin----------------------------------------------------";
	min2<std::vector<int> >																		("\n\tstd::vector       ");
	min2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	min2<misc::vector<int> >																	("\n\tmisc::vector      ");
	min2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	min2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	min2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	min2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::max2()
{
	misc::cout << "\n\n\tmax----------------------------------------------------";
	max2<std::vector<int> >																		("\n\tstd::vector       ");
	max2<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	max2<misc::vector<int> >																	("\n\tmisc::vector      ");
	max2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	max2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	max2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	max2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::min_element()
{
	misc::cout << "\n\n\tmin_element--------------------------------------------";
	min_element<std::vector<int> >																		("\n\tstd::vector       ");
	min_element<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	min_element<misc::vector<int> >																		("\n\tmisc::vector      ");
	min_element<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	min_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	min_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	min_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::max_element()
{
	misc::cout << "\n\n\tmax_element--------------------------------------------";
	max_element<std::vector<int> >																		("\n\tstd::vector       ");
	max_element<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	max_element<misc::vector<int> >																		("\n\tmisc::vector      ");
	max_element<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	max_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >				("\n\tmisc::vector<POD> ");
	max_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	max_element<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::lexicographical_compare()
{
	misc::cout << "\n\n\tlexicographical_compare--------------------------------";
	lexicographical_compare<std::vector<char> >																		("\n\tstd::vector       ");
	lexicographical_compare<std::vector<char, misc::allocator<char> > >												("\n\tstd::vector<A>    ");
	lexicographical_compare<misc::vector<char> >																	("\n\tmisc::vector      ");
	lexicographical_compare<misc::vector<char, std::allocator<char> > >												("\n\tstd::vector       ");
	lexicographical_compare<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	lexicographical_compare<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	lexicographical_compare<misc::vector<char, misc::allocator<char>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::next_permutation()
{
	misc::cout << "\n\n\tnext_permutation---------------------------------------";
	next_permutation<std::vector<int> >																		("\n\tstd::vector       ");
	next_permutation<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	next_permutation2<misc::vector<int> >																	("\n\tmisc::vector      ");
	next_permutation2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	next_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	next_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	next_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

void test_algorithm::prev_permutation()
{
	misc::cout << "\n\n\tprev_permutation---------------------------------------";
	prev_permutation<std::vector<int> >																		("\n\tstd::vector       ");
	prev_permutation<std::vector<int, misc::allocator<int> > >												("\n\tstd::vector<A>    ");
	prev_permutation2<misc::vector<int> >																	("\n\tmisc::vector      ");
	prev_permutation2<misc::vector<int, std::allocator<int> > >												("\n\tstd::vector       ");
	prev_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE> >			("\n\tmisc::vector<POD> ");
	prev_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_POD_TYPE | misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::ve<POD|ITD> ");
	prev_permutation2<misc::vector<int, misc::allocator<int>, misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING> >	("\n\tmisc::vector<ITD> ");
}

//test end

//////////////////////////////////////////////////////////////////////////
//template version of test function

//Non-modifying sequence operations:
int myfunction_for_each_integer = 10;
void myfunction_for_each (int i)
{
	CPPUNIT_ASSERT(i == myfunction_for_each_integer);
	myfunction_for_each_integer += 10;
}

struct myclass_for_each
{
	myclass_for_each():m_count(10){}
	void operator() (int i)
	{
		CPPUNIT_ASSERT(i == m_count);
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
		//	MISC
		time_printer tm(msg, m_print_time);

		// for_each(InputIterator first, InputIterator last, Function f)
		myfunction_for_each_integer = 10;
		misc::for_each<It, Function>(myvector.begin(), myvector.end(), myfunction_for_each);

		myclass_for_each myobject_for_each;
		misc::for_each (myvector.begin(), myvector.end(), myobject_for_each);


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

		// MISC
		// pointer to array element:
		p = misc::find(mytable, mytable + m_container_size, m_container_size - 2);
		++p;
		CPPUNIT_ASSERT(*p == (m_container_size - 1));


		It it;
		// iterator to vector element:
		it = misc::find(myvector.begin(), myvector.end(), Cval(m_container_size - 2));
		it++;

		CPPUNIT_ASSERT(*it == (m_container_size - 1));
		
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
		CPPUNIT_ASSERT(*p == (m_container_size - 1));


		It it;
		// iterator to vector element:
		it = std::find(myvector.begin(), myvector.end(), Cval(m_container_size - 2));
		it++;

		CPPUNIT_ASSERT(*it == (m_container_size - 1));
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

		//MISC
		// technical
		it = misc::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		CPPUNIT_ASSERT( *it == 25 );

		v1.erase(it);
		it = misc::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		CPPUNIT_ASSERT( *it == 55 );

		v1.erase(it);
		it = misc::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		CPPUNIT_ASSERT( it == v1.end() );

		// performance
		Struct_find_if<Cval> sfif1(m_container_size - 2);
		it = misc::find_if(v2.begin(), v2.end(), sfif1);

		CPPUNIT_ASSERT( *(++it) == (m_container_size - 1 ));
		
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
		CPPUNIT_ASSERT( *it == 25 );

		v1.erase(it);
		it = std::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		CPPUNIT_ASSERT( *it == 55 );

		v1.erase(it);
		it = std::find_if(v1.begin(), v1.end(), IsOdd_find_if);
		CPPUNIT_ASSERT( it == v1.end() );

		// performance
		Struct_find_if<Cval> sfif1(m_container_size - 2);
		it = std::find_if(v2.begin(), v2.end(), sfif1);

		CPPUNIT_ASSERT( *(++it) == (m_container_size - 1 ));
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


		//MISC
		It it;
		Cval mycheck1[] = {1,2,3};

		/*	Looks in a range for the last subsequence that is identical 
			to a specified sequence or that is equivalent in a sense specified 
			by a binary predicate.

			using default comparison:
		*/
		it = misc::find_end(v1.begin(), v1.end(), mycheck1, mycheck1 + 3);		
		//Match found at position 5
		CPPUNIT_ASSERT( (it-v1.begin()) == 5 );


		Cval mycheck2[] = {4,5,1};
		// using predicate comparison:
		it = misc::find_end(v1.begin(), v1.end(), mycheck2, mycheck2 + 3, myfunction_find_end);
		//Match last found at position 3
		CPPUNIT_ASSERT( (it-v1.begin()) == 3 );



		Cval mycheck3[] = { m_container_size - 3, m_container_size - 2, m_container_size - 1 };
		//v2: 0,1,2,3,4,5
		//ck: 3,4,5
		it = misc::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);

		it = misc::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3, myfunction_find_end);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);
		
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


		//MISC
		It it;
		Cval mycheck1[] = {1,2,3};

		/*	Looks in a range for the last subsequence that is identical 
			to a specified sequence or that is equivalent in a sense specified 
			by a binary predicate.

			using default comparison:
		*/
		
		it = std::find_end(v1.begin(), v1.end(), mycheck1, mycheck1 + 3);		
		//Match found at position 5
		CPPUNIT_ASSERT( (it-v1.begin()) == 5 );


		Cval mycheck2[] = {4,5,1};
		// using predicate comparison:
		it = std::find_end(v1.begin(), v1.end(), mycheck2, mycheck2 + 3, myfunction_find_end);
		//Match last found at position 3
		CPPUNIT_ASSERT( (it-v1.begin()) == 3 );



		Cval mycheck3[] = { m_container_size - 3, m_container_size - 2, m_container_size - 1 };
		//v2: 0,1,2,3,4,5
		//ck: 3,4,5
		it = std::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);

		it = std::find_end(v2.begin(), v2.end(), mycheck3, mycheck3 + 3, myfunction_find_end);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);		
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

		//MISC
		// using default comparison:
		it = misc::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3);
		CPPUNIT_ASSERT(*it == 'A');

		// using predicate comparison:
		it = misc::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		CPPUNIT_ASSERT(*it == 'a');

		it = misc::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3);
		CPPUNIT_ASSERT(*it == 'A');

		it = misc::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		CPPUNIT_ASSERT(*it == 'a');

#if !defined(DEBUG)
		//STD
		it = std::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3);
		CPPUNIT_ASSERT(*it == 'A');

		it = std::find_first_of (v1.begin(), v1.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		CPPUNIT_ASSERT(*it == 'a');

		it = std::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3);
		CPPUNIT_ASSERT(*it == 'A');

		it = std::find_first_of (v2.begin(), v2.end(), mycheck, mycheck+3, comp_case_insensitive_find_first_of);
		CPPUNIT_ASSERT(*it == 'a');
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

		// MISC
		//Searches for two adjacent elements that are either equal or satisfy a specified condition.
		// using default comparison:
		it = misc::adjacent_find (v1.begin(), v1.end());
		CPPUNIT_ASSERT(*it == 30);
		
		//"the first consecutive repeated elements are: 30"
		//using predicate comparison:
		it = misc::adjacent_find (++it, v1.end(), myfunction_adjacent_find);
		CPPUNIT_ASSERT( *it == 10 );		
		//"the second consecutive repeated elements are: 10"

#if !defined(DEBUG)  //std::_Debug_range2
		// STD
		it = std::adjacent_find (v1.begin(), v1.end());
		CPPUNIT_ASSERT(*it == 30);

		it = std::adjacent_find (++it, v1.end(), myfunction_adjacent_find);
		CPPUNIT_ASSERT( *it == 10 );
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

		// MISC
		Diff mycount = 0;
		// counting elements in array:		
		mycount = misc::count (myints, myints+8, 10);

		//cout << "10 appears " << mycount << " times.\n";
		CPPUNIT_ASSERT(mycount == 3);

		// counting elements in container:
		mycount = misc::count (v1.begin(), v1.end(), 20);
		//cout << "20 appears " << mycount  << " times.\n";
		CPPUNIT_ASSERT(mycount == 3);

		mycount = misc::count (v2.begin(), v2.end(), m_container_size -1);
		CPPUNIT_ASSERT(mycount == 1);

#if !defined(DEBUG)
		// STD
		mycount = std::count (myints, myints+8, 10);
		CPPUNIT_ASSERT(mycount == 3);

		mycount = std::count (v1.begin(), v1.end(), 20);
		//cout << "20 appears " << mycount  << " times.\n";
		CPPUNIT_ASSERT(mycount == 3);

		mycount = std::count (v2.begin(), v2.end(), m_container_size -1);
		CPPUNIT_ASSERT(mycount == 1);
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

		// MISC
		mycount = misc::count_if (v1.begin(), v1.end(), IsOdd_count_if);
		//cout << "v1 contains " << mycount  << " odd values.\n";
		CPPUNIT_ASSERT(mycount == 5);

		mycount = misc::count_if (v2.begin(), v2.end(), IsOdd_count_if);
		CPPUNIT_ASSERT(mycount == m_container_size/2);

#if !defined(DEBUG)
		// STD
		mycount = std::count_if (v1.begin(), v1.end(), IsOdd_count_if);
		//cout << "v1 contains " << mycount  << " odd values.\n";
		CPPUNIT_ASSERT(mycount == 5);

		mycount = std::count_if (v2.begin(), v2.end(), IsOdd_count_if);
		CPPUNIT_ASSERT(mycount == m_container_size/2);
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

	misc::pair<typename Container::iterator, Cval*>		pair1;
	misc::pair<typename Container::iterator, typename Container::iterator> pair2;
	std::pair<typename Container::iterator, Cval*>		pair3;
	std::pair<typename Container::iterator, typename Container::iterator> pair4;





	// TEST
	{
		time_printer tp(msg, m_print_time);

		// MISC
		// Compares two ranges element by element either for equality or
		// equivalent in a sense specified by a binary predicate and locates
		// the first position where a difference occurs.
		// Condition: first container.size() <= second container.size();

		// using default comparison:
		pair1 = misc::mismatch (v1.begin(), v1.end(), myints);
		//cout << "First mismatching elements: " << *pair1.first;
		CPPUNIT_ASSERT(*pair1.first == 30);

		//cout << " and " << *pair1.second << endl;;
		CPPUNIT_ASSERT(*pair1.second == 80);

		pair1.first++;
		pair1.second++;

		// using predicate comparison:
		pair1 = misc::mismatch (pair1.first, v1.end(), pair1.second, mypredicate_mismatch);
		//cout << "Second mismatching elements: " << *pair1.first;
		CPPUNIT_ASSERT(*pair1.first == 40);
		//cout << " and " << *pair1.second << endl;;
		CPPUNIT_ASSERT(*pair1.second == 320);


		pair1 = misc::mismatch (v2.begin(), v2.end(), myints);
		CPPUNIT_ASSERT(*pair1.first == 30);
		CPPUNIT_ASSERT(*pair1.second == 80);

		// condition: first container.size() < second container.size()
		pair2 = misc::mismatch (v3.begin(), v3.end(), v2.begin());
		CPPUNIT_ASSERT(pair2.first == v3.end());
		CPPUNIT_ASSERT(*pair2.second == (m_container_size/5) * 10);

#if !defined(DEBUG)
		// STD
		// the only test that compiles with _WIN32
		pair4 = std::mismatch (v3.begin(), v3.end(), v2.begin());
		CPPUNIT_ASSERT(pair4.first == v3.end());
		CPPUNIT_ASSERT(*pair4.second == (m_container_size/5) * 10);
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

		// MISC
		// using default comparison:
		bool res = misc::equal(v1.begin(), v1.end(), myints);
		CPPUNIT_ASSERT(res);

		v1[3]=81;                            // v1: 20 40 60 81 100
		// using predicate comparison:
		res = misc::equal(v1.begin(), v1.end(), myints, mypredicate_equal);
		CPPUNIT_ASSERT( !res );

		res = misc::equal(v2.begin(), v2.end(), v3.begin());
		CPPUNIT_ASSERT( res );

		res = misc::equal(v2.begin(), v2.end(), v3.begin(), mypredicate_equal);
		CPPUNIT_ASSERT(res);

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

		// MISC
		// using default comparison:
		bool res = std::equal(v1.begin(), v1.end(), myints);
		CPPUNIT_ASSERT(res);

		v1[3]=81;                            // v1: 20 40 60 81 100
		// using predicate comparison:
		res = std::equal(v1.begin(), v1.end(), myints, mypredicate_equal);
		CPPUNIT_ASSERT( !res );

		res = std::equal(v2.begin(), v2.end(), v3.begin());
		CPPUNIT_ASSERT( res );

		res = std::equal(v2.begin(), v2.end(), v3.begin(), mypredicate_equal);
		CPPUNIT_ASSERT(res);
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
		CPPUNIT_ASSERT( (int)(it - v1.begin()) == 3 );
		// using predicate comparison:
		it = std::search (v1.begin(), v1.end(), match2, match2+3, mypredicate_search);
		CPPUNIT_ASSERT( it == v1.end() );

		it = std::search (v2.begin(), v2.end(), v3.begin(), v3.end());	
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size / 2);

		it = std::search (v2.begin(), v2.end(), match4, match4+3, mypredicate_search);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);
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

		// MISC
		// using default comparison:
		it = misc::search (v1.begin(), v1.end(), match1, match1+4);	
		CPPUNIT_ASSERT( (int)(it - v1.begin()) == 3 );
		// using predicate comparison:
		it = misc::search (v1.begin(), v1.end(), match2, match2+3, mypredicate_search);
		CPPUNIT_ASSERT( it == v1.end() );

		it = misc::search (v2.begin(), v2.end(), v3.begin(), v3.end());	
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size / 2);

		it = misc::search (v2.begin(), v2.end(), match4, match4+3, mypredicate_search);
		CPPUNIT_ASSERT( (it - v2.begin()) == m_container_size - 3);
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
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 2);

		// using predicate comparison:
		it = std::search_n (v1.begin(), v1.end(), 2, 10, mypredicate_search_n);
		//cout << "two 10s found at position 5" << int(it-v1.begin()) << endl;
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 5);
		//Two 30s found at position 2
		//Two 10s found at position 5

		it = std::search_n (v2.begin(), v2.end(), 2, m_container_size - 2);		
		CPPUNIT_ASSERT((int)(it-v2.begin()) == m_container_size - 2);

		it = std::search_n (v2.begin(), v2.end(), 2, m_container_size - 2, mypredicate_search_n);
		CPPUNIT_ASSERT((int)(it-v2.begin()) == m_container_size - 2);
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


		// MISC
		/*	search_n(begin, end, how_many_consecutive, having_value)
			Searches for the first subsequence in a range that of a 
			specified number of elements having a particular value or 
			a relation to that value as specified by a binary predicate.
		*/
		// using default comparison:
		it = misc::search_n (v1.begin(), v1.end(), 2, 30);
		//cout << "two 30s found at position 2" << int(it-v1.begin()) << endl;
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 2);

		// using predicate comparison:
		it = misc::search_n (v1.begin(), v1.end(), 2, 10, mypredicate_search_n);
		//cout << "two 10s found at position 5" << int(it-v1.begin()) << endl;
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 5);
		//Two 30s found at position 2
		//Two 10s found at position 5

		it = misc::search_n (v2.begin(), v2.end(), 2, m_container_size - 2);	
		CPPUNIT_ASSERT((int)(it-v2.begin()) == m_container_size - 2);

		it = misc::search_n (v2.begin(), v2.end(), 2, m_container_size - 2, mypredicate_search_n);
		CPPUNIT_ASSERT((int)(it-v2.begin()) == m_container_size - 2);
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


		//	MISC
		// allocate space for 7 elements
		v1.resize(7);
		/*	Assigns the values of elements from a source range to a 
			destination range, iterating through the source sequence of 
			elements and assigning them new positions in a forward direction.
		*/
		misc::copy ( myints, myints+7, v1.begin() );

		//cout << "v1 contains:";
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(myints[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//myvector contains: 10 20 30 40 50 60 70

		misc::copy (v2.begin(), v2.end(), v3.begin());
		CPPUNIT_ASSERT(v3.size() == v2.size());
		for(size_t i = 0; i < v3.size(); ++i)
		{
			CPPUNIT_ASSERT((int)v3[i] == i);
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
			CPPUNIT_ASSERT(myints[it-v4.begin()] == *it);
			//cout << " " << *it;
		}
		//myvector contains: 10 20 30 40 50 60 70

		std::copy (v2.begin(), v2.end(), v5.begin());
		CPPUNIT_ASSERT(v5.size() == v2.size());
		for(size_t i = 0; i < v5.size(); ++i)
		{
			CPPUNIT_ASSERT((int)v5[i] == i);
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


		//	MISC
		/*	Assigns the values of elements from a source range to a 
			destination range, iterating through the source sequence of 
			elements and assigning them new positions in a backward direction.
		*/
		misc::copy_backward (v1.begin(), v1.begin()+5, v1.end());
				
		//cout << "v1 contains:";
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(myints[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//v1 contains: 10 20 30 10 20 30 40 50

		Container vv2(v2);
		vv2.resize(vv2.size()+m_container_size/2);		
		misc::copy_backward(vv2.begin(), vv2.begin() + m_container_size/2, vv2.end());
		it = vv2.begin();
		for(size_t i=0; i < m_container_size; ++i, ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(i));
		}
		for(size_t i=0; i < m_container_size/2; ++i, ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(i));
		}

#if !defined(DEBUG)		//std::_Debug_range2 debug iterator _WIN32
		//	STD		
		Container vv3(v2);
		vv3.resize(vv3.size()+m_container_size/2);		
		std::copy_backward(vv3.begin(), vv3.begin() + m_container_size/2, vv3.end());
		it = vv3.begin();
		for(size_t i=0; i < m_container_size; ++i, ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(i));
		}
		for(size_t i=0; i < m_container_size/2; ++i, ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(i));
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

		//	MISC		
		misc::swap<Cval>(x,y);
		CPPUNIT_ASSERT(x == Cval(20));
		CPPUNIT_ASSERT(y == Cval(10));
		
		misc::swap(v1,v2);		
		for (It it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(20));
		}

		for (It it=v2.begin(); it!=v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(10));
		}

		misc::swap (v3, v4);
		for(It it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(1));
		}
		for(It it = v4.begin(); it != v4.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(0));
		}

		//	STD
		std::swap(x,y);
		CPPUNIT_ASSERT(x == Cval(10));
		CPPUNIT_ASSERT(y == Cval(20));
		
		std::swap(v1,v2);		
		for (It it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(10));
		}
		for (It it=v2.begin(); it!=v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(20));
		}

		std::swap (v3, v4);
		for(It it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(0));
		}
		for(It it = v4.begin(); it != v4.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(1));
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

		//	MISC
		misc::swap_ranges(v1.begin()+1, v1.end()-1, v2.begin());

		// print out results of swap:
		// v1 contains: 10 33 33 33 10		
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(myints1[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
				
		// v2 contains: 10 10 10 33 33
		for (it=v2.begin(); it!=v2.end(); ++it)
		{
			CPPUNIT_ASSERT(myints2[it-v2.begin()] == *it);
			//cout << " " << *it;
		}

		misc::swap_ranges(v3.begin()+1, v3.end()-1, v4.begin());
		for(it = v3.begin(); it != v3.end(); ++it)
		{
			if(it == v3.begin()) CPPUNIT_ASSERT(*it == 0);
			else if(it == v3.end()-1) CPPUNIT_ASSERT(*it == 0);
			else CPPUNIT_ASSERT(*it == 1);
		}


#if !defined(DEBUG)
		//	STD
		std::swap_ranges(v2.begin(), v2.begin()+3, v1.begin()+1);
		for(it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == 10);
		}
		for(it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == 33);
		}

		std::swap_ranges(v3.begin()+1, v3.end()-1, v4.begin());
		for(it = v4.begin(); it != v4.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == 1);
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

		//	MISC
		misc::iter_swap(myints, v1.begin());      
		// myints: [99] 20  30  40  50
		//     v1: [10] 99  99  99
		misc::iter_swap(myints + 3, v1.begin() + 2);  
		// myints:  99  20  30 [99]
		//     v1:  10  99 [40] 99		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		It it2 = v2.begin();
		It it3 = v3.begin();
		for (; it2 != v2.end(); ++it2, ++it3)
		{
			It it_2 = it2;
			It it_3 = it3;
			misc::iter_swap (it_2, it_3);
		}
		
		for (It it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(1));
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
			CPPUNIT_ASSERT(*it == Cval(0));
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

		//	MISC	
		/*	Applies a specified function object to each element in 
			a source range or to a pair of elements from two source ranges 
			and copies the return values of the function object into 
			a destination range.
		*/
		misc::transform (v1.begin(), v1.end(), v2.begin(), op_increase_transform);
		// v2: 11 21 31 41 51

		misc::transform (v1.begin(), v1.end(), v2.begin(), v1.begin(), op_sum_transform);
		//  v1: 21 41 61 81 101		
		int mycheck[]={21, 41, 61, 81, 101};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}		

		misc::transform (v3.begin(), v3.end(), v3.begin(), op_decrease_transform);//v3:-2
		misc::transform (v3.begin(), v3.end(), v4.begin(), v3.begin(), op_sub_transform);//v3:-3
		for (It it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(-3));
		}


#if !defined(DEBUG)
		//	STD
		std::transform (v1.begin(), v1.end(), v2.begin(), v1.begin(), op_sub_transform);
		std::transform (v1.begin(), v1.end(), v2.begin(), op_decrease_transform);

		size_t stdck = 10;
		for (It it = v1.begin(); it != v1.end(); ++it, stdck += 10)
		{
			CPPUNIT_ASSERT(*it == stdck);			
		}

		std::transform (v3.begin(), v3.end(), v3.begin(), op_increase_transform);//v3:-2
		std::transform (v3.begin(), v3.end(), v4.begin(), v3.begin(), op_sum_transform);//v3:-1
		for (It it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT(*it == Cval(-1));
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
		
		//	MISC
		misc::replace (v1.begin(), v1.end(), 20, 99);
		// v1: 10 99 30 30 99 10 10 99				
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		misc::replace (v2.begin(), v2.end(), 1, 2);
		size_t i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
		{
			if(i2%2)
				CPPUNIT_ASSERT(*it == Cval(2));
			else
				CPPUNIT_ASSERT(*it == Cval(0));
		}

#if !defined(DEBUG)
		//	STD
		std::replace (v1.begin(), v1.end(), 99, 20);
		// v1: 10 20 30 30 20 10 10 20
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(myints[it-v1.begin()] == *it);			
		}

		misc::replace (v2.begin(), v2.end(), 2, 3);
		size_t i3 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i3)
		{
			if(i3%2)
				CPPUNIT_ASSERT(*it == Cval(3));
			else
				CPPUNIT_ASSERT(*it == Cval(0));
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
		
		//	MISC		
		/*	Examines each element in a range and replaces it 
			if it satisfies a specified predicate.
		*/
		misc::replace_if (v1.begin(), v1.end(), IsOdd_replace_if, 0); 
		// v1: 0 2 0 4 0 6 0 8 0

		Cval mycheck[]={0, 2, 0, 4, 0, 6, 0, 8, 0};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		misc::replace_if (v2.begin(), v2.end(), IsOdd_replace_if, -5);
		size_t i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
			if( IsOdd_replace_if((int) i2))
				CPPUNIT_ASSERT(*it == Cval(-5));
			else
				CPPUNIT_ASSERT(*it == Cval(i2));		
		
#if !defined(DEBUG)
		//	STD
		std::replace_if (v1.begin(), v1.end(), IsNull_replace_if, -1); 
		// v1: -1 2 -1 4 -1 6 -1 8 -1

		Cval mycheck2[]={-1, 2, -1, 4, -1, 6, -1, 8, -1};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck2[it-v1.begin()] == *it);			
		}

		misc::replace_if (v2.begin(), v2.end(), IsOdd_replace_if, -1);
		i2 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i2)
			if( IsOdd_replace_if((int) i2))
				CPPUNIT_ASSERT(*it == Cval(-1));
			else
				CPPUNIT_ASSERT(*it == Cval(i2));
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
		
		//	MISC
		/*	Examines each element in a source range and replaces it 
			if it matches a specified value while copying the result 
			into a new destination range.
		*/
		misc::replace_copy (myints, myints+8, v1.begin(), 20, 99);		
		//v1: 10 99 30 30 99 10 10 99		
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		//v2: 0, 1, 0, 3, 0, 5
		//v3:-1, 1,-1, 3,-1, 5
		misc::replace_copy (v2.begin(), v2.end(), v3.begin(), 0, -1);
		i0 = 0;
		for (it = v3.begin(); it != v3.end(); ++it, ++i0)
		{
			if(i0%2)	CPPUNIT_ASSERT(*it == Cval(i0));
			else		CPPUNIT_ASSERT(*it == Cval(-1));
		}		

#if !defined(DEBUG)
		//	STD
		std::replace_copy (myints, myints+8, v1.begin(), 99, 20);		
		//v1: 10 20 30 30 20 10 10 20
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(myints[it-v1.begin()] == *it);			
		}

		//v3:-1, 1,-1, 3,-1, 5
		//v2:-3, 1,-3, 3,-3, 5
		std::replace_copy (v3.begin(), v3.end(), v2.begin(), -1, -3);
		i0 = 0;
		for (it = v2.begin(); it != v2.end(); ++it, ++i0)
		{
			if(i0%2)	CPPUNIT_ASSERT(*it == Cval(i0));
			else		CPPUNIT_ASSERT(*it == Cval(-3));
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
		
		//	MISC
		/*	Examines each element in a source range and replaces it 
			if it satisfies a specified predicate while copying the result 
			into a new destination range.
		*/
		misc::replace_copy_if (v1.begin(), v1.end(), v2.begin(), IsOdd_replace_copy_if, Cval(0));
		//v2: 0 2 0 4 0 6 0 8 0		
		
		for (it=v2.begin(); it!=v2.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v2.begin()] == *it);			
		}

		misc::replace_copy_if (v3.begin(), v3.end(), v4.begin(), IsOdd_replace_copy_if, Cval(-5));
		for (it = v4.begin(), i0=0; it != v4.end(); ++it, ++i0)
		{
			if(i0%2 != 0)	CPPUNIT_ASSERT(*it == Cval(-5));
			else			CPPUNIT_ASSERT(*it == Cval(i0));
		}
		
#if !defined(DEBUG)
		//	STD
		std::replace_copy_if (v2.begin(), v2.end(), v1.begin(), IsNull_replace_copy_if, Cval(-1));
		//v1: -1 2 -1 4 -1 6 -1 8 -1				
		for (it = v1.begin(), i0 = 1; it != v1.end(); ++it, ++i0)
		{
			if(i0%2 == 0)	CPPUNIT_ASSERT(*it == Cval(i0));
			else			CPPUNIT_ASSERT(*it == Cval(-1));
		}

		std::replace_copy_if (v4.begin(), v4.end(), v3.begin(), IsOdd_replace_copy_if, Cval(-1));
		for (it = v3.begin(), i0=0; it != v3.end(); ++it, ++i0)
		{
			if(i0%2 != 0)	CPPUNIT_ASSERT(*it == Cval(-1));
			else			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		//	MISC
		/*	Assigns the same new value to every element in a specified range.
		*/
		misc::fill (v1.begin(), v1.begin() + 4, Cval(5));   // v1: 5 5 5 5 0 0 0 0
		misc::fill (v1.begin() + 3, v1.end() - 2, Cval(8)); // v1: 5 5 5 8 8 8 0 0

		//cout << "v1 contains:";
		Cval mycheck[]={5, 5, 5, 8, 8, 8, 0, 0};
		for ( it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}
		
		misc::fill (v2.begin(), v2.end(), Cval(-1));
		for (it = v2.begin(); it != v2.end(); ++it)
			CPPUNIT_ASSERT (*it == Cval(-1));


#if !defined(DEBUG)
		//	STD
		std::fill (v1.begin(), v1.begin() + 4, Cval(-5));    // v1: -5 -5 -5 -5  0  0 0 0
		std::fill (v1.begin() + 3, v1.end() - 2, Cval(-8));  // v1: -5 -5 -5 -8 -8 -8 0 0
				
		for ( it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(-1 * mycheck[it-v1.begin()] == *it);			
		}

		std::fill (v2.begin(), v2.end(), Cval(-2));
		for (it = v2.begin(); it != v2.end(); ++it)
			CPPUNIT_ASSERT (*it == Cval(-2));
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
		
		//	MISC
		/*	Assigns a new value to a specified number of elements 
			in a range beginning with a particular element.
		*/
		misc::fill_n (v1.begin(), 4, Cval(20));   // v1: 20 20 20 20 10 10 10 10
		misc::fill_n (v1.begin()+3, 3, Cval(33)); // v1: 20 20 20 33 33 33 10 10

		Cval mycheck[]={20, 20, 20, 33, 33, 33, 10, 10};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
		}

		misc::fill_n (v2.begin(), m_container_size, Cval(-1));
		for (it = v2.begin(); it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it == Cval(-1));

		//	STD
		std::fill_n (v1.begin(), 4, Cval(2));   // v1: 2 2 2 2 10 10 10 10
		std::fill_n (v1.begin()+3, 3, Cval(3)); // v1: 2 2 2 3  3  3 10 10

		Cval mycheck2[]={2, 2, 2, 3, 3, 3, 10, 10};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck2[it-v1.begin()] == *it);
		}

		std::fill_n (v2.begin(), m_container_size, Cval(-6));
		for (it = v2.begin(); it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it == Cval(-6));
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

		//	MISC
		misc::generate (v1.begin(), v1.end(), RandomNumber_generate);		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);	// weak check, cannot predict the value			
		}

		misc::generate (v1.begin(), v1.end(), UniqueNumber_generate);		
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);			
		}

		misc::generate (v2.begin(), v2.end(), RandomNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);
		}

		misc::generate (v2.begin(), v2.end(), UniqueNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);
		}
		
#if !defined(DEBUG)
		//	STD
		std::generate (v2.begin(), v2.end(), RandomNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);
		}

		std::generate (v2.begin(), v2.end(), UniqueNumber_generate);
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it > 0 && *it <= 100);
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

		//	MISC
		// reset the number generator
		current_generate_n = 0;
		misc::generate_n (myarray, 9, UniqueNumber_generate_n);
		
		for (i0 = 0; i0 < 9; ++i0)
		{
			CPPUNIT_ASSERT(myarray[i0] == Cval(i0+1));
		}

		current_generate_n = 0;	// reset the number generator
		misc::generate_n (v1.begin(), m_container_size, UniqueNumber_generate_n);

		for (i0 = 0, it = v1.begin(); it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0+1));
		}
		
		//	STD
		current_generate_n = 0;
		std::generate_n (myarray, 9, UniqueNumber_generate_n);

		for (i0 = 0; i0 < 9; ++i0)
		{
			CPPUNIT_ASSERT(myarray[i0] == Cval(i0+1));
		}

		current_generate_n = 0;	// reset the number generator
		std::generate_n (v1.begin(), m_container_size, UniqueNumber_generate_n);

		for (i0 = 0, it = v1.begin(); it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0+1));
		}
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
		
		//	MISC
		/*	Eliminates a specified value from a given range without disturbing
			the order of the remaining elements and returning the end of a new
			range free of the specified value.
		*/
		pend = misc::remove (pbegin, pend, 20);       // 10 30 30 10 10 ?  ?  ?
		                                              // ^              ^		
		
		int mycheck[]={10, 30, 30, 10, 10};
		for (int* p=pbegin; p!=pend; ++p)
		{
			CPPUNIT_ASSERT(mycheck[p-pbegin] == *p);			
		}

		It end1 = misc::remove (v1.begin(), v1.end(), Cval(-1));
		CPPUNIT_ASSERT( v1.begin() == end1);		



		//	STD
/*		error C2668: 'std::find' : ambiguous call to overloaded function
		Cannot decide which function to call:
		_InIt std::find<_FwdIt,_Ty>(_InIt,_InIt,const _Ty &)  or:
		InputIterator misc::find<_FwdIt,_Ty>(InputIterator,InputIterator,const T &)	
		
		when using std::remove with iterators belonging to misc::generic_array;
*/

//		It end2 = std::remove (v2.begin(), v2.end(), Cval(-2));
//		CPPUNIT_ASSERT( v2.begin() == end2);
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
		//	MISC
		/*	Eliminates elements that satisfy a predicate from a given range 
			without disturbing the order of the remaining elements and 
			returning the end of a new range free of the specified value.
		*/
		pend = misc::remove_if (pbegin, pend, IsOdd_remove_if);  // 2 4 6 8 ? ? ? ? ?
																 // ^       ^

		// the range contains:
		Cval mycheck[]={2, 4, 6, 8};
		for (Cval* p = pbegin; p != pend; ++p)
		{
			CPPUNIT_ASSERT(mycheck[p-pbegin] = *p);			
		}

		It end1 = misc::remove_if (v1.begin(), v1.end(), IsOdd_remove_if);
		CPPUNIT_ASSERT(v1.begin() == end1);

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
		//	MISC
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
			CPPUNIT_ASSERT(mycheck[p-pbegin] = *p);			
		}

		It end1 = std::remove_if (v1.begin(), v1.end(), IsOdd_remove_if);
		CPPUNIT_ASSERT(v1.begin() == end1);
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
		//	MISC
		/*	Copies elements from a source range to a destination range, 
			except that elements of a specified value are not copied, 
			without disturbing the order of the remaining elements and 
			returning the end of a new destination range.
		*/
		misc::remove_copy (myints, myints + 8, myvector.begin(), 20); // 10 30 30 10 10 0 0 0

		//cout << "myvector contains:";
		int mycheck[]={10, 30, 30, 10, 10, 0, 0, 0};
		for (it=myvector.begin(); it!=myvector.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-myvector.begin()] == *it);			
		}

		misc::remove_copy (v2.begin(), v2.end(), v3.begin(), Cval(1));
		for (it = v3.begin(); it != v3.end(); ++it)
			CPPUNIT_ASSERT(*it == Cval(-1));

#if !defined (DEBUG) // std::_Debug_range2
		//	STD
		std::remove_copy (v2.begin(), v2.end(), v3.begin(), Cval(1));
		for (it = v3.begin(); it != v3.end(); ++it)
			CPPUNIT_ASSERT(*it == Cval(-1));
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

		//	MISC
		/*	Copies elements from a source range to a destination range, 
			except that satisfying a predicate are not copied,
			without disturbing the order of the remaining elements 
			and returning the end of a new destination range.
		*/
		misc::remove_copy_if (myints, myints+9, v1.begin(), IsOdd_remove_copy_if);

		//cout << "v1 contains:";
		Cval check[]={2, 4, 6, 8, 0, 0, 0, 0, 0};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(check[it-v1.begin()] == *it);			
		}

		misc::remove_copy_if (v2.begin(), v2.end(), v3.begin(), IsOdd_remove_copy_if);
		for (it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT (*it == Cval(-1));
		}
		
#if !defined (DEBUG)
		//	STD
		std::remove_copy_if (v2.begin(), v2.end(), v3.begin(), IsOdd_remove_copy_if);
		for (it = v3.begin(); it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT (*it == Cval(-1));
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

		//	MISC
		/*	Removes duplicate elements that are adjacent to each other
			in a specified range.
		*/
		// using default comparison:
		it = misc::unique (v1.begin(), v1.end()); // 10 20 30 20 10 ?  ?  ?  ?		
		v1.resize(it - v1.begin());               // 10 20 30 20 10

		// using predicate comparison:
		it = misc::unique (v2.begin(), v2.end(), myfunction_unique);
		v2.resize (it - v2.begin());

		//cout << "v1 contains:";
		Cval mycheck[]={10, 20, 30, 20, 10};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}
		for (it = v2.begin(); it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v2.begin()] == *it);			
		}

		It end3 = misc::unique (v3.begin(), v3.end());
		CPPUNIT_ASSERT(++v3.begin() == end3);
		v3.resize(m_container_size, Cval(-1));
		end3 = misc::unique (v3.begin(), v3.end(), myfunction_unique);
		CPPUNIT_ASSERT(++v3.begin() == end3);


		//	STD
#if !defined (DEBUG)
		It end4 = std::unique (v4.begin(), v4.end());
		CPPUNIT_ASSERT(++v4.begin() == end4);
		v4.resize(m_container_size, Cval(-1));
		end4 = std::unique (v4.begin(), v4.end(), myfunction_unique);
		CPPUNIT_ASSERT(++v4.begin() == end4);
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
		
		//	MISC
		/*	Copies elements from a source range into a destination range
			except for the duplicate elements that are adjacent to each other.
		*/
		// using default comparison:
		// v1: 10 20 30 20 10 0  0  0  0
		it = misc::unique_copy (myints, myints + 9, v1.begin());
				
		// v1: 10 10 20 20 30 0  0  0  0
		misc::sort (v1.begin(),it);

		// using predicate comparison:
		it = misc::unique_copy (v1.begin(), it, v1.begin(), myfunction_unique_copy);
		
		// 10 20 30 20 30 0  0  0  0
		//          ^

		v1.resize( it - v1.begin() );
		// 10 20 30


		//cout << "v1 contains:";
		int mycheck[]={10, 20, 30};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}		
		
		it = misc::unique_copy (v2.begin(), v2.end(), v3.begin());
		CPPUNIT_ASSERT(++v3.begin() == it);


		//	STD
		// cannot deduce the iterator category
		// std::_Unique_copy : none of the 4 overloads could convert all the argument types
//		it = std::unique_copy (v2.begin(), v2.end(), v3.begin());
//		CPPUNIT_ASSERT(++v3.begin() == it);
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
		//	MISC
		//	Reverses the order of the elements within a range.
		misc::reverse(v1.begin(), v1.end()); // 9 8 7 6 5 4 3 2 1

		//cout << "v1 contains:";
		Cval mycheck[]={9, 8, 7, 6, 5, 4, 3, 2, 1};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
		}		

		misc::reverse (v2.begin(), v2.end());
		for (i0 = m_container_size-1, it = v2.begin(); it != v2.end(); ++it, --i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}


		//	STD
		// cannot deduce iterator category in:
		// void std::_Reverse<misc::generic_array_iterator<container>>(_BidIt,_BidIt,std::bidirectional_iterator_tag)
//		std::reverse (v3.begin(), v3.end());
//		for (i0 = m_container_size-1, it = v3.begin(); it != v3.end(); ++it, --i0)
//		{
//			CPPUNIT_ASSERT(*it == Cval(i0));
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

		//	MISC
		/*	Reverses the order of the elements within a source range 
			while copying them into a destination range.
		*/
		misc::reverse_copy (myints, myints+9, v1.begin());

		//cout << "v1 contains:";
		int mycheck[]={9, 8, 7, 6, 5, 4, 3, 2, 1};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
		}

		misc::reverse_copy (v2.begin(), v2.end(), v3.begin());
		for (it = v3.begin(), i0 = m_container_size-1; it != v3.end(); ++it, --i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}

#if !defined (DEBUG)	// std::_Debug_range2
		//	STD
		std::reverse_copy (v2.begin(), v2.end(), v3.begin());
		for (it = v3.begin(), i0 = m_container_size-1; it != v3.end(); ++it, --i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		//	MISC

		//Exchanges the elements in two adjacent ranges.
		misc::rotate(v1.begin(), v1.begin() + 3, v1.end()); // 4 5 6 7 8 9 1 2 3

		// v1: 4 5 6 7 8 9 1 2 3
		Cval mycheck[]={4, 5, 6, 7, 8, 9, 1, 2, 3};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		It mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		misc::rotate(v2.begin(), mid, v2.end()); //
		
		for(it = v2.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0 - m_container_size/2));
		}

		
		//	STD
		// Cannot deduce the iterator category.
	/*
		std::rotate(v3.begin(), ++v3.begin(), v3.end()); // 199999 1 2 3 4 ... 
		it = v3.begin();
		CPPUNIT_ASSERT(*it = Cval(m_container_size-1));
		for(i0 = 0; it != v3.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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

		//	MISC
		/*	Exchanges the elements in two adjacent ranges within 
			a source range and copies the result to a destination range.
		*/
		// v1: 40 50 60 70 10 20 30
		misc::rotate_copy(myints, myints + 3, myints + 7, v1.begin()); 

		// v1: 40 50 60 70 10 20 30
		Cval mycheck[]={40, 50, 60, 70, 10, 20, 30};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		It mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		misc::rotate_copy(v2.begin(), mid, v2.end(), v3.begin()); //

		for(it = v3.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0 - m_container_size/2));
		}
		

#if !defined(DEBUG)
		//	STD		
		mid = v2.begin();
		for(i0 = 0; i0 < m_container_size/2; ++i0) ++mid;
		std::rotate_copy(v2.begin(), mid, v2.end(), v3.begin()); //

		for(it = v3.begin(), i0 = 0; i0 < m_container_size/2; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(m_container_size/2 + i0));
		}
		for(; i0 < m_container_size; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0 - m_container_size/2));
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
		
		//	MISC
		/*	Rearranges a sequence of N elements in a range into one of N! 
			possible arrangements selected at random.
		*/
		
		// using built-in random generator:
		misc::random_shuffle(v1.begin(), v1.end());

		// using myrandom:
		misc::random_shuffle(v1.begin(), v1.end(), p_myrandom);
		// v1: 3 4 1 6 8 9 2 7 5 .. random sequence

		/*	It's good enough to check if each entry is unique, 
			which means that probably the shuffle is ok.
		*/
		for(i0 = 1; i0 < v1.size(); ++i0)
		{
			CPPUNIT_ASSERT(misc::count(v1.begin(), v1.end(), i0) == 1);
		}

#if !defined(DEBUG)
		//	STD
		std::random_shuffle(v2.begin(), v2.end());
		std::random_shuffle(v2.begin(), v2.end(), p_myrandom);

		for(i0 = 1; i0 < v1.size(); ++i0)
		{
			CPPUNIT_ASSERT(misc::count(v2.begin(), v2.end(), i0) == 1);
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
		
		
		//	MISC
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it.
		*/
		bound = misc::partition(v1.begin(), v1.end(), IsOdd_partition);

		//cout << "odd members:";
		Cval mycheck_odd[]={1, 9, 3, 7, 5};
		for(it = v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_odd[i0] == *it);			
		}

		//cout << "\neven members:";
		Cval mycheck_even[]={6, 4, 8, 2};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_even[i0] == *it);			
		}
		//odd members: 1 9 3 7 5
		//even members: 6 4 8 2

		bound = misc::partition(v2.begin(), v2.end(), IsOdd_partition);
		//odd members: 1 199999 3 199997 5 199995
		for (it = v2.begin(), i0 = 1; it != bound; ++it, ++i0)
		{
			if(i0%2)
			{
				CPPUNIT_ASSERT(*it == Cval(i0));				
			}
			else
			{
				CPPUNIT_ASSERT(*it == Cval(m_container_size - i0 + 1));
			}
		}

		//even members: ... 199994 6 199996 4 199998 2 200000
		for (it = --v2.end(), i0 = 1; it != bound; --it, ++i0)
		{
			if(i0%2)
			{
				CPPUNIT_ASSERT(*it == Cval(m_container_size - i0 + 1));
			}
			else
			{
				CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		
		//	MISC
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it.
		*/
		bound = std::partition(v1.begin(), v1.end(), IsOdd_partition);

		//cout << "odd members:";
		Cval mycheck_odd[]={1, 9, 3, 7, 5};
		for(it = v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_odd[i0] == *it);			
		}

		//cout << "\neven members:";
		Cval mycheck_even[]={6, 4, 8, 2};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_even[i0] == *it);			
		}
		//odd members: 1 9 3 7 5
		//even members: 6 4 8 2

		bound = std::partition(v2.begin(), v2.end(), IsOdd_partition);
		//odd members: 1 199999 3 199997 5 199995
		for (it = v2.begin(), i0 = 1; it != bound; ++it, ++i0)
		{
			if(i0%2)
			{
				CPPUNIT_ASSERT(*it == Cval(i0));				
			}
			else
			{
				CPPUNIT_ASSERT(*it == Cval(m_container_size - i0 + 1));
			}
		}

		//even members: ... 199994 6 199996 4 199998 2 200000
		for (it = --v2.end(), i0 = 1; it != bound; --it, ++i0)
		{
			if(i0%2)
			{
				CPPUNIT_ASSERT(*it == Cval(m_container_size - i0 + 1));
			}
			else
			{
				CPPUNIT_ASSERT(*it == Cval(i0));
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
			CPPUNIT_ASSERT(mycheck_odd[i0] == *it);
		}

		//even members:
		Cval mycheck_even[]={2, 4, 6, 8};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_even[i0] == *it);			
		}
		
		//odd members: 1 3 5 7 9 ... 199999
		bound = std::stable_partition(v2.begin(), v2.end(), IsOdd_stable_partition);
		for(it = v2.begin(), i0 = 1; it != bound; ++it, i0+=2)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}
		//even members: 2 4 6 8 ... 200000
		for(it = bound, i0 = 2; it != v2.end(); ++it, i0+=2)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		//	MISC (the entire method)
		/*	Classifies elements in a range into two disjoint sets, with those 
			elements satisfying a unary predicate preceding those that fail 
			to satisfy it, preserving the relative order of equivalent elements.
		*/
		bound = misc::stable_partition(v1.begin(), v1.end(), IsOdd_stable_partition);

		//odd members: 1 3 5 7 9
		//even members: 2 4 6 8

		//odd members:
		Cval mycheck_odd[]={1, 3, 5, 7, 9};
		for (it=v1.begin(), i0 = 0; it != bound; ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_odd[i0] == *it);
		}

		//even members:
		Cval mycheck_even[]={2, 4, 6, 8};
		for (it = bound, i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck_even[i0] == *it);			
		}
		
		//odd members: 1 3 5 7 9 ... 199999
		bound = misc::stable_partition(v2.begin(), v2.end(), IsOdd_stable_partition);
		for(it = v2.begin(), i0 = 1; it != bound; ++it, i0+=2)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}
		//even members: 2 4 6 8 ... 200000
		for(it = bound, i0 = 2; it != v2.end(); ++it, i0+=2)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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

		//	MISC
		// using default comparison (operator <):
		misc::sort(v1.begin(), v1.begin() + 4);
		//v1: (12 32 45 71)26 80 53 33

		// using function as comp
		misc::sort(v1.begin() + 4, v1.end(), myfunction_sort);
		//v1: 12 32 45 71(26 33 53 80)

		// using object as comp
		misc::sort(v1.begin(), v1.end(), myobject_sort);
		//v1: (12 26 32 33 45 53 71 80)

		//v1: 12 26 32 33 45 53 71 80
		int mycheck[]={12, 26, 32, 33, 45, 53, 71, 80};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
		}

		misc::sort(v2.begin() + m_container_size/2, v2.end(), myfunction_sort);
		misc::sort(v2.begin(), v2.end());
		for(it = v2.begin() + 1; it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it >= *(it - 1)); // used ::rand() so equal may exist.

#if !defined (DEBUG)
		//	STD
		std::sort(v3.begin() + m_container_size/2, v3.end(), myfunction_sort);
		std::sort(v3.begin(), v3.end());		
		for(it = v3.begin() + 1; it != v3.end(); ++it)
			CPPUNIT_ASSERT(*it >= *(it - 1));
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
			CPPUNIT_ASSERT(mycheck[i0] == *it);			
		}

		// reset to initial vaues
		v1.assign(mydoubles, mydoubles + 8);		

		// using 'compare_as_ints':
		std::stable_sort(v1.begin(), v1.end(), compare_as_ints_stable_sort);

		Cval mycheck2[]={1.41, 1.73, 1.32, 1.62, 2.72, 2.58, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck2[it-v1.begin()] == *it);			
		}

		std::stable_sort(v2.begin(), v2.end());
		for(it = v2.begin()+1; it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it >= *(it-1)); // ::rand may have created duplicates;
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
		
		//	MISC  (the entire method)
		/*	Arranges the elements in a specified range 
			into a non-descending order or according to an ordering criterion
			specified by a binary predicate and preserves the relative ordering
			of equivalent elements.
		*/
		
		// using default comparison:
		misc::stable_sort(v1.begin(), v1.end());
		Cval mycheck[]={1.32, 1.41, 1.62, 1.73, 2.58, 2.72, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck[i0] == *it);			
		}

		// reset to initial values
		v1.assign(mydoubles, mydoubles + 8);		

		// using 'compare_as_ints':
		misc::stable_sort(v1.begin(), v1.end(), compare_as_ints_stable_sort);

		Cval mycheck2[]={1.41, 1.73, 1.32, 1.62, 2.72, 2.58, 3.14, 4.67};
		for (it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck2[it-v1.begin()] == *it);			
		}

		misc::stable_sort(v2.begin(), v2.end());
		for(it = v2.begin()+1; it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it >= *(it-1)); // ::rand may have created duplicates;
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

		// MISC
		/*	Arranges a specified number of the smaller elements in a range 
			into a non-descending order or according to an ordering criterion 
			specified by a binary predicate.
		*/

		// using default comparison (operator <):
		misc::partial_sort(v1.begin(), v1.begin() + 5, v1.end());
		for(it = v1.begin(), i0=1; it != v1.begin()+5; ++it, ++i0)
		{		
			CPPUNIT_ASSERT(*it == Cval(i0));
		}

		// using function as comp
		misc::partial_sort(v1.begin(), v1.begin() + 5, v1.end(), myfunction_partial_sort);

		//cout << "v1 contains:";
		Cval mycheck[]={1, 2, 3, 4, 5, 9, 8, 7, 6};
		for (it=v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck[i0] == *it);			
		}
		//v1 contains: 1 2 3 4 5 9 8 7 6

		misc::partial_sort(v2.begin(), v2.begin() + m_container_size - 10, v2.end());		
		for(it = v2.begin(), i0 = 1; it != v2.begin() + m_container_size - 10; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}

#if !defined(DEBUG)
		// STD
		std::partial_sort(v3.begin(), v3.begin() + m_container_size - 10, v3.end());		
		for(it = v3.begin(), i0 = 1; it != v3.begin() + m_container_size - 10; ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		//	MISC
		/*	Copies elements from a source range into a destination range 
			where the source elements are ordered by either less than or 
			another specified binary predicate.
		*/

		// using default comparison (operator <):
		misc::partial_sort_copy (myints, myints + 9, v1.begin(), v1.end());

		// using function as comp
		misc::partial_sort_copy (myints, myints + 9, v1.begin(), v1.end(), myfunction_partial_sort_copy);

		//v1 : 1 2 3 4 5
		Cval mycheck[]={1, 2, 3, 4, 5};
		for (it = v1.begin(); it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);			
		}

		misc::partial_sort_copy(v2.begin(), v2.end(), v3.begin(), v3.end());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
		}

#if !defined(DEBUG)
		//	STD
		std::partial_sort_copy(v2.begin(), v2.end(), v3.begin(), v3.end());
		for(it = v3.begin(), i0 = 1; it != v3.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(*it == Cval(i0));
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
	misc::random_shuffle(v2.begin(), v2.end());

	Container v3(v2);

	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	MISC
		/*	Rearranges a sequence of N elements in a range into one of N! 
			possible arrangements selected at random. 
			Obs: thereis no ::seed(..) call, the sequence is always the 
				same in all implementations.
		*/
		misc::random_shuffle(v1.begin(), v1.end());

		//	nth_element
		/*	Partitions a range of elements, correctly locating the nth 
			element of the sequence in the range so that all the elements
			in front of it are less than or equal to it and all the elements
			that follow it in the sequence are greater than or equal to it.
		*/

		// using default comparison (operator <):
		misc::nth_element(v1.begin(), v1.begin() + 5, v1.end());
 
		// using function as comp
		misc::nth_element(v1.begin(), v1.begin() + 5, v1.end(), myfunction_nth_element);

		i2 = *(v1.begin() + 5);
		for(it = v1.begin(); it != v1.begin() + 5; ++it)
		{
			CPPUNIT_ASSERT(*it < i2);
		}
		for(it = v1.begin() + 5; it != v1.end(); ++it)
		{
			CPPUNIT_ASSERT(*it >= i2);
		}

		misc::nth_element(v2.begin(), v2.begin()+m_container_size/2, v2.end());
		i2 = *(v2.begin() + m_container_size/2);
		It mid =  v2.begin() + m_container_size/2;
		for(it = v2.begin(); it != mid; ++it)
		{
			CPPUNIT_ASSERT(*it < i2);
		}
		for(it = mid; it != v2.end(); ++it)
		{
			CPPUNIT_ASSERT(*it >= i2);
		}

#if !defined(DEBUG)
		//	STD
		// using default comparison (operator <):
		std::nth_element(v3.begin(), v3.begin()+m_container_size/2, v3.end());
		i2 = *(v3.begin() + m_container_size/2);
		mid = v3.begin() + m_container_size/2;
		for(it = v3.begin(); it != mid; ++it)
		{
			CPPUNIT_ASSERT(*it < i2);
		}
		for(it = mid; it != v3.end(); ++it)
		{
			CPPUNIT_ASSERT(*it >= i2);
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

		//	MISC
		misc::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		low = misc::lower_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //4th element
		up  = misc::upper_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //7th element

		CPPUNIT_ASSERT((low - v1.begin()) == 3);
		CPPUNIT_ASSERT(( up - v1.begin()) == 6);

		low = misc::lower_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));
		up = misc::upper_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));


		Diff d0v2 = low - v2.begin();
		Diff d2v2 = up - v2.begin();
		CPPUNIT_ASSERT( d0v2 == m_container_size/2 - 1 );
		CPPUNIT_ASSERT( d2v2 == m_container_size/2 );

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

		//	MISC
		misc::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		low = std::lower_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //4th element
		up  = std::upper_bound<It, Cval> (v1.begin(), v1.end(), Cval(20)); //7th element

		CPPUNIT_ASSERT((low - v1.begin()) == 3);
		CPPUNIT_ASSERT(( up - v1.begin()) == 6);

		low = std::lower_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));
		up = std::upper_bound<It, Cval>(v2.begin(), v2.end(), Cval(m_container_size/2));


		Diff d0v2 = low - v2.begin();
		Diff d2v2 = up - v2.begin();
		CPPUNIT_ASSERT( d0v2 == m_container_size/2 - 1 );
		CPPUNIT_ASSERT( d2v2 == m_container_size/2 );
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
	typedef typename misc::pair<It, It> MPair;
	

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
		//	MISC
		//	using default comparison:
		misc::sort(v1.begin(), v1.end()); // 10 10 10 20 20 20 30 30

		/*	Finds a pair of positions in an ordered range, the first less
			than or equivalent to the position of a specified element and 
			the second greater than the element's position, where the sense 
			of equivalence or ordering used to establish the positions 
			in the sequence may be specified by a binary predicate.
		*/
		bounds = misc::equal_range<It, Cval>(v1.begin(), v1.end(), 20);

		// using "mygreater_equal_range" as comp:
		misc::sort (v1.begin(), v1.end(), mygreater_equal_range);                                 // 30 30 20 20 20 10 10 10
		bounds = misc::equal_range<It, Cval>(v1.begin(), v1.end(), 20, mygreater_equal_range);    //       ^        ^

		CPPUNIT_ASSERT((int)(bounds.first - v1.begin()) == 2);
		CPPUNIT_ASSERT((int)(bounds.second - v1.begin()) == 5);


		bounds = misc::equal_range<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		CPPUNIT_ASSERT(bounds.first - v2.begin() == m_container_size/2);
		CPPUNIT_ASSERT(bounds.second - v2.begin() == m_container_size/2+1);
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
		//	MISC
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
		misc::sort (v1.begin(), v1.end(), mygreater_equal_range);                                 // 30 30 20 20 20 10 10 10
		bounds = std::equal_range<It, Cval>(v1.begin(), v1.end(), 20, mygreater_equal_range);    //       ^        ^

		CPPUNIT_ASSERT((int)(bounds.first - v1.begin()) == 2);
		CPPUNIT_ASSERT((int)(bounds.second - v1.begin()) == 5);


		bounds = std::equal_range<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		CPPUNIT_ASSERT(bounds.first - v2.begin() == m_container_size/2);
		CPPUNIT_ASSERT(bounds.second - v2.begin() == m_container_size/2+1);
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
		CPPUNIT_ASSERT(res);

		// using myfunction as comp:
		std::sort(v1.begin(), v1.end(), myfunction_binary_search);

		//cout << "looking for a 6... ";
		res = std::binary_search<It, Cval>(v1.begin(), v1.end(), 6, myfunction_binary_search);
		CPPUNIT_ASSERT(!res);

		res = std::binary_search<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		CPPUNIT_ASSERT(res);
		res = std::binary_search<It, Cval>(v2.begin(), v2.end(), 2*m_container_size, myfunction_binary_search);
		CPPUNIT_ASSERT(!res);
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
		
		
		//	MISC (the entire method)
		// using default comparison:
		misc::sort(v1.begin(), v1.end());

		//cout << "looking for a 3... ";
		bool res = misc::binary_search<It, Cval>(v1.begin(), v1.end(), 3);
		CPPUNIT_ASSERT(res);

		// using myfunction as comp:
		misc::sort(v1.begin(), v1.end(), myfunction_binary_search);

		//cout << "looking for a 6... ";
		res = misc::binary_search<It, Cval>(v1.begin(), v1.end(), 6, myfunction_binary_search);
		CPPUNIT_ASSERT(!res);

		res = misc::binary_search<It, Cval>(v2.begin(), v2.end(), m_container_size/2);
		CPPUNIT_ASSERT(res);
		res = misc::binary_search<It, Cval>(v2.begin(), v2.end(), 2*m_container_size, myfunction_binary_search);
		CPPUNIT_ASSERT(!res);
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
			CPPUNIT_ASSERT(mycheck[i0] == *it);
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
		
		
		//	MISC
		misc::sort(first, first + 5);
		misc::sort(second, second + 5);

		/*	Combines all the elements from two sorted source ranges 
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		misc::merge (first, first + 5, second, second + 5, v1.begin());

		//cout << "The resulting vector contains:";
		Cval mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for(it = v1.begin(), i0 = 0; it != v1.end(); ++it, ++i0)
		{
			CPPUNIT_ASSERT(mycheck[i0] == *it);
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50

		misc::sort(v2.begin(), v2.end());
		misc::sort(v3.begin(), v3.end());
		misc::merge(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
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
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50


		std::copy(v2.begin(), v2.end(), v4.begin());
		std::copy(v3.begin(), v3.end(), v4.begin() + v2.size());
		std::inplace_merge(v4.begin(), v4.begin() + m_container_size/2, v4.end());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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

		//	MISC (the entire method)
		misc::sort(first, first + 5);
		misc::sort(second, second + 5);

		misc::copy(first, first + 5, v1.begin());
		misc::copy(second, second + 5, v1.begin() + 5);

		/*	Combines the elements from two consecutive sorted ranges 
			into a single sorted range, where the ordering criterion 
			may be specified by a binary predicate.
		*/
		misc::inplace_merge(v1.begin(), v1.begin() + 5, v1.end());

		//cout << "The resulting vector contains:";
		int mycheck[]={5, 10, 10, 15, 20, 20, 25, 30, 40, 50};
		for (it=v1.begin(); it!=v1.end(); ++it)
		{
			CPPUNIT_ASSERT(mycheck[it-v1.begin()] == *it);
			//cout << " " << *it;
		}
		//The resulting vector contains: 5 10 10 15 20 20 25 30 40 50


		misc::copy(v2.begin(), v2.end(), v4.begin());
		misc::copy(v3.begin(), v3.end(), v4.begin() + v2.size());
		misc::inplace_merge(v4.begin(), v4.begin() + m_container_size/2, v4.end());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		CPPUNIT_ASSERT( res );
		//cout << "c1 includes c2!" << endl;
		
		// using myfunction as comp:
		res = std::includes(c1, c1+10, c2, c2+4, myfunction_includes);
		CPPUNIT_ASSERT( res );

		//c1 includes c2!
		//c1 includes c2!

		res = std::includes(v1.begin(), v1.end(), v2.begin(), v2.end());
		CPPUNIT_ASSERT( res );
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
		
		//	MISC (the entire method)
		misc::sort(c1, c1 + 10);       //5,10,15,20,25,30,35,40,45,50,
		misc::sort(c2, c2 + 4);        //  10,   20,   30,   40

		/*	Tests whether one sorted range contains all the elements contained
			in a second sorted range, where the ordering or equivalence 
			criterion between elements may be specified by a binary predicate.
		*/
		// using default comparison:
		res = misc::includes(c1, c1+10, c2, c2+4);
		CPPUNIT_ASSERT( res );
		//cout << "c1 includes c2!" << endl;
		
		// using myfunction as comp:
		res = misc::includes(c1, c1+10, c2, c2+4, myfunction_includes);
		CPPUNIT_ASSERT( res );

		//c1 includes c2!
		//c1 includes c2!

		res = misc::includes(v1.begin(), v1.end(), v2.begin(), v2.end());
		CPPUNIT_ASSERT( res );
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
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "union has " << int(it - v1.begin()) << " elements.\n";
		CPPUNIT_ASSERT((it-v1.begin()) == 8);
		//union has 8 elements

		std::set_union(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		
		//	MISC (the entire method)
		misc::sort(first, first + 5);                //  5 10 15 20 25
		misc::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to at least one of two 
			sorted source ranges into a single, sorted destination range, 
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = misc::set_union (first, first+5, second, second+5, v1.begin());
		// 5 10 15 20 25 30 40 50  0  0

		Cval mycheck[]={5, 10, 15, 20, 25, 30, 40, 50,  0,  0};
		for(size_t i=0; i < v1.size(); ++i)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "union has " << int(it - v1.begin()) << " elements.\n";
		CPPUNIT_ASSERT((it-v1.begin()) == 8);
		//union has 8 elements

		misc::set_union(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "intersection has " << int(it - v1.begin()) << " elements.\n";
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 2);
		//intersection has 2 elements
		
		it = std::set_intersection(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		CPPUNIT_ASSERT(it - v4.begin() == m_container_size);
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		
		//	MISC (the entire method)
		misc::sort(first, first + 5);                //  5 10 15 20 25
		misc::sort(second, second + 5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to both sorted source ranges
			into a single, sorted destination range, where the ordering 
			criterion may be specified by a binary predicate.
		*/

		it = misc::set_intersection (first, first+5, second, second+5, v1.begin());
		// 10 20 0  0  0  0  0  0  0  0

		Cval mycheck[]={10, 20, 0,  0,  0,  0,  0,  0,  0,  0};

		for(size_t i=0; i < v1.size(); ++i)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "intersection has " << int(it - v1.begin()) << " elements.\n";
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 2);
		//intersection has 2 elements
		
		it = misc::set_intersection(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin());
		CPPUNIT_ASSERT(it - v4.begin() == m_container_size);
		for(it = v4.begin(), i0 = 0; it != v4.end(); ++it, ++i0)
			CPPUNIT_ASSERT(*it == Cval(i0));
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
		
		//	MISC
		misc::sort (first,first+5);                //  5 10 15 20 25
		misc::sort (second,second+5);              // 10 20 30 40 50

		/*	Unites all of the elements that belong to one sorted source range,
			but not to a second sorted source range, into a single, sorted 
			destination range, where the ordering criterion may be specified 
			by a binary predicate.
		*/

		it = misc::set_difference (first, first+5, second, second+5, v1.begin());
		// 5 15 25  0  0  0  0  0  0  0

		Cval mycheck[]={5, 15, 25,  0,  0,  0,  0,  0,  0,  0};
		for(size_t i=0; i<v1.size(); ++i)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}
		//cout << "difference has " << int(it - v1.begin()) << " elements.\n";
		CPPUNIT_ASSERT((int)(it-v1.begin()) == 3);
		//difference has 3 elements


		it = misc::set_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), misc::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			CPPUNIT_ASSERT(*it2 == Cval(i0));

		//	STD
		it = misc::set_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), std::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			CPPUNIT_ASSERT(*it2 == Cval(i0));		
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
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "symmetric difference has " << int(it - v1.begin()) << " elements.\n";

		CPPUNIT_ASSERT((int)(it-v1.begin()) == 6);
		//symmetric difference has 6 elements

		it = std::set_symmetric_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), std::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			CPPUNIT_ASSERT(*it2 == Cval(i0));
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

		//	MISC (the entire method)
		misc::sort (first, first + 5);    //  5 10 15 20 25
		misc::sort (second, second + 5);  // 10 20 30 40 50


		/*	Unites all of the elements that belong to one, but not both, 
			of the sorted source ranges into a single, sorted destination range,
			where the ordering criterion may be specified by a binary predicate.
		*/
		it = misc::set_symmetric_difference (first, first+5, second, second+5, v1.begin());
		// 5 15 25 30 40 50  0  0  0  0

		Cval mycheck[]={5, 15, 25, 30, 40, 50,  0,  0,  0,  0};
		for(size_t i=0; i<v1.size(); ++i)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
		}

		//cout << "symmetric difference has " << int(it - v1.begin()) << " elements.\n";

		CPPUNIT_ASSERT((int)(it-v1.begin()) == 6);
		//symmetric difference has 6 elements

		it = misc::set_symmetric_difference(v2.begin(), v2.end(), v3.begin(), v3.end(), v4.begin(), misc::less<Cval>());
		for(it2 = v4.begin(), i0 = 1; it2 != it; ++it2, i0 += 2)
			CPPUNIT_ASSERT(*it2 == Cval(i0));
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
		CPPUNIT_ASSERT(v1.front() == 30);

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
		CPPUNIT_ASSERT(v1.front() == 20);


		/*	push_heap
			Adds an element that is at the end of a range to an existing heap 
			consisting of the prior elements in the range.
		*/
		v1.push_back(99);
		std::push_heap (v1.begin(), v1.end());
		// v1: 99 (20 10 5 15)

		//cout << "max heap after push: " << v1.front() << endl;
		CPPUNIT_ASSERT(v1.front() == 99);

		//Converts a heap into a sorted range.
		std::sort_heap (v1.begin(), v1.end());

		//cout << "final sorted range :";
		int mycheck[]={5, 10, 15, 20, 99};
		for (unsigned i=0; i<v1.size(); i++)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
			//cout << " " << v[i];
		}


		//v2: 0 1 2 3 ... 199999
		std::make_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 199999 (0 1 2 3 ... 199998)
		CPPUNIT_ASSERT(*v2.begin() == Cval(m_container_size-1));

		std::pop_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 199998 (0 1 2 3 ... 199999)
		CPPUNIT_ASSERT(*v2.begin() == m_container_size-2);
		CPPUNIT_ASSERT(*v2.rbegin() == m_container_size-1);

		v2.pop_back();
		//v2: 199998 (0 1 2 3 ... 199997)
		v2.push_back(m_container_size);
		std::push_heap(v2.begin(), v2.end(), std::less<Cval>());
		//v2: 200000 (199998 0 1 2 3 ... 199997)
		CPPUNIT_ASSERT(v2.front() == Cval(m_container_size));

		std::sort_heap(v2.begin(), v2.end());
		//v2: 0 1 2 3 ...
		for(it = v2.begin()+1; it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it > *(it-1));

		//v3: 0 1 2 3 ... 199999
		std::make_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 199999 (0 1 2 3 ... 199998)
		CPPUNIT_ASSERT(*v3.begin() == Cval(m_container_size-1));

		std::pop_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 199998 (0 1 2 3 ... 199999)
		CPPUNIT_ASSERT(*v3.begin() == m_container_size-2);
		CPPUNIT_ASSERT(*v3.rbegin() == m_container_size-1);

		v3.pop_back();
		//v3: 199998 (0 1 2 3 ... 199997)
		v3.push_back(m_container_size);
		std::push_heap(v3.begin(), v3.end(), std::less<Cval>());
		//v3: 200000 (199998 0 1 2 3 ... 199997)
		CPPUNIT_ASSERT(v3.front() == Cval(m_container_size));

		std::sort_heap(v3.begin(), v3.end());
		//v3: 0 1 2 3 ...
		for(it = v3.begin()+1; it != v3.end(); ++it)
			CPPUNIT_ASSERT(*it > *(it-1));
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
	misc::random_shuffle(v2.begin(), v2.end());

	Container v3(v2);


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	MISC (the entire method)
		/*	make_heap
			Converts elements from a specified range into a heap in which 
			the first element is the largest and for which a sorting criterion 
			may be specified with a binary predicate.
		*/

		misc::make_heap (v1.begin(), v1.end());
		//initial max heap : 30 (10 20 5 15)
		CPPUNIT_ASSERT(v1.front() == 30);

		/*	pop_heap
			Removes the largest element from the front of a heap to 
			the next-to-last position in the range and then forms a new heap 
			from the remaining elements.
		*/
		misc::pop_heap (v1.begin(), v1.end());
		// v1: 20 (10 5 15 30)
		v1.pop_back();
		// v1: 20 (10 5 15)

		//cout << "max heap after pop : " << v1.front() << endl;
		CPPUNIT_ASSERT(v1.front() == 20);


		/*	push_heap
			Adds an element that is at the end of a range to an existing heap 
			consisting of the prior elements in the range.
		*/
		v1.push_back(99);
		misc::push_heap (v1.begin(), v1.end());
		// v1: 99 (20 10 5 15)

		//cout << "max heap after push: " << v1.front() << endl;
		CPPUNIT_ASSERT(v1.front() == 99);

		//Converts a heap into a sorted range.
		misc::sort_heap (v1.begin(), v1.end());

		//cout << "final sorted range :";
		int mycheck[]={5, 10, 15, 20, 99};
		for (unsigned i=0; i<v1.size(); i++)
		{
			CPPUNIT_ASSERT(mycheck[i] == v1[i]);
			//cout << " " << v[i];
		}


		//v2: 0 1 2 3 ... 199999
		misc::make_heap(v2.begin(), v2.end(), misc::less<Cval>());
		//v2: 199999 (0 1 2 3 ... 199998)
		CPPUNIT_ASSERT(*v2.begin() == Cval(m_container_size-1));

		misc::pop_heap(v2.begin(), v2.end(), misc::less<Cval>());
		//v2: 199998 (0 1 2 3 ... 199999)
		CPPUNIT_ASSERT(*v2.begin() == m_container_size-2);
		CPPUNIT_ASSERT(*v2.rbegin() == m_container_size-1);

		v2.pop_back();
		//v2: 199998 (0 1 2 3 ... 199997)
		v2.push_back(m_container_size);
		misc::push_heap(v2.begin(), v2.end(), misc::less<Cval>());
		//v2: 200000 (199998 0 1 2 3 ... 199997)
		CPPUNIT_ASSERT(v2.front() == Cval(m_container_size));

		misc::sort_heap(v2.begin(), v2.end());
		//v2: 0 1 2 3 ...
		for(it = v2.begin()+1; it != v2.end(); ++it)
			CPPUNIT_ASSERT(*it > *(it-1));
		
		//v3: 0 1 2 3 ... 199999
		misc::make_heap(v3.begin(), v3.end(), misc::less<Cval>());
		//v3: 199999 (0 1 2 3 ... 199998)
		CPPUNIT_ASSERT(*v3.begin() == Cval(m_container_size-1));

		misc::pop_heap(v3.begin(), v3.end(), misc::less<Cval>());
		//v3: 199998 (0 1 2 3 ... 199999)
		CPPUNIT_ASSERT(*v3.begin() == m_container_size-2);
		CPPUNIT_ASSERT(*v3.rbegin() == m_container_size-1);

		v3.pop_back();
		//v3: 199998 (0 1 2 3 ... 199997)
		v3.push_back(m_container_size);
		misc::push_heap(v3.begin(), v3.end(), misc::less<Cval>());
		//v3: 200000 (199998 0 1 2 3 ... 199997)
		CPPUNIT_ASSERT(v3.front() == Cval(m_container_size));

		misc::sort_heap(v3.begin(), v3.end());
		//v3: 0 1 2 3 ...
		for(it = v3.begin()+1; it != v3.end(); ++it)
			CPPUNIT_ASSERT(*it > *(it-1));
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
		misc::min( will not prevent MS compiler from expanding min to its macro.
		misc::min(2, 1) : error.
		misc::min< will however DO prevent macro expanding due to template arg.
		misc::min<int>(2, 1) : OK.
	*/


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		
		//	MISC
		CPPUNIT_ASSERT( misc::min<Cval>(1,2) == 1 );
		CPPUNIT_ASSERT( misc::min<int>(1,2) == 1 );
		CPPUNIT_ASSERT( misc::min<int>(2,1) == 1 );
		CPPUNIT_ASSERT( misc::min<char>('a','z') == 'a' );
		CPPUNIT_ASSERT( misc::min<double>(3.14,2.72) == 2.72 );   


		//	STD
		CPPUNIT_ASSERT( std::min<Cval>(1,2) == 1 );
		CPPUNIT_ASSERT( std::min<int>(1,2) == 1 );
		CPPUNIT_ASSERT( std::min<int>(2,1) == 1 );
		CPPUNIT_ASSERT( std::min<char>('a','z') == 'a' );
		CPPUNIT_ASSERT( std::min<double>(3.14,2.72) == 2.72 ); 
	}	
}

template<typename Container>
void test_algorithm::max2(const char* msg)
{
	typedef typename Container::value_type Cval;


	//	TEST
	{
		time_printer tp(msg, m_print_time);
		//	MISC
		CPPUNIT_ASSERT( misc::max<Cval>(1,2) == 2 );
		CPPUNIT_ASSERT( misc::max<int>(1,2) == 2 );
		CPPUNIT_ASSERT( misc::max<long>(2,1) == 2 );
		CPPUNIT_ASSERT( misc::max<char>('a','z') == 'z' );
		CPPUNIT_ASSERT( misc::max<double>(3.14,2.72) == 3.14 );

		//	STD
		CPPUNIT_ASSERT( std::max<Cval>(1,2) == 2 );
		CPPUNIT_ASSERT( std::max<int>(1,2) == 2 );
		CPPUNIT_ASSERT( std::max<long>(2,1) == 2 );
		CPPUNIT_ASSERT( std::max<char>('a','z') == 'z' );
		CPPUNIT_ASSERT( std::max<double>(3.14,2.72) == 3.14 );
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
		//	MISC
		
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
		CPPUNIT_ASSERT(*misc::min_element(myints,myints+7) == 2);
		CPPUNIT_ASSERT(*misc::max_element(myints,myints+7) == 9);


		// using function myfn as comp:
		CPPUNIT_ASSERT(*misc::min_element(myints,myints+7,myfn_min_element) == 2);
		CPPUNIT_ASSERT(*misc::max_element(myints,myints+7,myfn_min_element) == 9);


		// using object myobj as comp:
		CPPUNIT_ASSERT(*misc::min_element(myints,myints+7,myobj_min_element) == 2);
		CPPUNIT_ASSERT(*misc::max_element(myints,myints+7,myobj_min_element) == 9);


		//	STD
		//default
		CPPUNIT_ASSERT(*std::min_element(myints,myints+7) == 2);
		CPPUNIT_ASSERT(*std::max_element(myints,myints+7) == 9);


		// using function myfn as comp:
		CPPUNIT_ASSERT(*std::min_element(myints,myints+7,myfn_min_element) == 2);
		CPPUNIT_ASSERT(*std::max_element(myints,myints+7,myfn_min_element) == 9);


		// using object myobj as comp:
		CPPUNIT_ASSERT(*std::min_element(myints,myints+7,myobj_min_element) == 2);
		CPPUNIT_ASSERT(*std::max_element(myints,myints+7,myobj_min_element) == 9);
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
		//	MISC

		//cout << "Using default comparison (operator<): ";
		// first is less then
		CPPUNIT_ASSERT(misc::lexicographical_compare(first,first+5,second,second+9));
		// second is not less then
		CPPUNIT_ASSERT(misc::lexicographical_compare(second,second+9,first,first+5) == false);


		//cout << "Using mycomp as comparison object: ";
		// first is not less then (when using mycomp... comparison)
		CPPUNIT_ASSERT(misc::lexicographical_compare(first,first+5,second,second+9,mycomp_lexicographical_compare) == false);
		// second is less then when using mycomp... comparison
		CPPUNIT_ASSERT(misc::lexicographical_compare(second,second+9,first,first+5,mycomp_lexicographical_compare));
		/*
		  Using default comparison (operator<): Apple is less than apartment
		  Using mycomp as comparison object: Apple is greater than apartment
		*/

		//	STD
		CPPUNIT_ASSERT(std::lexicographical_compare(first,first+5,second,second+9));
		CPPUNIT_ASSERT(std::lexicographical_compare(second,second+9,first,first+5) == false);
		CPPUNIT_ASSERT(std::lexicographical_compare(first,first+5,second,second+9,mycomp_lexicographical_compare) == false);
		CPPUNIT_ASSERT(std::lexicographical_compare(second,second+9,first,first+5,mycomp_lexicographical_compare));
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
			CPPUNIT_ASSERT(mycheck[i0][0] == myints[0]);
			CPPUNIT_ASSERT(mycheck[i0][1] == myints[1]);
			CPPUNIT_ASSERT(mycheck[i0][2] == myints[2]);
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
				CPPUNIT_ASSERT(*it1 == *it2);
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
		//	MISC (the entire method)
		time_printer tp(msg, m_print_time);
		
			
		//cout << "The 3! possible permutations with 3 elements:\n";
		misc::sort(myints, myints + 3);

		/*	next_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified 
			with a binary predicate.
		*/
		i0 = 0;
		do
		{
			CPPUNIT_ASSERT(mycheck[i0][0] == myints[0]);
			CPPUNIT_ASSERT(mycheck[i0][1] == myints[1]);
			CPPUNIT_ASSERT(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while(misc::next_permutation(myints, myints + 3));


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
		while(misc::next_permutation(v1.begin(), v1.end()) &&
			  misc::next_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				CPPUNIT_ASSERT(*it1 == *it2);
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
			CPPUNIT_ASSERT(mycheck[i0][0] == myints[0]);
			CPPUNIT_ASSERT(mycheck[i0][1] == myints[1]);
			CPPUNIT_ASSERT(mycheck[i0][2] == myints[2]);
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
				CPPUNIT_ASSERT(*it1 == *it2);
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
		//	MISC (the entire method)
		time_printer tp(msg, m_print_time);
		
		//cout << "The 3! possible permutations with 3 elements:\n";
		misc::sort(myints, myints + 3);
		misc::reverse(myints, myints + 3);

		/*	prev_permutation:
			Reorders the elements in a range so that the original ordering 
			is replaced by the lexicographically next greater permutation 
			if it exists, where the sense of next may be specified with 
			a binary predicate.
		*/
		i0 = 0;
		do
		{
			CPPUNIT_ASSERT(mycheck[i0][0] == myints[0]);
			CPPUNIT_ASSERT(mycheck[i0][1] == myints[1]);
			CPPUNIT_ASSERT(mycheck[i0][2] == myints[2]);
			i0++;
			//cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
		}
		while ( misc::prev_permutation(myints,myints+3) );

		/*
		  3 2 1
		  3 1 2
		  2 3 1
		  2 1 3
		  1 3 2
		  1 2 3
		*/

		while(misc::prev_permutation(v1.begin(), v1.end()) && 
			  misc::prev_permutation(v2.begin(), v2.end()) )
		{
			It it1 = v1.begin();
			It it2 = v2.begin();
			for(; it1 != v1.end(); ++it1, ++it2)
				CPPUNIT_ASSERT(*it1 == *it2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

















