// A simple example of BlockingCollection.
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
    }


    // Consume 26 characters.
    static void Consumer()
    {
        for(int i=0; i < 26; i++)
            Console.WriteLine("Consuming " + bc.Take());
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
