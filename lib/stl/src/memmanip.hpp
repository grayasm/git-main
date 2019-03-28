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
      this is left here only for symetry of alloc,*realloc*,free
    */
    template<typename T, typename Allocator>
    void mem_alloc(T** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(char** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(signed char** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(unsigned char** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(wchar_t** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(short** dest, size_t cap, Allocator& allocator)
    {
        *dest = (short*)::malloc(cap * sizeof(short));
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(unsigned short** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(int** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(unsigned int** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(long** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(unsigned long** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(double** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    template<typename Allocator>
    void mem_alloc(float** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(long long** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }

    template<typename Allocator>
    void mem_alloc(unsigned long long** dest, size_t cap, Allocator& allocator)
    {
        *dest = allocator.allocate(cap, 0);
        if(*dest == 0) throw stl::exception("bad allocation");
    }


    //////////////////////////////////////////////////////////////////////////
    /*
      mem_free - free memory, no dtor is called
      this is left only for symetry of alloc,*realloc*,free
    */
    template<typename T, typename Allocator>
    void mem_free(T** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(char** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(signed char** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(unsigned char** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(wchar_t** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(short** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(unsigned short** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(int** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(unsigned int** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(long** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(unsigned long** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(double** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }


    template<typename Allocator>
    void mem_free(float** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(long long** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

    template<typename Allocator>
    void mem_free(unsigned long long** dest, Allocator& allocator)
    {
        allocator.deallocate(*dest, 0);
    }

	//////////////////////////////////////////////////////////////////////////
    /*
      mem_destroy - call each element destructor, does not free memory
    */
    template<typename T, typename Allocator>
    void mem_destroy(T** dest, size_t sz, Allocator& allocator)
    {
	    for(size_t i=0; i < sz; ++i)
	    {		    
		    allocator.destroy((*dest)+i);
	    }
    }

	template<typename T, typename Allocator>
	void mem_destroy_pod(T**, size_t, Allocator&)
	{
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
    /* mem_copy */
    template<typename T>
    inline void mem_copy(T* dst, const T* src, size_t bytes)
    {
        size_t elems = bytes / sizeof(T);
        for(size_t i=0; i < elems; ++i)
        {
            T* d1 = dst + i;
            const T* s1 = src + i;
            if(d1 != s1)
            {				
                d1->T::~T(); //faults when object at d1 was not yet created;
                new(d1)T(*s1);
            }
        }
    }

    template<typename T>
    inline void mem_copy_pod(T* dst, const T* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(char* dst, const char* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(signed char* dst, const signed char* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(unsigned char* dst, const unsigned char* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(wchar_t* dst, const wchar_t* src, size_t bytes)
    {
        /*
          wchar_t *wmemcpy(wchar_t *dest,const wchar_t *src,size_t count);
          wmemcpy copies 'count' wide characters of 2 or 4 bytes.
        */
        if(bytes % sizeof(wchar_t)) throw stl::exception("invalid bytes value");
        ::wmemcpy(dst, src, bytes / sizeof(wchar_t));
    }

    inline void mem_copy(short* dst, const short* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(unsigned short* dst, const unsigned short* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(int* dst, const int* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(unsigned int* dst, const unsigned int* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(long* dst, const long* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(unsigned long* dst, const unsigned long* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(double* dst, const double* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(float* dst, const float* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(long long* dst, const long long* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    inline void mem_copy(unsigned long long* dst, const unsigned long long* src, size_t bytes)
    {
        ::memcpy(dst, src, bytes);
    }

    //////////////////////////////////////////////////////////////////////////
    /* mem_move */
    template<typename T>
    inline void mem_move(T* dst, const T* src, size_t bytes)
    {
		//TODO: test case for non_pod_type with overlapped code

        size_t elems = bytes / sizeof(T);
        if(src + elems < dst || dst + elems < src)
        {
            //non-overlapping region
            for(size_t i=0; i < elems; ++i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;
                d1->T::~T();//faults when object at d1 was not yet created;
                new(d1)T(*s1);
            }
        }
        else if(src > dst)
        {
            //overlapping at right [x]dst ...[x]src
            for(size_t i=0; i < elems; ++i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;
                d1->T::~T();//faults when object at d1 was not yet created;
                new(d1)T(*s1);
            }
        }
        else if(dst > src)
        {
            //overlapping at left [x]src ...[x]dst
            for(size_t i=elems-1; i != (size_t)-1; --i)
            {
                T* d1 = dst + i;
                const T* s1 = src + i;
                d1->T::~T();//faults when object at d1 was not yet created;
                new(d1)T(*s1);
            }
        }
    }

    template<typename T>
    inline void mem_move_pod(T* dst, const T* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(char* dst, const char* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(signed char* dst, const signed char* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(unsigned char* dst, const unsigned char* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(wchar_t* dst, const wchar_t* src, size_t bytes)
    {
        /*
          wchar_t *wmemmove(wchar_t *dest, const wchar_t *src, size_t count);
          wmemcpy copies 'count' wide characters of 2 or 4 bytes.
        */
        if(bytes % sizeof(wchar_t)) throw stl::exception("invalid bytes value");
        ::wmemmove(dst, src, bytes / sizeof(wchar_t));
    }

    inline void mem_move(short* dst, const short* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(unsigned short* dst, const unsigned short* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(int* dst, const int* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(unsigned int* dst, const unsigned int* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(long* dst, const long* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(unsigned long* dst, const unsigned long* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(double* dst, const double* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(float* dst, const float* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(long long* dst, const long long* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    inline void mem_move(unsigned long long* dst, const unsigned long long* src, size_t bytes)
    {
        ::memmove(dst, src, bytes);
    }

    //////////////////////////////////////////////////////////////////////////
    /* memset */
    template<typename T>
    inline void mem_set(T* dst, T val, size_t bytes)
    {
        size_t elems = bytes / sizeof(T);
        for(size_t i = 0; i < elems; ++i)
            dst[i] = val;
    }

    inline void mem_set(char* dst, char val, size_t bytes)
    {
        ::memset(dst, val, bytes);
    }

    inline void mem_set(unsigned char* dst, unsigned char val, size_t bytes)
    {
        ::memset(dst, val, bytes);
    }


    inline void mem_set(wchar_t* dst, wchar_t val, size_t bytes)
    {
        /*
          wchar_t *wmemset(wchar_t *dest, wchar_t c, size_t count);
          Sets the first count wide characters (2 or 4 bytes) of dest to the character c.
        */
        if(bytes % sizeof(wchar_t)) throw stl::exception("invalid bytes value");
        ::wmemset(dst, val, bytes / sizeof(wchar_t));
    }

    //////////////////////////////////////////////////////////////////////////


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
            // buy more memory
            *dest = allocator.allocate(cap, 0);
            if(*dest == 0) throw stl::exception("bad allocation");

            if(src)
            {
                for(size_t i=0; i < size; ++i)
                {
			T* d1 = (*dest) + i;
			T* s1 = src + i;
			new(d1)T(*s1);
			s1->T::~T();
                }

                // release memory at src
                allocator.deallocate(src, 0);
            }
        }
    }

    template<typename T, typename Allocator>
    void mem_realloc_pod(T** dest, size_t cap, T* src, size_t size, Allocator& allocator)
    {
	(void)allocator;
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (T*)::realloc(src, cap * sizeof(T));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(char** dest, size_t cap, char* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {			
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (char*)::realloc(src, cap * sizeof(char));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(signed char** dest, size_t cap, signed char* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (signed char*)::realloc(src, cap * sizeof(signed char));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(unsigned char** dest, size_t cap, unsigned char* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (unsigned char*)::realloc(src, cap * sizeof(unsigned char));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(wchar_t** dest, size_t cap, wchar_t* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (wchar_t*)::realloc(src, cap * sizeof(wchar_t));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(short** dest, size_t cap, short* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (short*)::realloc(src, cap * sizeof(short));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned short** dest, size_t cap, unsigned short* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (unsigned short*)::realloc(src, cap * sizeof(unsigned short));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(int** dest, size_t cap, int* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (int*)::realloc(src, cap * sizeof(int));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned int** dest, size_t cap, unsigned int* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (unsigned int*)::realloc(src, cap * sizeof(unsigned int));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(long** dest, size_t cap, long* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (long*)::realloc(src, cap * sizeof(long));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(unsigned long** dest, size_t cap, unsigned long* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (unsigned long*)::realloc(src, cap * sizeof(unsigned long));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(double** dest, size_t cap, double* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (double*)::realloc(src, cap * sizeof(double));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }


    template<typename Allocator>
    void mem_realloc(float** dest, size_t cap, float* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (float*)::realloc(src, cap * sizeof(float));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(long long** dest, size_t cap, long long* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (long long*)::realloc(src, cap * sizeof(long long));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    template<typename Allocator>
    void mem_realloc(unsigned long long** dest, size_t cap, unsigned long long* src, size_t size, Allocator& /*allocator*/)
    {
        if(cap <= size)
        {
            *dest = src;
        }
        else
        {
            /* src must be returned by an earlier call to malloc(), calloc() or realloc() */
            *dest = (unsigned long long*)::realloc(src, cap * sizeof(unsigned long long));
            if(*dest == 0) throw stl::exception("bad allocation");
        }
    }

    //////////////////////////////////////////////////////////////////////////

} // namespace



#endif // __memmanip_hpp__

