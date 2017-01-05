// Find the radius of a circle given its area.

using System;

class Example
{
    static void FindRadius()
    {
        Double r;
        Double area;

        area = 10.0;
        r = Math.Sqrt(area / 3.1416);
        Console.WriteLine("Radius is " + r);
    }

    static void Trigonometry()
    {
        Double theta; // angle in radians
        for(theta = 0.1; theta <= 1.0; theta = theta + 0.1)
        {
            Console.WriteLine("Sine of " + theta + " is " +
                              Math.Sin(theta));

            Console.WriteLine("Cosine of " + theta + " is " +
                              Math.Cos(theta));

            Console.WriteLine("Tangent of " + theta + " is " +
                              Math.Tan(theta));

            Console.WriteLine();
        }
    }

    static void Main()
    {
        FindRadius();
        Trigonometry();
    }
}