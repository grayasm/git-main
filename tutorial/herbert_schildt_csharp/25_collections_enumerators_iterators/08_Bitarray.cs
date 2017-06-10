// Demonstrate BitArray.
using System;
using System.Collections;


class BADemo
{
    public static void ShowBits(string rem, BitArray bits)
    {
        Console.WriteLine(rem);

        for(int i=0; i < bits.Count; i++)
            Console.Write("{0, -6} ", bits[i]);

        Console.WriteLine("\n");
    }


    static void Main()
    {
        BitArray ba = new BitArray(8);

        byte[] b = { 67 };

        BitArray ba2 = new BitArray(b);

        ShowBits("Original contents of ba:", ba);

        ba = ba.Not();

        ShowBits("Contents of ba after Not:", ba);
        ShowBits("Contents of ba2:", ba2);

        BitArray ba3 = ba.Xor(ba2);

        ShowBits("Result of ba XOR ba2:", ba3);
    }
}