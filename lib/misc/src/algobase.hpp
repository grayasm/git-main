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


#ifndef __algobase_hpp__
#define __algobase_hpp__


//c
#include <stdlib.h>
//c++
//misc
#include "functional.hpp"
#include "utility.hpp"
#include "memory.hpp"


namespace misc
{
	namespace algobase
	{
		// 25.1, non-modifying sequence operations:
		template<typename InputIterator, typename Function>
		Function for_each(InputIterator first, InputIterator last, Function f);

		template<typename InputIterator, typename T>
		InputIterator find(InputIterator first, InputIterator last, const T& value);

		template<typename InputIterator, typename Predicate>
		InputIterator find_if(
			InputIterator first, InputIterator last, Predicate pred);

		template<typename ForwardIterator1, typename ForwardIterator2>
		ForwardIterator1 find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2);

		template<typename ForwardIterator1, typename ForwardIterator2,
				 typename BinaryPredicate>
		ForwardIterator1 find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred);

		template<typename ForwardIterator1, typename ForwardIterator2>
		ForwardIterator1 find_first_of(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2);

		template<typename ForwardIterator1, typename ForwardIterator2,
				 typename BinaryPredicate>
		ForwardIterator1 find_first_of(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred);

		template<typename ForwardIterator>
		ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last);

		template<typename ForwardIterator, typename BinaryPredicate>
		ForwardIterator adjacent_find(
			ForwardIterator first, ForwardIterator last,
			BinaryPredicate pred);

		template<typename InputIterator, typename T>
		typename iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const T& value);

		template<typename InputIterator, typename Predicate>
		typename iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, Predicate pred);

		template<typename InputIterator1, typename InputIterator2>
		misc::pair<InputIterator1, InputIterator2>
		mismatch(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2);

		template<typename InputIterator1, typename InputIterator2,
				 typename BinaryPredicate>
		misc::pair<InputIterator1, InputIterator2>
		mismatch(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			BinaryPredicate pred);

		template<typename InputIterator1, typename InputIterator2>
		bool equal(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2);


		template<typename InputIterator1, typename InputIterator2,
				 typename BinaryPredicate>
		bool equal(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			BinaryPredicate pred);

		template<typename ForwardIterator1, typename ForwardIterator2>
		ForwardIterator1 search(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2);

		template<typename ForwardIterator1, typename ForwardIterator2,
				 typename BinaryPredicate>
		ForwardIterator1 search(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred);

		template<typename ForwardIterator, typename Size, typename T>
		ForwardIterator search_n(
			ForwardIterator first, ForwardIterator last,
			Size count, const T& value);

		template<typename ForwardIterator, typename Size, typename T,
				 typename BinaryPredicate>
		ForwardIterator search_n(
			ForwardIterator first, ForwardIterator last,
			Size count, const T& value, BinaryPredicate pred);



		// 25.2, modifying sequence operations:
		// 25.2.1, copy:
		template<typename InputIterator, typename OutputIterator>
		OutputIterator copy(
			InputIterator first, InputIterator last,
			OutputIterator result);

		template<typename BidirectionalIterator1, typename BidirectionalIterator2>
		BidirectionalIterator2 copy_backward(
			BidirectionalIterator1 first, BidirectionalIterator1 last,
			BidirectionalIterator2 result);


		// 25.2.2, swap:
		template<typename T>
		void swap(T& a, T& b);

		template<typename ForwardIterator1, typename ForwardIterator2>
		ForwardIterator2 swap_ranges(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2);

		template<typename ForwardIterator1, typename ForwardIterator2>
		void iter_swap(ForwardIterator1 a, ForwardIterator2 b);

		template<typename InputIterator, typename OutputIterator,
				 typename UnaryOperation>
		OutputIterator transform(
			InputIterator first, InputIterator last,
			OutputIterator result,
			UnaryOperation op);

		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename BinaryOperation>
		OutputIterator transform(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, OutputIterator result,
			BinaryOperation binary_op);

		template<typename ForwardIterator, typename T>
		void replace(
			ForwardIterator first, ForwardIterator last,
			const T& old_value, const T& new_value);

		template<typename ForwardIterator, typename Predicate, typename T>
		void replace_if(
			ForwardIterator first, ForwardIterator last,
			Predicate pred,
			const T& new_value);

		template<typename InputIterator, typename OutputIterator, typename T>
		OutputIterator replace_copy(
			InputIterator first, InputIterator last,
			OutputIterator result,
			const T& old_value, const T& new_value);

		template<typename Iterator, typename OutputIterator, typename Predicate,
				 typename T>
		OutputIterator replace_copy_if(
			Iterator first, Iterator last,
			OutputIterator result,
			Predicate pred,
			const T& new_value);

		template<typename ForwardIterator, typename T>
		void fill(ForwardIterator first, ForwardIterator last, const T& value);

		template<typename OutputIterator, typename Size, typename T>
		void fill_n(OutputIterator first, Size n, const T& value);

		template<typename ForwardIterator, typename Generator>
		void generate(ForwardIterator first, ForwardIterator last, Generator gen);

		template<typename OutputIterator, typename Size, typename Generator>
		void generate_n(OutputIterator first, Size n, Generator gen);

		template<typename ForwardIterator, typename T>
		ForwardIterator remove(ForwardIterator first, ForwardIterator last,
							   const T& value);

		template<typename ForwardIterator, typename Predicate>
		ForwardIterator remove_if(ForwardIterator first, ForwardIterator last,
								  Predicate pred);

		template<typename InputIterator, typename OutputIterator, typename T>
		OutputIterator remove_copy(
			InputIterator first, InputIterator last,
			OutputIterator result,
			const T& value);

		template<typename InputIterator, typename OutputIterator, typename Predicate>
		OutputIterator remove_copy_if(
			InputIterator first, InputIterator last,
			OutputIterator result,
			Predicate pred);

		template<typename ForwardIterator>
		ForwardIterator unique(ForwardIterator first, ForwardIterator last);

		template<typename ForwardIterator, typename BinaryPredicate>
		ForwardIterator unique(
			ForwardIterator first, ForwardIterator last, BinaryPredicate pred);

		template<typename InputIterator, typename OutputIterator>
		OutputIterator unique_copy(
			InputIterator first, InputIterator last, OutputIterator result);

		template<typename InputIterator, typename OutputIterator,
				 typename BinaryPredicate>
		OutputIterator unique_copy(
			InputIterator first, InputIterator last, OutputIterator result,
			BinaryPredicate pred);

		template<typename BidirectionalIterator>
		void reverse(BidirectionalIterator first, BidirectionalIterator last);

		template<typename BidirectionalIterator, typename OutputIterator>
		OutputIterator reverse_copy(
			BidirectionalIterator first, BidirectionalIterator last,
			OutputIterator result);

		template<typename ForwardIterator>
		void rotate(
			ForwardIterator first, ForwardIterator middle, ForwardIterator last);

		template<typename ForwardIterator, typename OutputIterator>
		OutputIterator rotate_copy(
			ForwardIterator first, ForwardIterator middle, ForwardIterator last,
			OutputIterator result);

		template<typename RandomAccessIterator>
		void random_shuffle(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename RandomNumberGenerator>
		void random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
							RandomNumberGenerator& rand);

		// 25.2.12, partitions:
		template<typename BidirectionalIterator, typename Predicate>
		BidirectionalIterator partition(
			BidirectionalIterator first, BidirectionalIterator last, Predicate pred);

		template<typename BidirectionalIterator, typename Predicate>
		BidirectionalIterator stable_partition(
			BidirectionalIterator first, BidirectionalIterator last, Predicate pred);



		// 25.3, sorting and related operations:
		// 25.3.1, sorting:
		template<typename RandomAccessIterator>
		void sort(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp);

		template<typename RandomAccessIterator>
		void stable_sort(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void stable_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp);

		template<typename RandomAccessIterator>
		void partial_sort(
			RandomAccessIterator first,
			RandomAccessIterator middle,
			RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void partial_sort(
			RandomAccessIterator first,
			RandomAccessIterator middle,
			RandomAccessIterator last,
			Compare comp);

		template<typename InputIterator, typename RandomAccessIterator>
		RandomAccessIterator partial_sort_copy(
			InputIterator first, InputIterator last,
			RandomAccessIterator first2, RandomAccessIterator last2);

		template<typename InputIterator, typename RandomAccessIterator,
				 typename Compare>
		RandomAccessIterator partial_sort_copy(
			InputIterator first, InputIterator last,
			RandomAccessIterator first2, RandomAccessIterator last2,
			Compare comp);

		template<typename RandomAccessIterator>
		void nth_element(
			RandomAccessIterator first,
			RandomAccessIterator nth,
			RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void nth_element(
			RandomAccessIterator first,
			RandomAccessIterator nth,
			RandomAccessIterator last, Compare comp);

		// 25.3.3, binary search:
		template<typename ForwardIterator, typename T>
		ForwardIterator lower_bound(
			ForwardIterator first, ForwardIterator last, const T& value);

		template<typename ForwardIterator, typename T, typename Compare>
		ForwardIterator lower_bound(
			ForwardIterator first, ForwardIterator last, const T& value,
			Compare comp);

		template<typename ForwardIterator, typename T>
		ForwardIterator upper_bound(
			ForwardIterator first, ForwardIterator last, const T& value);

		template<typename ForwardIterator, typename T, typename Compare>
		ForwardIterator upper_bound(
			ForwardIterator first, ForwardIterator last, const T& value,
			Compare comp);


		template<typename ForwardIterator, typename T>
		misc::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const T& value);

		template<typename ForwardIterator, typename T, typename Compare>
		misc::pair<ForwardIterator, ForwardIterator>
		equal_range(ForwardIterator first, ForwardIterator last, const T& value,
					Compare comp);

		template<typename ForwardIterator, typename T>
		bool binary_search(
			ForwardIterator first, ForwardIterator last, const T& value);

		template<typename ForwardIterator, typename T, typename Compare>
		bool binary_search(
			ForwardIterator first, ForwardIterator last, const T& value,
			Compare comp);

		// 25.3.4, merge:
		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator>
		OutputIterator merge(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result);

		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename Compare>
		OutputIterator merge(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp);

		template<typename BidirectionalIterator>
		void inplace_merge(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last);

		template<typename BidirectionalIterator, typename Compare>
		void inplace_merge(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			Compare comp);

		// 25.3.5, set operations:
		template<typename InputIterator1, typename InputIterator2>
		bool includes(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2);


		template<typename InputIterator1, typename InputIterator2, typename Compare>
		bool includes(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator>
		OutputIterator set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename Compare>
		OutputIterator set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp);



		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator>
		OutputIterator set_intersection(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename Compare>
		OutputIterator set_intersection(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator>
		OutputIterator set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result);

		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename Compare>
		OutputIterator set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator>
		OutputIterator set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result);


		template<typename InputIterator1, typename InputIterator2,
				 typename OutputIterator, typename Compare>
		OutputIterator set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator result, Compare comp);


		// 25.3.6, heap operations:
		template<typename RandomAccessIterator>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void push_heap(RandomAccessIterator first, RandomAccessIterator last,
					   Compare comp);

		template<typename RandomAccessIterator>
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void pop_heap(RandomAccessIterator first, RandomAccessIterator last,
					  Compare comp);

		template<typename RandomAccessIterator>
		void make_heap(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void make_heap(RandomAccessIterator first, RandomAccessIterator last,
					   Compare comp);

		template<typename RandomAccessIterator>
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last);

		template<typename RandomAccessIterator, typename Compare>
		void sort_heap(RandomAccessIterator first, RandomAccessIterator last,
					   Compare comp);



		// 25.3.7, minimum and maximum:
		template<typename T>
		const T& (min) (const T& a, const T& b);

		template<typename T, typename Compare>
		const T& (min) (const T& a, const T& b, Compare comp);

		template<typename T>
		const T& (max) (const T& a, const T& b);

		template<typename T, typename Compare>
		const T& (max) (const T& a, const T& b, Compare comp);

		template<typename ForwardIterator>
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last);

		template<typename ForwardIterator, typename Compare>
		ForwardIterator min_element(ForwardIterator first, ForwardIterator last,
									Compare comp);

		template<typename ForwardIterator>
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last);

		template<typename ForwardIterator, typename Compare>
		ForwardIterator max_element(ForwardIterator first, ForwardIterator last,
									Compare comp);

		// 25.3.8
		template<typename InputIterator1, typename InputIterator2>
		bool lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2);

		template<typename InputIterator1, typename InputIterator2, typename Compare>
		bool lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp);

		// 25.3.9, permutations
		template<typename BidirectionalIterator>
		bool next_permutation(
			BidirectionalIterator first, BidirectionalIterator last);

		template<typename BidirectionalIterator, typename Compare>
		bool next_permutation(
			BidirectionalIterator first, BidirectionalIterator last, Compare comp);

		template<typename BidirectionalIterator>
		bool prev_permutation(
			BidirectionalIterator first, BidirectionalIterator last);

		template<typename BidirectionalIterator, typename Compare>
		bool prev_permutation(
			BidirectionalIterator first, BidirectionalIterator last, Compare comp);




		///////////////////////////////////////////////////////////////////////////
		//IMPLEMENTATION
		///////////////////////////////////////////////////////////////////////////


		///////////////////////////////////////////////////////////////////////////
		// 25.1 - Non-modifying sequence operations [lib.alg.nonmodifying]
		// 25.1.1 - For Each [lib.alg.foreach]

		template<typename InputIterator, typename Function>
		inline Function for_each(InputIterator first, InputIterator last, Function f)
		{
			for( ; first!=last; ++first )
			{
				f(*first);
			}

			return f;
		}


		// 25.1.2 - Find [lib.alg.find]
		template<typename InputIterator, typename T>
		inline InputIterator find(
			InputIterator first, InputIterator last, const T& value )
		{
			for( ;first!=last; first++)
			{
				if(*first == value)
				{
					break;
				}
			}
			return first;
		}



		template <typename InputIterator, typename Predicate>
		inline InputIterator find_if(
			InputIterator first, InputIterator last, Predicate pred)
		{
			for( ; first!=last ; first++ )
			{
				if( pred(*first) )
				{
					break;
				}
			}
			return first;
		}



		// 25.1.3 - Find End [lib.alg.find.end]

		template <typename ForwardIterator1, typename ForwardIterator2>
		inline ForwardIterator1 find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator2>::difference_type Dist;

			const Dist dist1 = misc::distance(first2, last2);

			if (!dist1)
				return last1;

			typename misc::iterator_traits<ForwardIterator1>::difference_type
				dist2 = misc::distance(first1, last1);

			ForwardIterator1 res = last1;

			while (dist2 >= dist1)
			{
				if (misc::algobase::equal (first2, last2, first1))
					res  = first1;

				dist2 = misc::distance(++first1, last1);
			}
			return res;
		}


		template <typename ForwardIterator1, typename ForwardIterator2,
				  typename BinaryPredicate>
		inline ForwardIterator1 find_end(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator1>::difference_type Dist;

			const Dist dist1 = misc::distance(first2, last2);

			if (!dist1)
				return last1;
			
			Dist dist2 = misc::distance(first1, last1);

			ForwardIterator1  res = last1;

			while (dist2 >= dist1)
			{
				if (misc::algobase::equal (first2, last2, first1, pred))
					res = first1;

				dist2 = misc::distance(++first1, last1);
			}
			return res;

		}

		// 25.1.4 - Find First [lib.alg.find.first.of]
		template <typename ForwardIterator1, typename ForwardIterator2>
		inline ForwardIterator1 find_first_of(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
		{
			if (first2 == last2)
				return last1;

			for (ForwardIterator1 next = first1; !(next == last1); ++next)
				if (!(misc::algobase::find(first2, last2, *next) == last2))
					return next;

			return last1;
		}


		template <typename ForwardIterator1, typename ForwardIterator2,
				  typename BinaryPredicate>
		inline ForwardIterator1 find_first_of(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2,
			BinaryPredicate pred)
		{
			if (first2 == last2)
				return last1;

			for (ForwardIterator1 next = first1; !(next == last1); ++next)
				for (ForwardIterator2 iter = first2; !(iter == last2); ++iter)
					if (!(pred (*next, *iter) == false))
						return next;

			return last1;
		}



		// 25.1.5 - Adjacent Find [lib.alg.adjacent.find]
		template <typename ForwardIterator>
		inline ForwardIterator adjacent_find(
			ForwardIterator first, ForwardIterator last)
		{
			if (first == last)
				return last;

			for (ForwardIterator next = first; !(++next == last); first = next)
				if (*first == *next)
					return first;

			return last;
		}


		template <typename ForwardIterator, typename BinaryPredicate>
		inline ForwardIterator adjacent_find(
			ForwardIterator first, ForwardIterator last,
			BinaryPredicate pred)
		{
			if (first == last)
				return last;

			for (ForwardIterator next = first; !(++next == last); first = next)
				if (!(pred (*first, *next) == false))
					return first;

			return last;
		}


		// 25.1.6 - Count [lib.alg.count]
		template <typename InputIterator, typename TypeT>
		inline typename misc::iterator_traits<InputIterator>::difference_type
		count(InputIterator first, InputIterator last, const TypeT &val)
		{
			typedef typename
				misc::iterator_traits<InputIterator>::difference_type Dist;

			Dist n = 0;
			for ( ; !(first == last); ++first)
				if (*first == val)
					++n;
			return n;
		}


		template <typename InputIterator, typename Predicate>
		inline typename misc::iterator_traits<InputIterator>::difference_type
		count_if(InputIterator first, InputIterator last, Predicate pred)
		{
			typedef typename
				misc::iterator_traits<InputIterator>::difference_type Dist;

			Dist n = 0;
			for ( ; !(first == last); ++first)
				if (!(pred (*first) == false))
					++n;
			return n;
		}


		template <typename InputIterator, typename TypeT, typename Size>
		inline void count(
			InputIterator first, InputIterator last, const TypeT &val, Size& n)
		{
			for ( ; !(first == last); ++first)
				if (*first == val)
					++n;
		}


		template <typename InputIterator, typename Predicate, typename Size>
		inline void count_if(
			InputIterator first, InputIterator last, Predicate pred, Size& n)
		{
			for ( ; !(first == last); ++first)
				if (!(pred (*first) == false))
					++n;
		}


		// 25.1.7 - Mismatch [lib.mismatch]
		template <typename InputIterator1, typename InputIterator2>
		inline misc::pair<InputIterator1, InputIterator2> mismatch(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (!(first1 == last1) && *first1 == *first2)
			{
				++first1;
				++first2;
			}
			return misc::pair<InputIterator1, InputIterator2> (first1, first2);
		}


		template <typename InputIterator1, typename InputIterator2,
				  typename BinaryPredicate>
		inline misc::pair<InputIterator1, InputIterator2> mismatch(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			BinaryPredicate pred)
		{
			while (!(first1 == last1)
				   && !(pred (*first1, *first2) == false))
			{
				++first1;
				++first2;
			}
			return misc::pair<InputIterator1, InputIterator2> (first1, first2);
		}


		// 25.1.8 - Equal [lib.alg.equal]
		template <typename InputIterator1, typename InputIterator2>
		inline bool equal(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2)
		{
			return last1 == misc::algobase::mismatch (first1, last1, first2).first;
		}


		template <typename InputIterator1, typename InputIterator2,
				  typename BinaryPredicate>
		inline bool equal(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2,
			BinaryPredicate pred)
		{
			return
				last1 == misc::algobase::mismatch(first1, last1, first2, pred).first;
		}


		// 25.1.9 - Search [lib.alg.search]

		// 25.1.9, p1
		template <typename ForwardIterator1, typename ForwardIterator2>
		inline ForwardIterator1 search(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2, ForwardIterator2 last2)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator1>::difference_type Dist1;

			typedef typename
				misc::iterator_traits<ForwardIterator2>::difference_type Dist2;

			Dist1 dist1 = misc::distance(first1, last1);
			Dist2 dist2 = misc::distance(first2, last2);

			if (dist1 < dist2)
				return last1;

			ForwardIterator1 cur1 = first1;
			ForwardIterator2 cur2 = first2;

			while (!(cur2 == last2))
			{
				if (!(*cur1 == *cur2))
				{
					++cur1;
					++cur2;
					if (dist1-- == dist2)
						return last1;

					cur1 = ++first1;
					cur2 = first2;
				}
				else
				{
					++cur1;
					++cur2;
				}
			}

			return (cur2 == last2) ? first1 : last1;
		}


		template <typename ForwardIterator1, typename ForwardIterator2,
				  typename BinaryPredicate>
		inline ForwardIterator1 search(
			ForwardIterator1 first1,ForwardIterator1 last1,
			ForwardIterator2 first2,ForwardIterator2 last2,
			BinaryPredicate pred)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator1>::difference_type Dist1;

			typedef typename
				misc::iterator_traits<ForwardIterator2>::difference_type Dist2;


			Dist1 dist1 = misc::distance(first1, last1);
			Dist2 dist2 = misc::distance(first2, last2);

			if (dist1 < dist2) return last1;

			ForwardIterator1 cur1 = first1;
			ForwardIterator2 cur2 = first2;

			while (!(cur2 == last2))
			{
				if (pred (*cur1, *cur2) == false)
				{
					++cur1;
					++cur2;
					if (dist1-- == dist2)
						return last1;

					cur1 = ++first1;
					cur2 = first2;
				}
				else
				{
					++cur1;
					++cur2;
				}
			}

			return (cur2 == last2) ? first1 : last1;
		}



		 // 25.1.9, p4
		template <typename ForwardIterator, typename Size, typename TypeT>
		inline ForwardIterator search_n(
			ForwardIterator first, ForwardIterator last,
			Size count,
			const TypeT &value)
		{
			if (count)
			{
				typedef typename
					misc::iterator_traits<ForwardIterator>::difference_type Dist;

				if (count <= 0)
					return last;

				const Dist dist = misc::distance(first, last);

				if (dist < Dist (count))
					return last;

				Dist span    = dist - Dist (count);
				Dist matches = 0;

				ForwardIterator current = first;

				while (!(current == last))
				{
					if (!(*current == value))
					{
						if (span < matches + 1)
							return last;
						span   -= matches + 1;
						matches = 0;
						first   = ++current;
					}
					else
					{
						if (++matches == Dist (count))
							return first;
						++current;
					}
				}

				return last;
			}
			return first;
		}


		template <typename ForwardIterator, typename Size, typename TypeT,
				  typename BinaryPredicate>
		inline ForwardIterator search_n(
			ForwardIterator first, ForwardIterator last,
			Size count,
			const TypeT &value,
			BinaryPredicate pred)
		{
			if(count)
			{
				typedef typename
					misc::iterator_traits<ForwardIterator>::difference_type Dist;


				const Dist dist = misc::distance(first, last);
				const ptrdiff_t int_count = count; //check the type

				if (dist < int_count || int_count <= 0)
					return last;

				Dist span       = dist - int_count;
				Dist matches    = 0;
				ForwardIterator current = first;

				while (!(current == last))
				{
					if (pred (*current, value) == false)
					{
						if (span < matches + 1)
							return last;
						span   -= matches + 1;
						matches = 0;
						first   = ++current;
					}
					else
					{
						if (++matches == count)
							return first;
						++current;
					}
				}

				return last;

			}
			return first;
		}


		// 25.2 - Mutating sequence operations [lib.alg.modifying,operations]

		// 25.2.1 - Copy [lib.alg.copy]
		template <typename InputIterator, typename OutputIterator>
		inline OutputIterator copy(
			InputIterator first, InputIterator last, OutputIterator res)
		{
			for (; !(first == last); ++first, ++res)
				*res = *first;
			return res;
		}


		// 25.2.1, p5
		template <typename BidirectionalIterator1, typename BidirectionalIterator2>
		inline BidirectionalIterator2 copy_backward(
			BidirectionalIterator1 first, BidirectionalIterator1 last,
			BidirectionalIterator2 res)
		{
			while (!(first == last))
				*--res = *--last;
			return res;
		}

		// 25.2.2, p1 swap
		template <typename TypeT>
		inline void swap(TypeT& a, TypeT& b)
		{
			TypeT tmp = a;
			a = b;
			b = tmp;
		}


		template <typename ForwardIterator1, typename ForwardIterator2>
		inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
		{
			misc::algobase::swap(*a, *b);
		}

		// 25.2.2, p3
		template <typename ForwardIterator1, typename ForwardIterator2>
		inline ForwardIterator2 swap_ranges(
			ForwardIterator1 first1, ForwardIterator1 last1,
			ForwardIterator2 first2)
		{
			for (; !(first1 == last1); ++first1, ++first2)
				misc::algobase::iter_swap(first1, first2);
			return first2;
		}


		// 25.2.3 - Transform [lib.alg.transform]
		template <typename InputIterator, typename OutputIterator,
				  typename UnaryOperation>
		inline OutputIterator transform(
			InputIterator first, InputIterator last,
			OutputIterator res,
			UnaryOperation unary_op)
		{
			for (; !(first == last); ++res, ++first)
				*res = unary_op (*first);
			return res;
		}


		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename BinaryOperation>
		inline OutputIterator transform(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, OutputIterator res,
			BinaryOperation binary_op)
		{
			for (; !(first1 == last1); ++res, ++first1, ++first2)
				*res = binary_op (*first1, *first2);
			return res;
		}


		// 25.2.4 - Replace [lib.alg.replace]
		template <typename ForwardIterator, typename TypeT>
		inline void replace(
			ForwardIterator first, ForwardIterator last,
			const TypeT& old_value, const TypeT& new_value)
		{
			for (; !(first == last); ++first)
			{
				if (*first == old_value)
				{
					*first = new_value;
				}
			}
		}


		template <typename ForwardIterator, typename Predicate, typename TypeT>
		inline void replace_if(
			ForwardIterator first, ForwardIterator last,
			Predicate pred,
			const TypeT& new_value)
		{
			for (; !(first == last); ++first)
			{
				if (!(pred (*first) == false))
				{
					*first = new_value;
				}
			}
		}


		template <typename InputIterator, typename OutputIterator, typename TypeT>
		inline OutputIterator replace_copy(
			InputIterator first, InputIterator last,
			OutputIterator res,
			const TypeT& old_value, const TypeT& new_value)
		{
			for (; !(first == last); ++first, ++res)
			{
				*res = *first == old_value ? new_value : *first;
			}
			return res;
		}


		template <typename Iterator, typename OutputIterator,
				  typename Predicate, typename TypeT>
		inline OutputIterator replace_copy_if(
			Iterator first, Iterator last,
			OutputIterator res,
			Predicate pred,
			const TypeT& new_value)
		{
			for (; !(first == last); ++res, ++first)
			{
				*res = pred (*first) == false ? *first : new_value;
			}

			return res;
		}


		// 25.2.5 - Fill [lib.alg.fill]
		template <typename ForwardIterator, typename TypeT>
		inline void fill(ForwardIterator first, ForwardIterator last, TypeT& val)
		{
			for ( ; !(first == last); ++first)
			{
				*first = val;
			}
		}


		template <typename OutputIterator, typename Size, typename TypeT>
		inline void fill_n(OutputIterator first, Size n, const TypeT &val)
		{
			for (ptrdiff_t inx = n; 0 < inx; --inx, ++first)
			{
				*first = val;
			}
		}



		// 25.2.6 - Generate [lib.alg.generate]
		template <typename ForwardIterator, typename Generator>
		inline void generate(
			ForwardIterator first, ForwardIterator last, Generator gen)
		{
			for (; !(first == last); ++first)
			{
				*first = gen ();
			}
		}


		template <typename OutputIterator, typename Size, typename Generator>
		inline void generate_n(OutputIterator first, Size n, Generator gen)
		{
			for(ptrdiff_t inx = n; 0 < inx; --inx, ++first)
			{
				*first = gen ();
			}
		}


		// 25.2.7 - Remove [lib.alg.remove]
		template <typename InputIterator, typename OutputIterator, typename TypeT>
		inline OutputIterator remove_copy(
			InputIterator first, InputIterator last,
			OutputIterator res,
			const TypeT& value)
		{
			for (; !(first == last); ++first)
			{
				if (!(*first == value))
				{
					*res = *first;
					++res;
				}
			}
			return res;
		}



		template <typename InputIterator, typename OutputIterator,
				  typename Predicate>
		inline OutputIterator remove_copy_if(
			InputIterator first, InputIterator last,
			OutputIterator res,
			Predicate pred)
		{
			for (; !(first == last); ++first)
			{
				if (pred (*first) == false)
				{
					*res = *first;
					++res;
				}
			}
			return res;
		}



		template <typename ForwardIterator, typename TypeT>
		inline ForwardIterator remove(
			ForwardIterator first, ForwardIterator last,
			const TypeT &value)
		{
			first = misc::algobase::find(first, last, value);
			ForwardIterator next = first;
			return first == last ?
				first : misc::algobase::remove_copy(++next, last, first, value);
		}


		template <typename ForwardIterator, typename Predicate>
		inline ForwardIterator remove_if(
			ForwardIterator first, ForwardIterator last, Predicate pred)
		{
			first = misc::algobase::find_if(first, last, pred);
			ForwardIterator next = first;
			return first == last ?
				first : misc::algobase::remove_copy_if(++next, last, first, pred);
		}


		template <typename InputIterator, typename ForwardIterator>
		inline ForwardIterator unique_copy(
			InputIterator first, InputIterator last,
			ForwardIterator res,
			misc::forward_iterator_tag)
		{
			if (first == last)
				return res;

			*res = *first;
			while (!(++first == last))
			{
				if (!(*res == *first))
					*++res = *first;
			}
			return ++res;
		}


		template <typename InputIterator, typename BidirectionalIterator>
		inline BidirectionalIterator unique_copy(
			InputIterator first, InputIterator last,
			BidirectionalIterator res,
			misc::bidirectional_iterator_tag)
		{
			return misc::algobase::unique_copy(
				first, last, res, misc::forward_iterator_tag());
		}


		template <typename InputIterator, typename RandomAccessIterator>
		inline RandomAccessIterator unique_copy(
			InputIterator first, InputIterator last,
			RandomAccessIterator res,
			misc::random_access_iterator_tag)
		{
			return misc::algobase::unique_copy(
				first, last, res, misc::forward_iterator_tag());
		}


		template <typename InputIterator, typename OutputIterator>
		inline OutputIterator unique_copy(
			InputIterator first, InputIterator last,
			OutputIterator res,
			misc::output_iterator_tag)
		{
			typedef typename misc::iterator_traits<InputIterator>::value_type TypeT;

			if (first == last)
				return res;

			TypeT value = *first;

			for (*res = value; !(++first == last); )
			{
				if (!(value == *first))
				{
					value = *first;
					*++res = value;
				}
			}

			return ++res;
		}



		template <typename InputIterator, typename ForwardIterator,
				  typename BinaryPredicate>
		inline ForwardIterator unique_copy(
			InputIterator first, InputIterator last,
			ForwardIterator res,
			BinaryPredicate pred,
			misc::forward_iterator_tag)
		{
			if (first == last)
				return res;

			for (*res = *first; !(++first == last); )
			{
				if (pred (*res, *first) == false)
				{
					*++res = *first;
				}
			}

			return ++res;
		}





		template <typename InputIterator, typename BidirectionalIterator,
				  typename BinaryPredicate>
		inline BidirectionalIterator unique_copy(
			InputIterator first, InputIterator last,
			BidirectionalIterator res,
			BinaryPredicate pred,
			misc::bidirectional_iterator_tag)
		{
			return misc::algobase::unique_copy(
				first, last, res, pred, misc::forward_iterator_tag());
		}


		template <typename InputIterator, typename RandomAccessIterator,
				  typename BinaryPredicate>
		inline RandomAccessIterator unique_copy(
			InputIterator first, InputIterator last,
			RandomAccessIterator res,
			BinaryPredicate pred,
			misc::random_access_iterator_tag)
		{
			return misc::algobase::unique_copy(
				first, last, res, pred, misc::forward_iterator_tag());
		}


		template <typename InputIterator, typename OutputIterator,
				  typename BinaryPredicate>
		inline OutputIterator unique_copy(
			InputIterator first, InputIterator last,
			OutputIterator res,
			BinaryPredicate pred,
			misc::output_iterator_tag)
		{
			typedef typename misc::iterator_traits<InputIterator>::value_type TypeT;

			if (first == last)
				return res;

			TypeT value = *first;

			for (*res = value; !(++first == last); )
			{
				if (pred (value, *first) == false)
				{
					value = *first;
					*++res = value;
				}
			}

			return ++res;
		}


		// 25.2.8 - Unique   [lib.alg.unique]
		template <typename ForwardIterator>
		inline ForwardIterator unique(ForwardIterator first, ForwardIterator last)
		{
			first = misc::algobase::adjacent_find(first, last);

			if (first == last)
				return first;

			ForwardIterator next = ++first;

			while (!(++next == last))
			{
				if (!(*next == *first))
					break;
			}

			return misc::algobase::unique_copy
				(next, last, first,
				 misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		template <typename ForwardIterator, typename BinaryPredicate>
		inline ForwardIterator unique(
			ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
		{
			first = misc::algobase::adjacent_find (first, last, pred);

			if (first == last)
				return first;

			ForwardIterator next = ++first;

			while (!(++next == last))
			{
				if (pred (*next, *first) == false)
					break;
			}                

			return misc::algobase::unique_copy
				(next, last, first, pred,
				 misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		template <typename InputIterator, typename OutputIterator>
		inline OutputIterator unique_copy(
			InputIterator first, InputIterator last, OutputIterator res)
		{
			return  misc::algobase::unique_copy
				(first, last, res,
				 misc::iterator_traits<OutputIterator>::iterator_category());
		}


		template <typename InputIterator, typename OutputIterator,
				  typename BinaryPredicate>
		inline OutputIterator unique_copy(
			InputIterator first, InputIterator last, OutputIterator res,
			BinaryPredicate pred)
		{
			return misc::algobase::unique_copy(
				first, last, res, pred,
				misc::iterator_traits<OutputIterator>::iterator_category());
		}


		template <typename BidirectionalIterator>
		inline void reverse(
			BidirectionalIterator first, BidirectionalIterator last,
			misc::bidirectional_iterator_tag)
		{
			for (; !(first == last) && !(first == --last); ++first)
			{
				misc::algobase::iter_swap(first, last);
			}
		}


		template <typename RandomAccessIterator>
		inline void reverse(
			RandomAccessIterator first, RandomAccessIterator last,
			misc::random_access_iterator_tag)
		{
			if (!(first == last))
			{
				for (; first < --last; ++first)
				{
					misc::algobase::iter_swap(first, last);
				}
			}
		}


		template <typename BidirectionalIterator>
		inline void reverse(BidirectionalIterator first, BidirectionalIterator last)
		{
			misc::algobase::reverse(first, last,
					typename
						misc::iterator_traits<BidirectionalIterator>::iterator_category());
		}


		template <typename BidirectionalIterator, typename OutputIterator>
		inline OutputIterator reverse_copy(
			BidirectionalIterator first, BidirectionalIterator last,
			OutputIterator res)
		{
			for (; !(first == last); ++res)
			{
				*res = *--last;
			}
			return res;
		}


		//specialization of rotate (e.g. forward_iterator_tag)
		template <typename ForwardIterator>
		inline void rotate(
			ForwardIterator first, ForwardIterator middle, ForwardIterator last,
			misc::forward_iterator_tag)
		{
			for (ForwardIterator i = middle; ; )
			{
				misc::algobase::iter_swap (first, i);
				++i;
				if (++first == middle)
				{
					if (i == last)
						return;
					middle = i;
				}
				else if (i == last)
				{
					i = middle;
				}
			}
		}



		//specialization of rotate (e.g. bidirectional_iterator_tag)
		template <typename BidirectionalIterator>
		inline void rotate(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			misc::bidirectional_iterator_tag)
		{
			misc::algobase::reverse(first, middle);
			misc::algobase::reverse(middle, last);
			misc::algobase::reverse(first, last);
		}


		template <typename EuclideanRingElement>
		inline EuclideanRingElement gcd(
			EuclideanRingElement m, EuclideanRingElement n)
		{
			while (!(n == EuclideanRingElement ()))
			{
				const EuclideanRingElement r = m % n;
				m = n;
				n = r;
			}
			return m;
		}




		template <typename RandomAccessIterator, typename Dist>
			inline void rotate_cycle(
				RandomAccessIterator first, RandomAccessIterator last,
				RandomAccessIterator first2,
				Dist shift)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::value_type TypeT;

			const TypeT value = *first2;
			RandomAccessIterator it1 = first2;

			for (RandomAccessIterator it2 = it1 + shift; !(it2 == first2); )
			{
				*it1 = *it2;
				it1  = it2;

				if (last - it2 > shift)
				{
					it2 += shift;
				}
				else
				{
					it2 = first + (shift - (last - it2));
				}
			}

			*it1 = value;
		}



		//specialization of rotate (e.g. random_access_iterator_tag)
		template <typename RandomAccessIterator>
		inline void rotate(
			RandomAccessIterator first,
			RandomAccessIterator middle,
			RandomAccessIterator last,
			misc::random_access_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			for (Dist n = gcd (last - first, middle - first); n--; )
				misc::algobase::rotate_cycle(first, last, first + n, middle - first);
		}



		template <typename ForwardIterator>
		inline void rotate(
			ForwardIterator first, ForwardIterator middle, ForwardIterator last)
		{
			if (!(first == middle || middle == last))
			{
				misc::algobase::rotate(first, middle, last,
					typename misc::iterator_traits<ForwardIterator>::iterator_category());
			}
		}


		template <typename ForwardIterator, typename OutputIterator>
		inline OutputIterator rotate_copy(
			ForwardIterator first, ForwardIterator middle, ForwardIterator last,
			OutputIterator res)
		{
			return misc::algobase::copy(first, middle,
				misc::algobase::copy (middle, last, res));
		}


		template <typename RandomAccessIterator, typename RandomNumberGenerator>
		inline void random_shuffle(
			RandomAccessIterator first, RandomAccessIterator last,
			RandomNumberGenerator& rand)
		{
			if (!(first == last))
			{
				typename misc::iterator_traits<RandomAccessIterator>::difference_type
					limit = 2;

				for (RandomAccessIterator i = first; !(++i == last); ++limit)
				{
					const typename
						misc::iterator_traits<RandomAccessIterator>::difference_type
						rndoff(rand(limit));
					misc::algobase::iter_swap (i, first + rndoff);
				}
			}
		}


		template <typename RandomAccessIterator>
		inline void random_shuffle(
			RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::random_shuffle(first, last, ::rand());
		}


		template <typename BidirectionalIterator, typename Predicate>
		inline BidirectionalIterator partition(
			BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
		{
			for ( ; ; ++first)
			{
				for ( ; ; )
				{
					if (first == last)
						return first;
					if (!(pred (*first) == false))
						++first;
					else
						break;
				}

				for (--last; ; )
				{
					if (first == last)
						return first;
					if (pred (*last) == false)
						--last;
					else
						break;
				}
				misc::algobase::iter_swap (first, last);
			}
		}





		//part of stable_partition
		template <typename BidirectionalIterator, typename Predicate, typename Dist>
		inline BidirectionalIterator inplace_stable_partition(
			BidirectionalIterator first, BidirectionalIterator last,
			Predicate pred,
			Dist dist)
		{
			if (dist == 1)
				return !(pred (*first) == false) ? last : first;

			BidirectionalIterator middle = first;
			misc::advance(middle, dist / 2);
			BidirectionalIterator first_cut =
				misc::algobase::inplace_stable_partition(
					first, middle, pred, dist/2);

			BidirectionalIterator second_cut =
				misc::algobase::inplace_stable_partition(
					middle, last, pred, dist-dist/2);

			misc::algobase::rotate (first_cut, middle, second_cut);
			dist = misc::distance(middle, second_cut);
			misc::advance (first_cut, dist);
			return first_cut;
		}


		template <typename BidirectionalIterator, typename Pointer,
				  typename Predicate, typename Dist, typename TypeT>
		inline BidirectionalIterator stable_partition_adaptive(
			BidirectionalIterator first, BidirectionalIterator last,
			Predicate pred,
			Dist dist,
			Pointer buf,
			Dist buf_size,
			Dist& fill_pointer,
			TypeT*)
		{
			if (dist <= buf_size)
			{
				dist = 0;
				BidirectionalIterator res1 = first;
				Pointer res2 = buf;
				for (; !(first == last) && dist < fill_pointer; ++first)
				{
					if (!(pred (*first) == false))
					{
						*res1 = *first;
						++res1;
					}
					else
					{
						*res2 = *first;
						++res2;
						++dist;
					}
				}

				if (!(first == last))
				{
					misc::raw_storage_iterator<Pointer, TypeT> res3 (res2);
					for (; !(first == last); ++first)
					{
						if (!(pred (*first) == false))
						{
							*res1 = *first;
							++res1;
						}
						else
						{
							*res3 = *first;
							++res3;
							++dist;
						}
					}
					fill_pointer = dist;
				}
				misc::algobase::copy (buf, buf + dist, res1);
				return res1;
			}
			BidirectionalIterator middle = first;
			misc::advance (middle, dist / 2);

			BidirectionalIterator first_cut =
				misc::algobase::stable_partition_adaptive(
					first, middle, pred, Dist(dist/2), buf, buf_size, fill_pointer,
					(TypeT*)0);

			BidirectionalIterator second_cut =
				misc::algobase::stable_partition_adaptive(
					middle, last, pred, Dist(dist - dist/2), buf, buf_size,
					fill_pointer, (TypeT*)0);

			misc::algobase::rotate (first_cut, middle, second_cut);
			dist = misc::distance(middle, second_cut);
			misc::advance (first_cut, dist);
			return first_cut;
		}


		template <typename BidirectionalIterator, typename Predicate>
		inline BidirectionalIterator stable_partition(
			BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
		{
			typedef typename
				misc::iterator_traits<BidirectionalIterator>::value_type TypeT;
			typedef typename
				misc::iterator_traits<BidirectionalIterator>::difference_type Dist;


			const Dist dist = misc::distance<BidirectionalIterator>(first, last);

			if (!dist)
				return last;

			misc::pair<TypeT*, Dist> pair = misc::get_temporary_buffer<TypeT>(dist);

			if (pair.first == 0)
				return
					misc::algobase::inplace_stable_partition(first, last, pred, dist);

			Dist fill = 0;

			const BidirectionalIterator res =
				misc::algobase::stable_partition_adaptive(
					first, last, pred, dist, pair.first, pair.second, fill, (TypeT*)0);

			for (TypeT *ptr = pair.first + fill; !(pair.first == ptr--); )
				(*ptr).~TypeT ();

			misc::return_temporary_buffer (pair.first);

			return res;

		}


		// 25.3.1 - Sorting [lib.alg.sort]
		template <typename RandomAccessIterator, typename TypeT, typename Compare>
		inline RandomAccessIterator unguarded_partition(
			RandomAccessIterator first, RandomAccessIterator last,
			TypeT pivot,
			Compare comp)
		{
			for ( ; ; ++first)
			{
				for (; comp (*first, pivot); ++first);

				while (comp (pivot, *--last));

				if (!(first < last))
					return first;

				misc::algobase::iter_swap (first, last);
			}
		}


		template <typename TypeT, typename Compare>
		inline const TypeT& median(
			const TypeT& a, const TypeT& b, const TypeT& c, Compare comp)
		{
			return comp (a, b)
				? comp (b, c) ? b : comp (a, c) ? c : a
				: comp (a, c) ? a : comp (b, c) ? c : b;
		}

		enum { qs_threshold = 16 };

		template <typename RandomAccessIterator, typename TypeT, typename Compare>
		inline void unguarded_linear_insert(
			RandomAccessIterator last, TypeT value, Compare comp)
		{
			for(RandomAccessIterator next = last; comp (value, *--next); )
			{
				*last = *next;
				last = next;
			}
			*last = value;
		}


		template <typename RandomAccessIterator>
		inline void linear_insert(
			RandomAccessIterator first,
			RandomAccessIterator last)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::value_type TypeT;

			const TypeT value = *last;

			if (value < *first)
			{
				misc::algobase::copy_backward (first, last, last + 1);
				*first = value;
			}
			else
			{
				misc::algobase::unguarded_linear_insert(
					last, value,
					misc::less<
					typename
					misc::iterator_traits<RandomAccessIterator>::value_type>());
			}
		}




		template <typename RandomAccessIterator, typename Compare>
		inline void linear_insert(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Compare comp)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::value_type TypeT;

			const TypeT value = *last;

			if (comp (value, *first))
			{
				misc::algobase::copy_backward(first, last, last + 1);
				*first = value;
			}
			else
			{
				misc::algobase::unguarded_linear_insert(last, value, comp);
			}
		}




		template <typename RandomAccessIterator, typename Compare>
		inline void insertion_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (! (first == last))
			{
				for (RandomAccessIterator i = first + 1; !(i == last); ++i)
				{
					misc::algobase::linear_insert(first, i, comp);
				}
			}
		}





		template <typename RandomAccessIterator, typename Compare>
		inline void unguarded_insertion_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			for(RandomAccessIterator i = first; !(i == last); ++i)
				misc::algobase::unguarded_linear_insert(i, *i, comp);
		}


		// David R. Musser's Introspective Sorting algorithm
		// (see www.cs.rpi.edu/~musser/gp/introsort.ps)
		// O(N * log (N)) worst case complexity
		template <typename RandomAccessIterator, typename Dist, typename Compare>
		inline void introsort_loop(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Dist max_depth,
			Compare comp)
		{
			for ( ; qs_threshold < last - first; )
			{
				if (0 == max_depth)
				{
					misc::algobase::partial_sort(first, last, last, comp);
					break;
				}

				RandomAccessIterator cut =
					misc::algobase::unguarded_partition(
						first,
						last,
						misc::algobase::median(
							*first,
							*(first + (last - first) /2),
							*(last - 1),
							comp),
						comp);

				// limit the depth of the recursion tree to log2 (last - first)
				// where first and last are the initial values passed in from sort()
				misc::algobase::introsort_loop(cut, last, max_depth /= 2, comp);
				last = cut;
			}
		}


		template <typename RandomAccessIterator, typename Compare>
		inline void final_insertion_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (last - first > qs_threshold)
			{
				misc::algobase::insertion_sort(first, first + qs_threshold, comp);

				misc::algobase::unguarded_insertion_sort(
					first + qs_threshold, last, comp);
			}
			else
			{
				misc::algobase::insertion_sort (first, last, comp);
			}
		}




		// 25.3.1.1
		template <typename RandomAccessIterator, typename Compare>
		inline void sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (!(first == last))
			{
				// introsort guarantees O(N * log(N)) in the worst case
				misc::algobase::introsort_loop (first, last, last - first, comp);
				misc::algobase::final_insertion_sort (first, last, comp);
			}
		}


		template <typename RandomAccessIterator>
		inline void sort(RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::sort(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}


		template <typename BidirectionalIterator, typename Dist, typename Compare>
		inline void merge_without_buffer(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			Dist dist1,
			Dist dist2,
			Compare comp)
		{
			if (dist1 == 0 || dist2 == 0)
				return;

			if (dist1 + dist2 == 2)
			{
				if (comp (*middle, *first))
					misc::algobase::iter_swap (first, middle);
				return;
			}

			BidirectionalIterator first_cut = first;
			BidirectionalIterator second_cut = middle;
			Dist dist11;
			Dist dist22;

			if (dist1 > dist2)
			{
				dist11 = dist1 / 2;

				misc::advance (first_cut, dist11);

				second_cut = misc::algobase::lower_bound(
					middle, last, *first_cut, comp);

				dist22 = misc::distance(middle, second_cut);
			}
			else
			{
				dist22 = dist2 / 2;

				misc::advance (second_cut, dist22);
				first_cut = misc::algobase::upper_bound(
					first, middle, *second_cut, comp);

				dist11 = misc::distance(first, first_cut);
			}

			misc::algobase::rotate (first_cut, middle, second_cut);

			BidirectionalIterator middle2 = first_cut;

			misc::advance (middle2, dist22);

			misc::algobase::merge_without_buffer(
				first, first_cut, middle2, dist11, dist22, comp);

			misc::algobase::merge_without_buffer(
				middle2, second_cut, last, dist1 - dist11, dist2 - dist22, comp);
		}




		template <typename RandomAccessIterator, typename Compare>
		inline void inplace_stable_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (last - first < 15)
			{
				misc::algobase::insertion_sort (first, last, comp);
			}
			else
			{
				RandomAccessIterator middle = first + (last - first) / 2;
				misc::algobase::inplace_stable_sort(first, middle, comp);
				misc::algobase::inplace_stable_sort(middle, last, comp);
				misc::algobase::merge_without_buffer(
					first, middle, last, middle - first, last - middle, comp);
			}
		}


		template <typename RandomAccessIter1, typename RandomAccessIter2,
				  typename Dist, typename Compare>
		inline void merge_sort_loop(
			RandomAccessIter1 first,
			RandomAccessIter1 last,
			RandomAccessIter2 res,
			Dist step,
			Compare comp)
		{
			const Dist two_step = 2 * step;

			while (last - first >= two_step)
			{
				res = misc::algobase::merge(
					first, first + step, first + step, first + two_step, res, comp);

				first += two_step;
			}

			step = misc::algobase::min(Dist (last - first), step);

			misc::algobase::merge(first, first+step, first+step, last, res, comp);
		}


		template <typename RandomAccessIterator, typename Dist, typename Compare>
		inline void chunk_insertion_sort(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Dist chunk_size,
			Compare comp)
		{
			while (last - first >= chunk_size)
			{
				misc::algobase::insertion_sort (first, first + chunk_size, comp);
				first += chunk_size;
			}
			misc::algobase::insertion_sort (first, last, comp);
		}


		template <typename RandomAccessIterator, typename Pointer, typename Compare>
		inline void merge_sort_with_buffer(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Pointer buf,
			Compare comp)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			const Dist dist  = last - first;
			const Pointer bufend = buf + dist;

			Dist step = 7;   // STL chunk size

			misc::algobase::chunk_insertion_sort(first, last, step, comp);

			while (step < dist)
			{
				misc::algobase::merge_sort_loop(first, last, buf, step, comp);
				step *= 2;
				misc::algobase::merge_sort_loop(buf, bufend, first, step, comp);
				step *= 2;
			}
		}


		//declare in advance

		template <typename BidirectionalIterator, typename Dist,
				  typename Pointer, typename Compare>
		inline void merge_adaptive(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			Dist dist1,
			Dist dist2,
			Pointer buf,
			Dist buf_size,
			Compare comp);



		template <typename RandomAccessIterator, typename Pointer, typename Dist,
			typename Compare>
		inline void stable_sort_adaptive(
			RandomAccessIterator first,
			RandomAccessIterator last,
			Pointer buf,
			Dist buf_size,
			Compare comp)
		{
			const Dist dist = (last - first + 1) / 2;
			const RandomAccessIterator middle = first + dist;

			if (dist > buf_size)
			{
				misc::algobase::stable_sort_adaptive(
					first, middle, buf, buf_size, comp);

				misc::algobase::stable_sort_adaptive(
					middle, last, buf, buf_size, comp);
			}
			else
			{
				misc::algobase::merge_sort_with_buffer(
					first, middle, buf, comp);

				misc::algobase::merge_sort_with_buffer(
					middle, last, buf, comp);
			}

			misc::algobase::merge_adaptive(
				first, middle, last,
				Dist (middle - first),
				Dist (last - middle), buf, buf_size, comp);
		}


		// 25.3.1.2
		template <typename RandomAccessIterator, typename Compare>
		inline void stable_sort(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (!(first == last))
			{
				typedef typename
					misc::iterator_traits<RandomAccessIterator>::value_type TypeT;

				typedef typename
					misc::iterator_traits<RandomAccessIterator>::difference_type Dist;


				//call an extension of get_temporary_buffer<>() in case partial
				//typename specialization (and iterator_traits<>) isn't supported
				//by compiler
				misc::pair<TypeT*, Dist> p =
					misc::get_temporary_buffer<TypeT>(Dist(last - first));

				if (p.first == 0)
				{
					misc::algobase::inplace_stable_sort (first, last, comp);
				}
				else
				{
					Dist len = misc::algobase::min(Dist(p.second), Dist(last - first));
					misc::algobase::copy(
						first, first + len,
						misc::raw_storage_iterator<TypeT*, TypeT>(p.first));

					misc::algobase::stable_sort_adaptive(
						first, last, p.first, p.second, comp);

					for (TypeT *ptr = p.first + len; !(p.first == --ptr); )
						(*ptr).~TypeT ();

					misc::return_temporary_buffer (p.first);
				}
			}
		}


		template <typename RandomAccessIterator>
		inline void stable_sort(
			RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::stable_sort(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}



		//declared in advance
		template <typename RandomAccessIterator, typename TypeT, typename Compare>
			inline void pop_heap2(
				RandomAccessIterator first,
				RandomAccessIterator last,
				RandomAccessIterator res,
				TypeT value,
				Compare cmp);


		// 25.3.1.3
		template <typename RandomAccessIterator, typename Compare>
		inline void partial_sort(
			RandomAccessIterator first,
			RandomAccessIterator middle,
			RandomAccessIterator last,
			Compare comp)
		{
			if (!(first == middle))
			{
				misc::algobase::make_heap (first, middle, comp);

				for (RandomAccessIterator i = middle; i < last; ++i)
				{
					if (comp (*i, *first))
					{
						misc::algobase::pop_heap2(first, middle, i, *i, comp);
					}
				}

				misc::algobase::sort_heap (first, middle, comp);
			}
		}



		template <typename RandomAccessIterator>
		inline void partial_sort(
			RandomAccessIterator first,
			RandomAccessIterator middle,
			RandomAccessIterator last)
		{

			misc::algobase::partial_sort(
				first, middle, last,
				misc::less<
				typename misc::iterator_traits<RandomAccessIterator>::value_type>());
		}


		//declared in advance
		template <typename RandomAccessIterator, typename Dist,
				  typename TypeT, typename Compare>
		inline void adjust_heap(
			RandomAccessIterator first,
			Dist holeIndex,
			Dist dist,
			TypeT value,
			Compare comp);


		// 25.3.1.4
		template <typename InputIterator, typename RandomAccessIterator,
				  typename Compare>
		inline RandomAccessIterator partial_sort_copy(
			InputIterator first, InputIterator last,
			RandomAccessIterator first2, RandomAccessIterator last2,
			Compare comp)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::value_type Dist;

			if(first == last)
				return first2;

			//partial_sort_copy2 :
			if (first2 == last2)
				return last2;

			RandomAccessIterator res = first2;

			for (; !(first == last) && !(res == last2); ++first, ++res)
				*res = *first;

			misc::algobase::make_heap (first2, res, comp);

			for (; !(first == last); ++first)
			{
				if (comp (*first, *first2))
					misc::algobase::adjust_heap(
						first2, Dist(), Dist(res - first2), *first, comp);
			}

			misc::algobase::sort_heap(first2, res, comp);

			return res;
		}


		template <typename InputIterator, typename RandomAccessIterator>
		inline RandomAccessIterator partial_sort_copy(
			InputIterator first1, InputIterator last1,
			RandomAccessIterator first2, RandomAccessIterator last2)
		{
			return misc::algobase::partial_sort_copy(
				first1, last1,
				first2, last2,
				misc::less<typename
				misc::iterator_traits<InputIterator>::value_type>());
		}


		// 25.3.2 - Nth element [lib.alg.nth.element]
		template <typename RandomAccessIterator, typename Compare>
		inline void nth_element(
			RandomAccessIterator first,
			RandomAccessIterator nth,
			RandomAccessIterator last,
			Compare comp)
		{
			if (!(first == last))
			{
				typedef typename
					misc::iterator_traits<RandomAccessIterator>::value_type TypeT;

				while (last - first > 3)
				{
					const RandomAccessIterator cut =
						misc::algobase::unguarded_partition(
							first,
							last,
							TypeT(misc::algobase::median(
									  *first, *(first + (last - first)/2), * (last - 1), comp)),
							comp);

					if (!(nth < cut))
						first = cut;
					else
						last = cut;
				}

				misc::algobase::insertion_sort (first, last, comp);
			}
		}

		template <typename RandomAccessIterator>
		inline void nth_element(
			RandomAccessIterator first,
			RandomAccessIterator nth,
			RandomAccessIterator last)
		{
			misc::algobase::nth_element(
				first,
				nth,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}



		// 25.3.3 - Binary search [lib.alg.binary.search]
		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline ForwardIterator lower_bound2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT& value,
				Compare comp,
				misc::forward_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator>::difference_type Dist;

			for (Dist dist = misc::distance(first, last); dist; )
			{
				const Dist half = dist / 2;
				ForwardIterator middle = first;

				misc::advance(middle, half);

				if (comp (*middle, value))
				{
					first = middle;
					++first;
					dist = dist - half - 1;
				}
				else
				{
					dist = half;
				}
			}

			return first;
		}


		template <typename RandomAccessIterator, typename TypeT, typename Compare>
			inline RandomAccessIterator lower_bound2(
				RandomAccessIterator first,
				RandomAccessIterator last,
				const TypeT& value,
				Compare comp,
				misc::random_access_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			for (Dist dist = last - first; dist > 0; )
			{
				const Dist half = dist / 2;
				const RandomAccessIterator middle = first + half;

				if (comp (*middle, value))
				{
					first = middle + 1;
					dist  = dist - half - 1;
				}
				else
				{
					dist = half;
				}
			}

			return first;
		}


		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline ForwardIterator lower_bound2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT &value,
				Compare comp,
				misc::bidirectional_iterator_tag)
		{
			return misc::algobase::lower_bound2(
				first,
				last,
				value,
				comp,
				misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		// 25.3.3.1
		template <typename ForwardIterator, typename TypeT, typename Compare>
		inline ForwardIterator lower_bound(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT &value,
			Compare comp)
		{
			return misc::algobase::lower_bound2(
				first,
				last,
				value,
				comp,
				typename misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		template <typename ForwardIterator, typename TypeT>
		inline ForwardIterator lower_bound(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT &value)
		{
			return misc::algobase::lower_bound(
				first,
				last,
				value,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}



		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline ForwardIterator upper_bound2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT& value,
				Compare comp,
				misc::forward_iterator_tag)
		{

			typedef typename
				misc::iterator_traits<ForwardIterator>::difference_type Dist;

			for (Dist dist = misc::distance(first, last); dist;)
			{
				const Dist half = dist / 2;
				ForwardIterator middle = first;

				misc::advance (middle, half);

				if (comp (value, *middle))
					dist = half;
				else
				{
					first = middle;
					++first;
					dist = dist - half - 1;
				}
			}

			return first;
		}


		template <typename RandomAccessIterator, typename TypeT, typename Compare>
			inline RandomAccessIterator upper_bound2(
				RandomAccessIterator first,
				RandomAccessIterator last,
				const TypeT& value,
				Compare comp,
				misc::random_access_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			for (Dist dist = last - first; dist; )
			{
				const Dist half = dist / 2;
				const RandomAccessIterator middle = first + half;

				if (comp (value, *middle))
				{
					dist = half;
				}
				else
				{
					first = middle + 1;
					dist = dist - half - 1;
				}
			}

			return first;
		}





		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline ForwardIterator upper_bound2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT &value,
				Compare comp,
				misc::bidirectional_iterator_tag)
		{
			return misc::algobase::upper_bound2(
				first,
				last,
				value,
				comp,
				misc::forward_iterator_tag ());
		}


		// 25.3.3.2
		template <typename ForwardIterator, typename TypeT, typename Compare>
		inline ForwardIterator upper_bound(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT& value,
			Compare comp)
		{
			return misc::algobase::upper_bound2(
				first,
				last,
				value,
				comp,
				typename misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		template <typename ForwardIterator, typename TypeT>
		inline ForwardIterator upper_bound(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT& value)
		{
			return misc::algobase::upper_bound(
				first,
				last,
				value,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}



		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline  misc::pair<ForwardIterator, ForwardIterator> equal_range2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT& value,
				Compare comp,
				misc::forward_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<ForwardIterator>::difference_type Dist;

			for (Dist dist = misc::distance(first, last); dist; )
			{
				const Dist half = dist / 2;
				ForwardIterator middle = first;

				misc::advance (middle, half);

				if (comp (*middle, value))
				{
					first = middle;
					++first;
					dist = dist - half - 1;
				}
				else if (comp (value, *middle))
				{
					dist = half;
				}
				else
				{
					const ForwardIterator left =
						misc::algobase::lower_bound (first, middle, value, comp);

					misc::advance (first, dist);

					const ForwardIterator right =
						misc::algobase::upper_bound (++middle, first, value, comp);

					return misc::pair<ForwardIterator, ForwardIterator>(left, right);
				}
			}

			return misc::pair<ForwardIterator, ForwardIterator>(first, first);
		}



		template <typename RandomAccessIterator, typename TypeT, typename Compare>
			inline misc::pair<RandomAccessIterator, RandomAccessIterator> equal_range2(
				RandomAccessIterator first,
				RandomAccessIterator last,
				const TypeT& value,
				Compare comp,
				misc::random_access_iterator_tag)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			for (Dist dist = last - first; dist; )
			{
				const Dist half = dist / 2;
				const RandomAccessIterator middle = first + half;

				if (comp (*middle, value))
				{
					first = middle + 1;
					dist  = dist - half - 1;
				}
				else if (comp (value, *middle))
				{
					dist = half;
				}
				else
				{
					const RandomAccessIterator left =
						misc::algobase::lower_bound(first, middle, value, comp);

					const RandomAccessIterator right =
						misc::algobase::upper_bound(
							middle + 1, first + dist, value, comp);

					return misc::pair<RandomAccessIterator, RandomAccessIterator>(
						left, right);
				}
			}

			return misc::pair<RandomAccessIterator, RandomAccessIterator>(
				first, first);
		}


		template <typename ForwardIterator, typename TypeT, typename Compare>
			inline misc::pair<ForwardIterator, ForwardIterator> equal_range2(
				ForwardIterator first,
				ForwardIterator last,
				const TypeT &value,
				Compare comp,
				misc::bidirectional_iterator_tag)
		{
			return misc::algobase::equal_range2(
				first,
				last,
				value,
				comp,
				misc::forward_iterator_tag());
		}


		// 25.3.3.3
		template <typename ForwardIterator, typename TypeT, typename Compare>
		inline misc::pair<ForwardIterator, ForwardIterator> equal_range(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT &value,
			Compare comp)
		{
			return misc::algobase::equal_range2(
				first,
				last,
				value,
				comp,
				typename misc::iterator_traits<ForwardIterator>::iterator_category());
		}


		template <typename ForwardIterator, typename TypeT>
		inline misc::pair<ForwardIterator, ForwardIterator> equal_range(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT &value)
		{
			return misc::algobase::equal_range(
				first,
				last,
				value,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}


		// 25.3.3.4
		template <typename ForwardIterator, typename TypeT, typename Compare>
		inline bool binary_search(
			ForwardIterator first,
			ForwardIterator last,
			const TypeT &value,
			Compare comp)
		{
			ForwardIterator i =
				misc::algobase::lower_bound (first, last, value, comp);

			return !(i == last) && !comp(value, *i);
		}


		template <typename ForwardIterator, typename TypeT>
		inline bool binary_search(
			ForwardIterator first, ForwardIterator last, const TypeT &value)
		{
			return misc::algobase::binary_search(
				first,
				last,
				value,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}


		// 25.3.4 - Merge [lib.alg.merge]
		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename Compare>
		inline OutputIterator merge(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res,
			Compare comp)
		{
			for (; !(first1 == last1) && !(first2 == last2); ++res)
			{
				if (comp (*first2, *first1))
				{
					*res = *first2;
					++first2;
				}
				else
				{
					*res = *first1;
					++first1;
				}
			}

			return misc::algobase::copy(
				first2, last2, misc::algobase::copy(first1, last1, res));
		}




		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator>
		inline OutputIterator merge(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res)
		{
			return misc::algobase::merge(
				first1, last1,
				first2, last2,
				res,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}



		template <typename BidirectionalIterator1, typename BidirectionalIterator2,
				  typename Dist>
		inline BidirectionalIterator1 rotate_adaptive(
			BidirectionalIterator1 first,
			BidirectionalIterator1 middle,
			BidirectionalIterator1 last,
			Dist dist1,
			Dist dist2,
			BidirectionalIterator2 buf,
			Dist buf_size)
		{
			if (dist1 > dist2 && dist2 <= buf_size)
			{
				BidirectionalIterator2 buf_end =
					misc::algobase::copy (middle, last, buf);

				misc::algobase::copy_backward (first, middle, last);

				return misc::algobase::copy (buf, buf_end, first);
			}

			if (dist1 <= buf_size)
			{
				BidirectionalIterator2 buf_end =
					misc::algobase::copy (first, middle, buf);

				misc::algobase::copy (middle, last, first);

				return misc::algobase::copy_backward (buf, buf_end, last);
			}

			misc::algobase::rotate (first, middle, last);
			misc::advance (first, dist2);
			return first;
		}



		template <typename BidirectionalIterator1, typename BidirectionalIterator2,
				  typename BidirectionalIterator3>
		inline BidirectionalIterator3 merge_backward(
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			BidirectionalIterator3 res)
		{
			if (first1 == last1)
				return misc::algobase::copy_backward (first2, last2, res);

			if (first2 == last2)
				return misc::algobase::copy_backward (first1, last1, res);

			for (--last1, --last2; ; )
			{
				if (*last2 < *last1)
				{
					*--res = *last1;
					if (first1 == last1)
						return misc::algobase::copy_backward (first2, ++last2, res);
					--last1;
				}
				else
				{
					*--res = *last2;
					if (first2 == last2)
						return misc::algobase::copy_backward (first1, ++last1, res);
					--last2;
				}
			}
		}



		template <typename BidirectionalIterator1, typename BidirectionalIterator2,
				  typename BidirectionalIterator3, typename Compare>
		inline BidirectionalIterator3 merge_backward(
			BidirectionalIterator1 first1, BidirectionalIterator1 last1,
			BidirectionalIterator2 first2, BidirectionalIterator2 last2,
			BidirectionalIterator3 res,
			Compare comp)
		{

			if (first1 == last1)
				return misc::algobase::copy_backward (first2, last2, res);

			if (first2 == last2)
				return misc::algobase::copy_backward (first1, last1, res);

			for (--last1, --last2; ; )
			{
				if (comp (*last2, *last1))
				{
					*--res = *last1;
					if (first1 == last1)
						return misc::algobase::copy_backward (first2, ++last2, res);
					--last1;
				}
				else
				{
					*--res = *last2;
					if (first2 == last2)
						return misc::algobase::copy_backward (first1, ++last1, res);
					--last2;
				}
			}
		}


		template <typename BidirectionalIterator, typename Dist, typename Pointer,
				  typename Compare>
		inline void merge_adaptive(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			Dist dist1,
			Dist dist2,
			Pointer buf,
			Dist buf_size,
			Compare comp)
		{

			if (dist1 <= dist2 && dist1 <= buf_size)
			{
				Pointer buf_end = misc::algobase::copy (first, middle, buf);
				misc::algobase::merge (buf, buf_end, middle, last, first, comp);
			}
			else if (dist2 <= buf_size)
			{
				Pointer buf_end = misc::algobase::copy (middle, last, buf);
				misc::algobase::merge_backward(
					first, middle, buf, buf_end, last, comp);
			}
			else
			{
				BidirectionalIterator first_cut = first;
				BidirectionalIterator second_cut = middle;
				Dist dist11;
				Dist dist22;
				if (dist1 > dist2)
				{
					dist11 = dist1 / 2;
					misc::advance (first_cut, dist11);
					second_cut =
						misc::algobase::lower_bound (middle, last, *first_cut, comp);
					dist22 = misc::distance(middle, second_cut);
				}
				else
				{
					dist22 = dist2 / 2;
					misc::advance (second_cut, dist22);
					first_cut =
						misc::algobase::upper_bound (first, middle, *second_cut, comp);
					dist11 = misc::distance(first, first_cut);
				}

				BidirectionalIterator middle2 =
					misc::algobase::rotate_adaptive(
						first_cut, middle, second_cut,
						dist1 - dist11, dist22, buf, buf_size);

				misc::algobase::merge_adaptive(
					first, first_cut, middle2, dist11, dist22, buf, buf_size, comp);
				misc::algobase::merge_adaptive(
					middle2, second_cut, last,
					dist1 - dist11, dist2 - dist22, buf, buf_size, comp);
			}
		}


		// 25.3.4, p6
		template <typename BidirectionalIterator, typename Compare>
		inline void inplace_merge(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last,
			Compare comp)
		{
			if (!(first == middle || middle == last))
			{
				typedef typename
					misc::iterator_traits<BidirectionalIterator>::difference_type Dist;

				typedef typename
					misc::iterator_traits<BidirectionalIterator>::value_type TypeT;


				Dist dist1 = misc::distance(first, middle);
				Dist dist2 = misc::distance(middle, last);

				misc::pair<TypeT*, Dist> pair =
					misc::get_temporary_buffer<TypeT>(dist1 + dist2);

				if (pair.first == 0)
				{
					misc::algobase::merge_without_buffer(
						first, middle, last, dist1, dist2, comp);
				}
				else
				{
					Dist dist = misc::algobase::min(pair.second, dist1 + dist2);

					misc::algobase::fill_n(
						misc::raw_storage_iterator<TypeT*, TypeT>(pair.first),
						dist,
						*first);

					misc::algobase::merge_adaptive(
						first, middle, last, dist1, dist2, pair.first, pair.second,
						comp);

					for (TypeT *ptr = pair.first + dist; !(pair.first == --ptr); )
						(*ptr).~TypeT ();

					misc::return_temporary_buffer (pair.first);
				}
			}
		}


		// 25.3.4, p6
		template <typename BidirectionalIterator>
		inline void inplace_merge(
			BidirectionalIterator first,
			BidirectionalIterator middle,
			BidirectionalIterator last)
		{
			misc::algobase::inplace_merge(
				first,
				middle,
				last,
				misc::less<typename
				misc::iterator_traits<BidirectionalIterator>::value_type>());
		}

		// 25.3.5 - Set operations on sorted structures

		// 25.3.5.1 - returns true if every (not necessarily distinct) element
		// in [first2, last2) occurs (at least as many times) in [first1, last1)

		template <typename InputIterator1, typename InputIterator2, typename Compare>
		inline bool includes(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp)
		{
			for (; !(first1 == last1) && !(first2 == last2); ++first1)
			{
				if (comp (*first2, *first1))
					return false;

				if (comp (*first1, *first2) == false)
					++first2;
			}

			return first2 == last2;
		}


		template <typename InputIterator1, typename InputIterator2>
		inline bool includes(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
		{
			return misc::algobase::includes(
				first1, last1,
				first2, last2,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}


		// 25.3.5.2
		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename Compare>
		inline OutputIterator set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res,
			Compare comp)
		{
			for (; !(first1 == last1) && !(first2 == last2); ++res)
			{
				if (comp (*first1, *first2))
				{
					*res = *first1;
					++first1;
				}
				else if (comp (*first2, *first1))
				{
					*res = *first2;
					++first2;
				}
				else
				{
					*res = *first1;
					++first1;
					++first2;
				}
			}

			return misc::algobase::copy(
				first2, last2, misc::algobase::copy (first1, last1, res));
		}


		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator>
		inline OutputIterator set_union(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res)
		{
			return misc::algobase::set_union(
				first1, last1,
				first2, last2,
				res,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}


		// 25.3.5.3
		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename Compare>
		inline OutputIterator set_intersection(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res,
			Compare comp)
		{
			while (!(first1 == last1) && !(first2 == last2))
			{
				if (comp (*first1, *first2))
					++first1;
				else if (comp (*first2, *first1))
					++first2;
				else
				{
					*res = *first1;
					++res;
					++first1;
					++first2;
				}
			}

			return res;
		}



		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator>
		inline OutputIterator set_intersection(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res)
		{
			return misc::algobase::set_intersection(
				first1, last1,
				first2, last2,
				res,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}


		// 25.3.5.4
		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename Compare>
		inline OutputIterator set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res,
			Compare comp)
		{
			while (!(first1 == last1) && !(first2 == last2))
			{
				if (comp (*first1, *first2))
				{
					*res = *first1;
					++res;
					++first1;
				}
				else if (comp (*first2, *first1))
					++first2;
				else
				{
					++first1;
					++first2;
				}
			}

			return misc::algobase::copy (first1, last1, res);
		}



		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator>
		inline OutputIterator set_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res)
		{
			return misc::algobase::set_difference(
				first1, last1,
				first2, last2,
				res,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}


		// 25.3.5.5
		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator, typename Compare>
		inline OutputIterator set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res,
			Compare comp)
		{
			while (!(first1 == last1) && !(first2 == last2))
			{
				if (comp (*first1, *first2))
				{
					*res = *first1;
					++res;
					++first1;
				}
				else if (comp (*first2, *first1))
				{
					*res = *first2;
					++res;
					++first2;
				}
				else
				{
					++first1;
					++first2;
				}
			}

			return misc::algobase::copy(
				first2, last2, misc::algobase::copy(first1, last1, res));
		}




		template <typename InputIterator1, typename InputIterator2,
				  typename OutputIterator>
		inline OutputIterator set_symmetric_difference(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			OutputIterator res)
		{
			return   misc::algobase::set_symmetric_difference(
				first1, last1,
				first2, last2,
				res,
				misc::less<typename
				misc::iterator_traits<InputIterator1>::value_type>());
		}



		// 25.3.6 - Heap operations
		template <typename RandomAccessIterator, typename Dist, typename TypeT,
				  typename Compare>
		inline void push_heap2(
			RandomAccessIterator first,
			Dist holeIndex,
			Dist topIndex,
			TypeT value,
			Compare comp)
		{
			for (Dist parent = (holeIndex - 1) / 2;
				 holeIndex > topIndex && !(comp (*(first + parent), value) == false);
				 parent = ((holeIndex = parent) - 1) / 2)
			{
				*(first + holeIndex) = *(first + parent);
			}

			*(first + holeIndex) = value;
		}


		// 25.3.6.1
		template <typename RandomAccessIterator, typename Compare>
		inline void push_heap(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (!(first == last))
			{
				typedef typename
					misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

				--last;
				misc::algobase::push_heap2(
					first, Dist(last - first), Dist(), *last, comp);
			}
		}


		// 25.3.6.1
		template <typename RandomAccessIterator>
		inline void push_heap (RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::push_heap(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}


		template <typename RandomAccessIterator, typename Dist,
				  typename TypeT, typename Compare>
		inline void adjust_heap(
			RandomAccessIterator first,
			Dist holeIndex,
			Dist dist,
			TypeT value,
			Compare comp)
		{
			const Dist topIndex = holeIndex;

			Dist _2ndChild;

			while ((_2ndChild = 2 * holeIndex + 2) < dist)
			{
				if (comp (*(first + _2ndChild), *(first + (_2ndChild - 1))))
					--_2ndChild;

				*(first + holeIndex) = *(first + _2ndChild);

				holeIndex = _2ndChild;
			}

			if (_2ndChild == dist)
			{
				*(first + holeIndex) = *(first + (_2ndChild - 1));
				holeIndex = _2ndChild - 1;
			}

			misc::algobase::push_heap2(first, holeIndex, topIndex, value, comp);
		}



		template <typename RandomAccessIterator, typename TypeT, typename Compare>
			inline void pop_heap2(
				RandomAccessIterator first,
				RandomAccessIterator last,
				RandomAccessIterator res,
				TypeT value,
				Compare cmp)
		{
			typedef typename
				misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

			*res = *first;
			misc::algobase::adjust_heap(first, Dist(), Dist(last-first), value, cmp);
		}


		// 25.3.6.2
		template <typename RandomAccessIterator, typename Compare>
		inline void pop_heap(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (!(first == last))
			{
				--last;
				misc::algobase::pop_heap2(first, last, last, *last, comp);
			}
		}


		// 25.3.6.2
		template <typename RandomAccessIterator>
		inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::pop_heap(first, last,									 
									 misc::less<
									 typename
									 misc::iterator_traits<RandomAccessIterator>::value_type>());
		}

		// 25.3.6.3
		template <typename RandomAccessIterator, typename Compare>
		inline void make_heap(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			if (!(last - first < 2))
			{
				typedef typename
					misc::iterator_traits<RandomAccessIterator>::difference_type Dist;

				const Dist dist = last - first;

				for (Dist parent = dist / 2; 0 < parent; )
				{
					--parent;
					misc::algobase::adjust_heap(
						first, parent, dist, *(first + parent), comp);
				}
			}
		}


		// 25.3.6.3
		template <typename RandomAccessIterator>
		inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::make_heap(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}


		// 25.3.6.4
		template <typename RandomAccessIterator, typename Compare>
		inline void sort_heap(
			RandomAccessIterator first, RandomAccessIterator last, Compare comp)
		{
			for (; last - first > 1; --last)
			{
				misc::algobase::pop_heap(first, last, comp);
			}
		}


		// 25.3.6.4
		template <typename RandomAccessIterator>
		inline void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
		{
			misc::algobase::sort_heap(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<RandomAccessIterator>::value_type>());
		}




		// 25.3.7 - Minimum and maximum
		/*
			Disable function-like macro expansion
			You can prevent the expansion of function-like macros by hiding 
			the open-paren that must follow the macro name.		
			For example, let's say you have a math package, and one element 
			of your math package is a function that tests for NAN.

			if (MyCompany::math::isnan(result))
				exit(1);

			Now, if you were to compile this in a file that also included C99 
			headers, you would get an interesting compile error, because C99 
			has a function-like macro named isnan(), and it might look like this

			#define isnan(x) \
				(sizeof (x) == sizeof (float) ? __isnanf (x) : __isnan (x))

			In this case, if your code were written like this

			if ((MyCompany::math::isnan)(result))
				exit(1);

			it would compile properly - the macro preprocessor would have 
			the definition for the isnan macro, but it would not see an opening paren,
			so it wouldn't expand the macro in this case.

			Note that this only works for function-like macros; 
			it will not work for object-like macros.
				
			See more at http://blog.bfitz.us/?p=1408

			In this case we apply the above to Windows min/max macros.

			windef.h macros:
			
			#ifndef NOMINMAX
			#ifndef max
			#define max(a,b)            (((a) > (b)) ? (a) : (b))
			#endif
			#ifndef min
			#define min(a,b)            (((a) < (b)) ? (a) : (b))
			#endif
			#endif  // NOMINMAX
		*/

		template <typename T>
		inline const T& (min)(const T& a, const T& b)
		{
			return b < a ? b : a;
		}

		template <typename T, typename Compare>
		inline const T& (min)(const T& a, const T& b, Compare cmp)
		{
			return cmp (b, a) ? b : a;
		}


		// 25.3.7, p3
		template <typename T>
		inline const T& (max)(const T& a, const T& b)
		{
			return  a < b ? b : a;
		}


		template <typename T, typename Compare>
		inline const T& (max)(const T& a, const T& b, Compare cmp)
		{
			return !(cmp (a, b) == false) ? b : a;
		}


		// 25.3.7, p7

		template <typename ForwardIterator, typename Compare>
		inline ForwardIterator min_element(
			ForwardIterator first, ForwardIterator last, Compare comp)
		{
			ForwardIterator res = first;

			if (!(first == last))
			{
				while (!(++first == last))
				{
					if (comp (*first, *res))
						res = first;
				}
			}

			return res;
		}



		template <typename ForwardIterator>
		inline ForwardIterator min_element(
			ForwardIterator first, ForwardIterator last)
		{
			return misc::algobase::min_element(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}


		// 25.3.7, p9

		template <typename ForwardIterator, typename Compare>
		inline ForwardIterator max_element(
			ForwardIterator first, ForwardIterator last, Compare comp)
		{
			ForwardIterator res = first;

			if (!(first == last))
			{
				while (!(++first == last))
				{
					if (comp (*res, *first))
						res = first;
				}
			}

			return res;
		}




		template <typename ForwardIterator>
		inline ForwardIterator max_element(
			ForwardIterator first, ForwardIterator last)
		{
			return misc::algobase::max_element(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<ForwardIterator>::value_type>());
		}



		// 25.3.8 - Lexicographical Comparison
		template <typename InputIterator1, typename InputIterator2>
		inline bool lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
		{
			for ( ; ; ++first2, ++first1)
			{
				if (first1 == last1)
					return !(first2 == last2);

				if (first2 == last2 || *first2 < *first1)
					break;

				if (*first1 < *first2)
					return true;
			}
			return false;
		}


		template <typename InputIterator1, typename InputIterator2, typename Compare>
		inline bool lexicographical_compare(
			InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2,
			Compare comp)
		{
			for ( ; ; ++first2, ++first1)
			{
				if (first1 == last1)
					return !(first2 == last2);

				if (first2 == last2 || !(comp (*first2, *first1) == false))
					break;

				if (!(comp (*first1, *first2) == false))
					return true;
			}

			return false;
		}




		// 25.3.9 - Permutation generators [lib.alg.permutation.generators]
		template <typename BidirectionalIterator, typename Compare>
		inline bool next_permutation(
			BidirectionalIterator first, BidirectionalIterator last, Compare comp)
		{
			if (first == last)
				return false;

			BidirectionalIterator i = first;

			if (++i == last)
				return false;

			bool res;

			for (i = last, --i; ; )
			{
				const BidirectionalIterator ii = i;

				if (comp (*--i, *ii))
				{
					BidirectionalIterator j = last;

					while (comp (*i, *--j) == false);

					misc::algobase::iter_swap (i, j);

					first = ii;
					res   = true;

					break;
				}

				if (i == first)
				{
					res = false;
					break;
				}
			}

			misc::algobase::reverse (first, last);

			return res;
		}



		template <typename BidirectionalIterator>
		inline bool next_permutation(
			BidirectionalIterator first, BidirectionalIterator last)
		{
			return misc::algobase::next_permutation(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<BidirectionalIterator>::value_type>());
		}


		// 25.3.9, p3
		template <typename BidirectionalIterator, typename Compare>
		inline bool prev_permutation(
			BidirectionalIterator first, BidirectionalIterator last, Compare comp)
		{
			if (first == last)
				return false;

			BidirectionalIterator i = first;

			if (++i == last)
				return false;

			bool res;

			for (i = last, --i; ; )
			{
				const BidirectionalIterator ii = i;

				if (comp (*ii, *--i))
				{
					BidirectionalIterator j = last;

					while (comp (*--j, *i) == false);

					misc::algobase::iter_swap (i, j);

					first = ii;
					res   = true;

					break;
				}

				if (i == first)
				{
					res = false;
					break;
				}
			}

			misc::algobase::reverse (first, last);

			return res;
		}


		template <typename BidirectionalIterator>
		inline bool prev_permutation(
			BidirectionalIterator first, BidirectionalIterator last)
		{
			return misc::algobase::prev_permutation(
				first,
				last,
				misc::less<typename
				misc::iterator_traits<BidirectionalIterator>::value_type>());
		}

	} // algobase

} // misc




#endif//__algobase_hpp__



