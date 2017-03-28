/*
    Partial Methods
    As the preceding section described, you can use partial to create
    a partial type. Beginning with C# 3.0, there is a second use of
    partial that lets you create a partial method within a partial type.
    A partial method has its declaration in one part and its implementation
    in another part. Thus, in a partial class or structure, partial can be
    used to allow the declaration of a method to be separate from its
    implementation.
    The key aspect of a partial method is that the implementation is not
    required! When the partial method is not implemented by another part
    of the class or structure, then all calls to the partial method are
    silently ignored. This makes it possible for a class to specify, but
    not require, optional functionality. If that functionality is not
    implemented, then it is simply ignored.
*/


// Demonstrate a partial method.
using System;


partial class XY
{
    public XY(int a, int b)
    {
        X = a;
        Y = b;
    }

    // Declare a partial method.
    partial void Show();
}

partial class XY
{
    public int X { get; set; }

    // Implement a partial method.
    partial void Show()
    {
        Console.WriteLine("{0}, {1}", X, Y);
    }
}

partial class XY
{
    public int Y { get; set; }

    // Call a partial method.
    public void ShowXY()
    {
        Show();
    }
}


class Test
{
    static void Main()
    {
        XY xy = new XY(1, 2);
        xy.ShowXY();
    }
}
