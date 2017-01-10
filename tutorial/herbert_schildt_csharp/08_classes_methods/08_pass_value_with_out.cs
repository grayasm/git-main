// Use out.

using System;


class Decompose
{
    /* Decompose a floating-point value into its
       integer and fractional parts. */
    public int GetParts(double n, out double frac)
    {
        int whole;
        whole = (int) n;
        frac = n - whole; // pass fractional part back through frac
        return whole; // return integer portion
    }
}


class UseOut
{
    static void Main()
    {
        Decompose ob = new Decompose();
        int i;
        double f;
        i = ob.GetParts(10.125, out f);
        Console.WriteLine("Integer portion is " + i);
        Console.WriteLine("Fractional part is " + f);
    }
}
