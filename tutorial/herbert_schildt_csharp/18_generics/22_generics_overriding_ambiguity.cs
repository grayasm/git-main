/*
    Overloading Methods That Use Type Parameters
     In general, a method that uses a type parameter as the data type
     of a parameter can be overloaded as long as the signatures of the
     two versions differ.
*/

// Ambiguity can result when overloading methods that
// use type parameters.
//
// This program will not compile.

using System;


// A generic class that contains a potentially ambiguous
// overload of the Set() method.
class Gen<T, V>
{
    T ob1;
    V ob2;

    // ...
    // In some cases, these two methods
    // will not differ in their parameter types.
    public void Set(T o)
    {
        ob1 = o;
    }

    public void Set(V o)
    {
        ob2 = o;
    }
}


class AmbiguityDemo
{
    static void Main()
    {
        Gen<int, double> ok = new Gen<int, double>();
        Gen<int, int> notOK = new Gen<int, int>();

        ok.Set(10); // is valid, type args differ
        notOK.Set(10); // ambiguous, type args are the same!
    }
}
