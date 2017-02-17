/*
    Canceling Abort( )
    A thread can override a request to abort. To do so, the thread must
    catch the ThreadAbortException and then call ResetAbort( ).
    This prevents the exception from being automatically rethrown when the
    thread's exception handler ends.
    ResetAbort( ) is declared like this:

public static void ResetAbort( )

*/

// Using ResetAbort().
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
            try
            {
                Console.Write(i + " ");
                if((i%10)==0)
                {
                    Console.WriteLine();
                    Thread.Sleep(250);
                }
            }
            catch(ThreadAbortException exc)
            {
                if((int)exc.ExceptionState == 0)
                {
                    Console.WriteLine("Abort Cancelled! Code is " +
                                      exc.ExceptionState);

                    Thread.ResetAbort();
                }
                else
                {
                    Console.WriteLine("Thread aborting, code is " +
                                      exc.ExceptionState);
                }
            }
        }
        Console.WriteLine(Thrd.Name + " exiting normally.");
    }
}


class ResetAbort
{
    static void Main()
    {
        MyThread mt1 = new MyThread("My Thread");

        Thread.Sleep(1000); // let child thread start executing

        Console.WriteLine("Stopping thread.");
        mt1.Thrd.Abort(0); // this won’t stop the thread

        Thread.Sleep(1000); // let child execute a bit longer

        Console.WriteLine("Stopping thread.");

        mt1.Thrd.Abort(100); // this will stop the thread
        mt1.Thrd.Join(); // wait for thread to terminate

        Console.WriteLine("Main thread terminating.");
    }
}
