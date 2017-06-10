// Demonstrate LinkedList<T>.
using System;
using System.Collections.Generic;


class GenLinkedListDemo
{
    static void Main()
    {
        // Create a linked list.
        LinkedList<char> ll = new LinkedList<char>();

        Console.WriteLine("Initial number of elements: " + ll.Count);
        Console.WriteLine();
        Console.WriteLine("Adding 5 elements.");

        // Add elements to the linked list
        ll.AddFirst('A');
        ll.AddFirst('B');
        ll.AddFirst('C');
        ll.AddFirst('D');
        ll.AddFirst('E');

        Console.WriteLine("Number of elements: " + ll.Count);


        // Display the linked list by manually walking
        // through the list.
        LinkedListNode<char> node;
        Console.Write("Display contents by following links: ");
        for(node = ll.First; node != null; node = node.Next)
            Console.Write(node.Value + " ");
        Console.WriteLine("\n");


        //Display the linked list by use of a foreach loop.
        Console.Write("Display contents with foreach loop: ");
        foreach(char ch in ll)
            Console.Write(ch + " ");
        Console.WriteLine("\n");


        // Display the list backward by manually walking
        // from last to first.
        Console.Write("Follow links backwards: ");
        for(node = ll.Last; node != null; node = node.Previous)
            Console.Write(node.Value + " ");
        Console.WriteLine("\n");


        // Remove two elements.
        Console.WriteLine("Removing 2 elements.");

        // Remove elements from the linked list.
        ll.Remove('C');
        ll.Remove('A');
        Console.WriteLine("Number of elements: " + ll.Count);


        // Use foreach loop to display the modified list.
        Console.Write("Contents after deletion: ");
        foreach(char ch in ll)
            Console.Write(ch + " ");

        Console.WriteLine("\n");


        // Add three elements to the end of the list.
        ll.AddLast('X');
        ll.AddLast('Y');
        ll.AddLast('Z');

        Console.Write("Contents after addition to end: ");
        foreach(char ch in ll)
            Console.Write(ch + " ");

        Console.WriteLine("\n");
    }
}
