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

#ifndef __deque_hpp__
#define __deque_hpp__


//c/c++
//libraries
#include "vector.hpp"
#include "list.hpp"
#include "algorithm.hpp"
#include "functional.hpp"
#include "utility.hpp"



namespace misc
{

	template<typename T, typename Allocator, int attributes> 
	class deque;

	template<typename container>
	class deque_iterator : 
		public misc::iterator<misc::random_access_iterator_tag, typename container::value_type>
	{
	public:
		typedef misc::iterator<misc::random_access_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category    iterator_category;
		typedef typename base::value_type           value_type;
		typedef typename base::difference_type      difference_type;
		typedef typename base::distance_type        distance_type;
		typedef typename base::pointer              pointer;
		typedef typename base::reference            reference;
		typedef typename container::size_type       size_type;
		friend class misc::deque<typename container::value_type, typename container::allocator_type, container::nattributes>;


	public:
		deque_iterator()
		{
			m_cont=0;
			m_pos=0;
		}

		deque_iterator(container* cont, size_t pos)
		{
			m_cont=cont;
			m_pos=pos;
		}

		deque_iterator(const deque_iterator& it)
		{
			*this=it;
		}

		~deque_iterator()
		{
			m_cont = 0;
			m_pos = 0;
		}

		deque_iterator& operator=(const deque_iterator& it)
		{
			if(this!=&it)
			{
				m_cont=it.m_cont;
				m_pos=it.m_pos;
			}
			return *this;
		}

		reference operator*() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return (*m_cont)[m_pos];
		}

		pointer operator->() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return &(*m_cont)[m_pos];
		}

		deque_iterator& operator++()
		{
			++m_pos;
			return *this;
		}

		deque_iterator operator++(int)
		{
			deque_iterator<container> tmp = *this;
			++m_pos;
			return tmp;
		}

		deque_iterator& operator--()
		{
			--m_pos;
			return *this;
		}

		deque_iterator operator--(int)
		{
			deque_iterator<container> tmp = *this;
			--m_pos;
			return tmp;
		}

		deque_iterator& operator+=(difference_type off)
		{
			m_pos += off;
			return *this;
		}

		deque_iterator operator+(difference_type off) const
		{
			deque_iterator<container> tmp = *this;
			return tmp += off;
		}

		deque_iterator& operator-=(difference_type off)
		{
			m_pos -= off;
			return *this;
		}

		deque_iterator operator-(difference_type off) const
		{
			deque_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const deque_iterator& it) const
		{
			if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return m_pos - it.m_pos;
		}

		reference operator[](difference_type off) const
		{
			return *(*this + off);
		}


		bool operator==(const deque_iterator& it) const
		{
			//if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return (m_cont == it.m_cont && m_pos == it.m_pos);
		}


		bool operator!=(const deque_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const deque_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos < it.m_pos;
		}

		bool operator>(const deque_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos > it.m_pos;
		}

		bool operator<=(const deque_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos <= it.m_pos;
		}

		bool operator>=(const deque_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos >= it.m_pos;
		}


	private:
		container*		m_cont;
		size_t			m_pos;
	};  // iterator


//########################################################################
	template<typename container>
	class deque_const_iterator : public misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>
	{
	public:
		typedef misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category    iterator_category;
		typedef typename base::value_type           value_type;
		typedef typename base::difference_type      difference_type;
		typedef typename base::distance_type        distance_type;
		typedef typename base::const_pointer        pointer;
		typedef typename base::const_reference      reference;
		typedef typename container::size_type       size_type;
		friend class misc::deque<typename container::value_type, typename container::allocator_type, container::nattributes>;

	public:
		deque_const_iterator()
		{
			m_cont=0;
			m_pos=0;
		}

		deque_const_iterator(const container* cont, size_t pos)
		{
			m_cont=cont;
			m_pos=pos;
		}

		deque_const_iterator(const deque_const_iterator& it)
		{
			*this = it;
		}

		~deque_const_iterator()
		{
			m_cont = 0;
			m_pos = 0;
		}

		deque_const_iterator& operator=(const deque_const_iterator& it)
		{
			if(this != &it)
			{
				m_cont = it.m_cont;
				m_pos = it.m_pos;
			}
			return *this;
		}

		reference operator*() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return (*m_cont)[m_pos];
		}

		pointer operator->() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return &(*m_cont)[m_pos];
		}

		deque_const_iterator& operator++()
		{
			++m_pos;
			return *this;
		}

		deque_const_iterator operator++(int)
		{
			deque_const_iterator<container> tmp = *this;
			++m_pos;
			return tmp;
		}

		deque_const_iterator& operator--()
		{
			--m_pos;
			return *this;
		}

		deque_const_iterator operator--(int)
		{
			deque_const_iterator<container> tmp = *this;
			--m_pos;
			return tmp;
		}

		deque_const_iterator& operator+=(difference_type off)
		{
			m_pos += off;
			return *this;
		}

		deque_const_iterator operator+(difference_type off) const
		{
			deque_const_iterator<container> tmp = *this;
			return tmp += off;
		}


		deque_const_iterator& operator-=(difference_type off)
		{
			m_pos -= off;
			return *this;
		}

		deque_const_iterator operator-(difference_type off) const
		{
			deque_const_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const deque_const_iterator& it) const
		{
			if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return m_pos - it.m_pos;
		}

		reference operator[](difference_type off) const
		{
			return *(*this + off);
		}

		bool operator==(const deque_const_iterator& it) const
		{
			//if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return (m_cont == it.m_cont && m_pos == it.m_pos);
		}

		bool operator!=(const deque_const_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const deque_const_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos < it.m_pos;
		}

		bool operator>(const deque_const_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos > it.m_pos;
		}

		bool operator<=(const deque_const_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos <= it.m_pos;
		}

		bool operator>=(const deque_const_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos >= it.m_pos;
		}


	private:
		const container* m_cont;
		size_t m_pos;
	};  // const_iterator




//########################################################################
	template<typename container>
	class deque_reverse_iterator : public misc::iterator<misc::random_access_iterator_tag, typename container::value_type>
	{
	public:
		typedef misc::iterator<misc::random_access_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category    iterator_category;
		typedef typename base::value_type           value_type;
		typedef typename base::difference_type      difference_type;
		typedef typename base::distance_type        distance_type;
		typedef typename base::pointer              pointer;
		typedef typename base::reference            reference;
		typedef typename container::size_type       size_type;
		friend class misc::deque<typename container::value_type, typename container::allocator_type, container::nattributes>;

	public:
		deque_reverse_iterator()
		{
			m_cont=0;
			m_pos=0;
		}

		deque_reverse_iterator(container* cont, size_t pos)
		{
			m_cont=cont;
			m_pos=pos;
		}

		deque_reverse_iterator(const deque_reverse_iterator& it)
		{
			*this = it;
		}

		~deque_reverse_iterator()
		{
			m_cont = 0;
			m_pos = 0;
		}

		deque_reverse_iterator& operator=(const deque_reverse_iterator& it)
		{
			if(this != &it)
			{
				m_cont = it.m_cont;
				m_pos = it.m_pos;
			}
			return *this;
		}

		reference operator*() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return (*m_cont)[m_pos];
		}

		pointer operator->() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return &(*m_cont)[m_pos];
		}

		deque_reverse_iterator& operator++()
		{
			--m_pos;
			return *this;
		}

		deque_reverse_iterator operator++(int)
		{
			deque_reverse_iterator<container> tmp = *this;
			--m_pos;
			return tmp;
		}

		deque_reverse_iterator& operator--()
		{
			++m_pos;
			return *this;
		}

		deque_reverse_iterator operator--(int)
		{
			deque_reverse_iterator<container> tmp = *this;
			++m_pos;
			return tmp;
		}

		deque_reverse_iterator& operator+=(difference_type off)
		{
			m_pos -= off;
			return *this;
		}

		deque_reverse_iterator operator+(difference_type off) const
		{
			deque_reverse_iterator<container> tmp = *this;
			return tmp += off;
		}

		deque_reverse_iterator& operator-=(difference_type off)
		{
			m_pos += off;
			return *this;
		}

		deque_reverse_iterator operator-(difference_type off) const
		{
			deque_reverse_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const deque_reverse_iterator& it) const
		{
			if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return it.m_pos - m_pos;
		}

		reference operator[](difference_type off) const
		{
			return *(*this + off);
		}


		bool operator==(const deque_reverse_iterator& it) const
		{
			//if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return (m_cont == it.m_cont && m_pos == it.m_pos);
		}

		bool operator!=(const deque_reverse_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const deque_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos > it.m_pos;
		}

		bool operator>(const deque_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos < it.m_pos;
		}

		bool operator<=(const deque_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos >= it.m_pos;
		}

		bool operator>=(const deque_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos <= it.m_pos;
		}


	private:
		container* m_cont;
		size_t m_pos;
	};  // reverse_iterator


//########################################################################
	template<typename container>
	class deque_const_reverse_iterator : public misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>
	{
	public:
		typedef misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category    iterator_category;
		typedef typename base::value_type           value_type;
		typedef typename base::difference_type      difference_type;
		typedef typename base::distance_type        distance_type;
		typedef typename base::const_pointer        pointer;
		typedef typename base::const_reference      reference;
		typedef typename container::size_type       size_type;
		friend class misc::deque<typename container::value_type, typename container::allocator_type, container::nattributes>;

	public:
		deque_const_reverse_iterator()
		{
			m_cont = 0;
			m_pos = 0;
		}

		deque_const_reverse_iterator(const container* cont, size_t pos)
		{
			m_cont = cont;
			m_pos = pos;
		}

		deque_const_reverse_iterator(const deque_const_reverse_iterator& it)
		{
			*this = it;
		}

		~deque_const_reverse_iterator()
		{
			m_cont = 0;
			m_pos = 0;
		}

		deque_const_reverse_iterator& operator=(const deque_const_reverse_iterator& it)
		{
			if(this != &it)
			{
				m_cont = it.m_cont;
				m_pos = it.m_pos;
			}
			return *this;
		}

		reference operator*() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return (*m_cont)[m_pos];
		}

		pointer operator->() const
		{
			if(m_cont==0) throw misc::exception("invalid iterator");
			return &(*m_cont)[m_pos];
		}

		deque_const_reverse_iterator& operator++()
		{
			--m_pos;
			return *this;
		}

		deque_const_reverse_iterator operator++(int)
		{
			deque_const_reverse_iterator<container> tmp = *this;
			--m_pos;
			return tmp;
		}

		deque_const_reverse_iterator& operator--()
		{
			++m_pos;
			return *this;
		}

		deque_const_reverse_iterator operator--(int)
		{
			deque_const_reverse_iterator<container> tmp = *this;
			++m_pos;
			return tmp;
		}

		deque_const_reverse_iterator& operator+=(difference_type off)
		{
			m_pos -= off;
			return *this;
		}

		deque_const_reverse_iterator operator+(difference_type off) const
		{
			deque_const_reverse_iterator<container> tmp = *this;
			return tmp += off;
		}

		deque_const_reverse_iterator& operator-=(difference_type off)
		{
			m_pos += off;
			return *this;
		}

		deque_const_reverse_iterator operator-(difference_type off) const
		{
			deque_const_reverse_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const deque_const_reverse_iterator& it) const
		{
			if(m_cont != it.m_cont) throw misc::exception("containers are different");
			return it.m_pos - m_pos;
		}

		reference operator[](difference_type off) const
		{
			return *(*this + off);
		}


		bool operator==(const deque_const_reverse_iterator& it) const
		{
			//if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return (m_cont == it.m_cont && m_pos == it.m_pos);
		}

		bool operator!=(const deque_const_reverse_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const deque_const_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos > it.m_pos;
		}

		bool operator>(const deque_const_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos < it.m_pos;
		}

		bool operator<=(const deque_const_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos >= it.m_pos;
		}

		bool operator>=(const deque_const_reverse_iterator& it) const
		{
			if(m_cont!=it.m_cont) throw misc::exception("containers are different");
			return m_pos <= it.m_pos;
		}


	private:
		const container* m_cont;
		size_t m_pos;
	};  // const_reverse_iterator


	//////////////////////////////////////////////////////////////////////////
	/*deque container*/
	template<typename T, typename Allocator=misc::allocator<T>, int attributes=0>
	class deque
	{
	public:
		//types
		typedef deque<T,Allocator,attributes>			container;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;

		typedef typename Allocator::value_type			value_type;
		typedef typename Allocator::size_type			size_type;
		typedef typename Allocator::difference_type		difference_type;
		typedef Allocator								allocator_type;

		

	public:
		typedef deque_iterator<container>				iterator;
		typedef deque_const_iterator<container>			const_iterator;
		typedef deque_reverse_iterator<container>		reverse_iterator;
		typedef deque_const_reverse_iterator<container>	const_reverse_iterator;
		
		static const int nattributes = attributes;


	private:
		typedef typename misc::vector<T,allocator_type,attributes>	int_container;
		typedef typename misc::pair<bool, int_container>			Pair;
		typedef misc::list<Pair>									List;
	
		List*		m_data;
		size_t		m_size;	
		
		void init()
		{
			m_data = new List();
			m_size = 0;
		}

	public:

		//ctor
		deque()
		{
			init();
		}

		explicit deque( size_type n, const T& value= T())
		{
			init();

			Pair p(true, int_container());
			m_data->push_back(p);
			m_data->back().second.resize(n, value);
			m_size = n;
		}

		template <typename InputIterator>
		deque(InputIterator first, InputIterator last)
		{
			init();

			Pair p(true, int_container());
			m_data->push_back(p);
			int_container& cont = m_data->back().second;
			while (first != last)
			{
				cont.push_back(*first++);
				++m_size;
			}
		}

		deque( const deque<T>& x )
		{
			init();
			*this = x;
		}
        
		~deque()
		{
			if(m_data == NULL)
				throw misc::exception("invalid container");

			delete m_data;
			m_data = NULL;

			m_size = 0;
		}
        
		deque<T>& operator= ( const deque<T>& x )
		{
			if(this!=&x)
			{
				*m_data = *x.m_data;
				m_size = x.m_size;
			}
			return *this;
		}

        
		iterator begin()
		{
			return iterator(this, 0);
		}

		const_iterator begin() const
		{
			return const_iterator(this, 0);
		}

		iterator end()
		{
			return iterator(this, m_size);
		}

		const_iterator end() const
		{
			return const_iterator(this, m_size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(this, m_size-1);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(this, m_size-1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(this, static_cast<size_t>(-1));
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(this, static_cast<size_t>(-1));
		}

		size_type size() const
		{
			return m_size;
		}

		size_type max_size () const
		{
			return m_data->max_size();
		}

		void resize ( size_type sz, T c = T() )
		{
			if(m_size > sz)
			{
				//search for last container that sums up sz size
				typename List::iterator it = m_data->begin();
				size_t count = it->second.size();
				while(count < sz)
				{
					++it;
					count += it->second.size();
				}

				//resize current container to match total sz size for this
				int_container& cont = it->second;
				if(it->first)//container created in ascending order
				{
					size_t off = sz - (count - cont.size());
					cont.erase(cont.begin() + off, cont.end());
				}
				else//container is reversed
				{
					size_t off = cont.size() - (sz - (count - cont.size())) - 1;
					cont.erase(cont.begin() + off, cont.end());
				}


				//erase the remaining elements
				++it;
				m_data->erase(it, m_data->end());
			}
			else//m_size <= sz
			{
				//if this is empty
				if(m_size == 0)
				{
					Pair p(true, int_container());
					m_data->push_back(p);
					m_data->back().second.resize(sz, c);
				}
				else if(m_data->back().first)//last container is created in ascending order
				{
					int_container& cont = m_data->back().second;
					cont.resize(sz - (m_size - cont.size()), c );
				}
				else//last container is reversed
				{
					Pair p(true, int_container());
					m_data->push_back(p);
					m_data->back().second.resize(sz - m_size, c);
				}
			}
			m_size = sz;
		}

		bool empty () const
		{
			return m_size == 0;
		}




		//element access
		reference operator[] ( size_type n )
		{
			if( n>= m_size )
				throw misc::exception("outside valid range");


			//identify the container that contains element
			typename List::iterator it = m_data->begin();
			size_t count = it->second.size();
			while(count <= n)
			{
				++it;
				count += it->second.size();
			}

			//container
			int_container& cont = it->second;
			if(it->first)//container created in ascending order
			{
				size_t off = n - (count - cont.size());
				return cont[off];
			}
			else//container is reversed
			{
				size_t off = cont.size() - (n - (count - cont.size())) - 1;
				return cont[off];
			}
		}

		const_reference operator[] ( size_type n ) const
		{
			return const_cast<container& >(*this)[n];
		}

		const_reference at ( size_type n ) const
		{
			return (*this)[n];
		}

		reference at ( size_type n )
		{
			return (*this)[n];
		}

		reference front()
		{
			if(m_size == 0)
				throw misc::exception("outside valid range");

			typename List::iterator it = m_data->begin();
			int_container& cont = it->second;
			if(it->first)
			{
				return cont[0];
			}
			else
			{
				return cont[cont.size()-1];
			}
		}

		const_reference front() const
		{
			return const_cast<container&>(*this).front();
		}

		reference back()
		{
			if(m_size == 0)
				throw misc::exception("outside valid range");

			typename List::reverse_iterator it = m_data->rbegin();
			int_container& cont = it->second;
			if(it->first)
			{
				return cont[cont.size()-1];
			}
			else
			{
				return cont[0];
			}
		}

		const_reference back() const
		{
			return const_cast<container&>(*this).back();
		}



		//modifiers
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			m_data->clear();
			m_size = 0;

			Pair p(true, int_container());
			m_data->push_back(p);
			int_container& cont = m_data->back().second;
			while (first != last)
			{
				cont.push_back(*first++);
				++m_size;
			}
		}

		void assign(size_type n, const T& u)
		{
			m_data->clear();
			m_size = 0;

			Pair p(true, int_container());
			m_data->push_back(p);
			m_data->back().second.assign(n, u);

			m_size = n;
		}


		void push_back(const T& x)
		{
			if(m_size == 0 ||            //container is empty
			   !m_data->rbegin()->first)   //container is reversed
			{
				Pair p(true, int_container());
				m_data->push_back(p);
				m_data->rbegin()->second.push_back(x);
			}
			else
			{
				//container created in ascending order
				m_data->rbegin()->second.push_back(x);
			}

			++m_size;
		}

		void push_front(const T& x)
		{
			if(m_size == 0 ||            //container is empty
			   m_data->begin()->first)      //container created in ascending order
			{
				Pair p(false, int_container());
				m_data->push_front(p);
				m_data->begin()->second.push_back(x);
			}
			else
			{
				//container is reversed
				m_data->begin()->second.push_back(x);
			}

			++m_size;
		}

		void pop_back()
		{
			if(m_size == 0)
				throw misc::exception("cannot pop element");

			typename List::reverse_iterator it = m_data->rbegin();
			int_container& cont = it->second;
			if(it->first)//container created in ascending order
			{
				cont.pop_back();
			}
			else//container is reversed
			{
				cont.erase(cont.begin());
			}

			if(cont.empty())
			{
				m_data->erase(--(m_data->end()));
			}

			--m_size;
		}

		void pop_front()
		{
			if(m_size == 0)
				throw misc::exception("cannot pop element");

			typename List::iterator it = m_data->begin();
			int_container& cont = it->second;
			if(it->first)//container created in ascending order
			{
				cont.erase(cont.begin());
			}
			else//container is reversed
			{
				cont.pop_back();
			}

			if(cont.empty())
			{
				m_data->erase(it);
			}

			--m_size;
		}


		iterator insert(iterator position, const T& x)
		{
			//changes should be done also in insert(iterator, size_t, T)
#if defined DEBUG
			if(position.m_cont != this)
				throw misc::exception("Invalid iterator.");
#endif
			if(m_size == 0)
			{
				//container empty
				if(position.m_pos != 0)
					throw misc::exception("out of valid range");

				Pair p(true, int_container());
				m_data->push_back(p);
				m_data->begin()->second.push_back(x);
			}
			else
			{
				//container not empty
				size_t pos = position.m_pos;
				typename List::iterator it = m_data->begin();
				size_t count = it->second.size();
				while(count < pos)
				{
					++it;
					count += it->second.size();
				}

				int_container& cont = it->second;
				if(it->first)//container created in ascending order
				{
					size_t off = pos - (count - cont.size());
					cont.insert(cont.begin() + off, x);
				}
				else//container is reversed
				{
					size_t off = cont.size() - (pos - (count - cont.size()));
					cont.insert(cont.begin() + off, x);
				}
			}

			++m_size;

			return iterator(this, position.m_pos);
		}


		void insert(iterator position, size_type n, const T& x)
		{
			//changes should be done also in insert(iterator, T)
#if defined DEBUG
			if(position.m_cont != this)
				throw misc::exception("Invalid iterator.");
#endif
			if(m_size == 0)
			{
				//container empty
				if(position.m_pos != 0)
					throw misc::exception("out of valid range");

				Pair p(true, int_container());
				m_data->push_back(p);
				m_data->begin()->second.resize(n, x);
			}
			else
			{
				size_t pos = position.m_pos;
				typename List::iterator it = m_data->begin();
				size_t count = it->second.size();
				while(count < pos)
				{
					++it;
					count += it->second.size();
				}

				int_container& cont = it->second;
				if(it->first)//container created in ascending order
				{
					size_t off = pos - (count - cont.size());
					cont.insert(cont.begin() + off, n, x);
				}
				else//container is reversed
				{
					size_t off = cont.size() - (pos - (count - cont.size()));
					cont.insert(cont.begin() + off, n, x);
				}
			}

			m_size += n;
		}


		template <typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
#if defined DEBUG
			if(position.m_cont != this)
				throw misc::exception("Invalid iterator.");
			//      if(first.m_cont != last.m_cont)
			//         throw misc::exception("Iterators's container mismatch.");
#endif

			if(m_size == 0)
			{
				//container empty
				if(position.m_pos != 0)
					throw misc::exception("out of valid range");

				Pair p(true, int_container());
				m_data->push_back(p);
				int_container& cont = m_data->begin()->second;
				cont.insert(cont.begin(), first, last);
				m_size = cont.size();
			}
			else
			{
				size_t pos = position.m_pos;
				typename List::iterator it = m_data->begin();
				size_t count = it->second.size();
				while(count < pos)
				{
					++it;
					count += it->second.size();
				}

				int_container& cont = it->second;
				if(it->first)//container created in ascending order
				{
					size_t contsz = cont.size();
					size_t off = pos - (count - cont.size());

					cont.insert(cont.begin() + off, first, last);

					m_size += (cont.size() - contsz);
				}
				else//container is reversed
				{
					size_t off = cont.size() - (pos - (count - cont.size()));
					int_container rcont(first, last);
					misc::reverse(rcont.begin(), rcont.end());
					cont.insert(cont.begin() + off, rcont.begin(), rcont.end());
					m_size += rcont.size();
				}
			}
		}

		iterator erase(iterator position)
		{
			//changes should be done also in erase(iterator,iterator)
#if defined DEBUG
			if(position.m_cont != this)
				throw misc::exception("Invalid iterator.");
#endif
			size_t pos = position.m_pos;

			if(m_size <= pos)
				throw misc::exception("out of valid range");

			typename List::iterator it = m_data->begin();
			size_t count = it->second.size();
			while(count < pos)
			{
				++it;
				count += it->second.size();
			}

			int_container& cont = it->second;
			if(it->first)//container created in ascending order
			{
				size_t off = pos - (count - cont.size());
				cont.erase(cont.begin() + off);
			}
			else//container is reversed
			{
				size_t off = cont.size() - (pos - (count - cont.size()));
				cont.erase(cont.begin() + off);
			}

			--m_size;

			return iterator(this, position.m_pos);
		}

		iterator erase(iterator first, iterator last)
		{
			//changes should be done also in erase(iterator)
#if defined DEBUG
			if(first.m_cont != this || last.m_cont != this)
				throw misc::exception("Invalid iterator.");
#endif
			size_t start = first.m_pos;
			size_t end = last.m_pos;
			size_t total = end - start;
			(void)total;
            

			if(m_size <= start || end > m_size)
				throw misc::exception("out of valid range");

			//search start iterator
			typename List::iterator it = m_data->begin();
			size_t count = it->second.size();
			while(count < start)
			{
				++it;
				count += it->second.size();
			}

			size_t off = 0;
			size_t elem = 0;
			typename int_container::iterator bit, eit;
			while(start < end)
			{
				int_container& cont = it->second;
				off = start - (count - cont.size());
				elem = min(cont.size() - off, end - start);
				bit = cont.begin() + off;
				eit = bit + elem;
				cont.erase(bit, eit);
				start += elem;
				m_size -= elem;
				++it;
			}

			return iterator(this, start);
		}


		void swap(deque<T>& dqe)
		{
			if(this!=&dqe)
			{
				List* data2 = m_data;
				size_t size2 = m_size;

				m_data = dqe.m_data;
				m_size = dqe.m_size;

				dqe.m_data = data2;
				dqe.m_size = size2;
			}
		}


		void clear()
		{
			m_data->clear();
			m_size = 0;
		}

		//allocator
		//allocator_type get_allocator() const;

	protected:
	private:


	};  // deque


	
	template<typename T, typename Allocator, int attributes>
	inline void swap(
		deque<T, Allocator, attributes>& left,
		deque<T, Allocator, attributes>& right)
	{
		left.swap(right);
	}

	template<typename T, typename Allocator, int attributes>
	inline bool operator==(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return (left.size() == right.size()) &&
			equal(left.begin(), left.end(), right.begin());
	}



	template<typename T, typename Allocator, int attributes>
	inline bool operator!=(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return !(left == right);
	}

	template<typename T, typename Allocator, int attributes>
	inline bool operator<(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return	lexicographical_compare(
			left.begin(), left.end(), right.begin(), right.end());
	}

	template<typename T, typename Allocator, int attributes>
	inline bool operator<=(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return !(right < left);
	}

	template<typename T, typename Allocator, int attributes>
	inline bool operator>(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return (right < left);
	}

	template<typename T, typename Allocator, int attributes>
	inline bool operator>=(
		const deque<T, Allocator, attributes>& left,
		const deque<T, Allocator, attributes>& right)
	{
		return !(left < right);
	}



}  // namespace misc

#endif//__deque_hpp__


