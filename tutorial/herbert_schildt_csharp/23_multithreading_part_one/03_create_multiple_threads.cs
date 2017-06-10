// Create multiple threads of execution.
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
        Thrd.Name = name;
        Thrd.Start();
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


class MoreThreads
{
    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Construct three threads.
        MyThread mt1 = new MyThread("Child #1");
        MyThread mt2 = new MyThread("Child #2");
        MyThread mt3 = new MyThread("Child #3");

        do
        {
            Console.Write(".");
            Thread.Sleep(100);
        }
        while (mt1.Count < 10 || mt2.Count < 10 || mt3.Count < 10);

        Console.WriteLine("Main thread ending.");
    }
}
