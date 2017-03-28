// Demonstrate the Queue class.
using System;
using System.Collections;


class QueueDemo
{
    static void ShowEnq(Queue q, int a)
    {
        q.Enqueue(a);

        Console.WriteLine("Enqueue(" + a + ")");
        Console.Write("queue: ");

        foreach(int i in q)
            Console.Write(i + " ");
        Console.WriteLine();
    }


    static void ShowDeq(Queue q)
    {
        Console.Write("Dequeue -> ");
        int a = (int) q.Dequeue();

        Console.WriteLine(a);
        Console.Write("queue: ");

        foreach(int i in q)
            Console.Write(i + " ");
        Console.WriteLine();
    }


    static void Main()
    {
        Queue q = new Queue();

        foreach(int i in q)
            Console.Write(i + " ");

        Console.WriteLine();

        ShowEnq(q, 22);
        ShowEnq(q, 65);
        ShowEnq(q, 91);
        ShowDeq(q);
        ShowDeq(q);
        ShowDeq(q);

        try
        {
            ShowDeq(q);
        }
        catch (InvalidOperationException)
        {
            Console.WriteLine("Queue empty.");
        }
    }
}
