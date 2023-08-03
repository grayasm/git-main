/*
Copyright (C) 2009 Mihai Vasilian
*/


#ifndef __tree_hpp__
#define __tree_hpp__


//stl


//lib
#include "autoptr.hpp"
#include "list.hpp"

//#include "iterator.hpp"
//#include "exception.hpp"
//#include "memory.hpp"
//#include "memmanip.hpp"
//#include "algorithm.hpp"



namespace misc
{
	template<typename T, typename Allocator>
	class tree;

    /*
      Note on Preorder_Iterator and Preorder_Const_Iterator:


                             root
                              |
                  |-----------|-----------------|
                  1           2                 3
              |-------|       |                 |
              4       7       9                12
          |-------|   |       |            |---------|
          5       6   8      10            13       14
                              |
                             11


      Preorder_Iterator iterates recursively in all lists as follows:
      Preorder_Iterator::operator++(): 1,4,5,6,7,8,2,9,10,11,3,12,13,14
      Preorder_Iterator::operator--(): 14,13,12,3,11,10,9,2,8,7,6,5,4,1

    */


	template<typename container>
	class Preorder_Iterator : 
		public stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::pointer				pointer;
		typedef typename base::reference			reference;

		typedef typename container::iterator		Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	private:
		Iterator	m_it;
		Tree*		m_tree;

	public:
		Preorder_Iterator();
		~Preorder_Iterator();
		Preorder_Iterator(const Iterator& it, const Tree& tr);
		Preorder_Iterator(const Preorder_Iterator& rit);
		bool operator==(const Preorder_Iterator& it) const;
		bool operator!=(const Preorder_Iterator& it) const;
		value_type& operator*() const;
		value_type* operator->() const;
		Preorder_Iterator& operator++();
		Preorder_Iterator operator++(int);
		Preorder_Iterator& operator--();
		Preorder_Iterator operator--(int);

	private:
		// Wrap List::operator==(..) in a try/catch to avoid exceptions in DEBUG
		// This may happen when comparing 2 iterators of 2 different stl::list.
		// This is possible while walking up and down the tree node's list.
		bool Eq(const Iterator& itl, const Iterator& itr) const;
	};



	template<typename container>
	class Preorder_Const_Iterator : 
		private Preorder_Iterator<container>,
		public stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::const_pointer		pointer;
		typedef typename base::const_reference		reference;

		typedef Preorder_Iterator<container>		baseIt;
		typedef typename baseIt::Iterator			Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	public:
		Preorder_Const_Iterator();
		~Preorder_Const_Iterator();
		Preorder_Const_Iterator(const Iterator& it, const Tree& tr);
		Preorder_Const_Iterator(const Preorder_Const_Iterator& rit);
		Preorder_Const_Iterator(const Preorder_Iterator<container>& it);
		bool operator==(const Preorder_Const_Iterator& it) const;
		bool operator!=(const Preorder_Const_Iterator& it) const;
		const value_type& operator*() const;
		const value_type* operator->() const;
		Preorder_Const_Iterator& operator++();
		Preorder_Const_Iterator operator++(int);
		Preorder_Const_Iterator& operator--();
		Preorder_Const_Iterator operator--(int);
	};



    /*
      Note on Postorder_Iterator and Postorder_Const_Iterator:


                            root
                             |
                 |-----------|-----------------|
                 1           2                 3
             |-------|       |                 |
             4       7       9                12
         |-------|   |       |            |---------|
         5       6   8      10            13       14
                             |
                            11



      Postorder_Iterator iterates recursively in all lists as follows:
      Postorder_Iterator::operator++(): 5,6,4,8,7,1,11,10,9,2,13,14,12,3
      Postorder_Iterator::operator--(): 3,12,14,13,2,9,10,11,1,7,8,4,6,5
    */
	template<typename container>
	class Postorder_Iterator : 
		public stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category   iterator_category;
		typedef typename base::value_type          value_type;
		typedef typename base::difference_type     difference_type;
		typedef typename base::distance_type       distance_type;
		typedef typename base::pointer             pointer;
		typedef typename base::reference           reference;

		typedef typename container::iterator Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	private:
		Iterator	m_it;
		Tree*		m_tree;

	public:
		Postorder_Iterator();
		~Postorder_Iterator();
		Postorder_Iterator(const Iterator& it, const Tree& tr);
		Postorder_Iterator(const Postorder_Iterator& rit);
		bool operator==(const Postorder_Iterator& it) const;
		bool operator!=(const Postorder_Iterator& it) const;
		value_type& operator*() const;
		value_type* operator->() const;
		Postorder_Iterator& operator++();
		Postorder_Iterator operator++(int);
		Postorder_Iterator& operator--();
		Postorder_Iterator operator--(int);
	private:
		// Wrap List::operator==(..) in a try/catch to avoid exceptions in DEBUG
		// This may happen when comparing 2 iterators of 2 different stl::list.
		// This is possible while walking up and down the tree node's list.
		bool Eq(const Iterator& lhs, const Iterator& rhs) const;
	};


	template<typename container>
	class Postorder_Const_Iterator :
		private Postorder_Iterator<container>,
		public stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::const_pointer		pointer;
		typedef typename base::const_reference		reference;

		typedef Postorder_Iterator<container>		base2;
		typedef typename base2::Iterator			Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	public:
		Postorder_Const_Iterator();
		~Postorder_Const_Iterator();
		Postorder_Const_Iterator(const Iterator& it, const Tree& tr);
		Postorder_Const_Iterator(const Postorder_Const_Iterator& rit);
		Postorder_Const_Iterator(const Postorder_Iterator<container>& it);
		bool operator==(const Postorder_Const_Iterator& it) const;
		bool operator!=(const Postorder_Const_Iterator& it) const;
		const value_type& operator*() const;
		const value_type* operator->() const;
		Postorder_Const_Iterator& operator++();
		Postorder_Const_Iterator operator++(int);
		Postorder_Const_Iterator& operator--();
		Postorder_Const_Iterator operator--(int);
	};


    /*
      Note on First_Branch_Iterator:


                                root
                                 |
                     |-----------|-----------------|
                     1           2                 3
                 |-------|       |                 |
                 4       7       9                12
             |-------|   |       |            |---------|
             5       6   8      10            13       14
                                 |
                                11


      First_Branch_Iterator iterates only on right most branch (of given iterator, or root)
      First_Branch_Iterator::operator++(): 1,4,5 or: 7,8 or: 2,9,10,11 or: 3,12,13 or: 14
      First_Branch_Iterator::operator--(): 14, or: 13,12,3 or: 11,10,9,2 or: 8,7 or: 5,4,1
    */
	template<typename container>
	class First_Branch_Iterator : 
		public stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::pointer				pointer;
		typedef typename base::reference			reference;

		typedef typename container::iterator		Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	private:
		Iterator	m_it;
		Tree*		m_tree;

	public:
		First_Branch_Iterator();
		~First_Branch_Iterator();
		First_Branch_Iterator(const Iterator& it, const Tree& tr);
		First_Branch_Iterator(const First_Branch_Iterator& fit);
		bool operator==(const First_Branch_Iterator& it) const;
		bool operator!=(const First_Branch_Iterator& it) const;
		value_type& operator*() const;
		value_type* operator->() const;
		First_Branch_Iterator& operator++();
		First_Branch_Iterator operator++(int);
		First_Branch_Iterator& operator--();
		First_Branch_Iterator operator--(int);

	private:
		// Wrap List::operator==(..) in a try/catch to avoid exceptions in DEBUG
		// This may happen when comparing 2 iterators of 2 different stl::list.
		// This is possible while walking up and down the tree node's list.
		bool Eq(const Iterator& lhs, const Iterator& rhs) const;
	};


	template<typename container>
	class First_Branch_Const_Iterator : 
		private First_Branch_Iterator<container>,
		public stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::const_pointer		pointer;
		typedef typename base::const_reference		reference;

		typedef First_Branch_Iterator<container>	base2;
		typedef typename base2::Iterator			Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	public:
		First_Branch_Const_Iterator();
		~First_Branch_Const_Iterator();
		First_Branch_Const_Iterator(const Iterator& it, const Tree& tr);
		First_Branch_Const_Iterator(const First_Branch_Const_Iterator& fit);
		bool operator==(const First_Branch_Const_Iterator& it) const;
		bool operator!=(const First_Branch_Const_Iterator& it) const;
		const value_type& operator*() const;
		const value_type* operator->() const;
		First_Branch_Const_Iterator& operator++();
		First_Branch_Const_Iterator operator++(int);
		First_Branch_Const_Iterator& operator--();
		First_Branch_Const_Iterator operator--(int);
	};



    /*
      Notes on Child_Iterator and Child_Const_Iterator:

                           root
                            |
                |-----------|-----------------|
                1           2                 3
            |-------|       |                 |
            4       7       9                12
        |-------|   |       |            |---------|
        5       6   8      10            13       14
                            |
                           11

      Child_Iterator::operator++() iterates in children list of given iterator,
      or in root's children list (default)
      ex: 1,2,3 or: 4,7  or: 5,6 or: 8, or: 9, or: 10, or: 11, or: 13,14, etc
    */

	template<typename container>
	class Child_Iterator : 
		public stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::pointer				pointer;
		typedef typename base::reference			reference;

		typedef typename container::iterator		Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	private:
		Iterator	m_it;
		Tree*		m_tree;

	public:
		Child_Iterator();
		~Child_Iterator();
		Child_Iterator(const Iterator& it, const Tree& tr);
		Child_Iterator(const Child_Iterator& fit);
		bool operator==(const Child_Iterator& it) const;
		bool operator!=(const Child_Iterator& it) const;
		value_type& operator*() const;
		value_type* operator->() const;
		Child_Iterator& operator++();
		Child_Iterator operator++(int);
		Child_Iterator& operator--();
		Child_Iterator operator--(int);
	private:
		bool Eq(const Iterator& lhs, const Iterator& rhs) const;
	};


	template<typename container>
	class Child_Const_Iterator : 
		private Child_Iterator<container>,
		public stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type>
	{
	public:
		typedef stl::const_iterator<stl::bidirectional_iterator_tag, typename container::value_type> base;
		typedef typename base::iterator_category	iterator_category;
		typedef typename base::value_type			value_type;
		typedef typename base::difference_type		difference_type;
		typedef typename base::distance_type		distance_type;
		typedef typename base::const_pointer		pointer;
		typedef typename base::const_reference		reference;

		typedef Child_Iterator<container>			base2;
		typedef typename base2::Iterator			Iterator;
		typedef typename misc::tree<typename container::value_type, typename container::allocator_type> Tree;
		friend class misc::tree<typename container::value_type, typename container::allocator_type>;

	public:
		Child_Const_Iterator();
		~Child_Const_Iterator();
		Child_Const_Iterator(const Iterator& it, const Tree& tr);
		Child_Const_Iterator(const Child_Const_Iterator& fit);
		bool operator==(const Child_Const_Iterator& it) const;
		bool operator!=(const Child_Const_Iterator& it) const;
		const value_type& operator*() const;
		const value_type* operator->() const;
		Child_Const_Iterator& operator++();
		Child_Const_Iterator operator++(int);
		Child_Const_Iterator& operator--();
		Child_Const_Iterator operator--(int);
	};


	template<typename T>
	class tree_node
	{
	public:
		typedef T								value_type;
		typedef stl::list<tree_node>			List;
		typedef typename List::iterator			iterator;
		typedef typename List::const_iterator	const_iterator;

	public:
		tree_node();
		tree_node(tree_node* owner, const value_type& val);
		tree_node(const tree_node& t);
		~tree_node();
		tree_node& operator=(const tree_node& t);

	private:
		void init();
		void destroy();

	public:
		List						m_list;
		iterator					m_it;
		tree_node*					m_owner;
		value_type*					m_T;
	};  // tree_node



	template<typename T, typename Allocator = stl::allocator<T> >
	class tree
	{
	public:
		typedef tree<T, Allocator>						container;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef typename Allocator::value_type			value_type;
		typedef typename Allocator::size_type			size_type;
		typedef typename Allocator::difference_type		difference_type;		
		typedef Allocator								allocator_type;		

	public:
		typedef stl::autoptr<container>					Ptr;

		//Iterators
		typedef typename misc::tree_node<T>::List		List;
		typedef typename List::iterator					iterator;
		typedef Preorder_Iterator<container>			preorder_iterator;
		typedef Preorder_Const_Iterator<container>		preorder_const_iterator;
		typedef Postorder_Iterator<container>			postorder_iterator;
		typedef Postorder_Const_Iterator<container>		postorder_const_iterator;
		typedef First_Branch_Iterator<container>		first_branch_iterator;
		typedef First_Branch_Const_Iterator<container>	first_branch_const_iterator;
		typedef Child_Iterator<container>				child_iterator;
		typedef Child_Const_Iterator<container>			child_const_iterator;

	public:
		// If an iterator points to tree's end position it cannot be dereferenced
		// and it cannot be decremented safely without access to tree->m_root.list
		// Tree's end position is tree->m_root.m_list.end()
		// Iterators need access to tree->m_root.m_list to safely decrement.
		// Hence this friendship below.
		friend class Preorder_Iterator<misc::tree<T, Allocator> >;
		friend class Postorder_Iterator<misc::tree<T, Allocator> >;
		friend class First_Branch_Iterator<misc::tree<T, Allocator> >;
		friend class Child_Iterator<misc::tree<T, Allocator> >;

	private:
		void deep_copy_node(tree_node<T>& dest, const tree_node<T>& src);
		void deep_copy_tree(const container& tc);

	private:
		tree_node<T>	m_root;
		size_t			m_size;


	public:
		tree();
		~tree();
		tree(const tree& t);
		tree& operator=(const tree& t);

		bool operator==(const tree& t) const;
		bool operator!=(const tree& t) const;

		iterator get_iterator(preorder_iterator it) const;
		iterator get_iterator(preorder_const_iterator it) const;
		iterator get_iterator(postorder_iterator it) const;
		iterator get_iterator(postorder_const_iterator it) const;
		iterator get_iterator(first_branch_iterator it) const;
		iterator get_iterator(first_branch_const_iterator it) const;
		iterator get_iterator(child_iterator it) const;
		iterator get_iterator(child_const_iterator it) const;


		iterator push_back(const value_type& val);
		iterator push_front(const value_type& val);
		iterator insert_sibling_before(iterator i, const value_type& val);
		iterator insert_sibling_after(iterator i, const value_type& val);
		iterator push_back_child(iterator i, const value_type& val);
		iterator push_front_child(iterator i, const value_type& val);


		preorder_iterator preorder_begin();
		preorder_iterator preorder_end();
		preorder_const_iterator preorder_begin() const;
		preorder_const_iterator preorder_end() const;

		postorder_iterator postorder_begin();
		postorder_iterator postorder_end();
		postorder_const_iterator postorder_begin() const;
		postorder_const_iterator postorder_end() const;

		first_branch_iterator first_branch_begin();
		first_branch_iterator first_branch_end();
		first_branch_iterator first_branch_begin(iterator it);
		first_branch_iterator first_branch_end(iterator it);

		first_branch_const_iterator first_branch_begin() const;
		first_branch_const_iterator first_branch_end() const;
		first_branch_const_iterator first_branch_begin(iterator it) const;
		first_branch_const_iterator first_branch_end(iterator it) const;


		child_iterator child_begin();
		child_iterator child_end();
		child_iterator child_begin(iterator it);
		child_iterator child_end(iterator it);


		child_const_iterator child_begin() const;
		child_const_iterator child_end() const;
		child_const_iterator child_begin(iterator it) const;
		child_const_iterator child_end(iterator it) const;


		child_iterator siblings_begin(iterator it);
		child_iterator siblings_end(iterator it);
		child_const_iterator siblings_begin(iterator it) const;
		child_const_iterator siblings_end(iterator it) const;


		bool empty() const;
		size_t size() const;
		void clear();
		iterator erase(iterator it);

	private:
	protected:


	}; // tree


	//########################################################################
	//tree_node class
	template<typename T>
	tree_node<T>::tree_node()
	{
		init();
	}

	template<typename T>
	tree_node<T>::tree_node(tree_node* owner, const value_type& val)
	{
		init();
		m_owner = owner;
		m_T = new value_type(val);
	}

	template<typename T>
	tree_node<T>::tree_node(const tree_node& t)
	{
		init();
		*this=t;
	}

	template<typename T>
	tree_node<T>::~tree_node()
	{
		destroy();
	}

	template<typename T>
	tree_node<T>& tree_node<T>::operator=(const tree_node& t)
	{
		if(this!=&t)
		{
			destroy();
			init();

			m_list = t.m_list;

			//it is assumed that this copying originates from container (list) insert method.
			//new m_it is available as soon as this copying is finished,
			//and list's insert has returned the correct iterator;
			//m_it = t.m_it;

			//owner usually is passed on tree_node's ctor
			//when t comes from a preexisting list, this copying is not valid.
			//in this case, owner needs to be updated to new owner of this tree_node.
			m_owner = t.m_owner;
			if (t.m_T)
				m_T = new value_type(*(t.m_T));
		}
		return *this;
	}
	
	template<typename T>
	void tree_node<T>::init()
	{
		// m_list.clear();
		// m_it = typename List::iterator();
		m_owner = 0;
		m_T = 0;
	}

	template<typename T>
	void tree_node<T>::destroy()
	{
		//m_list - nothing
		//m_it - nothing
		//m_owner - nothing
		if(m_T)
		{
			delete m_T;
			m_T = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//Preorder_Iterator class
	template<typename container>
	Preorder_Iterator<container>::Preorder_Iterator()
	{
		m_tree = 0;
	}


	template<typename container>
	Preorder_Iterator<container>::~Preorder_Iterator()
	{
	}


	template<typename container>
	Preorder_Iterator<container>::Preorder_Iterator(const Iterator& it, const Tree& tr)
	{
		m_it = it;
		m_tree = const_cast<Tree*>(&tr);
	}

	template<typename container>
	Preorder_Iterator<container>::Preorder_Iterator(const Preorder_Iterator& rit)
	{
		m_it = rit.m_it;
		m_tree = rit.m_tree;
	}

	template<typename container>
	bool Preorder_Iterator<container>::operator==(const Preorder_Iterator& it) const
	{
		return Eq(m_it, it.m_it);
	}

	template<typename container>
	bool Preorder_Iterator<container>::operator!=(const Preorder_Iterator& it) const
	{
		return !(*this==it);
	}

	template<typename container>
	typename Preorder_Iterator<container>::value_type&
		Preorder_Iterator<container>::operator*() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return *(nod.m_T);
	}

	template<typename container>
	typename Preorder_Iterator<container>::value_type* 
		Preorder_Iterator<container>::operator->() const
	{
		const misc::tree_node<value_type>& nod = *m_it;
		return nod.m_T;
	}


	template<typename container>
	Preorder_Iterator<container>& Preorder_Iterator<container>::operator++()
	{
		//has children
		if( !m_it->m_list.empty() )
		{
			m_it = m_it->m_list.begin();
			return *this;
		}

		//has siblings
		Iterator sibl = m_it;
		if( ++sibl != m_it->m_owner->m_list.end() )	// same list, no throw
		{
			m_it = sibl;
			return *this;
		}

		//go up to next valid sibling
		Iterator up = m_it;
		while(up->m_owner != 0)
		{
			//end of tree
			if(up->m_owner->m_owner == 0)
			{
				// any further dereference of this iterator will throw
				m_it = up->m_owner->m_list.end();
				return *this;
			}

			//valid sibling
			up = up->m_owner->m_it;
			sibl = up;
			++sibl;
			if(sibl != up->m_owner->m_list.end())	// same list, no throw
			{
				m_it = sibl;
				return *this;
			}

			//invalid sibling, go up
			m_it = up;
		}

		throw stl::exception("iterator out of valid range");
	}


	template<typename container>
	Preorder_Iterator<container> Preorder_Iterator<container>::operator++(int)
	{
		Preorder_Iterator temp(*this);

		this->operator++();

		return temp;
	}


	template<typename container>
	Preorder_Iterator<container>& Preorder_Iterator<container>::operator--()
	{
		//end of tree
		if (Eq(m_it, m_tree->m_root.m_list.end()))	// throws in DEBUG
		{
			//empty tree
			if (m_tree->m_root.m_list.empty())
			{
				throw stl::exception("iterator out of valid range");
			}

			//when sibling available go left-down in loop
			Iterator down = --m_tree->m_root.m_list.end();
			while( !down->m_list.empty() )
			{
				down = --down->m_list.end();
			}

			m_it = down;

			return *this;
		}

		//if sibling not available go up
		Iterator up = m_it;
		if(up == up->m_owner->m_list.begin())	// same list, no throw
		{
			//end of the road
			if(up->m_owner->m_owner == 0)
			{
				throw stl::exception("iterator out of valid range");
			}

			//up
			m_it = up->m_owner->m_it;

			return *this;
		}

		// when sibling available go left-down in loop
		Iterator down = --up;
		while( !down->m_list.empty() )
		{
			down = --down->m_list.end();
		}

		m_it = down ;

		return *this;
	}


	template<typename container>
	Preorder_Iterator<container> Preorder_Iterator<container>::operator--(int)
	{
		Preorder_Iterator temp(*this);

		// TODO: check this, it's maybe worth it to spare a copy
		this->operator--();

		return temp;
	}

	template<typename container>
	bool Preorder_Iterator<container>::Eq(const Iterator& lhs, const Iterator& rhs) const
	{
#ifdef DEBUG
		// The underlying list container will throw an exception (in DEBUG only)
		// when two iterators from different lists are compared for equality.
		// It's not possible to check in advance, because 'm_it' can point
		// to the tree's end() iterator (e.g. m_root->m_list.end()) and
		// any attempt to dereference it will throw.
		// If it cannot be safely dereferenced, m_it->m_owner or m_it->m_list
		// cannot be checked. The only solution is to try/catch it.
		try
		{
			return lhs == rhs;
		}
		catch(stl::exception&)
		{
			return false;
		}
#else
		return lhs == rhs;
#endif
	}


	//////////////////////////////////////////////////////////////////////////
	//Preorder_Const_Iterator class
	template<typename container>
	Preorder_Const_Iterator<container>::Preorder_Const_Iterator()
		: Preorder_Iterator<container>()
	{
	}


	template<typename container>
	Preorder_Const_Iterator<container>::~Preorder_Const_Iterator()
	{
	}


	template<typename container>
	Preorder_Const_Iterator<container>::Preorder_Const_Iterator(const Iterator& it, const Tree& tr)
		: Preorder_Iterator<container>(it, tr)
	{
	}

	template<typename container>
	Preorder_Const_Iterator<container>::Preorder_Const_Iterator(const Preorder_Const_Iterator& it)
		: Preorder_Iterator<container>(it)
	{
	}


	template<typename container>
	Preorder_Const_Iterator<container>::Preorder_Const_Iterator(const Preorder_Iterator<container>& it)
		: Preorder_Iterator<container>(it)
	{
	}

	template<typename container>
	bool Preorder_Const_Iterator<container>::operator==(const Preorder_Const_Iterator& it) const
	{
		return Preorder_Iterator<container>::operator==(it);
	}

	template<typename container>
	bool Preorder_Const_Iterator<container>::operator!=(const Preorder_Const_Iterator& it) const
	{
		return Preorder_Iterator<container>::operator!=(it);
	}


	template<typename container>
	const typename Preorder_Const_Iterator<container>::value_type&
		Preorder_Const_Iterator<container>::operator*() const
	{
		return Preorder_Iterator<container>::operator*();
	}


	template<typename container>
	const typename Preorder_Const_Iterator<container>::value_type*
		Preorder_Const_Iterator<container>::operator->() const
	{
		return Preorder_Iterator<container>::operator->();
	}


	template<typename container>
	Preorder_Const_Iterator<container>& Preorder_Const_Iterator<container>::operator++()
	{
		Preorder_Iterator<container>::operator++();
		return *this;
	}


	template<typename container>
	Preorder_Const_Iterator<container> Preorder_Const_Iterator<container>::operator++(int)
	{
		return Preorder_Const_Iterator<container>(Preorder_Iterator<container>::operator++(1));
	}


	template<typename container>
	Preorder_Const_Iterator<container>& Preorder_Const_Iterator<container>::operator--()
	{
		Preorder_Iterator<container>::operator--();
		return *this;
	}


	template<typename container>
	Preorder_Const_Iterator<container> Preorder_Const_Iterator<container>::operator--(int)
	{
		return Preorder_Const_Iterator<container>(Preorder_Iterator<container>::operator--(1));
	}

	//////////////////////////////////////////////////////////////////////////
	//Postorder_Iterator class
	template<typename container>
	Postorder_Iterator<container>::Postorder_Iterator()
	{
		m_tree = 0;
	}

	template<typename container>
	Postorder_Iterator<container>::~Postorder_Iterator()
	{
	}

	template<typename container>
	Postorder_Iterator<container>::Postorder_Iterator(const Iterator& it, const Tree& tr)
	{
		m_it = it;
		m_tree = const_cast<Tree*>(&tr);
	}

	template<typename container>
	Postorder_Iterator<container>::Postorder_Iterator(const Postorder_Iterator& it)
	{
		m_it = it.m_it;
		m_tree = it.m_tree;
	}

	template<typename container>
	bool Postorder_Iterator<container>::operator==(const Postorder_Iterator& it) const
	{
		return Eq(m_it, it.m_it);
	}

	template<typename container>
	bool Postorder_Iterator<container>::operator!=(const Postorder_Iterator& it) const
	{
		return !(*this==it);
	}

	template<typename container>
	typename Postorder_Iterator<container>::value_type&
		Postorder_Iterator<container>::operator*() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return *(nod.m_T);
	}

	template<typename container>
	typename Postorder_Iterator<container>::value_type*
		Postorder_Iterator<container>::operator->() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return nod.m_T;
	}

	template<typename container>
	Postorder_Iterator<container>& Postorder_Iterator<container>::operator++()
	{
		//TODO: check going over root
		//TODO: check against m_root.m_list.end() ??
		//TODO: when does it reach the end of tree??

		//check sibling
		Iterator sibl = m_it;
		++sibl;
		if(sibl != m_it->m_owner->m_list.end())	// same list, no throw
		{
			//when sibling available go down-right in loop
			while( !sibl->m_list.empty() )
			{
				sibl = sibl->m_list.begin();
			}

			m_it = sibl;

			return *this;
		}

		//check parent
		if(m_it->m_owner->m_owner != 0)
		{
			m_it = m_it->m_owner->m_it;
			return *this;
		}

		throw stl::exception("iterator out of valid range");
	}

	template<typename container>
	Postorder_Iterator<container> Postorder_Iterator<container>::operator++(int)
	{
		Postorder_Iterator temp(*this);

		this->operator++();

		return temp;
	}

	template<typename container>
	Postorder_Iterator<container>& Postorder_Iterator<container>::operator--()
	{
		//check children
		if( !m_it->m_list.empty() )
		{
			m_it = --m_it->m_list.end();
			return *this;
		}

		//check sibling
		if(m_it != m_it->m_owner->m_list.begin())	// same list, no throw
		{
			--m_it;
			return *this;
		}

		//check parent's sibling
		Iterator up = m_it;
		while(up->m_owner != 0)
		{
			if(up->m_owner->m_owner == 0)
			{
				//TODO: where is the end of this?
				break;
			}

			up = up->m_owner->m_it;
			if(up != up->m_owner->m_list.begin())
			{
				m_it = --up;
				return *this;
			}

			m_it = up;
		}

		throw stl::exception("iterator out of valid range");
	}

	template<typename container>
	Postorder_Iterator<container> Postorder_Iterator<container>::operator--(int)
	{
		Postorder_Iterator temp(*this);

		this->operator--();

		return temp;
	}


	template<typename container>
	bool Postorder_Iterator<container>::Eq(const Iterator& lhs, const Iterator& rhs) const
	{
#ifdef DEBUG
		// The underlying list container will throw an exception (in DEBUG only)
		// when two iterators from different lists are compared for equality.
		// It's not possible to check in advance, because 'm_it' can point
		// to the tree's end() iterator (e.g. m_root->m_list.end()) and
		// any attempt to dereference it will throw.
		// If it cannot be safely dereferenced, m_it->m_owner or m_it->m_list
		// cannot be checked. The only solution is to try/catch it.
		try
		{
			return lhs == rhs;
		}
		catch(stl::exception&)
		{
			return false;
		}
#else
		return lhs == rhs;
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	//Postorder_Iterator class
	template<typename container>
	Postorder_Const_Iterator<container>::Postorder_Const_Iterator()
		: Postorder_Iterator<container>()
	{
	}

	template<typename container>
	Postorder_Const_Iterator<container>::~Postorder_Const_Iterator()
	{
	}

	template<typename container>
	Postorder_Const_Iterator<container>::Postorder_Const_Iterator(const Iterator& it, const Tree& tr)
		: Postorder_Iterator<container>(it, tr)
	{
	}

	template<typename container>
	Postorder_Const_Iterator<container>::Postorder_Const_Iterator(const Postorder_Const_Iterator& it)
		: Postorder_Iterator<container>(it)
	{
	}

	template<typename container>
	Postorder_Const_Iterator<container>::Postorder_Const_Iterator(const Postorder_Iterator<container>& it)
		: Postorder_Iterator<container>(it)
	{
	}

	template<typename container>
	bool Postorder_Const_Iterator<container>::operator==(const Postorder_Const_Iterator& it) const
	{
		return Postorder_Iterator<container>::operator ==(it);
	}

	template<typename container>
	bool Postorder_Const_Iterator<container>::operator!=(const Postorder_Const_Iterator& it) const
	{
		return Postorder_Iterator<container>::operator!=(it);
	}

	template<typename container>
	const typename Postorder_Const_Iterator<container>::value_type&
		Postorder_Const_Iterator<container>::operator*() const
	{
		return Postorder_Iterator<container>::operator*();
	}

	template<typename container>
	const typename Postorder_Const_Iterator<container>::value_type*
		Postorder_Const_Iterator<container>::operator->() const
	{
		return Postorder_Iterator<container>::operator->();
	}

	template<typename container>
	Postorder_Const_Iterator<container>& Postorder_Const_Iterator<container>::operator++()
	{
		Postorder_Iterator<container>::operator++();
		return *this;
	}

	template<typename container>
	Postorder_Const_Iterator<container> Postorder_Const_Iterator<container>::operator++(int)
	{
		return static_cast<Postorder_Const_Iterator<container>&>(Postorder_Iterator<container>::operator++(1));
	}

	template<typename container>
	Postorder_Const_Iterator<container>& Postorder_Const_Iterator<container>::operator--()
	{
		Postorder_Iterator<container>::operator--();
		return *this;
	}

	template<typename container>
	Postorder_Const_Iterator<container> Postorder_Const_Iterator<container>::operator--(int)
	{
		return static_cast<Postorder_Const_Iterator<container>&>(Postorder_Iterator<container>::operator--(1));
	}


	//////////////////////////////////////////////////////////////////////////
	//First_Branch_Iterator class
	template<typename container>
	First_Branch_Iterator<container>::First_Branch_Iterator()
	{
		m_tree = 0;
	}

	template<typename container>
	First_Branch_Iterator<container>::~First_Branch_Iterator()
	{
	}

	template<typename container>
	First_Branch_Iterator<container>::First_Branch_Iterator(const Iterator& it, const Tree& tr)
	{
		m_it=it;
		m_tree = const_cast<Tree*>(&tr);
	}

	template<typename container>
	First_Branch_Iterator<container>::First_Branch_Iterator(const First_Branch_Iterator& fit)
	{
		m_it = fit.m_it;
		m_tree = fit.m_tree;
	}

	template<typename container>
	bool First_Branch_Iterator<container>::operator==(const First_Branch_Iterator& it) const
	{
		return Eq(m_it, it.m_it);
	}

	template<typename container>
	bool First_Branch_Iterator<container>::operator!=(const First_Branch_Iterator& it) const
	{
		return !(*this==it);
	}

	template<typename container>
	typename First_Branch_Iterator<container>::value_type&
		First_Branch_Iterator<container>::operator*() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return *(nod.m_T);
	}


	template<typename container>
	typename First_Branch_Iterator<container>::value_type*
		First_Branch_Iterator<container>::operator->() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return nod.m_T;
	}


	template<typename container>
	First_Branch_Iterator<container>& First_Branch_Iterator<container>::operator++()
	{
		//has children
		if( !m_it->m_list.empty() )
		{
			m_it = m_it->m_list.begin();
			return *this;
		}

		throw stl::exception("iterator out of valid range");
	}

	template<typename container>
	First_Branch_Iterator<container> First_Branch_Iterator<container>::operator++(int)
	{
		First_Branch_Iterator temp(*this);

		this->operator++();

		return temp;
	}

	template<typename container>
	First_Branch_Iterator<container>& First_Branch_Iterator<container>::operator--()
	{
		//check branch begin
		if(m_it != m_it->m_owner->m_list.begin())
		{
			throw stl::exception("iterator out of valid range");
		}

		//check upper limit
		if(m_it->m_owner->m_owner == 0)
		{
			throw stl::exception("iterator out of valid range");
		}

		m_it = m_it->m_owner->m_it; // TODO: this doesn't look right

		return *this;
	}

	template<typename container>
	First_Branch_Iterator<container> First_Branch_Iterator<container>::operator--(int)
	{
		First_Branch_Iterator temp(*this);

		this->operator--();

		return temp;
	}

	template<typename container>
	bool First_Branch_Iterator<container>::Eq(const Iterator& lhs, const Iterator& rhs) const
	{
#ifdef DEBUG
		// The underlying list container will throw an exception (in DEBUG only)
		// when two iterators from different lists are compared for equality.
		// It's not possible to check in advance, because 'm_it' can point
		// to the tree's end() iterator (e.g. m_root->m_list.end()) and
		// any attempt to dereference it will throw.
		// If it cannot be safely dereferenced, m_it->m_owner or m_it->m_list
		// cannot be checked. The only solution is to try/catch it.
		try
		{
			return lhs == rhs;
		}
		catch(stl::exception&)
		{
			return false;
		}
#else
		return lhs == rhs;
#endif
	}


	//////////////////////////////////////////////////////////////////////////
	//First_Branch_Const_Iterator class
	template<typename container>
	First_Branch_Const_Iterator<container>::First_Branch_Const_Iterator()
		: First_Branch_Iterator<container>()
	{
	}

	template<typename container>
	First_Branch_Const_Iterator<container>::~First_Branch_Const_Iterator()
	{
	}

	template<typename container>
	First_Branch_Const_Iterator<container>::First_Branch_Const_Iterator(const Iterator& it, const Tree& tr)
		: First_Branch_Iterator<container>(it, tr)
	{
	}

	template<typename container>
	First_Branch_Const_Iterator<container>::First_Branch_Const_Iterator(const First_Branch_Const_Iterator& fit)
		: First_Branch_Iterator<container>(fit)
	{
	}

	template<typename container>
	bool First_Branch_Const_Iterator<container>::operator==(const First_Branch_Const_Iterator& it) const
	{
		return First_Branch_Iterator<container>::operator ==(it);
	}

	template<typename container>
	bool First_Branch_Const_Iterator<container>::operator!=(const First_Branch_Const_Iterator& it) const
	{
		return First_Branch_Iterator<container>::operator !=(it);
	}

	template<typename container>
	const typename First_Branch_Const_Iterator<container>::value_type&
		First_Branch_Const_Iterator<container>::operator*() const
	{
		return First_Branch_Iterator<container>::operator *();
	}


	template<typename container>
	const typename First_Branch_Const_Iterator<container>::value_type*
		First_Branch_Const_Iterator<container>::operator->() const
	{
		return First_Branch_Iterator<container>::operator->();
	}


	template<typename container>
	First_Branch_Const_Iterator<container>& First_Branch_Const_Iterator<container>::operator++()
	{
		First_Branch_Iterator<container>::operator ++();
		return *this;
	}

	template<typename container>
	First_Branch_Const_Iterator<container> First_Branch_Const_Iterator<container>::operator++(int)
	{
		return static_cast<First_Branch_Const_Iterator<container> >(First_Branch_Iterator<container>::operator ++(1));
	}

	template<typename container>
	First_Branch_Const_Iterator<container>& First_Branch_Const_Iterator<container>::operator--()
	{
		First_Branch_Iterator<container>::operator --();
		return *this;
	}

	template<typename container>
	First_Branch_Const_Iterator<container> First_Branch_Const_Iterator<container>::operator--(int)
	{
		return static_cast<First_Branch_Const_Iterator<container> >(First_Branch_Iterator<container>::operator--(1));
	}

	//////////////////////////////////////////////////////////////////////////
	//Child_Iterator class
	template<typename container>
	Child_Iterator<container>::Child_Iterator()
	{
		m_tree = 0;
	}

	template<typename container>
	Child_Iterator<container>::~Child_Iterator()
	{
	}

	template<typename container>
	Child_Iterator<container>::Child_Iterator(const Iterator& it, const Tree& tr)
	{
		m_it=it;
		m_tree = const_cast<Tree*>(&tr);
	}

	template<typename container>
	Child_Iterator<container>::Child_Iterator(const Child_Iterator& fit)
	{
		m_it = fit.m_it;
		m_tree = fit.m_tree;
	}

	template<typename container>
	bool Child_Iterator<container>::operator==(const Child_Iterator& it) const
	{
		return Eq(m_it, it.m_it);
	}

	template<typename container>
	bool Child_Iterator<container>::operator!=(const Child_Iterator& it) const
	{
		return !(*this==it);
	}

	template<typename container>
	typename Child_Iterator<container>::value_type& Child_Iterator<container>::operator*() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return nod.m_T;
	}


	template<typename container>
	typename Child_Iterator<container>::value_type* Child_Iterator<container>::operator->() const
	{
		misc::tree_node<value_type>& nod = *m_it;
		return nod.m_T;
	}


	template<typename container>
	Child_Iterator<container>& Child_Iterator<container>::operator++()
	{
		++m_it;
		return *this;
	}

	template<typename container>
	Child_Iterator<container> Child_Iterator<container>::operator++(int)
	{
		Child_Iterator temp(*this);
		++m_it;
		return temp;
	}

	template<typename container>
	Child_Iterator<container>& Child_Iterator<container>::operator--()
	{
		--m_it;
		return *this;
	}

	template<typename container>
	Child_Iterator<container> Child_Iterator<container>::operator--(int)
	{
		Child_Iterator temp(*this);
		--m_it;
		return temp;
	}

	template<typename container>
	bool Child_Iterator<container>::Eq(const Iterator& lhs, const Iterator& rhs) const
	{
#ifdef DEBUG
		// The underlying list container will throw an exception (in DEBUG only)
		// when two iterators from different lists are compared for equality.
		// It's not possible to check in advance, because 'm_it' can point
		// to the tree's end() iterator (e.g. m_root->m_list.end()) and
		// any attempt to dereference it will throw.
		// If it cannot be safely dereferenced, m_it->m_owner or m_it->m_list
		// cannot be checked. The only solution is to try/catch it.
		try
		{
			return lhs == rhs;
		}
		catch(stl::exception&)
		{
			return false;
		}
#else
		return lhs == rhs;
#endif
	}


	//////////////////////////////////////////////////////////////////////////
	//Child_Const_Iterator class
	template<typename container>
	Child_Const_Iterator<container>::Child_Const_Iterator()
		: Child_Iterator<container>()
	{
	}

	template<typename container>
	Child_Const_Iterator<container>::~Child_Const_Iterator()
	{
	}

	template<typename container>
	Child_Const_Iterator<container>::Child_Const_Iterator(const Iterator& it, const Tree& tr)
		: Child_Iterator<container>(it, tr)
	{
	}

	template<typename container>
	Child_Const_Iterator<container>::Child_Const_Iterator(const Child_Const_Iterator& fit)
		: Child_Iterator<container>(fit)
	{
	}

	template<typename container>
	bool Child_Const_Iterator<container>::operator==(const Child_Const_Iterator& it) const
	{
		return Child_Iterator<container>::operator ==(it);
	}

	template<typename container>
	bool Child_Const_Iterator<container>::operator!=(const Child_Const_Iterator& it) const
	{
		return Child_Iterator<container>::operator !=(it);
	}

	template<typename container>
	const typename Child_Const_Iterator<container>::value_type&
		Child_Const_Iterator<container>::operator*() const
	{
		return Child_Iterator<container>::operator *();
	}


	template<typename container>
	const typename Child_Const_Iterator<container>::value_type*
		Child_Const_Iterator<container>::operator->() const
	{
		return Child_Iterator<container>::operator->();
	}


	template<typename container>
	Child_Const_Iterator<container>& Child_Const_Iterator<container>::operator++()
	{
		Child_Iterator<container>::operator++();
	}

	template<typename container>
	Child_Const_Iterator<container> Child_Const_Iterator<container>::operator++(int)
	{
		return static_cast<Child_Const_Iterator<container> >(Child_Iterator<container>::operator ++(1));
	}

	template<typename container>
	Child_Const_Iterator<container>& Child_Const_Iterator<container>::operator--()
	{
		Child_Iterator<container>::operator--();
		return *this;
	}

	template<typename container>
	Child_Const_Iterator<container> Child_Const_Iterator<container>::operator--(int)
	{
		return static_cast<Child_Const_Iterator<container> >(Child_Iterator<container>::operator--(1));
	}



	//////////////////////////////////////////////////////////////////////////
	//tree class
	template<typename T, typename Allocator>
	tree<T, Allocator>::tree()
	{
		m_size=0;
	}


	template<typename T, typename Allocator>
	tree<T, Allocator>::~tree()
	{
	}


	template<typename T, typename Allocator>
	tree<T, Allocator>::tree(const tree& t)
	{
		m_size = 0;
		*this=t;
	}


	template<typename T, typename Allocator>
	void tree<T, Allocator>::deep_copy_node(tree_node<T>& dest, const tree_node<T>& src)
	{
		//List							m_list;
		//typename List::iterator		m_it;
		//tree_node*					m_owner;
		//value_type*					m_T;

		dest.m_T = new T(*src.m_T);
		for (typename tree_node<T>::const_iterator it = src.m_list.begin();
			it != src.m_list.end(); ++it)
		{
			dest.m_list.push_back(tree_node<T>());
			m_size++;

			const tree_node<T>& nr = *it;
			tree_node<T>& nl = dest.m_list.back();
			nl.m_it = --(dest.m_list.end());
			nl.m_owner = &nl;

			deep_copy_node(nl, nr);
		}
	}

	template<typename T, typename Allocator>
	void tree<T, Allocator>::deep_copy_tree(const tree& tc)
	{
		if (tc.m_size == 0)
			return;

		//List							m_list;
		//typename List::iterator		m_it;
		//tree_node*					m_owner;
		//value_type*					m_T;

		for (typename tree_node<T>::const_iterator it = tc.m_root.m_list.begin();
			it != tc.m_root.m_list.end(); ++it)
		{
			m_root.m_list.push_back(tree_node<T>());
			m_size++;

			const tree_node<T>& nr = *it;
			tree_node<T>& nl = m_root.m_list.back();
			nl.m_it = --(m_root.m_list.end());
			nl.m_owner = &nl;

			deep_copy_node(nl, nr);
		}
	}

	template<typename T, typename Allocator>
	tree<T, Allocator>&
		tree<T, Allocator>::operator=(const tree& t)
	{
		if(this==&t)
			return *this;

		deep_copy_tree(t);

		return *this;
#if 0

		//copy tree structure (nodes list, iterators, owners, values)
		//post copy update required for iterators and owners
		m_root.m_owner = 0;
		m_root.m_list = t.m_root.m_list;
		m_size = t.m_size;

		//update top level nodes's owner;
		//all beneath nodes are updated in while loop below.
		for(iterator it = m_root.m_list.begin(); it != m_root.m_list.end(); ++it)
		{
			it->m_owner = &m_root;
			it->m_it = it;
		}

		preorder_iterator beg = preorder_begin();
		preorder_iterator end = preorder_end();

		while(beg != end)
		{
			iterator cbeg = beg.m_it->m_list.begin();
			iterator cend = beg.m_it->m_list.end();

			//update owner and self iterator
			while(cbeg != cend)
			{
				tree_node<T>& nod = *cbeg;
				nod.m_it = cbeg;
				nod.m_owner = &*(beg.m_it);
				++cbeg;
			}

			++beg;
		}//while

		return *this;
#endif
	}


	template<typename T, typename Allocator>
	bool tree<T, Allocator>::operator==(const tree& t) const
	{
		if(this != &t)
		{
			if(m_size != t.m_size) 
				return false;			

			preorder_const_iterator cb = preorder_begin();
			preorder_const_iterator ce = preorder_end();

			preorder_const_iterator cb0 = t.preorder_begin();
			preorder_const_iterator ce0 = t.preorder_end();

			for(; cb != ce && cb0 != ce0; ++cb, ++cb0)
			{
				const value_type& val = *cb;
				const value_type& val2= *cb0;
				if(!(val == val2))
					return false;					
			}

			return (cb == ce && cb0 == ce0);
		}
		return true;
	}


	template<typename T, typename Allocator>
	bool tree<T, Allocator>::operator!=(const tree& t) const
	{
		return !(*this==t);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(preorder_iterator it) const
	{
		return it.m_it;
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(preorder_const_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(postorder_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(postorder_const_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(first_branch_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(first_branch_const_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(child_iterator it) const
	{
		return it.m_it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::get_iterator(child_const_iterator it) const
	{
		return it.m_it;
	}



	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::push_back(const value_type& val)
	{
		tree_node<T> nod(&m_root, val);
		iterator it = m_root.m_list.insert(m_root.m_list.end(), nod);
		it->m_it = it;
		++m_size;
		return it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::push_front(const value_type& val)
	{
		tree_node<T> nod(&m_root, val);
		iterator it = m_root.m_list.insert(m_root.m_list.begin(), nod);
		it->m_it = it;
		++m_size;
		return it;
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::insert_sibling_before(iterator i, const value_type& val)
	{
		tree_node<T>* owner = i->m_owner ;
		tree_node<T> nod(owner, val);
		iterator it = owner->m_list.insert(i, nod);
		nod.m_it = it;
		++m_size;
		return it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::insert_sibling_after(iterator i, const value_type& val)
	{
		tree_node<T>* owner = i->m_owner ;
		tree_node<T> nod(owner, val);
		i++;
		iterator it = owner->m_list.insert(i, nod);
		nod.m_it = it;
		++m_size;
		return it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::push_back_child(iterator i, const value_type& val)
	{
		tree_node<T>& owner = *i;
		tree_node<T> nod(&owner, val);
		iterator it = i->m_list.insert(i->m_list.end(), nod);
		it->m_it = it;
		++m_size;
		return it;
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::push_front_child(iterator i, const value_type& val)
	{
		tree_node<T>& owner = *i;
		tree_node<T> nod(&owner, val);
		iterator it = i->m_list.insert(i->m_list.begin(), nod);
		it->m_it = it;
		++m_size;
		return it;
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::preorder_iterator 
		tree<T, Allocator>::preorder_begin()
	{
		return preorder_iterator(m_root.m_list.begin(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::preorder_iterator 
		tree<T, Allocator>::preorder_end()
	{
		return preorder_iterator(m_root.m_list.end(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::preorder_const_iterator 
		tree<T, Allocator>::preorder_begin() const
	{
		List& nlist = const_cast<List&>(m_root.m_list);
		return preorder_const_iterator(nlist.begin(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::preorder_const_iterator 
		tree<T, Allocator>::preorder_end() const
	{
		List& nlist = const_cast<List&>(m_root.m_list);
		return preorder_const_iterator(nlist.end(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::postorder_iterator 
		tree<T, Allocator>::postorder_begin()
	{
		iterator m_it = m_root.m_list.begin();

		while(!m_it->m_list.empty())
		{
			m_it = m_it->m_list.begin();
		}

		return postorder_iterator(m_it, *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::postorder_iterator 
		tree<T, Allocator>::postorder_end()
	{
		return postorder_iterator(m_root.m_list.end(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_iterator 
		tree<T, Allocator>::first_branch_begin()
	{
		return first_branch_iterator(m_root.m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_iterator 
		tree<T, Allocator>::first_branch_end()
	{
		//TODO: would this make sense? e.g. to point the last end tree's end()?
		return first_branch_iterator(m_root.m_list.end(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_iterator 
		tree<T, Allocator>::first_branch_begin(iterator it)
	{
		return first_branch_iterator(it, *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_iterator 
		tree<T, Allocator>::first_branch_end(iterator it)
	{
		//return first_branch_iterator(it, *this);

		//TODO: where should the end position be ??
		throw stl::exception("operation is invalid");
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_const_iterator 
		tree<T, Allocator>::first_branch_begin() const
	{
		return first_branch_const_iterator(m_root.m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_const_iterator 
		tree<T, Allocator>::first_branch_end() const
	{
		//TODO: to be tested, but makes sense to put fbi end to tree's end, or??
		return first_branch_const_iterator(m_root.m_list.end(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_const_iterator 
		tree<T, Allocator>::first_branch_begin(iterator it) const
	{
		return first_branch_const_iterator(it, *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::first_branch_const_iterator 
		tree<T, Allocator>::first_branch_end(iterator it) const
	{
		// first_branch_const_iterator fbend(it);

		//TODO: where should this be??
		throw stl::exception("operation is invalid");
	}



	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::child_begin()
	{
		return child_iterator(m_root.m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::child_end()
	{
		return child_iterator(m_root.m_list.end(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::child_begin(iterator it)
	{
		return child_iterator(it->m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::child_end(iterator it)
	{
		return child_iterator(it->m_list.end(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::child_begin() const
	{
		return child_const_iterator(m_root.m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::child_end() const
	{
		return child_const_iterator(m_root.m_list.end(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::child_begin(iterator it) const
	{
		return child_const_iterator(it->m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::child_end(iterator it) const
	{
		return child_const_iterator(it->m_list.end(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::siblings_begin(iterator it)
	{
		return child_iterator(it->m_owner->m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_iterator 
		tree<T, Allocator>::siblings_end(iterator it)
	{
		return child_iterator(it->m_owner->m_list.end(), *this);
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::siblings_begin(iterator it) const
	{
		return child_const_iterator(it->m_owner->m_list.begin(), *this);
	}

	template<typename T, typename Allocator>
	typename tree<T, Allocator>::child_const_iterator 
		tree<T, Allocator>::siblings_end(iterator it) const
	{
		return child_const_iterator(it->m_owner->m_list.end(), *this);
	}

	//////////////////////////////////////////////////////////////////////////
	// tree implementation

	template<typename T, typename Allocator>
	bool tree<T, Allocator>::empty() const
	{
		return m_root.m_list.empty();
	}

	template<typename T, typename Allocator>
	size_t tree<T, Allocator>::size() const
	{
		return m_size;
	}

	template<typename T, typename Allocator>
	void tree<T, Allocator>::clear()
	{
		m_root.m_list.clear();
		m_size=0;
	}


	template<typename T, typename Allocator>
	typename tree<T, Allocator>::iterator 
		tree<T, Allocator>::erase(iterator it)
	{
		return it->m_owner->m_list.erase(it);
	}

	//tree end
	//////////////////////////////////////////////////////////////////////////

}  // namespace

#endif//__tree_hpp__

