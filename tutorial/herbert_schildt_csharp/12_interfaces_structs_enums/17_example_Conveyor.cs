// Simulate a conveyor belt.

using System;


class ConveyorControl
{
    // Enumerate the conveyor commands.
    public enum Action { Start, Stop, Forward, Reverse };

    public void Conveyor(Action com)
    {
        switch(com)
        {
            case Action.Start:
                Console.WriteLine("Starting conveyor.");
                break;
            case Action.Stop:
                Console.WriteLine("Stopping conveyor.");
                break;

            case Action.Forward:
                Console.WriteLine("Moving forward.");
                break;

            case Action.Reverse:
                Console.WriteLine("Moving backward.");
                break;
        }
    }
}


class ConveyorDemo
{
    static void Main()
    {
        ConveyorControl c = new ConveyorControl();

        c.Conveyor(ConveyorControl.Action.Start);
        c.Conveyor(ConveyorControl.Action.Forward);
        c.Conveyor(ConveyorControl.Action.Reverse);
        c.Conveyor(ConveyorControl.Action.Stop);
    }
}
