/*
    Here is another, more interesting example of boxing. In this case,
    an int is passed as an argument to the Sqr( ) method, which uses an
    object parameter.
*/

// Boxing also occurs when passing values.

using System;


class BoxingDemo
{
    static void Main()
    {
        int x;
        x = 10;

        Console.WriteLine("Here is x: " + x);

        // x is automatically boxed when passed to Sqr().
        x = BoxingDemo.Sqr(x);

        Console.WriteLine("Here is x squared: " + x);
    }

    static int Sqr(object o)
    {
        return (int)o * (int)o;
    }
}
