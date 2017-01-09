using System;

// Define a Class
class Building
{
    public int Floors;         // number of floors
    public int Area;           // total square footage of building
    public int Occupants;      // number of occupants
}




// This class declares an object of type Building.
class BuildingDemo
{
    static void Main()
    {
        // one object
        {
            Building house = new Building(); // create a Building object
            int areaPP; // area per person

            // Assign values to fields in house.
            house.Occupants = 4;
            house.Area = 2500;
            house.Floors = 2;

            // Compute the area per person.
            areaPP = house.Area / house.Occupants;
            Console.WriteLine("house has:\n " +
                              house.Floors + " floors\n " +
                              house.Occupants + " occupants\n " +
                              house.Area + " total area\n " +
                              areaPP + " area per person");
        }


        // This program creates two Building objects.
        {
            Building house = new Building();
            Building office = new Building();
            int areaPP; // area per person

            // Assign values to fields in house.
            house.Occupants = 4;
            house.Area = 2500;
            house.Floors = 2;

            // Assign values to fields in office.
            office.Occupants = 25;
            office.Area = 4200;
            office.Floors = 3;

            // Compute the area per person in house.
            areaPP = house.Area / house.Occupants;
            Console.WriteLine("house has:\n " +
                              house.Floors + " floors\n " +
                              house.Occupants + " occupants\n " +
                              house.Area + " total area\n " +
                              areaPP + " area per person");

            Console.WriteLine();

            // Compute the area per person in office.
            areaPP = office.Area / office.Occupants;
            Console.WriteLine("office has:\n " +
                              office.Floors + " floors\n " +
                              office.Occupants + " occupants\n " +
                              office.Area + " total area\n " +
                              areaPP + " area per person");
        }
    }
}