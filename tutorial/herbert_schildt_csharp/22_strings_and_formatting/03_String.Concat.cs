// Demonstrate the object form of Concat().
using System;


class MyClass
{
    public static int Count = 0;
    public MyClass() { Count++; }
}


class ConcatDemo
{
    static void Main()
    {
        string result = String.Concat("The value is " + 19);
        Console.WriteLine("result: " + result);

        result = String.Concat("hello ", 88, " ", 20.0, " ",
                               false, " ", 23.45M);
        Console.WriteLine("result: " + result);

        MyClass mc = new MyClass();
        result = String.Concat(mc, " current count is ", MyClass.Count);
        Console.WriteLine("result: " + result);
    }
}
