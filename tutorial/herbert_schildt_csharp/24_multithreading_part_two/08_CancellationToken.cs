// A simple example of cancellation that uses polling.
using System;
using System.Threading;
using System.Threading.Tasks;


class DemoCancelTask
{
    // A method to be run as a task.
    static void MyTask(Object ct)
    {
        CancellationToken cancelTok = (CancellationToken) ct;

        // Check if cancelled prior to starting.
        cancelTok.ThrowIfCancellationRequested();
        Console.WriteLine("MyTask() starting");

        for(int count = 0; count < 10; count++)
        {
            // This example uses polling to watch for cancellation.
            if(cancelTok.IsCancellationRequested)
            {
                Console.WriteLine("Cancellation request received.");
                cancelTok.ThrowIfCancellationRequested();
            }

            Thread.Sleep(500);
            Console.WriteLine("In MyTask(), count is " + count );
        }

        Console.WriteLine("MyTask terminating");
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        // Create a cancellation token source.
        CancellationTokenSource cancelTokSrc = new CancellationTokenSource();

        // Start a task, passing the cancellation token to both
        // the delegate and the task.
        Task tsk = Task.Factory.StartNew(MyTask,
                                         cancelTokSrc.Token,
                                         cancelTokSrc.Token);

        // Let tsk run until cancelled.
        Thread.Sleep(2000);

        try
        {
            // Cancel the task.
            cancelTokSrc.Cancel();

            // Suspend Main() until tsk terminates.
            tsk.Wait();
        }
        catch (AggregateException exc)
        {
            if(tsk.IsCanceled)
                Console.WriteLine("\ntsk Cancelled\n");

            // To see the exception, un-comment this line:
            // Console.WriteLine(exc);
        }
        finally
        {
            tsk.Dispose();
            cancelTokSrc.Dispose();
        }

        Console.WriteLine("Main thread ending.");
    }
}
