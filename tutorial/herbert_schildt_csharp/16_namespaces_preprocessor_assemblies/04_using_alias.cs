// Demonstrate a using alias.
using System;

// Create an alias for Counter.CountDown.
using MyCounter = Counter.CountDown;

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

        public void Reset(int n)
        {
            val = n;
        }

        public int Count()
        {
            if(val > 0) return val--;
            else return 0;
        }
    }
}

class NSDemo4
{
    static void Main()
    {
        // Here, MyCounter is used as a name for Counter.CountDown.
        MyCounter cd1 = new MyCounter(10);
        int i;

        do {
            i = cd1.Count();
            Console.Write(i + " ");
        } while(i > 0);

        Console.WriteLine();
        MyCounter cd2 = new MyCounter(20);

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
