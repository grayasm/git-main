/*
  Copyright (C) 2012 Mihai Vasilian

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

#ifndef __memory_hpp__
#define __memory_hpp__


#include "iterator.hpp"
#include "utility.hpp"



namespace stl
{

	//An adapter class that is provided to enable algorithms to store their results into uninitialized memory.
	//raw_storage_iterator
	template <typename OutputIterator, typename T>
	class raw_storage_iterator :
		public iterator<stl::output_iterator_tag,void,void,void,void>
	{
	protected:
		OutputIterator iter;

	public:
		explicit raw_storage_iterator (OutputIterator x)
			: iter(x)
		{
		};

		raw_storage_iterator<OutputIterator,T>& operator* ()
		{
			return *this;
		};

		raw_storage_iterator<OutputIterator,T>& operator= (const T& element)
		{
			new (static_cast<void*>(&*iter)) T (element);
			return *this;
		};

		raw_storage_iterator<OutputIterator,T>& operator++ ()
		{
			++iter;
			return *this;
		};

		raw_storage_iterator<OutputIterator,T> operator++ (int)
		{
			raw_storage_iterator<OutputIterator,T> tmp = *this;
			++iter;
			return tmp;
		};
	};


	//////////////////////////////////////////////////////////////////////////
	/*
	  Requests a memory block to contain up to n elements of type T temporarily.
	  The memory block is aligned appropriately to contain elements of type T, although it is left uninitialized (no object is constructed).
	  This function is specifically designed to obtain memory of temporary nature (such as for the operations of an algorithm).
	  Once the memory block is not needed anymore, it shall be released by calling return_temporary_buffer.
	*/

	template <typename T>
	stl::pair <T*,ptrdiff_t> get_temporary_buffer ( ptrdiff_t n )
	{
		// get raw temporary buffer of up to n elements
		T  *ptrbuff;

		if (n <= 0)
		{
			n = 0;
		}
		else if (((size_t)(-1) / n) < sizeof (T))
		{
			throw stl::exception("bad allocation");
		}

		for (ptrbuff = 0; 0 < n; n /= 2)
		{
			ptrbuff = (T*)operator new((size_t)n * sizeof (T)/*, nothrow*/);
			if ( ptrbuff != 0)
			{
				break;
			}
		}

		return (stl::pair<T*, ptrdiff_t>(ptrbuff, n));
	}
	//////////////////////////////////////////////////////////////////////////
	/*
	  Releases the memory block pointed by p.
	  p shall be a pointer value returned by a previous call to get_temporary_buffer.
	*/
	template <typename T>
	void return_temporary_buffer (T* p)
	{
		// delete raw temporary buffer
		operator delete(p);
	}



	//////////////////////////////////////////////////////////////////////////
	/*
	  Copy block of memory
	  Constructs copies of the elements in the range [first,last) into a range beginning at result and returns an iterator to the last element in the destination range.
	  Unlike algorithm copy, uninitialized_copy constructs the objects at destination, instead of just copying them.
	  This allows to obtain fully constructed copies of the elements into a range of uninitialized memory,
	  such as a memory block obtained by a call to get_temporary_buffer or malloc.
	*/
	template<typename InputIterator, typename ForwardIterator>
	ForwardIterator uninitialized_copy ( InputIterator first, InputIterator last, ForwardIterator result )
	{
		for (; first!=last; ++result, ++first)
		{
			new (static_cast<void*>(&*result)) typename stl::iterator_traits<ForwardIterator>::value_type(*first);
		}//for
		return result;
	}

	//////////////////////////////////////////////////////////////////////////
	/*
	  Constructs all the elements in the range [first,last) initializing them to a value of x.
	  Unlike algorithm fill, uninitialized_fill constructs the objects at destination, instead of just copying the value to them.
	  This allows to obtain fully constructed copies into a range of uninitialized memory,
	  such as a memory block obtained by a call to get_temporary_buffer or malloc.
	*/
	template < typename ForwardIterator, typename T >
	void uninitialized_fill ( ForwardIterator first, ForwardIterator last, const T& x )
	{
		for (; first!=last; ++first)
		{
			new (static_cast<void*>(&*first)) typename stl::iterator_traits<ForwardIterator>::value_type(x);
		}//for
	}

	//////////////////////////////////////////////////////////////////////////
	/*
	  Constructs n elements in the array pointed by first, initializing them to a value of x.
	  Unlike algorithm fill_n, uninitialized_fill_n constructs the objects at destination, instead of just copying the value to them.
	  This allows to obtain fully constructed copies into a range of uninitialized memory, such as a memory block obtained by a call to get_temporary_buffer or malloc.
	*/
	template < typename ForwardIterator, typename Size, typename T >
	void uninitialized_fill_n ( ForwardIterator first, Size n, const T& x )
	{
		for (; n--; ++first)
		{
			new (static_cast<void*>(&*first)) typename stl::iterator_traits<ForwardIterator>::value_type(x);
		}//for
	}

	//////////////////////////////////////////////////////////////////////////

	/* ISO/IEC 14882:2003(E)   $20.4.1, the default allocator: */
	template<typename T> class allocator;
	// specialize for void:
	template<> class allocator<void>
	{
	public:
		typedef void* pointer;
		typedef const void* const_pointer;
		// reference-to-void members are impossible.
		typedef void value_type;
		template<typename U> struct rebind { typedef allocator<U> other; };
	};


	// $20.4.1, the default allocator
	template<typename T>
	class allocator
	{
	public:
		typedef size_t          size_type;
		typedef ptrdiff_t       difference_type;
		typedef T*              pointer;
		typedef const T*        const_pointer;
		typedef T&              reference;
		typedef const T&        const_reference;
		typedef T               value_type;

		template<typename U>
		struct rebind { typedef allocator<U> other; };

	public:
		allocator() throw()
		{
		}
		allocator(const allocator& /*alloc*/) throw()
		{
		}
		template <class U>
		allocator(const allocator<U>& /*alloc*/) throw()
		{
		}
		~allocator() throw()
		{
		}
		inline pointer address(reference x) const
		{
			return &x;
		}
		const_pointer address(const_reference x) const
		{
			return &x;
		}
		inline pointer allocate(size_type n, allocator<void>::const_pointer  hint = 0)
		{
			(void)hint;
			if (n <= 0)
				n = 0;
			else if (((size_type)(-1) / n) < sizeof (value_type))
				throw stl::exception("bad allocation");

			/*	Buy memory, no ctor is called.
			 *
			 *	The advantage of ::realloc used in memmanip.hpp is of resizing
			 *	in place, without copying. It requires however a pointer allocated
			 *	with malloc,calloc,realloc.
			 *	This forbids the use of operator new and delete as below:
			 *	   return (pointer) ::operator new(n * sizeof(value_type));
			 *	   ::operator delete(p);
			*/
			return (pointer) ::calloc(n, sizeof(value_type));
		}
		inline void deallocate(pointer p, size_type)
		{
			::free(p);
		}
		inline size_type max_size() const throw()
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}
		inline void construct(pointer p, const_reference val)
		{
			/* construct with copy.ctor() */
			::new(p)value_type(val);
		}
		inline void destroy(pointer p)
		{
			p->T::~T();
		}

		/* $20.1.5, allocator requirements */
		/*
		  4. All instances of a given allocator type are required to be interchangeable
		  and always compare equal to each other.
		*/
		template<typename U>
		bool operator==(const stl::allocator<U>&) const throw()
		{
			/* returns true if storage allocated from each can be deallocated via the other */
			return true;
		}

		template<typename U>
		bool operator!=(const stl::allocator<U>&) const throw()
		{
			// see above
			return false;
		}
	}; // class
	//////////////////////////////////////////////////////////////////////////
} // namespace



#endif//__memory_hpp__
