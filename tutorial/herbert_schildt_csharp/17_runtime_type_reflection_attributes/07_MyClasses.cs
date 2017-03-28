// A file that contains three classes. Call this file MyClasses.cs.

using System;


class MyClass
{
    int x;
    int y;

    public MyClass(int i)
    {
        Console.WriteLine("Constructing MyClass(int). ");
        x = y = i;
        Show();
    }
    public MyClass(int i, int j)
    {
        Console.WriteLine("Constructing MyClass(int, int). ");
        x = i;
        y = j;
        Show();
    }
    public int Sum()
    {
        return x+y;
    }
    public bool IsBetween(int i)
    {
        if((x < i) && (i < y)) return true;
        else return false;
    }
    public void Set(int a, int b)
    {
        Console.Write("Inside Set(int, int). ");
        x = a;
        y = b;
        Show();
    }

    // Overload Set.
    public void Set(double a, double b)
    {
        Console.Write("Inside Set(double, double). ");
        x = (int) a;
        y = (int) b;
        Show();
    }
    public void Show()
    {
        Console.WriteLine("Values are x: {0}, y: {1}", x, y);
    }
}


class AnotherClass
{
    string msg;

    public AnotherClass(string str)
    {
        msg = str;
    }

    public void Show()
    {
        Console.WriteLine(msg);
    }
}


class Demo
{
    static void Main()
    {
        Console.WriteLine("This is a placeholder.");
    }
}
