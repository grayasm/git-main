/*
Copyright (C) 2012 Mihai Vasilian
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

