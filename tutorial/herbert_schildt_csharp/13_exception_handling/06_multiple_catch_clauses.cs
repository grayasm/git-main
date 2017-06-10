/*
    Using Multiple catch Clauses
    You can associate more than one catch clause with a try. In fact, it is
    common to do so. However, each catch must catch a different type of
    exception. For example, the program shown here catches both array
    boundary and divide-by-zero errors:
*/

using System;

class ExcDemo4
{
    static void Main()
    {
        // Here, numer is longer than denom.
        int[] numer = { 4, 8, 16, 32, 64, 128, 256, 512 };
        int[] denom = { 2, 0, 4, 4, 0, 8 };

        for(int i=0; i < numer.Length; i++)
        {
            try
            {
                Console.WriteLine(numer[i] + " / " + denom[i] + " is " +
                                  numer[i]/denom[i]);
            }
            catch (DivideByZeroException)
            {
                Console.WriteLine("Can't divide by Zero!");
            }
            catch (IndexOutOfRangeException)
            {
                Console.WriteLine("No matching element found.");
            }
        }
    }
}
