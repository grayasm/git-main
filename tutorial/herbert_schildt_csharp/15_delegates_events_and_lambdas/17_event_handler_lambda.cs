/*
    Use Anonymous Methods and Lambda Expressions with Events

    Anonymous methods and lambda expressions are especially useful when
    working with events because often the event handler is not called by
    any code other than the event handling mechanism. As a result, there
    is usually no reason to create a standalone method. Thus, the use of
    lambda expressions or anonymous methods can significantly streamline
    event handling code.
*/

// Use a lambda expression as an event handler.
using System;

// Declare a delegate type for an event.
delegate void MyEventHandler(int n);

// Declare a class that contains an event.
class MyEvent
{
    public event MyEventHandler SomeEvent;

    // This is called to raise the event.
    public void OnSomeEvent(int n)
    {
        if(SomeEvent != null)
            SomeEvent(n);
    }
}

class LambdaEventDemo
{
    static void Main()
    {
        MyEvent evt = new MyEvent();

        // Use a lambda expression as an event handler.
        evt.SomeEvent += (n) =>
            Console.WriteLine("Event received. Value is " + n);

        // Raise the event twice.
        evt.OnSomeEvent(1);
        evt.OnSomeEvent(2);
    }
}
