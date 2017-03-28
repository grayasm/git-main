/*
    Namespaces Prevent Name Conflicts
    The key point about a namespace is that names declared within it
    won’t conflict with similar names declared outside of it.
*/

// Namespaces prevent name conflicts.
using System;

// Declare the Counter namespace.
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
}

// Declare the Counter2 namespace.
namespace Counter2
{
    /* This CountDown is in the Counter2 namespace and
       does not conflict with the one in Counter. */
    class CountDown
    {
        public void Count()
        {
            Console.WriteLine("This is Count() in the " +
                              "Counter2 namespace.");
        }
    }
}

class NSDemo2
{
    static void Main()
    {
        // This is CountDown in the Counter namespace.
        Counter.CountDown cd1 = new Counter.CountDown(10);

        // This is CountDown in the Counter2 namespace.
        Counter2.CountDown cd2 = new Counter2.CountDown();
        int i;

        do {
            i = cd1.Count();
            Console.Write(i + " ");
        } while(i > 0);

        Console.WriteLine();
        cd2.Count();
    }
}
