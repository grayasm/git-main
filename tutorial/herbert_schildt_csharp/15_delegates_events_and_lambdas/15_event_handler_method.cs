/*
    Instance Methods vs. Static Methods as Event Handlers

    Although both instance methods and static methods can be used as event
    handlers, they do differ in one important way. When a static method is
    used as a handler, an event notification applies to the class. When an
    instance method is used as an event handler, events are sent to specific
    object instances. Thus, each object of a class that wants to receive an
    event notification must register individually. In practice, most event
    handlers are instance methods, but, of course, this is subject to the
    specific application.
*/

/* Individual objects receive notifications when instance
   event handlers are used. */

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
    int id;

    public X(int x) { id = x; }

    // This is an instance method that will be used as an event handler.
    public void Xhandler()
    {
        Console.WriteLine("Event received by object " + id);
    }
}

class EventDemo3
{
    static void Main()
    {
        MyEvent evt = new MyEvent();
        X o1 = new X(1);
        X o2 = new X(2);
        X o3 = new X(3);

        evt.SomeEvent += o1.Xhandler;
        evt.SomeEvent += o2.Xhandler;
        evt.SomeEvent += o3.Xhandler;

        // Raise the event.
        evt.OnSomeEvent();
    }
}
