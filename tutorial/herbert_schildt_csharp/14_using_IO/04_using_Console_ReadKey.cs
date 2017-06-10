// Read keystrokes from the console by using ReadKey().

using System;


class ReadKeys
{
    static void Main()
    {
        ConsoleKeyInfo keypress;
        Console.WriteLine("Enter keystrokes. Enter Q to stop.");

        do
        {
            keypress = Console.ReadKey(); // read keystrokes
            Console.WriteLine(" Your key is: " + keypress.KeyChar);

            // Check for modifier keys.
            if((ConsoleModifiers.Alt & keypress.Modifiers) != 0)
                Console.WriteLine("Alt key pressed.");

            if((ConsoleModifiers.Control & keypress.Modifiers) != 0)
                Console.WriteLine("Control key pressed.");

            if((ConsoleModifiers.Shift & keypress.Modifiers) != 0)
                Console.WriteLine("Shift key pressed.");
        }
        while(keypress.KeyChar != 'Q');

    }
}
