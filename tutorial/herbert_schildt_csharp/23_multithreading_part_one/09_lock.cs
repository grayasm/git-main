/*
    An Alternative Approach
    You might want to synchronize access to a method of a class you
    did not create, which is itself not synchronized. This can occur
    if you want to use a class that was written by a third party and
    for which you do not have access to the source code.
    Thus, it is not possible for you to add a lock statement to the
    appropriate method within the class. How can access to an object
    of this class be synchronized? Fortunately, the solution to this
    problem is simple: Lock access to the object from code outside
    the object by specifying the object in a lock statement.
*/

// Another way to use lock to synchronize access to an object.
using System;
using System.Threading;


class SumArray
{
    int sum;

    public int SumIt(int[] nums)
    {
        sum = 0; // reset sum
        for(int i=0; i < nums.Length; i++)
        {
            sum += nums[i];
            Console.WriteLine("Running total for " +
                              Thread.CurrentThread.Name +
                              " is " + sum);

            Thread.Sleep(10); // allow task-switch
        }
        return sum;
    }
}


class MyThread
{
    public Thread Thrd;
    int[] a;
    int answer;

    /* Create one SumArray object for all
       instances of MyThread. */

    static SumArray sa = new SumArray();

    // Construct a new thread.
    public MyThread(string name, int[] nums)
    {
        a = nums;
        Thrd = new Thread(this.Run);
        Thrd.Name = name;
        Thrd.Start(); // start the thread
    }

    // Begin execution of new thread.
    void Run()
    {
        Console.WriteLine(Thrd.Name + " starting.");

        // Lock calls to SumIt().
        lock(sa) answer = sa.SumIt(a);
        Console.WriteLine("Sum for " + Thrd.Name + " is " + answer);
        Console.WriteLine(Thrd.Name + " terminating.");
    }
}


class Sync
{
    static void Main()
    {
        int[] a = {1, 2, 3, 4, 5};

        MyThread mt1 = new MyThread("Child #1", a);
        MyThread mt2 = new MyThread("Child #2", a);

        mt1.Thrd.Join();
        mt2.Thrd.Join();
    }
}
