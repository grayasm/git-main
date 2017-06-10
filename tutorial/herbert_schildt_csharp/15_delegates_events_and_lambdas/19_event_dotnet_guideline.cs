/*
    .NET Event Guidelines

    C# allows you to write any type of event you desire. However, for
    component compatibility with the .NET Framework, you will need to
    follow the guidelines Microsoft has established for this purpose.
    At the core of these guidelines is the requirement that event handlers
    have two parameters. The first is a reference to the object that
    generated the event. The second is a parameter of type EventArgs that
    contains any other information required by the handler.

    Thus, .NET-compatible event handlers will have this general form:


void handler(object sender, EventArgs e) {
    // ...
}

*/

// A .NET-compatible event.
using System;

// Derive a class from EventArgs.
class MyEventArgs : EventArgs
{
    public int EventNum;
}

// Declare a delegate type for an event.
delegate void MyEventHandler(object sender, MyEventArgs e);

// Declare a class that contains an event.
class MyEvent
{
    static int count = 0;
    public event MyEventHandler SomeEvent;

    // This raises SomeEvent.
    public void OnSomeEvent()
    {
        MyEventArgs arg = new MyEventArgs();
        if(SomeEvent != null)
        {
            arg.EventNum = count++;
            SomeEvent(this, arg);
        }
    }
}

class X
{
    public void Handler(object sender, MyEventArgs e)
    {
        Console.WriteLine("Event " + e.EventNum + " received by an X object.");
        Console.WriteLine("Source is " + sender);
        Console.WriteLine();
    }
}

class Y
{
    public void Handler(object sender, MyEventArgs e)
    {
        Console.WriteLine("Event " + e.EventNum + " received by a Y object.");
        Console.WriteLine("Source is " + sender);
        Console.WriteLine();
    }
}

class EventDemo6
{
    static void Main()
    {
        X ob1 = new X();
        Y ob2 = new Y();
        MyEvent evt = new MyEvent();

        // Add Handler() to the event list.
        evt.SomeEvent += ob1.Handler;
        evt.SomeEvent += ob2.Handler;

        // Raise the event.
        evt.OnSomeEvent();
        evt.OnSomeEvent();
    }
}
