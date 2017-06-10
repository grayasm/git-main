// Demonstrate the Stack class.
using System;
using System.Collections;


class StackDemo
{
    static void ShowPush(Stack st, int a)
    {
        st.Push(a);

        Console.WriteLine("Push(" + a + ")");
        Console.Write("stack: ");

        foreach(int i in st)
            Console.Write(i + " ");
        Console.WriteLine();
    }


    static void ShowPop(Stack st)
    {
        Console.Write("Pop -> ");

        int a = (int) st.Pop();

        Console.WriteLine(a);
        Console.Write("stack: ");

        foreach(int i in st)
            Console.Write(i + " ");
        Console.WriteLine();
    }


    static void Main()
    {
        Stack st = new Stack();
        foreach(int i in st)
            Console.Write(i + " ");

        Console.WriteLine();

        ShowPush(st, 22);
        ShowPush(st, 65);
        ShowPush(st, 91);
        ShowPop(st);
        ShowPop(st);
        ShowPop(st);

        try
        {
            ShowPop(st);
        }
        catch (InvalidOperationException)
        {
            Console.WriteLine("Stack empty.");
        }
    }
}
