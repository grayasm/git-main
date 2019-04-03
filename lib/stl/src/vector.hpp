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
#include <new>


namespace stl
{
    template<typename container>
    struct vector_iterator_base
    {
        container*                        m_cont;
        typename container::size_type    m_pos;
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
        friend class stl::vector_const_iterator<container>;

    private:
        vector_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        vector_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }


        vector_iterator(const vector_iterator& tc)
        {
            *this = tc;
        }

        ~vector_iterator()
        {
        }

        vector_iterator& operator=(const vector_iterator& tc)
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
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;


    private:
        vector_const_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        vector_const_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        vector_const_iterator(const vector_const_iterator& tc)
        {
            *this = tc;
        }

        vector_const_iterator(const vector_iterator<container>& tc)
        {
            *this = tc;
        }

        ~vector_const_iterator()
        {
        }

        vector_const_iterator& operator=(const vector_const_iterator& tc)
        {
            if (this != &tc)
            {
                base2::m_cont = tc.m_cont;
                base2::m_pos = tc.m_pos;
            }
            return *this;
        }

        vector_const_iterator& operator=(const vector_iterator<container>& tc)
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
            return static_cast<difference_type>(base2::m_pos - it.m_pos);
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
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;
        friend class vector_const_reverse_iterator<container>;


    private:
        vector_reverse_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        vector_reverse_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }


        vector_reverse_iterator(const vector_reverse_iterator& it)
        {
            *this = it;
        }

        ~vector_reverse_iterator()
        {
        }

        vector_reverse_iterator& operator=(const vector_reverse_iterator& it)
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
            return static_cast<difference_type>(it.m_pos - base2::m_pos);
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
        typedef typename stl::vector_iterator_base<container> base2;
        friend class vector<typename container::value_type, typename container::allocator_type>;


    private:
        vector_const_reverse_iterator(container* cont, size_type pos)
        {
            base2::m_cont = cont;
            base2::m_pos = pos;
        }

    public:
        vector_const_reverse_iterator()
        {
            base2::m_cont = 0;
            base2::m_pos = 0;
        }

        vector_const_reverse_iterator(const vector_const_reverse_iterator& it)
        {
            *this = it;
        }

        ~vector_const_reverse_iterator()
        {
        }

        vector_const_reverse_iterator& operator=(const vector_const_reverse_iterator& it)
        {
            if (this != &it)
            {
                base2::m_cont = it.m_cont;
                base2::m_pos = it.m_pos;
            }
            return *this;
        }

        vector_const_reverse_iterator& operator=(const vector_reverse_iterator<container>& it)
        {
            base2::m_cont = it.m_cont;
            base2::m_pos = it.m_pos;

            return *this;
        }

        vector_const_reverse_iterator(const vector_reverse_iterator<container>& it)
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
            return static_cast<difference_type>(it.m_pos - base2::m_pos);
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
    };  // vector_const_reverse_iterator
    

    //    ISO/IEC 14882:2003  $23.2.4 Class template vector
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
        typedef typename vector_iterator<container>                    iterator;
        typedef typename vector_const_iterator<container>            const_iterator;
        typedef typename vector_reverse_iterator<container>            reverse_iterator;
        typedef typename vector_const_reverse_iterator<container>   const_reverse_iterator;

    private:
        value_type*             m_data;
        size_type               m_size;
        size_type               m_capacity;
        allocator_type          m_allocator;

    private:
        void init()
        {
            m_data = 0;
            m_size = 0;
            m_capacity = 0;
            // m_allocator - default ctor;
        }

        void allocate(size_type cap)
        {
            pointer mem = 0;

            /* buy memory, no ctor() called */
            mem = m_allocator.allocate(cap);

            if (mem == 0)
                throw stl::exception("bad allocation");

            m_data = mem;
            m_capacity = cap;
        }

        void grow(size_type cap)
        {
            if (m_capacity >= cap) return;

            stl::mem_realloc(&mem, cap, m_data, m_size, m_allocator);
            
            m_data = mem;
            m_capacity = cap;
        }

        inline void endof(size_type size)
        {
            if (m_capacity < size) throw stl::exception("bad size");

            if (size < m_size)
            {
                value_type* unused = m_data + size;
                stl::mem_destroy<value_type>(&unused, m_size - size, m_allocator);
            }
            m_size = size;
        }

        void swap_range(size_type beg, size_type end)
        {
            if (beg < end)
            {
                for (size_type i = beg, j = end - 1; i < j; ++i, --j)
                {
                    //stl::swap<value_type>(m_data[i], m_data[j]);
                    stl::swap(m_data[i], m_data[j]);
                }
            }
        }


    public:       
        // $23.2.4.1 construct/copy/destroy:
        vector()
        {
            init();
            allocate(1);
            m_size = 0;
        }

        explicit vector(size_type n, const T& c = T())
        {
            init();
            allocate(1);
            assign(n, c);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last)
        {
            init();
            allocate(1);
            assign(first, last);
        }

        vector(const container& x)
            : m_allocator(x.get_allocator())
        {
            init();
            allocate(1);
            assign(x);
        }

        ~vector()
        {
            stl::mem_destroy<value_type>(&m_data, m_size, m_allocator);
            m_allocator.deallocate(m_data, 0);

            m_data = 0;
            m_size = 0;
            m_capacity = 0;
        }

        container& operator=(const container& x)
        {
            return assign(x);
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
                    grow(size);

                    stl::mem_copy<value_type>(m_data, tc.m_data, size * sizeof(value_type));
                }
                
                endof(size);
            }

            return *this;
        }

        void assign(size_type count, const value_type& val)
        {
            if (count > 0)
            {
                grow(count);

                stl::mem_set<value_type>(m_data, val, count * sizeof(value_type));
            }

            endof(count);
        }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            assign_(first, last);
        }

    private:
        container& assign_(const value_type* first, const value_type* last)
        {
            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                // self assignment
                if (m_size > 0 && m_data <= first && (m_data + m_size) > first)
                {
                    stl::mem_move<value_type>(m_data, first, dist * sizeof(value_type));
                }
                else
                {
                    stl::mem_copy<value_type>(m_data, first, dist * sizeof(value_type));
                }
            }

            endof(dist);

            return *this;
        }

        container& assign_(const iterator& first, const iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
                {
                    stl::mem_move<value_type>(m_data, &((*first.m_cont)[first.m_pos]), dist * sizeof(value_type));
                }
                else
                {
                    stl::mem_copy<value_type>(m_data, &((*first.m_cont)[first.m_pos]), dist * sizeof(value_type));
                }
            }

            endof(dist);

            return *this;
        }

        container& assign_(const const_iterator& first, const const_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if n < 0 then let it explode.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
                {
                    stl::mem_move<value_type>(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
                }
                else
                {
                    stl::mem_copy<value_type>(m_data, &((*first.m_cont)[first.m_pos]), dist * numbytes);
                }
            }

            endof(dist);

            return *this;
        }
        
        template<typename InputIterator>
        container& assign_(InputIterator first, InputIterator last, stl::forward_iterator_tag)
        {
            difference_type dist = stl::distance(first, last);

            if (dist > 0)
            {
                grow(dist);

                for (size_type i = 0; first != last; ++first, ++i)
                {
                    T* d1 = m_data + i;
                    const T& s1 = *first;
                    if (d1 != &s1)
                    {
                        d1->T::~T(); //faults when object at d1 was not yet created;
                        new(d1)T(s1);
                    }
                }
            }

            endof(dist);

            return *this;
        }


        template<typename InputIterator>
        container& assign_(InputIterator n, InputIterator value, stl::input_iterator_tag)
        {
            // if n < 0 then let it blow up.
            size_type dist = static_cast<size_type>(n);
            if (dist > 0)
            {
                grow(dist);

                stl::mem_set<value_type>(m_data, value, dist * sizeof(value_type));
            }

            endof(dist);

            return *this;
        }

        template <class InputIterator>
        container& assign_(InputIterator first, InputIterator last)
        {
            return assign_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

#if 0
        container& assign_impl(const reverse_iterator& first, const reverse_iterator& last)
        {
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow than to cover it up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
                {
                    //TODO: see below, check for correctness
                    //erase(0, last.m_pos + 1);
                }
                else
                {
                    //TODO: copying in reverse means [0,1,2,3,4,5] -> [5,4,3,2,1,0] ; check if this is done correctly!!!
                    stl::mem_copy<value_type>(m_data, &((*last.m_cont)[last.m_pos + 1]), dist * sizeof(value_type));
                }

                swap_range(0, dist);
            }

            endof(dist);

            return *this;
        }

        container& assign_impl(const const_reverse_iterator& first, const const_reverse_iterator& last)
        {
            //validate containers
            if (first.m_cont != last.m_cont || first.m_cont == 0)
                throw stl::exception("invalid iterator");

            // if last < first then let it blow than to cover it up.
            size_type dist = static_cast<size_type>(last - first);

            if (dist > 0)
            {
                grow(dist);

                //self assignment
                if (this == first.m_cont)
                {
                    //TODO: see below, check for correctness
                    erase(0, last.m_pos + 1);
                }
                else
                {
                    //TODO: copying in reverse means [0,1,2,3,4,5] -> [5,4,3,2,1,0] ; check if this is done correctly!!!
                    stl::mem_copy<value_type>(m_data, &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);
                }

                swap_range(0, dist);
            }

            endof(dist);

            return *this;
        }
#endif

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
            if (m_size > sz)
            {
                // eos<T>(dist);
                size_type dist = sz;
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
            }
            else if (m_size < sz)
            {
                grow(sz);

                stl::mem_set(&m_data[m_size], c, (sz - m_size) * numbytes);

                // eos<T>(dist);
                size_type dist = sz;
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
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

            //eos<T>(m_size + 1);
            ++m_size;
        }

        // 23.2.4.3 modifiers (vector):
        void pop_back()
        {
            if (m_size)
            {
/*FIXME: test the following
            push_back(A(10));
            pop_back();
            push_back(A(11));
            Q: when is A(10) destroyed, if ever??
*/
                
                //eos<T>(m_size - 1);
                size_type dist = m_size - 1;
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
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
                    size_type size = m_size + dist;
                    grow(size);

                    // memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    stl::mem_move<value_type>(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * sizeof(value_type));
                    //memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * sizeof(value_type));
                    stl::mem_copy<value_type>(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * sizeof(value_type));

                    //eos<T>(size);
                    size_type dist = size;
                    if (dist < m_size)
                    {
                        value_type* unused = m_data + dist;
                        stl::mem_destroy(&unused, m_size - dist, m_allocator);
                    }
                    m_size = dist;
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
                    size_type size = m_size + dist;
                    grow(size);

                    //memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    stl::mem_move<value_type>(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    //memcpy_impl(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);
                    stl::mem_copy<value_type>(&m_data[p1], &((*first.m_cont)[first.m_pos]), dist * numbytes);

                    //eos<T>(size);
                    size_type dist = size;
                    if (dist < m_size)
                    {
                        value_type* unused = m_data + dist;
                        stl::mem_destroy(&unused, m_size - dist, m_allocator);
                    }
                    m_size = dist;
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
                    size_type size = m_size + dist;
                    grow(size);

                    //memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    stl::mem_move<value_type>(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    //memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);
                    stl::mem_copy<value_type>(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                    swap_range(p1, p1 + dist);

                    //eos<T>(size);
                    size_type dist = size;
                    if (dist < m_size)
                    {
                        value_type* unused = m_data + dist;
                        stl::mem_destroy(&unused, m_size - dist, m_allocator);
                    }
                    m_size = dist;
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
                    size_type size = m_size + dist;
                    grow(size);

                    //memmove_impl(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    stl::mem_move<value_type>(&m_data[p1 + dist], &m_data[p1], (m_size - p1) * numbytes);
                    //memcpy_impl(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);
                    stl::mem_copy<value_type>(&m_data[p1], &((*last.m_cont)[last.m_pos + 1]), dist * numbytes);

                    swap_range(p1, p1 + dist);

                    //eos<T>(size);
                    size_type dist = size;
                    if (dist < m_size)
                    {
                        value_type* unused = m_data + dist;
                        stl::mem_destroy(&unused, m_size - dist, m_allocator);
                    }
                    m_size = dist;
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
                size_type size = m_size + n2;

                grow(size);

                //memmove_impl(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);
                stl::mem_move<value_type>(&m_data[p1 + n2], &m_data[p1], (m_size - p1) * numbytes);

                stl::mem_set<value_type>(&m_data[p1], value, n2 * numbytes);

                //eos<T>(size);
                size_type dist = size;
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
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

                grow(size);

                //memmove_impl(&m_data[p1 + n], &m_data[p1], (m_size - p1) * numbytes);
                stl::mem_move<value_type>(&m_data[p1 + n], &m_data[p1], (m_size - p1) * sizeof(value_type));

                stl::mem_set<value_type>(&m_data[p1], x, n * numbytes);

                //eos<T>(size);
                size_type dist = size;
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy<value_type>(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
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

            //invalidate_iterators_gte(p1);

            //memmove_impl(&m_data[p1], &m_data[p1 + 1], (m_size - p1 - 1) * numbytes);
            stl::mem_move<value_type>(&m_data[p1], &m_data[p1 + 1], (m_size - p1 - 1) * sizeof(value_type));

            //eos<T>(m_size - 1);
            size_type dist = (m_size - 1);
            if (dist < m_size)
            {
                value_type* unused = m_data + dist;
                stl::mem_destroy<value_type>(&unused, m_size - dist, m_allocator);
            }
            m_size = dist;

            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first.m_cont != this || last.m_cont != this)
                throw stl::exception("invalid iterator");

            difference_type dist = last - first;
            if (dist > 0)
            {
                //invalidate_iterators_gte(first.m_pos);

                //fill the gap
                if (last.m_pos < m_size)
                {
                    //memmove_impl(&m_data[first.m_pos], &m_data[last.m_pos], (m_size - last.m_pos) * numbytes);
                    stl::mem_move<value_type>(&m_data[first.m_pos], &m_data[last.m_pos], (m_size - last.m_pos) * sizeof(value_type));
                }

                //eos<T>(m_size - dist);
                size_type dist = (m_size - dist);
                if (dist < m_size)
                {
                    value_type* unused = m_data + dist;
                    stl::mem_destroy<value_type>(&unused, m_size - dist, m_allocator);
                }
                m_size = dist;
            }

            return first;
        }

        void swap(container& ts)
        {
            stl::swap<Allocator>(m_allocator, ts.m_allocator);
            stl::swap<pointer>(m_data, ts.m_data);
            stl::swap<size_type>(m_size, ts.m_size);
            stl::swap<size_type>(m_capacity, ts.m_capacity);
        }

        void clear()
        {
            //invalidate_iterators();

            //eos<T>(0);
            size_type dist = 0;
            if (dist < m_size)
            {
                value_type* unused = m_data + dist;
                stl::mem_destroy(&unused, m_size - dist, m_allocator);
            }
            m_size = dist;
        }

        allocator_type get_allocator() const
        {
            return m_allocator;
        }

//#if 1    // Until the ambiguity with global operators gets solved, execute this.
//        bool operator==(const container& Right)
//        {
//            return vector_ops::operator ==(*this, Right);
//        }
//
//        bool operator<(const container& Right)
//        {
//            return vector_ops::operator <(*this, Right);
//        }
//        
//        bool operator!=(const container& Right)
//        {
//            return !(*this == Right);
//        }
//        
//        bool operator>(const container& Right)
//        {            
//            return (*this != Right) && !(*this < Right);
//        }
//
//        bool operator>=(const container& Right)
//        {
//            return !(*this < Right);
//        }
//
//        bool operator<=(const container& Right)
//        {
//            return (*this < Right) || (*this == Right);
//        }
//        
//#endif
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

    // specialized algorithms:
    //template<typename T, typename Allocator>
    //void swap (
    //    stl::vector<T, Allocator>& Left, 
    //    stl::vector<T, Allocator>& Right)
    //{
    //    return Left.swap(Right);
    //}

}  // namespace

#endif//__vector_hpp__
