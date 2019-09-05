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


#ifndef __queue_hpp__
#define __queue_hpp__


#include "deque.hpp"


namespace stl
{
	// FIFO queue implemented with a container
	template<typename T, typename container = stl::deque<T> >
    class queue
    {
    public:
        typedef container								container_type;
        typedef typename container::value_type			value_type;
        typedef typename container::size_type			size_type;
        typedef typename container::reference			reference;
        typedef typename container::const_reference		const_reference;


        explicit queue(const container_type& cont = container_type())
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

        reference front()
        {
            return m_cont.front();
        }

        const_reference front() const
        {
            return m_cont.front();
        }

        reference back()
        {
            return m_cont.back();
        }

        const_reference back() const
        {
            return (m_cont.back());
        }

        void push(const value_type& val)
        {
            m_cont.push_back(val);
        }

        void pop()
        {
            m_cont.pop_front();
        }


		//	Not part of standard - work around a problem in MS compiler.
		//	Cannot resolve external symbol
		//	bool operator==(const queue&, const queue&);
		const container& get_cont() const { return m_cont; }

    protected:
        container m_cont;
    };  // queue


    template<typename T, typename container>
    inline bool operator==(const queue<T, container>& left,
                           const queue<T, container>& right)
    {
        return left.get_cont() == right.get_cont();
    }


	template<typename T, typename container>
	inline bool operator<(const queue<T, container>& left,
		const queue<T, container>& right)
	{
		return left.get_cont() < right.get_cont();
	}
	
	template<typename T, typename container>
    inline bool operator!=(const queue<T, container>& left,
                           const queue<T, container>& right)
    {
        return !(left == right);
    }

    template<typename T, typename container>
    inline bool operator>(const queue<T, container>& left,
                          const queue<T, container>& right)
    {
        return right < left;
    }

    template<typename T, typename container>
    inline bool operator<=(const queue<T, container>& left,
                           const queue<T, container>& right)
    {
        return !(right < left);
    }

    template<typename T, typename container>
    inline bool operator>=(const queue<T, container>& left,
                           const queue<T, container>& right)
    {
        return !(left < right);
    }
	
	//########################################################################
	template<
		typename T, 
		typename container = stl::vector<T>,
		typename compare = stl::less<typename container::value_type> 
	>
	class priority_queue
	{
	public:
		typedef container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;		
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

	protected:
		container_type	m_cont;
		compare			m_comp;

	public:

		explicit priority_queue(
			const compare& cmp = compare(),
			const container_type& cont   = container_type()
			)
			: m_cont(cont)
			, m_comp(cmp)
		{
			stl::make_heap(m_cont.begin(), m_cont.end(), m_comp);
		}

		template<class InputIterator>
		priority_queue(
			InputIterator first, InputIterator last,
			const compare& cmp = compare(),
			const container& cont = container_type()
			)
			: m_cont(cont)
			, m_comp(cmp)
		{
			m_cont.insert(m_cont.end(), first, last);
			stl::make_heap(m_cont.begin(), m_cont.end(), m_comp);
		}

		bool empty() const
		{
			return m_cont.empty();
		}

		size_type size() const
		{
			return m_cont.size();
		}

		const_reference top() const
		{
			return m_cont.front();
		}

		void push(const value_type& val)
		{
			m_cont.push_back(val);
			stl::push_heap(m_cont.begin(), m_cont.end(), m_comp);
		}

		void pop() 
		{
			stl::pop_heap(m_cont.begin(), m_cont.end(), m_comp);
			m_cont.pop_back();
		}
	};  // priority_queue
	//########################################################################

}  // namespace

#endif//__queue_hpp__




