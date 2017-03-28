/*
    Calling Base Class Constructors
    A derived class can call a constructor defined in its base class by using
    an expanded form of the derived class' constructor declaration and the base
    keyword. The general form of this expanded declaration is shown here:

derived-constructor(parameter-list) : base(arg-list) {
 // body of constructor
}

    Here, arg-list specifies any arguments needed by the constructor in the
    base class. Notice the placement of the colon.
*/

// Add constructor to TwoDShape.

using System;


// A class for two-dimensional objects.
class TwoDShape
{
    double pri_width;
    double pri_height;

    // Constructor for TwoDShape.
    public TwoDShape(double w, double h)
    {
        Width = w;
        Height = h;
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

    // Call the base class constructor.
    public Triangle(string s, double w, double h) : base(w, h)
    {
        Style = s;
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


class Shapes4
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
