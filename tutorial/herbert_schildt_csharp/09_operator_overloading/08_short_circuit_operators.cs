/* A better way to overload !, |, and & for ThreeD.
   This version automatically enables the && and || operators. */

using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates
    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload | for short-circuit evaluation.
    public static ThreeD operator |(ThreeD op1, ThreeD op2)
    {
        if( ((op1.x != 0) || (op1.y != 0) || (op1.z != 0)) |
            ((op2.x != 0) || (op2.y != 0) || (op2.z != 0)) )
            return new ThreeD(1, 1, 1);
        else
            return new ThreeD(0, 0, 0);
    }

    // Overload & for short-circuit evaluation.
    public static ThreeD operator &(ThreeD op1, ThreeD op2)
    {
        if( ((op1.x != 0) && (op1.y != 0) && (op1.z != 0)) &
            ((op2.x != 0) && (op2.y != 0) && (op2.z != 0)) )
            return new ThreeD(1, 1, 1);
        else
            return new ThreeD(0, 0, 0);
    }

    // Overload !.
    public static bool operator !(ThreeD op)
    {
        if(op) return false;
        else return true;
    }

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

    // Show X, Y, Z coordinates.
    public void Show()
    {
        Console.WriteLine(x + ", " + y + ", " + z);
    }
}

class LogicalOpDemo
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
        if(b) Console.WriteLine("b is true.");
        if(c) Console.WriteLine("c is true.");
        if(!a) Console.WriteLine("a is false.");
        if(!b) Console.WriteLine("b is false.");
        if(!c) Console.WriteLine("c is false.");

        Console.WriteLine();
        Console.WriteLine("Use & and |");

        if(a & b) Console.WriteLine("a & b is true.");
        else Console.WriteLine("a & b is false.");

        if(a & c) Console.WriteLine("a & c is true.");
        else Console.WriteLine("a & c is false.");

        if(a | b) Console.WriteLine("a | b is true.");
        else Console.WriteLine("a | b is false.");

        if(a | c) Console.WriteLine("a | c is true.");
        else Console.WriteLine("a | c is false.");
        Console.WriteLine();

        // Now use short-circuit ops.
        Console.WriteLine("Use short-circuit && and ||");

        if(a && b) Console.WriteLine("a && b is true.");
        else Console.WriteLine("a && b is false.");

        if(a && c) Console.WriteLine("a && c is true.");
        else Console.WriteLine("a && c is false.");

        if(a || b) Console.WriteLine("a || b is true.");
        else Console.WriteLine("a || b is false.");

        if(a || c) Console.WriteLine("a || c is true.");
        else Console.WriteLine("a || c is false.");
    }
}
