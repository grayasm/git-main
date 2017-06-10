// Use a static constructor.

using System;


class Cons
{
    public static int alpha;
    public int beta;

    // A static constructor.
    static Cons()
    {
        alpha = 99;
        Console.WriteLine("Inside static constructor.");
    }

    // An instance constructor.
    public Cons()
    {
        beta = 100;
        Console.WriteLine("Inside instance constructor.");
    }
}


class ConsDemo
{
    static void Main()
    {
        Cons ob = new Cons();
        Console.WriteLine("Cons.alpha: " + Cons.alpha);
        Console.WriteLine("ob.beta: " + ob.beta);
    }
}
