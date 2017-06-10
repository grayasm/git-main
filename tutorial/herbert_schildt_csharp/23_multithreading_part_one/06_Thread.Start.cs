/*
    Passing an Argument to a Thread.
    It is possible to pass an argument to a thread. To do so, you must
    use different forms of Start( ), the Thread constructor, and the
    entry point method. An argument is passed to a thread through this
    version of Start( ):

public void Start(object parameter)

    The object passed to parameter is automatically passed to the
    thread’s entry point method. Thus, to pass an argument to a thread,
    you pass it to Start( ). To make use of the parameterized version
    of Start( ), you must use the following form of the Thread constructor:

public Thread(ParameterizedThreadStart start)

*/

// Passing an argument to the thread method.
using System;
using System.Threading;


class MyThread
{
    public int Count;
    public Thread Thrd;

    // Notice that MyThread is also passed an int value.
    public MyThread(string name, int num)
    {
        Count = 0;

        // Explicitly invoke ParameterizedThreadStart constructor
        // for the sake of illustration.
        Thrd = new Thread(this.Run);
        Thrd.Name = name;

        // Here, Start() is passed num as an argument.
        Thrd.Start(num);
    }


    // Notice that this version of Run() has
    // a parameter of type object.
    void Run(object num)
    {
        Console.WriteLine(Thrd.Name + " starting with count of " + num);
        do
        {
            Thread.Sleep(500);
            Console.WriteLine("In " + Thrd.Name + ", Count is " + Count);
            Count++;
        }
        while(Count < (int) num);

        Console.WriteLine(Thrd.Name + " terminating.");
    }
}


class PassArgDemo
{
    static void Main()
    {
        // Notice that the iteration count is passed
        // to these two MyThread objects.
        MyThread mt = new MyThread("Child #1", 5);
        MyThread mt2 = new MyThread("Child #2", 3);

        do
        {
            Thread.Sleep(100);
        }
        while (mt.Thrd.IsAlive | mt2.Thrd.IsAlive);

        Console.WriteLine("Main thread ending.");
    }
}
