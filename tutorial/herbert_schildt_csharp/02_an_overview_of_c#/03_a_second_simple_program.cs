/*
        pag. 24, A Second Simple Program
        This program demonstrates variables.
*/

using System;

class Example
{
    static void Main()
    {
        int x; // this declares a variable
        int y; // this declares another variable

        x = 100;
        Console.WriteLine("x contains " + x);

        y = x / 2;
        Console.Write("y contains x / 2 : ");
        Console.WriteLine(y);
    }
}