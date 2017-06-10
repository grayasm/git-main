using System;

class Example
{
    static void Main()
    {
        /*
            Operator Result
            &        Bitwise AND
            |        Bitwise OR
            ^        Bitwise exclusive OR (XOR)
            >>       Shift right
            <<       Shift left
            ~        One’s complement (unary NOT)
        */

        // Use bitwise AND to make a number even.
        ushort num;
        ushort i;
        for(i = 1; i <= 10; i++)
        {
            num = i;
            Console.WriteLine("num: " + num);
            num = (ushort) (num & 0xFFFE);
            Console.WriteLine("num after turning off bit zero: " + num + "\n");
        }

        // Use bitwise AND to determine if a number is odd.
        num = 10;
        if((num & 1) == 1)
            Console.WriteLine("This won't display.");

        num = 11;
        if((num & 1) == 1)
            Console.WriteLine(num + " is odd.");


        // Display the bits within a byte.
        byte val;

        val = 123;
        for(int t=128; t > 0; t = t/2)
        {
            if((val & t) != 0) Console.Write("1 ");
            if((val & t) == 0) Console.Write("0 ");
        }


        // Use bitwise OR to make a number odd.
        for(i = 1; i <= 10; i++)
        {
            num = i;
            Console.WriteLine("num: " + num);
            num = (ushort) (num | 1);
            Console.WriteLine("num after turning on bit zero: " + num + "\n");
        }


        // Demonstrate the XOR.

        char ch1 = 'H';
        char ch2 = 'i';
        char ch3 = '!';
        int key = 88;
        Console.WriteLine("Original message: " + ch1 + ch2 + ch3);

        // Encode the message.
        ch1 = (char) (ch1 ^ key);
        ch2 = (char) (ch2 ^ key);
        ch3 = (char) (ch3 ^ key);
        Console.WriteLine("Encoded message: " + ch1 + ch2 + ch3);

        // Decode the message.
        ch1 = (char) (ch1 ^ key);
        ch2 = (char) (ch2 ^ key);
        ch3 = (char) (ch3 ^ key);
        Console.WriteLine("Decoded message: " + ch1 + ch2 + ch3);


        // Demonstrate the bitwise NOT.

        sbyte b = -34;
        for(int t=128; t > 0; t = t/2)
        {
            if((b & t) != 0) Console.Write("1 ");
            if((b & t) == 0) Console.Write("0 ");
        }
        Console.WriteLine();

        // reverse all bits
        b = (sbyte) ~b;

        for(int t=128; t > 0; t = t/2)
        {
            if((b & t) != 0) Console.Write("1 ");
            if((b & t) == 0) Console.Write("0 ");
        }
    }
}