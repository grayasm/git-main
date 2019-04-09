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

#ifndef __memmanip_hpp__
#define __memmanip_hpp__


#include <cwchar>
#include <cstring>
#include "exception.hpp"


namespace stl
{


    //////////////////////////////////////////////////////////////////////////
    /*
      mem_alloc - buy memory, no ctor called
      There is no need to specialize for <char>, <unsigned char> or similar.
      Better: use the underling code directly where you need it.

      template<typename T, typename Allocator>
      void mem_alloc(T** dest, size_t cap, Allocator& allocator)
      {
            *dest = allocator.allocate(cap, 0);
            if(*dest == 0) throw stl::exception("bad allocation");
      }
    */
    
    //////////////////////////////////////////////////////////////////////////
    /*
      mem_free - free memory, no dtor is called
      There is no need to specialize for <char>, <unsigned char> or similar.
      Same: use the underling code directly where you need it.

      template<typename T, typename Allocator>
      void mem_free(T** dest, Allocator& allocator)
      {
            allocator.deallocate(*dest, 0);
      }
    */
    
    //////////////////////////////////////////////////////////////////////////
    /*
      mem_destroy - call each element destructor, does not free memory

      Specialize for the basic types to avoid the for loop in <T,Allocator>.
    */
    template<typename T, typename Allocator>
    void mem_destroy(T** dest, size_t count, Allocator& allocator)
    {
	    for(size_t i = 0; i < count; ++i)
	    {
            // p->T::~T();
		    allocator.destroy((*dest)+i);
	    }
    }

    template<typename Allocator>
    void mem_destroy(char**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(signed char**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(unsigned char**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(wchar_t**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(short**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(unsigned short**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(int**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(unsigned int**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(long**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(unsigned long**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(double**, size_t, Allocator&)
    {
    }


    template<typename Allocator>
    void mem_destroy(float**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(long long**, size_t, Allocator&)
    {
    }

    template<typename Allocator>
    void mem_destroy(unsigned long long**, size_t, Allocator&)
    {
    }


    //////////////////////////////////////////////////////////////////////////
    /*  mem_copy 
        -   dst_valid_sz is the size already initialized at dst address.
            everything equal or beyond this count is memory not initialized.
    */
    template<typename T, typename Allocator>
    inline void mem_copy(T* dst, size_t dst_valid_sz, const T* src, size_t count, Allocator& allocator)
    {
        for(size_t i=0; i < count; ++i)
        {
            T* d1 = dst + i;
            const T* s1 = src + i;
            if(d1 != s1)
            {
                if (i < dst_valid_sz)
                {
                    allocator.destroy(d1);//faults when object at d1 was not yet created;
                }

                allocator.construct(d1, *s1);
            }
        }
    }

    template<typename Allocator>
    inline void mem_copy(char* dst, size_t, const char* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(char));
    }

    template<typename Allocator>
    inline void mem_copy(signed char* dst, size_t, const signed char* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(signed char));
    }

    template<typename Allocator>
    inline void mem_copy(unsigned char* dst, size_t, const unsigned char* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(unsigned char));
    }

    template<typename Allocator>
    inline void mem_copy(wchar_t* dst, size_t, const wchar_t* src, size_t count, Allocator&)
    {
        /*
          wchar_t *wmemcpy(wchar_t *dest,const wchar_t *src,size_t count);
          wmemcpy copies 'count' wide characters of 2 or 4 bytes.
        */
        ::wmemcpy(dst, src, count);
    }

    template<typename Allocator>
    inline void mem_copy(short* dst, size_t, const short* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(short));
    }

    template<typename Allocator>
    inline void mem_copy(unsigned short* dst, size_t, const unsigned short* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(unsigned short));
    }

    template<typename Allocator>
    inline void mem_copy(int* dst, size_t, const int* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(int));
    }

    template<typename Allocator>
    inline void mem_copy(unsigned int* dst, size_t, const unsigned int* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(unsigned int));
    }

    template<typename Allocator>
    inline void mem_copy(long* dst, size_t, const long* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(long));
    }

    template<typename Allocator>
    inline void mem_copy(unsigned long* dst, size_t, const unsigned long* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(unsigned long));
    }

    template<typename Allocator>
    inline void mem_copy(double* dst, size_t, const double* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(double));
    }

    template<typename Allocator>
    inline void mem_copy(float* dst, size_t, const float* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(float));
    }

    template<typename Allocator>
    inline void mem_copy(long long* dst, size_t, const long long* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(long long));
    }

    template<typename Allocator>
    inline void mem_copy(unsigned long long* dst, size_t, const unsigned long long* src, size_t count, Allocator&)
    {
        ::memcpy(dst, src, count * sizeof(unsigned long long));
    }

    //////////////////////////////////////////////////////////////////////////
    /* mem_move - source: http://www.cplusplus.com/reference/cstring/memmove/
    
    void * memmove ( void * destination, const void * source, size_t num );
    
    Copies the values of num bytes from the location pointed by source to
    the memory block pointed by destination. Copying takes place as if an
    intermediate buffer were used, allowing the destination and source to
    overlap.

    The underlying type of the objects pointed by both the source and
    destination pointers are irrelevant for this function; The result
    is a binary copy of the data.

    The function does not check for any terminating null character in source
    - it always copies exactly num bytes.

    To avoid overflows, the size of the arrays pointed by both the destination
    and source parameters, shall be at least num bytes.

    My obs: The source pointer is not released (tested). It would also be
            impossible to tell if the pointer was created by new/malloc or
            if it is an offset from another pointer.
            memmove does not touch the source memory (no ~T() call, no free())
    */

    template<typename T, typename Allocator>
    inline void mem_move(T* dst, size_t dst_valid_sz, const T* src, size_t count, Allocator& allocator)
    {
        if(src + count < dst || dst + count < src)
        {
            //non-overlapping region
            for(size_t i=0; i < count; ++i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;

                // clean the destination, otherwise the pointer is leaked
                if (i < dst_valid_sz)
                {
                    allocator.destroy(d1); //faults when object at d1 was not yet created;
                }

                allocator.construct(d1, *s1);
            }
        }
        else if(src > dst)
        {
            //overlapping at right [x]dst ...[x]src
            for(size_t i=0; i < count; ++i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;

                // clean the destination, otherwise the pointer is leaked
                if (i < dst_valid_sz)
                {
                    allocator.destroy(d1); //faults when object at d1 was not yet created;
                }

                allocator.construct(d1, *s1);
            }
        }
        else if(dst > src)
        {
            //overlapping at left [x]src ...[x]dst
            for(size_t i=count-1; i != (size_t)-1; --i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;

                // clean the destination, otherwise the pointer is leaked
                if (i < dst_valid_sz)
                {
                    allocator.destroy(d1); //faults when object at d1 was not yet created;
                }

                allocator.construct(d1, *s1);
            }
        }
    }

    template<typename Allocator>
    inline void mem_move(char* dst, size_t, const char* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(char));
    }

    template<typename Allocator>
    inline void mem_move(signed char* dst, size_t, const signed char* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(signed char));
    }

    template<typename Allocator>
    inline void mem_move(unsigned char* dst, size_t, const unsigned char* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(unsigned char));
    }

    template<typename Allocator>
    inline void mem_move(wchar_t* dst, size_t, const wchar_t* src, size_t count, Allocator&)
    {
        /*
          wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t count);
          wmemcpy copies 'count' wide characters of 2 or 4 bytes.
        */
        ::wmemmove(dst, src, count);
    }

    template<typename Allocator>
    inline void mem_move(short* dst, size_t, const short* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(short));
    }

    template<typename Allocator>
    inline void mem_move(unsigned short* dst, size_t, const unsigned short* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(unsigned short));
    }

    template<typename Allocator>
    inline void mem_move(int* dst, size_t, const int* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(int));
    }

    template<typename Allocator>
    inline void mem_move(unsigned int* dst, size_t, const unsigned int* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(unsigned int));
    }

    template<typename Allocator>
    inline void mem_move(long* dst, size_t, const long* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(long));
    }

    template<typename Allocator>
    inline void mem_move(unsigned long* dst, size_t, const unsigned long* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(unsigned long));
    }

    template<typename Allocator>
    inline void mem_move(double* dst, size_t, const double* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(double));
    }

    template<typename Allocator>
    inline void mem_move(float* dst, size_t, const float* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(float));
    }

    template<typename Allocator>
    inline void mem_move(long long* dst, size_t, const long long* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(long long));
    }

    template<typename Allocator>
    inline void mem_move(unsigned long long* dst, size_t, const unsigned long long* src, size_t count, Allocator&)
    {
        ::memmove(dst, src, count * sizeof(unsigned long long));
    }

    //////////////////////////////////////////////////////////////////////////
    /*  memset: void * memset ( void * ptr, int value, size_t num );
        
        Sets the first num bytes of the block of memory pointed by ptr
        to the specified value (interpreted as an unsigned char).

        !!Do not specialize for anything other than <char>, <unsigned char>
        and <wchar_t> as the ::memset's value is casted to unsigned char.
        You cannot memset bigger data type than that.
     */
    template<typename T, typename Allocator>
    inline void mem_set(T* dst, const T& val, size_t bytes, Allocator& allocator)
    {
        size_t elems = bytes / sizeof(T);
        for (size_t i = 0; i < elems; ++i)
        {
            allocator.construct(&dst[i], val);
        }
    }

    template<typename Allocator>
    inline void mem_set(char* dst, char val, size_t bytes, Allocator&)
    {
        ::memset(dst, val, bytes);
    }

    template<typename Allocator>
    inline void mem_set(unsigned char* dst, unsigned char val, size_t bytes, Allocator&)
    {
        ::memset(dst, val, bytes);
    }

    template<typename Allocator>
    inline void mem_set(wchar_t* dst, wchar_t val, size_t bytes, Allocator&)
    {
        /*
          wchar_t *wmemset(wchar_t *dest, wchar_t c, size_t count);
          Sets the first count wide characters (2 or 4 bytes) of dest to the character c.
        */
        if(bytes % sizeof(wchar_t)) throw stl::exception("invalid bytes value");
        ::wmemset(dst, val, bytes / sizeof(wchar_t));
    }

    //////////////////////////////////////////////////////////////////////////
    /*
      mem_realloc - buy more memory, and relocate to new address

      The realloc() function changes the size of the memory block pointed by
      ptr to size bytes. The contents will be unchanged in the range from
      the start of the region up to the minimum of the old and new sizes. If
      the new size is larger then the old size, the added memory will not be
      initialized. If ptr is NULL, then the call is equivalent to malloc(size),
      for all values of size; if size is equal to zero, and ptr is not NULL,
      then the call is equivalent to free(ptr). Unless ptr is area pointed to
      was moved, a free(ptr) is done.
    */

    template<typename T, typename Allocator>
    void mem_realloc(T** dest, size_t cap, T* src, size_t size, Allocator& allocator)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /*  If ::realloc allocates at a new address, it will also free the
                current location, which means it is dangerous to construct
                from the old object with ::new(new_add)T(old_obj);

                You can fix this by using a memory pool and controlling all
                memory allocation (malloc, calloc, realloc and free).
            */
            *dest = allocator.allocate(cap, 0);
            if(*dest == 0) throw stl::exception("bad allocation");

            // if(*dest != src)
            for(size_t i = 0; i < size; ++i)
            {
                T* d1 = (*dest) + i;
                T* s1 = src + i;
                allocator.construct(d1, *s1);
                allocator.destroy(s1);
            }

            allocator.deallocate(src, 0);
        }
    }

    template<typename Allocator>
    void mem_realloc(char** dest, size_t cap, char* src, size_t size, Allocator& allocator)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(signed char** dest, size_t cap, signed char* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }
    
    template<typename Allocator>
    void mem_realloc(unsigned char** dest, size_t cap, unsigned char* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(wchar_t** dest, size_t cap, wchar_t* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(short** dest, size_t cap, short* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned short** dest, size_t cap, unsigned short* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(int** dest, size_t cap, int* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned int** dest, size_t cap, unsigned int* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(long** dest, size_t cap, long* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned long** dest, size_t cap, unsigned long* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(double** dest, size_t cap, double* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(float** dest, size_t cap, float* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(long long** dest, size_t cap, long long* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(unsigned long long** dest, size_t cap, unsigned long long* src, size_t size, Allocator& allocator)
    {
        if (cap <= size)
        {
            *dest = src;
        }
        else
        {
            // calls ::realloc underneath - no need to free src (see allocator)
            *dest = allocator.allocate(cap, src);
            if (*dest == 0) throw stl::exception("bad allocation");
        }
    }

    //////////////////////////////////////////////////////////////////////////

} // namespace



#endif // __memmanip_hpp__

