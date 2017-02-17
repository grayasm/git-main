// Using CompleteAdding(), IsCompleted, and TryTake().
using System;
using System.Threading.Tasks;
using System.Threading;
using System.Collections.Concurrent;


class BlockingDemo
{
    static BlockingCollection<char> bc;

    // Produce the characters A to Z.
    static void Producer()
    {
        for(char ch = 'A'; ch <= 'Z'; ch++)
        {
            bc.Add(ch);
            Console.WriteLine("Producing " + ch);
        }

        bc.CompleteAdding();
    }


    // Consume characters until producer is done.
    static void Consumer()
    {
        char ch;
        while(!bc.IsCompleted)
        {
            if(bc.TryTake(out ch))
                Console.WriteLine("Consuming " + ch);
        }
    }


    static void Main()
    {
        // Use a blocking collection that has a bound of 4.
        bc = new BlockingCollection<char>(4);


        // Create the producer and consumer tasks.
        Task Prod = new Task(Producer);
        Task Con = new Task(Consumer);

        // Start the tasks.
        Con.Start();
        Prod.Start();

        // Wait for both to finish.
        try
        {
            Task.WaitAll(Con, Prod);
        }
        catch(AggregateException exc)
        {
            Console.WriteLine(exc);
        }
        finally
        {
            Con.Dispose();
            Prod.Dispose();
            bc.Dispose();
        }
    }
}
