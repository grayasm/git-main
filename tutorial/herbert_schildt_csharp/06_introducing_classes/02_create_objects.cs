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
        Building house;         // declare reference to object
        house = new Building(); // allocate a Building object
        house.Occupants = 0;

        int x;
        x = 10;
        x *= 1;
        /*  x contains the value 10 because x is a variable of type int,
            which is a value type. However, in the case of
        */

        Building house2 = new Building();
        /*  house does not, itself, contain the object. Instead, it contains
            a reference to the object.
        */
        house2.Occupants = 0;
    }
}