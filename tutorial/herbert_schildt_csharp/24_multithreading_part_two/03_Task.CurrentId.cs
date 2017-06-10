// Demonstrate the Id and CurrentId properties.
using System;
using System.Threading;
using System.Threading.Tasks;


class DemoTask
{
    // A method to be run as a task.
    static void MyTask()
    {
        Console.WriteLine("MyTask() #" + Task.CurrentId + " starting");

        for(int count = 0; count < 10; count++)
        {
            Thread.Sleep(500);
            Console.WriteLine("In MyTask() #" + Task.CurrentId +
                              ", count is " + count );
        }

        Console.WriteLine("MyTask #" + Task.CurrentId + " terminating");
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Construct two tasks.
        Task tsk = new Task(MyTask);
        Task tsk2 = new Task(MyTask);

        // Run the tasks.
        tsk.Start();
        tsk2.Start();
        Console.WriteLine("Task ID for tsk is " + tsk.Id);
        Console.WriteLine("Task ID for tsk2 is " + tsk2.Id);

        // Keep Main() alive until the other tasks finish.
        for(int i = 0; i < 60; i++)
        {
            Console.Write(".");
            Thread.Sleep(100);
        }
        Console.WriteLine("Main thread ending.");
    }
}
