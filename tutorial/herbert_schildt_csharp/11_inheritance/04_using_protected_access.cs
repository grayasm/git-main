/*
    A protected member is created by using the protected access modifier.
    When a member of a class is declared as protected, that member is, with one
    important exception, private. The exception occurs when a protected member
    is inherited. In this case, a protected member of the base class becomes a
    protected member of the derived class and is, therefore, accessible to the
    derived class.
*/


// Demonstrate protected.

using System;


class B
{
    protected int i, j; // private to B, but accessible by D
    public void Set(int a, int b)
    {
        i = a;
        j = b;
    }

    public void Show()
    {
        Console.WriteLine(i + " " + j);
    }
}


class D : B
{
    int k; // private

    // D can access B's i and j
    public void Setk()
    {
        k = i * j;
    }

    public void Showk()
    {
        Console.WriteLine(k);
    }
}


class ProtectedDemo
{
    static void Main()
    {
        D ob = new D();

        ob.Set(2, 3); // OK, known to D
        ob.Show(); // OK, known to D
        ob.Setk(); // OK, part of D
        ob.Showk(); // OK, part of D
    }
}
