/*
    Generic Delegates

    Like methods, delegates can also be generic. To declare a generic
    delegate, use this general form:

delegate ret-type delegate-name<type-parameter-list>(arg-list);

*/

// A simple generic delegate.
using System;


// Declare a generic delegate.
delegate T SomeOp<T>(T v);


class GenDelegateDemo
{
    // Return the summation of the argument.
    static int Sum(int v)
    {
        int result = 0;
        for(int i=v; i>0; i--)
            result += i;
        return result;
    }

    // Return a string containing the reverse of the argument.
    static string Reflect(string str)
    {
        string result = "";
        foreach(char ch in str)
            result = ch + result;
        return result;
    }

    static void Main()
    {
        // Construct an int delegate.
        SomeOp<int> intDel = Sum;
        Console.WriteLine(intDel(3));

        // Construct a string delegate.
        SomeOp<string> strDel = Reflect;
        Console.WriteLine(strDel("Hello"));
    }
}
