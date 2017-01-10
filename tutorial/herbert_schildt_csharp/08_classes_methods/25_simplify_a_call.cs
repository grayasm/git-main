// Use an optional argument to simplify a call to a method.

using System;


class UseOptArgs
{
    // Display part or all of string.
    static void Display(string str, int start = 0, int stop = -1)
    {
        if(stop < 0)
        stop = str.Length;

        // Check for out-of-range condition.
        if(stop > str.Length | start > stop | start < 0)
            return;

        for(int i=start; i < stop; i++)
            Console.Write(str[i]);

        Console.WriteLine();
    }


    static void Main()
    {
        Display("this is a test");
        Display("this is a test", 10);
        Display("this is a test", 5, 12);
    }
}
