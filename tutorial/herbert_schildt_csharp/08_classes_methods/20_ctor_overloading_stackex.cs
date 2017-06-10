// A stack class for characters.

using System;


class Stack
{
    // These members are private.
    char[] stck;    // holds the stack
    int tos;        // index of the top of the stack

    // Construct an empty Stack given its size.
    public Stack(int size)
    {
        stck = new char[size]; // allocate memory for stack
        tos = 0;
    }

    // Construct a Stack from a stack.
    public Stack(Stack ob)
    {
        // Allocate memory for stack.
        stck = new char[ob.stck.Length];
        // Copy elements to new stack.
        for(int i=0; i < ob.tos; i++)
            stck[i] = ob.stck[i];

        // Set tos for new stack.
        tos = ob.tos;
    }

    // Push characters onto the stack.
    public void Push(char ch)
    {
        if(tos==stck.Length)
        {
            Console.WriteLine(" -- Stack is full.");
            return;
        }

        stck[tos] = ch;
        tos++;
    }

    // Pop a character from the stack.
    public char Pop()
    {
        if(tos==0)
        {
            Console.WriteLine(" -- Stack is empty.");
            return (char) 0;
        }
        tos--;
        return stck[tos];
    }

    // Return true if the stack is full.
    public bool IsFull()
    {
        return tos==stck.Length;
    }

    // Return true if the stack is empty.
    public bool IsEmpty()
    {
        return tos==0;
    }

    // Return total capacity of the stack.
    public int Capacity()
    {
        return stck.Length;
    }

    // Return number of objects currently on the stack.
    public int GetNum()
    {
        return tos;
    }
}


// Demonstrate the Stack class.
class StackDemo
{
    static void Main()
    {
        Stack stk1 = new Stack(10);
        char ch;
        int i;

        // Put some characters into stk1.
        Console.WriteLine("Push A through J onto stk1.");
        for(i=0; !stk1.IsFull(); i++)
            stk1.Push((char) ('A' + i));

        // Create a copy of stck1.
        Stack stk2 = new Stack(stk1);

        // Display the contents of stk1.
        Console.Write("Contents of stk1: ");
        while( !stk1.IsEmpty() )
        {
            ch = stk1.Pop();
            Console.Write(ch);
        }

        Console.WriteLine();
        Console.Write("Contents of stk2: ");
        while ( !stk2.IsEmpty() )
        {
            ch = stk2.Pop();
            Console.Write(ch);
        }

        Console.WriteLine("\n");
    }
}
