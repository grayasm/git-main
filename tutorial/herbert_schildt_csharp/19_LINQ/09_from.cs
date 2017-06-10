/*
    Use Nested from Clauses
    A query can contain more than one from clause. Thus, a query
    can contain nested from clauses. One common use of a nested
    from clause is found when a query needs to obtain data from
    two different sources.
*/


// Use two from clauses to create a list of all
// possible combinations of the letters A, B, and C
// with the letters X, Y, and Z.

using System;
using System.Linq;


// This class holds the result of the query.
class ChrPair
{
    public char First;
    public char Second;
    public ChrPair(char c, char c2)
    {
        First = c;
        Second = c2;
    }
}


class MultipleFroms
{
    static void Main()
    {
        char[] chrs = { 'A', 'B', 'C' };
        char[] chrs2 = { 'X', 'Y', 'Z' };

        // Notice that the first from iterates over chrs and
        // the second from iterates over chrs2.
        var pairs = from ch1 in chrs
                    from ch2 in chrs2
                    select new ChrPair(ch1, ch2);


        Console.WriteLine("All combinations of ABC with XYZ: ");
        foreach(var p in pairs)
            Console.WriteLine("{0} {1}", p.First, p.Second);
    }
}
