/*
    An Abort( ) Alternative
    You might find a second form of Abort( ) useful in some cases.
    Its general form is shown here:

public void Abort(object stateInfo)

*/


// Using Abort(object).
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
        try
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

            Console.WriteLine(Thrd.Name + " exiting normally.");
        }
        catch(ThreadAbortException exc)
        {
            Console.WriteLine("Thread aborting, code is " + exc.ExceptionState);
        }
    }
}


class UseAltAbort
{
    static void Main()
    {
        MyThread mt1 = new MyThread("My Thread");

        Thread.Sleep(1000); // let child thread start executing

        Console.WriteLine("Stopping thread.");

        mt1.Thrd.Abort(100);
        mt1.Thrd.Join(); // wait for thread to terminate

        Console.WriteLine("Main thread terminating.");
    }
}
