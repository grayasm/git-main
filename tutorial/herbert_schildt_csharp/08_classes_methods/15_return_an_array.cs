// Return an array.

using System;


class Factor
{
    /* Return an array containing the factors of num.
       On return, numfactors will contain the number of
       factors found. */
    public int[] FindFactors(int num, out int numfactors)
    {
        int[] facts = new int[80]; // size of 80 is arbitrary
        int i, j;

        // Find factors and put them in the facts array.
        for(i=2, j=0; i < num/2 + 1; i++)
            if( (num%i)==0 )
            {
                facts[j] = i;
                j++;
            }

        numfactors = j;
        return facts;
    }
}


class FindFactors
{
    static void Main()
    {
        Factor f = new Factor();
        int numfactors;
        int[] factors;
        factors = f.FindFactors(1000, out numfactors);
        Console.WriteLine("Factors for 1000 are: ");
        for(int i=0; i < numfactors; i++)
            Console.Write(factors[i] + " ");

        Console.WriteLine();
    }
}
