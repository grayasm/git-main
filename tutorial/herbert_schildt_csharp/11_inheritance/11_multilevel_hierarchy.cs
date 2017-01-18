/*
    Creating a Multilevel Hierarchy
    Up to this point, we have been using simple class hierarchies consisting of
    only a base class and a derived class. However, you can build hierarchies
    that contain as many layers of inheritance as you like. As mentioned, it is
    perfectly acceptable to use a derived class as a base class of another.
*/

// A multilevel hierarchy.

using System;


class TwoDShape
{
    double pri_width;
    double pri_height;

    // Default constructor.
    public TwoDShape()
    {
        Width = Height = 0.0;
    }

    // Constructor for TwoDShape.
    public TwoDShape(double w, double h)
    {
        Width = w;
        Height = h;
    }

    // Construct object with equal width and height.
    public TwoDShape(double x)
    {
        Width = Height = x;
    }

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
    string Style; // private

    /* A default constructor. This invokes the default
       constructor of TwoDShape. */
    public Triangle()
    {
        Style = "null";
    }

    // Constructor.
    public Triangle(string s, double w, double h) : base(w, h)
    {
        Style = s;
    }

    // Construct an isosceles triangle.
    public Triangle(double x) : base(x)
    {
        Style = "isosceles";
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


// Extend Triangle.
class ColorTriangle : Triangle
{
    string color;

    public ColorTriangle(string c, string s, double w, double h) : base(s, w, h)
    {
        color = c;
    }

    // Display the color.
    public void ShowColor()
    {
        Console.WriteLine("Color is " + color);
    }
}


class Shapes6
{
    static void Main()
    {
        ColorTriangle t1 = new ColorTriangle("Blue", "right", 8.0, 12.0);
        ColorTriangle t2 = new ColorTriangle("Red", "isosceles", 2.0, 2.0);

        Console.WriteLine("Info for t1: ");
        t1.ShowStyle();
        t1.ShowDim();
        t1.ShowColor();

        Console.WriteLine("Area is " + t1.Area());
        Console.WriteLine();

        Console.WriteLine("Info for t2: ");
        t2.ShowStyle();
        t2.ShowDim();
        t2.ShowColor();

        Console.WriteLine("Area is " + t2.Area());
    }
}
