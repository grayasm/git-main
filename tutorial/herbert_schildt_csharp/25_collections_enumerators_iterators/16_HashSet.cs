// Demonstrate the HashSet<T> class.
using System;
using System.Collections.Generic;


class HashSetDemo
{
    static void Show(string msg, HashSet<char> set)
    {
        Console.Write(msg);
        foreach(char ch in set)
            Console.Write(ch + " ");
        Console.WriteLine();
    }


    static void Main()
    {
        HashSet<char> setA = new HashSet<char>();
        HashSet<char> setB = new HashSet<char>();

        setA.Add('A');
        setA.Add('B');
        setA.Add('C');
        setB.Add('C');
        setB.Add('D');
        setB.Add('E');


        Show("Initial content of setA: ", setA);
        Show("Initial content of setB: ", setB);

        setA.SymmetricExceptWith(setB);

        Show("setA after Symmetric difference with SetB: ", setA);
        setA.UnionWith(setB);

        Show("setA after union with setB: ", setA);
        setA.ExceptWith(setB);

        Show("setA after subtracting setB: ", setA);

        Console.WriteLine();
    }
}
