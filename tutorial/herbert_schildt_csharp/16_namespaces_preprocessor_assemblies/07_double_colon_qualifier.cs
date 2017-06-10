/*
    The trouble is that both namespaces, Counter and AnotherCounter,
    declare a class called CountDown, and both namespaces have been
    brought into view. Thus, to which version of CountDown does the
    preceding declaration refer?

    The :: qualifier was designed to handle these types of problems.
    To use the :: you must first define an alias for the namespace
    you want to qualify. Then, simply qualify the ambiguous element
    with the alias.
*/

// Demonstrate the :: qualifier.
using System;
using Counter;
using AnotherCounter;


// Give Counter an alias called Ctr.
using Ctr = Counter;

// Declare a namespace for counters.
namespace Counter
{
    // A simple countdown counter.
    class CountDown
    {
        int val;
        public CountDown(int n)
        {
            val = n;
        }
        // ...
    }
}

// Another counter namespace.
namespace AnotherCounter
{
    // Declare another class called CountDown, which
    // is in the AnotherCounter namespace.

    class CountDown
    {
        int val;

        public CountDown(int n)
        {
            val = n;
        }
        // ...
    }
}

class AliasQualifierDemo
{
    static void Main()
    {
        // Here, the :: operator
        // tells the compiler to use the CountDown
        // that is in the Counter namespace.
        Ctr::CountDown cd1 = new Ctr::CountDown(10);

        // ...
    }
}
