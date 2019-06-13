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

#ifndef __vector_hpp__
#define __vector_hpp__


#include "iterator.hpp"
#include "exception.hpp"
#include "memory.hpp"
#include "memmanip.hpp"
#include "algorithm.hpp"


namespace stl
{
    template<typename container>
    struct vector_iterator_base
    {
        container*                      m_cont;
        typename container::size_type   m_pos;
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
        friend class stl::vector<typename container::value_type, typename container::allocator_type>;
        friend class stl::vector_const_iterator<container>;

    private:
        vector_iterator(container* cont, size_type pos)
        {
            // g++: m_cont was not declared in this scope
            this->m_cont = cont;
            this->m_pos = pos;
        }

    public:
        vector_iterator()
        {
            this->m_cont = 0;
            this->m_pos = 0;
        }


        vector_iterator(const vector_iterator& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        ~vector_iterator()
        {
        }

        vector_iterator& operator=(const vector_iterator& it)
        {
            if (this != &it)
            {
                this->m_cont = it.m_cont;
                this->m_pos = it.m_pos;
            }

            return *this;
        }

        reference operator*() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont->m_data + this->m_pos);
        }

        pointer operator->() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont + this->m_pos);
        }

        vector_iterator& operator++()
        {
            ++this->m_pos;
            return *this;
        }

        vector_iterator operator++(int)
        {
            vector_iterator<container> tmp = *this;
            ++this->m_pos;
            return tmp;
        }

        vector_iterator& operator--()
        {
            --this->m_pos;
            return *this;
        }

        vector_iterator operator--(int)
        {
            vector_iterator<container> tmp = *this;
            --this->m_pos;
            return tmp;
        }

        vector_iterator& operator+=(difference_type off)
        {
            this->m_pos += off;
            return *this;
        }

        vector_iterator operator+(difference_type off) const
        {
            vector_iterator<container> tmp = *this;
            return (tmp += off);
        }

        vector_iterator& operator-=(difference_type off)
        {
            this->m_pos -= off;
            return *this;
        }

        vector_iterator operator-(difference_type off) const
        {
            vector_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const vector_iterator& it) const
        {
            return static_cast<difference_type>(this->m_pos - it.m_pos);
        }

        bool operator==(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos == it.m_pos);
        }

        bool operator!=(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos != it.m_pos);
        }

        bool operator<(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos < it.m_pos);
        }

        bool operator>(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos > it.m_pos);
        }

        bool operator<=(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos <= it.m_pos);
        }

        bool operator>=(const vector_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont->m_data + this->m_pos + off);
        }
    };  // vector_iterator


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
        friend class vector<typename container::value_type, typename container::allocator_type>;


    private:
        vector_const_iterator(container* cont, size_type pos)
        {
            // g++: m_cont was not declared in this scope
            this->m_cont = cont;
            this->m_pos = pos;
        }

    public:
        vector_const_iterator()
        {
            this->m_cont = 0;
            this->m_pos = 0;
        }

        vector_const_iterator(const vector_const_iterator& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        vector_const_iterator(const vector_iterator<container>& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        ~vector_const_iterator()
        {
        }

        vector_const_iterator& operator=(const vector_const_iterator& it)
        {
            if (this != &it)
            {
                this->m_cont = it.m_cont;
                this->m_pos = it.m_pos;
            }
            return *this;
        }

        vector_const_iterator& operator=(const vector_iterator<container>& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;

            return *this;
        }

        reference operator*() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont + this->m_pos);
        }

        pointer operator->() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont + this->m_pos);
        }

        vector_const_iterator& operator++()
        {
            ++this->m_pos;
            return *this;
        }

        vector_const_iterator operator++(int)
        {
            vector_const_iterator<container> tmp = *this;
            ++this->m_pos;
            return tmp;
        }

        vector_const_iterator& operator--()
        {
            --this->m_pos;
            return *this;
        }

        vector_const_iterator operator--(int)
        {
            vector_const_iterator<container> tmp = *this;
            --this->m_pos;
            return tmp;
        }

        vector_const_iterator& operator+=(difference_type off)
        {
            this->m_pos += off;
            return *this;
        }

        vector_const_iterator operator+(difference_type off) const
        {
            vector_const_iterator<container> tmp = *this;
            return (tmp += off);
        }

        vector_const_iterator& operator-=(difference_type off)
        {
            this->m_pos -= off;
            return *this;
        }

        vector_const_iterator operator-(difference_type off) const
        {
            vector_const_iterator<container> tmp = *this;
            return tmp -= off;
        }

        difference_type operator-(const vector_const_iterator& it) const
        {
            return static_cast<difference_type>(this->m_pos - it.m_pos);
        }

        bool operator==(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos == it.m_pos);
        }

        bool operator!=(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos != it.m_pos);
        }

        bool operator<(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos < it.m_pos);
        }

        bool operator>(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos > it.m_pos);
        }

        bool operator<=(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos <= it.m_pos);
        }

        bool operator>=(const vector_const_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos >= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont + this->m_pos + off);
        }
    };  // vector_const_iterator


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
        friend class vector<typename container::value_type, typename container::allocator_type>;
        friend class vector_const_reverse_iterator<container>;


    private:
        vector_reverse_iterator(container* cont, size_type pos)
        {
            // g++: m_cont was not declared in this scope
            this->m_cont = cont;
            this->m_pos = pos;
        }

    public:
        vector_reverse_iterator()
        {
            this->m_cont = 0;
            this->m_pos = 0;
        }

        vector_reverse_iterator(const vector_reverse_iterator& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        ~vector_reverse_iterator()
        {
        }

        vector_reverse_iterator& operator=(const vector_reverse_iterator& it)
        {
            if (this != &it)
            {
                this->m_cont = it.m_cont;
                this->m_pos = it.m_pos;
            }
            return *this;
        }

        reference operator*() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont->m_data + this->m_pos);
        }

        pointer operator->() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont->m_data + this->m_pos);
        }

        vector_reverse_iterator& operator++()
        {
            --this->m_pos;
            return *this;
        }

        vector_reverse_iterator operator++(int)
        {
            vector_reverse_iterator<container> tmp = *this;
            --this->m_pos;
            return tmp;
        }

        vector_reverse_iterator& operator--()
        {
            ++this->m_pos;
            return *this;
        }

        vector_reverse_iterator operator--(int)
        {
            vector_reverse_iterator<container> tmp = *this;
            ++this->m_pos;
            return tmp;
        }

        vector_reverse_iterator& operator+=(difference_type off)
        {
            this->m_pos -= off;
            return *this;
        }

        vector_reverse_iterator operator+(difference_type off) const
        {
            vector_reverse_iterator<container> tmp = *this;
            return (tmp += off);
        }

        vector_reverse_iterator& operator-=(difference_type off)
        {
            this->m_pos += off;
            return *this;
        }

        vector_reverse_iterator operator-(difference_type off) const
        {
            vector_reverse_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const vector_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - this->m_pos);
        }

        bool operator==(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (it.m_pos == this->m_pos);
        }

        bool operator!=(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (it.m_pos != this->m_pos);
        }

        bool operator<(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos > it.m_pos);
        }

        bool operator>(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos < it.m_pos);
        }

        bool operator<=(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos >= it.m_pos);
        }

        bool operator>=(const vector_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont + this->m_pos - off);
        }
    };  // vector_reverse_iterator


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
        friend class vector<typename container::value_type, typename container::allocator_type>;


    private:
        vector_const_reverse_iterator(container* cont, size_type pos)
        {
            // g++: m_cont was not declared in this scope
            this->m_cont = cont;
            this->m_pos = pos;
        }

    public:
        vector_const_reverse_iterator()
        {
            this->m_cont = 0;
            this->m_pos = 0;
        }

        vector_const_reverse_iterator(const vector_const_reverse_iterator& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        ~vector_const_reverse_iterator()
        {
        }

        vector_const_reverse_iterator& operator=(const vector_const_reverse_iterator& it)
        {
            if (this != &it)
            {
                this->m_cont = it.m_cont;
                this->m_pos = it.m_pos;
            }
            return *this;
        }

        vector_const_reverse_iterator& operator=(const vector_reverse_iterator<container>& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;

            return *this;
        }

        vector_const_reverse_iterator(const vector_reverse_iterator<container>& it)
        {
            this->m_cont = it.m_cont;
            this->m_pos = it.m_pos;
        }

        reference operator*() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return *(this->m_cont->m_data + this->m_pos);
        }

        pointer operator->() const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont->m_data + this->m_pos);
        }

        vector_const_reverse_iterator& operator++()
        {
            --this->m_pos;
            return *this;
        }

        vector_const_reverse_iterator operator++(int)
        {
            vector_const_reverse_iterator<container> tmp = *this;
            --this->m_pos;
            return tmp;
        }

        vector_const_reverse_iterator& operator--()
        {
            ++this->m_pos;
            return *this;
        }

        vector_const_reverse_iterator operator--(int)
        {
            vector_const_reverse_iterator<container> tmp = *this;
            ++this->m_pos;
            return tmp;
        }

        vector_const_reverse_iterator& operator+=(difference_type off)
        {
            this->m_pos -= off;
            return *this;
        }

        vector_const_reverse_iterator operator+(difference_type off) const
        {
            vector_const_reverse_iterator<container> tmp = *this;
            return (tmp += off);
        }

        vector_const_reverse_iterator& operator-=(difference_type off)
        {
            this->m_pos += off;
            return *this;
        }

        vector_const_reverse_iterator operator-(difference_type off) const
        {
            vector_const_reverse_iterator<container> tmp = *this;
            return (tmp -= off);
        }

        difference_type operator-(const vector_const_reverse_iterator& it) const
        {
            return static_cast<difference_type>(it.m_pos - this->m_pos);
        }

        bool operator==(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos == it.m_pos);
        }

        bool operator!=(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos != it.m_pos);
        }

        bool operator<(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos > it.m_pos);
        }

        bool operator>(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos < it.m_pos);
        }

        bool operator<=(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos >= it.m_pos);
        }

        bool operator>=(const vector_const_reverse_iterator& it) const
        {
#ifdef DEBUG
            if (this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_pos <= it.m_pos);
        }

        reference operator[](difference_type off) const
        {
            if (!this->m_cont)
                throw stl::exception("invalid iterator");

            return (this->m_cont->m_data + this->m_pos - off);
        }
    };  // vector_const_reverse_iterator


    template<typename T, typename Allocator = stl::allocator<T> >
    class vector
    {
    public:
        typedef          vector<T, Allocator>           container;

        // types:
        typedef typename Allocator::value_type          value_type;
        typedef typename Allocator::size_type           size_type;
        typedef typename Allocator::difference_type     difference_type;
        typedef Allocator                               allocator_type;

        typedef typename Allocator::reference           reference;
        typedef typename Allocator::const_reference     const_reference;
        typedef typename Allocator::pointer             pointer;
        typedef typename Allocator::const_pointer       const_pointer;

        typedef vector_iterator<container>              iterator;
        typedef vector_const_iterator<container>        const_iterator;
        typedef vector_reverse_iterator<container>      reverse_iterator;
        typedef vector_const_reverse_iterator<container> const_reverse_iterator;

        friend class vector_iterator<container>;
        friend class vector_const_iterator<container>;
        friend class vector_reverse_iterator<container>;
        friend class vector_const_reverse_iterator<container>;

    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;

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
            // safety: only string needs a +1 element for '\0';
            if (size > m_capacity)
                throw stl::exception("out of valid range");
#endif

            if (size < m_size)
            {
                value_type* unused = m_data + size;
                size_type count = m_size - size;
                stl::mem_destroy(&unused, count, m_allocator);
            }
            m_size = size;
        }

    public:
        vector()
        {
            init();
        }

        explicit vector(size_type n, const T& c = T())
        {
            init();
            assign(n, c);
        }

        template <typename InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            init();
            assign(first, last);
        }

        vector(const container& tc)
        {
            init();
            assign(tc);
        }

        ~vector()
        {
            if (m_data)
            {
                stl::mem_destroy(&m_data, m_size, m_allocator);
                m_allocator.deallocate(m_data, 0);
            }

            m_data = 0;
            m_size = 0;
            m_capacity = 0;
        }

        container& operator=(const container& x)
        {
            return assign(x);
        }

        container& assign(const container& tc)
        {
            //self assignment
            if (this != &tc)
            {
                size_type size = tc.size();

                if (size > 0)
                {
                    grow(size);

                    stl::mem_copy(m_data, m_size, tc.m_data, size, m_allocator);
                }
                
                endof(size);
            }

            return *this;
        }

        void assign(size_type count, const value_type& val)
        {
            if (count > 0)
            {
                // Is the address inside this container ?
                if (m_data <= &val && (m_data + m_size) > &val)
                {
                    T temp(val);

                    // can relocate m_data and invalidate &val
                    grow(count);

                    stl::mem_set(m_data, temp, count * sizeof(value_type), m_allocator);
                }
                else// Address is outside this container.
                {
                    grow(count);

                    stl::mem_set(m_data, val, count * sizeof(value_type), m_allocator);
                }
            }

            endof(count);
        }

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            assign_(first, last);
        }

    private:
        inline void assign_(iterator& first, iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (first.m_cont == this)
                {
                    stl::mem_move(m_data, m_size, first.m_cont->m_data + first.m_pos, dist, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, first.m_cont->m_data + first.m_pos, dist, m_allocator);
                }
            }

            endof(dist);
        }

        inline void assign_(const_iterator& first, const_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if n < 0 then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
                {
                    stl::mem_move(m_data, m_size, first.m_cont->m_data + first.m_pos, dist, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, first.m_cont->m_data + first.m_pos, dist, m_allocator);
                }
            }

            endof(dist);
        }

        inline void assign_(value_type* first, value_type* last)
        {
            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                // Is range inside this container ?
                if (m_data <= first && (m_data + m_size) > first)
                {
                    stl::mem_move(m_data, m_size, first, dist, m_allocator);
                }
                else
                {
                    stl::mem_copy(m_data, m_size, first, dist, m_allocator);
                }
            }

            endof(dist);
        }

        inline void assign_(const value_type* first, const value_type* last)
        {
            assign_(const_cast<value_type*>(first), const_cast<value_type*>(last));
        }

        template <typename InputIterator>
        void assign_(InputIterator& first, InputIterator& last)
        {
            assign_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        template<typename InputIterator>
        inline void assign_(InputIterator& first, InputIterator& last, stl::forward_iterator_tag)
        {
            /*  Test with a.assign(b.rbegin(), b.rend());
                if last < first then let it blow up.
            */
            size_type dist = static_cast<size_type>(stl::distance(first, last));

            if (dist > 0)
            {
                const T& check = *first;

                // Is the range inside this container ?
                if (m_data <= &check && (m_data + m_size) > &check)
                {
                    container temp;
                    temp.assign(first, last);

                    // for safety, although could not invalidate the input for this case
                    grow(dist);

                    stl::mem_move(m_data, m_size, &temp.front(), dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(dist);

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        T* d1 = m_data + i;
                        const T& s1 = *first;
                        if (d1 != &s1)
                        {
                            // cannot destroy invalid objects in the destination
                            if (i < m_size)
                            {
                                m_allocator.destroy(d1);
                            }

                            m_allocator.construct(d1, s1);
                        }
                    }
                }
            }

            endof(dist);
        }

        template<typename InputIterator>
        inline void assign_(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            /*  Ex: a.assign(5, 0.5f);
                if n < 0 then let it blow up.
             */             
            size_type size = static_cast<size_type>(n);
            if (size > 0)
            {
                grow(size);

                // Not a self assignment as value is a temporary copy.
                stl::mem_set(m_data, value, size * sizeof(value_type), m_allocator);
            }

            endof(size);
        }

    public:
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
            if (sz > m_size)
            {
                grow(sz);

                // Not a self assignment as c is a temporary copy.
                stl::mem_set(m_data + m_size, c, (sz - m_size) * sizeof(value_type), m_allocator);
            }

            endof(sz);
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
        void push_back(const value_type& x)
        {
            // Is x address inside this container ?
            if (m_data <= &x && (m_data + m_size) > &x)
            {
                T temp(x);

                if (m_size == m_capacity)
                {
                    // can relocate m_data and invalidate &x
                    if (!m_capacity)
                        grow(2);
                    else
                        grow(m_capacity * 2);
                }

                m_allocator.construct(&m_data[m_size], temp);
            }
            else// x address is outside this container.
            {
                if (m_size == m_capacity)
                {
                    if (!m_capacity)
                        grow(2);
                    else
                        grow(m_capacity * 2);
                }

                m_allocator.construct(&m_data[m_size], x);
            }

            endof(m_size + 1);
        }

        // 23.2.4.3 modifiers (vector):
        void pop_back()
        {
            if (m_size == 0) throw stl::exception("vector is empty");
            
            endof(m_size - 1);
        }
        
        iterator insert(iterator position, const T& x)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            size_type size = m_size + 1;
            size_type p = position.m_pos;

            // Is x address inside this container ? 
            if (m_data <= &x && (m_data + m_size) > &x)
            {
                T temp(x);

                // can relocate m_data and invalidate &x
                grow(size);

                // move content unless insert position is end()
                if (position.m_pos < m_size)
                {
                    // mem_move cannot destroy invalid objects in the destination
                    size_type dst_valid_sz = 0;
                    if (p + 1 < m_size)
                    {
                        dst_valid_sz = m_size - p - 1;
                    }

                    stl::mem_move(m_data + p + 1, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                }

                m_allocator.construct(&m_data[p], temp);
            }
            else// x address is outside this container
            {
                grow(size);

                // move content unless insert position is end()
                if (position.m_pos < m_size)
                {
                    // mem_move cannot destroy invalid objects in the destination
                    size_type dst_valid_sz = 0;
                    if (p + 1 < m_size)
                    {
                        dst_valid_sz = m_size - p - 1;
                    }

                    stl::mem_move(m_data + p + 1, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                }

                m_allocator.construct(&m_data[p], x);
            }
            
            endof(size);

            return position;
        }

        void insert(iterator position, size_type n, const T& x)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (n)
            {
                size_type size = m_size + n;
                size_type p = position.m_pos;

                // Is x address inside this container ?
                if (m_data <= &x && (m_data + m_size) > &x)
                {
                    T temp(x);

                    // can relocate m_data and invalidate &x
                    grow(size);

                    // move content unless insert position is end()
                    if (position.m_pos < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + n < m_size)
                        {
                            dst_valid_sz = m_size - p - n;
                        }

                        stl::mem_move(m_data + p + n, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_set(m_data + p, temp, n * sizeof(value_type), m_allocator);
                }
                else// x address is outside this container
                {
                    grow(size);

                    // move content unless insert position is end()
                    if (position.m_pos < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + n < m_size)
                        {
                            dst_valid_sz = m_size - p - n;
                        }

                        stl::mem_move(m_data + p + n, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_set(m_data + p, x, n * sizeof(value_type), m_allocator);
                }

                endof(size);
            }
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

                grow(size);

                // Is the range inside this container ?
                if (first.m_cont == this)
                {
                    container temp;
                    temp.assign(first, last);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, &temp.front(), dist, m_allocator);
                }
                else// range is outside this container
                {
                    // move content unless insert positions is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, first.m_cont->m_data + first.m_pos, dist, m_allocator);
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

//#define VEC_USE_BUFFER
#ifdef VEC_USE_BUFFER
            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                size_type p = position.m_pos;
                size_type size = m_size + dist;

                grow(size);

                // Is the range inside this container ?
                if (first.m_cont == this)
                {
                    container temp;
                    temp.assign(first, last);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, &temp.front(), dist, m_allocator);
                }
                else// range is outside this container
                {
                    // move content unless insert positions is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, first.m_cont->m_data + first.m_pos, dist, m_allocator);
                }

                endof(size);
            }
#else
            // if last < first then let it blow up
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                // uses the fast no_buffer method
                replace_nb_(position.m_pos, 0, *first.m_cont, first.m_pos, dist);
            }
#endif
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
//TODO: can be optimized by passing pointers (e.g. first.m_cont + first.m_pos, ..)
                    temp.assign(first, last);

                    // can relocate m_data and invalidate first,last pointers
                    grow(size);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, &temp.front(), dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, first, dist, m_allocator);
                }

                endof(size);
            }
        }

        inline void insert_(iterator& position, const value_type* first, const value_type* last)
        {
            insert_(position, const_cast<value_type*>(first), const_cast<value_type*>(last));
        }

        template<typename InputIterator>
        void insert_(iterator& position, InputIterator& first, InputIterator& last)
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
                    grow(size);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    stl::mem_copy(m_data + p, m_size - p, &temp.front(), dist, m_allocator);
                }
                else// range is outside this container
                {
                    grow(size);

                    // move content unless insert position is end()
                    if (p < m_size)
                    {
                        // mem_move cannot destroy invalid objects in the destination
                        size_type dst_valid_sz = 0;
                        if (p + dist < m_size)
                        {
                            dst_valid_sz = m_size - p - dist;
                        }

                        stl::mem_move(m_data + p + dist, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                    }

                    for (size_type i = 0; first != last; ++first, ++i)
                    {
                        m_allocator.construct(&m_data[p + i], *first);
                    }
                }

                endof(size);
            }
        }

        template<typename InputIterator>
        inline void insert_(iterator& position, InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            // allow to insert in position = end(), aka m_pos == m_size;
            if (position.m_cont != this || position.m_pos > m_size)
                throw stl::exception("invalid iterator");

            if (n)
            {
                size_type p = position.m_pos;
                size_type size = m_size + n;

                grow(size);

                // value is always passed by copy, cannot be a reference inside this container;

                // move content unless insert position is end()
                if (p < m_size)
                {
                    // mem_move cannot destroy invalid objects in the destination
                    size_type dst_valid_sz = 0;
                    if (p + n < m_size)
                    {
                        dst_valid_sz = m_size - p - n;
                    }

                    stl::mem_move(m_data + p + n, dst_valid_sz, m_data + p, (m_size - p), m_allocator);
                }

                stl::mem_set(m_data + p, value, n * sizeof(value_type), m_allocator);
                
                endof(size);
            }
        }


        /*  Usually doing insert from self with a buffer performs 2x slower
            compared with std::string, if not slower.
            My initial version still performed worse, so I adapted this code
            from Visual Studio 12.0/VC/include/xstring
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
                size_type dst_valid_sz1(0), dst_valid_sz2(0);
                if (p1 + n2 < m_size)
                {
                    dst_valid_sz1 = m_size - p1 - n2;
                    dst_valid_sz2 = m_size - p1;
                }
                else if (p1 < m_size)
                {
                    dst_valid_sz2 = m_size - p1;
                }

                stl::mem_move(m_data + p1 + n2, dst_valid_sz1,
                              m_data + p1 + n1, Nm, m_allocator);   // empty hole
                stl::mem_copy(m_data + p1, dst_valid_sz2,
                              str.m_data + p2, n2, m_allocator);    // fill hole
            }
            else if (n2 <= n1)
            {   // hole doesn't get larger, just copy in substring
                size_type dst_valid_sz1(0), dst_valid_sz2(0);
                if (p1 + n2 < m_size)
                {
                    dst_valid_sz2 = m_size - p1 - n2;
                    dst_valid_sz1 = m_size - p1;
                }
                else if (p1 < m_size)
                {
                    dst_valid_sz1 = m_size - p1;
                }

                stl::mem_move(m_data + p1, dst_valid_sz1,
                              m_data + p2, n2, m_allocator);        // fill hole
                stl::mem_move(m_data + p1 + n2, dst_valid_sz2,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
            }
            else if (p2 <= p1)
            {   // hole gets larger, substring begins before hole
                size_type dst_valid_sz1(0), dst_valid_sz2(0);
                if (p1 + n2 < m_size)
                {
                    dst_valid_sz1 = m_size - p1 - n2;
                    dst_valid_sz2 = m_size - p1;
                }
                else if (p1 < m_size)
                {
                    dst_valid_sz2 = m_size - p1;
                }

                stl::mem_move(m_data + p1 + n2, dst_valid_sz1,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1, dst_valid_sz2,
                              m_data + p2, n2, m_allocator);        // fill hole
            }
            else if (p1 + n1 <= p2)
            {   // hole gets larger, substring begins after hole
                size_type dst_valid_sz1(0), dst_valid_sz2(0);
                if (p1 + n2 < m_size)
                {
                    dst_valid_sz1 = m_size - p1 - n2;
                    dst_valid_sz2 = m_size - p1;
                }
                else if (p1 < m_size)
                {
                    dst_valid_sz2 = m_size - p1;
                }

                stl::mem_move(m_data + p1 + n2, dst_valid_sz1,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1, dst_valid_sz2,
                              m_data + (p2 + n2 - n1), n2,
                              m_allocator);                         // fill hole
            }
            else
            {   // hole gets larger, substring begins in hole
                size_type dst_valid_sz1(0), dst_valid_sz2(0), dst_valid_sz3(0);
                if (p1 < m_size)
                    dst_valid_sz1 = m_size - p1;
                if (p1 + n2 < m_size)
                    dst_valid_sz2 = m_size - p1 - n2;
                if (p1 + n1 < m_size)
                    dst_valid_sz3 = m_size - p1 - n1;

                stl::mem_move(m_data + p1, dst_valid_sz1,
                              m_data + p2, n1, m_allocator);        // fill old hole
                stl::mem_move(m_data + p1 + n2, dst_valid_sz2,
                              m_data + p1 + n1, Nm, m_allocator);   // move tail down
                stl::mem_move(m_data + p1 + n1, dst_valid_sz3,
                              m_data + p2 + n2, n2 - n1,
                              m_allocator);                         // fill rest of new hole
            }

            endof(size);

            return *this;
        }

    public:
        iterator erase(iterator position)
        {
            // cannot remove end() position
            if (position.m_cont != this || position.m_pos >= m_size)
                throw stl::exception("invalid iterator");

            size_type p = position.m_pos;

            stl::mem_move(m_data + p, m_size - p, m_data + p + 1, (m_size - p - 1), m_allocator);

            endof(m_size - 1);

            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first.m_cont != last.m_cont || first.m_cont != this)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);
            if (dist > 0)
            {
                stl::mem_move(m_data + first.m_pos, m_size - first.m_pos, m_data + last.m_pos, (m_size - last.m_pos), m_allocator);

                endof(m_size - dist);
            }

            return first;
        }

        void swap(container& ts)
        {
            stl::swap<pointer>(m_data, ts.m_data);
            stl::swap<size_type>(m_size, ts.m_size);
            stl::swap<size_type>(m_capacity, ts.m_capacity);
            stl::swap<Allocator>(m_allocator, ts.m_allocator);
        }

        void clear()
        {
            endof(0);
        }

        allocator_type get_allocator() const
        {
            return m_allocator;
        }
    };  // class

    
    template<typename T, typename Allocator>
    inline bool operator== (
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
    inline bool operator< (
        const stl::vector<T, Allocator>& Left,
        const stl::vector<T, Allocator>& Right)
    {
        return stl::lexicographical_compare(
            Left.begin(), Left.end(), Right.begin(), Right.end());
    }

    template<typename T, typename Allocator>
    inline bool operator!= (
        const stl::vector<T, Allocator>& Left,
        const stl::vector<T, Allocator>& Right)
    {
        return !(Left == Right);
    }

    template<typename T, typename Allocator>
    inline bool operator> (
        const stl::vector<T, Allocator>& Left,
        const stl::vector<T, Allocator>& Right)
    {
        return (Left != Right) && !(Left < Right);
    }

    template<typename T, typename Allocator>
    inline bool operator>= (
        const stl::vector<T, Allocator>& Left,
        const stl::vector<T, Allocator>& Right)
    {
        return !(Left < Right);
    }

    template<typename T, typename Allocator>
    inline bool operator<= (
        const stl::vector<T, Allocator>& Left,
        const stl::vector<T, Allocator>& Right)
    {
        return (Left < Right) || (Left == Right);
    }

    template<typename T, typename Allocator>
    void swap(
        stl::vector<T, Allocator>& Left,
        stl::vector<T, Allocator>& Right)
    {
        return Left.swap(Right);
    }

}  // namespace

#endif//__vector_hpp__
