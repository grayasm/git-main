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

#ifndef __list_hpp__
#define __list_hpp__

#include "iterator.hpp"
#include "exception.hpp"
#include "memory.hpp"
#include "memmanip.hpp"
#include "algorithm.hpp"



namespace stl
{
    template<typename container, typename node>
    struct list_iterator_base
    {
        node*           m_node;
        container*      m_cont;
    };

    template<typename container>
    class list_node
    {
    public:
        list_node(typename container::const_reference val)
        {
            //  called from: m_allocator.construct(nod, value);
#ifdef DEBUG
            m_prev = 0;
            m_next = 0;
#endif
            m_T = val;
        }

    public:
        list_node*                      m_prev;
        list_node*                      m_next;
        typename container::value_type  m_T;
    };


    template<typename container, typename node> class list_const_iterator;
    template<typename container, typename node> class list_const_reverse_iterator;
    template<typename T, typename Allocator> class list;

    template<typename container, typename node>
    class list_iterator :
        public  stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>,
        private stl::list_iterator_base<container, node>
    {
    public:
        typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::pointer             pointer;
        typedef typename base::reference           reference;

        friend class stl::list<typename container::value_type, typename container::allocator_type>;
        friend class stl::list_const_iterator<container, node>;

    private:
        inline void init()
        {
            // g++: m_cont was not declared in this scope
            this->m_node = 0;
            this->m_cont = 0;
        }

        list_iterator(node* n, container* cont)
        {
            this->m_node = n;
            this->m_cont = cont;
        }


    public:
        list_iterator()
        {
            init();
        }

        list_iterator(const list_iterator& it)
        {
            init();
            *this = it;
        }

        ~list_iterator()
        {
        }

        list_iterator& operator=(const list_iterator& it)
        {
            if(this != &it)
            {
                this->m_node = it.m_node;
                this->m_cont = it.m_cont;
            }
            return *this;
        }

        reference operator*()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return this->m_node->m_T;
        }

        pointer operator->()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return &(this->m_node->m_T);
        }

        list_iterator& operator++()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            this->m_node = this->m_node->m_next;

            return *this;
        }

        list_iterator operator++(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            list_iterator tmp = *this;

            this->m_node = this->m_node->m_next;

            return tmp;
        }

        list_iterator& operator--()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");

            this->m_node = this->m_node->m_prev;

            return *this;
        }

        list_iterator operator--(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");

            list_iterator tmp = *this;

            this->m_node = this->m_node->m_prev;

            return tmp;
        }

        bool operator==(const list_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif

            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_iterator& it)const
        {
#ifdef DEBUG
            if (this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif

            return (this->m_node != it.m_node);
        }
    };  // list_iterator



    template<typename container, typename node>
    class list_const_iterator :
        public  stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>,
        private stl::list_iterator_base<container, node>
    {
    public:
        typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;

        friend class stl::list<typename container::value_type, typename container::allocator_type>;

    private:
        inline void init()
        {
            // g++: m_cont was not declared in this scope
            this->m_node = 0;
            this->m_cont = 0;
        }

        list_const_iterator(node* n, container* cont)
        {
            this->m_node = n;
            this->m_cont = cont;
        }

    public:
        list_const_iterator()
        {
            init();
        }

        list_const_iterator(const list_const_iterator& it)
        {
            init();
            *this = it;
        }

        ~list_const_iterator()
        {
        }

        list_const_iterator& operator=(const list_const_iterator& it)
        {
            if(this != &it)
            {
                this->m_node = it.m_node;
                this->m_cont = it.m_cont;
            }
            return *this;
        }

        list_const_iterator(const list_iterator<container, node>& it)
        {
            init();
            *this = it;
        }

        list_const_iterator& operator=(const list_iterator<container, node>& it)
        {
            this->m_node = it.m_node;
            this->m_cont = it.m_cont;

            return *this;
        }


        reference operator*()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return this->m_node->m_T;
        }

        pointer operator->()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return &(this->m_node->m_T);
        }

        list_const_iterator& operator++()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            this->m_node = this->m_node->m_next;

            return *this;
        }

        list_const_iterator operator++(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            list_const_iterator tmp = *this;

            this->m_node = this->m_node->m_next;

            return tmp;
        }

        list_const_iterator& operator--()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");

            this->m_node = this->m_node->m_prev;

            return *this;
        }

        list_const_iterator operator--(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");

            list_const_iterator tmp = *this;

            this->m_node = this->m_node->m_prev;

            return tmp;
        }

        bool operator==(const list_const_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif

            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_const_iterator& it)const
        {
#ifdef DEBUG
            if (this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif

            return (this->m_node != it.m_node);
        }
    };  // list_const_iterator


    template<typename container, typename node>
    class list_reverse_iterator :
        public stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>,
        private stl::list_iterator_base<container, node>
    {
    public:
        typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::pointer             pointer;
        typedef typename base::reference           reference;

        friend class stl::list<typename container::value_type, typename container::allocator_type>;
        friend class stl::list_const_reverse_iterator<container, node>;

    private:
        inline void init()
        {
            // g++: m_cont was not declared in this scope
            this->m_node = 0;
            this->m_cont = 0;
        }
        
        list_reverse_iterator(node* n, container* cont)
        {
            this->m_node = n;
            this->m_cont = cont;
        }


    public:
        list_reverse_iterator()
        {
            init();
        }

        list_reverse_iterator(const list_reverse_iterator& it)
        {
            init();
            *this = it;
        }

        ~list_reverse_iterator()
        {
        }

        list_reverse_iterator& operator=(const list_reverse_iterator& it)
        {
            if(this != &it)
            {
                this->m_node = it.m_node;
                this->m_cont = it.m_cont;
            }
            return *this;
        }

        reference operator*()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return this->m_node->m_T;
        }

        pointer operator->()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return &(this->m_node->m_T);
        }

        list_reverse_iterator& operator++()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            // end of list is not m_begin, but m_end
            if(this->m_node == this->m_cont->m_begin)
            {
                this->m_node = this->m_cont->m_end;
            }
            else
            {
                this->m_node = this->m_node->m_prev;
            }

            return *this;
        }

        list_reverse_iterator operator++(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            list_reverse_iterator tmp = *this;

            // end of list is not m_begin, but m_end
            if(this->m_node == this->m_cont->m_begin)
            {
                this->m_node = this->m_cont->m_end;
            }
            else
            {
                this->m_node = this->m_node->m_prev;
            }

            return tmp;
        }

        list_reverse_iterator& operator--()
        {
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");

            if(this->m_node == this->m_cont->m_end)
            {
                this->m_node = this->m_cont->m_begin;
            }
            else
            {
                this->m_node = this->m_node->m_next;
            }

            return *this;
        }

        list_reverse_iterator operator--(int)
        {
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");

            list_reverse_iterator tmp = *this;

            if(this->m_node == this->m_cont->m_end)
            {
                this->m_node = this->m_cont->m_begin;
            }
            else
            {
                this->m_node = this->m_node->m_next;
            }

            return tmp;
        }

        bool operator==(const list_reverse_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_reverse_iterator& it)const
        {
#ifdef DEBUG
            if (this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node != it.m_node);
        }
    };  // list_reverse_iterator


    template<typename container, typename node>
    class list_const_reverse_iterator :
        public stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>,
        private stl::list_iterator_base<container, node>
    {
    public:
        typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;

        friend class stl::list<typename container::value_type, typename container::allocator_type>;


    private:
        inline void init()
        {
            // g++: m_cont was not declared in this scope
            this->m_node = 0;
            this->m_cont = 0;
        }

        list_const_reverse_iterator(node* n, container* cont)
        {
            this->m_node = n;
            this->m_cont = cont;
        }


    public:
        list_const_reverse_iterator()
        {
            init();
        }

        list_const_reverse_iterator(const list_const_reverse_iterator& it)
        {
            init();
            *this = it;
        }

        ~list_const_reverse_iterator()
        {
        }

        list_const_reverse_iterator& operator=(const list_const_reverse_iterator& it)
        {
            if(this != &it)
            {
                this->m_cont = it.m_cont;
                this->m_node = it.m_node;
            }
            return *this;
        }

        list_const_reverse_iterator& operator=(const list_reverse_iterator<container, node>& it)
        {
            this->m_cont = it.m_cont;
            this->m_node = it.m_node;

            return *this;
        }

        list_const_reverse_iterator(const list_reverse_iterator<container, node>& it)
        {
            init();
            *this = it;
        }

        reference operator*()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return this->m_node->m_T;
        }

        pointer operator->()const
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            return &(this->m_node->m_T);
        }

        list_const_reverse_iterator& operator++()
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            // end of list is not m_begin, but m_end
            if(this->m_node == this->m_cont->m_begin)
            {
                this->m_node = this->m_cont->m_end;
            }
            else
            {
                this->m_node = this->m_node->m_prev;
            }

            return *this;
        }

        list_const_reverse_iterator operator++(int)
        {
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");

            list_const_reverse_iterator tmp = *this;

            // end of list is not m_begin, but m_end
            if(this->m_node == this->m_cont->m_begin)
            {
                this->m_node = this->m_cont->m_end;
            }
            else
            {
                this->m_node = this->m_node->m_prev;
            }

            return tmp;
        }

        list_const_reverse_iterator& operator--()
        {
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");

            if(this->m_node == this->m_cont->m_end)
            {
                this->m_node = this->m_cont->m_begin;
            }
            else
            {
                this->m_node = this->m_node->m_next;
            }

            return *this;
        }

        list_const_reverse_iterator operator--(int)
        {
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");

            list_const_reverse_iterator tmp = *this;

            if(this->m_node == this->m_cont->m_end)
            {
                this->m_node = this->m_cont->m_begin;
            }
            else
            {
                this->m_node = this->m_node->m_next;
            }

            return tmp;
        }

        bool operator==(const list_const_reverse_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_const_reverse_iterator& it)const
        {
#ifdef DEBUG
            if (this->m_cont == 0 || it.m_cont == 0)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node != it.m_node);
        }
    };  // list_const_reverse_iterator


    template<typename T, typename Allocator = stl::allocator<T> >
    class list
    {
    public:
        typedef          list<T, Allocator>              container;

        // types:
        typedef typename Allocator::value_type           value_type;
        typedef typename Allocator::size_type            size_type;
        typedef typename Allocator::difference_type      difference_type;
        typedef Allocator                                allocator_type;

        typedef typename Allocator::reference            reference;
        typedef typename Allocator::const_reference      const_reference;
        typedef typename Allocator::pointer              pointer;
        typedef typename Allocator::const_pointer        const_pointer;      

        typedef list_iterator<container, list_node<container> >          iterator;
        typedef list_const_iterator<container, list_node<container> >    const_iterator;
        typedef list_reverse_iterator<container, list_node<container> >  reverse_iterator;
        typedef list_const_reverse_iterator<container, list_node<container> > const_reverse_iterator;

        friend class list_iterator<container, list_node<container> >;
        friend class list_const_iterator<container, list_node<container> >;
        friend class list_reverse_iterator<container, list_node<container> >;
        friend class list_const_reverse_iterator<container, list_node<container> >;

//TODO: check if these are not-needed
        //friend struct stl::list_iterator_base<container, list_node<container> >;
        //typedef stl::list_iterator_base<container, list_node<container> > iterator_base;


    private:
        list_node<container>*      m_begin;
        list_node<container>*      m_end;
        size_type                  m_size;
        typename Allocator::template rebind<list_node<container> >::other  m_node_alloc;
    
    private:
        inline void init(const Allocator& alloc)
        {
            m_node_alloc = alloc;
            m_end = m_node_alloc.allocate(1);
            m_end->m_prev = 0;
            m_end->m_next = 0;
            m_begin = m_end;
            m_size = 0;
        }

    public:
        explicit list(const allocator_type& alloc= allocator_type())
        {
            init(alloc);
        }

        explicit list(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
        {
            init(alloc);
            assign(n, value);
        }


        template<typename InputIterator>
        explicit list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
        {
            init(alloc);
            assign(first, last);
        }

        list(const container& tc)
        {
            init( tc.get_allocator() );
            *this = tc;
        }

        ~list()
        {
            clear();

            m_node_alloc.deallocate(m_end, 1);
            m_begin = 0;
            m_end = 0;
        }

        container& operator=(const container& tc)
        {
            if(this == &tc)
                return *this;

            size_type n1 = 0;
            list_node<container>* nod1 = m_begin;
            list_node<container>* nod2 = tc.m_begin;

            while( n1 < tc.m_size )
            {
                if(n1 < m_size)
                {
                    nod1->m_T = nod2->m_T;

                    nod1 = nod1->m_next;
                    nod2 = nod2->m_next;
                }
                else
                {
                    // grow
                    push_back( nod2->m_T );
                    nod2 = nod2->m_next;
                }
                ++n1;
            }

            // remove tail
            while(n1 < m_size)
            {
                pop_back();
            }

            return *this;
        }


    private:
        template<typename InputIterator>
        inline void assign_impl(InputIterator first, InputIterator last, stl::bidirectional_iterator_tag)
        {
            /*
              we get both:

              double d[]={0.1,0.2,0.3};
              list l(d, d+3); -> random_access_iterator_tag

              list m(l.begin(), l.end()); -> bidirectional_iterator_tag
            */

            size_type n1 = 0;
            list_node<container>* nod1 = m_begin;
            while(first != last)
            {
                if(n1 < m_size)
                {
                    nod1->m_T = *first;

                    nod1 = nod1->m_next;
                }
                else
                {
                    // grow
                    push_back(*first);
                }

                ++first;
                ++n1;
            }

            // remove tail
            while(n1 < m_size)
            {
                pop_back();
            }
        }


        template<typename InputIterator>
        inline void assign_impl(InputIterator n, InputIterator u, stl::input_iterator_tag)
        {
            /*
              int sz = 10;
              list<int> l(sz, 0);
              list<int> m(5, 10);
            */
            size_type sz = static_cast<size_type>(n);
            value_type val = static_cast<value_type>(u);
            assign(sz , val);            
        }



    public:
        template<class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            assign_impl(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        void assign(size_type n, const value_type& u)
        {
            if(n > max_size())
                throw stl::exception("size is too big");

            size_type n1 = 0;
            list_node<container>* nod1 = m_begin;
            while( n1 < n )
            {
                if(n1 < m_size)
                {
                    nod1->m_T = u;

                    nod1 = nod1->m_next;
                }
                else
                {
                    // grow
                    push_back(u);
                }

                ++n1;
            }

            // remove tail
            while(n1 < m_size)
            {
                pop_back();
            }
        }

        allocator_type get_allocator() const
        {
            return m_node_alloc;
        }


        // $23.2.2. iterators:
        iterator begin ()
        {
            return iterator(m_begin, this);
        }

        const_iterator begin () const
        {
            return const_iterator(m_begin, this);
        }

        iterator end ()
        {
            return iterator(m_end, this);
        }

        const_iterator end () const
        {
            return const_iterator(m_end, this);
        }

        reverse_iterator rbegin()
        {
            if(m_size)
            {
                return reverse_iterator(m_end->m_prev, this);
            }
            else
            {
                return reverse_iterator(m_end, this);
            }            
        }

        const_reverse_iterator rbegin() const
        {
            if(m_size)
            {
                return const_reverse_iterator(m_end->m_prev, this);
            }
            else
            {
                return const_reverse_iterator(m_end, this);
            }
        }

        reverse_iterator rend()
        {
            return reverse_iterator(m_end, this);
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(m_end, this);
        }

        bool empty() const
        {
            return m_size == 0;
        }

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
            if(sz > m_size)
            {
                while(m_size < sz)
                {
                    // grow
                    push_back(c);
                }
            }
            else
            {
                while(m_size > sz)
                {
                    // remove tail
                    pop_back();
                }
            }
        }


        reference front()
        {
            if(m_size == 0)
                throw stl::exception("empty container");

            return m_begin->m_T;
        }

        const_reference front() const
        {
            if(m_size == 0)
                throw stl::exception("empty container");

            return m_begin->m_T;
        }

        reference back()
        {
            if(m_size == 0)
                throw stl::exception("empty container");

            return m_end->m_prev->m_T;
        }

        const_reference back() const
        {
            if(m_size == 0)
                throw stl::exception("empty container");

            return m_end->m_prev->m_T;
        }

        void push_front(const value_type& x)
        {
            list_node<container>* nod = m_node_alloc.allocate(1);
            m_node_alloc.construct(nod, x);

            if(m_size == 0)
            {
                m_end->m_prev = nod;
                nod->m_next = m_end;
                nod->m_prev = 0;
                m_begin = nod;
            }
            else
            {
                m_begin->m_prev = nod;
                nod->m_next = m_begin;
                nod->m_prev = 0;
                m_begin = nod;
            }

            ++m_size;
        }

        void pop_front()
        {
            if(m_size == 0)
                throw stl::exception("container is empty");

            list_node<container>* next = m_begin->m_next;

            m_node_alloc.destroy(m_begin);
            m_node_alloc.deallocate(m_begin, 1);

            next->m_prev = 0;
            m_begin = next;

            --m_size;
        }

        void push_back(const value_type& x)
        {
            list_node<container>* nod = m_node_alloc.allocate(1);
            m_node_alloc.construct(nod, x);

            if(m_size == 0)
            {
                // assign m_begin
                m_end->m_prev = nod;

                nod->m_next = m_end;
                nod->m_prev = 0;

                m_begin = nod;
            }
            else
            {
                // insert
                list_node<container>* prev = m_end->m_prev;
                m_end->m_prev = nod;

                nod->m_next = m_end;
                nod->m_prev = prev;

                prev->m_next = nod;
            }

            ++m_size;
        }

        void pop_back()
        {
            if(m_size == 0)
                throw stl::exception("container is empty");

            // > 1
            if(m_size > 1)
            {
                list_node<container>* nod = m_end->m_prev;
                list_node<container>* prev = nod->m_prev;

                m_node_alloc.destroy(nod);
                m_node_alloc.deallocate(nod, 1);

                m_end->m_prev = prev;
                prev->m_next = m_end;
            }
            // == 1
            else
            {
                m_node_alloc.destroy(m_begin);
                m_node_alloc.deallocate(m_begin, 1);

                m_end->m_prev = 0;
                m_begin = m_end;
            }

            --m_size;
        }

        iterator insert(iterator position, const value_type& x)
        {
            if(position.m_cont != this)
                throw stl::exception("Invalid iterator.");

            list_node<container>* nod = m_node_alloc.allocate(1);
            m_node_alloc.construct(nod, x);

            list_node<container>* pos = position.m_node;
            if(pos == m_begin)
            {
                // assign m_begin
                m_begin->m_prev = nod;

                nod->m_next = m_begin;
                nod->m_prev = 0;

                m_begin = nod;
            }
            // similar with (pos == m_end)
            else
            {
                // insert
                list_node<container>* prev = pos->m_prev;
                pos->m_prev = nod;

                nod->m_next = pos;
                nod->m_prev = prev;

                prev->m_next = nod;
            }

            ++m_size;
            return iterator(nod, this);
        }

        void insert(iterator position, size_type n, const value_type& x)
        {
            if(n > max_size())
                throw stl::exception("size is too big");

            for(size_type i=0; i < n; ++i)
            {
                insert(position, x);
            }
        }

        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            while(first != last)
            {
                // always before (unchanged) position
                insert(position, *first);
                ++first;
            }
        }


        iterator erase(iterator position)
        {
            if(position.m_cont != this || position.m_node == m_end)
                throw stl::exception("Invalid iterator.");


            list_node<container>* nod = position.m_node;
            list_node<container>* next = nod->m_next;

            if(nod == m_begin)
            {
                // move m_begin
                m_begin = m_begin->m_next;
                m_begin->m_prev = 0;
            }
            else
            {
                // untie position node
                list_node<container>* prev = nod->m_prev;

                prev->m_next = next;
                next->m_prev = prev;
            }

            m_node_alloc.destroy(nod);
            m_node_alloc.deallocate(nod, 1);

            // size
            --m_size;

            return iterator(next, this);
        }

        iterator erase(iterator first, iterator last)
        {
            while(first != last)
            {
                first = erase(first);
            }
            return first;
        }

        void swap(container& lst)
        {
            stl::swap<list_node<container>*>(m_begin, lst.m_begin);
            stl::swap<list_node<container>*>(m_end, lst.m_end);
            stl::swap<size_type>(m_size, lst.m_size);
        }

        void clear()
        {
            list_node<container>* next;
            for(; m_begin != m_end; m_begin = next)
            {
                next = m_begin->m_next;

                m_node_alloc.destroy(m_begin);
                m_node_alloc.deallocate(m_begin, 1);
            }

            m_end->m_prev = 0;
            m_begin = m_end;
            m_size = 0;
        }

        void splice(iterator position, container& x)
        {
            /*
              Inserts the contents of x before position and x becomes empty.
              Invalidates all iterators and references to the list x.
            */
            if(position.m_cont != this)
                throw stl::exception("Invalid iterator.");

            if(&x == this || x.empty())
                return;

            list_node<container>* first = x.m_begin;
            list_node<container>* last = x.m_end->m_prev;

            if(position.m_node == m_begin)
            {
                // tie last node
                m_begin->m_prev = last;
                last->m_next = m_begin;

                // new list begin
                m_begin = first;
            }
            else
            {
                list_node<container>* prev = position.m_node->m_prev;
                list_node<container>* next = position.m_node;

                // tie first
                prev->m_next = first;
                first->m_prev = prev;

                // tie last
                next->m_prev = last;
                last->m_next = next;
            }

            // grow
            m_size += x.m_size;

            // clear source list
            x.m_end->m_prev = 0;
            x.m_begin = x.m_end;
            x.m_size = 0;            
        }



        void splice(iterator position, container& x, iterator i)
        {
            /*
              Inserts an element pointed to by i from list x before position and removes the element from x.
              The result is unchanged if position == i or position == ++i.
              Invalidates only the iterators and references to the spliced element.
            */
            if(position.m_cont != this || i.m_cont != &x || i.m_node == x.m_end)
                throw stl::exception("Invalid iterator.");

            list_node<container>* inode = i.m_node;
            if(&x == this && (position.m_node == inode || position.m_node == inode->m_next))
                return;

            if(inode == x.m_begin)
            {
                // disconnect iterator
                inode->m_next->m_prev = 0;
                x.m_begin = inode->m_next;
            }
            else
            {
                // disconnect iterator
                inode->m_prev->m_next = inode->m_next;
                inode->m_next->m_prev = inode->m_prev;
            }


            if(position.m_node == m_begin)
            {
                // assign m_begin
                m_begin->m_prev = inode;
                inode->m_next = m_begin;
                inode->m_prev = 0;

                m_begin = inode;
            }
            else
            {
                // connect
                list_node<container>* prev = position.m_node->m_prev;
                list_node<container>* next = position.m_node;

                prev->m_next = inode;
                inode->m_prev = prev;

                next->m_prev = inode;
                inode->m_next = next;
            }
        }


        void splice(iterator position, container& x, iterator first, iterator last)
        {
            /*
              Inserts elements in the range [first, last) before position and removes the elements from x.
              Requires that [first, last) to be a valid range in x.
              The result is undefined if position is an iterator in the range [first, last).
              Invalidates only the iterators and references to the spliced elements.
            */
            if( position.m_cont != this || first.m_cont != &x || last.m_cont != &x)
                throw stl::exception("Invalid iterator.");

            if(x.empty() || first == last)
                return;


            // safety check
            if(this == &x)
            {
                // The result is unchanged if position == first or position == ++first.
                list_node<container>* inode = first.m_node;
                if(position.m_node == inode || position.m_node == inode->m_next)
                    return;

                // check for invalid condition: position inside [first, last] range
                list_node<container>* nod = first.m_node;
                list_node<container>* nod2 = last.m_node;
                bool bfound = false;
                for(; nod != nod2; nod = nod->m_next)
                {
                    if(position.m_node == nod)
                    {
                        bfound = true;
                        break;
                    }
                }
                if(bfound || position.m_node == nod)
                {
                    throw stl::exception("Insert position is inside [first, last] range. Result is undefined.");
                }
            }


            // disconnect [first, last) from owner
            list_node<container>* sbeg = first.m_node;
            list_node<container>* send = last.m_node->m_prev;
            if(sbeg == x.m_begin)
            {
                last.m_node->m_prev = 0;
                x.m_begin = last.m_node;
            }
            else
            {
                sbeg->m_prev->m_next = send->m_next;
                send->m_next->m_prev = sbeg->m_prev;
            }


            // connect range [first, last) into this list
            list_node<container>* dbeg = position.m_node->m_prev;
            list_node<container>* dend = position.m_node;

            if(position.m_node == m_begin)
            {
                // assign m_begin
                sbeg->m_prev = 0;

                send->m_next = m_begin;
                m_begin->m_prev = send;

                m_begin = sbeg;
            }
            else
            {
                // insert range
                dbeg->m_next = sbeg;
                sbeg->m_prev = dbeg;

                send->m_next = dend;
                dend->m_prev = send;
            }
        }


        void remove(const value_type& value)
        {
            /*
              Erases all the elements in the list referred by a list iterator i,
              for which the following conditions hold: *i == value, pred(*i) != false.
              Throws nothing unless an exception is thrown by *i == value or pred(*i) != false.
              Stable as the relative order of the elements that are not removed
              is the same as their relative order in the original list.
            */
            for(iterator it = begin(); it.m_node != m_end;)
            {
                if( *it == value )
                {
                    it = erase(it);
                    continue;
                }
                else
                {
                    ++it;
                }
            }
        }


        template<typename Predicate>
        void remove_if(Predicate pred)
        {
            // see explanation above.
            for(iterator it = begin(); it.m_node != m_end;)
            {
                if( pred(*it) )
                {
                    it = erase(it);
                    continue;
                }
                else
                {
                    ++it;
                }
            }
        }


        void unique()
        {
            /*
              Eliminates all but the first element from every consecutive group of equal elements referred to by
              the iterator i in the range [first + 1, last) for which *i == *(i-1) or pred(*i, *(i - 1)) holds.
            */
            if(m_size < 2)
                return;

            iterator it2(m_begin->m_next, this);
            for(iterator it = begin(); it2.m_node != m_end;)
            {
                if( *it == *it2 )
                {
                    it2 = erase(it2);
                    continue;
                }
                else
                {
                    ++it;
                    ++it2;
                }
            }
        }


        template<typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            // see explanation above.
            if(m_size < 2)
                return;

            iterator it2(m_begin->m_next, this);
            for(iterator it = begin(); it2.m_node != m_end;)
            {
                if( binary_pred(*it, *it2) )
                {
                    it2 = erase(it2);
                    continue;
                }
                else
                {
                    ++it;
                    ++it2;
                }
            }
        }



    private:
//TODO: "merge and sort to be MS comparable as performance"

        template<typename Predicate>
        void merge_impl(container& left, container& right, container& dst, Predicate comp)
        {
            while(true)
            {
                if(left.size() > 0 && right.size() > 0)
                {
                    if( comp(*right.begin(), *left.begin()) )
                    {
                        dst.splice(dst.end(), right, right.begin());
                    }
                    else
                    {
                        dst.splice(dst.end(), left, left.begin());
                    }
                }
                else if(left.size() > 0)
                {
                    dst.splice(dst.end(), left);
                }
                else if(right.size() > 0)
                {
                    dst.splice(dst.end(), right);
                }
                else
                {
                    break;
                }
            }//while
        }


    public:
        void merge(container& x)
        {
            /*
              comp defines a strict weak ordering and the list and the argument list are both sorted according to this ordering.
              Merges the argument list into the list.
              For equivalent elements in the two lists, the elements from the list always precede the elements from the argument list.
              x is empty after the merge.
            */
            container dst;
            merge_impl< stl::less<value_type> >(*this, x, dst, stl::less<value_type>());
            swap(dst);
        }


        template <typename Compare>
        void merge(container& x, Compare comp)
        {
            // see explanation above
            container dst;
            merge_impl<Compare>(*this, x, dst, comp);
            swap(dst);
        }



    private:
//TODO: "to be comparable with MS"

        template<typename Predicate>
        void merge_sort(container& dst, container& src, Predicate comp)
        {
            if(src.size() <= 1)
            {
                dst = src;
                return;
            }

            container left, right;
            size_type middle = src.size() / 2;

            typename container::iterator mid = src.begin();
            stl::advance(mid, middle);

            left.splice(left.begin(), src, src.begin(), mid);
            right.splice(right.begin(), src);

            // recursively call merge_sort() to further split each sublist
            // until sublist size is 1
            container subleft;
            container subright;
            merge_sort<Predicate>(subleft, left, comp);
            merge_sort<Predicate>(subright, right, comp);

            // merge the sublists returned from prior calls to merge_sort()
            // and return the resulting merged sublist
            merge_impl<Predicate>(subleft, subright, dst, comp);
        }


    public:
        /*
          Using merge_sort  http://en.wikipedia.org/wiki/Merge_sort
          The entire operation does not involve the construction, destruction or copy of any element object.
          They are moved within the container.
        */
        void sort()
        {
            container dst;
            merge_sort< stl::less<value_type> >(dst, *this, stl::less<value_type>());
            swap(dst);
        }


        /*templated sort*/
        template <typename Compare>
        void sort(Compare comp)
        {
            container dst;
            merge_sort<Compare>(dst, *this, comp);
            swap(dst);
        }


        void reverse()
        {
            if(m_size < 2)
                return;

            // switch neighbors (the order of iteration)
            list_node<container>* tmp = 0;
            for(list_node<container>* nod = m_begin; nod != m_end;)
            {
                tmp = nod->m_next;
                stl::swap<list_node<container>*>(nod->m_next, nod->m_prev);
                nod = tmp;
            }

            // re-connect begin & end of the container
            stl::swap<list_node<container>*>(m_end->m_prev, m_begin);
            m_begin->m_prev = 0;
            m_end->m_prev->m_next = m_end;
        }
    };  // list
}  // namespace stl



#endif//__list_hpp__
