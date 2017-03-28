/*
    Events
    An event is, essentially, an automatic notification that some action
    has occurred. Events work like this:

    An object that has an interest in an event registers an event handler
    for that event. When the event occurs, all registered handlers are
    called. Event handlers are represented by delegates.

    Events are members of a class and are declared using the "event" keyword.
    Its most commonly used form is shown here:

event event-delegate event-name;

    Here, event-delegate is the name of the delegate used to support the
    event, and event-name is the name of the specific event object being
    declared.
*/

// A very simple event demonstration.

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


class EventDemo
{
    // An event handler.
    static void Handler()
    {
        Console.WriteLine("Event occurred");
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
