/*
Copyright (C) 2011 Mihai Vasilian
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
    };


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
    };


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
