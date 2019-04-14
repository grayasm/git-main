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

        basic_string(const value_type* ptr, size_type count)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(ptr, count);
        }

        basic_string(const value_type* ptr)
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            assign(ptr);
        }


        basic_string(size_type n, value_type c)
            //: base(n, c)
        {
            const Allocator& alloc = Allocator();
            init(alloc);
            mem_alloc(1);       // avoid 0 capacity with n=0
            eos<T>(0);          // safety
            assign(n, c);
        }


        template<class InputIterator>
        basic_string(InputIterator begin, InputIterator end)
            //: base(begin, end)
        {
            const Allocator& alloc = Allocator();
            init(alloc);
            mem_alloc(1);       // avoid 0 capacity
            eos<T>(0);          // safety
            assign(begin, end);

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

        container& operator=(value_type ch)
        {
            invalidate_iterators();

            /* simplified */
            m_data[0] = ch;
            eos<T>(1);
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

        void reserve(size_type n)
        {
            grow(n);
        }

        void clear( )
        {
            invalidate_iterators();

            eos<T>(0);
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
            return append(str, 0, npos);
        }

        container& append(const container& str, size_type p2, size_type n2)
        {
            size_type strLen = str.length();

            if (strLen > 0)
            {
                if (p2 >= strLen) throw stl::exception("out of valid range");

                if (n2 > strLen - p2)
                    n2 = strLen - p2;

                size_type size = m_size + n2;

                grow(size);

                memcpy_impl(&m_data[m_size], &str[p2], n2 * numbytes);

                eos<T>(size);
            }

            return *this;
        }

        container& append(const value_type* ptr, size_type n2)
        {
            size_type ptrLen = length<value_type>(ptr);

            if (ptrLen > 0)
            {
                if (n2 > ptrLen)
                    n2 = ptrLen;

                size_type size = m_size + n2;

                grow(size);

                memcpy_impl(&m_data[m_size], ptr, n2 * numbytes);

                eos<T>(size);
            }

            return *this;
        }

        container& append(const value_type* ptr)
        {
            return append(ptr, npos);
        }


        container& append(size_type n, value_type value)
        {
            if (n > 0)
            {
                size_type size = m_size + n;

                grow(size);

                stl::mem_set(&m_data[m_size], value, n * numbytes);

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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
            {
                size_type size = m_size + dist;

                grow(size);

                memcpy_impl(&m_data[m_size], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                swap_range(m_size, size);

                eos<T>(size);
            }

            return *this;
        }

        inline container& append_impl(const const_reverse_iterator& first, const const_reverse_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
            {
                size_type size = m_size + dist;

                grow(size);

                memcpy_impl(&m_data[m_size], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                swap_range(m_size, size);

                eos<T>(size);
            }

            return *this;
        }


        /*
        -due to specialization for append_impl(const iterator& ...) and friends,
        compiler cannot find any suitable append_impl for next code:

        float fptr[]={0,...};
        stl::generic_array<float> fcont;
        fcont.append(fptr, fptr+10);
        */
        inline container& append_impl(const value_type* first, const value_type* last)
        {
            difference_type dist = last - first;
            if (dist > 0)
            {
                size_type size = m_size + dist;

                grow(size);

                memcpy_impl(&m_data[m_size], first, dist * numbytes);

                eos<T>(size);
            }

            return *this;
        }

        template<typename InputIterator>
        inline container& append_impl(const InputIterator& first, const InputIterator& last, stl::random_access_iterator_tag)
        {
            return append_impl(first, last);
        }

        template<typename InputIterator>
        inline container& append_impl(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {//e.g. str.append<int>(5, 0x2E);

            if (n > 0)
            {
                size_type size = m_size + n;

                grow(size);

                stl::mem_set(&m_data[m_size], value, n * numbytes);

                eos<T>(size);
            }

            return *this;
        }
    

    public:

        template<typename InputIterator>
        container& append(InputIterator first, InputIterator last)
        {
            return append_impl<InputIterator>(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }


        /* $21.3.5 modifiers ( push_back ) */
        void push_back(const value_type& x)
        {
            if (m_size == m_capacity)
            {
                grow(m_capacity * 2);
            }

            // call copy constructor not copy operator
            new(&m_data[m_size])value_type(x);

            eos<T>(m_size + 1);
        }

        /* $21.3.5 modifiers ( assign ) */
        container& assign(const container& tc)
        {
            //self assignment
            if (this != &tc)
            {
                size_type size = tc.size();

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
                if (off + n > str.size())
                    throw stl::exception("out of valid range");

                // self assignment
                if (this == &str)
                {
                    stl::mem_move(m_data, m_size, &m_data[off], n, m_allocator);
                }
                else
                {
                    grow(n + 1);    // extra '\0'

                    stl::mem_copy(m_data, m_size, &str[off], n, m_allocator);
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
                    if (m_data + m_size < ptr + n)
                        throw stl::exception("out of valid range");

                    stl::mem_move(m_data, m_size, ptr, n, m_allocator);
                }
                else
                {
                    size_type size = length(ptr);   // without '\0' termination

                    if (n > size)
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
            size_type n = length(ptr);   // without '\0' termination

            if (n > 0)
            {
                // Is the address inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    stl::mem_move(m_data, m_size, ptr, n, m_allocator);
                }
                else
                {
                    grow(n + 1);    // extra '\0'

                    stl::mem_copy(m_data, m_size, ptr, n, m_allocator);
                }
            }

            endof(n);

            return *this;
        }

        container& assign(size_type count, const value_type& val)
        {
            invalidate_iterators();

            if (count > 0)
            {
                grow(count);

                stl::mem_set(m_data, val, count * numbytes);
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            invalidate_iterators();

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0; // erase this array

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            invalidate_iterators();

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0; // erase this array

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            invalidate_iterators();

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0; // erase this array

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
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
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            invalidate_iterators();

            size_type dist = last - first;

            if (dist < 0)
                dist = 0; // erase this array

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
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
        stl::generic_array<float> fcont(fptr, fptr+10);
        */

        inline container& assign_impl(const value_type* first, const value_type* last)
        {
            invalidate_iterators();

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0; // erase this array

            if (dist > 0)
            {
                grow(dist);

                memcpy_impl(m_data, first, dist * numbytes);
            }

            eos<T>(dist);

            return *this;
        }


        template<typename InputIterator>
        inline container& assign_impl(InputIterator first, InputIterator last, stl::random_access_iterator_tag)
        {
            return assign_impl(first, last);
        }

        template<typename InputIterator>
        inline container& assign_impl(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            invalidate_iterators();

            if (n < 0)
                n = 0; // erase this array

            if (n > 0)
            {
                grow(n);

                stl::mem_set<value_type>(m_data, value, n * numbytes);
            }

            eos<T>(n);

            return *this;
        }

    public:
        template <typename InputIterator>
        container& assign(InputIterator first, InputIterator last)
        {
            return append_impl<InputIterator>(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }


        /* $21.3.5 modifiers ( insert ) */
        container& insert(size_type p1, const container& str)
        {
            return insert(p1, str, 0, npos);
        }

        container& insert(size_type p1, const container& str, size_type p2, size_type n2)
        {
            if (this == &str)
            {
                return replace(p1, 0, *this, p2, n2);
            }
            else
            {
                //allow insert in end_lock() position;
                if (p1 > m_size) throw stl::exception("out of valid range");

                size_type strLen = str.length();
                if (p2 >= strLen) throw stl::exception("out of valid range");

                if (n2 > strLen - p2)
                    n2 = strLen - p2;

                if (n2)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + n2;

                    grow(size);

                    memmove_impl(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], &str[p2], n2 * numbytes);


                    eos<T>(size);
                }
                return *this;
            }
        }

        container& insert(size_type p1, const value_type* ptr, size_type n2)
        {
            // if (inside(ptr))
            if (m_data <= ptr && m_data + m_size > ptr)
            {
                return replace(p1, 0, *this, 0, n2);
            }
            else
            {
                //allow insert in end_lock() position;
                if (p1 > m_size) throw stl::exception("out of valid range");

                size_type ptrLen = length<value_type>(ptr);
                if (n2 > ptrLen)
                    n2 = ptrLen;

                if (n2)
                {
                    // invalidate for effective insert only
                    invalidate_iterators_gte(p1);

                    size_type size = m_size + n2;

                    grow(size);

                    memmove_impl(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);
                    memcpy_impl(&m_data[p1], ptr, n2 * numbytes);

                    eos<T>(size);
                }
                return *this;
            }
        }

        container& insert(size_type p1, const value_type* ptr)
        {
            return insert(p1, ptr, npos);
        }

        container& insert(size_type p1, size_type n2, value_type ch)
        {
            //allow insert in end_lock() position;
            if (p1 > m_size) throw stl::exception("out of valid range");

            if (n2)
            {
                // invalidate for effective insert only
                invalidate_iterators_gte(p1);

                size_type size = m_size + n2;

                grow(size);

                memmove_impl(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);

                stl::mem_set(&m_data[p1], ch, n2 * numbytes);

                eos<T>(size);
            }

            return *this;
        }

        iterator insert(iterator position, const value_type& x)
        {
            insert(position, 1, x);
            return position;
        }

        void insert(iterator position, size_type n, const value_type& x)
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
        template <typename InputIterator>
        inline void insert(iterator position, InputIterator first, InputIterator last)
        {
            if (position.m_cont != this)
                throw stl::exception("invalid iterator");

            insert_impl(position.m_pos, first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        /* $21.3.5 modifiers ( erase ) */
        container& erase(size_type p1 = 0, size_type n1 = npos)
        {
            if (p1 >= m_size) throw stl::exception("out of valid range");

            if (n1 > m_size - p1)
                n1 = m_size - p1;

            if (n1)
            {
                // invalidate for effective erase only
                invalidate_iterators_gte(p1);

                memmove_impl(&m_data[p1], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);

                eos<T>(m_size - n1);
            }

            return *this;
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


        /* $21.3.5 modifiers ( replace ) */
        container& replace(size_type p1, size_type n1, const container& str)
        {
            return replace(p1, n1, str, 0, str.length());
        }

        container& replace(size_type p1, size_type n1, const container& str, size_type p2, size_type n2)
        {
            if (p1 >= m_size) throw stl::exception("out of valid range");
            if (n1 > m_size - p1)
                n1 = m_size - p1;
            size_type str_size = str.length();
            if (p2 > str_size) throw stl::exception("out of valid range");
            if (n2 > str_size - p2)
                n2 = str_size - p2;
            size_type size = m_size - n1 + n2;

            invalidate_iterators_gte(p1);

            grow(size);

            if (this != &str)
            {
                memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);
                memcpy_impl(&m_data[p1], &str.m_data[p2], n2 * numbytes);

            }
            else if (p1 >= p2)
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
            else if (p1 + n1 <= p2)
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
            else if (n1 < n2)
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

        container& replace(size_type p1, size_type n1, const value_type* ptr, size_type n2)
        {
            //if (inside(ptr))
            if (m_data <= ptr && m_data + m_size > ptr)
            {
                return replace(p1, n1, *this, ptr - m_data, n2);
            }
            else
            {
                if (p1 >= m_size) throw stl::exception("out of valid range");

                invalidate_iterators_gte(p1);

                if (n1 > m_size - p1)
                    n1 = m_size - p1;
                size_type ptrLen = length<value_type>(ptr);
                if (n2 > ptrLen)
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

        container& replace(size_type p1, size_type n1, const value_type* ptr)
        {
            return replace(p1, n1, ptr, npos);
        }

        container& replace(size_type p1, size_type n1, size_type n2, value_type ch)
        {
            if (p1 >= m_size) throw stl::exception("out of valid range");

            invalidate_iterators_gte(p1);

            if (n1 > m_size - p1)
                n1 = m_size - p1;
            size_type size = m_size - n1 + n2;

            grow(size);

            //move tail up
            memmove_impl(&m_data[p1 + n2], &m_data[p1 + n1], (m_size - p1 - n1) * numbytes);

            //set range
            stl::mem_set(&m_data[p1], ch, n2 * numbytes);

            eos<T>(size);

            return *this;
        }

        container& replace(iterator first, iterator last, const container& str)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0;

            return replace(first.m_pos, static_cast<size_type>(dist), str, 0, str.length());
        }

        container& replace(iterator first, iterator last, const value_type* ptr, size_type n2)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0;

            return replace(first.m_pos, static_cast<size_type>(dist), ptr, n2);
        }

        container& replace(iterator first, iterator last, const value_type* ptr)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0;

            return replace(first.m_pos, dist, ptr, npos);
        }

        container& replace(iterator first, iterator last, size_type n2, value_type ch)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
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
            if (first2.m_cont != last2.m_cont || first2.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last2 - first2;

            if (dist < 0)
                dist = 0;

            return replace(p1, n1, *(first2.m_cont), first2.m_pos, dist);
        }

        inline container& replace_impl(size_type p1, size_type n1, const const_iterator& first2, const const_iterator& last2)
        {
            if (first2.m_cont != last2.m_cont || first2.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last2 - first2;

            if (dist < 0)
                dist = 0;

            return replace(p1, n1, first2.m_cont, first2.m_pos, dist);
        }

        inline container& replace_impl(size_type p1, size_type n1, const reverse_iterator& first2, const reverse_iterator& last2)
        {
            if (first2.m_cont != last2.m_cont || first2.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last2 - first2;

            if (dist < 0)
                dist = 0;

            replace(p1, n1, first2.m_cont, last2.m_pos + 1, dist);

            swap_range(p1, p1 + dist);

            return *this;
        }

        inline container& replace_impl(size_type p1, size_type n1, const const_reverse_iterator& first2, const const_reverse_iterator& last2)
        {
            if (first2.m_cont != last2.m_cont || first2.m_cont == 0)
                throw stl::exception("invalid iterator");

            difference_type dist = last2 - first2;

            if (dist < 0)
                dist = 0;

            replace(p1, n1, first2.m_cont, last2.m_pos + 1, dist);

            swap_range(p1, p1 + dist);

            return *this;
        }

        /*
        -due to specialization for replace_impl(const iterator& ...) and friends,
        compiler cannot find any suitable replace_impl for next code:

        stl::generic_array<char> charr(10, 'x'), charr2(2, 'a');
        charr.replace(charr.begin(), ++charr.begin(),
        charr2.c_str(), charr2.c_str()+2);
        */
        inline container& replace_impl(size_type p1, size_type n1, const value_type* first, const value_type* last)
        {
            if (!first || !last)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0;

            return replace(p1, n1, first, dist);
        }

        template<typename InputIterator>
        inline container& replace_impl(size_type p1, size_type n1, const InputIterator& first2, const InputIterator& last2, stl::random_access_iterator_tag)
        {
            return replace_impl(p1, n1, first2, last2);
        }

        template<typename InputIterator>
        inline container& replace_impl(size_type p1, size_type n1, InputIterator n2, InputIterator value, stl::input_iterator_tag)
        {
            return replace(p1, n1, n2, value);
        }

    public:
        template<typename InputIterator>
        inline container& replace(iterator first, iterator last, InputIterator first2, InputIterator last2)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;

            if (dist < 0)
                dist = 0;

            return replace_impl(first.m_pos, dist, first2, last2, typename stl::iterator_traits<InputIterator>::iterator_category());
        }


        /* $21.3.5 modifiers ( copy ) */
        size_type copy(value_type* ptr, size_type n1, size_type p1 = 0) const
        {
            if (p1 >= m_size) throw stl::exception("out of valid range");

            if (n1 > m_size - p1)
                n1 = m_size - p1;

            memmove_impl(ptr, &m_data[p1], n1 * numbytes);

            return n1;
        }


        /* $21.3.5 modifiers ( swap ) */
        void swap(container& str)
        {
            stl::swap<Allocator>(m_allocator, vec.m_allocator);
            stl::swap<pointer>(m_data, vec.m_data);
            stl::swap<size_type>(m_size, vec.m_size);
            stl::swap<size_type>(m_capacity, vec.m_capacity);
            //stl::swap<iterator_array*>(m_itarray, vec.m_itarray);
        }

//TODO: use template specialization to disable anything but char,unsigned char,wchar_t
//      actually all that implements ::memcpy, ::memmove
//      because it is clear that c_str() would not work with anything that does
//      not end in '\0', right?

        /* $21.3.6 string operations */
        const value_type* c_str() const
        {
            return m_data;      // if string is '\0' terminated.
        }

        const value_type* data() const
        {
            return m_data;      // if string is '\0' terminated.
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
