// Compute the area of a circle.

using System;

class Circle
{
    static void Main()
    {
        double radius;
        double area;

        radius = 10.0;
        area = radius * radius * 3.1416;

        Console.WriteLine("Area is " + area);
    }
}