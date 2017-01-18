/*
    Using Abstract Classes
    An abstract method is created by specifying the abstract type modifier.
    An abstract method contains no body and is, therefore, not implemented by
    the base class. Thus, a derived class must override it—it cannot simply use
    the version defined in the base class.
    As you can probably guess, an abstract method is automatically virtual, and
    there is no need to use the virtual modifier. In fact, it is an error to use
    virtual and abstract together.

    To declare an abstract method, use this general form:

abstract type name(parameter-list);

    The abstract modifier can be used only on instance methods. It cannot be
    applied to static methods. Properties and indexers can also be abstract.
    A class that contains one or more abstract methods must also be declared as
    abstract by preceding its class declaration with the abstract specifier.
    Since an abstract class does not define a complete implementation, there
    can be no objects of an abstract class. Thus, attempting to create an object
    of an abstract class by using new will result in a compile-time error.

    When a derived class inherits an abstract class, it must implement all of
    the abstract methods in the base class. If it doesn’t, then the derived
    class must also be specified as abstract. Thus, the abstract attribute is
    inherited until such time as a complete implementation is achieved.
*/


// Create an abstract class.

using System;


abstract class TwoDShape
{
    double pri_width;
    double pri_height;

    // A default constructor.
    public TwoDShape()
    {
        Width = Height = 0.0;
        name = "null";
    }

    // Parameterized constructor.
    public TwoDShape(double w, double h, string n)
    {
        Width = w;
        Height = h;
        name = n;
    }

    // Construct object with equal width and height.
    public TwoDShape(double x, string n)
    {
        Width = Height = x;
        name = n;
    }

    // Construct a copy of a TwoDShape object.
    public TwoDShape(TwoDShape ob)
    {
        Width = ob.Width;
        Height = ob.Height;
        name = ob.name;
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

    public string name { get; set; }

    public void ShowDim()
    {
        Console.WriteLine("Width and height are " + Width + " and " + Height);
    }

    // Now, Area() is abstract.
    public abstract double Area();
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
    public Triangle(string s, double w, double h) : base(w, h, "triangle")
    {
        Style = s;
    }

    // Construct an isosceles triangle.
    public Triangle(double x) : base(x, "triangle")
    {
        Style = "isosceles";
    }

    // Construct a copy of a Triangle object.
    public Triangle(Triangle ob) : base(ob)
    {
        Style = ob.Style;
    }

    // Override Area() for Triangle.
    public override double Area()
    {
        return Width * Height / 2;
    }

    // Display a triangle's style.
    public void ShowStyle()
    {
        Console.WriteLine("Triangle is " + Style);
    }
}


// A derived class of TwoDShape for rectangles.
class Rectangle : TwoDShape
{
    // Constructor for Rectangle.
    public Rectangle(double w, double h) : base(w, h, "rectangle"){ }

    // Construct a square.
    public Rectangle(double x) : base(x, "rectangle") { }

    // Construct a copy of a Rectangle object.
    public Rectangle(Rectangle ob) : base(ob) { }

    // Return true if the rectangle is square.
    public bool IsSquare()
    {
        if(Width == Height) return true;
        return false;
    }

    // Override Area() for Rectangle.
    public override double Area()
    {
        return Width * Height;
    }
}


class AbsShape
{
    static void Main()
    {
        TwoDShape[] shapes = new TwoDShape[4];

        shapes[0] = new Triangle("right", 8.0, 12.0);
        shapes[1] = new Rectangle(10);
        shapes[2] = new Rectangle(10, 4);
        shapes[3] = new Triangle(7.0);

        for(int i=0; i < shapes.Length; i++)
        {
            Console.WriteLine("object is " + shapes[i].name);
            Console.WriteLine("Area is " + shapes[i].Area());
            Console.WriteLine();
        }
    }
}
