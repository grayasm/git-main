// Use Parallel.Invoke( ) to execute methods concurrently.
// This version uses lambda expressions.

using System;
using System.Threading;
using System.Threading.Tasks;


class DemoParallel
{
    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Run two anonymous methods specified via lambda expressions.
        Parallel.Invoke( () => {

            Console.WriteLine("Expression #1 starting");

            for(int count = 0; count < 5; count++)
            {
                Thread.Sleep(500);
                Console.WriteLine("Expression #1 count is " + count );
            }

            Console.WriteLine("Expression #1 terminating");

        }, () => {

            Console.WriteLine("Expression #2 starting");

            for(int count = 0; count < 5; count++)
            {
                Thread.Sleep(500);
                Console.WriteLine("Expression #2 count is " + count );
            }

            Console.WriteLine("Expression #2 terminating");
        } );

        Console.WriteLine("Main thread ending.");
    }
}
