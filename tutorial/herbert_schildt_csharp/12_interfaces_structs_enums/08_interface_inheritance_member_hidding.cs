/*
    Name Hiding with Interface Inheritance

    When one interface inherits another, it is possible to declare a member
    in the derived interface that hides one defined by the base interface.
    This happens when a member in a derived interface has the same declaration
    as one in the base interface. In this case, the base interface name is
    hidden. This will cause a warning message unless you specify the derived
    interface member with new.
*/
using System;

class Demo
{
    static void Main(){}
}