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
    };  // basic_string_iterator


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

        basic_string_const_iterator(const basic_string_const_iterator& tc)
        {
            *this = tc;
        }

        basic_string_const_iterator(const basic_string_iterator<container>& tc)
        {
            *this = tc;
        }

        ~basic_string_const_iterator()
        {
        }

        basic_string_const_iterator& operator=(const basic_string_const_iterator& tc)
        {
            if (this != &tc)
            {
                base2::m_cont = tc.m_cont;
                base2::m_pos = tc.m_pos;
            }
            return *this;
        }

        basic_string_const_iterator& operator=(const basic_string_iterator<container>& tc)
        {
            base2::m_cont = tc.m_cont;
            base2::m_pos = tc.m_pos;

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
    };  // basic_string_const_iterator


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

        basic_string_reverse_iterator(const basic_string_reverse_iterator& tc)
        {
            *this = tc;
        }

        ~basic_string_reverse_iterator()
        {
        }

        basic_string_reverse_iterator& operator=(const basic_string_reverse_iterator& tc)
        {
            if (this != &tc)
            {
                base2::m_cont = tc.m_cont;
                base2::m_pos = tc.m_pos;
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
    };  // basic_string_reverse_iterator


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

        basic_string_const_reverse_iterator(const basic_string_const_reverse_iterator& tc)
        {
            *this = tc;
        }

        ~basic_string_const_reverse_iterator()
        {
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_const_reverse_iterator& tc)
        {
            if (this != &tc)
            {
                base2::m_cont = tc.m_cont;
                base2::m_pos = tc.m_pos;
            }
            return *this;
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_reverse_iterator<container>& tc)
        {
            base2::m_cont = tc.m_cont;
            base2::m_pos = tc.m_pos;

            return *this;
        }

        basic_string_const_reverse_iterator(const basic_string_reverse_iterator<container>& tc)
        {
            *this = tc;
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
    };  // basic_string_const_reverse_iterator


    //  ISO/IEC 14882:2003  $21.3 Class template basic_string
    template<typename T, typename Allocator = stl::allocator<T>>
    class basic_string
    {
    public:
        typedef typename basic_string<T, Allocator>         container;

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

//TODO: if specialized for char,unsigned char,wchar_t then there is no need to
//      mem_destroy!!! -> then the whole endof(sz) can be replaced with
//      m_size = size;!! but requires also '\0' end termination
        inline void endof(size_type size)
        {
            if (size >= m_capacity)
                throw stl::exception("out of valid range");

            m_size = size;
            m_data[m_size] = 0;
        }

//TODO: specialize only for char*,unsigned char*,wchar_t ??
        inline size_type length(const value_type* ptr) const
        {
            if (ptr == 0)
                throw stl::exception("null pointer");

            const value_type* p = ptr;
            while (*p != 0)
                p++;
            return (p - ptr);
        }

//TODO: remove this in the next iteration!!
        inline void swap_range(size_type beg, size_type end)
        {
            if (beg < end)
            {
                for (size_type i = beg, j = end - 1; i < j; ++i, --j)
                {
                    misc::swap<value_type>(m_data[i], m_data[j]);
                }
            }
        }

    public:
        /*! $21.3.1 */
        basic_string()
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            endof(0);
        }

        basic_string(const container& tc)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(tc);
        }

        basic_string(const container& s, size_type off, size_type n = npos)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(s, off, n);
        }

        basic_string(const value_type* ptr, size_type n)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(ptr, n);
        }

        basic_string(const value_type* ptr)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(ptr);
        }


        basic_string(size_type n, value_type c)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(n, c);
        }


        template<class InputIterator>
        basic_string(InputIterator first, InputIterator last)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(first, last);
        }

        ~basic_string()
        {
            m_allocator.deallocate(m_data, 0); // always allocated

            m_data = 0;
            m_size = 0;
            m_capacity = 0;
        }

        /* $21.3.1 (assignment operators) */
        container& operator=(const container& str)
        {
            return assign(str);
        }

        container& operator=(const value_type* ptr)
        {
            return assign(ptr);
        }

        container& operator=(value_type c)
        {
            if (m_size + 1 == m_capacity)
                grow(m_capacity * 2);

            m_data[0] = c;

            endof(1);
            
            return *this;
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

        //$21.3.3 capacity
        size_type size() const
        {
            return m_size;
        }

        size_type length() const
        {
            return m_size;
        }

        size_type max_size() const
        {
            return static_cast<size_type>(-1) / sizeof(value_type);
        }

        void resize(size_type n, value_type c = value_type())
        {
            if (n > m_size)
            {
                grow(n + 1);    // extra '\0'

                // Not a self assignment as c is a temporary copy.
                stl::mem_set(&m_data[m_size], c, (n - m_size) * sizeof(value_type), m_allocator);
            }

            endof(n);
        }

        size_type capacity() const
        {
            return m_capacity;
        }

        void reserve(size_type n)
        {
            grow(n + 1);    // extra '\0'
        }

        void clear( )
        {
            endof(0);
        }

        bool empty () const
        {
            return m_size == 0;
        }

        //$21.3.4 element access:
        const_reference operator[] ( size_type n ) const
        {
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
        }

        reference operator[] ( size_type n )
        {
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
        }

        const_reference at ( size_type n ) const
        {
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
        }

        reference at ( size_type n )
        {
            if (n >= m_size) throw stl::exception("out of valid range");
            return m_data[n];
        }

        //$21.3.5 modifiers

        /* $21.3.5 modifiers ( operator += (...) ) */
        container& operator+=(const container& str)
        {
            return append(str);
        }

        container& operator+=(const value_type* ptr)
        {
            return append(ptr);
        }

        container& operator+=(value_type ch)
        {
            return append(1, ch);
        }

        /* $21.3.5 modifiers (append) */
        container& append(const container& str)
        {
            size_type n = str.length();    // without '\0'

            if (n > 0)
            {
                size_type size = m_size + n;

//TODO: actually test this relocation!!!
                // even if m_data is relocated, str remains valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], m_size, &str[0], n, m_allocator);

                endof(size);
            }

            return *this;
        }

        container& append(const container& str, size_type off, size_type n)
        {
            size_type len = str.length();    // without '\0'

            if (off >= len)
                throw stl::exception("out of valid range");

            if (n == npos)
                n = len - off;
            
            if (n > 0)
            {
                size_type size = m_size + n;

//TODO: actually test this relocation!!!
                // even if m_data is relocated, str remains valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], m_size, &str.m_data[off], n, m_allocator);

                endof(size);
            }

            return *this;
        }

        container& append(const value_type* ptr, size_type n2)
        {
            size_type n = length(ptr);    // without '\0'
            if (n > 0)
            {
                if (n2 > n)
                    throw stl::exception("out of valid range");

                size_type size = m_size + n2;

                // Is the range inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    container temp;
                    temp.assign(ptr, n2);

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, temp.m_data, n2, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, ptr, n2, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        container& append(const value_type* ptr)
        {
            size_type n = length(ptr);    // without '\0'
            if (n > 0)
            {
                size_type size = m_size + n;

                // Is the range inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    container temp;
//TODO: check that we avoid to call more than 1 time length(ptr)!!!!
                    temp.assign_(ptr, ptr + n);

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, temp.m_data, n, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, ptr, n, m_allocator);
                }

                endof(size);
            }

            return *this;
        }
        
        container& append(size_type n, value_type value)
        {
            if (n > 0)
            {
                size_type size = m_size + n;

                grow(size + 1);

                stl::mem_set(&m_data[m_size], value, n * sizeof(value_type), m_allocator);

                endof(size);
            }

            return *this;
        }

        template <typename InputIterator>
        container& append(InputIterator first, InputIterator last)
        {
            return append_(first, last);
        }

    private:
        //  You cannot trigger a const iterator& argument because the caller
        //  has a copy of the arguments and the caller itself is not const.
        inline container& append_(iterator& first, iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type size = m_size + dist;

                // even if m_data is reallocated, first and last remain valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], m_size, &((*first.m_cont)[first.m_pos]), dist, m_allocator);

                endof(size);
            }

            return *this;
        }

        //  You cannot trigger a const const_iterator& argument because the
        //  caller has a copy of the arguments and the caller itself is not const.
        inline container& append_(const_iterator& first, const_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type size = m_size + dist;

                // even if m_data is reallocated, first and last remain valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], m_size, &((*first.m_cont)[first.m_pos]), dist, m_allocator);

                endof(size);
            }

            return *this;
        }

        inline container& append_(value_type* first, value_type* last)
        {
            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                size_type size = m_size + dist;

                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, &temp[0], dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], m_size, first, dist, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        inline container& append_(const value_type* first, const value_type* last)
        {
            return append_(const_cast<value_type*>(first), const_cast<value_type*>(last));
        }

        template <typename InputIterator>
        container& append_(InputIterator& first, InputIterator& last)
        {
            return append_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        template<typename InputIterator>
        inline container& append_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        {
            // first type can be stl::reverse_iterator, char* or some other iterator
            // cannot check with: if(fist.m_cont != last.m_cont)

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(stl::distance(first, last));
            if (dist > 0)
            {
                size_type size = m_size + dist;

                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(size + 1); // extra '\0'

                    stl::mem_copy(&m_data[m_size], m_size, &temp[0], dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        m_allocator.construct(&m_data[m_size + i], *first);
                    }
                }

                endof(size);
            }

            return *this;
        }

        template<typename InputIterator>
        inline container& append_(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            if (n > 0)
            {
                size_type size = m_size + n;

                grow(size + 1);

                stl::mem_set(&m_data[m_size], value, n * sizeof(value_type), m_allocator);

                endof(size);
            }

            return *this;
        }

    public:
        /* $21.3.5 modifiers ( push_back ) */
        void push_back(const value_type& x)
        {
            // Is x address inside this container ?
            if (m_data <= &x && (m_data + m_size) > &x)
            {
                T temp(x);

                if (m_size + 1 == m_capacity)
                    grow(m_capacity * 2);

//TODO: remove construct, assign directly
//TODO: make sure nothing but char,unsigned char, wchar_t is allowed
                m_allocator.construct(&m_data[m_size], temp);
            }
            else// x address is outside this container.
            {
                if (m_size + 1 == m_capacity)
                    grow(m_capacity * 2);

                m_allocator.construct(&m_data[m_size], x);
            }

            endof(m_size + 1);
        }

        /* $21.3.5 modifiers ( assign ) */
        container& assign(const container& tc)
        {
            //self assignment
            if (this != &tc)
            {
                size_type size = tc.size(); // without '\0'

                if (size > 0)
                {
                    grow(size + 1); // extra '\0'

                    stl::mem_copy(m_data, m_size, tc.m_data, size, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        container& assign(const container& str, size_type off, size_type n)
        {
            if (n > 0)
            {
                // self assignment
                if (this == &str)
                {
                    if (off >= m_size)
                        throw stl::exception("out of valid range");

                    if (n == npos)
                        n = m_size - off;

                    stl::mem_move(m_data, m_size, &m_data[off], n, m_allocator);
                }
                else
                {
                    size_type len = str.length();   // without '\0'

                    if (off >= len)
                        throw stl::exception("out of valid range");

                    if (n == npos)
                        n = len - off;

                    grow(n + 1);    // extra '\0'

                    stl::mem_copy(m_data, m_size, &str.m_data[off], n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        container& assign(const value_type* ptr, size_type n)
        {
            if (n > 0)
            {
                // Is the address inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
//TODO: (1)test by assigning the entire string, + (2)try assigning + 1 extra '\0'!!
                    if (m_data + m_size < ptr + n)
                        throw stl::exception("out of valid range");

                    stl::mem_move(m_data, m_size, ptr, n, m_allocator);
                }
                else
                {
                    size_type len = length(ptr);   // without '\0'

                    if (n > len)
                        throw stl::exception("out of valid range");

                    grow(n + 1);    // extra '\0'

                    stl::mem_copy(m_data, m_size, ptr, n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        container& assign(const value_type* ptr)
        {
            size_type n = 0;
            
            // Is the address inside this container ?
            if (m_data <= ptr && (m_data + m_size) > ptr)
            {
                n = m_size - (ptr - m_data);
                if (n > 0)
                    stl::mem_move(m_data, m_size, ptr, n, m_allocator);
            }
            else
            {
                n = length(ptr);   // without '\0'

                if (n > 0)
                {
                    grow(n + 1);    // extra '\0'

                    stl::mem_copy(m_data, m_size, ptr, n, m_allocator);
                }                
            }

            endof(n);

            return *this;
        }

        container& assign(size_type n, const value_type& c)
        {
            if (n > 0)
            {
//TODO: test if indeed on grow(n + 1) &c becomes invalid

                // Is the address inside the container ?
                if (m_data <= &c && (m_data + m_size) > &c)
                {
                    T temp(c);

                    // can allocate m_data and invalidate &c
                    grow(n + 1);

                    stl::mem_set(m_data, temp, n * sizeof(value_type), m_allocator);
                }
                else// Address is outside this container
                {
                    grow(n + 1);

                    stl::mem_set(m_data, c, n * sizeof(value_type), m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        template <typename InputIterator>
        container& assign(InputIterator first, InputIterator last)
        {
            return assign_(first, last);
        }

    private:
        inline container& assign_(iterator& first, iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type n = static_cast<size_type>(last - first);

            if (n > 0)
            {
                grow(n + 1);    // extra '\0'

                //self assignment
                if (first.m_cont == this)
                {
                    stl::mem_move(m_data, m_size, &((*first.m_cont)[first.m_pos]), n, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, &((*first.m_cont)[first.m_pos]), n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        inline container& assign_(const_iterator& first, const_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if n < 0 then let it blow up.
            size_type n = static_cast<size_type>(last - first);

            if (n > 0)
            {
                grow(n + 1);    // extra '\0'

                //self assignment
                if (this == first.m_cont)
                {
                    stl::mem_move(m_data, m_size, &((*first.m_cont)[first.m_pos]), n, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, &((*first.m_cont)[first.m_pos]), n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }
        
        inline container& assign_(value_type* first, value_type* last)
        {
            // if last < first then let it blow up.
            size_type n = static_cast<size_type>(last - first);

            if (n > 0)
            {
                grow(n + 1); // extra '\0'

                // Is range inside this container ?
                if (m_data <= first && (m_data + m_size) > first)
                {
                    stl::mem_move(m_data, m_size, first, n, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, first, n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        inline container& assign_(const value_type* first, const value_type* last)
        {
            return assign_(const_cast<value_type*>(first), const_cast<value_type*>(last));
        }


        template <typename InputIterator>
        inline container& assign_(InputIterator& first, InputIterator& last)
        {
            return assign_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        template<typename InputIterator>
        inline container& assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        {
            /*  Test with a.assign(b.rbegin(), b.rend());
                if last < first then let it blow up.
            */
            size_type n = static_cast<size_type>(stl::distance(first, last));

            if (n > 0)
            {
                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(n + 1);

                    stl::mem_move(m_data, m_size, temp.m_data, n, m_allocator);
                }
                else// range is outside this container
                {
                    grow(n + 1);

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        T* d1 = m_data + i;
                        const T& s1 = *first;

//TODO: remove all m_allocator.construct(..) calls
//TODO: remove all m_allocator.destroy(..) calls

                        if (d1 != &s1)
                        {
                            // cannot destroy invalid objects in the destination
                            //if (i < m_size)
                            //{
                            //    m_allocator.destroy(d1);
                            //}

                            m_allocator.construct(d1, s1);
                        }
                    }
                }
            }

            endof(n);

            return *this;
        }


        template<typename InputIterator>
        inline container& assign_(InputIterator count, InputIterator value, stl::input_iterator_tag)
        {
            /*  Ex: a.assign(5, 'c');
                if n < 0 then let it blow up.
            */
            size_type n = static_cast<size_type>(count);
            if (n > 0)
            {
                grow(n + 1);    // extra '\0'

                // Not a self assignment as value is a temporary copy.
                stl::mem_set(m_data, value, n * sizeof(value_type), m_allocator);
            }

            endof(n);

            return *this;
        }

    public:
        container& insert(size_type pos, const container& str)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            size_type len = str.length();
           
            if (len)
            {
                size_type size = m_size + len;

                /*  Insert self content:
                    A buffer is not required. When making room for the new
                    content, a portion of m_data is moved beyond
                    m_data+m_size which means the source m_data remains
                    valid.
                */
                grow(size + 1);

                // move content unless insert position is end()
                if (pos < m_size)
                {
                    // size_type dst_valid_sz = (pos + len < m_size ? (m_size - pos - len) : 0);
                    stl::mem_move(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);
                }

                if (this == &str) // insert self content
                {
//TODO: add dst_valid_sz where required!
                    // size_type dst_valid_sz = m_size - pos;
                    stl::mem_move(&m_data[pos], 0, m_data, len, m_allocator);
                }
                else // insert other's content
                {
                    stl::mem_copy(&m_data[pos], 0, str.m_data, len, m_allocator);
                }

                endof(size);
            }
            
            return *this;
        }

        container& insert(size_type pos, const container& str, size_type off, size_type n)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (n)
            {
                size_type len = str.length();

                if (off >= len)
                    throw stl::exception("out of valid range");

                if (n == npos)
                    n = len - off;

                size_type size = m_size + n;

                if (this == &str)
                {
                    container temp(&m_data[off], &m_data[off] + n);

                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, n, m_allocator);
                }
                else
                {
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_copy(&m_data[pos], 0, &str.m_data[off], n, m_allocator);
                }

                endof(size);
            }
            
            return *this;
        }

        container& insert(size_type pos, const value_type* ptr)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            size_type len = length(ptr);

            if (len)
            {
                size_type size = m_size + len;

                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    container temp(ptr, static_cast<const value_type*>(m_data + m_size));

                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, len, m_allocator);
                }
                else
                {
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_copy(&m_data[pos], 0, ptr, len, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        container& insert(size_type pos, const value_type* ptr, size_type n)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (n)
            {
                size_type len = length(ptr);

                if (n > len)
                    throw stl::exception("out of valid range");

                size_type size = m_size + n;

                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    container temp(ptr, ptr + n);

                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_move(&m_data[pos], 0, temp.m_data, n, m_allocator);
                }
                else
                {
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (pos < m_size)
                    {
                        stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                    }
                    stl::mem_copy(&m_data[pos], 0, ptr, n, m_allocator);
                }

                endof(size);
            }            

            return *this;
        }
        
        container& insert(size_type pos, size_type n, value_type c)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (n)
            {
                size_type size = m_size + n;

                grow(size + 1);

                // move content unless insert position is end()
                if (pos < m_size)
                {
                    stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                }

                stl::mem_set(&m_data[pos], c, n * sizeof(value_type), m_allocator);

                endof(size);
            }

            return *this;
        }

        void insert(iterator position, size_type n, value_type c)
        {
            if (this != position.m_cont || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (n)
            {
                size_type pos = position.m_pos;
                size_type size = m_size + n;

                grow(size + 1);

                // move content unless insert position is end()
                if (pos < m_size)
                {
                    stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                }

                stl::mem_set(&m_data[pos], c, n * sizeof(value_type), m_allocator);

                endof(size);
            }
        }

        iterator insert(iterator position, value_type c)
        {
            if (this != position.m_cont || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            size_type pos = position.m_pos;
            size_type size = m_size + 1;

            grow(size + 1);

            // move content unless insert position is end()
            if (pos < m_size)
            {
                stl::mem_move(&m_data[pos + 1], 0, &m_data[pos], (m_size - pos), m_allocator);
            }

            stl::mem_set(&m_data[pos], c, 1 * sizeof(value_type), m_allocator);

            endof(size);

            return position;
        }
    
        template <typename InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            insert_(position, first, last);
        }


    private:
        inline void insert_(iterator& position, iterator& first, iterator& last)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type p = position.m_pos;
                size_type size = m_size + dist;

                grow(size + 1);

                // Is the range inside this container ?
                if (first.m_cont == this)
                {
//TODO: can be optimized by passing pointers (e.g. first.m_cont + first.m_pos,..)
                    container temp;
                    temp.assign(first, last);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }
                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    // move content unless insert positions is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }
                    stl::mem_copy(&m_data[p], 0, &((*first.m_cont)[first.m_pos]), dist, m_allocator);
                }

                endof(size);
            }
        }

        inline void insert_(iterator& position, const_iterator& first, const_iterator& last)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type p = position.m_pos;
                size_type size = m_size + dist;

                grow(size + 1);

                // Is the range inside this container ?
                if (first.m_cont == this)
                {
                    container temp;
                    temp.assign(first, last);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }
                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    // move content unless insert positions is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }

                    stl::mem_copy(&m_data[p], 0, &((*first.m_cont)[first.m_pos]), dist, m_allocator);
                }

                endof(size);
            }
        }

        inline void insert_(iterator& position, value_type* first, value_type* last)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                size_type p = position.m_pos;
                size_type size = m_size + dist;

                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // can relocate m_data and invalidate first,last pointers
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }
                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }

                    stl::mem_copy(&m_data[p], 0, first, dist, m_allocator);
                }

                endof(size);
            }
        }

        inline void insert_(iterator& position, const value_type* first, const value_type* last)
        {
            insert_(position, const_cast<value_type*>(first), const_cast<value_type*>(last));
        }

        template<typename InputIterator>
        inline void insert_(iterator& position, InputIterator& first, InputIterator& last)
        {
            insert_(position, first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        template<typename InputIterator>
        inline void insert_(iterator& position, InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            // first type can be stl::reverse_iterator, int* or some other iterator
            // cannot check with: if(fist.m_cont != last.m_cont)

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(stl::distance(first, last));
            if (dist > 0)
            {
                size_type p = position.m_pos;
                size_type size = m_size + dist;

                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }
                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);
                    }

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        // m_allocator.construct(&m_data[p + i], *first);
                        m_data[p + i] = *first;
                    }
                }

                endof(size);
            }
        }

        template<typename InputIterator>
        inline void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            if (this != position.m_cont || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (n)
            {
                size_type pos = position.m_pos;
                size_type size = m_size + n;

                grow(size + 1);

                // move content unless insert position is end()
                if (pos < m_size)
                {
                    stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);
                }

                stl::mem_set(&m_data[pos], value, n * sizeof(value_type), m_allocator);

                endof(size);
            }
        }


    public:
        /*  pos: Position of the first character to be erased.
                 If this is greater than the string length, it throws
                 out_of_range. The first character in str is denoted by
                 a value of 0 (not 1).

            len: Number of characters to erase (if the string is shorter,
                 as many characters as possible are erased).
                 A value of string::npos indicates all characters until
                 the end of the string.
        */
        container& erase(size_type pos = 0, size_type len = npos)
        {
            // cannot remove end() position
            if (pos >= m_size)
                throw stl::exception("invalid iterator");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type pend = pos + len;

            if (pend < m_size)
            {
                stl::mem_move(&m_data[pos], 0, &m_data[pend], (m_size - pend), m_allocator);
            }

            endof(m_size - len);

            return *this;
        }

        // position: Iterator to the character to be removed.
        iterator erase(iterator position)
        {
            // cannot remove end() position
            if (position.m_cont != this || position.m_pos >= m_size)
                throw stl::exception("invalid iterator");

            size_type pos = position.m_pos;

            stl::mem_move(&m_data[pos], 0, &m_data[pos + 1], (m_size - pos - 1), m_allocator);

            endof(m_size - 1);

            return position;
        }

        /*  first, last:
                Iterators specifying a range within the string] to be removed
                [first,last). i.e., the range includes all the characters
                between first and last, including the character pointed
                by first but not the one pointed by last.
        */
        iterator erase(iterator first, iterator last)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type count = m_size - last.m_pos;
                if (count)
                {
                    stl::mem_move(&m_data[first.m_pos], 0, &m_data[last.m_pos], count, m_allocator);
                }

                endof(m_size - dist);
            }

            return first;
        }

        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.

            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until
                 the end of the string.

            str: Another string object, whose value is copied.
        */
        container& replace(size_type pos, size_type len, const container& str)
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type slen = str.length();
            size_type size = m_size - len + slen;
            
            grow(size + 1);

            if (this == &str) // insert self content
            {
                container temp(str);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, str.m_data, slen, m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  first, last:
                Replaces the part of the string in the range
                between [first,last) by new contents.
        */
        inline container& replace(iterator first, iterator last, const container& str)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = str.length();
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (this == &str) // insert self content
            {
                container temp(str);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, str.m_data, slen, m_allocator);
            }

            endof(size);

            return *this;
        }


        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.
            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until
                 the end of the string.
            str: Another string object, whose value is copied.
         subpos: Position of the first character in str that is copied to the
                 object as replacement. If this is greater than str's length,
                 it throws out_of_range.
         sublen: Length of the substring to be copied (if the string is
                 shorter, as many characters as possible are copied).
                 A value of string::npos indicates all characters until
                 the end of str.
        */
        container& replace(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen)
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type slen = str.length();

            if (subpos >= slen)
                throw stl::exception("out of valid range");

            if (sublen > slen - subpos)
                sublen = slen - subpos;

            size_type size = m_size - len + sublen;

            grow(size + 1);

            if (this == &str) // insert self content
            {
                container temp(str, subpos, sublen);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, str.m_data, slen, m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.
            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until the
                 end of the string.
            ptr: Pointer to an array of characters (such as a c-string).
        */
        container& replace(size_type pos, size_type len, const char* ptr)
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type slen = length(ptr);
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (m_data <= ptr && (m_data + m_size > ptr)) // insert self content
            {
                container temp(ptr);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, ptr, slen, m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  first,last:
                 Replaces the part of the string in the range
                 between [first,last) by new contents.
            ptr: Pointer to an array of characters (such as a c-string).
        */
        container& replace(iterator first, iterator last, const value_type* ptr)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = length(ptr);
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (m_data <= ptr && (m_data + m_size) > ptr) // insert self content
            {
                container temp(ptr);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, ptr, slen, m_allocator);
            }

            endof(size);

            return *this;
        }


        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.
            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until
                 the end of the string.
            ptr: Pointer to an array of characters (such as a c-string).
              n: Number of characters to copy.
        */
        container& replace(size_type pos, size_type len, const value_type* ptr, size_type n)
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type slen = length(ptr);

            //  treat n as sublen from one of the previous methods
            size_type sublen = n;
            if (sublen > slen)
                sublen = slen;

            size_type size = m_size - len + sublen;

            grow(size + 1);

            if (m_data <= ptr && (m_data + m_size > ptr)) // insert self content
            {
                container temp(ptr);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, ptr, sublen, m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  first,last:
                 Replaces the part of the string in the range
                 between [first,last) by new contents.
            ptr: Pointer to an array of characters (such as a c-string).
              n: Number of characters to copy.
        */
        container& replace(iterator first, iterator last, const value_type* ptr, size_type n)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");
            
            size_type slen = length(ptr);

            //  treat n as sublen from one of the previous methods
            size_type sublen = n;
            if (sublen > slen)
                sublen = slen;

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type size = m_size - len + sublen;

            grow(size + 1);

            if (m_data <= ptr && (m_data + m_size) > ptr) // insert self content
            {
                container temp(ptr);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
//TODO: test with sublen == 0 and if tested ok, then add if (sublen) here...
                stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], tail, m_allocator);
                }
                stl::mem_copy(&m_data[pos], 0, ptr, sublen, m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.
            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until
                 the end of the string.
              n: Number of characters to copy.
              c: Character value, repeated n times.
        */
        container& replace(size_type pos, size_type len, size_type n, value_type c)
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type size = m_size - len + n;

            grow(size + 1);

            size_type tail = m_size - pos - len;
            if (tail)
            {
                stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], tail, m_allocator);
            }

            if (n)
            {
                stl::mem_set(&m_data[pos], c, n * sizeof(value_type), m_allocator);
            }

            endof(size);

            return *this;
        }

        /*  first,last:
                 Replaces the part of the string in the range
                 between [first,last) by new contents.
              n: Number of characters to copy.
              c: Character value, repeated n times.
        */
        container& replace(iterator first, iterator last, size_type n, value_type c)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type size = m_size - len + n;

            grow(size + 1);
            
            size_type tail = m_size - pos - len;
            if (tail)
            {
                stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], tail, m_allocator);
            }

            if (n)
            {
                stl::mem_set(&m_data[pos], c, n * sizeof(value_type), m_allocator);
            }

            endof(size);

            return *this;
        }

        //template <class InputIterator>
        //string& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

        /*  first,last:
                 Replaces the part of the string in the range
                 between [first,last) by new contents.
            first2,last2:
                 Input iterators to the initial and final positions in a range.
                 The range used is [first2,last2), which includes all
                 the characters between first and last, including the character
                 pointed by first but not the character pointed by last.
                 The function template argument InputIterator shall be
                 an input iterator type that points to elements of a type
                 convertible to char.
        */
        template<typename InputIterator>
        container& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
        {
            return replace_(first, last, first2, last2);
        }


    private:
        inline container& replace_(iterator& first, iterator& last, iterator& first2, iterator& last2)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            if (first2.m_cont != last2.m_cont)
                throw stl::exception("invalid iterator");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = static_cast<size_type>(last2.m_pos - first2.m_pos);
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (first.m_cont == first2.m_cont) // insert self content
            {
                container temp(first2, last2);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
                }
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, &*first2, slen, m_allocator);
                }
            }

            endof(size);

            return *this;
        }

        inline container& replace_(iterator& first, iterator& last, const_iterator& first2, const_iterator& last2)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            if (first2.m_cont != last2.m_cont)
                throw stl::exception("invalid iterator");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = static_cast<size_type>(last2.m_pos - first2.m_pos);
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (first.m_cont == first2.m_cont) // insert self content
            {
                container temp(first2, last2);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
                }
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, &*first2, slen, m_allocator);
                }
            }

            endof(size);

            return *this;
        }

        inline container& replace_(iterator& first, iterator& last, value_type* first2, value_type* last2)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = static_cast<size_type>(last2 - first2);
            size_type size = m_size - len + slen;

            grow(size + 1);

            if (m_data <= first2 && (m_data + m_size) > first2) // insert self content
            {
                container temp(first2, last2);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
                }
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, first2, slen, m_allocator);
                }
            }

            endof(size);

            return *this;
        }

        inline container& replace_(iterator& first, iterator& last, const value_type* first2, const value_type* last2)
        {
            return replace_(first, last, const_cast<value_type*>(first2), const_cast<value_type*>(last2));
        }

        template<typename InputIterator>
        inline container& replace_(iterator& first, iterator& last, InputIterator& first2, InputIterator& last2)
        {
            return replace_(first, last, first2, last2, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        template<typename InputIterator>
        inline container& replace_(iterator& first, iterator& last, InputIterator& first2, InputIterator& last2, stl::forward_iterator_tag)
        {
            // test with a reverse iterator
            // s.replace(s.begin(), s.begin() + 2, str.rbegin(), str.rend());
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type slen = static_cast<size_type>(stl::distance(first2, last2));
            size_type size = m_size - len + slen;

            grow(size + 1);

            const T& check = *first2;

            if (m_data <= &check && (m_data + m_size) > &check) // insert self content
            {
                container temp(first2, last2);

                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                if (slen)
                {
                    stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
                }
            }
            else // insert from another container
            {
                size_type tail = m_size - pos - len;
                if (tail)
                {
                    stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], tail, m_allocator);
                }
                // string.reverse_iterator, list.iterator, etc.
                for (size_t i = 0; first2 != last2; ++first2, ++i)
                {
                    m_data[pos + i] = *first2;
                }
            }

            endof(size);

            return *this;
        }

        template<typename InputIterator>
        inline container& replace_(iterator& first, iterator& last, InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            if (first.m_pos > last.m_pos || last.m_pos > m_size)
                throw stl::exception("out of valid range");

            size_type pos = first.m_pos;
            size_type len = static_cast<size_type>(last.m_pos - first.m_pos);
            size_type size = m_size - len + n;

            grow(size + 1);

            size_type tail = m_size - pos - len;
            if (tail)
            {
                stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], tail, m_allocator);
            }

            if (n)
            {
                stl::mem_set(&m_data[pos], value, n * sizeof(value_type), m_allocator);
            }

            endof(size);

            return *this;
        }

    public:

        /*  Copy a substring of this object to ptr.
            ptr: Pointer to an array of characters. The array shall contain
                 enough storage for the copied characters.
            len: Number of characters to copy (if the string is shorter,
                 as many characters as possible are copied).
            pos: Position of the first character to be copied. If this is
                 greater than the string length, it throws out_of_range.
                 Note: The first character in the string is denoted
                 by a value of 0 (not 1).
            ret: The number of characters copied to the array pointed by ptr.
        */
        size_type copy(value_type* ptr, size_type len, size_type pos = 0) const
        {
            if (pos >= m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            if (m_data <= ptr && (m_data + m_size) > ptr)   // copy to self
            {
                stl::mem_move(ptr, 0, &m_data[pos], len, m_allocator);
            }
            else // destination is outside the range of this string
            {
                stl::mem_copy(ptr, 0, &m_data[pos], len, m_allocator);
            }
            return len;
        }

        void swap(container& str)
        {
            stl::swap(m_data, str.m_data);
            stl::swap(m_size, str.m_size);
            stl::swap(m_capacity, str.m_capacity);
            stl::swap(m_allocator, str.m_allocator);
        }

//TODO: use template specialization to disable anything but char,unsigned char,wchar_t
//      actually all that implements ::memcpy, ::memmove
//      because it is clear that c_str() would not work with anything that does
//      not end in '\0', right?

        const value_type* c_str() const
        {
            return m_data;
        }

        const value_type* data() const
        {
            return m_data;
        }


        allocator_type get_allocator() const
        {
            return m_allocator;
        }

        /* $21.3.6 string operations (find) */
        size_type find(const container& str, size_type p1 = 0) const
        {
            return find(str.m_data, p1, str.length());
        }

        size_type find(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 >= m_size) throw stl::exception("out of valid range");

            size_type ptrLen = length<value_type>(ptr);

            if (n2 > ptrLen) return npos;

            if (n2)
            {
                //find
                for (size_type i = p1; i + n2 <= m_size; ++i)
                {
                    size_type i2 = i;
                    size_type j2 = 0;
                    while (j2 < n2 && m_data[i2++] == ptr[j2++])
                        ;
                    if (j2 == n2)
                        return i;
                }
            }

            return npos;
        }

        size_type find(const value_type* ptr, size_type p1 = 0) const
        {
            return find(ptr, p1, length<value_type>(ptr));
        }

        size_type find(value_type ch, size_type p1 = 0) const
        {
            for (size_type i = p1; i < m_size; ++i)
            {
                if (m_data[i] == ch)
                    return i;
            }

            return npos;
        }


        /* $21.3.6 string operations (rfind) */
        size_type rfind(const container& str, size_type p1 = npos) const
        {
            return rfind(str.m_data, p1, str.length());
        }

        size_type rfind(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 > m_size) p1 = m_size;
            if (n2 > m_size) return npos;
            if (p1 + n2 > m_size)
                p1 = m_size - n2;
            size_type ptrsz = length<value_type>(ptr);
            if (n2 > ptrsz) return npos;

            if (n2)
            {
                //rfind
                for (size_type i = p1; i != npos; --i)
                {
                    size_type i2 = i;
                    size_type j2 = 0;
                    while (j2 < n2 && m_data[i2++] == ptr[j2++])
                        ;

                    if (j2 == n2)
                        return i;
                }
            }

            return npos;
        }

        size_type rfind(const value_type* ptr, size_type p1 = npos) const
        {
            return rfind(ptr, p1, length<value_type>(ptr));
        }

        size_type rfind(value_type ch, size_type p1 = npos) const
        {
            p1 = stl::min<size_type>(p1, m_size - 1);

            //rfind
            for (size_type i = p1; i != npos; --i)
            {
                if (m_data[i] == ch)
                    return i;
            }

            return npos;
        }


        /* $21.3.6 string operations (find_first_of) */
        size_type find_first_of(const container& str, size_type pos = 0) const
        {
            return find_first_of(str.m_data, pos, str.length());
        }

        size_type find_first_of(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");
            size_type ptrsz = length<value_type>(ptr);
            if (n2 > ptrsz)
                n2 = ptrsz;

            if (n2)
            {
                //find
                for (size_type i = p1; i < m_size; ++i)
                {
                    for (size_type j = 0; j < n2; ++j)
                    {
                        if (m_data[i] == ptr[j])
                            return i;
                    }
                }
            }

            return npos;
        }

        size_type find_first_of(const value_type* ptr, size_type p1 = 0) const
        {
            return find_first_of(ptr, p1, length<value_type>(ptr));
        }

        size_type find_first_of(value_type c, size_type p1 = 0) const
        {
            //find
            for (size_type i = p1; i < m_size; ++i)
            {
                if (m_data[i] == c)
                    return i;
            }

            return npos;
        }

        /* $21.3.6 string operations (find_last_of) */
        size_type find_last_of(const container& str, size_type p1 = npos) const
        {
            return find_last_of(str.c_str(), p1, str.length());
        }

        size_type find_last_of(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 >= m_size) p1 = m_size - 1;
            size_type ptrsz = length<value_type>(ptr);
            if (n2 > ptrsz)
                n2 = ptrsz;

            if (n2)
            {
                //find
                for (size_type i = p1; i != npos; --i)
                {
                    for (size_type j = 0; j < n2; ++j)
                    {
                        if (m_data[i] == ptr[j])
                            return i;
                    }
                }
            }

            return npos;
        }

        size_type find_last_of(const value_type* ptr, size_type p1 = npos) const
        {
            return find_last_of(ptr, p1, length<value_type>(ptr));
        }

        size_type find_last_of(value_type ch, size_type p1 = npos) const
        {
            if (p1 >= m_size) p1 = m_size - 1;

            //find
            for (size_type i = p1; i != npos; --i)
            {
                if (m_data[i] == ch)
                    return i;
            }

            return npos;
        }

       /* $21.3.6 string operations (find_first_not_of) */
        size_type find_first_not_of(const container& str, size_type p1 = 0) const
        {
            return find_first_not_of(str.m_data, p1, str.length());
        }

        size_type find_first_not_of(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");
            size_type ptrLen = length<value_type>(ptr);
            if (n2 > ptrLen)
                n2 = ptrLen;

            if (n2)
            {
                //find
                for (size_type i = p1; i < m_size; ++i)
                {
                    bool found = false;
                    for (size_type j = 0; j < n2; ++j)
                    {
                        if (m_data[i] == ptr[j])
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                        return i; //m_data[i] is not in ptr
                }
            }

            return npos;
        }

        size_type find_first_not_of(const value_type* ptr, size_type n1 = 0) const
        {
            return find_first_not_of(ptr, n1, length<value_type>(ptr));
        }

        size_type find_first_not_of(value_type ch, size_type p1 = 0) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");

            //find
            for (size_type i = p1; i < m_size; ++i)
            {
                if (m_data[i] != ch)
                    return i;
            }

            return npos;
        }


        /* $21.3.6 string operations (find_last_not_of) */
        size_type find_last_not_of(const container& str, size_type p1 = npos) const
        {
            return find_last_not_of(str.m_data, p1, str.length());
        }

        size_type find_last_not_of(const value_type* ptr, size_type p1, size_type n2) const
        {
            if (p1 >= m_size)
                p1 = m_size - 1;

            size_type ptrLen = length<value_type>(ptr);
            if (n2 > ptrLen)
                n2 = ptrLen;

            if (n2)
            {
                //find
                for (size_type i = p1; i != npos; --i)
                {
                    bool found = false;
                    for (size_type j = 0; j < n2; ++j)
                    {
                        if (m_data[i] == ptr[j])
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                        return i; // m_data[i] is not in ptr
                }
            }

            return npos;
        }

        size_type find_last_not_of(const value_type* ptr, size_type p1 = npos) const
        {
            return find_last_not_of(ptr, p1, length<value_type>(ptr));
        }

        size_type find_last_not_of(value_type ch, size_type p1 = npos) const
        {
            if (p1 >= m_size) p1 = m_size - 1;
            //find
            for (size_type i = p1; i != npos; --i)
            {
                if (m_data[i] != ch)
                    return i;
            }

            return npos;
        }


        /* $21.3.6 string operations (substr) */
        container substr(size_type p1 = 0, size_type n1 = npos) const
        {
            if (p1 > m_size) throw stl::exception("ouf of valid range");
            if (n1 > m_size - p1)
                n1 = m_size - p1;

            return container(&m_data[p1], n1);
        }


        /* $21.3.6 string operations (compare) */
        int compare(const container& str) const
        {
            size_type rsz = str.size();
            size_type minsz = stl::min<size_type>(m_size, rsz);
            size_type i = 0;
            while (i < minsz && m_data[i] == str.m_data[i])
            {
                ++i;
            }

            if (i < minsz)
            {
                value_type c1 = m_data[i];
                value_type c2 = str.m_data[i];
                return ((c1 < c2) ? -1 : (c1 > c2));
            }
            else
            {
                return ((m_size < rsz) ? -1 : (m_size > rsz));
            }
        }

        int compare(size_type p1, size_type n1, const container& str) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");
            size_type lsz = m_size - p1;
            size_type rsz = str.size();
            size_type minsz = stl::min<size_type>(lsz, rsz, n1);

            size_type i = 0;
            while (i < minsz && m_data[p1] == str.m_data[i])
            {
                ++p1;
                ++i;
            }

            if (i == n1)
                return 0;

            if (i == minsz)
            {
                return ((lsz < rsz) ? -1 : lsz > rsz);
            }

            value_type c1 = m_data[p1];
            value_type c2 = str.m_data[i];
            return ((c1 < c2) ? -1 : (c1 > c2));
        }

        int compare(size_type p1, size_type n1, const container& str, size_type p2, size_type n2) const
        {
            if (p1 > m_size || p2 > str.m_size) throw stl::exception("out of valid range");
            size_type lsz = m_size - p1;
            size_type rsz = str.m_size - p2;
            size_type minsz = stl::min<size_type>(lsz, rsz, n1, n2);

            size_type i = 0;
            while (i < minsz && m_data[p1] == str.m_data[p2])
            {
                ++p1;
                ++p2;
                ++i;
            }

            if (i < minsz)
            {
                value_type c1 = m_data[p1];
                value_type c2 = str.m_data[p2];
                return ((c1 < c2) ? -1 : (c1 > c2));
            }

            if (n1 == n2 && n1 <= lsz && n1 <= rsz && i == n1)
                return 0;

            return ((lsz < rsz) ? -1 : lsz > rsz);
        }

        int compare(const value_type* ptr) const
        {
            size_type size = length<value_type>(ptr);
            size_type minsz = stl::min<size_type>(m_size, size);
            size_type i = 0;
            while (i < minsz && m_data[i] == ptr[i])
            {
                ++i;
            }

            if (i < minsz)
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

        int compare(size_type p1, size_type n1, const value_type* ptr) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");

            size_type lsz = m_size - p1;
            size_type rsz = length<value_type>(ptr);
            size_type minsz = stl::min<size_type>(lsz, rsz, n1);

            size_type i = 0;
            while (i < minsz && m_data[p1] == ptr[i])
            {
                ++p1;
                ++i;
            }

            if (i == n1)
                return 0;

            if (i == minsz)
            {
                return ((lsz < rsz) ? -1 : lsz > rsz);
            }

            value_type c1 = m_data[p1];
            value_type c2 = ptr[i];
            return ((c1 < c2) ? -1 : (c1 > c2));
        }

        int compare(size_type p1, size_type n1, const value_type* ptr, size_type n2) const
        {
            if (p1 > m_size) throw stl::exception("out of valid range");
            size_type lsz = m_size - p1;
            size_type rsz = length<value_type>(ptr);
            size_type minsz = stl::min<size_type>(lsz, rsz, n1, n2);

            size_type i = 0;
            while (i < minsz && m_data[p1] == ptr[i])
            {
                ++p1;
                ++i;
            }

            if (i < minsz)
            {
                value_type c1 = m_data[p1];
                value_type c2 = ptr[i];
                return ((c1 < c2) ? -1 : (c1 > c2));
            }

            if (n1 == n2 && n1 <= lsz && n1 <= rsz && i == n1)
                return 0;

            return ((lsz < rsz) ? -1 : lsz > rsz);
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
         *    basic_string class.
         */

        ////Concatenates two string objects.
        //container operator+(const container& Right) const
        //{
        //    stl::basic_string<T> res(*this);
        //    res += Right;
        //    return res;
        //}
        //
        //container operator+(const T* Right) const
        //{
        //    container res(*this);
        //    res += Right;
        //    return res;
        //}
        //
        //container operator+(const T Right) const
        //{
        //    container res(*this);
        //    res += Right;
        //    return res;
        //}

        //bool operator!=(const container& Right) const
        //{
        //    return compare(Right) != 0;
        //}
        //
        //bool operator!=(const T* Right) const
        //{
        //    return compare(Right) != 0;
        //}

        //bool operator==(const container& Right) const
        //{
        //    return compare(Right) == 0;
        //}

        //bool operator==(const T* Right) const
        //{
        //    return compare(Right) == 0;
        //}
        //
        //bool operator<(const container& Right) const
        //{
        //    return compare(Right) < 0;
        //}

        //bool operator<(const T* Right) const
        //{
        //    return compare(Right) < 0;
        //}

        //bool operator<=(const container& Right) const
        //{
        //    return compare(Right) <= 0;
        //}

        //bool operator<=(const T* Right) const
        //{
        //    return compare(Right) <= 0;
        //}

        //bool operator>(const container& Right) const
        //{
        //    return compare(Right) > 0;
        //}

        //bool operator>(const T* Right) const
        //{
        //    return compare(Right) > 0;
        //}

        //bool operator>=(const container& Right) const
        //{
        //    return compare(Right) >= 0;
        //}

        //bool operator>=(const T* Right) const
        //{
        //    return compare(Right) >= 0;
        //}
    };  // class
}  // namespace


//########################################################################
// Operators
// 
// Commented operators are moved inside basic_string to avoid compiler errors
// about unknown template arguments during matching of operands.



/*
 *    MS Compiler issue error while trying to deduce template argument for stl::string
 *    std::less<stl::string> comp;
 *    stl::string s1("0"), s2("1");
 *    bool res = comp(s1, s2); <--- error using global operators
 *    
 *    Moving all global operators with left operand as stl::string, inside
 *    basic_string class.
 */

//Concatenates two string objects.
template<typename T, typename Allocator>
stl::basic_string<T, Allocator> operator+(
    const stl::basic_string<T, Allocator>& Left,
    const stl::basic_string<T, Allocator>& Right)
{
    stl::basic_string<T> res(Left);
    res += Right;
    return res;
}


template<typename T, typename Allocator>
stl::basic_string<T, Allocator> operator+(
    const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    stl::basic_string<T> res(Left);
    res += Right;
    return res;
}

template<typename T, typename Allocator>
stl::basic_string<T, Allocator> operator+(
    const stl::basic_string<T, Allocator>& Left, const T Right)
{
    stl::basic_string<T> res(Left);
    res += Right;
    return res;
}

template<typename T, typename Allocator>
stl::basic_string<T, Allocator> operator+(
    const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    stl::basic_string<T> res(Left);
    res += Right;
    return res;
}

template<typename T, typename Allocator>
stl::basic_string<T, Allocator> operator+(
    const T Left, const stl::basic_string<T, Allocator>& Right)
{
    stl::basic_string<T> res(1, Left);
    res += Right;
    return res;
}


//Tests if the string object on the left side of the operator is not equal
//to the string object on the right side.
template<typename T, typename Allocator>
bool operator!=(
                const stl::basic_string<T, Allocator>& Left, 
                const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) != 0;
}

template<typename T, typename Allocator>
bool operator!=(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) != 0;
}


template<typename T, typename Allocator>
bool operator!=(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) != 0;
}

//Tests if the string object on the left side of the operator is equal to the string object on the right side.
template<typename T, typename Allocator>
bool operator==(
                const stl::basic_string<T, Allocator>& Left, 
                const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) == 0;
}

template<typename T, typename Allocator>
bool operator==(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) == 0;
}

template<typename T, typename Allocator>
bool operator==(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) == 0;
}

//Tests if the string object on the left side of the operator is less than to the string object on the right side.
template<typename T, typename Allocator>
bool operator<(
                const stl::basic_string<T, Allocator>& Left, 
                const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) < 0;
}

template<typename T, typename Allocator>
bool operator<(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) < 0;
}


template<typename T, typename Allocator>
bool operator<(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) > 0;
}



//Tests if the string object on the left side of the operator is less than or equal to the string object on the right side.
template<typename T, typename Allocator>
bool operator<=(
                const stl::basic_string<T, Allocator>& Left, 
                const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) <= 0;
}

template<typename T, typename Allocator>
bool operator<=(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) <= 0;
}




template<typename T, typename Allocator>
bool operator<=(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) >= 0;
}

//A template function that writes a string into the output stream.
template<typename T, typename Allocator>
std::basic_ostream<T>& operator<<(
    std::basic_ostream<T>& Ostr, const stl::basic_string<T, Allocator>& str)
{
    Ostr << str.c_str();
    return Ostr;
}


//Tests if the string object on the left side of the operator is greater
//than to the string object on the right side.
template<typename T, typename Allocator>
bool operator>(
               const stl::basic_string<T, Allocator>& Left, 
               const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) > 0;
}

template<typename T, typename Allocator>
bool operator>(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) > 0;
}


template<typename T, typename Allocator>
bool operator>(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) < 0;
}


//Tests if the string object on the left side of the operator is greater
//than or equal to the string object on the right side.
template<typename T, typename Allocator>
bool operator>=(
                const stl::basic_string<T, Allocator>& Left, 
                const stl::basic_string<T, Allocator>& Right)
{
    return Left.compare(Right) >= 0;
}

template<typename T, typename Allocator>
bool operator>=(const stl::basic_string<T, Allocator>& Left, const T* Right)
{
    return Left.compare(Right) >= 0;
}


template<typename T, typename Allocator>
bool operator>=(const T* Left, const stl::basic_string<T, Allocator>& Right)
{
    return Right.compare(Left) <= 0;
}

//A template function that reads a string from an input stream.
template<typename T, typename Allocator>
std::basic_istream<T>& operator>>(
    std::basic_istream<T>& Istr, stl::basic_string<T, Allocator>& Right)
{
    std::basic_string<T> chunk;
    Istr >> chunk;
    Right += chunk.c_str();
    return Istr;
}

//Specialized template function
//Exchanges the arrays of characters of two strings.
template<typename T, typename Allocator>
void swap(
          stl::basic_string<T, Allocator>& Left, 
          stl::basic_string<T, Allocator>& Right)
{
    Left.swap(Right);
}

#endif // __basic_string_hpp__
