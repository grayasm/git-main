/*
    For any given class and operator, an operator method can, itself, be
    overloaded. One of the most common reasons for this is to allow operations
    between a class type and other types of data, such as a built-in type.
*/

// Overload addition for ThreeD + ThreeD, and for ThreeD + int.
using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates
    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload binary + for ThreeD + ThreeD.
    public static ThreeD operator +(ThreeD op1, ThreeD op2)
    {
        ThreeD result = new ThreeD();
        /* This adds together the coordinates of the two points
           and returns the result. */
        result.x = op1.x + op2.x;
        result.y = op1.y + op2.y;
        result.z = op1.z + op2.z;
        return result;
    }

    // Overload binary + for object + int.
    public static ThreeD operator +(ThreeD op1, int op2)
    {
        ThreeD result = new ThreeD();
        result.x = op1.x + op2;
        result.y = op1.y + op2;
        result.z = op1.z + op2;
        return result;
    }

    // Overload binary + for int + ThreeD.
    public static ThreeD operator +(int op1, ThreeD op2)
    {
        ThreeD result = new ThreeD();
        result.x = op2.x + op1;
        result.y = op2.y + op1;
        result.z = op2.z + op1;
        return result;
    }

    // Show X, Y, Z coordinates.
    public void Show()
    {
        Console.WriteLine(x + ", " + y + ", " + z);
    }
}


class ThreeDDemo
{
    static void Main()
    {
        ThreeD a = new ThreeD(1, 2, 3);
        ThreeD b = new ThreeD(10, 10, 10);
        ThreeD c = new ThreeD();

        Console.Write("Here is a: ");
        a.Show();
        Console.WriteLine();
        Console.Write("Here is b: ");
        b.Show();
        Console.WriteLine();

        c = a + b; // ThreeD + ThreeD
        Console.Write("Result of a + b: ");
        c.Show();
        Console.WriteLine();

        c = b + 10; // ThreeD + int
        Console.Write("Result of b + 10: ");
        c.Show();

        c = 15 + b; // int + ThreeD
        Console.Write("Result of 15 + b: ");
        c.Show();
    }
}
