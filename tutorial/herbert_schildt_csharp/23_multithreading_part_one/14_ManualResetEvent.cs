/*
    Using Events
    C# supports another type of synchronization object: the event.
    There are two types of events: manual reset and auto reset.
    These are supported by the classes ManualResetEvent and AutoResetEvent.
    These classes are derived from the top-level class EventWaitHandle

    The constructors for ManualResetEvent and AutoResetEvent are shown here:

public ManualResetEvent(bool initialState)
public AutoResetEvent(bool initialState)

    ManualResetEvent: thread calls WaitOne() to wait for an event. WaitOne()
                      returns immediately if event is in signaled state, or
                      suspends thread execution until the event is signaled.
                      Set() sets the event signaled.
                      Reset() resets the event into non-signaled state.
                      For this event type Reset() needs to be called manually.
    AutoResetEvent:   Similar as above with the difference that the event
                      automatically changes to a non-signaled state as soon
                      as a thread receives the signaled state and resumes its
                      execution.
*/

// Use a manual event object.
using System;
using System.Threading;


// This thread signals the event passed to its constructor.
class MyThread
{
    public Thread Thrd;
    ManualResetEvent mre;

    public MyThread(string name, ManualResetEvent evt)
    {
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        mre = evt;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        Console.WriteLine("Inside thread " + Thrd.Name);
        for(int i=0; i<5; i++)
        {
            Console.WriteLine(Thrd.Name);
            Thread.Sleep(500);
        }

        Console.WriteLine(Thrd.Name + " Done!");
         // Signal the event.
         mre.Set();
     }
}


class ManualEventDemo
{
    static void Main()
    {
        ManualResetEvent evtObj = new ManualResetEvent(false);

        MyThread mt1 = new MyThread("Event Thread 1", evtObj);
        Console.WriteLine("Main thread waiting for event.");

        // Wait for signaled event.
        evtObj.WaitOne();

        Console.WriteLine("Main thread received first event.");

        // Reset the event.
        evtObj.Reset();

        mt1 = new MyThread("Event Thread 2", evtObj);

        // Wait for signaled event.
        evtObj.WaitOne();

        Console.WriteLine("Main thread received second event.");
    }
}
