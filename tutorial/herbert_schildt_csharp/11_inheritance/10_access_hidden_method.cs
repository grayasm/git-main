/*
    Hidden methods can also be called through the use of base.
*/

// Call a hidden method.

using System;


class A
{
    public int i = 0;

    // Show() in A
    public void Show()
    {
        Console.WriteLine("i in base class: " + i);
    }
}

// Create a derived class.
class B : A
{
    new int i;    // this i hides the i in A

    public B(int a, int b)
    {
        base.i = a;    // this uncovers the i in A
        i = b;         // i in B
    }

    // This hides Show() in A. Notice the use of new.
    new public void Show()
    {
        base.Show();   // this calls Show() in A

        // this displays the i in B
        Console.WriteLine("i in derived class: " + i);
    }
}

class UncoverName
{
    static void Main()
    {
        B ob = new B(1, 2);
        ob.Show();
    }
}
