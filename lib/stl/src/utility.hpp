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




#ifndef __utility_hpp__
#define __utility_hpp__

#include "iterator.hpp"


namespace stl
{

    template <typename T1, typename T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;
        pair()
            : first(T1())
            , second(T2())
        {
        }

        pair(const T1& x, const T2& y)
            : first(x)
            , second(y)
        {
        }

        pair(const pair& p)
            : first(p.first)
            , second(p.second)
        {
        }


        template <typename U, typename V>
        pair (const pair<U,V> &p)
            : first(p.first)
            , second(p.second)
        {
        }
    };//pair


    template <typename T1,typename T2>
    inline pair<T1,T2> make_pair (T1 x, T2 y)
    {
        return ( pair<T1,T2>(x,y) );
    }


    namespace rel_ops
    {
        template <typename T>
        inline bool operator!= (const T& x, const T& y)
        {
            return !(x==y);
        }

        template <typename T>
        inline bool operator > (const T& x, const T& y)
        {
            return y<x;
        }

        template <typename T>
        inline bool operator <= (const T& x, const T& y)
        {
            return !(y<x);
        }

        template <typename T>
        inline bool operator >= (const T& x, const T& y)
        {
            return !(x<y);
        }

    }  //  namespace rel_ops


//////////////////////////////////////////////////////////////////////////
//additional functionality
    template<typename Iterator>
    typename stl::iterator_traits<Iterator>::iterator_category it_cat(const Iterator&)
    {
        typename stl::iterator_traits<Iterator>::iterator_category cat;
        return cat;
    }


    template<> struct iterator_traits<bool>
    {//get traits from bool type
        typedef input_iterator_tag iterator_category;
        typedef bool    value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef bool*   pointer;
        typedef bool&   reference;
    };

    template<> struct iterator_traits<char>
    {//get traits from char type
        typedef input_iterator_tag iterator_category;
        typedef char    value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef char*   pointer;
        typedef char&   reference;
    };


    template<> struct iterator_traits<signed char>
    {   // get traits from signed char type
        typedef input_iterator_tag iterator_category;
        typedef signed char     value_type;
        typedef long            difference_type;
        typedef long            distance_type;
        typedef signed char*    pointer;
        typedef signed char&    reference;
    };

    template<> struct iterator_traits<unsigned char>
    {   // get traits from unsigned char type
        typedef input_iterator_tag iterator_category;
        typedef unsigned char   value_type;
        typedef long            difference_type;
        typedef long            distance_type;
        typedef unsigned char*  pointer;
        typedef unsigned char&  reference;
    };


    template<> struct iterator_traits<wchar_t>
    {   // get traits from wchar_t type
        typedef input_iterator_tag iterator_category;
        typedef wchar_t     value_type;
        typedef long        difference_type;
        typedef long        distance_type;
        typedef wchar_t*    pointer;
        typedef wchar_t&    reference;
    };


    template<> struct iterator_traits<short>
    {   // get traits from short type
        typedef input_iterator_tag iterator_category;
        typedef short   value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef short*  pointer;
        typedef short&  reference;
    };

    template<> struct iterator_traits<unsigned short>
    {   // get traits from unsigned short type
        typedef input_iterator_tag iterator_category;
        typedef unsigned short  value_type;
        typedef long            difference_type;
        typedef long            distance_type;
        typedef unsigned short* pointer;
        typedef unsigned short& reference;
    };

    template<> struct iterator_traits<int>
    {   // get traits from int type
        typedef input_iterator_tag iterator_category;
        typedef int     value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef int*    pointer;
        typedef int&    reference;
    };

    template<> struct iterator_traits<unsigned int>
    {   // get traits from unsigned int type
        typedef input_iterator_tag iterator_category;
        typedef unsigned int    value_type;
        typedef long            difference_type;
        typedef long            distance_type;
        typedef unsigned int*   pointer;
        typedef unsigned int&   reference;
    };

    template<> struct iterator_traits<long>
    {   // get traits from long type
        typedef input_iterator_tag iterator_category;
        typedef long    value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef long*   pointer;
        typedef long&   reference;
    };

    template<> struct iterator_traits<unsigned long>
    {   // get traits from unsigned long type
        typedef input_iterator_tag iterator_category;
        typedef unsigned long   value_type;
        typedef long            difference_type;
        typedef long            distance_type;
        typedef unsigned long*  pointer;
        typedef unsigned long&  reference;
    };

    template<> struct iterator_traits<double>
    {// get traits from double type
        typedef input_iterator_tag iterator_category;
        typedef double      value_type;
        typedef long        difference_type;
        typedef long        distance_type;
        typedef double*     pointer;
        typedef double&     reference;
    };

    template<> struct iterator_traits<float>
    {// get traits from float type
        typedef input_iterator_tag iterator_category;
        typedef float   value_type;
        typedef long    difference_type;
        typedef long    distance_type;
        typedef float*  pointer;
        typedef float&  reference;
    };


    template<> struct iterator_traits<long long>
    {   // get traits from long long type
        typedef input_iterator_tag iterator_category;
        typedef long long   value_type;
        typedef long        difference_type;
        typedef long        distance_type;
        typedef long long*  pointer;
        typedef long long&  reference;
    };

    template<> struct iterator_traits<unsigned long long>
    {   // get traits from unsigned long long type
        typedef input_iterator_tag iterator_category;
        typedef unsigned long long      value_type;
        typedef long                    difference_type;
        typedef long                    distance_type;
        typedef unsigned long long*     pointer;
        typedef unsigned long long&     reference;
    };

//////////////////////////////////////////////////////////////////////////
//classic metaprogramming if statement
    template<bool cond, typename T1, typename T2>
    class If
    {
    public:
        typedef T2 result;
    };

    template<typename T1, typename T2>
    class If<true, T1, T2>
    {
    public:
        typedef T1 result;
    };
//////////////////////////////////////////////////////////////////////////
//advance function
    template<typename InputIterator, typename Difference>
    inline void advance(InputIterator& where, Difference offset, stl::input_iterator_tag)
    {
        //negative values only for bidirectional_iterator_tag and random_access_iterator_tag
        for(; 0 < offset; --offset)
        {
            ++where;
        }
    }

    template<typename ForwardIterator, typename Difference>
    inline void advance(ForwardIterator& where, Difference offset, stl::forward_iterator_tag)
    {
        //negative values only for bidirectional_iterator_tag and random_access_iterator_tag
        for(; 0 < offset; --offset)
        {
            ++where;
        }
    }

    template<typename BidirectionalIterator, typename Difference>
    inline void advance(BidirectionalIterator& where, Difference offset, stl::bidirectional_iterator_tag)
    {
        for(; 0 < offset; --offset)
        {
            ++where;
        }

        for(; offset < 0; ++offset)
        {
            --where;
        }
    }

    template<typename RandomIterator, typename Difference>
    inline void advance(RandomIterator& where, Difference offset, stl::random_access_iterator_tag)
    {
        where += offset;
    }


    template<typename Iterator, typename Difference>
    inline void advance(Iterator& where, Difference offset)
    {
        stl::advance(where, offset, stl::it_cat(where));//it_cat is Iterator::iterator_category;
    }

//////////////////////////////////////////////////////////////////////////
//distance function
    template<typename InputIterator>
    inline typename stl::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last, stl::input_iterator_tag)
    {
        typename stl::iterator_traits<InputIterator>::difference_type offset = 0;
        for(; first != last; ++first)
        {
            ++offset;
        }
        return offset;
    }

    template<typename ForwardIterator>
    inline typename stl::iterator_traits<ForwardIterator>::difference_type
    distance(ForwardIterator first, ForwardIterator last, stl::forward_iterator_tag)
    {
        typename stl::iterator_traits<ForwardIterator>::difference_type offset = 0;
        for(; first != last; ++first)
        {
            ++offset;
        }
        return offset;
    }

    template<typename BidirectionalIterator>
    inline typename stl::iterator_traits<BidirectionalIterator>::difference_type
    distance(BidirectionalIterator first, BidirectionalIterator last, stl::bidirectional_iterator_tag)
    {
        typename stl::iterator_traits<BidirectionalIterator>::difference_type offset = 0;
        for(; first != last; ++first)
        {
            ++offset;
        }
        return offset;
    }


    template<typename RandomIterator>
    inline typename stl::iterator_traits<RandomIterator>::difference_type
    distance(RandomIterator first, RandomIterator last, stl::random_access_iterator_tag)
    {
        return static_cast<typename stl::iterator_traits<RandomIterator>::difference_type>(last - first);
    }


    template<typename Iterator>
    inline typename stl::iterator_traits<Iterator>::difference_type
    distance(Iterator first, Iterator last)
    {
        return stl::distance(first, last, stl::it_cat(first));
    }

//////////////////////////////////////////////////////////////////////////
//back insert iterator
    template <typename Container>
    class back_insert_iterator : public iterator<stl::output_iterator_tag, typename Container::value_type>
    {
    protected:
        Container* container;

    public:
        typedef Container container_type;

        explicit back_insert_iterator (Container& x)
            : container(&x)
        {
        }

        back_insert_iterator<Container>& operator= (typename Container::const_reference value)
        {	// push value into container
            container->push_back(value);
            return *this;
        }

        back_insert_iterator<Container>& operator* ()
        {	// pretend to return designated value
            return *this;
        }

        back_insert_iterator<Container>& operator++ ()
        {	// pretend to preincrement
            return *this;
        }

        back_insert_iterator<Container> operator++ (int)
        {	// pretend to postincrement
            return *this;
        }
    };//back_insert_iterator


// return a back_insert_iterator
    template<typename Container>
    inline stl::back_insert_iterator<Container> back_inserter(Container& cont)
    {
        return stl::back_insert_iterator<Container>(cont);
    }

//////////////////////////////////////////////////////////////////////////
//front insert iterator
    template <class Container>
    class front_insert_iterator : public iterator<stl::output_iterator_tag, typename Container::value_type>
    {
    protected:
        Container* container;

    public:
        typedef Container container_type;

        explicit front_insert_iterator (Container& x)
            : container(&x)
        {
        }

        front_insert_iterator<Container>& operator= (typename Container::const_reference value)
        {	// push value into container
            container->push_front(value);
            return *this;
        }

        front_insert_iterator<Container>& operator* ()
        {	// pretend to return designated value
            return *this;
        }

        front_insert_iterator<Container>& operator++ ()
        {	// pretend to preincrement
            return *this;
        }

        front_insert_iterator<Container> operator++ (int)
        {	// pretend to postincrement
            return *this;
        }
    };


// return front_insert_iterator
    template<typename Container>
    inline stl::front_insert_iterator<Container> front_inserter(Container& cont)
    {
        return stl::front_insert_iterator<Container>(cont);
    }

//////////////////////////////////////////////////////////////////////////
//insert iterator
    template <class Container>
    class insert_iterator : public iterator<stl::output_iterator_tag, typename Container::value_type>
    {
    protected:
        Container* container;
        typename Container::iterator iter;

    public:
        typedef Container container_type;

        explicit insert_iterator (Container& x, typename Container::iterator i)
            : container(&x),
              iter(i)
        {
        }

        insert_iterator<Container>& operator= (typename Container::const_reference value)
        {	// insert into container and increment stored iterator
            iter=container->insert(iter,value);
            ++iter;
            return *this;
        }

        insert_iterator<Container>& operator* ()
        {	// pretend to return designated value
            return *this;
        }

        insert_iterator<Container>& operator++ ()
        {	// pretend to preincrement
            return *this;
        }

        insert_iterator<Container> operator++ (int)
        {	// pretend to postincrement
            return *this;
        }
    };


// return insert_iterator
    template<typename Container, class Iterator>
    inline stl::insert_iterator<Container> inserter(Container& cont, Iterator position)
    {
        return stl::insert_iterator<Container>(cont, position);
    }


//////////////////////////////////////////////////////////////////////////

} // namespace

#endif//__utility_hpp__
