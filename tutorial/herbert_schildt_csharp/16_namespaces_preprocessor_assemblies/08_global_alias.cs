// Use the global alias.
using System;


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

// Declare another class called CountDown, which
// is in the global namespace.
class CountDown
{
    int val;
    public CountDown(int n)
    {
        val = n;
    }
    // ...
}

class GlobalAliasQualifierDemo
{
    static void Main()
    {
        // Here, the :: qualifier tells the compiler
        // to use the CountDown in the Counter namespace.

        Ctr::CountDown cd1 = new Ctr::CountDown(10);

        // Next, create CountDown object from global namespace.

        global::CountDown cd2 = new global::CountDown(10);

        // ...
    }
}
