/*
  Copyright (C) 2011 Mihai Vasilian

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



#ifndef __iterator_hpp__
#define __iterator_hpp__


namespace stl
{
    struct input_iterator_tag {};

    struct output_iterator_tag {};

    struct forward_iterator_tag : public input_iterator_tag {};

    struct bidirectional_iterator_tag : public forward_iterator_tag {};

    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename category,
             typename T,
             typename diff = long,
             typename ptr = T*,
             typename ref = T&>
    struct iterator
    {
        typedef category iterator_category;
        typedef T value_type;
        typedef diff difference_type;
        typedef diff distance_type;
        typedef ptr pointer;
        typedef ref reference;
    };//struct


    template<typename category,
             typename T,
             typename diff = long,
             typename const_ptr = const T*,
             typename const_ref = const T&>
    struct const_iterator
    {
        typedef category iterator_category;
        typedef T value_type;
        typedef diff difference_type;
        typedef diff distance_type;
        typedef const_ptr const_pointer;
        typedef const_ref const_reference;
    };//struct



    template <typename Iterator> struct iterator_traits {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };

    template <typename T> struct iterator_traits<T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef long difference_type; // ptrdiff_t
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
    };

    template <typename T> struct iterator_traits<const T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef long difference_type; // ptrdiff_t
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
    };


    //see utility.hpp for specialized iterator_traits  (e.g. <bool>, <char>, etc)


} // namespace




#endif//__iterator_hpp__
