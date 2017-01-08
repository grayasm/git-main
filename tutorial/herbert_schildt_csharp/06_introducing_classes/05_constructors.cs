using System;


class MyClass
{
    public int x;

    // A simple constructor.
    public MyClass()
    {
        x = 10;
    }

    // A parameterized constructor.
    public MyClass(int i)
    {
        x = i;
    }
}


class Building
{
    public int Floors;     // number of floors
    public int Area;       // total square footage of building
    public int Occupants;  // number of occupants

    // A parameterized constructor for Building.
    public Building(int f, int a, int o)
    {
        Floors = f;
        Area = a;
        Occupants = o;
    }

    // Display the area per person.
    public int AreaPerPerson()
    {
        return Area / Occupants;
    }

    // Return the maximum number of occupants if each
    // is to have at least the specified minimum area.
    public int MaxOccupant(int minArea)
    {
        return Area / minArea;
    }
}



class Constructor
{
    static void Main()
    {

        MyClass t1 = new MyClass();
        MyClass t2 = new MyClass();

        Console.WriteLine(t1.x + " " + t2.x);

        MyClass t3 = new MyClass(10);
        MyClass t4 = new MyClass(88);
        Console.WriteLine(t3.x + " " + t4.x);


        Building house = new Building(2, 2500, 4);
        Building office = new Building(3, 4200, 25);
        Console.WriteLine("Maximum occupants for house if each has " +
                          300 + " square feet: " + house.MaxOccupant(300));

        Console.WriteLine("Maximum occupants for office if each has " +
                          300 + " square feet: " + office.MaxOccupant(300));

    }
}