/*
    In the language of C#, a class that is inherited is called a base class.
    The class that does the inheriting is called a derived class. Therefore, a
    derived class is a specialized version of a base class. It inherits all of
    the variables, methods, properties, and indexers defined by the base class
    and adds its own unique elements.
*/

// A simple class hierarchy.

using System;


// A class for two-dimensional objects.
class TwoDShape
{
    public double Width;
    public double Height;

    public void ShowDim()
    {
        Console.WriteLine("Width and height are " + Width + " and " + Height);
    }
}


// Triangle is derived from TwoDShape.
class Triangle : TwoDShape
{
    public string Style; // style of triangle

    // Return area of triangle.
    public double Area()
    {
        return Width * Height / 2;
    }

    // Display a triangle's style.
    public void ShowStyle()
    {
        Console.WriteLine("Triangle is " + Style);
    }
}


class Shapes
{
    static void Main()
    {
        Triangle t1 = new Triangle();
        Triangle t2 = new Triangle();

        t1.Width = 4.0;
        t1.Height = 4.0;
        t1.Style = "isosceles";
        t2.Width = 8.0;
        t2.Height = 12.0;
        t2.Style = "right";

        Console.WriteLine("Info for t1: ");
        t1.ShowStyle();
        t1.ShowDim();

        Console.WriteLine("Area is " + t1.Area());
        Console.WriteLine();
        Console.WriteLine("Info for t2: ");

        t2.ShowStyle();
        t2.ShowDim();
        Console.WriteLine("Area is " + t2.Area());
    }
}
