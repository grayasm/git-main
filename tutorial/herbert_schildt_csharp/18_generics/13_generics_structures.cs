/*
    Generic Structures
    C# allows you to create generic structures. The syntax is the same
    as for generic classes. For example, in the following program, the
    XY structure, which stores X, Y coordinates, is generic:
*/

// Demonstrate a generic struct.
using System;


// This structure is generic.
struct XY<T>
{
    T x;
    T y;

    public XY(T a, T b)
    {
        x = a;
        y = b;
    }

    public T X
    {
        get { return x; }
        set { x = value; }
    }

    public T Y
    {
        get { return y; }
        set { y = value; }
    }
}


class StructTest
{
    static void Main()
    {
        XY<int> xy = new XY<int>(10, 20);
        XY<double> xy2 = new XY<double>(88.0, 99.0);

        Console.WriteLine(xy.X + ", " + xy.Y);
        Console.WriteLine(xy2.X + ", " + xy2.Y);
    }
}
