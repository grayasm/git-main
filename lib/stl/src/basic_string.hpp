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

#ifndef __basic_string_hpp__
#define __basic_string_hpp__


#include "iterator.hpp"
#include "exception.hpp"
#include "memory.hpp"
#include "memmanip.hpp"
#include "algorithm.hpp"


namespace stl
{
    template<typename container>
    struct basic_string_iterator_base
    {
        container*                      m_cont;
        typename container::size_type   m_pos;
    };

    template<typename T, typename Allocator> class basic_string;
    template<typename container> class basic_string_const_iterator;
    template<typename container> class basic_string_const_reverse_iterator;

    template<typename container>
    class basic_string_iterator :
        public stl::iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::basic_string_iterator_base<container>
    {
    public:
        // types
        typedef stl::iterator<stl::random_access_iterator_tag, typename container::value_type>    base;
        typedef typename base::iterator_category    iterator_category;
        typedef typename base::value_type           value_type;
        typedef typename base::difference_type      difference_type;
        typedef typename base::distance_type        distance_type;
        typedef typename base::pointer              pointer;
        typedef typename base::reference            reference;
        typedef typename container::size_type       size_type;
        typedef typename stl::basic_string_iterator_base<container> base2;
        friend class stl::basic_string<typename container::value_type, typename container::allocator_type>;
        friend class stl::basic_string_const_iterator<container>;


    private:
        basic_string_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        basic_string_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        basic_string_iterator(const basic_string_iterator& it)
        {
            *this = it;
        }

        ~basic_string_iterator()
        {
        }

        basic_string_iterator& operator=(const basic_string_iterator& it)
        {
            if (this != &it)
            {
                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;
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

        basic_string_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        basic_string_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        basic_string_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        basic_string_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        basic_string_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        basic_string_iterator operator+(difference_type off) const
        {
            basic_string_iterator<container> tmp = *this;
            return tmp += off;
        }

        basic_string_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        basic_string_iterator operator-(difference_type off) const
        {
            basic_string_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const basic_string_iterator& it) const
        {
            return static_cast<difference_type>(base2::m_pos - it.m_pos);
        }

        bool operator==(const basic_string_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const basic_string_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator>(const basic_string_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator<=(const basic_string_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        bool operator>=(const basic_string_iterator& it) const
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
    class basic_string_const_iterator :
        public stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::basic_string_iterator_base<container>
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
        typedef typename stl::basic_string_iterator_base<container> base2;
        friend class basic_string<typename container::value_type, typename container::allocator_type>;

    private:
        basic_string_const_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        basic_string_const_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        basic_string_const_iterator(const basic_string_const_iterator& it)
        {
            *this = it;
        }

        basic_string_const_iterator(const basic_string_iterator<container>& it)
        {
            *this = it;
        }

        ~basic_string_const_iterator()
        {
        }

        basic_string_const_iterator& operator=(const basic_string_const_iterator& it)
        {
            if (this != &it)
            {
                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;
            }
            return *this;
        }

        basic_string_const_iterator& operator=(const basic_string_iterator<container>& it)
        {
            base2::m_cont = it.m_cont;
            base2::m_pos = it.m_pos;

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

        basic_string_const_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        basic_string_const_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_const_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        basic_string_const_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        basic_string_const_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_const_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        basic_string_const_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        basic_string_const_iterator operator+(difference_type off) const
        {
            basic_string_const_iterator<container> tmp = *this;
            return tmp += off;
        }

        basic_string_const_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        basic_string_const_iterator operator-(difference_type off) const
        {
            basic_string_const_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const basic_string_const_iterator& it) const
        {
            return static_cast<difference_type>(base2::m_pos - it.m_pos);
        }

        bool operator==(const basic_string_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_const_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const basic_string_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator>(const basic_string_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator<=(const basic_string_const_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        bool operator>=(const basic_string_const_iterator& it) const
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
    class basic_string_reverse_iterator :
        public stl::iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::basic_string_iterator_base<container>
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
        typedef typename stl::basic_string_iterator_base<container> base2;
        friend class basic_string<typename container::value_type, typename container::allocator_type>;
        friend class basic_string_const_reverse_iterator<container>;


    private:
        basic_string_reverse_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        basic_string_reverse_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        basic_string_reverse_iterator(const basic_string_reverse_iterator& it)
        {
            *this = it;
        }

        ~basic_string_reverse_iterator()
        {
        }

        basic_string_reverse_iterator& operator=(const basic_string_reverse_iterator& it)
        {
            if (this != &it)
            {
                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;
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

        basic_string_reverse_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        basic_string_reverse_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_reverse_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        basic_string_reverse_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        basic_string_reverse_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_reverse_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        basic_string_reverse_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        basic_string_reverse_iterator operator+(difference_type off) const
        {
            basic_string_reverse_iterator<container> tmp = *this;
            return tmp += off;
        }

        basic_string_reverse_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        basic_string_reverse_iterator operator-(difference_type off) const
        {
            basic_string_reverse_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const basic_string_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - base2::m_pos);
        }

        bool operator==(const basic_string_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && it.m_pos == base2::m_pos);
        }

        bool operator!=(const basic_string_reverse_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const basic_string_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator>(const basic_string_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator<=(const basic_string_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        bool operator>=(const basic_string_reverse_iterator& it) const
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
    class basic_string_const_reverse_iterator :
        public stl::const_iterator<stl::random_access_iterator_tag, typename container::value_type>,
        public stl::basic_string_iterator_base<container>
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
        typedef typename stl::basic_string_iterator_base<container> base2;
        friend class basic_string<typename container::value_type, typename container::allocator_type>;


    private:
        basic_string_const_reverse_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        basic_string_const_reverse_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        basic_string_const_reverse_iterator(const basic_string_const_reverse_iterator& it)
        {
            *this = it;
        }

        ~basic_string_const_reverse_iterator()
        {
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_const_reverse_iterator& it)
        {
            if (this != &it)
            {
                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;
            }
            return *this;
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_reverse_iterator<container>& it)
        {
            base2::m_cont = it.m_cont;
            base2::m_pos = it.m_pos;

            return *this;
        }

        basic_string_const_reverse_iterator(const basic_string_reverse_iterator<container>& it)
        {
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

        basic_string_const_reverse_iterator& operator++()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            --base2::m_pos;
            return *this;
        }

        basic_string_const_reverse_iterator operator++(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_const_reverse_iterator<container> tmp = *this;
            --base2::m_pos;
            return tmp;
        }

        basic_string_const_reverse_iterator& operator--()
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            ++base2::m_pos;
            return *this;
        }

        basic_string_const_reverse_iterator operator--(int)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            basic_string_const_reverse_iterator<container> tmp = *this;
            ++base2::m_pos;
            return tmp;
        }

        basic_string_const_reverse_iterator& operator+=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos -= off;
            return *this;
        }

        basic_string_const_reverse_iterator operator+(difference_type off) const
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            return tmp += off;
        }

        basic_string_const_reverse_iterator& operator-=(difference_type off)
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            base2::m_pos += off;
            return *this;
        }

        basic_string_const_reverse_iterator operator-(difference_type off) const
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const basic_string_const_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - base2::m_pos);
        }

        bool operator==(const basic_string_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_const_reverse_iterator& it) const
        {
            return !(*this == it);
        }

        bool operator<(const basic_string_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos > it.m_pos);
        }

        bool operator>(const basic_string_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos < it.m_pos);
        }

        bool operator<=(const basic_string_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos >= it.m_pos);
        }

        bool operator>=(const basic_string_const_reverse_iterator& it) const
        {
            return (base2::m_cont == it.m_cont && base2::m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!base2::m_cont) throw stl::exception("invalid iterator");

            return (*base2::m_cont)[base2::m_pos - off];
        }
    };  // const_reverse_iterator


    //  ISO/IEC 14882:2003  $21.3 Class template basic_string
    template<typename T, typename Allocator = stl::allocator<T>>
    class basic_string
    {
    public:
        typedef typename basic_string<T, Allocator>     container;

        // types:
        typedef typename Allocator::value_type              value_type;
        typedef typename Allocator::size_type               size_type;
        typedef typename Allocator::difference_type         difference_type;
        typedef Allocator                                   allocator_type;

        typedef typename Allocator::reference               reference;
        typedef typename Allocator::const_reference         const_reference;
        typedef typename Allocator::pointer                 pointer;
        typedef typename Allocator::const_pointer           const_pointer;

    public:
        typedef typename basic_string_iterator<container>           iterator;
        typedef typename basic_string_const_iterator<container>     const_iterator;
        typedef typename basic_string_reverse_iterator<container>   reverse_iterator;
        typedef typename basic_string_const_reverse_iterator<container>  const_reverse_iterator;

    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;

    public:
        static const size_type npos = static_cast<size_type>(-1);


    private:
        inline void init()
        {
            m_data = 0;
            m_size = 0;
            m_capacity = 0;
            // m_allocator - default ctor;
        }

        inline void grow(size_type cap)
        {
            if (m_capacity >= cap) return;

            pointer mem = 0;
            if (!m_data)
                mem = m_allocator.allocate(cap);
            else
                stl::mem_realloc(&mem, cap, m_data, m_size, m_allocator);

            if (mem == 0)
                throw stl::exception("bad allocation");

            m_data = mem;
            m_capacity = cap;
        }

        inline void endof(size_type size)
        {
            if (size < m_size)
            {
                value_type* unused = m_data + size;
                size_type count = m_size - size;
                stl::mem_destroy(&unused, count, m_allocator);
            }
            m_size = size;
        }

    public:
        /*! $21.3.1 */
        basic_string()
        {
            init();
        }

        basic_string(const container& x)
        {
            init();
            assign(x);
        }

        basic_string(const container& str, size_type off, size_type count = npos)
        {
        }

        basic_string(const value_type* ptr, size_type count)
            : base(ptr, count)
        {
        }

        basic_string(const value_type* ptr)
            : base(ptr)
        {
        }


        basic_string(size_type n, value_type c)
            : base(n, c)
        {
        }


        template<class InputIterator>
        basic_string(InputIterator begin, InputIterator end)
            : base(begin, end)
        {
        }

        ~basic_string()
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
         *    MS Compiler issue fails to deduce template arguments for stl::string
         *    while calling global operators with 1 or 2 string operands (as below).
         *    
         *    std::less<stl::string> comp;
         *    stl::string s1("0"), s2("1");
         *    bool res = comp(s1, s2); <--- error
         *    
         *    Moving all global operators with left operand as stl::string, inside
         *    generic_string class.
         */

        //Concatenates two string objects.
        container operator+(const container& Right) const
        {
            stl::generic_string<T> res(*this);
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
 *    MS Compiler issue error while trying to deduce template argument for stl::string
 *    std::less<stl::string> comp;
 *    stl::string s1("0"), s2("1");
 *    bool res = comp(s1, s2); <--- error using global operators
 *    
 *    Moving all global operators with left operand as stl::string, inside
 *    generic_string class.
 */

//Concatenates two string objects.
template<typename T, typename Allocator, int attributes>
stl::generic_string<T, Allocator, attributes> operator+(
    const stl::generic_string<T, Allocator, attributes>& Left,
    const stl::generic_string<T, Allocator, attributes>& Right)
{
    stl::generic_string<T> res(Left);
    res += Right;
    return res;
}


template<typename T, typename Allocator, int attributes>
stl::generic_string<T, Allocator, attributes> operator+(
    const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    stl::generic_string<T> res(Left);
    res += Right;
    return res;
}

template<typename T, typename Allocator, int attributes>
stl::generic_string<T, Allocator, attributes> operator+(
    const stl::generic_string<T, Allocator, attributes>& Left, const T Right)
{
    stl::generic_string<T> res(Left);
    res += Right;
    return res;
}
#endif



template<typename T, typename Allocator, int attributes>
stl::generic_string<T, Allocator, attributes> operator+(
    const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    stl::generic_string<T> res(Left);
    res += Right;
    return res;
}

template<typename T, typename Allocator, int attributes>
stl::generic_string<T, Allocator, attributes> operator+(
    const T Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    stl::generic_string<T> res(1, Left);
    res += Right;
    return res;
}



#if 0

//Tests if the string object on the left side of the operator is not equal
//to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator!=(
                const stl::generic_string<T, Allocator, attributes>& Left, 
                const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) != 0;
}

template<typename T, typename Allocator, int attributes>
bool operator!=(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) != 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator!=(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) != 0;
}



#if 0
//Tests if the string object on the left side of the operator is equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator==(
                const stl::generic_string<T, Allocator, attributes>& Left, 
                const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) == 0;
}

template<typename T, typename Allocator, int attributes>
bool operator==(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) == 0;
}

#endif 



template<typename T, typename Allocator, int attributes>
bool operator==(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) == 0;
}


#if 0
//Tests if the string object on the left side of the operator is less than to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator<(
                const stl::generic_string<T, Allocator, attributes>& Left, 
                const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) < 0;
}

template<typename T, typename Allocator, int attributes>
bool operator<(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) < 0;
}

#endif



template<typename T, typename Allocator, int attributes>
bool operator<(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) > 0;
}


#if 0
//Tests if the string object on the left side of the operator is less than or equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator<=(
                const stl::generic_string<T, Allocator, attributes>& Left, 
                const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) <= 0;
}

template<typename T, typename Allocator, int attributes>
bool operator<=(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) <= 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator<=(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) >= 0;
}

//A template function that writes a string into the output stream.
template<typename T, typename Allocator, int attributes>
std::basic_ostream<T>& operator<<(
    std::basic_ostream<T>& Ostr, const stl::generic_string<T, Allocator, attributes>& str)
{
    Ostr << str.c_str();
    return Ostr;
}


#if 0
//Tests if the string object on the left side of the operator is greater
//than to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator>(
               const stl::generic_string<T, Allocator, attributes>& Left, 
               const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) > 0;
}

template<typename T, typename Allocator, int attributes>
bool operator>(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) > 0;
}

#endif


template<typename T, typename Allocator, int attributes>
bool operator>(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) < 0;
}


#if 0
//Tests if the string object on the left side of the operator is greater
//than or equal to the string object on the right side.
template<typename T, typename Allocator, int attributes>
bool operator>=(
                const stl::generic_string<T, Allocator, attributes>& Left, 
                const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Left.compare(Right) >= 0;
}

template<typename T, typename Allocator, int attributes>
bool operator>=(const stl::generic_string<T, Allocator, attributes>& Left, const T* Right)
{
    return Left.compare(Right) >= 0;
}
#endif



template<typename T, typename Allocator, int attributes>
bool operator>=(const T* Left, const stl::generic_string<T, Allocator, attributes>& Right)
{
    return Right.compare(Left) <= 0;
}

//A template function that reads a string from an input stream.
template<typename T, typename Allocator, int attributes>
std::basic_istream<T>& operator>>(
    std::basic_istream<T>& Istr, stl::generic_string<T, Allocator, attributes>& Right)
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
          stl::generic_string<T, Allocator, attributes>& Left, 
          stl::generic_string<T, Allocator, attributes>& Right)
{
    Left.swap(Right);
}

#endif//__basic_string_hpp__
