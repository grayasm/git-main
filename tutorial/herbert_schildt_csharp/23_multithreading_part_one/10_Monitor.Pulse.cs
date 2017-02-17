/*
    Thread Communication Using Wait( ), Pulse( ), and PulseAll( )
    The Wait( ), Pulse( ), and PulseAll( ) methods are defined by
    the Monitor class. These methods can be called only from within
    a locked block of code. Here is how they are used.

    When a thread is temporarily blocked from running, it calls Wait( ).
    This causes the thread to go to sleep and the lock for that object
    to be released, allowing another thread to acquire the lock. At a
    later point, the sleeping thread is awakened when some other thread
    enters the same lock and calls Pulse( ) or PulseAll( ).
    A call to Pulse( ) resumes the first thread in the queue of threads
    waiting for the lock. A call to PulseAll( ) signals the release of
    the lock to all waiting threads.

    Here are two commonly used forms of Wait( ):

public static bool Wait(object obj)
public static bool Wait(object obj, int millisecondsTimeout)

    Here are the general forms for Pulse( ) and PulseAll( ):

public static void Pulse(object obj)
public static void PulseAll(object obj)

*/

// Use Wait() and Pulse() to create a ticking clock.
using System;
using System.Threading;


class TickTock
{
    object lockOn = new object();

    public void Tick(bool running)
    {
        lock(lockOn)
        {
            if(!running) // stop the clock
            {
                Monitor.Pulse(lockOn); // notify any waiting threads
                return;
            }

            Console.Write("Tick ");

            Monitor.Pulse(lockOn); // let Tock() run
            Monitor.Wait(lockOn); // wait for Tock() to complete
        }
    }

    public void Tock(bool running)
    {
        lock(lockOn)
        {
            if(!running) // stop the clock
            {
                Monitor.Pulse(lockOn); // notify any waiting threads
                return;
            }

            Console.WriteLine("Tock");

            Monitor.Pulse(lockOn); // let Tick() run
            Monitor.Wait(lockOn); // wait for Tick() to complete
        }
    }
}


class MyThread
{
    public Thread Thrd;
    TickTock ttOb;

    // Construct a new thread.
    public MyThread(string name, TickTock tt)
    {
        Thrd = new Thread(this.Run);
        ttOb = tt;
        Thrd.Name = name;
        Thrd.Start();
    }

    // Begin execution of new thread.
    void Run()
    {
        if(Thrd.Name == "Tick")
        {
            for(int i=0; i<5; i++)
                ttOb.Tick(true);

            ttOb.Tick(false);
        }
        else
        {
            for(int i=0; i<5; i++)
                ttOb.Tock(true);

            ttOb.Tock(false);
        }
    }
}


class TickingClock
{
    static void Main()
    {
        TickTock tt = new TickTock();

        MyThread mt1 = new MyThread("Tick", tt);
        MyThread mt2 = new MyThread("Tock", tt);

        mt1.Thrd.Join();
        mt2.Thrd.Join();

        Console.WriteLine("Clock Stopped");
    }
}
