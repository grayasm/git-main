// Overload true and false for ThreeD.

using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates
    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload true.
    public static bool operator true(ThreeD op)
    {
        if((op.x != 0) || (op.y != 0) || (op.z != 0))
            return true; // at least one coordinate is non-zero
        else
            return false;
    }

    // Overload false.
    public static bool operator false(ThreeD op)
    {
        if((op.x == 0) && (op.y == 0) && (op.z == 0))
            return true; // all coordinates are zero
        else
            return false;
    }

    // Overload unary --.
    public static ThreeD operator --(ThreeD op)
    {
        ThreeD result = new ThreeD();
        // Return the decremented result.
        result.x = op.x - 1;
        result.y = op.y - 1;
        result.z = op.z - 1;
        return result;
    }

    // Show X, Y, Z coordinates.
    public void Show()
    {
        Console.WriteLine(x + ", " + y + ", " + z);
    }
}

class TrueFalseDemo
{
    static void Main()
    {
        ThreeD a = new ThreeD(5, 6, 7);
        ThreeD b = new ThreeD(10, 10, 10);
        ThreeD c = new ThreeD(0, 0, 0);
        Console.Write("Here is a: ");
        a.Show();
        Console.Write("Here is b: ");
        b.Show();
        Console.Write("Here is c: ");
        c.Show();
        Console.WriteLine();

        if(a) Console.WriteLine("a is true.");
        else Console.WriteLine("a is false.");
        if(b) Console.WriteLine("b is true.");
        else Console.WriteLine("b is false.");
        if(c) Console.WriteLine("c is true.");
        else Console.WriteLine("c is false.");

        Console.WriteLine();
        Console.WriteLine("Control a loop using a ThreeD object.");
        do
        {
            b.Show();
            b--;
        } while(b);
    }
}
