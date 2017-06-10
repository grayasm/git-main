// A keypress event example.

using System;


// Derive a custom EventArgs class that holds the key.
class KeyEventArgs : EventArgs
{
    public char ch;
}


// Declare a keypress event class.
class KeyEvent
{
    public event EventHandler <KeyEventArgs> KeyPress;

    // This is called when a key is pressed.
    public void OnKeyPress(char key)
    {
        KeyEventArgs k = new KeyEventArgs();
        if(KeyPress != null)
        {
            k.ch = key;
            KeyPress(this, k);
        }
    }
}


// Demonstrate KeyEvent.
class KeyEventDemo
{
    static void Main()
    {
        KeyEvent kevt = new KeyEvent();
        ConsoleKeyInfo key;
        int count = 0;

        // Use a lambda expression to display the keypress.
        kevt.KeyPress += (sender, e) =>
            Console.WriteLine(" Received keystroke: " + e.ch);

        // Use a lambda expression to count keypresses.
        kevt.KeyPress += (sender, e) =>
            count++; // count is an outer variable

            Console.WriteLine("Enter some characters. " +
                              "Enter a period to stop.");

        do {
            key = Console.ReadKey();
            kevt.OnKeyPress(key.KeyChar);
        } while(key.KeyChar != '.');

        Console.WriteLine(count + " keys pressed.");
    }
}
