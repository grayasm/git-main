/*
    Use let to Create a Variable in a Query
    In a query, you will sometimes want to retain a value temporarily.
    For example, you might want to create an enumerable variable that
    can, itself, be queried. Or, you might want to store a value that
    will be used later on in a where clause. Whatever the purpose,
    these types of actions can be accomplished through the use of let.
    The let clause has this general form:

let name = expression

*/

// Use a let clause and a nested from clause.
using System;
using System.Linq;


class LetDemo
{
    static void Main()
    {
        string[] strs = { "alpha", "beta", "gamma" };

        // Create a query that obtains the characters in the
        // strings, returned in sorted order. Notice the use
        // of a nested from clause.
        var chrs = from str in strs
                   let chrArray = str.ToCharArray()
                   from ch in chrArray
                   orderby ch
                   select ch;

        Console.WriteLine("The individual characters in sorted order:");

        // Execute the query and display the results.
        foreach(char c in chrs)
            Console.Write(c + " ");
        Console.WriteLine();
    }
}
