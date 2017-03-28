// An automated pair of dice.
using System;


class RandDice
{
    static void Main()
    {
        Random ran = new Random();

        Console.Write(ran.Next(1, 7) + " ");
        Console.WriteLine(ran.Next(1, 7));
    }
}
