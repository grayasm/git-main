// Demonstrate ICloneable.
using System;


class X
{
    public int a;
    public X(int x) { a = x; }
}


class Test : ICloneable
{
    public X o;
    public int b;
    public Test(int x, int y)
    {
        o = new X(x);
        b = y;
    }
    public void Show(string name)
    {
        Console.Write(name + " values are ");
        Console.WriteLine("o.a: {0}, b: {1}", o.a, b);
    }

    // Make a deep copy of the invoking object.
    public object Clone()
    {
        Test temp = new Test(o.a, b);
        return temp;
    }
}


class CloneDemo
{
    static void Main()
    {
        Test ob1 = new Test(10, 20);
        ob1.Show("ob1");
        Console.WriteLine("Make ob2 a clone of ob1.");

        Test ob2 = (Test) ob1.Clone();
        ob2.Show("ob2");
        Console.WriteLine("Changing ob1.o.a to 99 and ob1.b to 88.");

        ob1.o.a = 99;
        ob1.b = 88;
        ob1.Show("ob1");
        ob2.Show("ob2");
    }
}
