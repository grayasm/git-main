// Demonstrate using statement.
using System;
using System.IO;


class UsingDemo
{
    static void Main()
    {
        try
        {
            StreamReader sr = new StreamReader("test.txt");

            // Use object inside using statement.
            using(sr)
            {
                // ...
            }
        }
        catch(IOException exc)
        {
            // ...
        }


        try
        {
            // Create a StreamReader inside the using statement.
            using(StreamReader sr2 = new StreamReader("test.txt"))
            {
                // ...
            }
        }
        catch(IOException exc)
        {
            // ...
        }
    }
}
