/*
Copyright (C) 2012 Mihai Vasilian
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




