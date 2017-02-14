// Format an enumeration.
using System;


class EnumFmtDemo
{
    enum Direction { North, South, East, West }

    [Flags] enum Status { Ready=0x1, OffLine=0x2,

    Waiting=0x4, TransmitOK=0x8,
    RecieveOK=0x10, OnLine=0x20 }


    static void Main()
    {
        Direction d = Direction.West;
        Console.WriteLine("{0:G}", d);
        Console.WriteLine("{0:F}", d);
        Console.WriteLine("{0:D}", d);
        Console.WriteLine("{0:X}", d);

        Status s = Status.Ready | Status.TransmitOK;
        Console.WriteLine("{0:G}", s);
        Console.WriteLine("{0:F}", s);
        Console.WriteLine("{0:D}", s);
        Console.WriteLine("{0:X}", s);
    }
}
