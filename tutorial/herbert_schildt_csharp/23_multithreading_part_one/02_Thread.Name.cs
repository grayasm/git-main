// An alternate way to start a thread.
using System;
using System.Threading;


class MyThread
{
    public int Count;
    public Thread Thrd;
    public MyThread(string name)
    {
        Count = 0;
        Thrd = new Thread(this.Run);
        Thrd.Name = name; // set the name of the thread
        Thrd.Start(); // start the thread
    }

    // Entry point of thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " starting.");
        do
        {
            Thread.Sleep(500);
            Console.WriteLine("In " + Thrd.Name + ", Count is " + Count);
            Count++;
        }
        while(Count < 10);

        Console.WriteLine(Thrd.Name + " terminating.");
    }
}


class MultiThreadImproved
{
    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // First, construct a MyThread object.
        MyThread mt = new MyThread("Child #1");

        do
        {
            Console.Write(".");
            Thread.Sleep(100);
        }
        while (mt.Count != 10);

        Console.WriteLine("Main thread ending.");
    }
}
