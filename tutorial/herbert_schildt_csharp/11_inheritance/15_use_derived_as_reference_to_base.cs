/*
    Although the preceding discussion may seem a bit esoteric, it has some
    important practical applications. One is described here. The other is
    discussed later in this chapter, when virtual methods are covered.

    An important place where derived class references are assigned to base class
    variables is when constructors are called in a class hierarchy. As you know,
    it is common for a class to define a constructor that takes an object of its
    class as a parameter. This allows the class to construct a copy of an
    object. Classes derived from such a class can take advantage of this
    feature.
*/

// Pass a derived class reference to a base class reference.

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

    // Construct a copy of a TwoDShape object.
    public TwoDShape(TwoDShape ob)
    {
        Width = ob.Width;
        Height = ob.Height;
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
    string Style;

    // A default constructor.
    public Triangle()
    {
        Style = "null";
    }

    // Constructor for Triangle.
    public Triangle(string s, double w, double h) : base(w, h)
    {
        Style = s;
    }

    // Construct an isosceles triangle.
    public Triangle(double x) : base(x)\
    {
        Style = "isosceles";
    }

    // Construct a copy of a Triangle object.
    public Triangle(Triangle ob) : base(ob)
    {
        Style = ob.Style;
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


class Shapes7
{
    static void Main()
    {
        Triangle t1 = new Triangle("right", 8.0, 12.0);

        // Make a copy of t1.
        Triangle t2 = new Triangle(t1);
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
