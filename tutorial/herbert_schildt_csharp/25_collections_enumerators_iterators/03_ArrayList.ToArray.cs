// Convert an ArrayList into an array.
using System;
using System.Collections;


class ArrayListToArray
{
    static void Main()
    {
        ArrayList al = new ArrayList();

        // Add elements to the array list.
        al.Add(1);
        al.Add(2);
        al.Add(3);
        al.Add(4);
        Console.Write("Contents: ");

        foreach(int i in al)
            Console.Write(i + " ");
        Console.WriteLine();

        // Get the array.
        int[] ia = (int[]) al.ToArray(typeof(int));
        int sum = 0;

        // Sum the array.
        for(int i=0; i<ia.Length; i++)
            sum += ia[i];

        Console.WriteLine("Sum is: " + sum);
    }
}
