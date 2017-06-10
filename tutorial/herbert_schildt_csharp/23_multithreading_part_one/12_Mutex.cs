/*
    The Mutex
    A mutex is a mutually exclusive synchronization object. This means
    it can be acquired by one and only one thread at a time.
    The mutex is supported by the System.Threading.Mutex class. It has
    several constructors. Two commonly used ones are shown here:

public Mutex( )
public Mutex(bool initiallyOwned)

    To acquire the mutex, your code will call WaitOne( ) on the mutex.
    This method is inherited by Mutex from the Thread.WaitHandle class.
    Here is its simplest form:

public bool WaitOne( );

    When your code no longer needs ownership of the mutex, it releases
    it by calling ReleaseMutex( ), shown here:

public void ReleaseMutex( )
*/


// Use a Mutex.
using System;
using System.Threading;


// This class contains a shared resource (Count),
// and a mutex (Mtx) to control access to it.
class SharedRes
{
    public static int Count = 0;
    public static Mutex Mtx = new Mutex();
}


// This thread increments SharedRes.Count.
class IncThread
{
    int num;
    public Thread Thrd;

    public IncThread(string name, int n)
    {
        Thrd = new Thread(this.Run);
        num = n;
        Thrd.Name = name;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " is waiting for the mutex.");

        // Acquire the Mutex.
        SharedRes.Mtx.WaitOne();
        Console.WriteLine(Thrd.Name + " acquires the mutex.");
        do
        {
            Thread.Sleep(500);
            SharedRes.Count++;
            Console.WriteLine("In " + Thrd.Name +
                              ", SharedRes.Count is " +
                              SharedRes.Count);

            num--;
        }
        while(num > 0);

        Console.WriteLine(Thrd.Name + " releases the mutex.");

        // Release the Mutex.
        SharedRes.Mtx.ReleaseMutex();
    }
}


// This thread decrements SharedRes.Count.
class DecThread
{
    int num;
    public Thread Thrd;
    public DecThread(string name, int n)
    {
        Thrd = new Thread(new ThreadStart(this.Run));
        num = n;
        Thrd.Name = name;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " is waiting for the mutex.");

        // Acquire the Mutex.
        SharedRes.Mtx.WaitOne();
        Console.WriteLine(Thrd.Name + " acquires the mutex.");

        do
        {
            Thread.Sleep(500);
            SharedRes.Count--;
            Console.WriteLine("In " + Thrd.Name +
                              ", SharedRes.Count is " +
                              SharedRes.Count);

            num--;
        }
        while(num > 0);

        Console.WriteLine(Thrd.Name + " releases the mutex.");

        // Release the Mutex.
        SharedRes.Mtx.ReleaseMutex();
    }
}

class MutexDemo
{
    static void Main()
    {
        // Construct three threads.
        IncThread mt1 = new IncThread("Increment Thread", 5);

        Thread.Sleep(1); // let the Increment thread start
        DecThread mt2 = new DecThread("Decrement Thread", 5);

        mt1.Thrd.Join();
        mt2.Thrd.Join();
    }
}
