// Demonstrate Concat().
using System;


class ConcatDemo
{
    static void Main()
    {
        string result = String.Concat("This ", "is ", "a ",
                                      "test ", "of ", "the ",
                                      "String ", "class.");

        Console.WriteLine("result: " + result);
    }
}
