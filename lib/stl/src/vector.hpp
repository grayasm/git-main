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
#include "memory.hpp"
#include "memmanip.hpp"

//        typedef std::vector<iterator_base*>             iterator_array;
#include <vector>


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
		typedef typename vector_iterator<container>		            iterator;
        typedef typename vector_const_iterator<container>			const_iterator;
        typedef typename vector_reverse_iterator<container>		    reverse_iterator;
        typedef typename vector_const_reverse_iterator<container>   const_reverse_iterator;

        typedef vector_iterator_base<container>         iterator_base;
        typedef std::vector<iterator_base*>             iterator_array;

    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;


        // debug_iterator implementation
        iterator_array*         m_itarray;
        friend class vector_iterator<container>;
        friend class vector_const_iterator<container>;
        friend class vector_reverse_iterator<container>;
        friend class vector_const_reverse_iterator<container>;


    private:
        inline void init(const Allocator& alloc)
        {
            m_data = 0;
            m_size = 0;
            m_capacity = 0;
            m_allocator = alloc;

            // ms comp warn 4127
            int hasITDBG = 0;// (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (hasITDBG)
            {
                m_itarray = new iterator_array;
            }
        }

        inline void mem_alloc(size_type cap)
        {
            pointer mem = 0;

            /* buy memory, no ctor() called */
            mem = m_allocator.allocate(cap + 1);

            if (mem == 0)
                throw stl::exception("bad allocation");

            m_data = mem;
            m_capacity = cap;
        }

        inline void grow(size_type cap)
        {
            if (m_capacity >= cap) return;

            pointer mem = 0;

            // ms comp warn 4127
            int hasPOD = 0;// (attributes & stl::GENERIC_ARRAY_HAS_POD_TYPE);
            if (hasPOD)
            {
                stl::mem_realloc_pod(&mem, cap + 1, m_data, m_size, m_allocator);
            }
            else
            {
                stl::mem_realloc(&mem, cap + 1, m_data, m_size, m_allocator);
            }

            m_data = mem;
            m_capacity = cap;
        }

        template<typename T2>
        inline size_t length(const value_type* ptr) const
        {
            return length(ptr, stl::vector_spec<T2>());
        }

        template<typename T2>
        inline size_t length(const value_type* ptr, stl::vector_spec<T2>) const
        {
            if (ptr == 0) throw stl::exception("null pointer");
            const value_type* p = ptr;
            while (*p != 0)
                p++;
            return (p - ptr);
        }

        inline size_t length(const value_type* ptr, stl::vector_spec<char>) const
        {
            return ::strlen(ptr);
        }

        inline size_t length(const value_type* ptr, stl::vector_spec<unsigned char>) const
        {
#if defined _WIN32
            return ::_mbslen(ptr);
#else // LINUX
            /*	I will find out that this doesn't work when the string will hold
            some Russian characters.
            */
            return ::strlen((const char*)ptr);
#endif
        }

        inline size_t length(const value_type* ptr, stl::vector_spec<wchar_t>) const
        {
            return ::wcslen(ptr);
        }

        template<typename T2>
        inline void eos(size_type size)
        {
            eos(size, stl::vector_spec<T2>());
        }

        template<typename T2>
        inline void eos(size_type size, stl::vector_spec<T2>)
        {
            if (m_capacity < size) throw stl::exception("bad size");

            // ms comp warn 4127
            int hasPOD = 0;// (attributes & stl::GENERIC_ARRAY_HAS_POD_TYPE);
            if (size < m_size && !hasPOD)
            {
                // Non POD types;
                value_type* unused = m_data + size;
                stl::mem_destroy(&unused, m_size - size, m_allocator);
            }
            m_size = size;
        }

        inline void eos(size_type size, stl::vector_spec<char>)
        {
            if (m_capacity < size) throw stl::exception("bad size");
            m_size = size;
            m_data[m_size] = 0;
        }

        inline void eos(size_type size, stl::vector_spec<unsigned char>)
        {
            if (m_capacity < size) throw stl::exception("bad size");
            m_size = size;
            m_data[m_size] = 0;
        }

        inline void eos(size_type size, stl::vector_spec<wchar_t>)
        {
            if (m_capacity < size) throw stl::exception("bad size");
            m_size = size;
            m_data[m_size] = 0;
        }

        inline void swap_range(size_type beg, size_type end)
        {
            if (beg < end)
            {
                for (size_type i = beg, j = end - 1; i < j; ++i, --j)
                {
                    stl::swap<value_type>(m_data[i], m_data[j]);
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
            int hasPOD = 0;// (attributes & stl::GENERIC_ARRAY_HAS_POD_TYPE);
            if (hasPOD)
            {
                stl::mem_copy_pod(dest, src, bytes);
            }
            else
            {
                stl::mem_copy(dest, src, bytes);
            }
        }

        inline void memmove_impl(pointer dest, const_pointer src, size_type bytes) const
        {
            // ms comp warn 4127
            int hasPOD = 0;// (attributes & stl::GENERIC_ARRAY_HAS_POD_TYPE);
            if (hasPOD)
            {
                stl::mem_move_pod(dest, src, bytes);
            }
            else
            {
                stl::mem_move(dest, src, bytes);
            }
        }


        // debug_iterator implementation
        inline void add_iterator(iterator_base* it)
        {
            // ms comp warn 4127
            int hasITDBG = 0;// (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (!hasITDBG)
            {
                return;
            }

            if (it->m_cont != this)
                throw stl::exception("invalid debug iterator");

            //	extra test for debugging
#if CHECK_ITERATOR_DUPLICATES
            for (size_t i = 0; i < m_itarray->size(); ++i)
            {
                if (it == (*m_itarray)[i])
                    throw stl::exception("duplicate iterator");
            }
#endif

            m_itarray->push_back(it);
        }

        inline void remove_iterator(iterator_base* it)
        {
            // ms comp warn 4127
            int hasITDBG = 0;// (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (!hasITDBG)
            {
                return;
            }

            /* container must match */
            if (it->m_cont != this)
                throw stl::exception("invalid debug iterator");

            //	Before iterator gets destroyed, it asks for removal.
            for (typename iterator_array::iterator beg = m_itarray->begin(); beg != m_itarray->end();)
            {
                iterator_base* iter = *beg;
                if (it == iter)
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
            int hasITDBG = 0;// (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (!hasITDBG)
            {
                return;
            }

            /*	When a container gets deleted, all its iterators
            are invalidated.
            */
            for (size_t i = 0; i < m_itarray->size(); ++i)
            {
                (*m_itarray)[i]->m_cont = 0;
            }
            m_itarray->resize(0);
        }

        inline void invalidate_iterators_gte(size_t pos)
        {
            /* invalidate container iterators at element's pos >= pos */
            // ms comp warn 4127
            int hasITDBG = 0;// (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (!hasITDBG)
            {
                return;
            }

            for (typename iterator_array::iterator beg = m_itarray->begin(); beg != m_itarray->end();)
            {
                iterator_base* iter = *beg;
                if (iter->m_pos >= pos)
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
		// $23.2.4.1 construct/copy/destroy:
		vector()
		{
            const Allocator& alloc = Allocator();
            init(alloc);
            mem_alloc(1);
            eos<T>(0);
		}

		explicit vector(size_type n, const T& value = T())
		{
            const Allocator& alloc = Allocator();
            init(alloc);
            mem_alloc(1);       // avoid 0 capacity with n=0
            eos<T>(0);          // safety
            assign(n, c);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
            const Allocator& alloc = Allocator();
            init(alloc);
            mem_alloc(1);       // avoid 0 capacity
            eos<T>(0);          // safety
            assign(first, last);
		}

		vector(const container& x)
		{
            init(x.get_allocator());
            mem_alloc(1);       // avoid 0 capacity with x.empty()
            eos<T>(0);          // protect against self assignment
            assign(x);        // may return with no action
		}

		~vector()
		{
            // ms comp warn 4127
            int hasPOD = 0; // (attributes & stl::GENERIC_ARRAY_HAS_POD_TYPE);
            if (hasPOD)
            {
                m_allocator.deallocate(m_data, 0);
            }
            else
            {
                stl::mem_destroy(&m_data, m_size, m_allocator);
                m_allocator.deallocate(m_data, 0);
            }

            m_data = 0;
            m_size = 0;
            m_capacity = 0;


            // ms comp warn 4127
            int hasITDBG = 0; // (attributes & stl::GENERIC_ARRAY_HAS_ITERATOR_DEBUGGING);
            if (hasITDBG)
            {
                invalidate_iterators();
                delete m_itarray;
            }
		}

		container& operator=(const container& x)
		{
            return assign(x);
		}

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
            return assign_impl(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
		}

		void assign(size_type n, const T& u)
		{
            invalidate_iterators();

            if (count > 0)
            {
                grow(count);

                stl::mem_set(m_data, val, count * numbytes);
            }

            eos<T>(count);

            // return *this;
		}

        //$21.3.2 iterators
		iterator begin()
		{
            return iterator(this, 0);
		}

		const_iterator begin() const
		{
            container* mutable_cont = const_cast<container*>(this);
            return const_iterator(mutable_cont, 0);
		}

		iterator end()
		{
            return iterator(this, m_size);
		}

		const_iterator end() const
		{
            container* mutable_cont = const_cast<container*>(this);
            return const_iterator(mutable_cont, m_size);
		}

		reverse_iterator rbegin()
		{
            return reverse_iterator(this, static_cast<size_type>(m_size - 1));
		}

		const_reverse_iterator rbegin() const
		{
            container* mutable_cont = const_cast<container*>(this);
            return const_reverse_iterator(mutable_cont, static_cast<size_type>(m_size - 1));
		}

		reverse_iterator rend()
		{
            return reverse_iterator(this, static_cast<size_type>(-1));
		}

		const_reverse_iterator rend() const
		{
            container* mutable_cont = const_cast<container*>(this);
            return const_reverse_iterator(mutable_cont, static_cast<size_type>(-1));
		}

		// 23.2.4.2 capacity:
		size_type size() const
		{
            return m_size;
		}

		size_type max_size() const
		{
            return static_cast<size_type>(-1) / sizeof(value_type);
		}

		void resize(size_type sz, value_type c = value_type())
		{
            if (m_size > sz)
            {
                invalidate_iterators_gte(sz > 0 ? sz - 1 : 0);

                eos<T>(sz);
            }
            else if (m_size < sz)
            {
                grow(sz);

                stl::mem_set(&m_data[m_size], c, (sz - m_size) * numbytes);

                eos<T>(sz);
            }
		}

		size_type capacity() const
		{
            return m_capacity;
		}

		bool empty() const
		{
            return m_size == 0;
		}

		void reserve(size_type n)
		{
            grow(n);
		}

		// element access:
		reference operator[](size_type n)
		{
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
		}

		const_reference operator[](size_type n) const
		{
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
		}

		const_reference at(size_type n) const
		{
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
		}

		reference at(size_type n)
		{
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
		}

        /* ISO/IEC 14882:2003  23.2.4 Class template vector */
        // 23.2.4.2 element access:
		reference front()
		{
            if (!m_size) throw stl::exception("out of valid range");
            return m_data[0];
		}

		const_reference front() const
		{
            if (!m_size) throw stl::exception("out of valid range");
            return m_data[0];
		}

		reference back()
		{
            if (!m_size) throw stl::exception("out of valid range");
            return m_data[m_size - 1];
		}

		const_reference back() const
		{
            if (!m_size) throw stl::exception("out of valid range");
            return m_data[m_size - 1];
		}

        /* $21.3.5 modifiers ( push_back ) */
		void push_back(const T& x)
		{
            if (m_size == m_capacity)
            {
                grow(m_capacity * 2);
            }

            // call copy constructor not copy operator
            new(&m_data[m_size])value_type(x);

            eos<T>(m_size + 1);
		}

        // 23.2.4.3 modifiers (vector):
		void pop_back()
		{
            if (m_size)
            {
                eos<T>(m_size - 1);
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
            if (this == first.m_cont)
            {
                replace_impl(p1, 0, first, last);
            }
            else
            {
                if (first.m_cont != last.m_cont || first.m_cont == 0)
                    throw stl::exception("invalid iterator");

                if (p1 > m_size) throw stl::exception("out of valid range");

                difference_type dist = last - first;
                if (dist > 0)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + dist;
                    grow(size);

                    memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);

                    eos<T>(size);
                }
            }
        }

        inline void insert_impl(size_type p1, const const_iterator& first, const const_iterator& last)
        {
            if (this == first.m_cont)
            {
                replace(p1, 0, first, last);
            }
            else
            {
                if (first.m_cont != last.m_cont || first.m_cont == 0)
                    throw stl::exception("invalid iterator");

                if (p1 > m_size) throw stl::exception("out of valid range");

                difference_type dist = last - first;
                if (dist > 0)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + dist;
                    grow(size);

                    memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);

                    eos<T>(size);
                }
            }
        }

        inline void insert_impl(size_type p1, const reverse_iterator& first, const reverse_iterator& last)
        {
            if (this == first.m_cont)
            {
                replace(p1, 0, first, last);
            }
            else
            {
                if (first.m_cont != last.m_cont || first.m_cont == 0)
                    throw stl::exception("invalid iterator");

                if (p1 > m_size) throw stl::exception("out of valid range");

                difference_type dist = last - first;
                if (dist > 0)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + dist;
                    grow(size);

                    memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                    swap_range(p1, p1 + dist);

                    eos<T>(size);
                }
            }
        }

        inline void insert_impl(size_type p1, const const_reverse_iterator& first, const const_reverse_iterator& last)
        {
            if (this == first.m_cont)
            {
                replace(p1, 0, first, last);
            }
            else
            {
                if (first.m_cont != last.m_cont || first.m_cont == 0)
                    throw stl::exception("invalid iterator");

                if (p1 > m_size) throw stl::exception("out of valid range");

                difference_type dist = last - first;
                if (dist > 0)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + dist;
                    grow(size);

                    memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                    swap_range(p1, p1 + dist);

                    eos<T>(size);
                }
            }
        }

        template<typename InputIterator>
        inline void insert_impl(size_type p1, const InputIterator& first, const InputIterator& last, stl::random_access_iterator_tag)
        {
            insert_impl(p1, first, last);
        }

        template<typename InputIterator>
        inline void insert_impl(size_type p1, InputIterator n2, InputIterator value, stl::input_iterator_tag)
        {
            if (n2)
            {
                // invalidate for effective insert only
                invalidate_iterators_gte(p1);

                size_type size = m_size + n2;

                grow(size);

                memmove_impl(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);

                stl::mem_set(&m_data[p1], value, n2 * numbytes);

                eos<T>(size);
            }
        }

    public:

		iterator insert(iterator position, const T& x)
		{
            insert(position, 1, x);
            return position;
		}

		void insert(iterator position, size_type n, const T& x)
		{
            if (this != position.m_cont) throw stl::exception("invalid iterator");
            if (position.m_pos > m_size) throw stl::exception("out of valid range");


            if (n)
            {
                size_type size = m_size + n;
                size_type p1 = position.m_pos;

                // invalidate for effective insert only
                invalidate_iterators_gte(p1);

                grow(size);

                memmove_impl(&m_data[p1 + n], &m_data[p1], (m_size - p1) * numbytes);

                stl::mem_set(&m_data[p1], x, n * numbytes);

                eos<T>(size);
            }
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
            if (position.m_cont != this)
                throw stl::exception("invalid iterator");

            insert_impl(position.m_pos, first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
		}

		iterator erase(iterator position)
		{
            if (position.m_cont != this) throw stl::exception("invalid iterator");
            if (position.m_pos >= m_size) throw stl::exception("out of valid range");

            size_type p1 = position.m_pos;

            invalidate_iterators_gte(p1);

            memmove_impl(&m_data[p1], &m_data[p1 + 1], (m_size - p1 - 1) * numbytes);

            eos<T>(m_size - 1);

            return position;
		}

		iterator erase(iterator first, iterator last)
		{
            if (first.m_cont != this || last.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
            {
                invalidate_iterators_gte(first.m_pos);

                //fill the gap
                if (last.m_pos < m_size)
                {
                    memmove_impl(&m_data[first.m_pos], &m_data[last.m_pos], (m_size - last.m_pos) * numbytes);
                }

                eos<T>(m_size - dist);
            }

            return first;
		}

		void swap(container& x)
		{
            stl::swap<Allocator>(m_allocator, vec.m_allocator);
            stl::swap<pointer>(m_data, vec.m_data);
            stl::swap<size_type>(m_size, vec.m_size);
            stl::swap<size_type>(m_capacity, vec.m_capacity);
            stl::swap<iterator_array*>(m_itarray, vec.m_itarray);
		}

		void clear()
		{
            invalidate_iterators();

            eos<T>(0);
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
