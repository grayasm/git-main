/*
  Copyright (C) 2013 Mihai Vasilian

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



#ifndef __vector_hpp__
#define __vector_hpp__



#include "generic_array.hpp"



namespace misc
{
	/*!
		ISO/IEC 14882:2003  $23.2.4 Class template vector

		One exception from ISO is the extended attribute(s),
		to indicate additional properties of this container like 
		debug_iterator, multi threading, etc.
		More details can be found in class misc::generic_array.
	*/
	template<typename T, typename Allocator = misc::allocator<T>, int attributes = 0>
	class vector : private generic_array<T, Allocator, attributes>
	{
	public:
		typedef vector<T, Allocator, attributes>						container;
		typedef typename misc::generic_array<T, Allocator, attributes>	base;		

		// types:
		typedef typename base::value_type                value_type;
		typedef typename base::size_type                 size_type;
		typedef typename base::difference_type           difference_type;

		typedef typename base::reference                 reference;
		typedef typename base::const_reference           const_reference;
		typedef typename base::pointer                   pointer;
		typedef typename base::const_pointer             const_pointer;

	public:
		typedef typename base::iterator					iterator;
		typedef typename base::const_iterator			const_iterator;
		typedef typename base::reverse_iterator			reverse_iterator;
		typedef typename base::const_reverse_iterator	const_reverse_iterator;

	public:
		// extension
		static const int nattributes = base::nattributes;     

	public:       
		// $23.2.4.1 construct/copy/destroy:
		vector()
			: base()
		{
		}

		explicit vector(size_type n, const T& value = T())
			: base(n, value)
		{
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			: base(first, last)
		{
		}

		vector(const container& x)
			: base(x)
		{
		}

		~vector()
		{
		}

		container& operator=(const container& x)
		{
			base::operator =(x);
			return *this;
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			base::assign(first, last);
		}

		void assign(size_type n, const T& u)
		{
			base::assign(n, u);
		}

		// iterators:
		iterator begin()
		{
			return base::begin();
		}

		const_iterator begin() const
		{
			return base::begin();
		}

		iterator end()
		{
			return base::end();
		}

		const_iterator end() const
		{
			return base::end();
		}

		reverse_iterator rbegin()
		{
			return base::rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return base::rbegin();
		}

		reverse_iterator rend()
		{
			return base::rend();
		}

		const_reverse_iterator rend() const
		{
			return base::rend();
		}

		// 23.2.4.2 capacity:
		size_type size() const
		{
			return base::size();
		}

		size_type max_size() const
		{
			return base::max_size();
		}

		void resize(size_type sz, T c = T())
		{
			return base::resize(sz, c);
		}

		size_type capacity() const
		{
			return base::capacity();
		}

		bool empty() const
		{
			return base::empty();
		}

		void reserve(size_type n)
		{
			return base::reserve(n);
		}

		// element access:
		reference operator[](size_type n)
		{
			return base::operator [](n);
		}

		const_reference operator[](size_type n) const
		{
			return base::operator [](n);
		}

		const_reference at(size_type n) const
		{
			return base::at(n);
		}

		reference at(size_type n)
		{
			return base::at(n);
		}

		reference front()
		{
			return base::front();
		}

		const_reference front() const
		{
			return base::front();
		}

		reference back()
		{
			return base::back();
		}

		const_reference back() const
		{
			return base::back();
		}

		// 23.2.4.3 modifiers:
		void push_back(const T& x)
		{
			base::push_back(x);
		}

		void pop_back()
		{
			base::pop_back();
		}

		iterator insert(iterator position, const T& x)
		{
			return base::insert(position, x);
		}

		void insert(iterator position, size_type n, const T& x)
		{
			return base::insert(position, n, x);
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			return base::insert(position, first, last);
		}

		iterator erase(iterator position)
		{
			return base::erase(position);
		}

		iterator erase(iterator first, iterator last)
		{
			return base::erase(first, last);
		}

		void swap(container& x)
		{
			return base::swap(x);
		}

		void clear()
		{
			base::clear();
		}

#if 1	// Until the ambiguity with global operators gets solved, execute this.
		bool operator==(const container& Right)
		{
			return generic_array_ops::operator ==(*this, Right);
		}

		bool operator<(const container& Right)
		{
			return generic_array_ops::operator <(*this, Right);
		}
		
		bool operator!=(const container& Right)
		{
			return !(*this == Right);
		}
		
		bool operator>(const container& Right)
		{			
			return (*this != Right) && !(*this < Right);
		}

		bool operator>=(const container& Right)
		{
			return !(*this < Right);
		}

		bool operator<=(const container& Right)
		{
			return (*this < Right) || (*this == Right);
		}
		
#endif
	};  // class



#if 0	//Ambiguity in fxcm application. Disabled until it gets fixed.
	template<typename T, typename Allocator, int attributes>
	bool operator== (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		
		typedef misc::vector<T, Allocator, attributes> Cont;
		
		typename Cont::size_type sz = Left.size();
		if(sz != Right.size())
			return false;

		typename Cont::size_type j = 0;
		while(j < sz && Left[j] == Right[j])
			++j;

		return j == sz;
		
	}

	template<typename T, typename Allocator, int attributes>
	bool operator< (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		return misc::lexicographical_compare(
			Left.begin(), Left.end(), Right.begin(), Right.end());
	}

	template<typename T, typename Allocator, int attributes>
	bool operator!= (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		return !(Left == Right);
	}

	template<typename T, typename Allocator, int attributes>
	bool operator> (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		return (Left != Right) && !(Left < Right);
	}

	template<typename T, typename Allocator, int attributes>
	bool operator>= (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		return !(Left < Right);
	}

	template<typename T, typename Allocator, int attributes>
	bool operator<= (
		const misc::vector<T, Allocator, attributes>& Left,
		const misc::vector<T, Allocator, attributes>& Right)
	{
		return (Left < Right) || (Left == Right);
	}

	// specialized algorithms:
	template<typename T, typename Allocator, int attributes>
	void swap (
		misc::vector<T, Allocator, attributes>& Left, 
		misc::vector<T, Allocator, attributes>& Right)
	{
		return Left.swap(Right);
	}
#endif
}  // namespace

#endif//__vector_hpp__
