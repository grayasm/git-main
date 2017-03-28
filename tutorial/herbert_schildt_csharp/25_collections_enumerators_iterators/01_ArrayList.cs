// Demonstrate ArrayList.
using System;
using System.Collections;


class ArrayListDemo
{
    static void Main()
    {
        // Create an array list.
        ArrayList al = new ArrayList();
        Console.WriteLine("Initial number of elements: " + al.Count);
        Console.WriteLine();
        Console.WriteLine("Adding 6 elements");

        // Add elements to the array list
        al.Add('C');
        al.Add('A');
        al.Add('E');
        al.Add('B');
        al.Add('D');
        al.Add('F');
        Console.WriteLine("Number of elements: " + al.Count);

        // Display the array list using array indexing.
        Console.Write("Current contents: ");
        for(int i=0; i < al.Count; i++)
            Console.Write(al[i] + " ");

        Console.WriteLine("\n");
        Console.WriteLine("Removing 2 elements");

        // Remove elements from the array list.
        al.Remove('F');
        al.Remove('A');

        Console.WriteLine("Number of elements: " + al.Count);


        // Use foreach loop to display the list.
        Console.Write("Contents: ");
        foreach(char c in al)
            Console.Write(c + " ");
        Console.WriteLine("\n");
        Console.WriteLine("Adding 20 more elements");

        // Add enough elements to force al to grow.
        for(int i=0; i < 20; i++)
            al.Add((char)('a' + i));

        Console.WriteLine("Current capacity: " + al.Capacity);
        Console.WriteLine("Number of elements after adding 20: " + al.Count);
        Console.Write("Contents: ");

        foreach(char c in al)
            Console.Write(c + " ");
        Console.WriteLine("\n");

        // Change contents using array indexing.
        Console.WriteLine("Change first three elements");

        al[0] = 'X';
        al[1] = 'Y';
        al[2] = 'Z';

        Console.Write("Contents: ");
        foreach(char c in al)
            Console.Write(c + " ");

        Console.WriteLine();
    }
}
