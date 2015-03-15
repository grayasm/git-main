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




#ifndef __generic_array_hpp__
#define __generic_array_hpp__

#include "exception.hpp"
#include "algorithm.hpp"
#include "memmanip.hpp"
#include "autoptr.hpp"
#include <iostream>

//TODO: remove when done
#include <vector>

/*
  it helps when removing elements that we don't need to get the end_lock position again (it remains consistent)
  what happens when inserting elements ?
  for(iterator it = vect.begin(); it != vec.end_lock(); ++it)
  vect.push_front(*it); ?? is this an infinite loop ? or
  vect.push_back(*it); ?? same infinite loop ?

*/


#define CHECK_ITERATOR_DUPLICATES	1		// extra check is slow


namespace misc
{
	/* iterator base */
	template<typename container>
	struct generic_array_iterator_base
	{
		container*						m_cont;
		typename container::size_type	m_pos;		
	};


//TODO: implement retry allocation for largest mem-block available
	/* container attributes enumeration
	   attributes : non-standard container extension to implement extra features.
	*/
	enum generic_array_attributes
	{
		GENERIC_ARRAY_NONE = 0,
		GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING = 1,
		GENERIC_ARRAY_HAS_POD_TYPE = 1 << 1		
		// IS_MULTI_THREADING = 1 << 2
		// etc
	};


	template<typename T, typename Allocator, int attributes> class generic_array;
	template<typename container> class generic_array_const_iterator;
	template<typename container> class generic_array_const_reverse_iterator;


	/* class iterator */
	template<typename container>
	class generic_array_iterator :
		public misc::iterator<misc::random_access_iterator_tag, typename container::value_type>,
		public generic_array_iterator_base<container>
	{
	public:
		// types
		typedef misc::iterator<misc::random_access_iterator_tag, typename container::value_type>    base;
		typedef typename base::iterator_category    iterator_category;
		typedef typename base::value_type           value_type;
		typedef typename base::difference_type      difference_type;
		typedef typename base::distance_type        distance_type;
		typedef typename base::pointer              pointer;
		typedef typename base::reference            reference;
		typedef typename container::size_type       size_type;
		

		typedef typename misc::generic_array_iterator_base<container> base2;
		friend class misc::generic_array<typename container::value_type, typename container::allocator_type, container::nattributes>;
		friend class generic_array_const_iterator<container>;


	private:
		inline void init()
		{
			base2::m_cont = 0;
			base2::m_pos = 0;
		}

	private:
		generic_array_iterator(container* cont, size_type pos)
		{
			init();

			base2::m_cont = cont;
			base2::m_pos = pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}
		}

	public:
		generic_array_iterator()
		{
			init();
		}


		generic_array_iterator(const generic_array_iterator& it)
		{
			init();
			*this=it;
		}

		~generic_array_iterator()
		{
			if(base2::m_cont)
			{
				base2::m_cont->remove_iterator(this);
			}
		}

		generic_array_iterator& operator=(const generic_array_iterator& it)
		{
			if(this != &it)
			{
				if(base2::m_cont)
				{
					base2::m_cont->remove_iterator(this);
				}

				base2::m_cont = it.m_cont;
				base2::m_pos = it.m_pos;

				if(base2::m_cont)
				{
					base2::m_cont->add_iterator(this);
				}
			}
			return *this;
		}

		reference operator*() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos];
		}

		pointer operator->() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return &(*base2::m_cont)[base2::m_pos];
		}

		generic_array_iterator& operator++()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			++base2::m_pos;
			return *this;
		}

		generic_array_iterator operator++(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");			
			
			generic_array_iterator<container> tmp = *this;
			++base2::m_pos;
			return tmp;
		}

		generic_array_iterator& operator--()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			--base2::m_pos;
			return *this;
		}

		generic_array_iterator operator--(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_iterator<container> tmp = *this;
			--base2::m_pos;
			return tmp;
		}

		generic_array_iterator& operator+=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos += off;
			return *this;
		}

		generic_array_iterator operator+(difference_type off) const
		{
			generic_array_iterator<container> tmp = *this;
			return tmp += off;
		}

		generic_array_iterator& operator-=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos -= off;
			return *this;
		}

		generic_array_iterator operator-(difference_type off) const
		{
			generic_array_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const generic_array_iterator& it) const
		{
			return static_cast<difference_type>(base2::m_pos - it.m_pos);
		}

		bool operator==(const generic_array_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
		}

		bool operator!=(const generic_array_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const generic_array_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
		}

		bool operator>(const generic_array_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
		}

		bool operator<=(const generic_array_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
		}

		bool operator>=(const generic_array_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
		}

		reference operator[](difference_type off) const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos + off];
		}
	};  // iterator


	template<typename container>
	class generic_array_const_iterator :
		public misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>,
		public generic_array_iterator_base<container>
	{
	public:
		typedef misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>  base;
		typedef typename base::iterator_category   iterator_category;
		typedef typename base::value_type          value_type;
		typedef typename base::difference_type     difference_type;
		typedef typename base::distance_type       distance_type;
		typedef typename base::const_pointer       pointer;
		typedef typename base::const_reference     reference;
		typedef typename container::size_type      size_type;
		typedef typename misc::generic_array_iterator_base<container> base2;
		friend class generic_array<typename container::value_type, typename container::allocator_type, container::nattributes>;


	private:
		inline void init()
		{
			base2::m_cont = 0;
			base2::m_pos = 0;
		}

	private:
		generic_array_const_iterator(container* cont, size_type pos)
		{
			init();

			base2::m_cont = cont;
			base2::m_pos = pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}
		}

	public:
		generic_array_const_iterator()
		{
			init();
		}

		generic_array_const_iterator(const generic_array_const_iterator& it)
		{
			init();
			*this=it;
		}

		~generic_array_const_iterator()
		{
			if(base2::m_cont)
			{
				base2::m_cont->remove_iterator(this);
			}
		}

		generic_array_const_iterator& operator=(const generic_array_const_iterator& it)
		{
			if(this != &it)
			{
				if(base2::m_cont)
				{
					base2::m_cont->remove_iterator(this);
				}

				base2::m_cont = it.m_cont;
				base2::m_pos = it.m_pos;

				if(base2::m_cont)
				{
					base2::m_cont->add_iterator(this);
				}

			}
			return *this;
		}

		generic_array_const_iterator& operator=(const generic_array_iterator<container>& it)
		{
			if(base2::m_cont)
			{
				base2::m_cont->remove_iterator(this);
			}

			base2::m_cont = it.m_cont;
			base2::m_pos = it.m_pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}

			return *this;
		}

		generic_array_const_iterator(const generic_array_iterator<container>& it)
		{
			init();
			*this = it;
		}

		reference operator*() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos];
		}

		pointer operator->() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return &(*base2::m_cont)[base2::m_pos];
		}

		generic_array_const_iterator& operator++()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			++base2::m_pos;
			return *this;
		}

		generic_array_const_iterator operator++(int)
		{
			if (!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_const_iterator<container> tmp = *this;
			++base2::m_pos;
			return tmp;
		}

		generic_array_const_iterator& operator--()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");			
			
			--base2::m_pos;
			return *this;
		}

		generic_array_const_iterator operator--(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");			
			
			generic_array_const_iterator<container> tmp = *this;
			--base2::m_pos;
			return tmp;
		}

		generic_array_const_iterator& operator+=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos += off;
			return *this;
		}

		generic_array_const_iterator operator+(difference_type off) const
		{
			generic_array_const_iterator<container> tmp = *this;
			return tmp += off;
		}

		generic_array_const_iterator& operator-=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos -= off;
			return *this;
		}

		generic_array_const_iterator operator-(difference_type off) const
		{
			generic_array_const_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const generic_array_const_iterator& it) const
		{
			return base2::m_pos - it.m_pos;
		}

		bool operator==(const generic_array_const_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
		}

		bool operator!=(const generic_array_const_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const generic_array_const_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
		}

		bool operator>(const generic_array_const_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
		}

		bool operator<=(const generic_array_const_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
		}

		bool operator>=(const generic_array_const_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
		}

		reference operator[](difference_type off) const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos + off];
		}
	};  // const_iterator


	template<typename container>
	class generic_array_reverse_iterator :
		public misc::iterator<misc::random_access_iterator_tag, typename container::value_type>,
		public generic_array_iterator_base<container>
	{
	public:
		typedef misc::iterator<misc::random_access_iterator_tag, typename container::value_type>    base;
		typedef typename base::iterator_category   iterator_category;
		typedef typename base::value_type          value_type;
		typedef typename base::difference_type     difference_type;
		typedef typename base::distance_type       distance_type;
		typedef typename base::pointer             pointer;
		typedef typename base::reference           reference;
		typedef typename container::size_type      size_type;
		typedef typename misc::generic_array_iterator_base<container> base2;
		friend class generic_array<typename container::value_type, typename container::allocator_type, container::nattributes>;
		friend class generic_array_const_reverse_iterator<container>;


	private:
		inline void init()
		{
			base2::m_cont = 0;
			base2::m_pos = 0;
		}

	private:
		generic_array_reverse_iterator(container* cont, size_type pos)
		{
			init();

			base2::m_cont = cont;
			base2::m_pos = pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}
		}

	public:
		generic_array_reverse_iterator()
		{
			init();
		}


		generic_array_reverse_iterator(const generic_array_reverse_iterator& it)
		{
			init();
			*this=it;
		}

		~generic_array_reverse_iterator()
		{
			if(base2::m_cont != 0)
			{
				base2::m_cont->remove_iterator(this);
			}
		}

		generic_array_reverse_iterator& operator=(const generic_array_reverse_iterator& it)
		{
			if(this != &it)
			{
				if(base2::m_cont)
				{
					base2::m_cont->remove_iterator(this);
				}

				base2::m_cont = it.m_cont;
				base2::m_pos = it.m_pos;

				if(base2::m_cont)
				{
					base2::m_cont->add_iterator(this);
				}
			}
			return *this;
		}

		reference operator*() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos];
		}

		pointer operator->() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return &(*base2::m_cont)[base2::m_pos];
		}

		generic_array_reverse_iterator& operator++()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			--base2::m_pos;
			return *this;
		}

		generic_array_reverse_iterator operator++(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_reverse_iterator<container> tmp = *this;
			--base2::m_pos;
			return tmp;
		}

		generic_array_reverse_iterator& operator--()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			++base2::m_pos;
			return *this;
		}

		generic_array_reverse_iterator operator--(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_reverse_iterator<container> tmp = *this;
			++base2::m_pos;
			return tmp;
		}

		generic_array_reverse_iterator& operator+=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos -= off;
			return *this;
		}

		generic_array_reverse_iterator operator+(difference_type off) const
		{
			generic_array_reverse_iterator<container> tmp = *this;
			return tmp += off;
		}

		generic_array_reverse_iterator& operator-=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos += off;
			return *this;
		}

		generic_array_reverse_iterator operator-(difference_type off) const
		{
			generic_array_reverse_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const generic_array_reverse_iterator& it) const
		{
			return it.m_pos - base2::m_pos;
		}

		bool operator==(const generic_array_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && it.m_pos == base2::m_pos);
		}

		bool operator!=(const generic_array_reverse_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const generic_array_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
		}

		bool operator>(const generic_array_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
		}

		bool operator<=(const generic_array_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
		}

		bool operator>=(const generic_array_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
		}

		reference operator[](difference_type off) const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos - off];
		}
	};  // reverse_iterator


	template<typename container>
	class generic_array_const_reverse_iterator :
		public misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>,
		public generic_array_iterator_base<container>
	{
	public:
		typedef misc::const_iterator<misc::random_access_iterator_tag, typename container::value_type>  base;
		typedef typename base::iterator_category   iterator_category;
		typedef typename base::value_type          value_type;
		typedef typename base::difference_type     difference_type;
		typedef typename base::distance_type       distance_type;
		typedef typename base::const_pointer       pointer;
		typedef typename base::const_reference     reference;
		typedef typename container::size_type      size_type;
		typedef typename misc::generic_array_iterator_base<container> base2;
		friend class generic_array<typename container::value_type, typename container::allocator_type, container::nattributes>;



	private:
		inline void init()
		{
			base2::m_cont = 0;
			base2::m_pos = 0;
		}
	
	private:
		generic_array_const_reverse_iterator(container* cont, size_type pos)
		{
			init();

			base2::m_cont = cont;
			base2::m_pos = pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}
		}

	public:
		generic_array_const_reverse_iterator()
		{
			init();
		}

		generic_array_const_reverse_iterator(const generic_array_const_reverse_iterator& it)
		{
			init();
			*this=it;
		}

		~generic_array_const_reverse_iterator()
		{
			if(base2::m_cont)
			{
				base2::m_cont->remove_iterator(this);
			}
		}

		generic_array_const_reverse_iterator& operator=(const generic_array_const_reverse_iterator& it)
		{
			if(this != &it)
			{
				if(base2::m_cont)
				{
					base2::m_cont->remove_iterator(this);
				}

				base2::m_cont = it.m_cont;
				base2::m_pos = it.m_pos;

				if(base2::m_cont)
				{
					base2::m_cont->add_iterator(this);
				}
			}
			return *this;
		}

		generic_array_const_reverse_iterator& operator=(const generic_array_reverse_iterator<container>& it)
		{
			if(base2::m_cont)
			{
				base2::m_cont->remove_iterator(this);
			}

			base2::m_cont = it.m_cont;
			base2::m_pos = it.m_pos;

			if(base2::m_cont)
			{
				base2::m_cont->add_iterator(this);
			}

			return *this;
		}

		generic_array_const_reverse_iterator(const generic_array_reverse_iterator<container>& it)
		{
			init();
			*this = it;
		}


		reference operator*() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos];
		}

		pointer operator->() const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return &(*base2::m_cont)[base2::m_pos];
		}

		generic_array_const_reverse_iterator& operator++()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			--base2::m_pos;
			return *this;
		}

		generic_array_const_reverse_iterator operator++(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_const_reverse_iterator<container> tmp = *this;
			--base2::m_pos;
			return tmp;
		}

		generic_array_const_reverse_iterator& operator--()
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			++base2::m_pos;
			return *this;
		}

		generic_array_const_reverse_iterator operator--(int)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			generic_array_const_reverse_iterator<container> tmp = *this;
			++base2::m_pos;
			return tmp;
		}

		generic_array_const_reverse_iterator& operator+=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos -= off;
			return *this;
		}

		generic_array_const_reverse_iterator operator+(difference_type off) const
		{
			generic_array_const_reverse_iterator<container> tmp = *this;
			return tmp += off;
		}

		generic_array_const_reverse_iterator& operator-=(difference_type off)
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");
			
			base2::m_pos += off;
			return *this;
		}

		generic_array_const_reverse_iterator operator-(difference_type off) const
		{
			generic_array_const_reverse_iterator<container> tmp = *this;
			return tmp -= off;
		}

		difference_type operator-(const generic_array_const_reverse_iterator& it) const
		{
			return it.m_pos - base2::m_pos;
		}

		bool operator==(const generic_array_const_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
		}

		bool operator!=(const generic_array_const_reverse_iterator& it) const
		{
			return !(*this == it);
		}

		bool operator<(const generic_array_const_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
		}

		bool operator>(const generic_array_const_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
		}

		bool operator<=(const generic_array_const_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
		}

		bool operator>=(const generic_array_const_reverse_iterator& it) const
		{
			return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
		}

		reference operator[](difference_type off) const
		{
			if(!base2::m_cont) throw misc::exception("invalid iterator");

			return (*base2::m_cont)[base2::m_pos - off];
		}
	};  // const_reverse_iterator


	/*
	  http://stackoverflow.com/questions/4944156/c-method-specialization-and-templates

	  It turns out that there's a provision in the C++ spec that explicitly
	  disallows specializing a template class or function nested inside of a
	  template class unless you also explicitly specialize the outer template as well.

	  If you want to specialize the template, your options will either be to
	  also specialize the outer template or to somehow fake up the behavior of
	  specialization by having the method dispatch to one of two different
	  implementations based on the template parameter.

	  Emulate the behavior of the explicit specialization
	  through a technique called tag dispatching.
	*/
	template<typename T>
	struct generic_array_spec
	{
		typedef T value;
	};


	/*!	ISO/IEC 14882:2003  $21.3 Class template basic_string
		ISO/IEC 14882:2003  $23.2.4 Class template vector
		attributes : non-standard container extension to implement extra features.
	*/
	template<typename T, typename Allocator = misc::allocator<T>, int attributes = 0>
	class generic_array
	{
	public:
		typedef generic_array<T, Allocator, attributes>  container;
		typedef typename Allocator::reference            reference;
		typedef typename Allocator::const_reference      const_reference;
		typedef typename Allocator::pointer              pointer;
		typedef typename Allocator::const_pointer        const_pointer;

		typedef typename Allocator::value_type           value_type;
		typedef typename Allocator::size_type            size_type;
		typedef typename Allocator::difference_type      difference_type;
		typedef Allocator                                allocator_type;

	public:
		typedef generic_array_iterator<container>               iterator;
		typedef generic_array_const_iterator<container>         const_iterator;
		typedef generic_array_reverse_iterator<container>       reverse_iterator;
		typedef generic_array_const_reverse_iterator<container> const_reverse_iterator;


//TODO: can have generic_array without debugging iterator to eliminate recursion
		// debug_iterator implementation
		typedef generic_array_iterator_base<container>   iterator_base;
		typedef std::vector<iterator_base*>              iterator_array;


	private:
		value_type*             m_data;
		size_type               m_size;
		size_type               m_capacity;
		allocator_type          m_allocator;		

		// debug_iterator implementation
		iterator_array*         m_itarray;
		friend class generic_array_iterator<container>;
		friend class generic_array_const_iterator<container>;
		friend class generic_array_reverse_iterator<container>;
		friend class generic_array_const_reverse_iterator<container>;




//TODO: bring allocator implementation !


	public:
		static const size_type npos = static_cast<size_type>(-1);
		static const size_type numbytes = sizeof(T);
		static const int nattributes = attributes;
		

	private:
		inline void init(const Allocator& alloc)
		{
			m_data = 0;
			m_size = 0;
			m_capacity = 0;
			m_allocator = alloc;

			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if(hasITDBG)
			{
				m_itarray = new iterator_array;
			}
		}

		inline void mem_alloc(size_type cap)
		{
			pointer mem = 0;

			/* buy memory, no ctor() called */
			mem = m_allocator.allocate(cap + 1);

			if(mem == 0) 
				throw misc::exception("bad allocation");				
			
			m_data = mem;
			m_capacity = cap;
		}

		inline void grow(size_type cap)
		{
			if(m_capacity >= cap) return;

			pointer mem = 0;

			// ms comp warn 4127
			int hasPOD = (attributes & misc::GENERIC_ARRAY_HAS_POD_TYPE);
			if(hasPOD)
			{
				misc::mem_realloc_pod(&mem, cap+1, m_data, m_size, m_allocator);
			}
			else
			{
				misc::mem_realloc(&mem, cap+1, m_data, m_size, m_allocator);
			}

			m_data = mem;
			m_capacity = cap;
		}

		template<typename T2>
		inline size_t length(const value_type* ptr) const
		{
			return length(ptr, misc::generic_array_spec<T2>());
		}

		template<typename T2>
		inline size_t length(const value_type* ptr, misc::generic_array_spec<T2>) const
		{
			if(ptr == 0) throw misc::exception("null pointer");
			const value_type* p = ptr;
			while( *p != 0 )
				p++ ;
			return (p - ptr);
		}

		inline size_t length(const value_type* ptr, misc::generic_array_spec<char>) const
		{
			return ::strlen(ptr);
		}

		inline size_t length(const value_type* ptr, misc::generic_array_spec<unsigned char>) const
		{
#if defined _WIN32
			return ::_mbslen(ptr);
#else // LINUX
			/*	I will find out that this doesn't work when the string will hold
				some Russian characters.
			 */
			return ::strlen((const char*) ptr);
#endif
		}

		inline size_t length(const value_type* ptr, misc::generic_array_spec<wchar_t>) const
		{
			return ::wcslen(ptr);
		}

		template<typename T2>
		inline void eos(size_type size)
		{
			eos(size, misc::generic_array_spec<T2>());
		}

		template<typename T2>
		inline void eos(size_type size, misc::generic_array_spec<T2>)
		{
			if(m_capacity < size) throw misc::exception("bad size");
			
			// ms comp warn 4127
			int hasPOD = (attributes & misc::GENERIC_ARRAY_HAS_POD_TYPE);
			if(size < m_size && !hasPOD)
			{
				// Non POD types;
				value_type* unused = m_data+size;
				misc::mem_destroy(&unused, m_size - size, m_allocator);
			}
			m_size = size;
		}

		inline void eos(size_type size, misc::generic_array_spec<char>)
		{
			if(m_capacity < size) throw misc::exception("bad size");
			m_size = size;
			m_data[m_size] = 0;
		}

		inline void eos(size_type size, misc::generic_array_spec<unsigned char>)
		{
			if(m_capacity < size) throw misc::exception("bad size");
			m_size = size;
			m_data[m_size] = 0;
		}

		inline void eos(size_type size, misc::generic_array_spec<wchar_t>)
		{
			if(m_capacity < size) throw misc::exception("bad size");
			m_size = size;
			m_data[m_size] = 0;
		}

		inline void swap_range(size_type beg, size_type end)
		{
			if(beg < end)
			{
				for(size_type i = beg, j = end - 1; i < j; ++i, --j)
				{
					misc::swap<value_type>(m_data[i], m_data[j]);
				}
			}
		}

		inline bool inside(const value_type* ptr) const
		{
			return (m_data <= ptr && m_data + m_size >= ptr);
		}

		inline void memcpy_impl(pointer dest, const_pointer src, size_type bytes)
		{			
			// ms comp warn 4127
			int hasPOD = (attributes & misc::GENERIC_ARRAY_HAS_POD_TYPE);
			if(hasPOD)
			{
				misc::mem_copy_pod(dest, src, bytes);
			}
			else
			{
				misc::mem_copy(dest, src, bytes);
			}
		}

		inline void memmove_impl(pointer dest, const_pointer src, size_type bytes) const
		{
			// ms comp warn 4127
			int hasPOD = (attributes & misc::GENERIC_ARRAY_HAS_POD_TYPE);
			if(hasPOD)
			{
				misc::mem_move_pod(dest, src, bytes);
			}
			else
			{
				misc::mem_move(dest, src, bytes);
			}
		}


		// debug_iterator implementation
		inline void add_iterator(iterator_base* it)
		{			
			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if( !hasITDBG )
			{
				return;
			}
			
			if(it->m_cont != this)
				throw misc::exception("invalid debug iterator");

			//	extra test for debugging
#if CHECK_ITERATOR_DUPLICATES
			for(size_t i=0; i < m_itarray->size(); ++i)
			{
				if(it == (*m_itarray)[i])
					throw misc::exception("duplicate iterator");
			}
#endif
			
			m_itarray->push_back(it);
		}

		inline void remove_iterator(iterator_base* it)
		{			
			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if( !hasITDBG )
			{
				return;
			}

			/* container must match */
			if(it->m_cont != this)
				throw misc::exception("invalid debug iterator");

			//	Before iterator gets destroyed, it asks for removal.
			for(typename iterator_array::iterator beg = m_itarray->begin(); beg != m_itarray->end(); )
			{
				iterator_base* iter = *beg;
				if( it == iter )
				{					
					iter->m_cont = 0;					
					beg = m_itarray->erase(beg);
					return; // no duplicates
				}
				else
				{
					++beg;
				}
			}
		}

		inline void invalidate_iterators()
		{			
			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if( !hasITDBG )
			{
				return;
			}

			/*	When a container gets deleted, all its iterators
				are invalidated.
			*/
			for(size_t i=0; i < m_itarray->size(); ++i)
			{
				(*m_itarray)[i]->m_cont = 0;				
			}
			m_itarray->resize(0);
		}

		inline void invalidate_iterators_gte(size_t pos)
		{
			/* invalidate container iterators at element's pos >= pos */
			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if( !hasITDBG )
			{
				return;
			}

			for(typename iterator_array::iterator beg = m_itarray->begin(); beg != m_itarray->end();)
			{
				iterator_base* iter = *beg;
				if(iter->m_pos >= pos)
				{					
					iter->m_cont = 0;
					beg = m_itarray->erase(beg);
				}
				else
				{
					++beg;
				}				
			}
		}

	public:
		/*! $21.3.1 construct / copy / destroy */
		explicit generic_array(const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);
			eos<T>(0);
		}

		generic_array(const container& x)
		{
			init( x.get_allocator() );
			mem_alloc(1);       // avoid 0 capacity with x.empty()
			eos<T>(0);          // protect against self assignment
			assign( x );        // may return with no action
		}

		generic_array(const container& str, size_type off, size_type count = npos,
					  const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);       // avoid 0 capacity with x.empty
			eos<T>(0);          // protect against self assignment
			assign(str, off, count);
		}

		generic_array(const value_type* ptr, size_type count,
					  const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);       // avoid 0 capacity with ptr 0
			eos<T>(0);          // safety
			assign(ptr, count);
		}

		generic_array(const value_type* ptr, const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);       // avoid 0 capacity with ptr 0
			eos<T>(0);          // safety
			assign(ptr);
		}


		generic_array(size_type n, value_type c, const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);       // avoid 0 capacity with n=0
			eos<T>(0);          // safety
			assign(n, c);
		}


		template<class InputIterator>
		inline generic_array(InputIterator begin, InputIterator end,
							 const Allocator& alloc = Allocator())
		{
			init(alloc);
			mem_alloc(1);       // avoid 0 capacity
			eos<T>(0);          // safety
			assign(begin, end);
		}

		~generic_array()
		{	
			// ms comp warn 4127
			int hasPOD = (attributes & misc::GENERIC_ARRAY_HAS_POD_TYPE);
			if(hasPOD)
			{
				m_allocator.deallocate(m_data, 0);
			}
			else
			{
				misc::mem_destroy(&m_data, m_size, m_allocator);
				m_allocator.deallocate(m_data, 0);
			}

			m_data=0;
			m_size=0;
			m_capacity=0;
			

			// ms comp warn 4127
			int hasITDBG = (attributes & misc::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
			if(hasITDBG)
			{
				invalidate_iterators();
				delete m_itarray;
			}
		}

		/* $21.3.1 (assignment operators) */
		inline container& operator=(const container& str)
		{
			return assign(str);
		}

		inline container& operator=(const value_type* ptr)
		{
			return assign(ptr);
		}

		inline container& operator=(value_type ch)
		{
			invalidate_iterators();

			/* simplified */
			m_data[0] = ch;
			eos<T>(1);
			return *this;
		}


		//$21.3.2 iterators
		inline iterator begin()
		{
			return iterator(this, 0);
		}

		inline const_iterator begin() const
		{
			container* mutable_cont = const_cast<container*>(this);
			return const_iterator(mutable_cont, 0);
		}

		inline iterator end()
		{
			return iterator(this, m_size);
		}

		inline const_iterator end() const
		{
			container* mutable_cont = const_cast<container*>(this);
			return const_iterator(mutable_cont, m_size);
		}

		inline reverse_iterator rbegin()
		{
			return reverse_iterator(this, static_cast<size_type>(m_size - 1));
		}

		inline const_reverse_iterator rbegin() const
		{
			container* mutable_cont = const_cast<container*>(this);
			return const_reverse_iterator(mutable_cont, static_cast<size_type>(m_size - 1));
		}

		inline reverse_iterator rend()
		{
			return reverse_iterator(this, static_cast<size_type>(-1));
		}

		inline const_reverse_iterator rend() const
		{
			container* mutable_cont = const_cast<container*>(this);
			return const_reverse_iterator(mutable_cont, static_cast<size_type>(-1));
		}

		//$21.3.3 capacity
		inline size_type size() const
		{
			return m_size;
		}

		inline size_type length() const
		{
			return m_size;
		}

		inline size_type max_size() const
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}

		inline void resize(size_type sz, value_type c = value_type())
		{
			if(m_size > sz)
			{
				invalidate_iterators_gte(sz > 0 ? sz-1 : 0);

				eos<T>(sz);
			}
			else if(m_size < sz)
			{
				grow(sz);

				misc::mem_set(&m_data[m_size], c, (sz - m_size) * numbytes);

				eos<T>(sz);
			}
		}

		inline size_type capacity() const
		{
			return m_capacity;
		}

		inline void reserve(size_type n)
		{
			grow(n);
		}

		inline void clear()
		{
			invalidate_iterators();

			eos<T>(0);
		}

		inline bool empty() const
		{
			return m_size==0;
		}

		//$21.3.4 element access:
		inline reference operator[](size_type n) const
		{
			if(n >= m_size) throw misc::exception("out of valid range");
			return m_data[n];
		}

		inline reference operator[](size_type n)
		{
			if(n >= m_size) throw misc::exception("out of valid range");
			return m_data[n];
		}

		inline reference at(size_type n) const
		{
			if(n >= m_size) throw misc::exception("out of valid range");
			return m_data[n];
		}

		inline reference at(size_type n)
		{
			if(n >= m_size) throw misc::exception("out of valid range");
			return m_data[n];
		}


		// $21.3.5 modifiers

		/* $21.3.5 modifiers ( operator += (...) ) */
		inline container& operator+=(const container& str)
		{
			return append(str);
		}

		inline container& operator+=(const value_type* ptr)
		{
			return append(ptr);
		}

		inline container& operator+=(value_type ch)
		{
			return append(1, ch);
		}

		/* $21.3.5 modifiers (append) */
		inline container& append(const container& str)
		{
			return append(str, 0, npos);
		}

		inline container& append(const container& str, size_type p2, size_type n2)
		{
			size_type strLen = str.length();

			if(strLen > 0)
			{
				if(p2 >= strLen) throw misc::exception("out of valid range");

				if(n2 > strLen - p2)
					n2 = strLen - p2;

				size_type size = m_size + n2;

				grow(size);

				memcpy_impl(&m_data[m_size], &str[p2], n2 * numbytes);

				eos<T>(size);
			}

			return *this;
		}

		inline container& append(const value_type* ptr, size_type n2)
		{
			size_type ptrLen = length<value_type>(ptr);

			if(ptrLen > 0)
			{
				if(n2 > ptrLen)
					n2 = ptrLen;

				size_type size = m_size + n2;

				grow(size);

				memcpy_impl(&m_data[m_size], ptr, n2 * numbytes);

				eos<T>(size);
			}

			return *this;
		}

		inline container& append(const value_type* ptr)
		{
			return append(ptr, npos);
		}


		inline container& append(size_type n, value_type value)
		{
			if(n > 0)
			{
				size_type size = m_size + n;

				grow(size);

				misc::mem_set(&m_data[m_size], value, n * numbytes);

				eos<T>(size);
			}
			return *this;
		}


	private:
		/*
		  implementation of:
		  template<typename InputIterator>
		  container& append(InputIterator first, InputIterator last);
		*/
		inline container& append_impl(const iterator& first, const iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;
			if(dist > 0)
			{
				size_type size = m_size + dist;

				grow(size);

				memcpy_impl(&m_data[m_size], &((*first.m_cont)[first.m_pos]), dist * numbytes);

				eos<T>(size);
			}

			return *this;
		}

		inline container& append_impl(const const_iterator& first, const const_iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;
			if(dist > 0)
			{
				size_type size = m_size + dist;

				grow(size);

				memcpy_impl(&m_data[m_size], &(*(first.m_cont)[first.m_pos]), dist * numbytes);

				eos<T>(size);
			}

			return *this;
		}

		inline container& append_impl(const reverse_iterator& first, const reverse_iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;
			if(dist > 0)
			{
				size_type size = m_size + dist;

				grow(size);

				memcpy_impl(&m_data[m_size], &((*last.m_cont)[last.m_pos+1]), dist * numbytes);

				swap_range(m_size, size);

				eos<T>(size);
			}

			return *this;
		}

		inline container& append_impl(const const_reverse_iterator& first, const const_reverse_iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;
			if(dist > 0)
			{
				size_type size = m_size + dist;

				grow(size);

				memcpy_impl(&m_data[m_size], &((*last.m_cont)[last.m_pos+1]), dist * numbytes);

				swap_range(m_size, size);

				eos<T>(size);
			}

			return *this;
		}


		/*
		  -due to specialization for append_impl(const iterator& ...) and friends,
		  compiler cannot find any suitable append_impl for next code:

		  float fptr[]={0,...};
		  misc::generic_array<float> fcont;
		  fcont.append(fptr, fptr+10);
		*/
		inline container& append_impl(const value_type* first, const value_type* last)
		{
			difference_type dist = last - first;
			if(dist > 0)
			{
				size_type size = m_size + dist;

				grow(size);

				memcpy_impl(&m_data[m_size], first, dist * numbytes);

				eos<T>(size);
			}

			return *this;
		}


		template<typename InputIterator>
		inline container& append_impl(const InputIterator& first, const InputIterator& last, misc::random_access_iterator_tag)
		{
			return append_impl(first, last);
		}


		template<typename InputIterator>
		inline container& append_impl(InputIterator n, InputIterator value, misc::input_iterator_tag)
		{//e.g. str.append<int>(5, 0x2E);

			if(n > 0)
			{
				size_type size = m_size + n;

				grow(size);

				misc::mem_set(&m_data[m_size], value, n * numbytes);

				eos<T>(size);
			}

			return *this;
		}

	public:
		template<typename InputIterator>
		inline container& append(InputIterator first, InputIterator last)
		{
			return append_impl<InputIterator>(first, last, typename misc::iterator_traits<InputIterator>::iterator_category());
		}


		/* $21.3.5 modifiers ( push_back ) */
		inline void push_back(const value_type& x)
		{
			if(m_size == m_capacity )
			{
				grow(m_capacity * 2);
			}

			// call copy constructor not copy operator
			new(&m_data[m_size])value_type(x);

			eos<T>(m_size + 1);
		}


		/* $21.3.5 modifiers ( assign ) */
		inline container& assign(const container& str)
		{
			//self assignment
			if( this != &str )
			{
				invalidate_iterators();

				size_type size = str.length();

				if(size > 0)
				{
					grow(size);

					memcpy_impl(m_data, str.m_data, size * numbytes);
				}

				eos<T>(size);
			}

			return *this;
		}

		inline container& assign(const container& str, size_type p2, size_type n2)
		{
			invalidate_iterators();

			size_type strLen = str.length();

			if(p2 >= strLen) throw misc::exception("out of valid range");

			if(n2 > strLen - p2)
				n2 = strLen - p2;

			if(n2 > 0)
			{
				grow(n2);

				//self assignment
				if(this == &str)
				{
					memmove_impl(m_data, &str[p2], n2 * numbytes);
				}
				else
				{
					memcpy_impl(m_data, &str[p2], n2 * numbytes);
				}
			}

			eos<T>(n2);

			return *this;
		}

		inline container& assign(const value_type* ptr, size_type n2)
		{
			invalidate_iterators();

			size_type ptrLen = length<value_type>(ptr);

			if(n2 > ptrLen)
				n2 = ptrLen;

			if(n2 > 0)
			{
				grow(n2);

				//ptr may overlap m_data
				memmove_impl(m_data, ptr, n2 * numbytes);
			}

			eos<T>(n2);

			return *this;
		}

		inline container& assign(const value_type* ptr)
		{
			return assign(ptr, npos);
		}

		inline container& assign(size_type count, const value_type& val)
		{
			invalidate_iterators();

			if(count > 0)
			{
				grow(count);

				misc::mem_set(m_data, val, count * numbytes);
			}

			eos<T>(count);

			return *this;
		}

	private:
		/*
		  implementation of:
		  template <class InputIterator>
		  string& assign ( InputIterator first, InputIterator last );
		*/
		inline container& assign_impl(const iterator& first, const iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			invalidate_iterators();

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0; // erase this array

			if(dist > 0)
			{
				grow(dist);

				//self assignment
				if(this == first.m_cont)
				{
					memmove_impl(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
				}
				else
				{
					memcpy_impl(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
				}
			}

			eos<T>(dist);

			return *this;
		}

		inline container& assign_impl(const const_iterator& first, const const_iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			invalidate_iterators();

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0; // erase this array

			if(dist > 0)
			{
				grow(dist);

				//self assignment
				if(this == first.m_cont)
				{
					memmove_impl(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
				}
				else
				{
					memcpy_impl(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
				}
			}

			eos<T>(dist);

			return *this;
		}

		inline container& assign_impl(const reverse_iterator& first, const reverse_iterator& last)
		{
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			invalidate_iterators();

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0; // erase this array

			if(dist > 0)
			{
				grow(dist);

				//self assignment
				if( this == first.m_cont )
				{
					erase(0, last.m_pos + 1);
				}
				else
				{
					memcpy_impl(m_data, &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);
				}

				swap_range(0, dist);
			}

			eos<T>(dist);

			return *this;
		}

		inline container& assign_impl(const const_reverse_iterator& first, const const_reverse_iterator& last)
		{
			//validate containers
			if(first.m_cont != last.m_cont || first.m_cont == 0)
				throw misc::exception("invalid iterator");

			invalidate_iterators();

			size_type dist = last - first;

			if(dist < 0)
				dist = 0; // erase this array

			if(dist > 0)
			{
				grow(dist);

				//self assignment
				if( this == first.m_cont )
				{
					erase(0, last.m_pos + 1);
				}
				else
				{
					memcpy_impl(m_data, &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);
				}

				swap_range(0, dist);
			}

			eos<T>(dist);

			return *this;
		}

		/*
		  -due to specialization for assign_impl(const iterator& ...) and friends,
		  compiler cannot find any suitable assign_impl for next code:

		  float fptr[]={0,...};
		  misc::generic_array<float> fcont(fptr, fptr+10);
		*/

		inline container& assign_impl(const value_type* first, const value_type* last)
		{
			invalidate_iterators();

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0; // erase this array

			if(dist > 0)
			{
				grow(dist);

				memcpy_impl(m_data, first, dist * numbytes);
			}

			eos<T>(dist);

			return *this;
		}


		template<typename InputIterator>
		inline container& assign_impl(InputIterator first, InputIterator last, misc::random_access_iterator_tag)
		{
			return assign_impl(first, last);
		}

		template<typename InputIterator>
		inline container& assign_impl(InputIterator n, InputIterator value, misc::input_iterator_tag)
		{
			invalidate_iterators();

			if(n < 0)
				n = 0; // erase this array

			if(n > 0)
			{
				grow(n);

				misc::mem_set<value_type>(m_data, value, n * numbytes);
			}

			eos<T>(n);

			return *this;
		}


	public:
		template <typename InputIterator>
		inline container& assign(InputIterator first, InputIterator last)
		{
			return assign_impl(first, last, typename misc::iterator_traits<InputIterator>::iterator_category());
		}


		/* $21.3.5 modifiers ( insert ) */
		inline container& insert(size_type p1, const container& str)
		{
			return insert(p1, str, 0, npos);
		}

		inline container& insert(size_type p1, const container& str, size_type p2, size_type n2)
		{
			if(this == &str)
			{
				return replace(p1, 0, *this, p2, n2);
			}
			else
			{
				//allow insert in end_lock() position;
				if(p1 > m_size) throw misc::exception("out of valid range");

				size_type strLen = str.length();
				if(p2 >= strLen) throw misc::exception("out of valid range");

				if(n2 > strLen - p2)
					n2 = strLen - p2;

				if(n2)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + n2;

					grow(size);

					memmove_impl(&m_data[p1+n2], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], &str[p2], n2 * numbytes);


					eos<T>(size);
				}
				return *this;
			}
		}

		inline container& insert(size_type p1, const value_type* ptr, size_type n2)
		{
			if( inside(ptr) )
			{
				return replace(p1, 0, *this, 0, n2);
			}
			else
			{
				//allow insert in end_lock() position;
				if(p1 > m_size) throw misc::exception("out of valid range");

				size_type ptrLen = length<value_type>(ptr);
				if(n2 > ptrLen)
					n2 = ptrLen;

				if(n2)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + n2;

					grow(size);

					memmove_impl(&m_data[p1+n2], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], ptr, n2 * numbytes);

					eos<T>(size);
				}
				return *this;
			}
		}

		inline container& insert(size_type p1, const value_type* ptr)
		{
			return insert(p1, ptr, npos);
		}

		inline container& insert(size_type p1, size_type n2, value_type ch)
		{
			//allow insert in end_lock() position;
			if(p1 > m_size) throw misc::exception("out of valid range");

			if(n2)
			{
				// invalidate for effective insert only
				invalidate_iterators_gte(p1);

				size_type size = m_size + n2;

				grow(size);

				memmove_impl(&m_data[p1+n2], &m_data[p1], (m_size - p1) * numbytes);

				misc::mem_set(&m_data[p1], ch, n2 * numbytes);

				eos<T>(size);
			}

			return *this;
		}

		inline iterator insert(iterator position, const value_type& x)
		{
			insert(position, 1, x);
			return position;
		}

		inline void insert(iterator position, size_type n, const value_type& x)
		{
			if(this != position.m_cont) throw misc::exception("invalid iterator");
			if(position.m_pos > m_size) throw misc::exception("out of valid range");


			if(n)
			{
				size_type size = m_size + n;
				size_type p1 = position.m_pos;

				// invalidate for effective insert only
				invalidate_iterators_gte(p1);

				grow(size);

				memmove_impl(&m_data[p1 + n], &m_data[p1], (m_size - p1) * numbytes);

				misc::mem_set(&m_data[p1], x, n * numbytes);

				eos<T>(size);
			}
		}

	private:
		/*
		  implementation of:
		  template<class InputIterator>
		  void insert ( iterator p, InputIterator first, InputIterator last );
		*/
		inline void insert_impl(size_type p1, const iterator& first, const iterator& last)
		{
			if(this == first.m_cont)
			{
				replace_impl(p1, 0, first, last);
			}
			else
			{
				if(first.m_cont != last.m_cont || first.m_cont == 0)
					throw misc::exception("invalid iterator");

				if(p1 > m_size) throw misc::exception("out of valid range");

				difference_type dist = last - first;
				if(dist > 0)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + dist;
					grow(size);

					memmove_impl(&m_data[p1+dist], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);

					eos<T>(size);
				}
			}
		}

		inline void insert_impl(size_type p1, const const_iterator& first, const const_iterator& last)
		{
			if(this == first.m_cont)
			{
				replace(p1, 0, first, last);
			}
			else
			{
				if(first.m_cont != last.m_cont || first.m_cont == 0)
					throw misc::exception("invalid iterator");

				if(p1 > m_size) throw misc::exception("out of valid range");

				difference_type dist = last - first;
				if(dist > 0)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + dist;
					grow(size);

					memmove_impl(&m_data[p1+dist], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);

					eos<T>(size);
				}
			}
		}

		inline void insert_impl(size_type p1, const reverse_iterator& first, const reverse_iterator& last)
		{
			if(this == first.m_cont)
			{
				replace(p1, 0, first, last);
			}
			else
			{
				if(first.m_cont != last.m_cont || first.m_cont == 0)
					throw misc::exception("invalid iterator");

				if(p1 > m_size) throw misc::exception("out of valid range");

				difference_type dist = last - first;
				if(dist > 0)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + dist;
					grow(size);

					memmove_impl(&m_data[p1+dist], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos+1]), dist * numbytes);

					swap_range(p1, p1 + dist);

					eos<T>(size);
				}
			}
		}

		inline void insert_impl(size_type p1, const const_reverse_iterator& first, const const_reverse_iterator& last)
		{
			if(this == first.m_cont)
			{
				replace(p1, 0, first, last);
			}
			else
			{
				if(first.m_cont != last.m_cont || first.m_cont == 0)
					throw misc::exception("invalid iterator");

				if(p1 > m_size) throw misc::exception("out of valid range");

				difference_type dist = last - first;
				if(dist > 0)
				{
					// invalidate for effective insert only
					invalidate_iterators_gte(p1);

					size_type size = m_size + dist;
					grow(size);

					memmove_impl(&m_data[p1+dist], &m_data[p1], (m_size - p1) * numbytes);
					memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos+1]), dist * numbytes);

					swap_range(p1, p1 + dist);

					eos<T>(size);
				}
			}
		}

		template<typename InputIterator>
		inline void insert_impl(size_type p1, const InputIterator& first, const InputIterator& last, misc::random_access_iterator_tag)
		{
			insert_impl(p1, first, last);
		}

		template<typename InputIterator>
		inline void insert_impl(size_type p1, InputIterator n2, InputIterator value, misc::input_iterator_tag)
		{
			if(n2)
			{
				// invalidate for effective insert only
				invalidate_iterators_gte(p1);

				size_type size = m_size + n2;

				grow(size);

				memmove_impl(&m_data[p1+n2], &m_data[p1], (m_size - p1) * numbytes);

				misc::mem_set(&m_data[p1], value, n2 * numbytes);

				eos<T>(size);
			}
		}


	public:
		template <typename InputIterator>
		inline void insert(iterator position, InputIterator first, InputIterator last)
		{
			if(position.m_cont != this)
				throw misc::exception("invalid iterator");

			insert_impl(position.m_pos, first, last, typename misc::iterator_traits<InputIterator>::iterator_category());
		}

//TODO: "to invalidate all iterators to elements at or past the p1 position"

		/* $21.3.5 modifiers ( erase ) */
		inline container& erase(size_type p1 = 0, size_type n1 = npos)
		{
			if(p1 >= m_size) throw misc::exception("out of valid range");

			if(n1 > m_size - p1)
				n1 = m_size - p1;

			if(n1)
			{
				// invalidate for effective erase only
				invalidate_iterators_gte(p1);

				memmove_impl(&m_data[p1], &m_data[p1+n1], (m_size-p1-n1) * numbytes);

				eos<T>(m_size-n1);
			}

			return *this;
		}

		inline iterator erase(iterator position)
		{
			if(position.m_cont != this) throw misc::exception("invalid iterator");
			if(position.m_pos >= m_size) throw misc::exception("out of valid range");

			size_type p1 = position.m_pos;

			invalidate_iterators_gte(p1);

			memmove_impl(&m_data[p1], &m_data[p1+1], (m_size - p1 - 1) * numbytes);

			eos<T>(m_size-1);

			return position;
		}

		inline iterator erase(iterator first, iterator last)
		{
			if(first.m_cont != this || last.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;
			if(dist > 0)
			{
				invalidate_iterators_gte(first.m_pos);

				//fill the gap
				if(last.m_pos < m_size)
				{
					memmove_impl(&m_data[first.m_pos], &m_data[last.m_pos], (m_size - last.m_pos) * numbytes);
				}

				eos<T>(m_size-dist);
			}

			return first;
		}


		/* $21.3.5 modifiers ( replace ) */
		inline container& replace(size_type p1, size_type n1, const container& str)
		{
			return replace(p1, n1, str, 0, str.length());
		}

		inline container& replace(size_type p1, size_type n1, const container& str, size_type p2, size_type n2)
		{
			if(p1 >= m_size) throw misc::exception("out of valid range");
			if(n1 > m_size - p1)
				n1 = m_size - p1;
			size_type str_size = str.length();
			if(p2 > str_size) throw misc::exception("out of valid range");
			if(n2 > str_size - p2)
				n2 = str_size - p2;
			size_type size = m_size - n1 + n2;

			invalidate_iterators_gte(p1);

			grow(size);

			if(this != &str)
			{
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
				memcpy_impl(&m_data[p1], &str.m_data[p2], n2 * numbytes);

			}
			else if(p1 >= p2)
			{
				/*

				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
						  |x|x|x|x|x|x|
						  |*|*|*|*|*|*|*|*|*|
				  m_size = 17
				  p1=4 n1=6
				  p2=4 n2=9
				  new_size = m_size - n1 + n2 = 20
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|!|!|!|x|
				  (1) move tail up
					  s1 = p1 + n1 = 10
					  d1 = p1 + n2 = 13
					  k1 = m_size - s1 = 7
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|a|b|c|d|e|f|g|x|
				  (2) move down
					  s2 = p2 = 4
					  d2 = p1 = 4
					  k2 = n2 = 9
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|a|b|c|d|e|f|g|x|
				*/
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n2) * numbytes);
				memmove_impl(&m_data[p1], &m_data[p2], n2 * numbytes);
			}
			else if(p1 + n1 <= p2)
			{
				/*
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
					  |x|x|x|x|x|
								|*|*|*|
				  m_size = 17
				  p1=2 n1=5
				  p2=7 n2=3
				  new_size = m_size - n1 + n2 = 15
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
				  (1) move tail up
					  s1 = p1 + n1 = 7
					  d1 = p1 + n2 = 5
					  k1 = m_size - s1 = 10
				  |0|1|2|3|4|7|8|9|a|b|c|d|e|f|g|f|g|x|
				  (2) move down
					  s2 = d1 + p2 - s1 = 5
					  d2 = p1 = 2
					  k2 = n2 = 3
				  |0|1|7|8|9|7|8|9|a|b|c|d|e|f|g|f|g|x|
				  |0|1|7|8|9|7|8|9|a|b|c|d|e|f|g|x|!|!|
				*/
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
				memmove_impl(&m_data[p1], &m_data[p1 + n2 + p2 - p1 - n1], n2 * numbytes);
			}
			/* p1 + n1 > p2 , need to check additional condition */
			else if(n1 < n2)
			{
				/*
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
					  |x|x|x|
						  |*|*|*|*|*|*|*|*|*|*|*|
				  m_size = 17
				  p1=2 n1=3
				  p2=4 n2=11
				  new_size = m_size - n1 + n2 = 25
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|!|!|!|!|!|!|!|!|x|
				  (1) move tail up
					  s1 = p1 + n1 = 5
					  d1 = p1 + n2 = 13
					  k1 = m_size - s1 = 12
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|5|6|7|8|9|a|b|c|d|e|f|g|x|
				  (2) move down 1st part
					  s2 = p2 = 4
					  d2 = p1 = 2
					  k2 = p1 + n1 - p2 = 1
				  |0|1|4|3|4|5|6|7|8|9|a|b|c|5|6|7|8|9|a|b|c|d|e|f|g|x|
				  (3) move down 2nd part
					  s3 = p1 + n2 = 13
					  d3 = p1 + k2 = 3
					  k3 = n2 - k2 = 10
				  |0|1|4|5|6|7|8|9|a|b|c|d|e|5|6|7|8|9|a|b|c|d|e|f|g|x|
				*/
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
				memmove_impl(&m_data[p1], &m_data[p2], (p1 + n1 - p2) * numbytes);
				memmove_impl(&m_data[p1 + p1 + n1 - p2], &m_data[p1 + n2], (n2 - p1 - n1 + p2) * numbytes);
			}
			/* p1 + n1 > p2 , it is assumed n1 >= n2, it can't be otherwise */
			else
			{
				/*
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
					  |x|x|x|x|x|x|x|
								  |*|*|
				  m_size = 17
				  p1=2 n1=7
				  p2=8 n2=2
				  new_size = m_size - n1 + n2 = 12
				  |0|1|2|3|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
				  (1) move down
					  s1 = p2 = 8
					  d1 = p1 = 2
					  k1 = n2 = 2
				  |0|1|8|9|4|5|6|7|8|9|a|b|c|d|e|f|g|x|
				  (2) move tail down
					  s2 = p1 + n1 = 9
					  d2 = p1 + n2 = 4
					  k2 = m_size - s2 = 8
				  |0|1|8|9|9|a|b|c|d|e|f|g|c|d|e|f|g|x|
				  |0|1|2|3|4|5|6|7|8|9|a|b|x|!|!|!|!|!|
				*/
				memmove_impl(&m_data[p1], &m_data[p2], n2 * numbytes);
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
			}

			eos<T>(size);
			return *this;
		}

		inline container& replace(size_type p1, size_type n1, const value_type* ptr, size_type n2)
		{
			if( inside(ptr) )
			{
				return replace(p1, n1, *this, ptr - m_data, n2);
			}
			else
			{
				if(p1 >= m_size) throw misc::exception("out of valid range");

				invalidate_iterators_gte(p1);

				if(n1 > m_size - p1)
					n1 = m_size - p1;
				size_type ptrLen = length<value_type>(ptr);
				if(n2 > ptrLen)
					n2 = ptrLen;

				size_type size = m_size - n1 + n2;
				grow(size);

				//move tail
				memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
				//copy data
				memcpy_impl(&m_data[p1], ptr, n2 * numbytes);

				eos<T>(size);
				return *this;
			}
		}

		inline container& replace(size_type p1, size_type n1, const value_type* ptr)
		{
			return replace(p1, n1, ptr, npos);
		}

		inline container& replace(size_type p1, size_type n1, size_type n2, value_type ch)
		{
			if(p1 >= m_size) throw misc::exception("out of valid range");

			invalidate_iterators_gte(p1);

			if(n1 > m_size - p1)
				n1 = m_size - p1;
			size_type size = m_size - n1 + n2;

			grow(size);

			//move tail up
			memmove_impl(&m_data[p1+n2], &m_data[p1+n1], (m_size-p1-n1) * numbytes);

			//set range
			misc::mem_set(&m_data[p1], ch, n2 * numbytes);

			eos<T>(size);

			return *this;
		}

		inline container& replace(iterator first, iterator last, const container& str)
		{
			if(first.m_cont != last.m_cont || first.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace(first.m_pos, static_cast<size_type>(dist), str, 0, str.length());
		}

		inline container& replace(iterator first, iterator last, const value_type* ptr, size_type n2)
		{
			if(first.m_cont != last.m_cont || first.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace(first.m_pos, static_cast<size_type>(dist), ptr, n2);
		}

		inline container& replace(iterator first, iterator last, const value_type* ptr)
		{
			if(first.m_cont != last.m_cont || first.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace(first.m_pos, dist, ptr, npos);
		}

		inline container& replace(iterator first, iterator last, size_type n2, value_type ch)
		{
			if(first.m_cont != last.m_cont || first.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace(first.m_pos, dist, n2, ch);
		}


	private:
		/* implementation of:
		   template <class InputIterator>
		   string& replace ( iterator first, iterator last, InputIterator First, InputIterator Last );
		*/
		inline container& replace_impl(size_type p1, size_type n1, const iterator& first2, const iterator& last2)
		{
			if(first2.m_cont != last2.m_cont || first2.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last2 - first2;

			if(dist < 0)
				dist = 0;

			return replace(p1, n1, *(first2.m_cont), first2.m_pos, dist);
		}

		inline container& replace_impl(size_type p1, size_type n1, const const_iterator& first2, const const_iterator& last2)
		{
			if(first2.m_cont != last2.m_cont || first2.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last2 - first2;

			if(dist < 0)
				dist = 0;

			return replace(p1, n1, first2.m_cont, first2.m_pos, dist);
		}

		inline container& replace_impl(size_type p1, size_type n1, const reverse_iterator& first2, const reverse_iterator& last2)
		{
			if(first2.m_cont != last2.m_cont || first2.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last2 - first2;

			if(dist < 0)
				dist = 0;

			replace(p1, n1, first2.m_cont, last2.m_pos+1, dist);

			swap_range(p1, p1 + dist);

			return *this;
		}

		inline container& replace_impl(size_type p1, size_type n1, const const_reverse_iterator& first2, const const_reverse_iterator& last2)
		{
			if(first2.m_cont != last2.m_cont || first2.m_cont == 0)
				throw misc::exception("invalid iterator");

			difference_type dist = last2 - first2;

			if(dist < 0)
				dist = 0;

			replace(p1, n1, first2.m_cont, last2.m_pos+1, dist);

			swap_range(p1, p1 + dist);

			return *this;
		}

		/*
		  -due to specialization for replace_impl(const iterator& ...) and friends,
		   compiler cannot find any suitable replace_impl for next code:

		  misc::generic_array<char> charr(10, 'x'), charr2(2, 'a');
		  charr.replace(charr.begin(), ++charr.begin(),
						charr2.c_str(), charr2.c_str()+2);
		*/
		inline container& replace_impl(size_type p1, size_type n1, const value_type* first, const value_type* last)
		{
			if(!first || !last)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace(p1, n1, first, dist);
		}

		template<typename InputIterator>
		inline container& replace_impl(size_type p1, size_type n1, const InputIterator& first2, const InputIterator& last2, misc::random_access_iterator_tag)
		{
			return replace_impl(p1, n1, first2, last2);
		}

		template<typename InputIterator>
		inline container& replace_impl(size_type p1, size_type n1, InputIterator n2, InputIterator value, misc::input_iterator_tag)
		{
			return replace(p1, n1, n2, value);
		}

	public:
		template<typename InputIterator>
		inline container& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
		{
			if(first.m_cont != last.m_cont || first.m_cont != this)
				throw misc::exception("invalid iterator");

			difference_type dist = last - first;

			if(dist < 0)
				dist = 0;

			return replace_impl(first.m_pos, dist, first2, last2, typename misc::iterator_traits<InputIterator>::iterator_category());
		}


		/* $21.3.5 modifiers ( copy ) */
		inline size_type copy(value_type* ptr, size_type n1, size_type p1 = 0) const
		{
			if(p1 >= m_size) throw misc::exception("out of valid range");

			if(n1 > m_size - p1)
				n1 = m_size - p1;

			memmove_impl(ptr, &m_data[p1], n1 * numbytes);

			return n1;
		}

//TODO: "to rename str everywhere with something more appropriate ?"


		/* $21.3.5 modifiers ( swap ) */
		inline void swap ( container& vec )
		{
			misc::swap<Allocator>(m_allocator, vec.m_allocator);
			misc::swap<pointer>(m_data, vec.m_data);
			misc::swap<size_type>(m_size, vec.m_size);
			misc::swap<size_type>(m_capacity, vec.m_capacity);
			misc::swap<iterator_array*>(m_itarray, vec.m_itarray);
		}


		/* $21.3.6 string operations */
		inline const value_type *c_str( ) const
		{
			return m_data;      // if string is '\0' terminated.
		}

		inline const value_type *data( ) const
		{
			return m_data;      // if string is '\0' terminated.
		}

		allocator_type get_allocator() const
		{
			return m_allocator;
		}

		/* $21.3.6 string operations (find) */
		inline size_type find(const container& str, size_type p1 = 0) const
		{
			return find(str.m_data, p1, str.length());
		}

		inline size_type find(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 >= m_size) throw misc::exception("out of valid range");

			size_type ptrLen = length<value_type>(ptr);

			if(n2 > ptrLen) return npos;

			if(n2)
			{
				//find
				for(size_type i = p1; i + n2 <= m_size; ++i)
				{
					size_type i2 = i;
					size_type j2 = 0;
					while(j2 < n2 && m_data[i2++] == ptr[j2++])
						;
					if(j2 == n2)
						return i;
				}
			}

			return npos;
		}

		inline size_type find(const value_type* ptr, size_type p1 = 0) const
		{
			return find(ptr, p1, length<value_type>(ptr));
		}

		inline size_type find(value_type ch, size_type p1 = 0) const
		{
			for(size_type i = p1; i < m_size; ++i)
			{
				if(m_data[i] == ch)
					return i;
			}

			return npos;
		}


		/* $21.3.6 string operations (rfind) */
		inline size_type rfind(const container& str, size_type p1 = npos) const
		{
			return rfind(str.m_data, p1, str.length());
		}

		inline size_type rfind(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 > m_size) p1 = m_size;
			if(n2 > m_size) return npos;
			if(p1 + n2 > m_size)
				p1 = m_size - n2;
			size_type ptrsz = length<value_type>(ptr);
			if(n2 > ptrsz) return npos;

			if(n2)
			{
				//rfind
				for(size_type i = p1; i != npos; --i)
				{
					size_type i2 = i;
					size_type j2 = 0;
					while(j2 < n2 && m_data[i2++] == ptr[j2++])
						;

					if(j2 == n2)
						return i;
				}
			}

			return npos;
		}

		inline size_type rfind(const value_type* ptr, size_type p1 = npos) const
		{
			return rfind(ptr, p1, length<value_type>(ptr));
		}

		inline size_type rfind(value_type ch, size_type p1 = npos) const
		{
			p1 = misc::min<size_type>(p1, m_size - 1);

			//rfind
			for(size_type i = p1; i != npos; --i)
			{
				if(m_data[i] == ch)
					return i;
			}

			return npos;
		}


		/* $21.3.6 string operations (find_first_of) */
		inline size_type find_first_of(const container& str, size_type pos = 0) const
		{
			return find_first_of(str.m_data, pos, str.length());
		}

		inline size_type find_first_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");
			size_type ptrsz = length<value_type>(ptr);
			if(n2 > ptrsz)
				n2 = ptrsz;

			if(n2)
			{
				//find
				for(size_type i = p1; i < m_size; ++i)
				{
					for(size_type j = 0; j < n2; ++j)
					{
						if(m_data[i] == ptr[j])
							return i;
					}
				}
			}

			return npos;
		}

		inline size_type find_first_of(const value_type* ptr, size_type p1 = 0) const
		{
			return find_first_of(ptr, p1, length<value_type>(ptr));
		}

		inline size_type find_first_of(value_type c, size_type p1 = 0) const
		{
			//find
			for(size_type i = p1; i < m_size; ++i)
			{
				if(m_data[i] == c)
					return i;
			}

			return npos;
		}

		/* $21.3.6 string operations (find_last_of) */
		inline size_type find_last_of(const container& str, size_type p1 = npos) const
		{
			return find_last_of(str.c_str(), p1, str.length());
		}

		inline size_type find_last_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 >= m_size) p1 = m_size - 1;
			size_type ptrsz = length<value_type>(ptr);
			if(n2 > ptrsz)
				n2 = ptrsz;

			if(n2)
			{
				//find
				for(size_type i = p1; i != npos; --i)
				{
					for(size_type j = 0; j < n2; ++j)
					{
						if( m_data[i] == ptr[j] )
							return i;
					}
				}
			}

			return npos;
		}

		inline size_type find_last_of(const value_type* ptr, size_type p1 = npos) const
		{
			return find_last_of(ptr, p1, length<value_type>(ptr));
		}

		inline size_type find_last_of(value_type ch, size_type p1 = npos) const
		{
			if( p1 >= m_size) p1 = m_size - 1;

			//find
			for(size_type i = p1; i != npos; --i)
			{
				if(m_data[i] == ch)
					return i;
			}

			return npos;
		}

		/* $21.3.6 string operations (find_first_not_of) */
		inline size_type find_first_not_of(const container& str, size_type p1 = 0) const
		{
			return find_first_not_of(str.m_data, p1, str.length());
		}

		inline size_type find_first_not_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");
			size_type ptrLen = length<value_type>(ptr);
			if(n2 > ptrLen)
				n2 = ptrLen;

			if(n2)
			{
				//find
				for(size_type i = p1; i < m_size; ++i)
				{
					bool found = false;
					for(size_type j=0; j < n2; ++j)
					{
						if(m_data[i] == ptr[j])
						{
							found = true;
							break;
						}
					}

					if(!found)
						return i; //m_data[i] is not in ptr
				}
			}

			return npos;
		}

		inline size_type find_first_not_of(const value_type* ptr, size_type n1 = 0) const
		{
			return find_first_not_of(ptr, n1, length<value_type>(ptr));
		}

		inline size_type find_first_not_of(value_type ch, size_type p1 = 0) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");

			//find
			for(size_type i = p1; i < m_size; ++i)
			{
				if(m_data[i] != ch)
					return i;
			}

			return npos;
		}


		/* $21.3.6 string operations (find_last_not_of) */
		inline size_type find_last_not_of(const container& str, size_type p1 = npos) const
		{
			return find_last_not_of(str.m_data, p1, str.length());
		}

		inline size_type find_last_not_of(const value_type* ptr, size_type p1, size_type n2) const
		{
			if(p1 >= m_size)
				p1 = m_size - 1;

			size_type ptrLen = length<value_type>(ptr);
			if(n2 > ptrLen)
				n2 = ptrLen;

			if(n2)
			{
				//find
				for(size_type i = p1; i != npos; --i)
				{
					bool found = false;
					for(size_type j = 0; j < n2; ++j)
					{
						if(m_data[i] == ptr[j])
						{
							found = true;
							break;
						}
					}

					if(!found)
						return i; // m_data[i] is not in ptr
				}
			}

			return npos;
		}

		inline size_type find_last_not_of(const value_type* ptr, size_type p1 = npos) const
		{
			return find_last_not_of(ptr, p1, length<value_type>(ptr));
		}

		inline size_type find_last_not_of(value_type ch, size_type p1 = npos) const
		{
			if(p1 >= m_size) p1 = m_size - 1;
			//find
			for(size_type i = p1; i != npos; --i)
			{
				if(m_data[i] != ch)
					return i;
			}

			return npos;
		}


		/* $21.3.6 string operations (substr) */
		inline container substr(size_type p1 = 0, size_type n1 = npos) const
		{
			if(p1 > m_size) throw misc::exception("ouf of valid range");
			if(n1 > m_size - p1)
				n1 = m_size - p1;

			return container(&m_data[p1], n1);
		}


		/* $21.3.6 string operations (compare) */
		inline int compare(const container& str) const
		{
			size_type rsz = str.size();
			size_type minsz = misc::min<size_type>(m_size, rsz);
			size_type i=0;
			while(i < minsz && m_data[i] == str.m_data[i])
			{
				++i;
			}

			if(i < minsz)
			{
				value_type c1 = m_data[i];
				value_type c2 = str.m_data[i];
				return ((c1 < c2)? -1 : (c1 > c2));
			}
			else
			{
				return ((m_size < rsz)? -1 : (m_size > rsz));
			}
		}

		inline int compare(size_type p1, size_type n1, const container& str) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");
			size_type lsz = m_size - p1;
			size_type rsz = str.size();
			size_type minsz = misc::min<size_type>(lsz, rsz, n1);
			
			size_type i = 0;
			while(i < minsz && m_data[p1] == str.m_data[i])
			{
				++p1;
				++i;
			}

			if(i == n1)
				return 0;

			if(i == minsz)
			{
				return ((lsz < rsz) ? -1 : lsz > rsz);
			}

			value_type c1 = m_data[p1];
			value_type c2 = str.m_data[i];
			return ((c1 < c2) ? -1 : (c1 > c2));
		}

		inline int compare(size_type p1, size_type n1, const container& str, size_type p2, size_type n2) const
		{
			if(p1 > m_size || p2 > str.m_size) throw misc::exception("out of valid range");
			size_type lsz = m_size - p1;
			size_type rsz = str.m_size - p2;			
			size_type minsz = misc::min<size_type>(lsz, rsz, n1, n2);

			size_type i = 0;
			while(i < minsz && m_data[p1] == str.m_data[p2])
			{
				++p1;
				++p2;
				++i;
			}

			if(i < minsz)
			{
				value_type c1 = m_data[p1];
				value_type c2 = str.m_data[p2];
				return ((c1 < c2) ? -1 : (c1 > c2));
			}
			
			if(n1 == n2 && n1 <= lsz && n1 <= rsz && i == n1)
				return 0;
			
			return ((lsz < rsz) ? -1 : lsz > rsz);
		}

		inline int compare(const value_type* ptr) const
		{
			size_type size = length<value_type>(ptr);
			size_type minsz = misc::min<size_type>(m_size, size);
			size_type i = 0;
			while(i < minsz && m_data[i] == ptr[i])
			{
				++i;
			}

			if(i < minsz)
			{
				value_type c1 = m_data[i];
				value_type c2 = ptr[i];
				return ((c1 < c2) ? -1 : (c1 > c2));
			}
			else
			{
				return ((m_size < size) ? -1 : m_size > size);
			}
		}

		inline int compare(size_type p1, size_type n1, const value_type* ptr) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");

			size_type lsz = m_size - p1;
			size_type rsz = length<value_type>(ptr);
			size_type minsz = misc::min<size_type>(lsz, rsz, n1);
			
			size_type i = 0;
			while(i < minsz && m_data[p1] == ptr[i])
			{
				++p1;
				++i;
			}

			if(i == n1)
				return 0;

			if(i == minsz)
			{
				return ((lsz < rsz) ? -1 : lsz > rsz);
			}

			value_type c1 = m_data[p1];
			value_type c2 = ptr[i];
			return ((c1 < c2) ? -1 : (c1 > c2));
		}

		inline int compare(size_type p1, size_type n1, const value_type* ptr, size_type n2) const
		{
			if(p1 > m_size) throw misc::exception("out of valid range");
			size_type lsz = m_size - p1;
			size_type rsz = length<value_type>(ptr);			
			size_type minsz = misc::min<size_type>(lsz, rsz, n1, n2);

			size_type i = 0;
			while(i < minsz && m_data[p1] == ptr[i])
			{
				++p1;
				++i;
			}

			if(i < minsz)
			{
				value_type c1 = m_data[p1];
				value_type c2 = ptr[i];
				return ((c1 < c2) ? -1 : (c1 > c2));
			}

			if(n1 == n2 && n1 <= lsz && n1 <= rsz && i == n1)
				return 0;

			return ((lsz < rsz) ? -1 : lsz > rsz);
		}



		/* ISO/IEC 14882:2003  23.2.4 Class template vector */
		// 23.2.4.2 element access:
		inline reference front()
		{
			if( !m_size ) throw misc::exception("out of valid range");
			return m_data[0];
		}

		inline const_reference front() const
		{
			if( !m_size ) throw misc::exception("out of valid range");
			return m_data[0];
		}

		inline reference back()
		{
			if( !m_size ) throw misc::exception("out of valid range");
			return m_data[m_size - 1];
		}

		inline const_reference back() const
		{
			if( !m_size ) throw misc::exception("out of valid range");
			return m_data[m_size - 1];
		}

		// 23.2.4.3 modifiers (vector):
		inline void pop_back()
		{
			if( m_size )
			{
				eos<T>(m_size - 1);
			}
		}
	};  // class


	/* operators not accessible directly */
	namespace generic_array_ops
	{

		//Operators
		//Concatenates two string objects.
		template<typename T, typename Allocator, int attributes>
		misc::generic_array<T, Allocator, attributes> operator+ (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			misc::generic_array<T, Allocator, attributes> res(Left);
			res += Right;
			return res;
		}

		template<typename T, typename Allocator, int attributes>
		misc::generic_array<T, Allocator, attributes> operator+ (
			const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			misc::generic_array<T, Allocator, attributes> res(Left);
			res += Right;
			return res;
		}

		template<typename T, typename Allocator, int attributes>
		misc::generic_array<T, Allocator, attributes> operator+ (
			const misc::generic_array<T, Allocator, attributes>& Left, const T Right)
		{
			misc::generic_array<T, Allocator, attributes> res(Left);
			res += Right;
			return res;
		}

		template<typename T, typename Allocator, int attributes>
		misc::generic_array<T, Allocator, attributes> operator+ (
			const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			misc::generic_array<T, Allocator, attributes> res(Left);
			res += Right;
			return res;
		}

		template<typename T, typename Allocator, int attributes>
		misc::generic_array<T, Allocator, attributes> operator+ (
			const T Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			misc::generic_array<T, Allocator, attributes> res(1, Left);
			res += Right;
			return res;
		}

		//Tests if the string object on the left side of the operator is not equal
		//to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator!= (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) != 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator!= (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) != 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator!= (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) != 0;
		}

		//Tests if the string object on the left side of the operator is equal to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator== (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) == 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator== (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) == 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator== (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) == 0;
		}

		//Tests if the string object on the left side of the operator is less than to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator< (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) < 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator< (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) < 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator< (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) > 0;
		}

		//Tests if the string object on the left side of the operator is less than or equal to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator<= (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) <= 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator<= (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) <= 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator<= (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) >= 0;
		}

		//Tests if the string object on the left side of the operator is greater
		//than to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator> (
			const misc::generic_array<T, Allocator, attributes>& Left,
			const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) > 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator> (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) > 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator> (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) < 0;
		}

		//Tests if the string object on the left side of the operator is greater
		//than or equal to the string object on the right side.
		template<typename T, typename Allocator, int attributes>
		bool operator>= (const misc::generic_array<T, Allocator, attributes>& Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Left.compare(Right) >= 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator>= (const misc::generic_array<T, Allocator, attributes>& Left, const T* Right)
		{
			return Left.compare(Right) >= 0;
		}

		template<typename T, typename Allocator, int attributes>
		bool operator>= (const T* Left, const misc::generic_array<T, Allocator, attributes>& Right)
		{
			return Right.compare(Left) <= 0;
		}


		//A template function that writes a string into the output stream.
		template<typename T, typename Allocator, int attributes>
		std::basic_ostream<T>& operator<< (
			std::basic_ostream<T>& Ostr, const misc::generic_array<T, Allocator, attributes>& str)
		{
			Ostr << str.c_str();
			return Ostr;
		}


		//A template function that reads a string from an input stream.
		template<typename T, typename Allocator, int attributes>
		std::basic_istream<T>& operator>> (
			std::basic_istream<T>& Istr, misc::generic_array<T, Allocator, attributes>& Right)
		{
			std::basic_string<T> chunk;
			Istr >> chunk;
			Right += chunk.c_str();
			return Istr;
		}

		//Specialized template function
		template<typename T, typename Allocator, int attributes>
		void swap(
			misc::generic_array<T, Allocator, attributes>& Left,
			misc::generic_array<T, Allocator, attributes>& Right)
		{
			Left.swap(Right);
		}
	} //namespace
}//namespace

#endif//__generic_array_hpp__
