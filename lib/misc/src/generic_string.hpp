/*
  Copyright (C) 2011 Mihai Vasilian

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

#ifndef __generic_string_hpp__
#define __generic_string_hpp__


#include "generic_array.hpp"



namespace misc
{

	/*!
		  ISO/IEC 14882:2003  $21.3 Class template basic_string

		  One exception from ISO is the extended attribute(s),
		  to indicate additional properties of this container like 
		  debug_iterator, multi threading, etc.
		  More details can be found in class misc::generic_array.
	 */
	template<typename T, typename Allocator = misc::allocator<T>, int attributes = 0>
	class generic_string : private generic_array<T, Allocator, attributes>
	{
		typedef typename misc::generic_array<T, Allocator, attributes> base;
		typedef typename misc::generic_string<T, Allocator, attributes> container;

	public:
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
		static const size_type npos = base::npos;
		// extension
		static const int nattributes = base::nattributes;

	public:
		/*! $21.3.1 */
		generic_string()
			: base()
		{
		}

		generic_string(const container& x)
			: base(x)
		{
		}


		generic_string(const container& str, size_type off, size_type count = npos)
			: base(str, off, count)
		{
		}

		generic_string(const value_type* ptr, size_type count)
			: base(ptr, count)
		{
		}

		generic_string(const value_type* ptr)
			: base(ptr)
		{
		}


		generic_string(size_type n, value_type c)
			: base(n, c)
		{
		}


		template<class InputIterator>
		generic_string(InputIterator begin, InputIterator end)
			: base(begin, end)
		{
		}

		~generic_string()
		{
		}

		/* $21.3.1 (assignment operators) */
		container& operator=(const container& str)
		{
			base::operator =(str);
			return *this;
		}

		container& operator=(const value_type* ptr)
		{
			base::operator =(ptr);
			return *this;
		}

		container& operator=(value_type ch)
		{
			base::operator =(ch);
			return *this;
		}


		//$21.3.2 iterators
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

		//$21.3.3 capacity
		size_type size() const
		{
			return base::size();
		}

		size_type length() const
		{
			return base::length();
		}

		size_type max_size() const
		{
			return base::max_size();
		}

		void resize(size_type sz, value_type c = value_type())
		{
			base::resize(sz,c);
		}

		size_type capacity() const
		{
			return base::capacity();
		}

		void reserve(size_type n)
		{
			base::resize(n);
		}

		void clear( )
		{
			base::clear();
		}

		bool empty () const
		{
			return base::empty();
		}

		//$21.3.4 element access:
		reference operator[] ( size_type n ) const
		{
			return base::operator [](n);
		}

		reference operator[] ( size_type n )
		{
			return base::operator [](n);
		}

		reference at ( size_type n ) const
		{
			return base::at(n);
		}

		reference at ( size_type n )
		{
			return base::at(n);
		}

		//$21.3.5 modifiers

		/* $21.3.5 modifiers ( operator += (...) ) */
		container& operator+=(const container& str)
		{
			base::operator +=(str);
			return *this;
		}

		container& operator+=(const value_type* ptr)
		{
			base::operator +=(ptr);
			return *this;
		}

		container& operator+=(value_type ch)
		{
			base::operator +=(ch);
			return *this;
		}

		/* $21.3.5 modifiers (append) */
		container& append(const container& str)
		{
			base::append(str);
			return *this;
		}

		container& append(const container& str, size_type p2, size_type n2)
		{
			base::append(str,p2,n2);
			return *this;
		}

		container& append(const value_type* ptr, size_type n2)
		{
			base::append(ptr,n2);
			return *this;
		}

		container& append(const value_type* ptr)
		{
			base::append(ptr);
			return *this;
		}


		container& append(size_type n, value_type value)
		{
			base::append(n, value);
			return *this;
		}


		template<typename InputIterator>
		container& append(InputIterator first, InputIterator last)
		{
			base::append(first, last);
			return *this;
		}


		/* $21.3.5 modifiers ( push_back ) */
		void push_back(const value_type& x)
		{
			base::push_back(x);
		}


		/* $21.3.5 modifiers ( assign ) */
		container& assign(const container& str)
		{
			base::assign(str);
			return *this;
		}

		container& assign(const container& str, size_type p2, size_type n2)
		{
			base::assign(str, p2, n2);
			return *this;
		}

		container& assign(const value_type* ptr, size_type n2)
		{
			base::assign(ptr, n2);
			return *this;
		}

		container& assign(const value_type* ptr)
		{
			base::assign(ptr);
			return *this;
		}

		container& assign(size_type count, const value_type& val)
		{
			base::assign(count, val);
			return *this;
		}

		template <typename InputIterator>
		container& assign(InputIterator first, InputIterator last)
		{
			base::assign(first, last);
			return *this;
		}


		/* $21.3.5 modifiers ( insert ) */
		container& insert(size_type p1, const container& str)
		{
			base::insert(p1, str);
			return *this;
		}

		container& insert(size_type p1, const container& str, size_type p2, size_type n2)
		{
			base::insert(p1, str, p2, n2);
			return *this;
		}

		container& insert(size_type p1, const value_type* ptr, size_type n2)
		{
			base::insert(p1, ptr, n2);
			return *this;
		}

		container& insert(size_type p1, const value_type* ptr)
		{
			base::insert(p1, ptr);
			return *this;
		}

		container& insert(size_type p1, size_type n2, value_type ch)
		{
			base::insert(p1, n2, ch);
			return *this;
		}

		iterator insert(iterator position, const value_type& x)
		{
			return base::insert(position, x);
		}

		void insert(iterator position, size_type n, const value_type& x)
		{
			base::insert(position, n, x);
		}

		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			base::insert(position, first, last);
		}


		/* $21.3.5 modifiers ( erase ) */
		container& erase(size_type p1 = 0, size_type n1 = npos)
		{
			base::erase(p1, n1);
			return *this;
		}

		iterator erase(iterator position)
		{
			return base::erase(position);
		}

		iterator erase(iterator first, iterator last)
		{
			return base::erase(first, last);
		}


		/* $21.3.5 modifiers ( replace ) */
		container& replace(size_type p1, size_type n1, const container& str)
		{
			base::replace(p1, n1, str);
			return *this;
		}

		container& replace(size_type p1, size_type n1, const container& str, size_type p2, size_type n2)
		{
			base::replace(p1, n1, str, p2, n2);
			return *this;
		}

		container& replace(size_type p1, size_type n1, const value_type* ptr, size_type n2)
		{
			base::replace(p1, n1, ptr, n2);
			return *this;
		}

		container& replace(size_type p1, size_type n1, const value_type* ptr)
		{
			base::replace(p1, n1, ptr);
			return *this;
		}

		container& replace(size_type p1, size_type n1, size_type n2, value_type ch)
		{
			base::replace(p1, n1, n2, ch);
			return *this;
		}

		container& replace(iterator first, iterator last, const container& str)
		{
			base::replace(first, last, str);
			return *this;
		}

		container& replace(iterator first, iterator last, const value_type* ptr, size_type n2)
		{
			base::replace(first, last, ptr, n2);
			return *this;
		}

		container& replace(iterator first, iterator last, const value_type* ptr)
		{
			base::replace(first, last, ptr);
			return *this;
		}

		container& replace(iterator first, iterator last, size_type n2, value_type ch)
		{
			base::replace(first, last, n2, ch);
			return *this;
		}


		template<typename InputIterator>
		container& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
		{
			base::replace(first, last, first2, last2);
			return *this;
		}


		/* $21.3.5 modifiers ( copy ) */
		size_type copy(value_type* ptr, size_type n1, size_type p1 = 0) const
		{
			return base::copy(ptr, n1, p1);
		}


		/* $21.3.5 modifiers ( swap ) */
		void swap(container& str)
		{
			base::swap(str);
		}


		/* $21.3.6 string operations */
		const value_type* c_str() const
		{
			return base::c_str();
		}

		const value_type* data() const
		{
			return base::data();
		}

		/* $21.3.6 string operations (find) */
		size_type find(const container& str, size_type p1 = 0) const
		{
			return base::find(str, p1);
		}

		size_type find(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::find(ptr, p1, n2);
		}

		size_type find(const value_type* ptr, size_type p1 = 0) const
		{
			return base::find(ptr, p1);
		}

		size_type find(value_type ch, size_type p1 = 0) const
		{
			return base::find(ch, p1);
		}


		/* $21.3.6 string operations (rfind) */
		size_type rfind(const container& str, size_type p1 = npos) const
		{
			return base::rfind(str, p1);
		}

		size_type rfind(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::rfind(ptr, p1, n2);
		}

		size_type rfind(const value_type* ptr, size_type p1 = npos) const
		{
			return base::rfind(ptr, p1);
		}

		size_type rfind(value_type ch, size_type p1 = npos) const
		{
			return base::rfind(ch, p1);
		}


		/* $21.3.6 string operations (find_first_of) */
		size_type find_first_of(const container& str, size_type pos = 0) const
		{
			return base::find_first_of(str, pos);
		}

		size_type find_first_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::find_first_of(ptr, p1, n2);
		}

		size_type find_first_of(const value_type* ptr, size_type p1 = 0) const
		{
			return base::find_first_of(ptr, p1);
		}

		size_type find_first_of(value_type c, size_type p1 = 0) const
		{
			return base::find_first_of(c, p1);
		}

		/* $21.3.6 string operations (find_last_of) */
		size_type find_last_of(const container& str, size_type p1 = npos) const
		{
			return base::find_last_of(str, p1);
		}

		size_type find_last_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::find_last_of(ptr, p1, n2);
		}

		size_type find_last_of(const value_type* ptr, size_type p1 = npos) const
		{
			return base::find_last_of(ptr, p1);
		}

		size_type find_last_of(value_type ch, size_type p1 = npos) const
		{
			return base::find_last_of(ch, p1);
		}

	   /* $21.3.6 string operations (find_first_not_of) */
		size_type find_first_not_of(const container& str, size_type p1 = 0) const
		{
			return base::find_first_not_of(str, p1);
		}

		size_type find_first_not_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::find_first_not_of(ptr, p1, n2);
		}

		size_type find_first_not_of(const value_type* ptr, size_type n1 = 0) const
		{
			return base::find_first_not_of(ptr, n1);
		}

		size_type find_first_not_of(value_type ch, size_type p1 = 0) const
		{
			return base::find_first_not_of(ch, p1);
		}


		/* $21.3.6 string operations (find_last_not_of) */
		size_type find_last_not_of(const container& str, size_type p1 = npos) const
		{
			return base::find_last_not_of(str, p1);
		}

		size_type find_last_not_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			return base::find_last_not_of(ptr, p1, n2);
		}

		size_type find_last_not_of(const value_type* ptr, size_type p1 = npos) const
		{
			return base::find_last_not_of(ptr, p1);
		}

		size_type find_last_not_of(value_type ch, size_type p1 = npos) const
		{
			return base::find_last_not_of(ch, p1);
		}


		/* $21.3.6 string operations (substr) */
		container substr(size_type p1 = 0, size_type n1 = npos) const
		{
			base b = base::substr(p1, n1);
			return container(b.begin(), b.end());
		}


		/* $21.3.6 string operations (compare) */
		int compare(const container& str) const
		{
			return base::compare(str);
		}

		int compare(size_type p1, size_type n1, const container& str) const
		{
			return base::compare(p1, n1, str);
		}

		int compare(size_type p1, size_type n1, const container& str, size_type p2, size_type n2) const
		{
			return base::compare(p1, n1, str, p2, n2);
		}

		int compare(const value_type* ptr) const
		{
			return base::compare(ptr);
		}

		int compare(size_type p1, size_type n1, const value_type* ptr) const
		{
			return base::compare(p1, n1, ptr);
		}

		int compare(size_type p1, size_type n1, const value_type* ptr, size_type n2) const
		{
			return base::compare(p1, n1, ptr, n2);
		}

		/*
		 *	MS Compiler issue fails to deduce template arguments for misc::string
		 *	while calling global operators with 1 or 2 string operands (as below).
		 *	
		 *	std::less<misc::string> comp;
		 *	misc::string s1("0"), s2("1");
		 *	bool res = comp(s1, s2); <--- error
		 *	
		 *	Moving all global operators with left operand as misc::string, inside
		 *	generic_string class.
		 */

		//Concatenates two string objects.
		container operator+(const container& Right) const
		{
			misc::generic_string<T> res(*this);
			res += Right;
			return res;
		}
		
		container operator+(const T* Right) const
		{
			container res(*this);
			res += Right;
			return res;
		}
		
		container operator+(const T Right) const
		{
			container res(*this);
			res += Right;
			return res;
		}

		bool operator!=(const container& Right) const
		{
			return compare(Right) != 0;
		}
		
		bool operator!=(const T* Right) const
		{
			return compare(Right) != 0;
		}

		bool operator==(const container& Right) const
		{
			return compare(Right) == 0;
		}

		bool operator==(const T* Right) const
		{
			return compare(Right) == 0;
		}
		
		bool operator<(const container& Right) const
		{
			return compare(Right) < 0;
		}

		bool operator<(const T* Right) const
		{
			return compare(Right) < 0;
		}

		bool operator<=(const container& Right) const
		{
			return compare(Right) <= 0;
		}

		bool operator<=(const T* Right) const
		{
			return compare(Right) <= 0;
		}

		bool operator>(const container& Right) const
		{
			return compare(Right) > 0;
		}

		bool operator>(const T* Right) const
		{
			return compare(Right) > 0;
		}

		bool operator>=(const container& Right) const
		{
			return compare(Right) >= 0;
		}

		bool operator>=(const T* Right) const
		{
			return compare(Right) >= 0;
		}
	};  // class
}  // namespace


//########################################################################
// Operators
// 
// Commented operators are moved inside generic_string to avoid compiler errors
// about unknown template arguments during matching of operands.

#if 0

/*
 *	MS Compiler issue error while trying to deduce template argument for misc::string
 *	std::less<misc::string> comp;
 *	misc::string s1("0"), s2("1");
 *	bool res = comp(s1, s2); <--- error using global operators
 *	
 *	Moving all global operators with left operand as misc::string, inside
 *	generic_string class.
 */

//Concatenates two string objects.
template<typename T, typename Allocator, int attributes>
misc::generic_string<T, Allocator, attributes> operator+(
	const misc::generic_string<T, Allocator, attributes>& Left,
	const misc::generic_string<T, Allocator, attributes>& Right)
{
	misc::generic_string<T> res(Left);
	res += Right;
	return res;
}


template<typename T, typename Allocator, int attributes>
misc::generic_string<T, Allocator, attributes> operator+(
	const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	misc::generic_string<T> res(Left);
	res += Right;
	return res;
}

template<typename T, typename Allocator, int attributes>
misc::generic_string<T, Allocator, attributes> operator+(
	const misc::generic_string<T, Allocator, attributes>& Left, const T Right)
{
	misc::generic_string<T> res(Left);
	res += Right;
	return res;
}
#endif



template<typename T, typename Allocator, int attributes>
misc::generic_string<T, Allocator, attributes> operator+(
	const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	misc::generic_string<T> res(Left);
	res += Right;
	return res;
}

template<typename T, typename Allocator, int attributes>
misc::generic_string<T, Allocator, attributes> operator+(
	const T Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	misc::generic_string<T> res(1, Left);
	res += Right;
	return res;
}



#if 0

//Tests if the string object on the left side of the operator is not equal
//to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator!=(
				const misc::generic_string<T, Allocator, attributes>& Left, 
				const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) != 0;
}

template<typename T, typename Allocator, int attributes>
bool operator!=(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) != 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator!=(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) != 0;
}



#if 0
//Tests if the string object on the left side of the operator is equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator==(
				const misc::generic_string<T, Allocator, attributes>& Left, 
				const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) == 0;
}

template<typename T, typename Allocator, int attributes>
bool operator==(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) == 0;
}

#endif 



template<typename T, typename Allocator, int attributes>
bool operator==(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) == 0;
}


#if 0
//Tests if the string object on the left side of the operator is less than to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator<(
				const misc::generic_string<T, Allocator, attributes>& Left, 
				const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) < 0;
}

template<typename T, typename Allocator, int attributes>
bool operator<(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) < 0;
}

#endif



template<typename T, typename Allocator, int attributes>
bool operator<(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) > 0;
}


#if 0
//Tests if the string object on the left side of the operator is less than or equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator<=(
				const misc::generic_string<T, Allocator, attributes>& Left, 
				const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) <= 0;
}

template<typename T, typename Allocator, int attributes>
bool operator<=(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) <= 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator<=(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) >= 0;
}

//A template function that writes a string into the output stream.
template<typename T, typename Allocator, int attributes>
std::basic_ostream<T>& operator<<(
	std::basic_ostream<T>& Ostr, const misc::generic_string<T, Allocator, attributes>& str)
{
	Ostr << str.c_str();
	return Ostr;
}


#if 0
//Tests if the string object on the left side of the operator is greater
//than to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator>(
			   const misc::generic_string<T, Allocator, attributes>& Left, 
			   const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) > 0;
}

template<typename T, typename Allocator, int attributes>
bool operator>(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) > 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator>(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) < 0;
}


#if 0
//Tests if the string object on the left side of the operator is greater
//than or equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator>=(
				const misc::generic_string<T, Allocator, attributes>& Left, 
				const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Left.compare(Right) >= 0;
}

template<typename T, typename Allocator, int attributes>
bool operator>=(const misc::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
	return Left.compare(Right) >= 0;
}
#endif



template<typename T, typename Allocator, int attributes>
bool operator>=(const T* Left, const misc::generic_string<T, Allocator, attributes>& Right)
{
	return Right.compare(Left) <= 0;
}

//A template function that reads a string from an input stream.
template<typename T, typename Allocator, int attributes>
std::basic_istream<T>& operator>>(
	std::basic_istream<T>& Istr, misc::generic_string<T, Allocator, attributes>& Right)
{
	std::basic_string<T> chunk;
	Istr >> chunk;
	Right += chunk.c_str();
	return Istr;
}

//Specialized template function
//Exchanges the arrays of characters of two strings.
template<typename T, typename Allocator, int attributes>
void swap(
		  misc::generic_string<T, Allocator, attributes>& Left, 
		  misc::generic_string<T, Allocator, attributes>& Right)
{
	Left.swap(Right);
}

#endif//__generic_string_hpp__
