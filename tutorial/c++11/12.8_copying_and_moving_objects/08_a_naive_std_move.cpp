/*  This is an in depth tutorial about move semantics and rvalue references:
    http://thbecker.net/articles/rvalue_references/section_08.html

    In pre-11 C++, it was not allowed to take a reference to a reference:
    something like A& & would cause a compile error. C++11, by contrast,
    introduces the following reference collapsing rules:

    A& &  becomes A&
    A& && becomes A&
    A&& & becomes A&
    A&& && becomes A&&

    This applies to template argument deduction for function templates that take
    an argument by rvalue reference to a template argument:

    template<typename T>
    void foo(T&&)

    when foo is called on an lvalue the argument resolves to T&
    when foo is called on an rvalue the argument resolves to T&&
*/

#include <stdio.h>

// reference transformations /usr/include/c++/4.8.2/type_traits, line:1372
template<typename T>
struct remove_reference
{
    typedef T type;
};

template<typename T>
struct remove_reference<T&>
{
    typedef T type;
};

template<typename T>
struct remove_reference<T&&>
{
    typedef T type;
};

template<typename T>
constexpr T&& forward(typename remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}

template<typename T>
constexpr T&& forward(typename remove_reference<T>::type&& t) noexcept
{
    return static_cast<T&&>(t);
}

template<typename T>
constexpr typename remove_reference<T>::type&& move(T&& t) noexcept
{
    return static_cast<typename remove_reference<T>::type&&>(t);
}


// define a class to test move and forward functions
class X
{
public:
    explicit X(int) { printf("X(int)\n"); }

    X(const X& tc) { printf("X(const X&)\n"); }

    X& operator=(const X& tc) { printf("operator=(const X&)\n"); return *this; }

    ~X() { printf("~X()\n"); }

    X(X&& rvref) { printf("X(X&&)\n"); }

    X& operator=(X&& rvref) { printf("operator=(X&&)\n"); return *this; }
};

X&& foo()
{
    X x(3);
    return forward<X>(x);  // use forward to move the temporary x
}

main()
{
    X x(2);
    X y = move(x); // moving x leaves it in undefined state
    X z = foo();
}

/*
  X(int)
  X(X&&)       <- X y = move(x)
  X(int)
  ~X()
  X(X&&)       <- return forward<X>(x)
  ~X()
  ~X()
  ~X()
*/
