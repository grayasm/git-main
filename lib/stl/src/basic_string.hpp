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
        friend class stl::basic_string<typename container::value_type, typename container::allocator_type>;
        friend class stl::basic_string_const_iterator<container>;


    private:
        basic_string_iterator(container* cont, size_type pos)
        {
            m_cont = cont;
            m_pos = pos;
        }

    public:
        basic_string_iterator()
        {
            m_cont = 0;
            m_pos = 0;
        }

        basic_string_iterator(const basic_string_iterator& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        ~basic_string_iterator()
        {
        }

        basic_string_iterator& operator=(const basic_string_iterator& it)
        {
            if (this != &it)
            {
                m_cont = it.m_cont;
                m_pos = it.m_pos;
            }

            return *this;
        }

        reference operator*() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos);
        }

        pointer operator->() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos);
        }

        basic_string_iterator& operator++()
        {
            ++m_pos;
            return *this;
        }

        basic_string_iterator operator++(int)
        {
            basic_string_iterator<container> tmp = *this;
            ++m_pos;
            return tmp;
        }

        basic_string_iterator& operator--()
        {
            --m_pos;
            return *this;
        }

        basic_string_iterator operator--(int)
        {
            basic_string_iterator<container> tmp = *this;
            --m_pos;
            return tmp;
        }

        basic_string_iterator& operator+=(difference_type off)
        {
            m_pos += off;
            return *this;
        }

        basic_string_iterator operator+(difference_type off) const
        {
            basic_string_iterator<container> tmp = *this;
            return (tmp += off);
        }

        basic_string_iterator& operator-=(difference_type off)
        {
            m_pos -= off;
            return *this;
        }

        basic_string_iterator operator-(difference_type off) const
        {
            basic_string_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const basic_string_iterator& it) const
        {
            return static_cast<difference_type>(m_pos - it.m_pos);
        }

        bool operator==(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos != it.m_pos);
        }

        bool operator<(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos < it.m_pos);
        }

        bool operator>(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos > it.m_pos);
        }

        bool operator<=(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos <= it.m_pos);
        }

        bool operator>=(const basic_string_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos + off);
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
        friend class basic_string<typename container::value_type, typename container::allocator_type>;

    private:
        basic_string_const_iterator(container* cont, size_type pos)
        {
            m_cont = cont;
            m_pos = pos;
        }

    public:
        basic_string_const_iterator()
        {
            m_cont = 0;
            m_pos = 0;
        }

        basic_string_const_iterator(const basic_string_const_iterator& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        basic_string_const_iterator(const basic_string_iterator<container>& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        ~basic_string_const_iterator()
        {
        }

        basic_string_const_iterator& operator=(const basic_string_const_iterator& it)
        {
            if (this != &it)
            {
                m_cont = it.m_cont;
                m_pos = it.m_pos;
            }

            return *this;
        }

        basic_string_const_iterator& operator=(const basic_string_iterator<container>& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;

            return *this;
        }

        reference operator*() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos);
        }

        pointer operator->() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos);
        }

        basic_string_const_iterator& operator++()
        {
            ++m_pos;
            return *this;
        }

        basic_string_const_iterator operator++(int)
        {
            basic_string_const_iterator<container> tmp = *this;
            ++m_pos;
            return tmp;
        }

        basic_string_const_iterator& operator--()
        {
            --m_pos;
            return *this;
        }

        basic_string_const_iterator operator--(int)
        {
            basic_string_const_iterator<container> tmp = *this;
            --m_pos;
            return tmp;
        }

        basic_string_const_iterator& operator+=(difference_type off)
        {
            m_pos += off;
            return *this;
        }

        basic_string_const_iterator operator+(difference_type off) const
        {
            basic_string_const_iterator<container> tmp = *this;
            return (tmp += off);
        }

        basic_string_const_iterator& operator-=(difference_type off)
        {
            m_pos -= off;
            return *this;
        }

        basic_string_const_iterator operator-(difference_type off) const
        {
            basic_string_const_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const basic_string_const_iterator& it) const
        {
            return static_cast<difference_type>(m_pos - it.m_pos);
        }

        bool operator==(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos != it.m_pos);
        }

        bool operator<(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos < it.m_pos);
        }

        bool operator>(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos > it.m_pos);
        }

        bool operator<=(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos <= it.m_pos);
        }

        bool operator>=(const basic_string_const_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos + off);
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
        friend class basic_string<typename container::value_type, typename container::allocator_type>;
        friend class basic_string_const_reverse_iterator<container>;


    private:
        basic_string_reverse_iterator(container* cont, size_type pos)
        {
            m_cont = cont;
            m_pos = pos;
        }

    public:
        basic_string_reverse_iterator()
        {
            m_cont = 0;
            m_pos = 0;
        }

        basic_string_reverse_iterator(const basic_string_reverse_iterator& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        ~basic_string_reverse_iterator()
        {
        }

        basic_string_reverse_iterator& operator=(const basic_string_reverse_iterator& it)
        {
            if (this != &it)
            {
                m_cont = it.m_cont;
                m_pos = it.m_pos;
            }

            return *this;
        }

        reference operator*() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos);
        }

        pointer operator->() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos);
        }

        basic_string_reverse_iterator& operator++()
        {
            --m_pos;
            return *this;
        }

        basic_string_reverse_iterator operator++(int)
        {
            basic_string_reverse_iterator<container> tmp = *this;
            --m_pos;
            return tmp;
        }

        basic_string_reverse_iterator& operator--()
        {
            ++m_pos;
            return *this;
        }

        basic_string_reverse_iterator operator--(int)
        {
            basic_string_reverse_iterator<container> tmp = *this;
            ++m_pos;
            return tmp;
        }

        basic_string_reverse_iterator& operator+=(difference_type off)
        {
            m_pos -= off;
            return *this;
        }

        basic_string_reverse_iterator operator+(difference_type off) const
        {
            basic_string_reverse_iterator<container> tmp = *this;
            return (tmp += off);
        }

        basic_string_reverse_iterator& operator-=(difference_type off)
        {
            m_pos += off;
            return *this;
        }

        basic_string_reverse_iterator operator-(difference_type off) const
        {
            basic_string_reverse_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const basic_string_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - m_pos);
        }

        bool operator==(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (it.m_pos == m_pos);
        }

        bool operator!=(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (it.m_pos != m_pos);
        }

        bool operator<(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos > it.m_pos);
        }

        bool operator>(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos < it.m_pos);
        }

        bool operator<=(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos >= it.m_pos);
        }

        bool operator>=(const basic_string_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos - off)
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
        friend class basic_string<typename container::value_type, typename container::allocator_type>;


    private:
        basic_string_const_reverse_iterator(container* cont, size_type pos)
        {
            m_cont = cont;
            m_pos = pos;
        }

    public:
        basic_string_const_reverse_iterator()
        {
            m_cont = 0;
            m_pos = 0;
        }

        basic_string_const_reverse_iterator(const basic_string_const_reverse_iterator& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        ~basic_string_const_reverse_iterator()
        {
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_const_reverse_iterator& it)
        {
            if (this != &it)
            {
                m_cont = it.m_cont;
                m_pos = it.m_pos;
            }
            return *this;
        }

        basic_string_const_reverse_iterator& operator=(const basic_string_reverse_iterator<container>& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;

            return *this;
        }

        basic_string_const_reverse_iterator(const basic_string_reverse_iterator<container>& it)
        {
            m_cont = it.m_cont;
            m_pos = it.m_pos;
        }

        reference operator*() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return *(m_cont->m_data + m_pos);
        }

        pointer operator->() const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos);
        }

        basic_string_const_reverse_iterator& operator++()
        {
            --m_pos;
            return *this;
        }

        basic_string_const_reverse_iterator operator++(int)
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            --m_pos;
            return tmp;
        }

        basic_string_const_reverse_iterator& operator--()
        {
            ++m_pos;
            return *this;
        }

        basic_string_const_reverse_iterator operator--(int)
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            ++m_pos;
            return tmp;
        }

        basic_string_const_reverse_iterator& operator+=(difference_type off)
        {
            m_pos -= off;
            return *this;
        }

        basic_string_const_reverse_iterator operator+(difference_type off) const
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            return (tmp += off);
        }

        basic_string_const_reverse_iterator& operator-=(difference_type off)
        {
            m_pos += off;
            return *this;
        }

        basic_string_const_reverse_iterator operator-(difference_type off) const
        {
            basic_string_const_reverse_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const basic_string_const_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - m_pos);
        }

        bool operator==(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos == it.m_pos);
        }

        bool operator!=(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos != it.m_pos);
        }

        bool operator<(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos > it.m_pos);
        }

        bool operator>(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos < it.m_pos);
        }

        bool operator<=(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos >= it.m_pos);
        }

        bool operator>=(const basic_string_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!m_cont)
                throw stl::exception("invalid iterator");

            return (m_cont->m_data + m_pos - off);
        }
    };  // basic_string_const_reverse_iterator


    template<typename T, typename Allocator = stl::allocator<T> >
    class basic_string
    {
    public:
        typedef          basic_string<T, Allocator>         container;

        // types:
        typedef typename Allocator::value_type              value_type;
        typedef typename Allocator::size_type               size_type;
        typedef typename Allocator::difference_type         difference_type;
        typedef Allocator                                   allocator_type;

        typedef typename Allocator::reference               reference;
        typedef typename Allocator::const_reference         const_reference;
        typedef typename Allocator::pointer                 pointer;
        typedef typename Allocator::const_pointer           const_pointer;

        typedef basic_string_iterator<container>            iterator;
        typedef basic_string_const_iterator<container>      const_iterator;
        typedef basic_string_reverse_iterator<container>    reverse_iterator;
        typedef basic_string_const_reverse_iterator<container>  const_reverse_iterator;

        friend class iterator;
        friend class const_iterator;
        friend class reverse_iterator;
        friend class const_reverse_iterator;

    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;

    public:
        static const size_type npos = static_cast<size_type>(-1);


    private:
        /*  1) memset only accepted types
            2) discard allocator.construct and allocator.destroy
        */
        inline void check_type(char*) { }
        inline void check_type(unsigned char*) { }
        inline void check_type(wchar_t*) { }
        
        inline void init()
        {
            check_type(m_data);

            m_data = 0;
            m_size = 0;
            m_capacity = 0;
            // m_allocator - default ctor;
        }

        inline void grow(size_type cap)
        {
            if (m_capacity >= cap)
                return;

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
#ifdef DEBUG
            // safety guard: if this throws the issue needs fixing.
            if (size >= m_capacity)
                throw stl::exception("out of valid range");
#endif

            m_size = size;
            m_data[m_size] = 0;
        }

        inline size_type length(const value_type* ptr) const
        {
            if (ptr == 0)
                throw stl::exception("null pointer");

            const value_type* p = ptr;
            while (*p != 0)
                p++;
            return (p - ptr);
        }

    public:
        basic_string()
        {
            init();
            grow(1);    // .c_str() is '\0' terminated
            endof(0);
        }

        basic_string(const container& str)
        {
            init();
            assign(str);
        }

        basic_string(const container& str, size_type pos, size_type sublen = npos)
        {
            init();
            assign(str, pos, sublen);
        }

        basic_string(const value_type* ptr)
        {
            init();
            assign(ptr);
        }

        basic_string(const value_type* ptr, size_type n)
        {
            init();
            assign(ptr, n);
        }

        basic_string(size_type n, value_type c)
        {
            init();
            assign(n, c);
        }


        template<class InputIterator>
        basic_string(InputIterator first, InputIterator last)
        {
            init();
            assign_(first, last);       // take a shortcut
        }

        ~basic_string()
        {
            m_allocator.deallocate(m_data, 0); // always allocated

            m_data = 0;
            m_size = 0;
            m_capacity = 0;
        }

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

        const_reference operator[] ( size_type n ) const
        {
            return m_data[n];
        }

        reference operator[] ( size_type n )
        {
            return m_data[n];
        }

        const_reference at ( size_type n ) const
        {
            if (n >= m_size)
                throw stl::exception("out of valid range");

            return m_data[n];
        }

        reference at ( size_type n )
        {
            if (n >= m_size)
                throw stl::exception("out of valid range");

            return m_data[n];
        }

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

        /*  Extends the basic_string by appending additional characters
            at the end of its current value.
            
            str: Another basic_string object of the same type (with the same
                 class template arguments), whose value is appended.
        */
        container& append(const container& str)
        {
            size_type n = str.length();    // without '\0'

            if (n > 0)
            {
                size_type size = m_size + n;

                // even if m_data is relocated, str remains valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], 0, str.m_data, n, m_allocator);

                endof(size);
            }

            return *this;
        }

        /*  subpos: Position of the first character in str that is copied
                    to the object as a substring. If this is greater than
                    str length, it throws out_of_range.
            Note: The first character in str is denoted by a value of 0 (not 1).

            sublen: Length of the substring to be copied (if the string is
                    shorter, as many characters as possible are copied).
                    A value of basic_string::npos indicates all characters
                    until the end of str.
        */
        container& append(const container& str, size_type subpos, size_type sublen)
        {
            size_type strlen = str.length();    // without '\0'

            if (subpos > strlen)
                throw stl::exception("out of valid range");

            if (sublen > strlen - subpos)
                sublen = strlen - subpos;
            
            if (sublen)
            {
                size_type size = m_size + sublen;

                grow(size + 1);

                // no need for memmove when appending from self
                stl::mem_copy(&m_data[m_size], 0, &str.m_data[subpos], sublen, m_allocator);

                endof(size);
            }

            return *this;
        }

        /*  Appends a copy of the first n characters in the array of characters
            pointed by ptr.
        */
        container& append(const value_type* ptr, size_type n)
        {
            size_type strlen = length(ptr);    // without '\0'

            if (strlen)
            {
                if (n > strlen)
                    n = strlen;

                size_type size = m_size + n;

                // Is the range inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    size_type off = ptr - m_data;

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, m_data + off, n, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, ptr, n, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        container& append(const value_type* ptr)
        {
            size_type n = length(ptr);    // without '\0'

            if (n)
            {
                size_type size = m_size + n;

                // Is the range inside this container ?
                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    size_type off = ptr - m_data;

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, m_data + off, n, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, ptr, n, m_allocator);
                }

                endof(size);
            }

            return *this;
        }
        
        container& append(size_type n, value_type value)
        {
            if (n)
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
            if (dist)
            {
                size_type size = m_size + dist;

                // even if m_data is relocated, first and last remain valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], 0, &((*first.m_cont)[first.m_pos]), dist, m_allocator);

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
            if (dist)
            {
                size_type size = m_size + dist;

                // even if m_data is relocated, first and last remain valid
                grow(size + 1);

                stl::mem_copy(&m_data[m_size], 0, &((*first.m_cont)[first.m_pos]), dist, m_allocator);

                endof(size);
            }

            return *this;
        }

        inline container& append_(value_type* first, value_type* last)
        {
            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist)
            {
                size_type size = m_size + dist;

                // Is the range inside this container ?
                if (m_data <= first && (m_data + m_size) > first)
                {
                    size_type off = first - m_data;

                    // can relocate m_data and free the old block
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, m_data + off, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, first, dist, m_allocator);
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
            // first can be string::reverse_iterator, list::iterator or something else
            // cannot check with: if(fist.m_cont != last.m_cont)

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(stl::distance(first, last));
            if (dist)
            {
                size_type size = m_size + dist;

                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(size + 1);

                    stl::mem_copy(&m_data[m_size], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        m_data[m_size + i] = *first;
                    }
                }

                endof(size);
            }

            return *this;
        }

        template<typename InputIterator>
        inline container& append_(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            if (n)
            {
                size_type size = m_size + n;

                grow(size + 1);

                stl::mem_set(&m_data[m_size], value, n * sizeof(value_type), m_allocator);

                endof(size);
            }

            return *this;
        }

    public:
        void push_back(const value_type& x)
        {
            m_data[m_size] = x;

            if (m_size + 1 == m_capacity)
            {
                grow(m_capacity * 2);
            }

            endof(m_size + 1);
        }

        /*  Assigns a new value to the string, replacing its current contents.
            
            str: Another basic_string object of the same type (with the same
                 class template arguments), whose value is either copied or
                 moved.
        */
        container& assign(const container& str)
        {
            //self assignment
            if (this != &str)
            {
                size_type size = str.length(); // without '\0'

                grow(size + 1); // extra '\0'  (critical when size is 0)

                stl::mem_copy(m_data, 0, str.m_data, size, m_allocator);

                endof(size);
            }

            return *this;
        }

        /*  Assigns a new value to the string, replacing its current contents.

            str: Another basic_string object of the same type (with the same
                 class template arguments), whose value is either copied or
                 moved.

         subpos: Position of the first character in str that is copied
                 to the object as a substring. If this is greater than
                 str length, it throws out_of_range.
           Note: The first character in str is denoted by a value of 0 (not 1).

         sublen: Length of the substring to be copied (if the string is
                 shorter, as many characters as possible are copied).
                 A value of basic_string::npos indicates all characters
                 until the end of str.
        */
        container& assign(const container& str, size_type subpos, size_type sublen)
        {
            if (subpos > str.m_size)
                throw stl::exception("out of valid range");

            // if subpos is m_size then sublen is 0 and internal string discarded
            if (sublen > str.m_size - subpos)
                sublen = str.m_size - subpos;

            // self assignment
            if (this == &str)
            {
                // Should work w/o extra buffer/memmove (copy to left side)
                stl::mem_copy(m_data, m_size, &m_data[subpos], sublen, m_allocator);
            }
            else
            {
                grow(sublen + 1);    // extra '\0'

                stl::mem_copy(m_data, m_size, &str.m_data[subpos], sublen, m_allocator);
            }
            
            endof(sublen);

            return *this;
        }

        /*  Assigns a new value to the string, replacing its current contents.
            Copies the first n characters from the array of characters pointed
            by ptr.

            ptr: Pointer to an array of characters (such as a c-string).
              n: Number of characters to copy.
        */
        container& assign(const value_type* ptr, size_type n)
        {
            // Is the address inside this container ?
            if (m_data <= ptr && (m_data + m_size) > ptr)
            {
                // Should work w/o extra buffer/memmove (copy to left side)
                stl::mem_copy(m_data, 0, ptr, n, m_allocator);
            }
            else
            {
                grow(n + 1);    // extra '\0'

                stl::mem_copy(m_data, 0, ptr, n, m_allocator);
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

                // Should work w/o an extra buffer/memmove (copy to left side)
                stl::mem_copy(m_data, 0, ptr, n, m_allocator);
            }
            else
            {
                n = length(ptr);   // without '\0'

                grow(n + 1);    // extra '\0'  (critical when n is 0)

                stl::mem_copy(m_data, 0, ptr, n, m_allocator);
            }

            endof(n);

            return *this;
        }

        container& assign(size_type n, const value_type& c)
        {
            T temp(c);      // cheaper than the full comparison

            grow(n + 1);    // critical when n is 0

            if (n)
            {
                stl::mem_set(m_data, temp, n * sizeof(value_type), m_allocator);
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

            grow(n + 1);    // extra '\0'   (critical when n is 0)

            if (n)
            {
                //self assignment
                if (first.m_cont == this)
                {
                    stl::mem_move(m_data, m_size, &((*first.m_cont)[first.m_pos]), n, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, 0, &((*first.m_cont)[first.m_pos]), n, m_allocator);
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

            grow(n + 1);    // extra '\0'   (critical when n is 0)

            if (n)
            {
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

            grow(n + 1); // extra '\0'  (critical when n is 0)

            if (n)
            {
                // Is range inside this container ?
                if (m_data <= first && (m_data + m_size) > first)
                {
                    stl::mem_move(m_data, 0, first, n, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, 0, first, n, m_allocator);
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

            grow(n + 1);

            if (n)
            {
                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp(first, last);
                    
                    stl::mem_move(m_data, 0, temp.m_data, n, m_allocator);
                }
                else// range is outside this container
                {
                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        m_data[i] = *first;
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

            grow(n + 1);    // extra '\0'   (critical when n is 0)

            if (n)
            {
                // Not a self assignment as value is a temporary copy.
                stl::mem_set(m_data, value, n * sizeof(value_type), m_allocator);
            }

            endof(n);

            return *this;
        }

    public:
        /*  Inserts a copy of str into the basic_string right before
            the character indicated by pos.

            pos: Insertion point. The new contents are inserted before
                 the character at position pos. If this is greater than
                 the object's length, it throws out_of_range.
            Note: The first character is denoted by a value of 0 (not 1).
        */
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
                    m_data + m_size which means the source m_data remains
                    intact.
                */
                grow(size + 1);

                // move content unless insert position is end()
                if (pos < m_size)
                {
                    // copying to uninitialized area - non overlapping
                    stl::mem_copy(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);
                }

                if (this == &str) // insert self content
                {
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

        /*  Inserts a copy of a substring of str. The substring is
            the portion of str that begins at the character position subpos
            and spans sublen characters (or until the end of str, if either
            str is too short or if sublen is npos).

            pos: Insertion point. The new contents are inserted before
                 the character at position pos. If this is greater than
                 the object's length, it throws out_of_range.
                 
         subpos: Position of the first character in str that is inserted
                 into the object as a substring. If this is greater than
                 str's length, it throws out_of_range.

         sublen: Length of the substring to be copied (if the string is
                 shorter, as many characters as possible are copied).
                 A value of npos indicates all characters until the end of str.
        */
        container& insert(size_type pos, const container& str, size_type subpos, size_type sublen)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            size_type strlen = str.length();

            if (subpos > strlen)
                throw stl::exception("out of valid range");

            if (sublen > strlen - subpos)
                sublen = strlen - subpos;   // sublen can become 0

            if (sublen)
            {
                size_type size = m_size + sublen;

                // relocation does not invalidate str
                grow(size + 1);

                if (this == &str)
                {
                    container temp(&m_data[subpos], &m_data[subpos + sublen]);

                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos], (m_size - pos), m_allocator);

                    stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
                }
                else
                {
                    stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos], (m_size - pos), m_allocator);

                    stl::mem_copy(&m_data[pos], 0, &str.m_data[subpos], sublen, m_allocator);
                }

                endof(size);
            }
            
            return *this;
        }

        /*  Inserts a copy of the string formed by the null-terminated
            character sequence (C-string) pointed by ptr.
            The length of this character sequence is determined by calling
            traits_type::length(ptr).
        */
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

                    stl::mem_move(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);

                    stl::mem_copy(&m_data[pos], 0, temp.m_data, len, m_allocator);
                }
                else
                {
                    grow(size + 1);

                    stl::mem_move(&m_data[pos + len], 0, &m_data[pos], (m_size - pos), m_allocator);

                    stl::mem_copy(&m_data[pos], 0, ptr, len, m_allocator);
                }

                endof(size);
            }

            return *this;
        }

        /*  Inserts a copy of the first n characters in the array of characters
            pointed by ptr.
        */
        container& insert(size_type pos, const value_type* ptr, size_type n)
        {
            // allow to insert in position = end(), aka pos == m_size;
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (n)
            {
                size_type size = m_size + n;

                if (m_data <= ptr && (m_data + m_size) > ptr)
                {
                    container temp(ptr, ptr + n);

                    grow(size + 1);

                    stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);

                    stl::mem_move(&m_data[pos], 0, temp.m_data, n, m_allocator);
                }
                else
                {
                    grow(size + 1);

                    stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);

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

                stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);

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

                stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);

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

            stl::mem_move(&m_data[pos + 1], 0, &m_data[pos], (m_size - pos), m_allocator);

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
            if (dist)
            {
                // take advantage of the fast replace
                replace_nb_(position.m_pos, 0, *first.m_cont, first.m_pos, dist);
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
                // take advantage of the fast replace
                replace_nb_(position.m_pos, 0, *first.m_cont, first.m_pos, dist);
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

                // Is the range inside this container ?
                if (m_data <= first && (m_data + m_size) > first)
                {
                    container temp(first, last);

                    // can relocate m_data and invalidate first,last pointers
                    grow(size + 1);

                    stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);

                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);

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
                    container temp(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(size + 1);

                    stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);

                    stl::mem_copy(&m_data[p], 0, temp.m_data, dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size + 1);

                    stl::mem_move(&m_data[p + dist], 0, &m_data[p], (m_size - p), m_allocator);

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

                stl::mem_move(&m_data[pos + n], 0, &m_data[pos], (m_size - pos), m_allocator);

                stl::mem_set(&m_data[pos], value, n * sizeof(value_type), m_allocator);

                endof(size);
            }
        }

        /*  Usually doing insert from self with a buffer performs 2x slower
            compared with std::string, if not slower.
            My initial version still performed worse, so I adapted this code
            from VC/include/xstring
        */
        inline container& replace_nb_(size_type p1, size_type n1, const container& str, size_type p2, size_type n2)
        {
            if (p1 > m_size || p2 > str.m_size)
                throw stl::exception("out of valid range");

            if (n1 > m_size - p1)
                n1 = m_size - p1;

            if (n2 > str.m_size - p2)
                n2 = str.m_size - p2;

            size_type size = m_size - n1 + n2;

            size_t Nm = m_size - p1 - n1;    // length of kept tail
            

            grow(size + 1);


            if (this != &str)
            {   // no overlap, just move down and copy in new stuff
                stl::mem_move(m_data + p1 + n2, 0,
                              m_data + p1 + n1, Nm, m_allocator);   // empty hole
                stl::mem_copy(m_data + p1, 0,
                              str.m_data + p2, n2, m_allocator);    // fill hole
            }
            else if (n2 <= n1)
            {   // hole doesn't get larger, just copy in substring
                stl::mem_move(m_data + p1, 0,
                              m_data + p2, n2, m_allocator);        // fill hole
                stl::mem_move(m_data + p1 + n2, 0,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
            }
            else if (p2 <= p1)
            {   // hole gets larger, substring begins before hole
                stl::mem_move(m_data + p1 + n2, 0,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1, 0,
                              m_data + p2, n2, m_allocator);        // fill hole
            }
            else if (p1 + n1 <= p2)
            {   // hole gets larger, substring begins after hole
                stl::mem_move(m_data + p1 + n2, 0,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1, 0,
                              m_data + (p2 + n2 - n1),
                              n2, m_allocator);                     // fill hole
            }
            else
            {   // hole gets larger, substring begins in hole
                stl::mem_move(m_data + p1, 0,
                              m_data + p2, n1, m_allocator);        // fill old hole
                stl::mem_move(m_data + p1 + n2, 0,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1 + n1, 0,
                              m_data + p2 + n2,
                              n2 - n1, m_allocator);                // fill rest of new hole
            }

            endof(size);

            return *this;

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
            if (pos > m_size)
                throw stl::exception("invalid iterator");

            if (len > m_size - pos)
                len = m_size - pos;

            stl::mem_move(&m_data[pos], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

            size_type dist = last.m_pos - first.m_pos;

            stl::mem_copy(&m_data[first.m_pos], 0, &m_data[last.m_pos], (m_size - last.m_pos), m_allocator);

            endof(m_size - dist);

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
                container temp(m_data, m_data + m_size); // from str

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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
                container temp(m_data, m_data + m_size);

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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
            return replace_nb_(pos, len, str, subpos, sublen);
        }

        /*  pos: Position of the first character to be replaced. If this is
                 greater than the string length, it throws out_of_range.
            len: Number of characters to replace (if the string is shorter,
                 as many characters as possible are replaced).
                 A value of string::npos indicates all characters until the
                 end of the string.
            ptr: Pointer to an array of characters (such as a c-string).
        */
        container& replace(size_type pos, size_type len, const value_type* ptr)
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
                container temp(ptr, ptr + slen);

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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
                container temp(ptr, ptr + slen);

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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
                container temp(ptr, ptr + slen);

                stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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
                container temp(ptr, ptr + slen);

                stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

//TODO: test with sublen == 0 and if tested ok, then add if (sublen) here...
                stl::mem_copy(&m_data[pos], 0, temp.m_data, sublen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + sublen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

            stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

            stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);
                
                stl::mem_copy(&m_data[pos], 0, &*first2, slen, m_allocator);
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

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);
                
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, &*first2, slen, m_allocator);
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

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);
                
                stl::mem_copy(&m_data[pos], 0, first2, slen, m_allocator);
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

                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);
                
                stl::mem_copy(&m_data[pos], 0, temp.m_data, slen, m_allocator);
            }
            else // insert from another container
            {
                stl::mem_move(&m_data[pos + slen], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

            stl::mem_move(&m_data[pos + n], 0, &m_data[pos + len], (m_size - pos - len), m_allocator);

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

        /*  Finds the first substring equal to the given character sequence.
            Search begins at pos, i.e. the found substring must not begin in
            a position preceding pos.
            Returns the position of the first character of the found substring
            or npos if no such substring is found.
        */
        size_type find(const container& str, size_type pos = 0) const
        {
            size_type strlen = str.length();    // without '\0'

            // str is bigger than this, or bigger than [pos, end) search range.
            if (strlen > m_size || pos > (m_size - strlen))
                return npos;
            
            for (size_type i = pos; i < m_size; ++i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == str.m_data[k])
                {
                    j++;
                    k++;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }

        /*  Finds the first substring equal to the character string
            pointed to by ptr. The length of the string is determined
            by the first null character using Traits::length(ptr).
        */
        size_type find(const value_type* ptr, size_type pos = 0) const
        {
            size_type strlen = length(ptr);    // without '\0'

            // ptr is bigger than this, or bigger than [pos, end) search range.
            if (strlen > m_size || pos > (m_size - strlen))
                return npos;

            for (size_type i = pos; i < m_size; ++i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == ptr[k])
                {
                    j++;
                    k++;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }
        
        /*  Finds the first substring equal to the range [ptr, ptr+n).
            This range may contain null characters.
            Search in this object begins at pos, i.e. the found substring
            must not begin in a position preceding pos.
        */
        size_type find(const value_type* ptr, size_type pos, size_type n) const
        {
            size_type strlen = n;   // no check for '\0' termination in ptr;

            // ptr is bigger than this, or bigger than [pos, end) search range.
            if (strlen > m_size || pos > (m_size - strlen))
                return npos;

            for (size_type i = pos; i < m_size; ++i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == ptr[k])
                {
                    j++;
                    k++;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }

        /*  Finds the first character ch, treated as a single-character
            substring.

            pos: Position of the first character in the string to be
                 considered in the search. If this is greater than the string
                 length, the function never finds matches.
        */
        size_type find(value_type ch, size_type pos = 0) const
        {
            for (size_type i = pos; i < m_size; ++i)
            {
                if (m_data[i] == ch)
                    return i;
            }

            return npos;
        }


        /*  Finds the last substring equal to str.
            Search begins at pos, i.e. the found substring must not begin
            in a position following pos. If npos or any value not smaller
            than size()-1 is passed as pos, whole string will be searched.

            str: Another string with the subject to search for.
            pos: Position of the last character in the string to be considered
                 as the beginning of a match. Any value greater or equal than
                 the string length (including string::npos) means that the
                 entire string is searched.
            Note: The first character is denoted by a value of 0 (not 1).
        */
        size_type rfind(const container& str, size_type pos = npos) const
        {
            size_type strlen = str.length();

            // if str is bigger than this, it cannot be a substring.
            if (strlen > m_size)
                return npos;

            // adjust the last pos where str can fit into this
            if (pos > (m_size - strlen))
                pos = m_size - strlen;
            
            for (size_type i = pos; i != npos; --i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == str.m_data[k])
                {
                    ++j;
                    ++k;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }

        /*  Finds the last substring equal to the character string pointed
            to by ptr. The length of the string is determined by the first
            null character using Traits::length(ptr).

            ptr: Pointer to a character string to search for
            pos: Position of the last character in the string to be considered
                 as the beginning of a match. Any value greater or equal than
                 the string length (including string::npos) means that the
                 entire string is searched.
            Note: The first character is denoted by a value of 0 (not 1).
        */
        size_type rfind(const value_type* ptr, size_type pos = npos) const
        {
            size_type strlen = length(ptr);

            // if ptr is bigger than this, it cannot be a substring.
            if (strlen > m_size)
                return npos;

            // adjust the last pos where ptr can fit into this
            if (pos > (m_size - strlen))
                pos = m_size - strlen;

            for (size_type i = pos; i != npos; --i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == ptr[k])
                {
                    ++j;
                    ++k;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }


        /*  Finds the last substring equal to the range [ptr, ptr + n).
            This range can include null characters.

            ptr: Pointer to a character string to search for
            pos: Position of the last character in the string to be considered
                 as the beginning of a match. Any value greater or equal than
                 the string length (including string::npos) means that the
                 entire string is searched.
            Note: The first character is denoted by a value of 0 (not 1).
        */
        size_type rfind(const value_type* ptr, size_type pos, size_type n) const
        {
            size_type strlen = n;   // no check for '\0' termination in ptr;

            // if ptr is bigger than this, it cannot be a substring.
            if (strlen > m_size)
                return npos;

            // adjust the last pos where ptr can fit into this
            if (pos > (m_size - strlen))
                pos = m_size - strlen;

            for (size_type i = pos; i != npos; --i)
            {
                size_type j = i;
                size_type k = 0;
                while (j < m_size && k < strlen && m_data[j] == ptr[k])
                {
                    ++j;
                    ++k;
                }
                if (k == strlen)
                    return i;
            }

            return npos;
        }

        size_type rfind(value_type ch, size_type pos = npos) const
        {
            if (!m_size)
                return npos;
            
            if (pos > (m_size - 1))
                pos = m_size - 1;

            for (size_type i = pos; i != npos; --i)
            {
                if (m_data[i] == ch)
                    return i;
            }

            return npos;
        }

        /*  Searches the string for the first character that matches any
            of the characters specified in its arguments.
            When pos is specified, the search only includes characters
            at or after position pos, ignoring any possible occurrences
            before pos. Notice that it is enough for one single character
            of the sequence to match (not all of them).
            See string::find for a function that matches entire sequences.
        */
        size_type find_first_of(const container& str, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = str.length(); // without '\0'

            for (size_type i = pos; i < m_size; ++i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == str.m_data[j])
                        return i;
                }
            }

            return npos;
        }

        /*  Finds the first character equal to one of the characters in
            character string pointed to by ptr. The length of the string
            is determined by the first null character using Traits::length(ptr).
        */
        size_type find_first_of(const value_type* ptr, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = length(ptr); // without '\0'

            for (size_type i = pos; i < m_size; ++i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                        return i;
                }
            }

            return npos;
        }

        /*  Finds the first character equal to one of the characters
            in the range [ptr, ptr + n). This range can include null
            characters.
        */
        size_type find_first_of(const value_type* ptr, size_type pos, size_type n) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = n; // does not check for '\0' termination

            for (size_type i = pos; i < m_size; ++i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                        return i;
                }
            }

            return npos;
        }

        // Finds the first character equal to c.
        size_type find_first_of(value_type c, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            for (size_type i = pos; i < m_size; ++i)
            {
                if (m_data[i] == c)
                    return i;
            }

            return npos;
        }

        /*  Searches the string for the last character that matches
            any of the characters specified in its arguments.
            When pos is specified, the search only includes characters at or
            before position pos, ignoring any possible occurrences after pos.
        */
        size_type find_last_of(const container& str, size_type pos = npos) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = str.length();

            for (size_type i = pos; i != npos; --i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == str.m_data[j])
                        return i;
                }
            }

            return npos;
        }

        /*  Finds the last character equal to one of characters in character
            string pointed to by ptr. The length of the string is determined
            by the first null character using Traits::length(ptr).
        */
        size_type find_last_of(const value_type* ptr, size_type pos = npos) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = length(ptr); // without '\0'

            for (size_type i = pos; i != npos; --i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                        return i;
                }
            }

            return npos;
        }

        /*  Finds the last character equal to one of characters
            in range [ptr, ptr+n). This range can include null characters.
        */
        size_type find_last_of(const value_type* ptr, size_type pos, size_type n) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = n; // does not check for '\0' inside ptr

            for (size_type i = pos; i != npos; --i)
            {
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                        return i;
                }
            }

            return npos;
        }

        // Finds the last character equal to c.
        size_type find_last_of(value_type c, size_type pos = npos) const
        {
            if (!m_size)
                return npos;

            if (pos > (m_size - 1))
                pos = m_size - 1;

            for (size_type i = pos; i != npos; --i)
            {
                if (m_data[i] == c)
                    return i;
            }

            return npos;
        }

        /*  Searches the string for the first character that does
            not match any of the characters specified in its arguments.
            When pos is specified, the search only includes characters
            at or after position pos, ignoring any possible occurrences
            before that character.
        */
        size_type find_first_not_of(const container& str, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = str.length(); // without '\0'

            for (size_type i = pos; i < m_size; ++i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == str.m_data[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        /*  Finds the first character equal to none of characters in character
            string pointed to by ptr. The length of the string is determined
            by the first null character using Traits::length(ptr).
        */
        size_type find_first_not_of(const value_type* ptr, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = length(ptr); // without '\0'

            for (size_type i = pos; i < m_size; ++i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        /*  Finds the first character equal to none of characters
            in range [ptr, ptr+n). This range can include null characters.
        */
        size_type find_first_not_of(const value_type* ptr, size_type pos, size_type n) const
        {
            if (pos >= m_size)
                return npos;

            size_type strlen = n; // does not check for '\0' inside ptr

            for (size_type i = pos; i < m_size; ++i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        // Finds the first character not equal to c.
        size_type find_first_not_of(value_type c, size_type pos = 0) const
        {
            if (pos >= m_size)
                return npos;

            for (size_type i = pos; i < m_size; ++i)
            {
                if (m_data[i] != c)
                    return i;
            }

            return npos;
        }

        /*  Searches the string for the last character that does not match
            any of the characters specified in its arguments.
            When pos is specified, the search only includes characters at or
            before position pos, ignoring any possible occurrences after pos.
        */
        size_type find_last_not_of(const container& str, size_type pos = npos) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = str.length(); // without '\0'

            for (size_type i = pos; i != npos; --i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == str.m_data[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        /*  Finds the last character equal to none of characters in character
            string pointed to by ptr. The length of the string is determined
            by the first null character using Traits::length(ptr).
        */
        size_type find_last_not_of(const value_type* ptr, size_type pos = npos) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = length(ptr); // without '\0'

            for (size_type i = pos; i != npos; --i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        /*  Finds the last character equal to none of characters in the
            range [ptr, ptr + n). This range can include null characters.
        */
        size_type find_last_not_of(const value_type* ptr, size_type pos, size_type n) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            size_type strlen = n; // does not check for '\0' inside ptr

            for (size_type i = pos; i != npos; --i)
            {
                bool found = false;
                for (size_type j = 0; j < strlen; ++j)
                {
                    if (m_data[i] == ptr[j])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    return i;
            }

            return npos;
        }

        // Finds the last character not equal to c.
        size_type find_last_not_of(value_type c, size_type pos = npos) const
        {
            if (pos >= m_size)
                pos = m_size - 1;

            for (size_type i = pos; i != npos; --i)
            {
                if (m_data[i] != c)
                    return i;
            }

            return npos;
        }

        /*  Returns a newly constructed string object with its value
            initialized to a copy of a substring of this object.
            The substring is the portion of the object that starts
            at character position pos and spans len characters
            (or until the end of the string, whichever comes first).

            pos: Position of the first character to be copied as a substring.
                 If this is equal to the string length, the function returns
                 an empty string. If this is greater than the string length,
                 it throws out_of_range.
            Note: The first character is denoted by a value of 0 (not 1).

            len: Number of characters to include in the substring
            (if the string is shorter, as many characters as possible
            are used). A value of string::npos indicates all characters
            until the end of the string.
        */
        container substr(size_type pos = 0, size_type len = npos) const
        {
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            return container(&m_data[pos], &m_data[pos + len]);
        }

        

        /*  Compares the value of this string to the sequence of characters
            specified by its arguments.

            str: Another string object, used entirely (or partially)
                 as the comparing string.

            Returns a signed integral indicating the relation between
            the strings:
                0: They compare equal
               <0: Either the value of the first character that does not match
                   is lower in the compared string, or all compared characters
                   match but the compared string is shorter.
               >0: Either the value of the first character that does not match
                   is greater in the compared string, or all compared characters
                   match but the compared string is longer.
        */
        int compare(const container& str) const
        {
            size_type strlen = str.length(); // without '\0'
            size_type len = strlen;

            if (len > m_size)
                len = m_size;

            size_type i = 0;
            while (i < len && m_data[i] == str.m_data[i])
                ++i;

            if (i < len)
                return (m_data[i] < str.m_data[i]) ? -1 : (m_data[i] > str.m_data[i]);
            else
                return (m_size < strlen) ? -1 : (m_size > strlen);
        }


        /*  Compares the value of this string to the sequence of characters
            specified by its arguments.

            pos: Position of the first character in the compared string.
                 If this is greater than the string length, it throws
                 out_of_range.
            Note: The first character is denoted by a value of 0 (not 1).

            len: Length of compared string (if the string is shorter, as many
                 characters as possible). A value of string::npos indicates
                 all characters until the end of the string.

            str: Another string object, used entirely (or partially)
                 as the comparing string.

            Returns a signed integral indicating the relation between
            the strings:
                0: They compare equal
               <0: Either the value of the first character that does not match
                   is lower in the compared string, or all compared characters
                   match but the compared string is shorter.
               >0: Either the value of the first character that does not match
                   is greater in the compared string, or all compared characters
                   match but the compared string is longer.
        */

        int compare(size_type pos, size_type len, const container& str) const
        {
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type strlen = str.length(); // without '\0'

            size_type minlen = strlen;  // cannot change len due to final
            if (minlen > m_size)        // compare with strlen to decide
                minlen = m_size;        // for inequality

            size_type i = 0;
            while (i < minlen && m_data[pos + i] == str.m_data[i])
                ++i;

            if (i < minlen)
                return (m_data[pos + i] < str.m_data[i]) ? -1 : (m_data[pos + i] > str.m_data[i]);
            else
                return (len < strlen) ? -1 : (len > strlen);
        }


        /*  subpos, sublen:
                Same as pos and len above, but for the comparing string.
        */
        int compare(size_type pos, size_type len, const container& str, size_type subpos, size_type sublen) const
        {
            if (pos > m_size || subpos > str.m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            if (sublen > str.m_size - subpos)
                sublen = str.m_size - subpos;

            size_type minlen = len;     // cannot change len due to final
            if (minlen > sublen)        // compare with sublen to decide
                minlen = sublen;        // for inequality

            size_type i = 0;
            while (i < minlen && m_data[pos + i] == str.m_data[subpos + i])
                ++i;

            if (i < minlen)
                return (m_data[pos + i] < str.m_data[subpos + i]) ? -1 : (m_data[pos + i] > str.m_data[subpos + i]);
            else
                return (len < sublen) ? -1 : (len > sublen);
        }

        /*  Compares the value of this string to the sequence of characters
            specified by its arguments.
        */
        int compare(const value_type* ptr) const
        {
            size_type strlen = length(ptr); // without '\0'
            
            size_type len = strlen;
            if (len > m_size)
                len = m_size;

            size_type i = 0;
            while (i < len && m_data[i] == ptr[i])
                ++i;

            if (i < len)
                return (m_data[i] < ptr[i]) ? -1 : (m_data[i] > ptr[i]);
            else
                return (m_size < strlen) ? -1 : (m_size > strlen);
        }

        /*  Compares the value of this string to the sequence of characters
            specified by its arguments.
        */
        int compare(size_type pos, size_type len, const value_type* ptr) const
        {
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type strlen = length(ptr); // without '\0'

            size_type minlen = strlen;  // cannot change len due to final
            if (minlen > m_size)        // compare with strlen to decide
                minlen = m_size;        // for inequality

            size_type i = 0;
            while (i < minlen && m_data[pos + i] == ptr[i])
                ++i;

            if (i < minlen)
                return (m_data[pos + i] < ptr[i]) ? -1 : (m_data[pos + i] > ptr[i]);
            else
                return (len < strlen) ? -1 : (len > strlen);
        }

        /*
            pos: Position of the first character in the compared string.
                 If this is greater than the string length, it throws
                 out_of_range.
            Note: The first character is denoted by a value of 0 (not 1).

            len: Length of compared string (if the string is shorter, as many
                 characters as possible). A value of string::npos indicates
                 all characters until the end of the string.

            ptr: Pointer to string array used as the comparing string.
              n: The first n characters in the array are used as
                 the comparing string.

            Returns a signed integral indicating the relation between
            the strings:
                0: They compare equal
               <0: Either the value of the first character that does not match
                   is lower in the compared string, or all compared characters
                   match but the compared string is shorter.
               >0: Either the value of the first character that does not match
                   is greater in the compared string, or all compared characters
                   match but the compared string is longer.
        */
        int compare(size_type pos, size_type len, const value_type* ptr, size_type n) const
        {
            if (pos > m_size)
                throw stl::exception("out of valid range");

            if (len > m_size - pos)
                len = m_size - pos;

            size_type minlen = len;     // cannot change len due to final
            if (minlen > n)             // compare with n to decide
                minlen = n;             // for inequality

            size_type i = 0;
            while (i < minlen && m_data[pos + i] == ptr[i])
                ++i;

            if (i < minlen)
                return (m_data[pos + i] < ptr[i]) ? -1 : (m_data[pos + i] > ptr[i]);
            else
                return (len < n) ? -1 : (len > n);
        }
    };  // class

    /*
    string operator+ (const string& lhs, const string& rhs);
    string operator+ (const string& lhs, const char*   rhs);
    string operator+ (const char*   lhs, const string& rhs);
    string operator+ (const string& lhs, char          rhs);
    string operator+ (char          lhs, const string& rhs);
    */


}  // namespace




//########################################################################
// Operators
//
////Concatenates two string objects.
//template<typename T, typename Allocator>
//stl::basic_string<T, Allocator> operator+(
//    const stl::basic_string<T, Allocator>& Left,
//    const stl::basic_string<T, Allocator>& Right)
//{
//    stl::basic_string<T> res(Left);
//    res += Right;
//    return res;
//}
//
//
//template<typename T, typename Allocator>
//stl::basic_string<T, Allocator> operator+(
//    const stl::basic_string<T, Allocator>& Left,
//    const T* Right)
//{
//    stl::basic_string<T> res(Left);
//    res += Right;
//    return res;
//}
//
//template<typename T, typename Allocator>
//stl::basic_string<T, Allocator> operator+(
//    const stl::basic_string<T, Allocator>& Left,
//    const T Right)
//{
//    stl::basic_string<T> res(Left);
//    res += Right;
//    return res;
//}
//
//template<typename T, typename Allocator>
//stl::basic_string<T, Allocator> operator+(
//    const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    stl::basic_string<T> res(Left);
//    res += Right;
//    return res;
//}
//
//template<typename T, typename Allocator>
//stl::basic_string<T, Allocator> operator+(
//    const T Left, const stl::basic_string<T, Allocator>& Right)
//{
//    stl::basic_string<T> res(1, Left);
//    res += Right;
//    return res;
//}
//
//
////Tests if the string object on the left side of the operator is not equal
////to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator!=(
//                const stl::basic_string<T, Allocator>& Left, 
//                const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) != 0;
//}
//
//template<typename T, typename Allocator>
//bool operator!=(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) != 0;
//}
//
//
//template<typename T, typename Allocator>
//bool operator!=(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) != 0;
//}
//
////Tests if the string object on the left side of the operator is equal to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator==(
//                const stl::basic_string<T, Allocator>& Left, 
//                const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) == 0;
//}
//
//template<typename T, typename Allocator>
//bool operator==(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) == 0;
//}
//
//template<typename T, typename Allocator>
//bool operator==(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) == 0;
//}
//
////Tests if the string object on the left side of the operator is less than to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator<(
//                const stl::basic_string<T, Allocator>& Left, 
//                const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) < 0;
//}
//
//template<typename T, typename Allocator>
//bool operator<(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) < 0;
//}
//
//
//template<typename T, typename Allocator>
//bool operator<(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) > 0;
//}
//
//
//
////Tests if the string object on the left side of the operator is less than or equal to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator<=(
//                const stl::basic_string<T, Allocator>& Left, 
//                const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) <= 0;
//}
//
//template<typename T, typename Allocator>
//bool operator<=(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) <= 0;
//}
//
//
//
//
//template<typename T, typename Allocator>
//bool operator<=(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) >= 0;
//}
//
////A template function that writes a string into the output stream.
//template<typename T, typename Allocator>
//std::basic_ostream<T>& operator<<(
//    std::basic_ostream<T>& Ostr, const stl::basic_string<T, Allocator>& str)
//{
//    Ostr << str.c_str();
//    return Ostr;
//}
//
//
////Tests if the string object on the left side of the operator is greater
////than to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator>(
//               const stl::basic_string<T, Allocator>& Left, 
//               const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) > 0;
//}
//
//template<typename T, typename Allocator>
//bool operator>(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) > 0;
//}
//
//
//template<typename T, typename Allocator>
//bool operator>(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) < 0;
//}
//
//
////Tests if the string object on the left side of the operator is greater
////than or equal to the string object on the right side.
//template<typename T, typename Allocator>
//bool operator>=(
//                const stl::basic_string<T, Allocator>& Left, 
//                const stl::basic_string<T, Allocator>& Right)
//{
//    return Left.compare(Right) >= 0;
//}
//
//template<typename T, typename Allocator>
//bool operator>=(const stl::basic_string<T, Allocator>& Left, const T* Right)
//{
//    return Left.compare(Right) >= 0;
//}
//
//
//template<typename T, typename Allocator>
//bool operator>=(const T* Left, const stl::basic_string<T, Allocator>& Right)
//{
//    return Right.compare(Left) <= 0;
//}
//
////A template function that reads a string from an input stream.
//template<typename T, typename Allocator>
//std::basic_istream<T>& operator>>(
//    std::basic_istream<T>& Istr, stl::basic_string<T, Allocator>& Right)
//{
//    std::basic_string<T> chunk;
//    Istr >> chunk;
//    Right += chunk.c_str();
//    return Istr;
//}
//
////Specialized template function
////Exchanges the arrays of characters of two strings.
//template<typename T, typename Allocator>
//void swap(
//          stl::basic_string<T, Allocator>& Left, 
//          stl::basic_string<T, Allocator>& Right)
//{
//    Left.swap(Right);
//}

#endif // __basic_string_hpp__
