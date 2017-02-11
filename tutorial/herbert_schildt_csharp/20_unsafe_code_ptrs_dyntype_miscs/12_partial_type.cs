/*
    Partial Types
    Beginning with C# 2.0, a class, structure, or interface definition
    can be broken into two or more pieces, with each piece residing in
    a separate file. This is accomplished through the use of the partial
    contextual keyword. When your program is compiled, the pieces are
    united. When used to create a partial type, the partial modifier has
    this general form:

partial type typename { // ...

*/

// Demonstrate partial class definitions.
using System;

// Here is an example that divides a simple XY coordinate class into
// three separate files.
// The first file is shown here:

partial class XY
{
    public XY(int a, int b)
    {
        X = a;
        Y = b;
    }
}

// The second file is shown next:
partial class XY
{
    public int X { get; set; }
}

// The third file is
partial class XY
{
    public int Y { get; set; }
}


class Test
{
    static void Main()
    {
        XY xy = new XY(1, 2);

        Console.WriteLine(xy.X + "," + xy.Y);
    }
}
