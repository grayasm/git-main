// Overload < and >.
using System;


// A three-dimensional coordinate class.
class ThreeD
{
    int x, y, z; // 3-D coordinates
    public ThreeD() { x = y = z = 0; }
    public ThreeD(int i, int j, int k) { x = i; y = j; z = k; }

    // Overload <.
    public static bool operator <(ThreeD op1, ThreeD op2)
    {
        if (Math.Sqrt(op1.x * op1.x + op1.y * op1.y + op1.z * op1.z) <
            Math.Sqrt(op2.x * op2.x + op2.y * op2.y + op2.z * op2.z))
            return true;
        else
            return false;
    }

    // Overload >.
    public static bool operator >(ThreeD op1, ThreeD op2)
    {
        if (Math.Sqrt(op1.x * op1.x + op1.y * op1.y + op1.z * op1.z) >
            Math.Sqrt(op2.x * op2.x + op2.y * op2.y + op2.z * op2.z))
            return true;
        else
            return false;
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
        ThreeD a = new ThreeD(5, 6, 7);
        ThreeD b = new ThreeD(10, 10, 10);
        ThreeD c = new ThreeD(1, 2, 3);
        ThreeD d = new ThreeD(6, 7, 5);

        Console.Write("Here is a: ");
        a.Show();
        Console.Write("Here is b: ");
        b.Show();
        Console.Write("Here is c: ");
        c.Show();
        Console.Write("Here is d: ");
        d.Show();
        Console.WriteLine();

        if(a > c) Console.WriteLine("a > c is true");
        if(a < c) Console.WriteLine("a < c is true");
        if(a > b) Console.WriteLine("a > b is true");
        if(a < b) Console.WriteLine("a < b is true");
        if(a > d) Console.WriteLine("a > d is true");
        else if(a < d) Console.WriteLine("a < d is true");
        else Console.WriteLine("a and d are same distance from origin");
    }
}
