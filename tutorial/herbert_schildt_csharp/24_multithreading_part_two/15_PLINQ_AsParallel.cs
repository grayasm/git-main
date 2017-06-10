// A Simple PLINQ Query.
using System;
using System.Linq;


class PLINQDemo
{
    static void Main()
    {
        int[] data = new int[10000000];

        // Initialize the data to positive values.
        for(int i=0; i < data.Length; i++)
            data[i] = i;

        // Now, insert some negative values.
        data[1000] = -1;
        data[14000] = -2;
        data[15000] = -3;
        data[676000] = -4;
        data[8024540] = -5;
        data[9908000] = -6;


        // Use a PLINQ query to find the negative values.
        var negatives = from val in data.AsParallel()
                        where val < 0
                        select val;

        foreach(var v in negatives)
            Console.Write(v + " ");

        Console.WriteLine();
    }
}
