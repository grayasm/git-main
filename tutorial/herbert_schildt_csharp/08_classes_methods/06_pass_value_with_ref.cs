// Use ref to pass a value type by reference.

using System;

class RefTest
{
    // This method changes its argument. Notice the use of ref.
    public void Sqr(ref int i)
    {
        i = i * i;
    }
}


class RefDemo
{
    static void Main()
    {
        RefTest ob = new RefTest();
        int a = 10;
        Console.WriteLine("a before call: " + a);
        ob.Sqr(ref a); // notice the use of ref
        Console.WriteLine("a after call: " + a);
    }
}
