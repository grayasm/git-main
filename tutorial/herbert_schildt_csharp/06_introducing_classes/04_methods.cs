using System;


// class with methods returning void or int
class Building
{
    public int Floors;         // number of floors
    public int Area;           // total square footage of building
    public int Occupants;      // number of occupants

    // Display the area per person.
    public void ShowAreaPerPerson()
    {
        Console.WriteLine(" " + Area / Occupants + " area per person");
    }

    // Return the area per person.
    public int CalcAreaPerPerson()
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


// A simple example that uses a parameter.
class ChkNum
{
    // Return true if x is prime.
    public bool IsPrime(int x)
    {
        if(x <= 1) return false;

        for(int i=2; i <= x/i; i++)
            if((x %i) == 0) return false;

        return true;
    }

    // Return the least common factor.
    public int LeastComFactor(int a, int b)
    {
        int max;
        if(IsPrime(a) || IsPrime(b)) return 1;

        max = a < b ? a : b;

        for(int i=2; i <= max/2; i++)
            if(((a%i) == 0) && ((b%i) == 0)) return i;

        return 1;
    }
}


// Use the AreaPerPerson() method.
class BuildingDemo
{
    //Return from a Method
    public void MyMeth()
    {
        int i;

        for(i=0; i<10; i++)
        {
            if(i == 5) return; // stop at 5
            Console.WriteLine();
        }
    }

    static void Main()
    {
        Building house = new Building();
        Building office = new Building();

        // Assign values to fields in house.
        house.Occupants = 4;
        house.Area = 2500;
        house.Floors = 2;

        // Assign values to fields in office.
        office.Occupants = 25;
        office.Area = 4200;
        office.Floors = 3;

        Console.WriteLine("house has:\n " +
                          house.Floors + " floors\n " +
                          house.Occupants + " occupants\n" +
                          house.Area + " total area");

        house.ShowAreaPerPerson();

        Console.WriteLine();

        Console.WriteLine("office has:\n " +
                          office.Floors + " floors\n " +
                          office.Occupants + " occupants\n" +
                          office.Area + " total area");

        office.ShowAreaPerPerson();

        // Use the return value from AreaPerPerson().
        int areaPP; // area per person

        // Obtain area per person for house.
        areaPP = house.CalcAreaPerPerson();

        Console.WriteLine("house has:\n " +
                          house.Floors + " floors\n " +
                          house.Occupants + " occupants\n " +
                          house.Area + " total area\n " +
                          areaPP + " area per person");

        Console.WriteLine();

        // Obtain area per person for office.
        areaPP = office.CalcAreaPerPerson();
        Console.WriteLine("office has:\n " +
                          office.Floors + " floors\n " +
                          office.Occupants + " occupants\n " +
                          office.Area + " total area\n " +
                          areaPP + " area per person");


        // A simple example that uses a parameter.
        ChkNum ob0 = new ChkNum();
        for(int i=2; i < 10; i++)
            if(ob0.IsPrime(i))
                Console.WriteLine(i + " is prime.");
            else
                Console.WriteLine(i + " is not prime.");


        // Use a method that takes 2 parameters
        ChkNum ob = new ChkNum();
        int a, b;

        for(int i=2; i < 10; i++)
            if(ob.IsPrime(i))
                Console.WriteLine(i + " is prime.");
            else
                Console.WriteLine(i + " is not prime.");

        a = 7;
        b = 8;

        Console.WriteLine("Least common factor for " +
                          a + " and " + b + " is " +
                          ob.LeastComFactor(a, b));
        a = 100;
        b = 8;

        Console.WriteLine("Least common factor for " +
                          a + " and " + b + " is " +
                          ob.LeastComFactor(a, b));

        a = 100;
        b = 75;

        Console.WriteLine("Least common factor for " +
                          a + " and " + b + " is " +
                          ob.LeastComFactor(a, b));


        /*
        Add a parameterized method that computes the
        maximum number of people that can occupy a
        building assuming each needs a specified
        minimum space.
        */
        Console.WriteLine("Maximum occupants for house if each has " +
                          300 + " square feet: " +
                          house.MaxOccupant(300));

        Console.WriteLine("Maximum occupants for office if each has " +
                          300 + " square feet: " +
                          office.MaxOccupant(300));


        // Avoiding Unreachable Code
        if(a==b)
        {
            Console.WriteLine("equal");
            return;
        }
        else
        {
            Console.WriteLine("not equal");
            return;
        }
        Console.WriteLine("this is unreachable");
    }
}