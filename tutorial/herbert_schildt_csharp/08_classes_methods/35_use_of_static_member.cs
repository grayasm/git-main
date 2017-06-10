// Use a static field to count instances.

using System;


class CountInst
{
    static int count = 0;

    // Increment count when object is created.
    public CountInst()
    {
        count++;
    }

    // Decrement count when object is destroyed.
    ~CountInst()
    {
        count--;
    }

    public static int GetCount()
    {
        return count;
    }
}


class CountDemo
{
    static void Main()
    {
        CountInst ob;
        for(int i=0; i < 10; i++)
        {
            ob = new CountInst();
            Console.WriteLine("Current count: " + CountInst.GetCount());
        }
    }
}
