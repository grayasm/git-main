/*
    The Interlocked Class.

    It easies the change the value of a shared variable. The class guarantee
    the execution performed as a single, uninterruptable operation.
*/

// Use Interlocked operations.
using System;
using System.Threading;


// A shared resource.
class SharedRes
{
    public static int Count = 0;
}


// This thread increments SharedRes.Count.
class IncThread
{
    public Thread Thrd;

    public IncThread(string name)
    {
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        for(int i=0; i<5; i++)
        {
            Interlocked.Increment(ref SharedRes.Count);
            Console.WriteLine(Thrd.Name + " Count is " + SharedRes.Count);
        }
    }
}


// This thread decrements SharedRes.Count.
class DecThread
{
    public Thread Thrd;

    public DecThread(string name)
    {
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        for(int i=0; i<5; i++)
        {
            Interlocked.Decrement(ref SharedRes.Count);
            Console.WriteLine(Thrd.Name + " Count is " + SharedRes.Count);
        }
    }
}


class InterlockedDemo
{
    static void Main()
    {
        // Construct two threads.
        IncThread mt1 = new IncThread("Increment Thread");
        DecThread mt2 = new DecThread("Decrement Thread");

        mt1.Thrd.Join();
        mt2.Thrd.Join();
    }
}
