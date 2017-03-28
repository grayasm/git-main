// Use ParallelLoopResult, ParallelLoopState, and Break()
// with a parallel For loop.
using System;
using System.Threading.Tasks;


class DemoParallelForWithLoopResult
{
    static int[] data;

    // A method to be run as the body of a parallel loop.
    // The statements in this loop are designed to simply
    // consume some CPU time for the purposes of demonstration.

    static void MyTransform(int i, ParallelLoopState pls)
    {
        // Break out of loop if a negative value is found.
        if(data[i] < 0)
            pls.Break();

        data[i] = data[i] / 10;

        if(data[i] < 1000)                      data[i] = 0;
        if(data[i] > 1000 & data[i] < 2000)     data[i] = 100;
        if(data[i] > 2000 & data[i] < 3000)     data[i] = 200;
        if(data[i] > 3000)                      data[i] = 300;
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        data = new int[100000000];

        // Initialize data.
        for(int i=0; i < data.Length; i++)
            data[i] = i;

        // Put a negative value into data.
        data[1000] = -10;

        // Parallel transform loop.
        ParallelLoopResult loopResult = Parallel.For(0,
                                                     data.Length,
                                                     MyTransform);

        // See if the loop ran to completion.
        if(!loopResult.IsCompleted)
            Console.WriteLine("\nLoop Terminated early because a " +
                              "negative value was encountered\n" +
                              "in iteration number " +
                              loopResult.LowestBreakIteration +
                              ".\n");

        Console.WriteLine("Main thread ending.");
    }
}
