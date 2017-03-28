/*
    Using a Constraint to Establish a Relationship Between Two Type Parameters

    There is a variation of the base class constraint that allows you
    to establish a relationship between two type parameters. For example,
    consider the following generic class declaration:

class Gen<T, V> where V : T {

    In this declaration, the where clause tells the compiler that the
    type argument bound to V must be identical to or inherit from the
    type argument bound to T. If this relationship is not present when
    an object of type Gen is declared, then a compile-time error will
    result. A constraint that uses a type parameter, such as that just
    shown, is called a naked type constraint.
*/

// Create relationship between two type parameters.
using System;

class A
{
    //...
}

class B : A
{
    // ...
}


// Here, V must be or inherit from T.
class Gen<T, V> where V : T
{
    // ...
}


class NakedConstraintDemo
{
    static void Main()
    {
        // This declaration is OK because B inherits A.
        Gen<A, B> x = new Gen<A, B>();

        // This declaration is in error because
        // A does not inherit B.
        // Gen<B, A> y = new Gen<B, A>();
    }
}
