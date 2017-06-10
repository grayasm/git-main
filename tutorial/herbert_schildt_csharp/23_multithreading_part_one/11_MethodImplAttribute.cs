/*
    Using MethodImplAttribute.

    It is possible to synchronize an entire method by using the
    MethodImplAttribute attribute. This approach can be used as
    an alternative to the lock statement in cases in which the
    entire contents of a method are to be locked. MethodImplAttribute
    is defined within the System.Runtime.CompilerServices namespace.
    The constructor that applies to synchronization is shown here:

public MethodImplAttribute(MethodImplOptions methodImplOptions)

*/


// Use MethodImplAttribute to synchronize a method.
using System;
using System.Threading;
using System.Runtime.CompilerServices;


// Rewrite of TickTock to use MethodImplOptions.Synchronized.
class TickTock
{
    /* The following attribute synchronizes the entire Tick() method. */
    [MethodImplAttribute(MethodImplOptions.Synchronized)]
    public void Tick(bool running)
    {
        if(!running) // stop the clock
        {
            Monitor.Pulse(this); // notify any waiting threads
            return;
        }

        Console.Write("Tick ");
        Monitor.Pulse(this); // let Tock() run
        Monitor.Wait(this); // wait for Tock() to complete
    }

    /* The following attribute synchronizes the entire Tock() method. */
    [MethodImplAttribute(MethodImplOptions.Synchronized)]
    public void Tock(bool running)
    {
        if(!running) // stop the clock
        {
            Monitor.Pulse(this); // notify any waiting threads
            return;
        }

        Console.WriteLine("Tock");
        Monitor.Pulse(this); // let Tick() run
        Monitor.Wait(this); // wait for Tick() to complete
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
