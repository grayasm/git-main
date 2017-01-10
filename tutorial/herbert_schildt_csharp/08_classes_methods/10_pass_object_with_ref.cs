// Swap two references.

using System;


class RefSwap
{
    int a, b;
    public RefSwap(int i, int j)
    {
        a = i;
        b = j;
    }

    public void Show()
    {
        Console.WriteLine("a: {0}, b: {1}", a, b);
    }

    // This method changes its arguments.
    public void Swap(ref RefSwap ob1, ref RefSwap ob2)
    {
        RefSwap t;
        t = ob1;
        ob1 = ob2;
        ob2 = t;
    }
}


class RefSwapDemo
{
    static void Main()
    {
        RefSwap x = new RefSwap(1, 2);
        RefSwap y = new RefSwap(3, 4);
        Console.Write("x before call: ");
        x.Show();
        Console.Write("y before call: ");
        y.Show();
        Console.WriteLine();

        // Exchange the objects to which x and y refer.
        x.Swap(ref x, ref y);

        Console.Write("x after call: ");
        x.Show();
        Console.Write("y after call: ");
        y.Show();
    }
}
