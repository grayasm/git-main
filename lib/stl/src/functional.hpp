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


#ifndef __functional_hpp__
#define __functional_hpp__


namespace stl
{

    //////////////////////////////////////////////////////////////////////////
    //Base classes:
    //////////////////////////////////////////////////////////////////////////

    //unary_function   Unary function object base class (class template)
    template <typename Arg, typename Result>
    struct unary_function
    {
        typedef Arg argument_type;
        typedef Result result_type;
    };


    //binary_function   Binary function object base class (class template)
    template <typename Arg1, typename Arg2, typename Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };


    //////////////////////////////////////////////////////////////////////////
    //Operator classes
    //////////////////////////////////////////////////////////////////////////

    //Arithmetic operations:
    //////////////////////////////////////////////////////////////////////////


    //plus   Addition function object class (class template)
    template <typename T>
    struct plus : binary_function <T,T,T>
    {
        T operator() (const T& x, const T& y) const
        {
            return x + y;
        }
    };


    //minus   Subtraction function object class (class template)
    template <typename T>
    struct minus : binary_function <T,T,T>
    {
        T operator() (const T& x, const T& y) const
        {
            return x - y;
        }
    };


    //multiplies   Multiplication function object class (class template)
    template <typename T>
    struct multiplies : binary_function <T,T,T>
    {
        T operator() (const T& x, const T& y) const
        {
            return x * y;
        }
    };


    //divides   Division function object class (class template)
    template <typename T>
    struct divides : binary_function <T,T,T>
    {
        T operator() (const T& x, const T& y) const
        {
            return x / y;
        }
    };


    //modulus   Modulus function object class (class template )
    template <typename T>
    struct modulus : binary_function <T,T,T>
    {
        T operator() (const T& x, const T& y) const
        {
            return x % y;
        }
    };


    //negate   Negative function object class (class template)
    template <typename T>
    struct negate : unary_function <T,T>
    {
        T operator() (const T& x) const
        {
            return -x;
        }
    };

    //Comparison operations:
    //////////////////////////////////////////////////////////////////////////


    //equal_to   Function object class for equality comparison (class template )
    template <typename T>
    struct equal_to : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x == y;
        }
    };


    //not_equal_to   Function object class for non-equality comparison (class template )
    template <typename T>
    struct not_equal_to : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x != y;
        }
    };

    //greater   Function object class for greater-than inequality comparison (class template )
    template <typename T>
    struct greater : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x > y;
        }
    };


    //less   Function object class for less-than inequality comparison (class template )
    template <typename T>
    struct less : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x < y;
        }
    };

    //greater_equal   Function object class for greater-than-or-equal-to comparison (class template )
    template <typename T>
    struct greater_equal : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x >= y;
        }
    };


    //less_equal   Function object class for less-than-or-equal-to comparison (class template )
    template <typename T>
    struct less_equal : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x <= y;
        }
    };


    //Logical operations:
    //////////////////////////////////////////////////////////////////////////

    //logical_and   Logical AND function object class (class template )
    template <typename T>
    struct logical_and : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x && y;
        }
    };


    //logical_or   Logical OR function object class (class template )
    template <typename T>
    struct logical_or : binary_function <T,T,bool>
    {
        bool operator() (const T& x, const T& y) const
        {
            return x || y;
        }
    };


    //logical_not   Logical NOT function object class (class template )
    template <typename T>
    struct logical_not : unary_function <T,bool>
    {
        bool operator() (const T& x) const
        {
            return !x;
        }
    };



    //////////////////////////////////////////////////////////////////////////
    //Instrumental types
    //////////////////////////////////////////////////////////////////////////


    //unary_negate   Generate negation of unary function object class (class template)
    template <typename Predicate>
    class unary_negate : public unary_function <typename Predicate::argument_type, bool>
    {
    protected:
        Predicate fn;
    public:
        explicit unary_negate ( const Predicate& pred )
            : fn (pred)
        {
        }

        bool operator() (const typename Predicate::argument_type& x) const
        {
            return !fn(x);
        }
    };


    //binary_negate   Generate negation of binary function object class (class template)
    template <typename Predicate>
    class binary_negate
        : public binary_function <typename Predicate::first_argument_type,
                                  typename Predicate::second_argument_type, bool>
    {
    protected:
        Predicate fn;
    public:
        explicit binary_negate ( const Predicate& pred )
            : fn (pred)
        {
        }

        bool operator() (const typename Predicate::first_argument_type& x,
                         const typename Predicate::second_argument_type& y) const
        {
            return !fn(x,y);
        }
    };


    //binder1st   Generate function object class with 1st parameter bound (class template )
    template <typename Operation>
    class binder1st
        : public unary_function <typename Operation::second_argument_type,
                                 typename Operation::result_type>
    {
    protected:
        Operation op;
        typename Operation::first_argument_type value;

    public:
        binder1st ( const Operation& x, const typename Operation::first_argument_type& y)
            : op (x)
            , value(y)
        {
        }

        typename Operation::result_type operator() (const typename Operation::second_argument_type& x) const
        {
            return op(value, x);
        }
    };


    //binder2nd   Generate function object class with 2nd parameter bound (class template )
    template <typename Operation>
    class binder2nd : public unary_function <typename Operation::first_argument_type,
                                             typename Operation::result_type>
    {
    protected:
        Operation op;
        typename Operation::second_argument_type value;

    public:
        binder2nd ( const Operation& x, const typename Operation::second_argument_type& y)
            : op (x)
            , value(y)
        {
        }

        typename Operation::result_type operator() (const typename Operation::first_argument_type& x) const
        {
            return op(x, value);
        }
    };


    //pointer_to_unary_function   Generate unary function object class from pointer (class template)
    template <typename Arg, typename Result>
    class pointer_to_unary_function : public unary_function <Arg,Result>
    {
    protected:
        Result(*pfunc)(Arg);

    public:
        explicit pointer_to_unary_function ( Result (*f)(Arg) )
        : pfunc (f)
        {
        }

        Result operator() (Arg x) const
        {
            return pfunc(x);
        }
    };


    //pointer_to_binary_function   Generate binary function object class from pointer (class template)
    template <typename Arg1, typename Arg2, typename Result>
    class pointer_to_binary_function : public binary_function <Arg1,Arg2,Result>
    {
    protected:
        Result(*pfunc)(Arg1,Arg2);

    public:
        explicit pointer_to_binary_function ( Result (*f)(Arg1,Arg2) )
        : pfunc (f)
        {
        }

        Result operator() (Arg1 x, Arg2 y) const
        {
            return pfunc(x, y);
        }
    };


    //mem_fun_t   Generate function object class from parameterless member (pointer version) (class template)
    template <typename S, typename T>
    class mem_fun_t : public unary_function <T*,S>
    {
        S (T::*pmem)();

    public:
        explicit mem_fun_t ( S (T::*p)() )
        : pmem (p)
        {
        }

        S operator() (T* p) const
        {
            return (p->*pmem)();
        }
    };


    //mem_fun1_t   Generate function object class from single-parameter member (pointer version) (class template)
    template <typename S, typename T, typename A>
    class mem_fun1_t : public binary_function <T*,A,S>
    {
        S (T::*pmem)(A);

    public:
        explicit mem_fun1_t ( S (T::*p)(A) )
        : pmem (p)
        {
        }

        S operator() (T* p, A x) const
        {
            return (p->*pmem)(x);
        }
    };

    //const_mem_fun_t   Generate function object class from const parameterless member (pointer version) (class template)
    template <typename S, typename T>
    class const_mem_fun_t : public unary_function <T*,S>
    {
        S (T::*pmem)() const;

    public:
        explicit const_mem_fun_t ( S (T::*p)() const )
        : pmem (p)
        {
        }

        S operator() (T* p) const
        {
            return (p->*pmem)();
        }
    };


    //const_mem_fun1_t   Generate function object class from single-parameter const member (pointer version) (class template)
    template <typename S, typename T, typename A>
    class const_mem_fun1_t : public binary_function <T*,A,S>
    {
        S (T::*pmem)(A) const;

    public:
        explicit const_mem_fun1_t ( S (T::*p)(A) const )
        : pmem (p)
        {
        }

        S operator() (T* p, A x) const
        {
            return (p->*pmem)(x);
        }
    };


    //mem_fun_ref_t   Generate function object class from parameterless member (reference version) (class template)
    template <typename S, typename T>
    class mem_fun_ref_t : public unary_function <T,S>
    {
        S (T::*pmem)();

    public:
        explicit mem_fun_ref_t ( S (T::*p)() )
        : pmem (p)
        {
        }

        S operator() (T& p) const
        {
            return (p.*pmem)();
        }
    };


    //mem_fun1_ref_t   Generate function object class from single-parameter member (reference version) (class template)
    template <typename S, typename T, typename A>
    class mem_fun1_ref_t : public binary_function <T,A,S>
    {
        S (T::*pmem)(A);

    public:
        explicit mem_fun1_ref_t ( S (T::*p)(A) )
        : pmem (p)
        {
        }

        S operator() (T& p, A x) const
        {
            return (p.*pmem)(x);
        }
    };


    //const_mem_fun_ref_t   Generate function object class from const parameterless member (reference version) (class template)
    template <typename S, typename T>
    class const_mem_fun_ref_t : public unary_function <T,S>
    {
        S (T::*pmem)() const;

    public:
        explicit const_mem_fun_ref_t ( S (T::*p)() const )
        : pmem (p)
        {
        }

        S operator() (T& p) const
        {
            return (p.*pmem)();
        }
    };


    //const_mem_fun1_ref_t   Generate function object class from single-parameter const member (reference version) (class template)
    template <typename S, typename T, typename A>
    class const_mem_fun1_ref_t : public binary_function <T,A,S>
    {
        S (T::*pmem)(A) const;

    public:
        explicit const_mem_fun1_ref_t ( S (T::*p)(A) const )
        : pmem (p)
        {
        }

        S operator() (T& p, A x) const
        {
            return (p.*pmem)(x);
        }
    };





    //////////////////////////////////////////////////////////////////////////
    //Adaptor and conversion functions
    //////////////////////////////////////////////////////////////////////////

    //Negators
    //////////////////////////////////////////////////////////////////////////

    //not1   Return negation of unary function object (function template)
    template <typename Predicate>
    inline unary_negate<Predicate> not1 (const Predicate& pred)
    {
        return unary_negate<Predicate>(pred);
    }


    //not2   Return negation of binary function object (function template)
    template <typename Predicate>
    inline binary_negate<Predicate> not2 (const Predicate& pred)
    {
        return binary_negate<Predicate>(pred);
    }


    //Parameter binders
    //////////////////////////////////////////////////////////////////////////

    //bind1st   Return function object with first parameter bound (function template )
    template <typename Operation, typename T>
    inline binder1st<Operation> bind1st (const Operation& op, const T& x)
    {
        return binder1st<Operation>(op, typename Operation::first_argument_type(x));
    }

    //bind2nd   Return function object with second parameter bound (function template )
    template <typename Operation, typename T>
    inline binder2nd<Operation> bind2nd (const Operation& op, const T& x)
    {
        return binder2nd<Operation>(op, typename Operation::second_argument_type(x));
    }


    //Converters
    //////////////////////////////////////////////////////////////////////////

    //ptr_fun   Convert function pointer to function object (function template)
    template <typename Arg, typename Result>
    inline pointer_to_unary_function<Arg,Result> ptr_fun (Result (*f)(Arg))
    {
        return pointer_to_unary_function<Arg,Result>(f);
    }

    template <typename Arg1, typename Arg2, typename Result>
    inline pointer_to_binary_function<Arg1,Arg2,Result> ptr_fun (Result (*f)(Arg1,Arg2))
    {
        return pointer_to_binary_function<Arg1,Arg2,Result>(f);
    }


    //mem_fun   Convert member function to function object (pointer version) (function template)
    template <typename S, typename T>
    inline mem_fun_t<S,T> mem_fun (S (T::*f)())
    {
        return mem_fun_t<S,T>(f);
    }


    template <typename S, typename T, typename A>
    inline mem_fun1_t<S,T,A> mem_fun (S (T::*f)(A))
    {
        return mem_fun1_t<S,T,A>(f);
    }


    template <typename S, typename T>
    inline const_mem_fun_t<S,T> mem_fun (S (T::*f)() const)
    {
        return const_mem_fun_t<S,T>(f);
    }


    template <typename S, typename T, typename A>
    inline const_mem_fun1_t<S,T,A> mem_fun (S (T::*f)(A) const)
    {
        return const_mem_fun1_t<S,T,A>(f);
    }


    //mem_fun_ref   Convert member function to function object (reference version) (class template)
    template <typename S, typename T>
    inline mem_fun_ref_t<S,T> mem_fun_ref (S (T::*f)())
    {
        return mem_fun_ref_t<S,T>(f);
    }


    template <typename S, typename T, typename A>
    inline mem_fun1_ref_t<S,T,A> mem_fun_ref (S (T::*f)(A))
    {
        return mem_fun1_ref_t<S,T,A>(f);
    }


    template <typename S, typename T>
    inline const_mem_fun_ref_t<S,T> mem_fun_ref (S (T::*f)() const)
    {
        return const_mem_fun_ref_t<S,T>(f);
    }


    template <typename S, typename T, typename A>
    inline const_mem_fun1_ref_t<S,T,A> mem_fun_ref (S (T::*f)(A) const)
    {
        return const_mem_fun1_ref_t<S,T,A>(f);
    }

} // namespace


#endif//__functional_hpp__

