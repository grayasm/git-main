// Use nullable objects in expressions.
using System;


class NullableDemo
{
    static void Main()
    {
        int? count = null;
        int? result = null;
        int incr = 10; // notice that incr is a non-nullable type

        // result contains null, because count is null.
        result = count + incr;

        if(result.HasValue)
            Console.WriteLine("result has this value: " + result.Value);
        else
            Console.WriteLine("result has no value");


        // Now, count is given a value and result will contain a value.
        count = 100;
        result = count + incr;

        if(result.HasValue)
            Console.WriteLine("result has this value: " + result.Value);
        else
            Console.WriteLine("result has no value");
    }
}
