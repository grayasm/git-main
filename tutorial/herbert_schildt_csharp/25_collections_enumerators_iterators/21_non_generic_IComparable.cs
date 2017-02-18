/*
    Implementing IComparable for Non-Generic Collections
    If you want to sort objects that are stored in a non-generic
    collection, then you will implement the non-generic version of
    IComparable. This version defines only one method, CompareTo( ),
    which determines how comparisons are performed.
    The general form of CompareTo( ) is shown here:

int CompareTo(object obj)

    It compares the invoking object with other. To sort in ascending order
    return zero for equal, a positive value if the invoking object is greater
    than other and a negative value if smaller.
*/

// Implement IComparable.
using System;
using System.Collections;


// Implement the non-generic IComparable interface.
class Inventory : IComparable
{
    string name;
    double cost;
    int onhand;

    public Inventory(string n, double c, int h)
    {
        name = n;
        cost = c;
        onhand = h;
    }

    public override string ToString()
    {
        return String.Format("{0,-10}Cost: {1,6:C} On hand: {2}",
                             name,
                             cost,
                             onhand);
    }


    // Implement the IComparable interface.
    public int CompareTo(object obj)
    {
        Inventory b;
        b = (Inventory) obj;
        return string.Compare(name, b.name, StringComparison.Ordinal);
    }
}


class IComparableDemo
{
    static void Main()
    {
        ArrayList inv = new ArrayList();

        // Add elements to the list
        inv.Add(new Inventory("Pliers", 5.95, 3));
        inv.Add(new Inventory("Wrenches", 8.29, 2));
        inv.Add(new Inventory("Hammers", 3.50, 4));
        inv.Add(new Inventory("Drills", 19.88, 8));

        Console.WriteLine("Inventory list before sorting:");

        foreach(Inventory i in inv)
        {
            Console.WriteLine(" " + i);
        }
        Console.WriteLine();


        // Sort the list.
        inv.Sort();

        Console.WriteLine("Inventory list after sorting:");

        foreach(Inventory i in inv)
        {
            Console.WriteLine(" " + i);
        }
    }
}
