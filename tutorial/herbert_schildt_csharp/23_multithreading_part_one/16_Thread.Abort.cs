/*
    Terminating a Thread Via Abort( )
    To terminate a thread prior to its normal conclusion, use Thread.Abort( ).
    Its simplest form is shown here:

public void Abort()

*/

// Stopping a thread by use of Abort().
using System;
using System.Threading;


class MyThread
{
    public Thread Thrd;
    public MyThread(string name)
    {
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        Thrd.Start();
    }

    // This is the entry point for thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " starting.");

        for(int i = 1; i <= 1000; i++)
        {
            Console.Write(i + " ");
            if((i%10)==0)
            {
                Console.WriteLine();
                Thread.Sleep(250);
            }
        }

        Console.WriteLine(Thrd.Name + " exiting.");
    }
}


class StopDemo
{
    static void Main()
    {
        MyThread mt1 = new MyThread("My Thread");

        Thread.Sleep(1000); // let child thread start executing

        Console.WriteLine("Stopping thread.");

        mt1.Thrd.Abort();
        mt1.Thrd.Join(); // wait for thread to terminate

        Console.WriteLine("Main thread terminating.");
    }
}
