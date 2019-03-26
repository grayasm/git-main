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


#include "iterator.hpp"
#include "exception.hpp"



#ifndef __vector_hpp__
#define __vector_hpp__

namespace stl
{
    template<typename container>
    struct vector_iterator_base
    {
        container*						m_cont;
        typename container::size_type	m_pos;
    };

    template<typename T, typename Allocator> class vector;
    template<typename container> class vector_const_iterator;
    template<typename container> class vector_const_reverse_iterator;

    template<typename container>
    class vector_iterator :
        public stl::iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::vector_iterator_base<container>
    {
    public:
        // types
        typedef stl::iterator<stl::random_access_iterator_tag, typename container::value_type>  base;
        typedef typename base::iterator_category    iterator_category;
        typedef typename base::value_type           value_type;
        typedef typename base::difference_type      difference_type;
        typedef typename base::distance_type        distance_type;
        typedef typename base::pointer              pointer;
        typedef typename base::reference            reference;
        typedef typename container::size_type       size_type;
        typedef typename stl::vector_iterator_base<container>   base2;
        friend class stl::vector<typename container::value_type, typename container::allocator_type>;
        friend class vector_const_iterator<container>;


    private:
        inline void init()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

    private:
        vector_iterator(container* cont, size_type pos)
        {
            init();

            base2::m_cont = cont;
            base2::m_pos = pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }
        }

    public:
        vector_iterator()
        {
            init();
        }


        vector_iterator(const vector_iterator& it)
        {
            init();
            *this = it;
        }

        ~vector_iterator()
        {
            if (base2::m_cont)
            {
                base2::m_cont->remove_iterator(this);
            }
        }

        vector_iterator& operator=(const vector_iterator& it)
        {
            if (this != &it)
            {
                if (base2::m_cont)
                {
                    base2::m_cont->remove_iterator(this);
                }

                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;

                if (base2::m_cont)
                {
                    base2::m_cont->add_iterator(this);
                }
            }
            return *this;
        }

        reference operator*() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos];
        }

        pointer operator->() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return &(*base2::m_cont)[base2::m_pos];
        }

        vector_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        vector_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        vector_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        vector_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        vector_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        vector_iterator operator+(difference_type off) const
        {
            vector_iterator<container> tmp = *this;
            return tmp += off;
        }

        vector_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        vector_iterator operator-(difference_type off) const
        {
            vector_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const vector_iterator& it) const
        {
            return static_cast<difference_type>(base2::m_pos - it.m_pos);
        }

        bool operator==(const vector_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const vector_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const vector_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator>(const vector_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator<=(const vector_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        bool operator>=(const vector_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos + off];
        }
    };  // iterator


    template<typename container>
    class vector_const_iterator :
        public stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::vector_iterator_base<container>
    {
    public:
        typedef stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>  base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;
        typedef typename container::size_type      size_type;
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;


    private:
        inline void init()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

    private:
        vector_const_iterator(container* cont, size_type pos)
        {
            init();

            base2::m_cont = cont;
            base2::m_pos = pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }
        }

    public:
        vector_const_iterator()
        {
            init();
        }

        vector_const_iterator(const vector_const_iterator& it)
        {
            init();
            *this = it;
        }

        ~vector_const_iterator()
        {
            if (base2::m_cont)
            {
                base2::m_cont->remove_iterator(this);
            }
        }

        vector_const_iterator& operator=(const vector_const_iterator& it)
        {
            if (this != &it)
            {
                if (base2::m_cont)
                {
                    base2::m_cont->remove_iterator(this);
                }

                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;

                if (base2::m_cont)
                {
                    base2::m_cont->add_iterator(this);
                }

            }
            return *this;
        }

        vector_const_iterator& operator=(const vector_iterator<container>& it)
        {
            if (base2::m_cont)
            {
                base2::m_cont->remove_iterator(this);
            }

            base2::m_cont = it.m_cont;
            base2::m_pos = it.m_pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }

            return *this;
        }

        vector_const_iterator(const vector_iterator<container>& it)
        {
            init();
            *this = it;
        }

        reference operator*() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos];
        }

        pointer operator->() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return &(*base2::m_cont)[base2::m_pos];
        }

        vector_const_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        vector_const_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_const_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        vector_const_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        vector_const_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_const_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        vector_const_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        vector_const_iterator operator+(difference_type off) const
        {
            vector_const_iterator<container> tmp = *this;
            return tmp += off;
        }

        vector_const_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        vector_const_iterator operator-(difference_type off) const
        {
            vector_const_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const vector_const_iterator& it) const
        {
            return base2::m_pos - it.m_pos;
        }

        bool operator==(const vector_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const vector_const_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const vector_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator>(const vector_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator<=(const vector_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        bool operator>=(const vector_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos + off];
        }
    };  // const_iterator


    template<typename container>
    class vector_reverse_iterator :
        public stl::iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::vector_iterator_base<container>
    {
    public:
        typedef stl::iterator<stl::random_access_iterator_tag, typename container::value_type>    base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::pointer             pointer;
        typedef typename base::reference           reference;
        typedef typename container::size_type      size_type;
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;
        friend class vector_const_reverse_iterator<container>;


    private:
        inline void init()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

    private:
        vector_reverse_iterator(container* cont, size_type pos)
        {
            init();

            base2::m_cont = cont;
            base2::m_pos = pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }
        }

    public:
        vector_reverse_iterator()
        {
            init();
        }


        vector_reverse_iterator(const vector_reverse_iterator& it)
        {
            init();
            *this = it;
        }

        ~vector_reverse_iterator()
        {
            if (base2::m_cont != 0)
            {
                base2::m_cont->remove_iterator(this);
            }
        }

        vector_reverse_iterator& operator=(const vector_reverse_iterator& it)
        {
            if (this != &it)
            {
                if (base2::m_cont)
                {
                    base2::m_cont->remove_iterator(this);
                }

                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;

                if (base2::m_cont)
                {
                    base2::m_cont->add_iterator(this);
                }
            }
            return *this;
        }

        reference operator*() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos];
        }

        pointer operator->() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return &(*base2::m_cont)[base2::m_pos];
        }

        vector_reverse_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        vector_reverse_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_reverse_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        vector_reverse_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        vector_reverse_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_reverse_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        vector_reverse_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        vector_reverse_iterator operator+(difference_type off) const
        {
            vector_reverse_iterator<container> tmp = *this;
            return tmp += off;
        }

        vector_reverse_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        vector_reverse_iterator operator-(difference_type off) const
        {
            vector_reverse_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const vector_reverse_iterator& it) const
        {
            return it.m_pos - base2::m_pos;
        }

        bool operator==(const vector_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && it.m_pos == base2::m_pos);
        }

        bool operator!=(const vector_reverse_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const vector_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator>(const vector_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator<=(const vector_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        bool operator>=(const vector_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos - off];
        }
    };  // reverse_iterator


    template<typename container>
    class vector_const_reverse_iterator :
        public stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::vector_iterator_base<container>
    {
    public:
        typedef stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>  base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;
        typedef typename container::size_type      size_type;
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;



    private:
        inline void init()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

    private:
        vector_const_reverse_iterator(container* cont, size_type pos)
        {
            init();

            base2::m_cont = cont;
            base2::m_pos = pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }
        }

    public:
        vector_const_reverse_iterator()
        {
            init();
        }

        vector_const_reverse_iterator(const vector_const_reverse_iterator& it)
        {
            init();
            *this = it;
        }

        ~vector_const_reverse_iterator()
        {
            if (base2::m_cont)
            {
                base2::m_cont->remove_iterator(this);
            }
        }

        vector_const_reverse_iterator& operator=(const vector_const_reverse_iterator& it)
        {
            if (this != &it)
            {
                if (base2::m_cont)
                {
                    base2::m_cont->remove_iterator(this);
                }

                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;

                if (base2::m_cont)
                {
                    base2::m_cont->add_iterator(this);
                }
            }
            return *this;
        }

        vector_const_reverse_iterator& operator=(const vector_reverse_iterator<container>& it)
        {
            if (base2::m_cont)
            {
                base2::m_cont->remove_iterator(this);
            }

            base2::m_cont = it.m_cont;
            base2::m_pos = it.m_pos;

            if (base2::m_cont)
            {
                base2::m_cont->add_iterator(this);
            }

            return *this;
        }

        vector_const_reverse_iterator(const vector_reverse_iterator<container>& it)
        {
            init();
            *this = it;
        }


        reference operator*() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos];
        }

        pointer operator->() const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return &(*base2::m_cont)[base2::m_pos];
        }

        vector_const_reverse_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        vector_const_reverse_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_const_reverse_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        vector_const_reverse_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        vector_const_reverse_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            vector_const_reverse_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        vector_const_reverse_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        vector_const_reverse_iterator operator+(difference_type off) const
        {
            vector_const_reverse_iterator<container> tmp = *this;
            return tmp += off;
        }

        vector_const_reverse_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        vector_const_reverse_iterator operator-(difference_type off) const
        {
            vector_const_reverse_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const vector_const_reverse_iterator& it) const
        {
            return it.m_pos - base2::m_pos;
        }

        bool operator==(const vector_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const vector_const_reverse_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const vector_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator>(const vector_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator<=(const vector_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        bool operator>=(const vector_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

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
    struct vector_spec
    {
        typedef T value;
    };



	//	ISO/IEC 14882:2003  $23.2.4 Class template vector
	template<typename T, typename Allocator = stl::allocator<T>>
	class vector
	{
	public:
		typedef vector<T, Allocator>                    container;

		// types:
        typedef typename Allocator::value_type           value_type;
        typedef typename Allocator::size_type            size_type;
        typedef typename Allocator::difference_type      difference_type;
        typedef Allocator                                allocator_type;

        typedef typename Allocator::reference            reference;
        typedef typename Allocator::const_reference      const_reference;
        typedef typename Allocator::pointer              pointer;
        typedef typename Allocator::const_pointer        const_pointer;

	public:
		typedef typename base::iterator					iterator;
		typedef typename base::const_iterator			const_iterator;
		typedef typename base::reverse_iterator			reverse_iterator;
		typedef typename base::const_reverse_iterator	const_reverse_iterator;


    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;

    private:
        void init(const Allocator& alloc)
        {
            m_data = 0;
            m_size = 0;
            m_capacity = 0;
            m_allocator = alloc;
        }

        void mem_alloc(size_type cap)
        {
            pointer mem = 0;

            /* buy memory, no ctor() called */
            mem = m_allocator.allocate(cap);

            if (mem == 0)
                throw misc::exception("bad allocation");

            m_data = mem;
            m_capacity = cap;
        }

        inline void grow(size_type cap)
        {
            if (m_capacity >= cap) return;

            pointer mem = 0;

            stl::mem_realloc(&mem, cap + 1, m_data, m_size, m_allocator);

            m_data = mem;
            m_capacity = cap;
        }



	public:       
		// $23.2.4.1 construct/copy/destroy:
		vector()
		{
            init(alloc);
            mem_alloc(1);
            
		}

		explicit vector(size_type n, const T& value = T())
		{
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
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
			return vector_ops::operator ==(*this, Right);
		}

		bool operator<(const container& Right)
		{
			return vector_ops::operator <(*this, Right);
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
	template<typename T, typename Allocator>
	bool operator== (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		
		typedef stl::vector<T, Allocator> Cont;
		
		typename Cont::size_type sz = Left.size();
		if(sz != Right.size())
			return false;

		typename Cont::size_type j = 0;
		while(j < sz && Left[j] == Right[j])
			++j;

		return j == sz;
		
	}

	template<typename T, typename Allocator>
	bool operator< (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		return stl::lexicographical_compare(
			Left.begin(), Left.end(), Right.begin(), Right.end());
	}

	template<typename T, typename Allocator>
	bool operator!= (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		return !(Left == Right);
	}

	template<typename T, typename Allocator>
	bool operator> (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		return (Left != Right) && !(Left < Right);
	}

	template<typename T, typename Allocator>
	bool operator>= (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		return !(Left < Right);
	}

	template<typename T, typename Allocator>
	bool operator<= (
		const stl::vector<T, Allocator>& Left,
		const stl::vector<T, Allocator>& Right)
	{
		return (Left < Right) || (Left == Right);
	}

	// specialized algorithms:
	template<typename T, typename Allocator>
	void swap (
		stl::vector<T, Allocator>& Left, 
		stl::vector<T, Allocator>& Right)
	{
		return Left.swap(Right);
	}
#endif
}  // namespace

#endif//__vector_hpp__
