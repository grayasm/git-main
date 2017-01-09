using System;

// Define a Class
class Building
{
    public int Floors;         // number of floors
    public int Area;           // total square footage of building
    public int Occupants;      // number of occupants
}




class Example
{
    static void Main()
    {
        // Reference Variables and Assignment
        Building house1 = new Building();
        Building house2 = house1;
        // house1 and house2 will both refer to the same object


        house1.Area = 2600;
        Console.WriteLine(house1.Area);
        Console.WriteLine(house2.Area);
    }
}