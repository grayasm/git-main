// Public vs. private access.

using System;

class MyClass
{
    private int alpha;  // private access explicitly specified
    int beta;           // private access by default
    public int gamma;   // public access

    // Methods to access alpha and beta. It is OK for a member
    // of a class to access a private member of the same class.

    public void SetAlpha(int a)
    {
        alpha = a;
    }

    public int GetAlpha()
    {
        return alpha;
    }

    public void SetBeta(int a)
    {
        beta = a;
    }

    public int GetBeta()
    {
        return beta;
    }
}


class AccessDemo
{
    static void Main()
    {
        MyClass ob = new MyClass();

        // Access to alpha and beta is allowed only through methods.
        ob.SetAlpha(-99);
        ob.SetBeta(19);
        Console.WriteLine("ob.alpha is " + ob.GetAlpha());
        Console.WriteLine("ob.beta is " + ob.GetBeta());


        // You cannot access alpha or beta like this:
        ob.alpha = 10; // Wrong! alpha is private!
        ob.beta = 9;

        // Wrong! beta is private!
        //
        //
        // It is OK to directly access gamma because it is public.
        ob.gamma = 99;
    }
}
