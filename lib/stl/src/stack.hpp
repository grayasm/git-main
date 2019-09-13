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


#ifndef __stack_hpp__
#define __stack_hpp__


#include "deque.hpp"

namespace stl
{
	// LIFO queue implemented with a container
	template<typename T, typename container = stl::deque<T> >
	class stack
	{
	public:
		typedef container									container_type;
		typedef typename container::value_type				value_type;
		typedef typename container::size_type				size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

	protected:
		container m_cont;

	public:
		explicit stack(const container& cont = container())
			: m_cont(cont)
		{
		}

		bool empty() const
		{
			return m_cont.empty();
		}

		size_type size() const
		{
			return m_cont.size();
		}

		value_type& top()
		{
			return m_cont.back();
		}

		const value_type& top() const
		{
			return m_cont.back();
		}

		void push(const T& x)
		{
			m_cont.push_back(x);
		}

		void pop()
		{
			m_cont.pop_back();
		}    

		//	Not part of standard - work around a problem in MS compiler.
		//	Cannot resolve external symbol
		//	bool operator==(const stack&, const stack&);
		const container& get_cont() const { return m_cont; }
	};  // stack

	//////////////////////////////////////////////////////////////////////////

	template<typename T, typename container>
	inline bool operator==(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return (left.get_cont() == right.get_cont());
	}

	template<typename T, typename container>
	inline bool operator<(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return (left.get_cont() < right.get_cont());
	}

	template<typename T, typename container>
	inline bool operator!=(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return !(left == right);
	}
    
	template<typename T, typename container>
	inline bool operator>(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return (right < left);
	}

	template<typename T, typename container>
	inline bool operator<=(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return !(right < left);
	}

	template<typename T, typename container>
	inline bool operator>=(
		const stack<T, container>& left,
		const stack<T, container>& right)
	{
		return !(left < right);
	}
	//////////////////////////////////////////////////////////////////////////

}  // namespace


#endif//__stack_hpp__

