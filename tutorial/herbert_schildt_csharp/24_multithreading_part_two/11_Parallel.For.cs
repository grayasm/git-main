// Use Parallel.For() to create a data-parallel loop.
using System;
using System.Threading.Tasks;


class DemoParallelFor
{
    static int[] data;

    // A method to be run as the body of a parallel loop.
    // The statements in this loop are designed to simply
    // consume some CPU time for the purposes of demonstration.

    static void MyTransform(int i)
    {
        data[i] = data[i] / 10;

        if(data[i] < 10000)                     data[i] = 0;
        if(data[i] > 10000 & data[i] < 20000)   data[i] = 100;
        if(data[i] > 20000 & data[i] < 30000)   data[i] = 200;
        if(data[i] > 30000)                     data[i] = 300;
    }


    static void Main()
    {
        Console.WriteLine("Main thread starting.");
        data = new int[100000000];

        // Initialize the data using a regular for loop.
        for(int i=0; i < data.Length; i++)
            data[i] = i;

        // A parallel For loop.
        Parallel.For(0, data.Length, MyTransform);
        Console.WriteLine("Main thread ending.");
    }
}
