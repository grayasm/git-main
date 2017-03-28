/*
    Using the Main Thread

    As mentioned at the start of this chapter, all C# programs have at
    least one thread of execution, called the main thread, which is given
    to the program automatically when it begins running.

    The main thread can be handled just like all other threads. To access
    the main thread, you must obtain a Thread object that refers to it.
    You do this through the CurrentThread property, which is a member
    of Thread. Its general form is shown here:

public static Thread CurrentThread { get; }

*/


// Control the main thread.
using System;
using System.Threading;


class UseMain
{
    static void Main()
    {
        Thread Thrd;

        // Get the main thread.
        Thrd = Thread.CurrentThread;

        // Display main thread’s name.
        if(Thrd.Name == null)
            Console.WriteLine("Main thread has no name.");
        else
            Console.WriteLine("Main thread is called: " + Thrd.Name);

        // Display main thread’s priority.
        Console.WriteLine("Priority: " + Thrd.Priority);
        Console.WriteLine();

        // Set the name and priority.
        Console.WriteLine("Setting name and priority.\n");

        Thrd.Name = "Main Thread";

        Thrd.Priority = ThreadPriority.AboveNormal;
        Console.WriteLine("Main thread is now called: " + Thrd.Name);

        Console.WriteLine("Priority is now: " + Thrd.Priority);
    }
}
