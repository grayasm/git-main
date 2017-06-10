// Use Parallel.Invoke() to execute methods concurrently.
using System;
using System.Threading;
using System.Threading.Tasks;


class DemoParallel
{
    // A method to be run as a task.
    static void MyMeth()
    {
        Console.WriteLine("MyMeth starting");

        for(int count = 0; count < 5; count++)
        {
            Thread.Sleep(500);
            Console.WriteLine("In MyMeth, count is " + count );
        }

        Console.WriteLine("MyMeth terminating");
    }

    // A method to be run as a task.
    static void MyMeth2()
    {
        Console.WriteLine("MyMeth2 starting");
        for(int count = 0; count < 5; count++)
        {
            Thread.Sleep(500);
            Console.WriteLine("In MyMeth2, count is " + count );
        }

        Console.WriteLine("MyMeth2 terminating");
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Run two named methods.
        Parallel.Invoke(MyMeth, MyMeth2);
        Console.WriteLine("Main thread ending.");
    }
}
