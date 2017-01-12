// Demonstrate an overloaded constructor.

using System;


class MyClass
{
    public int x;

    public MyClass()
    {
        Console.WriteLine("Inside MyClass().");
        x = 0;
    }

    public MyClass(int i)
    {
        Console.WriteLine("Inside MyClass(int).");
        x = i;
    }

    public MyClass(double d)
    {
        Console.WriteLine("Inside MyClass(double).");
        x = (int) d;
    }

    public MyClass(int i, int j)
    {
        Console.WriteLine("Inside MyClass(int, int).");
        x = i * j;
    }
}


class OverloadConsDemo
{
    static void Main()
    {
        MyClass t1 = new MyClass();
        MyClass t2 = new MyClass(88);
        MyClass t3 = new MyClass(17.23);
        MyClass t4 = new MyClass(2, 4);

        Console.WriteLine("t1.x: " + t1.x);
        Console.WriteLine("t2.x: " + t2.x);
        Console.WriteLine("t3.x: " + t3.x);
        Console.WriteLine("t4.x: " + t4.x);
    }
}
