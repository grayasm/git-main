/*
Copyright (C) 2012 Mihai Vasilian
*/

#ifndef __memory_hpp__
#define __memory_hpp__


#include "iterator.hpp"
#include "utility.hpp"
#include <stdlib.h>
#include <new>


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
        }

        raw_storage_iterator<OutputIterator,T>& operator* ()
        {
            return *this;
        }

        raw_storage_iterator<OutputIterator,T>& operator= (const T& element)
        {
            new (static_cast<void*>(&*iter)) T (element);
            return *this;
        }

        raw_storage_iterator<OutputIterator,T>& operator++ ()
        {
            ++iter;
            return *this;
        }

        raw_storage_iterator<OutputIterator,T> operator++ (int)
        {
            raw_storage_iterator<OutputIterator,T> tmp = *this;
            ++iter;
            return tmp;
        }
    };


    //////////////////////////////////////////////////////////////////////////
    /*
      Requests a memory block to contain up to n elements of type T temporarily.
      The memory block is aligned appropriately to contain elements of type T, although it is left uninitialized (no object is constructed).
      This function is specifically designed to obtain memory of temporary nature (such as for the operations of an algorithm).
      Once the memory block is not needed anymore, it shall be released by calling return_temporary_buffer.
    */

    template <typename T>
    //stl::pair <T*,ptrdiff_t> get_temporary_buffer ( ptrdiff_t n )
    stl::pair <T*, long> get_temporary_buffer (long n)
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

        // return (stl::pair<T*, ptrdiff_t>(ptrbuff, n));
        return (stl::pair<T*, long>(ptrbuff, n));
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
        //typedef ptrdiff_t       difference_type;
        typedef long            difference_type;
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

        pointer address(reference x) const
        {
            return &x;
        }

        const_pointer address(const_reference x) const
        {
            return &x;
        }

        pointer allocate(size_type n, allocator<void>::const_pointer  hint = 0)
        {
            /*  hint:
            Either 0 or a value previously obtained by another call to allocate
            and not yet freed with deallocate. When it is not 0, this value may
            be used as a hint to improve performance by allocating the new block
            near the one specified. The address of an adjacent element is often
            a good choice.
            */

            if (n > 0)
            {
                if (hint)
                {
                /*  https://en.cppreference.com/w/c/memory/realloc
                    The reallocation is done by either:
                a)  expanding or contracting the existing area pointed to by ptr,
                    if possible. The contents of the area remain unchanged up to
                    the lesser of the new and old sizes. If the area is expanded,
                    the contents of the new part of the array are undefined.
                b)  allocating a new memory block of size new_size bytes,
                    copying memory area with size equal the lesser of the
                    new and the old sizes, and freeing the old block.
                */
                    return (pointer)::realloc((void*)hint, n * sizeof(value_type));
                }
                else
                {
                    /* Initializes all bits to zero.*/
                    return (pointer) ::calloc(n, sizeof(value_type));
                }
            }

            return 0;
        }

        void deallocate(pointer p, size_type)
        {
            ::free(p);
        }

        size_type max_size() const throw()
        {
            return static_cast<size_type>(-1) / sizeof(value_type);
        }

        void construct(pointer p, const_reference val)
        {
            /* construct with copy.ctor() */
            ::new(p)value_type(val);
        }

        void destroy(pointer p)
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
