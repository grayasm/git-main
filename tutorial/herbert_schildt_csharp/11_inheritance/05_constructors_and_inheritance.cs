/*
    In a hierarchy, it is possible for both base classes and derived classes to
    have their own constructors. This raises an important question:
    What constructor is responsible for building an object of the derived class?
    The one in the base class, the one in the derived class, or both?
    Here is the answer: The constructor for the base class constructs the base
    class portion of the object, and the constructor for the derived class
    constructs the derived class part. This makes sense because the base class
    has no knowledge of or access to any element in a derived class.
    Thus, their construction must be separate.
*/

// Add a constructor to Triangle.

using System;


// A class for two-dimensional objects.
class TwoDShape
{
    double pri_width;
    double pri_height;

    // Properties for Width and Height.
    public double Width
    {
        get { return pri_width; }
        set { pri_width = value < 0 ? -value : value; }
    }

    public double Height
    {
        get { return pri_height; }
        set { pri_height = value < 0 ? -value : value; }
    }

    public void ShowDim()
    {
        Console.WriteLine("Width and height are " + Width + " and " + Height);
    }
}


// A derived class of TwoDShape for triangles.
class Triangle : TwoDShape
{
    string Style;

    // Constructor.
    public Triangle(string s, double w, double h)
    {
        Width = w; // init the base class
        Height = h; // init the base class
        Style = s; // init the derived class
    }

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


class Shapes3
{
    static void Main()
    {
        Triangle t1 = new Triangle("isosceles", 4.0, 4.0);
        Triangle t2 = new Triangle("right", 8.0, 12.0);

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
