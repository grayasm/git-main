// Use a static class factory.

using System;


class MyClass
{
    int a, b;

    // Create a class factory for MyClass.
    static public MyClass Factory(int i, int j)
    {
        MyClass t = new MyClass();
        t.a = i;
        t.b = j;
        return t; // return an object
    }

    public void Show()
    {
        Console.WriteLine("a and b: " + a + " " + b);
    }
}


class MakeObjects
{
    static void Main()
    {
        int i, j;

        // Generate objects using the factory.
        for(i=0, j=10; i < 10; i++, j--)
        {
            MyClass ob = MyClass.Factory(i, j); // get an object
            ob.Show();
        }

        Console.WriteLine();
    }
}
