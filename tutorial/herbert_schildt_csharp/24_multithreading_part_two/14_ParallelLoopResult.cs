// Use ParallelLoopResult, ParallelLoopState, and Break()
// with a parallel ForEach() loop.
using System;
using System.Threading.Tasks;


class DemoParallelForWithLoopResult
{
    static int[] data;

    // A method to be run as the body of a parallel loop.
    // In this version, notice that the value of an element of
    // of data is passed to v, not an index.

    static void DisplayData(int v, ParallelLoopState pls)
    {
        // Break out of loop if a negative value is found.
        if(v < 0)
            pls.Break();

        Console.WriteLine("Value: " + v);
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");

        data = new int[100000000];

        // Initialize data.
        for(int i=0; i < data.Length; i++)
            data[i] = i;

        // Put a negative value into data.
        data[100000] = -10;

        // Use a parallel ForEach() loop to display the data.
        ParallelLoopResult loopResult = Parallel.ForEach(data, DisplayData);

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
