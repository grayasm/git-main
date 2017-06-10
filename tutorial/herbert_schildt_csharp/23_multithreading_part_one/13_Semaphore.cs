/*
    The Semaphore.

    A semaphore is similar to a mutex except that it can grant more than
    one thread access to a shared resource at the same time. The semaphore
    is implemented by System.Threading.Semaphore. It has several constructors.
    The simplest form is shown here:

public Semaphore(int initialCount, int maximumCount)

    To acquire access, your code will call WaitOne( ) on the semaphore.
    This method is inherited by Semaphore from the WaitHandle class.
    When your code no longer needs ownership of the semaphore, it releases
    it by calling Release( ), which is shown here:

public int Release( )
public int Release(int releaseCount)

*/

// Use a Semaphore.
using System;
using System.Threading;


// This thread allows only two instances of itself
// to run at any one time.
class MyThread
{
    public Thread Thrd;

    // This creates a semaphore that allows up to two
    // permits to be granted and that initially has
    // two permits available.
    static Semaphore sem = new Semaphore(2, 2);

    public MyThread(string name)
    {
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        Thrd.Start();
    }

    // Entry point of thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " is waiting for a permit.");

        sem.WaitOne();

        Console.WriteLine(Thrd.Name + " acquires a permit.");

        for(char ch='A'; ch < 'D'; ch++)
        {
            Console.WriteLine(Thrd.Name + " : " + ch + " ");
            Thread.Sleep(500);
        }

        Console.WriteLine(Thrd.Name + " releases a permit.");
        // Release the semaphore.
        sem.Release();
    }
}


class SemaphoreDemo
{
    static void Main()
    {
        // Construct three threads.
        MyThread mt1 = new MyThread("Thread #1");
        MyThread mt2 = new MyThread("Thread #2");
        MyThread mt3 = new MyThread("Thread #3");

        mt1.Thrd.Join();
        mt2.Thrd.Join();
        mt3.Thrd.Join();
    }
}
