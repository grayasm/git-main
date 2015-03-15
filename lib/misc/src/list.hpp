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


//c
//c++
#include <vector>
#include <list> // for internal iterators storage
//misc
#include "autoptr.hpp"
#include "math.hpp"
#include "algorithm.hpp"
#include "functional.hpp"
#include "utility.hpp"
#include "memmanip.hpp"
#include "exception.hpp"
#include "memory.hpp"


namespace misc
{
	
    /* iterator base */
    template<typename container, typename node>
    struct list_iterator_base
    {
        node*           m_node;
        container*      m_cont;
    };


    /* list's node */
    template<typename container>
    class list_node
    {
    public:
        // debug_iterator is implemented at node level
        typedef list_iterator_base<container, list_node>    iterator_base;
        typedef std::vector<iterator_base*>                 iterator_array;

    public:
		list_node(typename container::const_reference val)
			: m_T(val)
        {
            m_itarray = 0;
        }
		
        ~list_node()
        {
            if(m_itarray)
            {
                delete m_itarray;
                m_itarray = 0;
            }
        }


        inline void add_iterator(iterator_base* it)
        {
            // debug_iterator holder is initialized on demand
            if( !m_itarray )
            {
                m_itarray = new iterator_array();
                m_itarray->reserve(5);
            }

#if 1
            /* check scenarios in which iterator forgot to update
             * the node it was suppose to retain.
             */
            if(it->m_node != this)
                throw misc::exception("invalid list_node");

            for(size_t i=0; i < m_itarray->size(); ++i)
            {
                if(it == (*m_itarray)[i])
                    throw misc::exception("iterator registered multiple times");
            }
#endif

            m_itarray->push_back(it);
        }

        inline void remove_iterator(iterator_base* it)
        {
#if 1
            /* iterator should hold this node */
            if(it->m_node != this)
                throw misc::exception("invalid list_node");
#endif

            if(!m_itarray)
                return;

            /* before iterator gets destroyed, it
               removes itself from the node it points to.
            */
            for(size_t i=0; i < m_itarray->size(); ++i)
            {
                if(it == (*m_itarray)[i])
                {
                    m_itarray->erase( m_itarray->begin() + i );
                    return;
                }
            }
        }

        inline void invalidate_iterators()
        {
            if(!m_itarray)
                return;

            /* when a node gets deleted, all its iterators
               are invalidated
            */
            for(size_t i=0; i < m_itarray->size(); ++i)
            {
                (*m_itarray)[i]->m_cont = 0;
            }
            m_itarray->resize(0);
        }

        inline void update_container(container* cont)
        {
            if(!m_itarray)
                return;

            /* when a node is moved to another container
               its iterators are (probably) updated as well.
            */
            for(size_t i=0; i < m_itarray->size(); ++i)
            {
                (*m_itarray)[i]->m_cont = cont;
            }
        }


    public:
        list_node*                      m_prev;
        list_node*                      m_next;
        typename container::value_type  m_T;

        // debug_iterator implementation
        iterator_array*                 m_itarray;
    };  // end list_node;


	/* container attributes */
	enum Attributes
	{
		GENERIC_LIST_NONE = 0,
		GENERIC_LIST_HAS_ITERATOR_DEBUGGING = 1
		// GENERIC_LIST_IS_MULTI_THREADING = 1 << 1
		// etc
	};


    // forward declarations
	
    template<typename container, typename node> class list_const_iterator;
    template<typename container, typename node> class list_const_reverse_iterator;
	template<typename T, typename Allocator, int attributes> class list;




    /* list iterator */
    template<typename container, typename node>
    class list_iterator :
        public misc::iterator<misc::bidirectional_iterator_tag, typename container::value_type>,
        public list_iterator_base<container, node>
    {
    public:
        typedef misc::iterator<misc::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::pointer             pointer;
        typedef typename base::reference           reference;
        typedef typename misc::list_iterator_base<container, node> base2;

        friend class misc::list<typename container::value_type, typename container::allocator_type, container::nattributes>;
        friend class list_const_iterator<container, node>;

    private:
        inline void init()
        {
            base2::m_node = 0;
            base2::m_cont = 0;
        }

        list_iterator(node* n, container* cont)
        {
            init();

            base2::m_node = n;
            base2::m_cont = cont;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }
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
            if(base2::m_cont)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }
        }

        list_iterator& operator=(const list_iterator& it)
        {
            if(this != &it)
            {
                if(base2::m_cont)
                {
                    base2::m_cont->remove_iterator(base2::m_node, this);
                }

                base2::m_node = it.base2::m_node;
                base2::m_cont = it.base2::m_cont;

                if(base2::m_cont)
                {
                    base2::m_cont->add_iterator(base2::m_node, this);
                }
            }
            return *this;
        }

        reference operator*()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return base2::m_node->m_T;
        }

        pointer operator->()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return &(base2::m_node->m_T);
        }

        list_iterator& operator++()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_next;

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_iterator operator++(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            list_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_next;

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        list_iterator& operator--()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_begin)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_prev;

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_iterator operator--(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_begin)
                throw misc::exception("invalid iterator");

            list_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_prev;

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        bool operator==(const list_iterator& it)const
        {
            if(base2::m_cont == 0 || it.base2::m_cont == 0)
                throw misc::exception("invalid iterator");

            return (base2::m_node == it.base2::m_node);
        }

        bool operator!=(const list_iterator& it)const
        {
            return !(*this == it);
        }
    };  // iterator



    template<typename container, typename node>
    class list_const_iterator :
        public misc::const_iterator<misc::bidirectional_iterator_tag, typename container::value_type>,
        private list_iterator_base<container, node>
    {
    public:
        typedef misc::const_iterator<misc::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;
        typedef typename misc::list_iterator_base<container, node> base2;

        friend class misc::list<typename container::value_type, typename container::allocator_type, container::nattributes>;

    private:
        inline void init()
        {
            base2::m_node = 0;
            base2::m_cont = 0;
        }

        list_const_iterator(node* n, container* cont)
        {
            init();

            base2::m_node = n;
            base2::m_cont = cont;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }
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
            if(base2::m_cont)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }
        }

        list_const_iterator& operator=(const list_const_iterator& it)
        {
            if(this != &it)
            {
                if(base2::m_cont)
                {
                    base2::m_cont->remove_iterator(base2::m_node, this);
                }

                base2::m_node = it.base2::m_node;
                base2::m_cont = it.base2::m_cont;

                if(base2::m_cont)
                {
                    base2::m_cont->add_iterator(base2::m_node, this);
                }
            }
            return *this;
        }

        list_const_iterator& operator=(const list_iterator<container, node>& it)
        {
            if(base2::m_cont)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }

            base2::m_node = it.base2::m_node;
            base2::m_cont = it.base2::m_cont;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }

            return *this;
        }

        list_const_iterator(const list_iterator<container, node>& it)
        {
            init();
            *this = it;
        }

        reference operator*()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return base2::m_node->m_T;
        }

        pointer operator->()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return &(base2::m_node->m_T);
        }

        list_const_iterator& operator++()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_next;

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_const_iterator operator++(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            list_const_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_next;

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        list_const_iterator& operator--()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_begin)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_prev;

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_const_iterator operator--(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_begin)
                throw misc::exception("invalid iterator");

            list_const_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            base2::m_node = base2::m_node->m_prev;

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        bool operator==(const list_const_iterator& it)const
        {
            if(base2::m_cont == 0 || it.base2::m_cont == 0)
                throw misc::exception("invalid iterator");

            return (base2::m_node == it.base2::m_node);
        }

        bool operator!=(const list_const_iterator& it)const
        {
            return !(*this == it);
        }
    };  // const_iterator


    template<typename container, typename node>
    class list_reverse_iterator :
        public misc::iterator<misc::bidirectional_iterator_tag, typename container::value_type>,
        private list_iterator_base<container, node>
    {
    public:
        typedef misc::iterator<misc::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::pointer             pointer;
        typedef typename base::reference           reference;
        typedef typename misc::list_iterator_base<container, node> base2;


        friend class misc::list<typename container::value_type, typename container::allocator_type, container::nattributes>;
        friend class list_const_reverse_iterator<container, node>;

    private:
        inline void init()
        {
            base2::m_node = 0;
            base2::m_cont = 0;
        }
		
        list_reverse_iterator(node* n, container* cont)
        {
            init();

            base2::m_node = n;
            base2::m_cont = cont;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }
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
            if(base2::m_cont != 0)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }
        }

        list_reverse_iterator& operator=(const list_reverse_iterator& it)
        {
            if(this != &it)
            {
                if(base2::m_cont)
                {
                    base2::m_cont->remove_iterator(base2::m_node, this);
                }

                base2::m_node = it.base2::m_node;
                base2::m_cont = it.base2::m_cont;

                if(base2::m_cont)
                {
                    base2::m_cont->add_iterator(base2::m_node, this);
                }
            }
            return *this;
        }

        reference operator*()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return base2::m_node->m_T;
        }

        pointer operator->()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return &(base2::m_node->m_T);
        }

        list_reverse_iterator& operator++()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            // end of list is not m_begin, but m_end
            if(base2::m_node == base2::m_cont->m_begin)
            {
                base2::m_node = base2::m_cont->m_end;
            }
            else
            {
                base2::m_node = base2::m_node->m_prev;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_reverse_iterator operator++(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            list_reverse_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            // end of list is not m_begin, but m_end
            if(base2::m_node == base2::m_cont->m_begin)
            {
                base2::m_node = base2::m_cont->m_end;
            }
            else
            {
                base2::m_node = base2::m_node->m_prev;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        list_reverse_iterator& operator--()
        {
            if(base2::m_cont == 0 || base2::m_cont->empty() || base2::m_node == base2::m_cont->m_end->m_prev)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            if(base2::m_node == base2::m_cont->m_end)
            {
                base2::m_node = base2::m_cont->m_begin;
            }
            else
            {
                base2::m_node = base2::m_node->m_next;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_reverse_iterator operator--(int)
        {
            if(base2::m_cont == 0 || base2::m_cont->empty() || base2::m_node == base2::m_cont->m_end->m_prev)
                throw misc::exception("invalid iterator");

            list_reverse_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            if(base2::m_node == base2::m_cont->m_end)
            {
                base2::m_node = base2::m_cont->m_begin;
            }
            else
            {
                base2::m_node = base2::m_node->m_next;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        bool operator==(const list_reverse_iterator& it)const
        {
            if(base2::m_cont == 0 || it.base2::m_cont == 0)
                throw misc::exception("invalid iterator");

            return (base2::m_node == it.base2::m_node);
        }

        bool operator!=(const list_reverse_iterator& it)const
        {
            return !(*this == it);
        }
    };  // reverse_iterator


    template<typename container, typename node>
    class list_const_reverse_iterator :
        public misc::const_iterator<misc::bidirectional_iterator_tag, typename container::value_type>,
        private list_iterator_base<container, node>
    {
    public:
        typedef misc::const_iterator<misc::bidirectional_iterator_tag, typename container::value_type> base;
        typedef typename base::iterator_category   iterator_category;
        typedef typename base::value_type          value_type;
        typedef typename base::difference_type     difference_type;
        typedef typename base::distance_type       distance_type;
        typedef typename base::const_pointer       pointer;
        typedef typename base::const_reference     reference;
        typedef typename misc::list_iterator_base<container, node> base2;

        friend class misc::list<typename container::value_type, typename container::allocator_type, container::nattributes>;


    private:
        inline void init()
        {
            base2::m_node = 0;
            base2::m_cont = 0;
        }

        list_const_reverse_iterator(node* n, container* cont)
        {
            init();

            base2::m_node = n;
            base2::m_cont = cont;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }
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
            if(base2::m_cont != 0)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }
        }

        list_const_reverse_iterator& operator=(const list_const_reverse_iterator& it)
        {
            if(this != &it)
            {
                if(base2::m_cont)
                {
                    base2::m_cont->remove_iterator(base2::m_node, this);
                }

                base2::m_cont = it.base2::m_cont;
                base2::m_node = it.base2::m_node;

                if(base2::m_cont)
                {
                    base2::m_cont->add_iterator(base2::m_node, this);
                }
            }
            return *this;
        }

        list_const_reverse_iterator& operator=(const list_reverse_iterator<container, node>& it)
        {
            if(base2::m_cont)
            {
                base2::m_cont->remove_iterator(base2::m_node, this);
            }

            base2::m_cont = it.base2::m_cont;
            base2::m_node = it.base2::m_node;

            if(base2::m_cont)
            {
                base2::m_cont->add_iterator(base2::m_node, this);
            }

            return *this;
        }

        list_const_reverse_iterator(const list_reverse_iterator<container, node>& it)
        {
            init();
            *this = it;
        }

        reference operator*()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return base2::m_node->m_T;
        }

        pointer operator->()const
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            return &(base2::m_node->m_T);
        }

        list_const_reverse_iterator& operator++()
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            // end of list is not m_begin, but m_end
            if(base2::m_node == base2::m_cont->m_begin)
            {
                base2::m_node = base2::m_cont->m_end;
            }
            else
            {
                base2::m_node = base2::m_node->m_prev;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_const_reverse_iterator operator++(int)
        {
            if(base2::m_cont == 0 || base2::m_node == base2::m_cont->m_end)
                throw misc::exception("invalid iterator");

            list_const_reverse_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);

            // end of list is not m_begin, but m_end
            if(base2::m_node == base2::m_cont->m_begin)
            {
                base2::m_node = base2::m_cont->m_end;
            }
            else
            {
                base2::m_node = base2::m_node->m_prev;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        list_const_reverse_iterator& operator--()
        {
            if(base2::m_cont == 0 || base2::m_cont->empty() || base2::m_node == base2::m_cont->m_end->m_prev)
                throw misc::exception("invalid iterator");

            base2::m_cont->remove_iterator(base2::m_node, this);

            if(base2::m_node == base2::m_cont->m_end)
            {
                base2::m_node = base2::m_cont->m_begin;
            }
            else
            {
                base2::m_node = base2::m_node->m_next;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return *this;
        }

        list_const_reverse_iterator operator--(int)
        {
            if(base2::m_cont == 0 || base2::m_cont->empty() || base2::m_node == base2::m_cont->m_end->m_prev)
                throw misc::exception("invalid iterator");

            list_const_reverse_iterator tmp = *this;

            base2::m_cont->remove_iterator(base2::m_node, this);


            if(base2::m_node == base2::m_cont->m_end)
            {
                base2::m_node = base2::m_cont->m_begin;
            }
            else
            {
                base2::m_node = base2::m_node->m_next;
            }

            base2::m_cont->add_iterator(base2::m_node, this);

            return tmp;
        }

        bool operator==(const list_const_reverse_iterator& it)const
        {
            if(base2::m_cont == 0 || it.base2::m_cont == 0)
                throw misc::exception("invalid iterator");

            return (base2::m_node == it.base2::m_node);
        }

        bool operator!=(const list_const_reverse_iterator& it)const
        {
            return !(*this == it);
        }
    };  // class



    /* ISO/IEC 14882:2003(E)   $23.2.2 Class template list

       One exception from ISO is the extended attribute(s),
       to indicate additional properties of this container
       e.g. debug_iterator, multi threading, etc.
    */
    template<typename T, typename Allocator = misc::allocator<T>, int attributes = 0>
    class list
    {
    public:
        // types:
        typedef list<T, Allocator, attributes>           container;
        typedef typename Allocator::reference            reference;
        typedef typename Allocator::const_reference      const_reference;
        typedef typename Allocator::pointer              pointer;
        typedef typename Allocator::const_pointer        const_pointer;

        typedef typename Allocator::value_type           value_type;
        typedef typename Allocator::size_type            size_type;
        typedef typename Allocator::difference_type      difference_type;
        typedef Allocator                                allocator_type;


    public:
        typedef list_iterator<container, list_node<container> >          iterator;
        typedef list_const_iterator<container, list_node<container> >    const_iterator;
        typedef list_reverse_iterator<container, list_node<container> >  reverse_iterator;
        typedef list_const_reverse_iterator<container, list_node<container> > const_reverse_iterator;


    private:
        friend class list_iterator<container, list_node<container> >;
        friend class list_const_iterator<container, list_node<container> >;
        friend class list_reverse_iterator<container, list_node<container> >;
        friend class list_const_reverse_iterator<container, list_node<container> >;
        friend struct list_iterator_base<container, list_node<container> >;
        typedef list_iterator_base<container, list_node<container> > iterator_base;


    private:
        list_node<container>*      m_begin;
        list_node<container>*      m_end;
        size_type                  m_size;
        typename Allocator::template rebind<list_node<container> >::other  m_NodAlloc;
	
	public:
		static const int nattributes = attributes;
    
    private:
        inline void init(const Allocator& alloc)
        {
            m_NodAlloc = alloc;
            m_end = m_NodAlloc.allocate(1);
			//TODO: c++0x has changed construct parameters (adapt if needed)
			
			/*	Define a place holder for end position. No construction allowed
				to avoid potential circular reference
				struct Node { list<Node> n; }
			*/
			// m_NodAlloc.construct(m_end, 0);
            // m_end->m_T; Default ctor is not allowed.

            m_end->m_prev = 0;
            m_end->m_next = 0;
			m_end->m_itarray = 0;
            m_begin = m_end;
            m_size = 0;
        }

		inline void deinit()
		{
			if(m_size > 0 || m_begin != m_end)
				throw misc::exception("container is not empty");

			// m_NodAlloc.destroy(m_end);  - not constructed

			// Release the array allocated for end node's iterators.
			if(m_end->m_itarray != 0)
			{
				delete m_end->m_itarray;
				m_end->m_itarray = 0;
			}

			m_NodAlloc.deallocate(m_end, 1);
		}

        /* iterator debugging
           since container carries this attribute it may allow or not
           iterators to register with the nodes they hold.
        */
        void add_iterator(list_node<container>* nod, iterator_base* it)
        {
            if( attributes & GENERIC_LIST_HAS_ITERATOR_DEBUGGING )
            {
                nod->add_iterator(it);
            }
        }

        inline void remove_iterator(list_node<container>* nod, iterator_base* it)
        {
            if( attributes & GENERIC_LIST_HAS_ITERATOR_DEBUGGING )
            {
                nod->remove_iterator(it);
            }
        }

        inline void invalidate_iterators(list_node<container>* nod)
        {
            if( attributes & GENERIC_LIST_HAS_ITERATOR_DEBUGGING )
            {
                nod->invalidate_iterators();
            }
        }

        inline void update_container(list_node<container>* nod, container* cont)
        {
            if( attributes & GENERIC_LIST_HAS_ITERATOR_DEBUGGING )
            {
                nod->update_container(cont);
            }
        }

    public:

        // $23.2.2.1 construct/copy/destroy:
        explicit list(const Allocator& alloc= Allocator())
        {
            init(alloc);
        }

        explicit list(size_type n, const value_type& value = value_type(),
                      const Allocator& alloc= Allocator())
        {
            init(alloc);
            assign(n, value);
        }


        template<typename InputIterator>
        explicit list(InputIterator first, InputIterator last,
                      const Allocator& alloc = Allocator())
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

            invalidate_iterators(m_end);

            deinit();
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
        inline void assign_impl(InputIterator first, InputIterator last, misc::bidirectional_iterator_tag)
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
        inline void assign_impl(InputIterator n, InputIterator u, misc::input_iterator_tag)
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
            assign_impl(first, last, typename misc::iterator_traits<InputIterator>::iterator_category());
        }

        void assign(size_type n, const value_type& u)
        {
            if(n > max_size())
                throw misc::exception("size is too big");

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
            return m_NodAlloc;
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

        // $23.2.2.2 capacity:
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


        // $23.2.2.2  element access:
        reference front()
        {
            if(m_size == 0)
                throw misc::exception("empty container");

            return m_begin->m_T;
        }

        const_reference front() const
        {
            if(m_size == 0)
                throw misc::exception("empty container");

            return m_begin->m_T;
        }

        reference back()
        {
            if(m_size == 0)
                throw misc::exception("empty container");

            return m_end->m_prev->m_T;
        }

        const_reference back() const
        {
            if(m_size == 0)
                throw misc::exception("empty container");

            return m_end->m_prev->m_T;
        }


        // $23.2.2.3 modifiers:
        void push_front(const value_type& x)
        {
            list_node<container>* nod = m_NodAlloc.allocate(1);
            m_NodAlloc.construct(nod, x);

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
                throw misc::exception("container is empty");

            list_node<container>* next = m_begin->m_next;

            invalidate_iterators(m_begin);

            m_NodAlloc.destroy(m_begin);
            m_NodAlloc.deallocate(m_begin, 1);

            next->m_prev = 0;
            m_begin = next;

            --m_size;
        }

        void push_back(const value_type& x)
        {
            list_node<container>* nod = m_NodAlloc.allocate(1);
            m_NodAlloc.construct(nod, x);

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
                throw misc::exception("container is empty");

            // > 1
            if(m_size > 1)
            {
                list_node<container>* nod = m_end->m_prev;
                list_node<container>* prev = nod->m_prev;

                invalidate_iterators(nod);

                m_NodAlloc.destroy(nod);
                m_NodAlloc.deallocate(nod, 1);

                m_end->m_prev = prev;
                prev->m_next = m_end;
            }
            // == 1
            else
            {
                invalidate_iterators(m_begin);

                m_NodAlloc.destroy(m_begin);
                m_NodAlloc.deallocate(m_begin, 1);

                m_end->m_prev = 0;
                m_begin = m_end;
            }

            --m_size;
        }

        iterator insert(iterator position, const value_type& x)
        {
            if(position.m_cont != this)
                throw misc::exception("Invalid iterator.");

            list_node<container>* nod = m_NodAlloc.allocate(1);
            m_NodAlloc.construct(nod, x);

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
                throw misc::exception("size is too big");

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
                throw misc::exception("Invalid iterator.");


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

            invalidate_iterators(nod);

            m_NodAlloc.destroy(nod);
            m_NodAlloc.deallocate(nod, 1);

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
            misc::swap<list_node<container>*>(m_begin, lst.m_begin);
            misc::swap<list_node<container>*>(m_end, lst.m_end);
            misc::swap<size_type>(m_size, lst.m_size);

            for(list_node<container>* nod = m_begin; nod != m_end; nod = nod->m_next)
            {
                // already swapped, contains lst nodes
                update_container(nod, this);
            }

            for(list_node<container>* nod = lst.m_begin; nod != lst.m_end; nod = nod->m_next)
            {
                // already swapped, contains this nodes
                update_container(nod, &lst);
            }
        }

        void clear()
        {
            list_node<container>* next;
            for(; m_begin != m_end; m_begin = next)
            {
                next = m_begin->m_next;

                invalidate_iterators(m_begin);

                m_NodAlloc.destroy(m_begin);
                m_NodAlloc.deallocate(m_begin, 1);
            }

            m_end->m_prev = 0;
            m_begin = m_end;
            m_size = 0;
        }


//TODO: "check n3485 for all functions that should/should not invalidate iterators"		
        /* current implementation uses 14882 / 2003 where iterators get invalidated */

        // $23.2.2.4 list operations:
        void splice(iterator position, container& x)
        {
            /*
              Inserts the contents of x before position and x becomes empty.
              Invalidates all iterators and references to the list x.
            */
            if(position.m_cont != this)
                throw misc::exception("Invalid iterator.");

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


            // Invalidates all iterators and references to the list x.
            for(list_node<container>* nod = first;  nod != last->m_next; nod=nod->m_next)
            {
                invalidate_iterators(nod);
            }
        }



        void splice(iterator position, container& x, iterator i)
        {
            /*
              Inserts an element pointed to by i from list x before position and removes the element from x.
              The result is unchanged if position == i or position == ++i.
              Invalidates only the iterators and references to the spliced element.
            */
            if(position.m_cont != this || i.m_cont != &x || i.m_node == x.m_end)
                throw misc::exception("Invalid iterator.");

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


            // update size
            if(&x != this)
            {
                --x.m_size;
                ++m_size;

                // Invalidates only the iterators and references to the spliced element.
                invalidate_iterators(i.m_node);
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
                throw misc::exception("Invalid iterator.");

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
                    throw misc::exception("Insert position is inside [first, last] range. Result is undefined.");
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


            // count the incoming elements
            size_type size = 0;
            list_node<container>* nod = sbeg;
            for(; nod != dend; nod = nod->m_next)
            {
                ++size;

                // Invalidates only the iterators and references to the spliced elements.
                // obs: splice during iteration through container may switch compared iterators
                //      positions within container. For safety reason, iterators to spliced elements
                //      should become invalid.
                invalidate_iterators(nod);
            }

            // update size
            if(&x != this)
            {
                x.m_size -= size;
                m_size += size;
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
            merge_impl< misc::less<value_type> >(*this, x, dst, misc::less<value_type>());
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
            misc::advance(mid, middle);

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
            merge_sort< misc::less<value_type> >(dst, *this, misc::less<value_type>());
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
                misc::swap<list_node<container>*>(nod->m_next, nod->m_prev);
                nod = tmp;
            }

            // re-connect begin & end of the container
            misc::swap<list_node<container>*>(m_end->m_prev, m_begin);
            m_begin->m_prev = 0;
            m_end->m_prev->m_next = m_end;
        }


    };  // list
}  // namespace misc



#endif//__list_hpp__
