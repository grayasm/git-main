/*
Copyright (C) 2012 Mihai Vasilian
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
            //  get correct first, then fast
            m_prev = 0;
            m_next = 0;

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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return this->m_node->m_T;
        }

        pointer operator->()const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return &(this->m_node->m_T);
        }

        list_iterator& operator++()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            this->m_node = this->m_node->m_next;

            return *this;
        }

        list_iterator operator++(int)
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            list_iterator tmp = *this;

            this->m_node = this->m_node->m_next;

            return tmp;
        }

        list_iterator& operator--()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");
#endif
            this->m_node = this->m_node->m_prev;

            return *this;
        }

        list_iterator operator--(int)
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");
#endif
            list_iterator tmp = *this;

            this->m_node = this->m_node->m_prev;

            return tmp;
        }

        bool operator==(const list_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node != it.m_node);
        }
    };  // list_iterator



    template<typename container, typename node>
    class list_const_iterator :
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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return this->m_node->m_T;
        }

        pointer operator->()const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return &(this->m_node->m_T);
        }

        list_const_iterator& operator++()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            this->m_node = this->m_node->m_next;

            return *this;
        }

        list_const_iterator operator++(int)
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            list_const_iterator tmp = *this;

            this->m_node = this->m_node->m_next;

            return tmp;
        }

        list_const_iterator& operator--()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");
#endif
            this->m_node = this->m_node->m_prev;

            return *this;
        }

        list_const_iterator operator--(int)
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_begin)
                throw stl::exception("invalid iterator");
#endif
            list_const_iterator tmp = *this;

            this->m_node = this->m_node->m_prev;

            return tmp;
        }

        bool operator==(const list_const_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_const_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return this->m_node->m_T;
        }

        pointer operator->()const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return &(this->m_node->m_T);
        }

        list_reverse_iterator& operator++()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
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
#ifdef DEBUG
            //  Cannot decrement beyond rbegin() node
            if( this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");
#endif
            // end of list is not m_begin, but m_end
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
#ifdef DEBUG
            //  Cannot decrement beyond rbegin() node
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");
#endif
            list_reverse_iterator tmp = *this;

            // end of list is not m_begin, but m_end
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
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_reverse_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return this->m_node->m_T;
        }

        pointer operator->()const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
            return &(this->m_node->m_T);
        }

        list_const_reverse_iterator& operator++()
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
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
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_node == this->m_cont->m_end)
                throw stl::exception("invalid iterator");
#endif
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
#ifdef DEBUG
            //  Cannot decrement beyond rbegin() node
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");
#endif
            // end of list is not m_begin, but m_end
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
#ifdef DEBUG
            //  Cannot decrement beyond rbegin() node
            if(this->m_cont == 0 || this->m_cont->empty() || this->m_node == this->m_cont->m_end->m_prev)
                throw stl::exception("invalid iterator");
#endif
            list_const_reverse_iterator tmp = *this;

            // end of list is not m_begin, but m_end
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
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
                throw stl::exception("invalid iterator");
#endif
            return (this->m_node == it.m_node);
        }

        bool operator!=(const list_const_reverse_iterator& it)const
        {
#ifdef DEBUG
            if(this->m_cont == 0 || this->m_cont != it.m_cont)
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

        typedef list_iterator<container, list_node<container> >                 iterator;
        typedef list_const_iterator<container, list_node<container> >           const_iterator;
        typedef list_reverse_iterator<container, list_node<container> >         reverse_iterator;
        typedef list_const_reverse_iterator<container, list_node<container> >   const_reverse_iterator;

        friend class list_iterator<container, list_node<container> >;
        friend class list_const_iterator<container, list_node<container> >;
        friend class list_reverse_iterator<container, list_node<container> >;
        friend class list_const_reverse_iterator<container, list_node<container> >;

    private:
        list_node<container>*      m_begin;
        list_node<container>*      m_end;
        size_type                  m_size;
        typename Allocator::template rebind<list_node<container> >::other  m_nallocator;

        inline void init(const Allocator& alloc)
        {
            m_nallocator = alloc;
            m_end = m_nallocator.allocate(1);
            m_end->m_prev = 0;
            m_end->m_next = 0;
            m_begin = m_end;
            m_size = 0;
        }

    public:
        explicit list(const Allocator& alloc= Allocator())
        {
            init(alloc);
        }

        explicit list(size_type n, const T& value = T(), const Allocator& alloc = Allocator())
        {
            init(alloc);
            assign(n, value);
        }


        template<typename InputIterator>
        explicit list(InputIterator first, InputIterator last, const Allocator& alloc = Allocator())
        {
            init(alloc);
            assign_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

        list(const container& tc)
        {
            init( tc.get_allocator() );
            *this = tc;
        }

        ~list()
        {
            clear();

            m_nallocator.deallocate(m_end, 1);
            m_begin = 0;
            m_end = 0;
        }

        container& operator=(const container& tc)
        {
            if (this != &tc)
            {
                size_type n1 = 0;
                list_node<container>* nod1 = m_begin;
                list_node<container>* nod2 = tc.m_begin;

                // copy container
                while (n1 < tc.m_size)
                {
                    if (n1 < m_size)
                    {
                        nod1->m_T = nod2->m_T;
                        nod1 = nod1->m_next;
                        nod2 = nod2->m_next;
                    }
                    else
                    {
                        // grow
                        push_back(nod2->m_T);
                        nod2 = nod2->m_next;
                    }
                    ++n1;
                }

                // remove tail
                while (n1 < m_size)
                {
                    pop_back();
                }
            }            

            return *this;
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            assign_(first, last, typename stl::iterator_traits<InputIterator>::iterator_category());
        }

    private:
        template<typename InputIterator>
        inline void assign_(InputIterator& first, InputIterator& last, stl::bidirectional_iterator_tag)
        {
            size_type n = 0;
            list_node<container>* node = m_begin;

            // copy range
            while(first != last)
            {
                if(n < m_size)
                {
                    node->m_T = *first;
                    node = node->m_next;
                }
                else
                {
                    // grow
                    push_back(*first);
                }

                ++first;
                ++n;
            }

            // remove tail
            while(n < m_size)
            {
                pop_back();
            }
        }

        template<typename InputIterator>
        inline void assign_(InputIterator& n, InputIterator& value, stl::input_iterator_tag)
        {
            assign(static_cast<size_type>(n), static_cast<T>(value));   
        }

    public:
        void assign(size_type count, const value_type& value)
        {
            if(count > max_size())
                throw stl::exception("size is too big");

            size_type n = 0;
            list_node<container>* node = m_begin;

            // fill n positions
            while(n < count)
            {
                if(n < m_size)
                {
                    node->m_T = value;
                    node = node->m_next;
                }
                else
                {
                    // grow
                    push_back(value);
                }

                ++n;
            }

            // remove tail
            while(n < m_size)
            {
                pop_back();
            }
        }

        allocator_type get_allocator() const
        {
            return m_nallocator;
        }

        iterator begin ()
        {
            return iterator(m_begin, this);
        }

        const_iterator begin () const
        {
            return const_iterator(m_begin, const_cast<container*>(this));
        }

        iterator end ()
        {
            return iterator(m_end, this);
        }

        const_iterator end () const
        {
            return const_iterator(m_end, const_cast<container*>(this));
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
                return const_reverse_iterator(m_end->m_prev, const_cast<container*>(this));
            }
            else
            {
                return const_reverse_iterator(m_end, const_cast<container*>(this));
            }
        }

        reverse_iterator rend()
        {
            return reverse_iterator(m_end, this);
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(m_end, const_cast<container*>(this));
        }

        bool empty() const
        {
            return (m_size == 0);
        }

        size_type size() const
        {
            return m_size;
        }

        size_type max_size() const
        {
            return static_cast<size_type>(-1) / sizeof(value_type);
        }

        void resize(size_type n, value_type value = value_type())
        {
            if(n > m_size)
            {
                while(m_size < n)
                {
                    // grow
                    push_back(value);
                }
            }
            else
            {
                while(m_size > n)
                {
                    // remove tail
                    pop_back();
                }
            }
        }

        reference front()
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("empty container");
#endif
            return m_begin->m_T;
        }

        const_reference front() const
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("empty container");
#endif
            return m_begin->m_T;
        }

        reference back()
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("empty container");
#endif
            return m_end->m_prev->m_T;
        }

        const_reference back() const
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("empty container");
#endif
            return m_end->m_prev->m_T;
        }

        void push_front(const value_type& value)
        {
            list_node<container>* node = m_nallocator.allocate(1);
            m_nallocator.construct(node, value);

            if(m_size == 0)
            {
                node->m_prev = 0;
                node->m_next = m_end;
                m_end->m_prev = node;
                m_begin = node;
            }
            else
            {
                node->m_prev = 0;
                node->m_next = m_begin;
                m_begin->m_prev = node;
                m_begin = node;
            }

            ++m_size;
        }

        void pop_front()
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("container is empty");
#endif
            list_node<container>* next = m_begin->m_next;

            m_nallocator.destroy(m_begin);
            m_nallocator.deallocate(m_begin, 1);

            next->m_prev = 0;
            m_begin = next;

            --m_size;
        }

        void push_back(const value_type& value)
        {
            list_node<container>* node = m_nallocator.allocate(1);
            m_nallocator.construct(node, value);

            if(m_size == 0)
            {
                node->m_prev = 0;
                node->m_next = m_end;
                m_end->m_prev = node;
                m_begin = node;
            }
            else
            {
                node->m_prev = m_end->m_prev;
                node->m_next = m_end;
                node->m_prev->m_next = node;
                m_end->m_prev = node;
            }

            ++m_size;
        }

        void pop_back()
        {
#ifdef DEBUG
            if(m_size == 0)
                throw stl::exception("container is empty");
#endif
            // > 1
            if(m_size > 1)
            {
                list_node<container>* nod = m_end->m_prev;
                list_node<container>* prev = nod->m_prev;

                m_nallocator.destroy(nod);
                m_nallocator.deallocate(nod, 1);

                prev->m_next = m_end;
                m_end->m_prev = prev;                
            }
            // == 1
            else
            {
                m_nallocator.destroy(m_begin);
                m_nallocator.deallocate(m_begin, 1);

                m_end->m_prev = 0;
                m_begin = m_end;
            }

            --m_size;
        }

        iterator insert(iterator position, const value_type& value)
        {
            insert_(position, value);
            return --position;
        }

    private:
        inline void insert_(iterator& position, const value_type& value)
        {
#ifdef DEBUG
            if (position.m_cont != this)
                throw stl::exception("Invalid iterator.");
#endif
            list_node<container>* node = m_nallocator.allocate(1);
            m_nallocator.construct(node, value);

            list_node<container>* pos = position.m_node;
            // front
            if (pos == m_begin)
            {
                node->m_prev = 0;
                node->m_next = m_begin;
                m_begin->m_prev = node;
                m_begin = node;
            }
            // middle or end
            else
            {
                node->m_prev = pos->m_prev;
                node->m_next = pos;
                pos->m_prev->m_next = node;
                pos->m_prev = node;
            }

            ++m_size;
        }

    public:
        void insert(iterator position, size_type n, const value_type& value)
        {
            for(size_type i = 0; i < n; ++i)
            {
                insert_(position, value);
            }
        }

        template<class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
            {
                insert_(position, *first);
            }
        }

        iterator erase(iterator position)
        {
            iterator next(position);
            ++next;

            erase_(position);

            return next;
        }


    private:
        inline void erase_(iterator& position)
        {
#ifdef DEBUG
            if (position.m_cont != this || position.m_node == m_end)
                throw stl::exception("Invalid iterator.");
#endif
            list_node<container>* node = position.m_node;

            if (node == m_begin)
            {
                m_begin = node->m_next;
                m_begin->m_prev = 0;
            }
            else
            {
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
            }

            m_nallocator.destroy(node);
            m_nallocator.deallocate(node, 1);

            --m_size;
        }


    public:
        iterator erase(iterator first, iterator last)
        {
            iterator next(first);
            while (next != last)
            {
                ++next;
                erase_(first);
                first = next;
            }
            return next;
        }

        void swap(container& x)
        {
            stl::swap(m_begin, x.m_begin);
            stl::swap(m_end, x.m_end);
            stl::swap(m_size, x.m_size);
            stl::swap(m_nallocator, x.m_nallocator);
        }

        void clear()
        {
            list_node<container>* node = 0;
            while (m_begin != m_end)
            {
                node = m_begin;
                m_begin = m_begin->m_next;
                
                m_nallocator.destroy(node);
                m_nallocator.deallocate(node, 1);
            }

            m_end->m_prev = 0;
            m_size = 0;
        }

        /*  Transfers elements from x into the container, inserting them
            at (before) position. This effectively inserts those elements
            into the container and removes them from x, altering the sizes
            of both containers. The operation does not involve the
            construction or destruction of any element. They are transferred,
            no matter whether x is an l-value or an r-value, or whether
            the value_type supports move-construction or not.

            The behavior is undefined if: get_allocator() != x.get_allocator()
        */
        void splice(iterator position, container& x)
        {
#ifdef DEBUG
            if (position.m_cont != this)
                throw stl::exception("Invalid iterator.");
#endif
            if (this != &x && !x.empty())
            {
                list_node<container>* first = x.m_begin;
                list_node<container>* last = x.m_end->m_prev;

                if (position.m_node == m_begin)
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
        }


        /*  This version transfers only the element pointed by it
            from x into the container.

            The behavior is undefined if: get_allocator() != x.get_allocator()
        */
        void splice(iterator position, container& x, iterator it)
        {
#ifdef DEBUG
            if (position.m_cont != this)
                throw stl::exception("Invalid iterator.");
#endif
            // inserting from self (safety check)
            if (this == &x)
            {
                // same position: nothing to do.
                if (position.m_node == it.m_node ||
                    (it.m_node != m_end && position.m_node == it.m_node->m_next))
                    return;
            }

            // allows inserting from self
            if (it.m_node != x.m_end)
            {
                // untie it from x
                list_node<container>* node = it.m_node;
                if (node == x.m_begin)
                {
                    x.m_begin = node->m_next;
                    x.m_begin->m_prev = 0;
                }
                else
                {
                    node->m_prev->m_next = node->m_next;
                    node->m_next->m_prev = node->m_prev;
                }
                --x.m_size;


                // add node to container
                list_node<container>* pos = position.m_node;
                if (pos == m_begin)
                {
                    m_begin->m_prev = node;
                    node->m_next = m_begin;
                    node->m_prev = 0;
                    m_begin = node;
                }
                else
                {
                    list_node<container>* prev = pos->m_prev;
                    list_node<container>* next = pos;

                    prev->m_next = node;
                    node->m_prev = prev;

                    node->m_next = next;
                    next->m_prev = node;
                }
                ++m_size;
            }
        }

        /*  This version transfers the range [first,last) from x
            into the container.

            The behavior is undefined if: get_allocator() != x.get_allocator()
            The behavior is undefined if position is an iterator
            in the range [first,last).
        */
        void splice(iterator position, container& x, iterator first, iterator last)
        {
#ifdef DEBUG
            if (position.m_cont != this || first.m_cont != &x || first.m_cont != last.m_cont)
                throw stl::exception("Invalid iterator.");
#endif
            // inserting from self (safety check)
            if(this == &x)
            {
                // same position: nothing to do.
                if (position.m_node == first.m_node ||
                    (first != last && position.m_node == first.m_node->m_next))
                    return;

                // UB if position is inside [first,last)
                list_node<container>* nod1 = first.m_node;
                list_node<container>* nod2 = last.m_node;
                for(; nod1 != nod2; nod1 = nod1->m_next)
                {
                    if(nod1 == position.m_node)
                        throw stl::exception("Invalid iterator.");
                }
            }

            // allows inserting from self
            if (first != last)
            {
                size_type dist = stl::distance(first, last);

                list_node<container>* node1 = first.m_node;
                list_node<container>* node2 = last.m_node->m_prev;

                // untie [first,last) range from x
                if (node1 == x.m_begin)
                {
                    x.m_begin = last.m_node;
                    x.m_begin->m_prev = 0;
                }
                else
                {
                    node1->m_prev->m_next = last.m_node;
                    last.m_node->m_prev = node1->m_prev;
                }
                x.m_size -= dist;

                // add [first, last) to container
                list_node<container>* pos = position.m_node;
                if (pos == m_begin)
                {
                    m_begin->m_prev = node2;
                    node2->m_next = m_begin;

                    m_begin = node1;
                    m_begin->m_prev = 0;
                }
                else
                {
                    list_node<container>* prev = pos->m_prev;
                    list_node<container>* next = pos;

                    prev->m_next = node1;
                    node1->m_prev = prev;

                    node2->m_next = next;
                    next->m_prev = node2;
                }
                m_size += dist;
            }
        }

        /*  Remove elements with specific value.
            Removes from the container all the elements that compare equal
            to value. This calls the destructor of these objects and reduces
            the container size by the number of elements removed.

            Unlike member function list::erase, which erases elements
            by their position (using an iterator), this function (list::remove)
            removes elements by their value.

            A similar function, list::remove_if, exists, which allows
            for a condition other than an equality comparison to determine
            whether an element is removed.
        */
        void remove(const value_type& value)
        {
            list_node<container>* node = m_begin;
            while (node != m_end)
            {
                if (node->m_T == value)
                {
                    iterator del(node, this);
                    node = node->m_next;
                    erase_(del);
                    continue;
                }

                node = node->m_next;
            }
        }

        /*  Remove elements fulfilling condition.
            Removes from the container all the elements for which
            Predicate pred returns true. This calls the destructor
            of these objects and reduces the container size by the
            number of elements removed.

            The function calls pred(*i) for each element
            (where i is an iterator to that element).
            Any of the elements in the list for which this returns true,
            are removed from the container.
        */
        template<typename Predicate>
        void remove_if(Predicate pred)
        {
            list_node<container>* node = m_begin;
            while (node != m_end)
            {
                if (pred(node->m_T))
                {
                    iterator del(node, this);
                    node = node->m_next;
                    erase_(del);
                    continue;
                }

                node = node->m_next;
            }
        }

        /*  Remove duplicate values.
            This version removes all but the first element from every
            consecutive group of equal elements in the container.
            Notice that an element is only removed from the list container
            if it compares equal to the element immediately preceding it.
            Thus, this function is especially useful for sorted lists.

            The elements removed are destroyed.
        */
        void unique()
        {
            if(m_size < 2)
                return;

            list_node<container>* nod1 = m_begin;
            list_node<container>* nod2 = nod1->m_next;
            while (nod2 != m_end)
            {
                if (nod1->m_T == nod2->m_T)
                {
                    iterator del(nod2, this);
                    nod2 = nod2->m_next;
                    erase_(del);
                    continue;
                }

                nod1 = nod1->m_next;
                nod2 = nod2->m_next;
            }
        }

        /*  Remove duplicate values.
            Removes all consecutive duplicate elements from the container.
            Only the first element in each group of equal elements is left.
            This version takes as argument a specific comparison function
            that determine the "uniqueness" of an element. In fact, any
            behavior can be implemented (and not only an equality comparison),
            but notice that the function will call binary_pred(*i,*(i-1))
            for all pairs of elements (where i is an iterator to an element,
            starting from the second) and remove i from the list
            if the predicate returns true.

            The elements removed are destroyed.
        */
        template<typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred)
        {
            if (m_size < 2)
                return;

            list_node<container>* nod1 = m_begin;
            list_node<container>* nod2 = nod1->m_next;
            while (nod2 != m_end)
            {
                if (binary_pred(nod2->m_T, nod1->m_T))
                {
                    iterator del(nod2, this);
                    nod2 = nod2->m_next;
                    erase_(del);
                    continue;
                }

                nod1 = nod1->m_next;
                nod2 = nod2->m_next;
            }
        }

        /*  Merge sorted lists.
            Merges x into the list by transferring all of its elements
            at their respective ordered positions into the container
            (both containers shall already be ordered).

            This effectively removes all the elements in x (which becomes empty),
            and inserts them into their ordered position within container
            (which expands in size by the number of elements transferred).
            The operation is performed without constructing nor destroying
            any element: they are transferred, no matter whether x is an
            l-value or an r-value, or whether the value_type supports
            move-construction or not.

            This function requires that the list containers have their
            elements already ordered by value before the call.
            For an alternative on unordered lists, see list::splice.
        */
        void merge(container& x)
        {
            if (this != &x)
            {
                container dest;
                merge_(*this, x, dest, stl::less<value_type>());
                swap(dest);
            }            
        }

        /*  Merge sorted lists.
            The template versions have the same behavior as the merge above,
            but take a specific predicate (comp) to perform the comparison
            operation between elements.
            This comparison shall produce a strict weak ordering
            of the elements (i.e., a consistent transitive comparison,
            without considering its reflexiveness).

            This function requires that the list containers have their
            elements already ordered by comp before the call.
            For an alternative on unordered lists, see list::splice.
        */
        template <typename Compare>
        void merge(container& x, Compare comp)
        {
            if (this != &x)
            {
                container dest;
                merge_<Compare>(*this, x, dest, comp);
                swap(dest);
            }            
        }

    private:
        template<typename Predicate>
        inline void merge_(container& left, container& right, container& dest, Predicate comp)
        {
            while (true)
            {
                if (left.size() > 0 && right.size() > 0)
                {
                    //if (comp(*right.begin(), *left.begin())) -- slower
                    if (comp(right.m_begin->m_T, left.m_begin->m_T))
                    {
                        dest.splice(dest.end(), right, right.begin());
                    }
                    else
                    {
                        dest.splice(dest.end(), left, left.begin());
                    }
                }
                else if (left.size() > 0)
                {
                    dest.splice(dest.end(), left);
                }
                else if (right.size() > 0)
                {
                    dest.splice(dest.end(), right);
                }
                else
                {
                    break;
                }
            } // while
        }

    public:
        /*  Sort elements in container.
            Sorts the elements in the list, altering their position within
            the container. The sorting is performed by applying an algorithm
            that uses operator < to compare elements. This comparison shall
            produce a strict weak ordering of the elements (i.e., a consistent
            transitive comparison, without considering its reflexiveness).

            The resulting order of equivalent elements is stable:
            i.e., equivalent elements preserve the relative order they had
            before the call. The entire operation does not involve
            the construction, destruction or copy of any element object.
            Elements are moved within the container.
        */
        void sort()
        {
            container dest;
            merge_sort_(dest, *this, stl::less<value_type>());
            swap(dest);
        }

        /*  Sort elements in container.
            The sorting is performed by applying an algorithm that uses
            comp to compare elements. This comparison shall produce
            a strict weak ordering of the elements (i.e., a consistent
            transitive comparison, without considering its reflexiveness).

            The resulting order of equivalent elements is stable:
            i.e., equivalent elements preserve the relative order they had
            before the call.
        */
        template <typename Compare>
        void sort(Compare comp)
        {
            container dest;
            merge_sort_<Compare>(dest, *this, comp);
            swap(dest);
        }

    private:
        //  http://en.wikipedia.org/wiki/Merge_sort
        template<typename Predicate>
        inline void merge_sort_(container& dest, container& src, Predicate comp)
        {
            if (src.size() <= 1)
            {
                dest = src;
                return;
            }

            container left, right;
            size_type middle = src.size() / 2;

            typename container::iterator mid = src.begin();
            stl::advance(mid, middle);

            left.splice(left.begin(), src, src.begin(), mid);
            right.splice(right.begin(), src);

            // recursively call merge_sort_() to further split each sublist
            // until sublist size is 1
            container subleft;
            container subright;
            merge_sort_<Predicate>(subleft, left, comp);
            merge_sort_<Predicate>(subright, right, comp);

            // merge the sublists returned from prior calls to merge_sort_()
            // and return the resulting merged sublist
            merge_<Predicate>(subleft, subright, dest, comp);
        }

    public:
        void reverse()
        {
            // switch neighbors (the order of iteration)
            for (list_node<container>* node = m_begin; node != m_end;)
            {
                list_node<container>* next = node->m_next;
                stl::swap(node->m_next, node->m_prev);
                node = next;
            }

            // re-connect begin & end of the container
            stl::swap(m_end->m_prev, m_begin);
            m_begin->m_prev = 0;
            m_end->m_prev->m_next = m_end;
        }
    };  // list
}  // namespace stl



#endif//__list_hpp__
