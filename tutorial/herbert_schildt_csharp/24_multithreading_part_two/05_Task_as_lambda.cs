// Use a lambda expression as a task.
using System;
using System.Threading;
using System.Threading.Tasks;


class DemoLambdaTask
{
    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // The following uses a lambda expression to define a task.
        Task tsk = Task.Factory.StartNew( () =>
        {
            Console.WriteLine("Task starting");
            for(int count = 0; count < 10; count++)
            {
                Thread.Sleep(500);
                Console.WriteLine("Task count is " + count );
            }

            Console.WriteLine("Task terminating");
        } );


        // Wait until tsk finishes.
        tsk.Wait();

        // Dispose of tsk.
        tsk.Dispose();

        Console.WriteLine("Main thread ending.");
    }
}
