// Demonstrate method overloading.

using System;


class Overload
{
    public void OvlDemo()
    {
        Console.WriteLine("No parameters");
    }

    // Overload OvlDemo for one integer parameter.
    public void OvlDemo(int a)
    {
        Console.WriteLine("One parameter: " + a);
    }

    // Overload OvlDemo for two integer parameters.
    public int OvlDemo(int a, int b)
    {
        Console.WriteLine("Two parameters: " + a + " " + b);
        return a + b;
    }

    // Overload OvlDemo for two double parameters.
    public double OvlDemo(double a, double b)
    {
        Console.WriteLine("Two double parameters: " + a + " "+ b);
        return a + b;
    }
}


class OverloadDemo
{
    static void Main()
    {
        Overload ob = new Overload();
        int resI;
        double resD;

        // Call all versions of OvlDemo().
        ob.OvlDemo();
        Console.WriteLine();

        ob.OvlDemo(2);
        Console.WriteLine();

        resI = ob.OvlDemo(4, 6);
        Console.WriteLine("Result of ob.OvlDemo(4, 6): " + resI);
        Console.WriteLine();

        resD = ob.OvlDemo(1.1, 2.32);
        Console.WriteLine("Result of ob.OvlDemo(1.1, 2.32): " + resD);
    }
}
