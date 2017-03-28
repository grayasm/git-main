// Store Inventory Objects in a List<T> collection.
using System;
using System.Collections.Generic;


class Inventory
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
}


class TypeSafeInventoryList
{
    static void Main()
    {
        List<Inventory> inv = new List<Inventory>();

        // Add elements to the list
        inv.Add(new Inventory("Pliers", 5.95, 3));
        inv.Add(new Inventory("Wrenches", 8.29, 2));
        inv.Add(new Inventory("Hammers", 3.50, 4));
        inv.Add(new Inventory("Drills", 19.88, 8));

        Console.WriteLine("Inventory list:");
        foreach(Inventory i in inv)
        {
            Console.WriteLine(" " + i);
        }
    }
}
