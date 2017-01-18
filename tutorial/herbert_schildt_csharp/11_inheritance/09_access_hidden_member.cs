/*
    Using base to Access a Hidden Name
    There is a second form of base that acts somewhat like this, except that it
    always refers to the base class of the derived class in which it is used.
    This usage has the following general form:

base.member

    Here, member can be either a method or an instance variable. This form of
    base is most applicable to situations in which member names of a derived
    class hide members by the same name in the base class.
*/


// Using base to overcome name hiding.

using System;


class A
{
    public int i = 0;
}


// Create a derived class.
class B : A
{
    new int i; // this i hides the i in A

    public B(int a, int b)
    {
        base.i = a;    // this uncovers the i in A
        i = b;         // i in B
    }

    public void Show()
    {
        // This displays the i in A.
        Console.WriteLine("i in base class: " + base.i);

        // This displays the i in B.
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
