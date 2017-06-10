// Demonstrate a continuation.
using System;
using System.Threading;
using System.Threading.Tasks;


class ContinuationDemo
{
    // A method to be run as a task.
    static void MyTask()
    {
        Console.WriteLine("MyTask() starting");

        for(int count = 0; count < 5; count++)
        {
            Thread.Sleep(500);
            Console.WriteLine("In MyTask() count is " + count );
        }

        Console.WriteLine("MyTask terminating");
    }

    // A method to be run as a continuation.
    static void ContTask(Task t)
    {
        Console.WriteLine("Continuation starting");

        for(int count = 0; count < 5; count++)
        {
            Thread.Sleep(500);
            Console.WriteLine("Continuation count is " + count );
        }

        Console.WriteLine("Continuation terminating");
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Construct the first task.
        Task tsk = new Task(MyTask);

        // Now, create the continuation.
        Task taskCont = tsk.ContinueWith(ContTask);

        // Begin the task sequence.
        tsk.Start();

        // Just wait on the continuation.
        taskCont.Wait();
        tsk.Dispose();
        taskCont.Dispose();

        Console.WriteLine("Main thread ending.");
    }
}
