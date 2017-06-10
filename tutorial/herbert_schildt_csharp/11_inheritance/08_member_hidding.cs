/*
    Inheritance and Name Hiding
    It is possible for a derived class to define a member that has the same name
    as a member in its base class. When this happens, the member in the base
    class is hidden within the derived class. While this is not technically an
    error in C#, the compiler will issue a warning message. This warning alerts
    you to the fact that a name is being hidden. If your intent is to hide a
    base class member, then to prevent this warning, the derived class member
    must be preceded by the new keyword. Understand that this use of new is
    separate and distinct from its use when creating an object instance.
*/

// An example of inheritance-related name hiding.

using System;


class A
{
    public int i = 0;
}


// Create a derived class.
class B : A
{
    new int i;    // this i hides the i in A

    public B(int b)
    {
        i = b; // i in B
    }

    public void Show()
    {
        Console.WriteLine("i in derived class: " + i);
    }
}


class NameHiding
{
    static void Main()
    {
        B ob = new B(2);
        ob.Show();
    }
}
