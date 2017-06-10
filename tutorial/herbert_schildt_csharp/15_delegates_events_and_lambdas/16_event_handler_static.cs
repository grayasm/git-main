/*
    A class receives the notification when a static method is used as an
    event handler.
*/


using System;

// Declare a delegate type for an event.

delegate void MyEventHandler();

// Declare a class that contains an event.
class MyEvent
{
    public event MyEventHandler SomeEvent;

    // This is called to raise the event.
    public void OnSomeEvent()
    {
        if(SomeEvent != null)
            SomeEvent();
    }
}

class X
{
    /* This is a static method that will be used as an event handler. */

    public static void Xhandler()
    {
        Console.WriteLine("Event received by class.");
    }
}

class EventDemo4
{
    static void Main()
    {
        MyEvent evt = new MyEvent();
        evt.SomeEvent += X.Xhandler;

        // Raise the event.
        evt.OnSomeEvent();
    }
}
