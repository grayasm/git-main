/*
    Overloading Unary Operators
    The unary operators are overloaded just like the binary operators.
    The main difference, of course, is that there is only one operand.
*/

using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates

    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload binary +.
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

    // Overload binary -.
    public static ThreeD operator -(ThreeD op1, ThreeD op2)
    {
        ThreeD result = new ThreeD();

        /* Notice the order of the operands. op1 is the left
           operand and op2 is the right. */
        result.x = op1.x - op2.x;
        result.y = op1.y - op2.y;
        result.z = op1.z - op2.z;

        return result;
    }

    // Overload unary -.
    public static ThreeD operator -(ThreeD op)
    {
        ThreeD result = new ThreeD();
        result.x = -op.x;
        result.y = -op.y;
        result.z = -op.z;
        return result;
    }

    // Overload unary ++.
    public static ThreeD operator ++(ThreeD op)
    {
        ThreeD result = new ThreeD();

        // Return the incremented result.
        result.x = op.x + 1;
        result.y = op.y + 1;
        result.z = op.z + 1;
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

        c = a + b; // add a and b together
        Console.Write("Result of a + b: ");
        c.Show();
        Console.WriteLine();

        c = a + b + c; // add a, b, and c together
        Console.Write("Result of a + b + c: ");
        c.Show();
        Console.WriteLine();

        c = c - a; // subtract a
        Console.Write("Result of c - a: ");
        c.Show();
        Console.WriteLine();

        c = c - b; // subtract b
        Console.Write("Result of c - b: ");
        c.Show();
        Console.WriteLine();

        c = -a; // assign -a to c
        Console.Write("Result of -a: ");
        c.Show();
        Console.WriteLine();

        c = a++; // post-increment a
        Console.WriteLine("Given c = a++");
        Console.Write("c is ");
        c.Show();
        Console.Write("a is ");
        a.Show();


        // Reset a to 1, 2, 3
        a = new ThreeD(1, 2, 3);
        Console.Write("\nResetting a to ");
        a.Show();

        c = ++a; // pre-increment a
        Console.WriteLine("\nGiven c = ++a");
        Console.Write("c is ");
        c.Show();
        Console.Write("a is ");
        a.Show();
    }
}
