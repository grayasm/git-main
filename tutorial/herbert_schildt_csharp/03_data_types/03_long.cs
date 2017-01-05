// Compute the distance from the Earth to the sun, in inches.
using System;

class Inches
{
    static void Main()
    {
        long inches;
        long miles;

        miles = 93000000; // 93,000,000 miles to the sun

        // 5,280 feet in a mile, 12 inches in a foot.
        inches = miles * 5280 * 12;
        Console.WriteLine("Distance to the sun: " +
                           inches + " inches.");
    }
}