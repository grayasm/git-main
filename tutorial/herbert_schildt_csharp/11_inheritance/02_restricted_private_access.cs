/*
    Member Access and Inheritance
    Members of a class are often declared private to prevent their unauthorized
    use or tampering. Inheriting a class does not overrule the private access
    restriction. Thus, even though a derived class includes all of the members
    of its base class, it cannot access those members of the base class that
    are private.
*/

// Access to private members is not inherited.

// This example will not compile.

using System;


// A class for two-dimensional objects.
class TwoDShape
{
    double Width;    // now private
    double Height;   // now private

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
        return Width * Height / 2; // Error, can't access private member
    }

    // Display a triangle's style.
    public void ShowStyle()
    {
        Console.WriteLine("Triangle is " + Style);
    }
}
