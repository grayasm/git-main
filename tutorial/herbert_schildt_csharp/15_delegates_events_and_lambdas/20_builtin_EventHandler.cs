// Use the built-in EventHandler delegate.

using System;

// Declare a class that contains an event.
class MyEvent
{
    public event EventHandler SomeEvent; // uses EventHandler delegate

    // This is called to raise SomeEvent.
    public void OnSomeEvent()
    {
        if(SomeEvent != null)
            SomeEvent(this, EventArgs.Empty);
    }
}

class EventDemo7
{
    static void Handler(object sender, EventArgs e)
    {
        Console.WriteLine("Event occurred");
        Console.WriteLine("Source is " + sender);
    }

    static void Main()
    {
        MyEvent evt = new MyEvent();

        // Add Handler() to the event list.
        evt.SomeEvent += Handler;

        // Raise the event.
        evt.OnSomeEvent();
    }
}
