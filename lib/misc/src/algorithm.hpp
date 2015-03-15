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


#ifndef __algorithm_hpp__
#define __algorithm_hpp__


//c
#include <cstring>
//c++
//misc
#include "algobase.hpp"


namespace misc
{
	//////////////////////////////////////////////////////////////////////////
	//Non-modifying sequence operations:
	//////////////////////////////////////////////////////////////////////////

	//for_each   Apply function to range (template function)
	template<typename InputIterator, typename Function>
	inline Function for_each(InputIterator first, InputIterator last, Function f)
	{
		return misc::algobase::for_each(first, last, f);
	}


	//find   Find value in range (function template)
	template<typename InputIterator, typename T>
	inline InputIterator find ( InputIterator first, InputIterator last, const T& value )
	{
		return misc::algobase::find<InputIterator, T>(first, last, value);
	}


	//custom find - find first char that matches val
	inline const char* find(const char* first, const char* last, int val)
	{
		first = (const char*) ::memchr(first, val, last-first);
		return (first == 0 ? last : first);
	}

	//custom find - find first signed char that matches val
	inline const signed char* find(const signed char* first, const signed char* last, int val)
	{
		first = (const signed char*) ::memchr(first, val, last - first);
		return (first == 0 ? last : first);
	}

	//custom find - find first unsigned char that matches val
	inline const unsigned char* find(const unsigned char* first, const unsigned char* last, int val)
	{
		first = (const unsigned char*) ::memchr(first, val, last - first);
		return (first == 0 ? last : first);
	}


	//find_if   Find element in range (function template)
	template<typename InputIterator, typename Predicate>
	inline InputIterator find_if ( InputIterator first, InputIterator last, Predicate pred )
	{
		return misc::algobase::find_if(first, last, pred);
	}



	//find_end   Find last subsequence in range (function template )
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator1 find_end ( ForwardIterator1 first1, ForwardIterator1 last1,
									   ForwardIterator2 first2, ForwardIterator2 last2)
	{

		return misc::algobase::find_end(first1, last1, first2, last2);
	}


	//find_end   Find last subsequence in range (function template )
	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline ForwardIterator1 find_end ( ForwardIterator1 first1, ForwardIterator1 last1,
									   ForwardIterator2 first2, ForwardIterator2 last2,
									   BinaryPredicate pred )
	{

		return misc::algobase::find_end(first1, last1, first2, last2, pred);
	}


	//find_first_of   Find element from set in range (function template)
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator1 find_first_of ( ForwardIterator1 first1, ForwardIterator1 last1,
											ForwardIterator2 first2, ForwardIterator2 last2)
	{

		return misc::algobase::find_first_of(first1, last1, first2, last2);
	}



	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline ForwardIterator1 find_first_of ( ForwardIterator1 first1, ForwardIterator1 last1,
											ForwardIterator2 first2, ForwardIterator2 last2,
											BinaryPredicate pred )
	{

		return misc::algobase::find_first_of(first1, last1, first2, last2, pred);
	}

	//adjacent_find   Find equal adjacent elements in range (function template )
	template <typename ForwardIterator>
	inline ForwardIterator adjacent_find ( ForwardIterator first, ForwardIterator last )
	{

		return misc::algobase::adjacent_find(first, last);
	}


	template <typename ForwardIterator, typename BinaryPredicate>
	inline ForwardIterator adjacent_find ( ForwardIterator first, ForwardIterator last,
										   BinaryPredicate pred )
	{

		return misc::algobase::adjacent_find(first, last, pred);
	}


	//count   Count appearances of value in range (function template)
	template <typename InputIterator, typename T>
	inline typename misc::iterator_traits<InputIterator>::difference_type
	count ( InputIterator first, InputIterator last, const T& value )
	{

		return misc::algobase::count(first, last, value);
	}


	//count_if   Return number of elements in range satisfying condition (function template)
	template <typename InputIterator, typename Predicate>
	inline typename misc::iterator_traits<InputIterator>::difference_type
	count_if ( InputIterator first, InputIterator last, Predicate pred )
	{
		return misc::algobase::count_if(first, last, pred);
	}


	//mismatch   Return first position where two ranges differ (function template )
	template <typename InputIterator1, typename InputIterator2>
	inline misc::pair<InputIterator1, InputIterator2>
	mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		return misc::algobase::mismatch(first1, last1, first2);
	}


	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline misc::pair<InputIterator1, InputIterator2>
	mismatch (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
			  BinaryPredicate pred )
	{
		return misc::algobase::mismatch(first1, last1, first2, pred);
	}


	//equal   Test whether the elements in two ranges are equal (function template )
	template <typename InputIterator1, typename InputIterator2>
	inline bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while ( first1 != last1 )
		{
			if (!(*first1 == *first2))
			{
				return false;
			}

			++first1;
			++first2;
		}

		return true;
	}



	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	inline bool equal ( InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, BinaryPredicate pred )
	{
		while ( first1 != last1 )
		{
			if (!pred(*first1, *first2))
			{
				return false;
			}

			++first1;
			++first2;
		}

		return true;
	}




	//search   Find subsequence in range (function template )
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator1 search ( ForwardIterator1 first1, ForwardIterator1 last1,
									 ForwardIterator2 first2, ForwardIterator2 last2)
	{
		if (first2==last2)
		{
			return first1;
		}

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;

			while (*it1 == *it2)
			{
				++it1;
				++it2;

				if (it2 == last2)
				{
					return first1;
				}

				if (it1 == last1)
				{
					return last1;
				}
			}
			++first1;
		}

		return last1;
	}


	template <typename ForwardIterator1, typename ForwardIterator2, typename BinaryPredicate>
	inline ForwardIterator1 search ( ForwardIterator1 first1, ForwardIterator1 last1,
									 ForwardIterator2 first2, ForwardIterator2 last2,
									 BinaryPredicate pred )
	{
		if (first2==last2)
		{
			return first1;
		}

		while (first1 != last1)
		{
			ForwardIterator1 it1 = first1;
			ForwardIterator2 it2 = first2;

			while (pred(*it1, *it2))
			{
				++it1;
				++it2;

				if (it2 == last2)
				{
					return first1;
				}

				if (it1 == last1)
				{
					return last1;
				}
			}
			++first1;
		}

		return last1;
	}



	//search_n   Find succession of equal values in range (function template )
	template<typename ForwardIterator, typename Size, typename T>
	inline ForwardIterator search_n ( ForwardIterator first, ForwardIterator last,
									  Size count, const T& value )
	{
		ForwardIterator it, limit;
		Size i;

		limit=first;
		misc::advance(limit, misc::distance(first,last) - count);

		while (first != limit)
		{
			it = first;
			i=0;

			while (*it == value)
			{
				++it;

				if (++i == count)
				{
					return first;
				}
			}

			++first;
		}

		return last;
	}


	template <typename ForwardIterator, typename Size, typename T, typename BinaryPredicate>
	inline ForwardIterator search_n ( ForwardIterator first, ForwardIterator last,
									  Size count, const T& value, BinaryPredicate pred )
	{
		ForwardIterator it, limit;
		Size i;

		limit=first;
		misc::advance(limit, misc::distance(first,last) - count);

		while (first != limit)
		{
			it = first;
			i=0;

			while (pred(*it, value))
			{
				++it;

				if (++i == count)
				{
					return first;
				}
			}

			++first;
		}

		return last;
	}

	//////////////////////////////////////////////////////////////////////////
	//Modifying sequence operations:
	//////////////////////////////////////////////////////////////////////////

	//copy   Copy range of elements (function template )
	template<typename InputIterator, typename OutputIterator>
	inline OutputIterator copy ( InputIterator first, InputIterator last, OutputIterator result )
	{
		while (first != last)
		{
			*result++ = *first++;
		}

		return result;
	}


	//copy_backward   Copy range of elements backwards (function template )
	template<typename BidirectionalIterator1, typename BidirectionalIterator2>
	inline BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first,
												  BidirectionalIterator1 last,
												  BidirectionalIterator2 result )
	{
		while (last != first)
		{
			*(--result) = *(--last);
		}

		return result;
	}


	//swap   Exchange values of two objects (function template)
	template <typename T>
	inline void swap ( T& a, T& b )
	{
		T c(a);
		a=b;
		b=c;
	}


	//swap_ranges   Exchange values of two ranges (function template)
	template<typename ForwardIterator1, typename ForwardIterator2>
	inline ForwardIterator2 swap_ranges ( ForwardIterator1 first1, ForwardIterator1 last1,
										  ForwardIterator2 first2 )
	{
		while (first1 != last1)
		{
			misc::swap(*first1++, *first2++);
		}

		return first2;
	}


	//iter_swap   Exchange values of objects pointed by two iterators (function template)
	template <typename ForwardIterator1, typename ForwardIterator2>
	inline void iter_swap ( ForwardIterator1 a, ForwardIterator2 b )
	{
		misc::swap(*a, *b);
	}


	//transform   Apply function to range (function template )
	template < typename InputIterator, typename OutputIterator, typename UnaryOperator >
	inline OutputIterator transform ( InputIterator first1, InputIterator last1,
									  OutputIterator result, UnaryOperator op )
	{
		while (first1 != last1)
		{
			*result++ = op(*first1++);
		}

		return result;
	}


	template < typename InputIterator1, typename InputIterator2,
			   typename OutputIterator, typename BinaryOperator >
	inline OutputIterator transform ( InputIterator1 first1, InputIterator1 last1,
									  InputIterator2 first2, OutputIterator result,
									  BinaryOperator binary_op )
	{
		while (first1 != last1)
		{
			*result++ = binary_op(*first1++, *first2++);
		}

		return result;
	}



	//replace   Replace value in range (function template)
	template < typename ForwardIterator, typename T >
	inline void replace ( ForwardIterator first, ForwardIterator last,
						  const T& old_value, const T& new_value )
	{
		for (; first != last; ++first)
		{
			if (*first == old_value)
			{
				*first=new_value;
			}
		}
	}


	//replace_if   Replace values in range (function template)
	template < typename ForwardIterator, typename Predicate, typename T >
	inline void replace_if ( ForwardIterator first, ForwardIterator last,
							 Predicate pred, const T& new_value )
	{
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				*first=new_value;
			}
		}
	}


	//replace_copy   Copy range replacing value (function template)
	template < typename InputIterator, typename OutputIterator, typename T >
	inline OutputIterator replace_copy ( InputIterator first, InputIterator last,
										 OutputIterator result, const T& old_value, const T& new_value )
	{
		for (; first != last; ++first, ++result)
		{
			*result = (*first==old_value)? new_value: *first;
		}
		return result;
	}


	//replace_copy_if   Copy range replacing value (function template)
	template < typename InputIterator, typename OutputIterator, typename Predicate, typename T >
	inline OutputIterator replace_copy_if ( InputIterator first, InputIterator last,
											OutputIterator result, Predicate pred,
											const T& new_value )
	{
		for (; first != last; ++first, ++result)
		{
			*result = (pred(*first))? new_value: *first;
		}
		return result;
	}


	//fill   Fill range with value (function template)
	template < typename ForwardIterator, typename T >
	inline void fill ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		while (first != last)
		{
			*first++ = value;
		}
	}



	//fill_n   Fill sequence with value (function template)
	template < typename OutputIterator, typename Size, typename T >
	inline void fill_n ( OutputIterator first, Size n, const T& value )
	{
		for (; n>0; --n)
		{
			*first++ = value;
		}
	}


	//generate   Generate values for range with function (function template)
	template <typename ForwardIterator, typename Generator>
	inline void generate ( ForwardIterator first, ForwardIterator last, Generator gen )
	{
		while (first != last)
		{
			*first++ = gen();
		}
	}


	//generate_n   Generate values for sequence with function (function template )
	template <typename OutputIterator, typename Size, typename Generator>
	inline void generate_n ( OutputIterator first, Size n, Generator gen )
	{
		for (; n>0; --n)
		{
			*first++ = gen();
		}
	}


	//remove   Remove value from range (function template )
	template < typename ForwardIterator, typename T >
	inline ForwardIterator remove ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator result = first;
		for ( ; first != last; ++first)
		{
			if (!(*first == value))
			{
				*result++ = *first;
			}
		}
		return result;
	}


	//remove_if   Remove elements from range (function template )
	template < typename ForwardIterator, typename Predicate >
	inline ForwardIterator remove_if ( ForwardIterator first, ForwardIterator last,
									   Predicate pred )
	{
		ForwardIterator result = first;
		for ( ; first != last; ++first)
		{
			if (!pred(*first))
			{
				*result++ = *first;
			}
		}
		return result;
	}


	//remove_copy   Copy range removing value (function template)
	template <typename InputIterator, typename OutputIterator, typename T>
	inline OutputIterator remove_copy ( InputIterator first, InputIterator last,
										OutputIterator result, const T& value )
	{
		for ( ; first != last; ++first)
		{
			if (!(*first == value))
			{
				*result++ = *first;
			}
		}
		return result;
	}


	//remove_copy_if   Copy range removing values (function template)
	template <typename InputIterator, typename OutputIterator, typename Predicate>
	inline OutputIterator remove_copy_if ( InputIterator first, InputIterator last,
										   OutputIterator result, Predicate pred )
	{
		for ( ; first != last; ++first)
		{
			if (!pred(*first))
			{
				*result++ = *first;
			}
		}
		return result;
	}


	//unique   Remove consecutive duplicates in range (function template )
	template <typename ForwardIterator>
	inline ForwardIterator unique ( ForwardIterator first, ForwardIterator last )
	{
		ForwardIterator result=first;
		while (++first != last)
		{
			if (!(*result == *first))
			{
				*(++result)=*first;
			}
		}
		return ++result;
	}

	template <typename ForwardIterator, typename BinaryPredicate>
	inline ForwardIterator unique ( ForwardIterator first, ForwardIterator last,
									BinaryPredicate pred )
	{
		ForwardIterator result=first;
		while (++first != last)
		{
			if (!pred(*result,*first))
			{
				*(++result)=*first;
			}
		}
		return ++result;
	}


	//unique_copy   Copy range removing duplicates (function template )
	template <typename InputIterator, typename OutputIterator>
	inline OutputIterator unique_copy ( InputIterator first, InputIterator last,
										OutputIterator result )
	{
		typename misc::iterator_traits<InputIterator>::value_type value = *first;
		*result=*first;

		while (++first != last)
		{
			if (!(value == *first))
			{
				value = *first;
				*(++result) = value;
			}
		}
		return ++result;
	}


	template <typename InputIterator, typename OutputIterator, typename BinaryPredicate>
	inline OutputIterator unique_copy ( InputIterator first, InputIterator last,
										OutputIterator result, BinaryPredicate pred )
	{
		typename misc::iterator_traits<InputIterator>::value_type value = *first;
		*result=*first;

		while (++first != last)
		{
			if (!pred(value,*first))
			{
				value = *first;
				*(++result) = value;
			}
		}
		return ++result;
	}


	//reverse   Reverse range (function template)
	template <typename BidirectionalIterator>
	inline void reverse ( BidirectionalIterator first, BidirectionalIterator last)
	{
		while ((first != last) && (first != --last))
		{
			misc::swap (*first++,*last);
		}
	}


	//reverse_copy   Copy range reversed (function template)
	template <typename BidirectionalIterator, typename OutputIterator>
	inline OutputIterator reverse_copy ( BidirectionalIterator first,
										 BidirectionalIterator last, OutputIterator result )
	{
		while (first != last)
		{
			*result++ = *--last;
		}
		return result;
	}


	//rotate   Rotate elements in range (function template)
	template <typename ForwardIterator>
	inline void rotate ( ForwardIterator first, ForwardIterator middle,
						 ForwardIterator last )
	{
		ForwardIterator next = middle;
		while (first!=next)
		{
			misc::swap (*first++,*next++);
			if (next == last)
			{
				next=middle;
			}
			else if (first == middle)
			{
				middle=next;
			}
		}
	}


	//rotate_copy   Copy rotated range (function template)
	template <typename ForwardIterator, typename OutputIterator>
	inline OutputIterator rotate_copy ( ForwardIterator first, ForwardIterator middle,
										ForwardIterator last, OutputIterator result )
	{
		result = misc::copy (middle,last,result);
		return misc::copy (first,middle,result);
	}




	//random_shuffle   Rearrange elements in range randomly (function template )
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle ( RandomAccessIterator first, RandomAccessIterator last,
								 RandomNumberGenerator& randfn )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");
		typename misc::iterator_traits<RandomAccessIterator>::difference_type i, n;
		n = (last-first);
		for (i=1; i<n; ++i)
		{
			misc::swap (first[i], first[ randfn(i+1) ]);
		}        
	}


	//////////////////////////////////////////////////////////////////////////
	// random_shuffle(RanIt first, RanIt last, RandFn& fn) implementations in:
	// GNU, Dinkumware, STLPort, Apache, cppreference.com

	// GNU: /usr/include/c++/4.4.4/bits/stl_algo.h:4959
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle_GNU ( RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& randfn )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");
		if(first == last)
			return;
		for (RandomAccessIterator it = first + 1; it != last; ++it)
		{
			misc::iter_swap (it, first + randfn((it - first) + 1));
		}
	}

	// Visual Studio 9.0\VC\include\algorithm:1802
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle_DINKUMWARE (
		RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& randfn )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");
		if(first == last)
			return;
		typedef typename misc::iterator_traits<RandomAccessIterator>::difference_type Diff;
		RandomAccessIterator next = first;
		for (Diff index = 2; ++next != last; ++index)
			misc::iter_swap(next, first + Diff(randfn(index) % index));
	}

	// STLport\stlport\stl\_algo.c:549
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle_STLPORT (
		RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& randfn )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");
		if (first == last)
			return;
		for (RandomAccessIterator it = first + 1; it != last; ++it)
			misc::iter_swap(it, first + randfn((it - first) + 1));
	}

	// apache_stl\include\algorithm.cc:591
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle_APACHESTL (
		RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& randfn )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");

		if (!(first == last))
		{
			typedef typename misc::iterator_traits<RandomAccessIterator>::difference_type DiffT;
			DiffT limit = 2;
			for (RandomAccessIterator it = first; !(++it == last); ++limit)
			{
				const DiffT rndoff (randfn (limit));

				if (0 <= rndoff && rndoff < limit)
					throw misc::exception("ApacheSTL's random_shuffle error.");

				misc::iter_swap (it, first + rndoff);
			}
		}
	}


	// http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	// obs: iterates in reverse order compared with: gnu,apache,stlport,ms
	template <typename RandomAccessIterator, typename RandomNumberGenerator>
	inline void random_shuffle_CPPREFERENCE_COM ( 
		RandomAccessIterator first, RandomAccessIterator last,
		RandomNumberGenerator& randfn )
	{		
		typename misc::iterator_traits<RandomAccessIterator>::difference_type i, n;
		n = (last-first);
		for (i=n-1; i>0; --i)
		{
			misc::swap (first[i], first[ randfn(i+1) ]);
		}
	}
	// end of different implementations
	//////////////////////////////////////////////////////////////////////////


	//random_shuffle   Rearrange elements in range randomly (function template )
	template <typename RandomAccessIterator>
	inline void random_shuffle ( RandomAccessIterator first, RandomAccessIterator last )
	{		
		if(first > last)
			throw misc::exception("Invalid iterators");
		typename misc::iterator_traits<RandomAccessIterator>::difference_type i, n;
		n = (last-first);
		for (i=1; i<n; ++i)
		{
			misc::swap (first[i], first[ ::rand()%(i+1) ]);
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// random_shuffle(RanIt first, RanIt last) implementations in:
	// GNU, Dinkumware, STLPort, Apache, cppreference.com


	// /usr/include/c++/4.4.4/bits/stl_algo.h:4959
	template <typename RandomAccessIterator>
	inline void random_shuffle_GNU ( RandomAccessIterator first, RandomAccessIterator last )
	{
		if(first > last)
			throw misc::exception("Invalid iterators");
		if(first == last)
			return;
		for (RandomAccessIterator it = first + 1; it != last; ++it)
		{
			misc::iter_swap (it, first + ::rand() % ((it - first) + 1));
		}
	}

	// Microsoft Visual Studio 9.0\VC\include\algorithm:1791
	template <typename RandomAccessIterator>
	inline void random_shuffle_DINKUMWARE( RandomAccessIterator first, RandomAccessIterator last )
	{
		if( first > last )
			throw misc::exception("Invalid iterator");

		const int _RANDOM_BITS = 15;	// minimum random bits from rand()
		const int _RANDOM_MAX = (1U << _RANDOM_BITS) - 1;

		RandomAccessIterator next = first;
		for (unsigned long index = 2; ++next != last; ++index)
		{	// assume unsigned long big enough for _Diff count
			unsigned long _Rm = _RANDOM_MAX;
			unsigned long _Rn = ::rand() & _RANDOM_MAX;

			// build random value
			for (; _Rm < index && _Rm != ~0UL; _Rm = _Rm << _RANDOM_BITS | _RANDOM_MAX)
				_Rn = _Rn << _RANDOM_BITS | (::rand() & _RANDOM_MAX);

			// swap a pair
			misc::iter_swap(next, first + ptrdiff_t(_Rn % index));
		}
	}

	// STLport\stlport\stl\_algo.c:540
	template <typename RandomAccessIterator>
	inline void random_shuffle_STLPORT ( RandomAccessIterator first, RandomAccessIterator last )
	{
		if( first > last )
			throw misc::exception("Invalid iterator");
		if (first == last)
			return;

		for (RandomAccessIterator it = first + 1; it != last; ++it)
			misc::iter_swap(it, first + ::rand() % ((it - first) + 1));
	}

	// apache_stl\include\algorithm.cc:591
	template <typename RandomAccessIterator>
	inline void random_shuffle_APACHESTL ( RandomAccessIterator first, RandomAccessIterator last )
	{
		if(first > last)
			throw misc::exception("Invalid iterator");

		if (!(first == last)) 
		{
			typedef typename misc::iterator_traits<RandomAccessIterator>::difference_type DiffT;
			DiffT limit = 2;

			for (RandomAccessIterator it = first; !(++it == last); ++limit) 
			{				
				const DiffT rndoff ( ::rand() % limit );

				if( !(0 <= rndoff && rndoff < limit) )
					throw misc::exception("ApacheSTL's random_shuffle exception.");
				misc::iter_swap (it, first + rndoff);
			}
		}
	}

	// http://en.cppreference.com/w/cpp/algorithm/random_shuffle	
	// obs: iterates in reverse order compared with: gnu,apache,stlport,ms
	template <typename RandomAccessIterator>
	inline void random_shuffle_CPPREFERENCE_COM ( RandomAccessIterator first, RandomAccessIterator last )
	{
		typename misc::iterator_traits<RandomAccessIterator>::difference_type i, n;
		n = (last-first);
		// reversed order of iteration
		for (i=n-1; i>0; --i)
		{
			misc::swap (first[i], first[ ::rand()%(i+1) ]);
		}
	}
	// end of implementations.
	//////////////////////////////////////////////////////////////////////////



	//partition   Partition range in two (function template )
	template <typename BidirectionalIterator, typename Predicate>
	inline BidirectionalIterator partition ( BidirectionalIterator first,
											 BidirectionalIterator last, Predicate pred )
	{
		while (true)
		{
			while (first!=last && pred(*first))
			{
				++first;
			}

			if (first==last--)
			{
				break;
			}

			while (first!=last && !pred(*last))
			{
				--last;
			}

			if (first==last)
			{
				break;
			}

			misc::swap (*first++,*last);
		}
		return first;
	}


	//stable_partition   Partition range in two - stable ordering (function template)
	template <typename BidirectionalIterator, typename Predicate>
	inline BidirectionalIterator stable_partition ( BidirectionalIterator first,
													BidirectionalIterator last,
													Predicate pred )
	{
		return misc::algobase::stable_partition(first, last, pred);
	}



	//////////////////////////////////////////////////////////////////////////
	//Sorting:
	//////////////////////////////////////////////////////////////////////////
	template<typename T>
	inline void quicksort(T* values, size_t first, size_t last)
	{
		size_t start;
		size_t end;
		size_t pivot;
		T k;


		if (first < last)
		{
			pivot = (first+last)/2;

			misc::swap(values[first], values[pivot]);

			k = values[first];
			start = (first+1);
			end = last;

			while (start <= end)
			{
				while ((start <= last) && (values[start] <= k))
				{
					start++;
				}
				while ((end >= first) && (values[end] > k))
				{
					end--;
				}
				if (start < end)
				{
					swap(values[start], values[end]);

				}
			}

			misc::swap(values[first], values[end]);
			misc::quicksort(values,first,(end-1));
			misc::quicksort(values,(end+1),last);
		}
	}


	////sort   Sort elements in range (function template)
	
	template<typename RandomAccessIterator>
	inline void sort(RandomAccessIterator first, RandomAccessIterator last)
	{
		misc::algobase::sort(first, last);
	}


	template <typename RandomAccessIterator, typename Compare>
	inline void sort ( RandomAccessIterator first, RandomAccessIterator last, Compare comp )
	{
		misc::algobase::sort(first, last, comp);
	}




	//stable_sort   Sort elements preserving order of equivalents (function template )
	template <typename RandomAccessIterator>
	inline void stable_sort ( RandomAccessIterator first, RandomAccessIterator last )
	{
		misc::algobase::stable_sort(first, last);
	}

	template <typename RandomAccessIterator, typename Compare>
	inline void stable_sort ( RandomAccessIterator first, RandomAccessIterator last,
							  Compare comp )
	{
		misc::algobase::stable_sort(first, last, comp);
	}


	//partial_sort   Partially Sort elements in range (function template)
	/*	Rearranges the elements in the range [first,last), in such a way 
		that the elements before middle are the smallest elements in the entire 
		range and are sorted in ascending order, while the remaining elements 
		are left without any specific order.
	*/
	template <typename RandomAccessIterator>
	inline void partial_sort ( RandomAccessIterator first, RandomAccessIterator middle,
							   RandomAccessIterator last )
	{
		misc::algobase::partial_sort(first, middle, last);
	}

	template <typename RandomAccessIterator, typename Compare>
	inline void partial_sort ( RandomAccessIterator first, RandomAccessIterator middle,
							   RandomAccessIterator last, Compare comp )
	{
		misc::algobase::partial_sort(first, middle, last, comp);
	}


	//partial_sort_copy   Copy and partially sort range (function template)
	template <typename InputIterator, typename RandomAccessIterator>
	inline RandomAccessIterator
	partial_sort_copy ( InputIterator first,InputIterator last,
						RandomAccessIterator result_first,
						RandomAccessIterator result_last )
	{
		return misc::algobase::partial_sort_copy(first, last, result_first, result_last);
	}



	template <typename InputIterator, typename RandomAccessIterator, typename Compare>
	inline RandomAccessIterator
	partial_sort_copy ( InputIterator first,InputIterator last,
						RandomAccessIterator result_first,
						RandomAccessIterator result_last, Compare comp )
	{
		return misc::algobase::partial_sort_copy(first, last, result_first, result_last, comp);
	}


	//nth_element   Sort element in range (function template)
	template <typename RandomAccessIterator>
	inline void nth_element ( RandomAccessIterator first, RandomAccessIterator nth,
							  RandomAccessIterator last )
	{
		misc::algobase::nth_element(first, nth, last);
	}



	template <typename RandomAccessIterator, typename Compare>
	inline void nth_element ( RandomAccessIterator first, RandomAccessIterator nth,
							  RandomAccessIterator last, Compare comp )
	{
		misc::algobase::nth_element(first, nth, last, comp);
	}


	//////////////////////////////////////////////////////////////////////////
	//Binary search (operating on sorted ranges):
	//////////////////////////////////////////////////////////////////////////
	//lower_bound   Return iterator to lower bound (function template )
	template <typename ForwardIterator, typename T>
	inline ForwardIterator lower_bound ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator it;
		typename misc::iterator_traits<ForwardIterator>::difference_type count, step;
		count = misc::distance(first,last);
		while (count > 0)
		{
			it = first;
			step = count / 2;
			misc::advance (it,step);

			if (*it<value) // or: if (comp(*it,value)), for the comp version
			{
				first = ++it;
				count -= step + 1;
			}
			else
			{
				count=step;
			}
		}
		return first;
	}


	template <typename ForwardIterator, typename T, typename Compare>
	inline ForwardIterator lower_bound ( ForwardIterator first, ForwardIterator last,
										 const T& value, Compare comp )
	{
		ForwardIterator it;
		typename misc::iterator_traits<ForwardIterator>::difference_type count, step;
		count = misc::distance(first,last);
		while (count>0)
		{
			it = first;
			step = count/2;
			misc::advance (it,step);

			if (comp(*it,value))
			{
				first = ++it;
				count -= step + 1;
			}
			else
			{
				count=step;
			}
		}
		return first;
	}


	//upper_bound   Return iterator to upper bound (function template )
	template <typename ForwardIterator, typename T>
	inline ForwardIterator upper_bound ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator it;
		typename misc::iterator_traits<ForwardIterator>::difference_type count, step;

		count = misc::distance(first,last);

		while (count > 0)
		{
			it = first;
			step = count / 2;
			misc::advance (it,step);

			if ( !(value<*it) )
			{
				first = ++it;
				count -= step + 1;
			}
			else
			{
				count=step;
			}
		}
		return first;
	}


	template <typename ForwardIterator, typename T, typename Compare>
	inline ForwardIterator upper_bound ( ForwardIterator first, ForwardIterator last, const T& value, Compare comp )
	{
		ForwardIterator it;
		typename misc::iterator_traits<ForwardIterator>::difference_type count, step;

		count = misc::distance(first,last);

		while (count > 0)
		{
			it = first;
			step = count / 2;
			misc::advance (it,step);

			if ( !comp(value,*it) )
			{
				first = ++it;
				count -= step + 1;
			}
			else
			{
				count = step;
			}
		}
		return first;
	}



	//equal_range   Get subrange of equal elements (function template)
	template <typename ForwardIterator, typename T>
	inline misc::pair<ForwardIterator,ForwardIterator>
	equal_range ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator it = misc::lower_bound (first,last,value);
		return misc::make_pair( it, misc::upper_bound(it,last,value) );
	}

	template <typename ForwardIterator, typename T, typename Compare>
	inline misc::pair<ForwardIterator,ForwardIterator>
	equal_range ( ForwardIterator first, ForwardIterator last, const T& value,
				  Compare comp )
	{
		return misc::algobase::equal_range(first, last, value, comp);
	}

	//binary_search   Test if value exists in sorted array (function template)
	template <typename ForwardIterator, typename T>
	inline bool binary_search ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		first = misc::lower_bound<ForwardIterator, T>(first,last,value);
		return (first != last && !(value < *first));
	}


	template <typename ForwardIterator, typename T, typename Compare>
	inline bool binary_search ( ForwardIterator first, ForwardIterator last,
								const T& value, Compare comp )
	{
		return misc::algobase::binary_search(first, last, value, comp);
	}

	//////////////////////////////////////////////////////////////////////////
	//Merge (operating on sorted ranges):
	//////////////////////////////////////////////////////////////////////////

	//merge   Merge sorted ranges (function template)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	inline OutputIterator merge ( InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2,
								  OutputIterator result )
	{
		while (true)
		{
			*result++ = (*first2<*first1) ? *first2++ : *first1++;
			if (first1==last1)
			{
				return misc::copy(first2,last2,result);
			}

			if (first2==last2)
			{
				return misc::copy(first1,last1,result);
			}
		}
	}

	template <typename InputIterator1, typename InputIterator2,
			  typename OutputIterator, typename Compare>
	inline OutputIterator merge ( InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2,
								  OutputIterator result, Compare comp )
	{
		while (true)
		{
			if( comp(*first2, *first1) )
			{
				*result++ = *first2++;
			}
			else
			{
				*result++ = *first1++;
			}

			if (first1==last1)
			{
				return misc::copy(first2,last2,result);
			}

			if (first2==last2)
			{
				return misc::copy(first1,last1,result);
			}
		}
	}


	//inplace_merge   Merge consecutive sorted ranges (function template )
	template <typename BidirectionalIterator>
	inline void inplace_merge ( BidirectionalIterator first, BidirectionalIterator middle,
								BidirectionalIterator last )
	{
		misc::algobase::inplace_merge(first, middle, last);
	}


	template <typename BidirectionalIterator, typename Compare>
	inline void inplace_merge ( BidirectionalIterator first, BidirectionalIterator middle,
								BidirectionalIterator last, Compare comp )
	{
		misc::algobase::inplace_merge(first, middle, last, comp);
	}


	//includes   Test whether sorted range includes another sorted range (function template )
	template <typename InputIterator1, typename InputIterator2>
	inline bool includes ( InputIterator1 first1, InputIterator1 last1,
						   InputIterator2 first2, InputIterator2 last2 )
	{
		while (first1 != last1)
		{
			if (*first2 < *first1)
			{
				break;
			}
			else if (*first1<*first2)
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}

			if (first2==last2)
			{
				return true;
			}
		}
		return false;
	}


	template <typename InputIterator1, typename InputIterator2, typename Compare>
	inline bool includes ( InputIterator1 first1, InputIterator1 last1,
						   InputIterator2 first2, InputIterator2 last2, Compare comp )
	{
		return misc::algobase::includes(first1, last1, first2, last2, comp);
	}


	//set_union   Union of two sorted ranges (function template )
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	inline OutputIterator set_union ( InputIterator1 first1, InputIterator1 last1,
									  InputIterator2 first2, InputIterator2 last2,
									  OutputIterator result )
	{
		while (true)
		{
			if (first1 == last1)
			{
				return misc::copy(first2,last2,result);
			}

			if (first2 == last2)
			{
				return misc::copy(first1,last1,result);
			}

			if (*first1 < *first2)
			{
				*result++ = *first1++;
			}
			else if (*first2 < *first1)
			{
				*result++ = *first2++;
			}
			else
			{
				*result++ = *first1++;
				first2++;
			}
		}
	}


	template <typename InputIterator1, typename InputIterator2,
			  typename OutputIterator, typename Compare>
	inline OutputIterator set_union ( InputIterator1 first1, InputIterator1 last1,
									  InputIterator2 first2, InputIterator2 last2,
									  OutputIterator result, Compare comp )
	{
		return misc::algobase::set_union(first1, last1, first2, last2, result, comp);
	}



	//set_intersection   Intersection of two sorted ranges (function template)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	inline OutputIterator set_intersection ( InputIterator1 first1, InputIterator1 last1,
											 InputIterator2 first2, InputIterator2 last2,
											 OutputIterator result )
	{
		while (first1!=last1 && first2!=last2)
		{
			if (*first1<*first2)
			{
				++first1;
			}
			else if (*first2<*first1)
			{
				++first2;
			}
			else
			{
				*result++ = *first1++;
				first2++;
			}
		}
		return result;
	}

	template <typename InputIterator1, typename InputIterator2,
			  typename OutputIterator, typename Compare>
	inline OutputIterator set_intersection ( InputIterator1 first1, InputIterator1 last1,
											 InputIterator2 first2, InputIterator2 last2,
											 OutputIterator result, Compare comp )
	{
		return misc::algobase::set_intersection(first1, last1, first2, last2, result, comp);
	}


	//set_difference   Difference of two sorted ranges (function template )
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	inline OutputIterator set_difference ( InputIterator1 first1, InputIterator1 last1,
										   InputIterator2 first2, InputIterator2 last2,
										   OutputIterator result )
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
			{
				*result++ = *first1++;
			}
			else if (*first2 < *first1)
			{
				first2++;
			}
			else
			{
				first1++;
				first2++;
			}
		}
		return misc::copy(first1,last1,result);
	}


	template <typename InputIterator1, typename InputIterator2,
			  typename OutputIterator, typename Compare>
	inline OutputIterator set_difference ( InputIterator1 first1, InputIterator1 last1,
										   InputIterator2 first2, InputIterator2 last2,
										   OutputIterator result, Compare comp )
	{
		return misc::algobase::set_difference(first1, last1, first2, last2, result, comp);
	}



	//set_symmetric_difference   Symmetric difference of two sorted ranges (function template)
	template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
	inline OutputIterator
	set_symmetric_difference ( InputIterator1 first1, InputIterator1 last1,
							   InputIterator2 first2, InputIterator2 last2,
							   OutputIterator result )
	{
		while (true)
		{
			if (first1 == last1)
			{
				return misc::copy(first2,last2,result);
			}

			if (first2 == last2)
			{
				return misc::copy(first1,last1,result);
			}

			if (*first1 < *first2)
			{
				*result++ = *first1++;
			}
			else if (*first2 < *first1)
			{
				*result++ = *first2++;
			}
			else
			{
				first1++;
				first2++;
			}
		}
	}


	template <typename InputIterator1, typename InputIterator2,
			  typename OutputIterator, typename Compare>
	inline OutputIterator
	set_symmetric_difference ( InputIterator1 first1, InputIterator1 last1,
							   InputIterator2 first2, InputIterator2 last2,
							   OutputIterator result, Compare comp )
	{
		return misc::algobase::set_symmetric_difference(first1, last1, first2, last2, result, comp);
	}


	//////////////////////////////////////////////////////////////////////////
	//Heap:
	//////////////////////////////////////////////////////////////////////////

	//push_heap   Push element into heap range (function template)
	template <typename RandomAccessIterator>
	inline void push_heap ( RandomAccessIterator first, RandomAccessIterator last )
	{
		misc::algobase::push_heap(first, last);
	}

	template <typename RandomAccessIterator, typename Compare>
	inline void push_heap ( RandomAccessIterator first, RandomAccessIterator last,
							Compare comp )
	{
		misc::algobase::push_heap(first, last, comp);
	}



	//pop_heap   Pop element from heap range (function template)
	template <typename RandomAccessIterator>
	inline void pop_heap ( RandomAccessIterator first, RandomAccessIterator last )
	{
		misc::algobase::pop_heap(first, last);
	}

	template <typename RandomAccessIterator, typename Compare>
	inline void pop_heap ( RandomAccessIterator first, RandomAccessIterator last,
						   Compare comp )
	{
		misc::algobase::pop_heap(first, last, comp);
	}


	//make_heap   Make heap from range (function template )
	template <typename RandomAccessIterator>
	inline void make_heap ( RandomAccessIterator first, RandomAccessIterator last )
	{
		misc::algobase::make_heap(first, last);
	}

	template <typename RandomAccessIterator, typename Compare>
	inline void make_heap ( RandomAccessIterator first, RandomAccessIterator last,
							Compare comp )
	{
		misc::algobase::make_heap(first, last, comp);
	}


	//sort_heap   Sort elements of heap (function template)
	template <typename RandomAccessIterator>
	inline void sort_heap ( RandomAccessIterator first, RandomAccessIterator last )
	{
		misc::algobase::sort_heap(first, last);
	}


	template <typename RandomAccessIterator, typename Compare>
	inline void sort_heap ( RandomAccessIterator first, RandomAccessIterator last,
							Compare comp )
	{
		misc::algobase::sort_heap(first, last, comp);
	}


	//////////////////////////////////////////////////////////////////////////
	//Min/max:
	//////////////////////////////////////////////////////////////////////////
	
	//min   Return the lesser of two arguments (function template )
	//		See algobase::min for explanation on macro expansion min vs (min)
	template <typename T>
	inline const T& (min) ( const T& a, const T& b )
	{		
		return (misc::algobase::min)(a, b);
	}

	template <typename T, typename Compare>
	inline const T& (min) ( const T& a, const T& b, Compare comp )
	{
		return (misc::algobase::min)(a, b, comp);
	}

	// extension -------------------------------------------------------------
	template<typename T>
	inline const T& (min) (const T& a, const T& b, const T& c)
	{
		const T& u = (misc::algobase::min) (a, b);
		return (misc::algobase::min)(u, c);
	}
	template<typename T>
	inline const T& (min) (const T& a, const T& b, const T& c, const T& d)
	{
		const T& u = (misc::algobase::min) (a, b);
		const T& v = (misc::algobase::min) (u, c);
		return (misc::algobase::min)(v, d);
	}
	template<typename T>
	inline const T& (min) (const T& a, const T& b, const T& c, const T& d, const T& e)
	{
		const T& u = (misc::algobase::min) (a, b);
		const T& v = (misc::algobase::min) (u, c);
		const T& w = (misc::algobase::min) (v, d);
		return (misc::algobase::min)(w, e);
	}	
	// extension -------------------------------------------------------------
	
	//max   Return the greater of two arguments (function template )
	template <typename T>
	inline const T& (max) ( const T& a, const T& b )
	{
		return (misc::algobase::max)(a, b);
	}

	template <typename T, typename Compare>
	inline const T& (max) ( const T& a, const T& b, Compare comp )
	{
		return (misc::algobase::max)(a, b, comp);
	}


	// extension -------------------------------------------------------------
	template<typename T>
	inline const T& (max) (const T& a, const T& b, const T& c)
	{
		const T& u = (misc::algobase::max) (a, b);
		return (misc::algobase::max)(u, c);
	}
	template<typename T>
	inline const T& (max) (const T& a, const T& b, const T& c, const T& d)
	{
		const T& u = (misc::algobase::max) (a, b);
		const T& v = (misc::algobase::max) (u, c);
		return (misc::algobase::max)(v, d);
	}
	template<typename T>
	inline const T& (max) (const T& a, const T& b, const T& c, const T& d, const T& e)
	{
		const T& u = (misc::algobase::max) (a, b);
		const T& v = (misc::algobase::max) (u, c);
		const T& w = (misc::algobase::max) (v, d);
		return (misc::algobase::max)(w, e);
	}	
	// extension -------------------------------------------------------------


	//min_element   Return smallest element in range (function template)
	template <typename ForwardIterator>
	inline ForwardIterator min_element ( ForwardIterator first, ForwardIterator last )
	{
		if (first==last) return last;
		ForwardIterator lowest = first;
		while (++first!=last)
			if (*first<*lowest)
				lowest=first;
		return lowest;
	}



	template <typename ForwardIterator, typename Compare>
	inline ForwardIterator min_element ( ForwardIterator first, ForwardIterator last,
										 Compare comp )
	{
		ForwardIterator lowest = first;
		if (first==last) return last;
		while (++first!=last)
			if (comp(*first,*lowest))
				lowest=first;
		return lowest;
	}

	//max_element   Return largest element in range (function template )
	template <typename ForwardIterator>
	inline ForwardIterator max_element ( ForwardIterator first, ForwardIterator last )
	{
		ForwardIterator largest = first;
		if (first==last) return last;
		while (++first!=last)
			if (*largest<*first)
				largest=first;
		return largest;
	}

	template <typename ForwardIterator, typename Compare>
	inline ForwardIterator max_element ( ForwardIterator first, ForwardIterator last,
										 Compare comp )
	{
		ForwardIterator largest = first;
		if (first==last) return last;
		while (++first!=last)
			if (comp(*largest,*first))
				largest=first;
		return largest;
	}


	/*
		$25.3.8	lexicographical_compare   Lexicographical less-than comparison (function template )
		
		true if the sequence of elements defined by the range [first1, last1) 
		is lexicographically less than the sequence of elements defined by the 
		range [first2, last2).
	*/
	template <typename InputIterator1, typename InputIterator2>
	inline bool lexicographical_compare ( InputIterator1 first1, InputIterator1 last1,
										  InputIterator2 first2, InputIterator2 last2 )
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2 < *first1) return false;
			else if (*first1 < *first2) return true;
			first1++; first2++;
		}
		return (first2!=last2);
	}


	template <typename InputIterator1, typename InputIterator2, typename Compare>
	inline bool lexicographical_compare ( InputIterator1 first1, InputIterator1 last1,
										  InputIterator2 first2, InputIterator2 last2,
										  Compare comp )
	{
		return misc::algobase::lexicographical_compare(first1, last1, first2, last2, comp);
	}


	//next_permutation   Transform range to next permutation (function template)
	template <typename BidirectionalIterator>
	inline bool next_permutation (BidirectionalIterator first,
								  BidirectionalIterator last )
	{
		return misc::algobase::next_permutation<BidirectionalIterator>(first, last);
	}


	template <typename BidirectionalIterator, typename Compare>
	inline bool next_permutation (BidirectionalIterator first,
								  BidirectionalIterator last, Compare comp)
	{
		return misc::algobase::next_permutation<BidirectionalIterator>(first, last, comp);
	}


	//prev_permutation   Transform range to previous permutation (function template)
	template <typename BidirectionalIterator>
	inline bool prev_permutation (BidirectionalIterator first,
								  BidirectionalIterator last )
	{
		return misc::algobase::prev_permutation(first, last);
	}


	template <typename BidirectionalIterator, typename Compare>
	inline bool prev_permutation (BidirectionalIterator first,
								  BidirectionalIterator last, Compare comp)
	{
		return misc::algobase::prev_permutation(first, last, comp);
	}

}//namespace misc




#endif//__algorithm_hpp__




