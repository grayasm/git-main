// Return a value from a task.
using System;
using System.Threading;
using System.Threading.Tasks;


class DemoTask
{
    // A trivial method that returns a result and takes no arguments.
    static bool MyTask()
    {
        return true;
    }

    // This method returns the summation of a positive integer
    // which is passed to it.
    static int SumIt(object v)
    {
        int x = (int) v;
        int sum = 0;
        for(; x > 0; x--)
            sum += x;
        return sum;
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Construct the first task.
        Task<bool> tsk = Task<bool>.Factory.StartNew(MyTask);
        Console.WriteLine("After running MyTask. The result is " + tsk.Result);

        // Construct the second task.
        Task<int> tsk2 = Task<int>.Factory.StartNew(SumIt, 3);
        Console.WriteLine("After running SumIt. The result is " + tsk2.Result);

        tsk.Dispose();
        tsk2.Dispose();

        Console.WriteLine("Main thread ending.");
    }
}
