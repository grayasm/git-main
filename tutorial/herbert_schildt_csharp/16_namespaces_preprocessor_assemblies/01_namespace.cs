/*
    Declaring a Namespace
    A namespace is declared using the namespace keyword.
    The general form of namespace is shown here:

namespace name {
    // members
}

*/

using System;

// Declare a namespace for counters.
namespace Counter {

    // A simple countdown counter.
    class CountDown
    {
        int val;

        public CountDown(int n)
        {
            val = n;
        }

        public void Reset(int n)
        {
            val = n;
        }

        public int Count()
        {
            if(val > 0)
                return val--;
            else
                return 0;
        }
    }
} // This is the end of the Counter namespace.


class NSDemo
{
    static void Main()
    {
        // Notice how CountDown is qualified by Counter.
        Counter.CountDown cd1 = new Counter.CountDown(10);

        int i;
        do {
            i = cd1.Count();
            Console.Write(i + " ");
        } while(i > 0);

        Console.WriteLine();

        // Again, notice how CountDown is qualified by Counter.
        Counter.CountDown cd2 = new Counter.CountDown(20);

        do {
            i = cd2.Count();
            Console.Write(i + " ");
        } while(i > 0);

        Console.WriteLine();
        cd2.Reset(4);

        do {
            i = cd2.Count();
            Console.Write(i + " ");
        } while(i > 0);

        Console.WriteLine();
    }
}
