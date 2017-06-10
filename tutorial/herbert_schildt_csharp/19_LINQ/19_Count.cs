/*
    Deferred vs. Immediate Query Execution
    In LINQ, queries have two different modes of execution: immediate
    and deferred. As explained early in this chapter, a query defines
    a set of rules that are not actually executed until a foreach
    statement executes. This is called deferred execution. However, if
    you use one of the extension methods that produces a non-sequence
    result, then the query must be executed to obtain that result.
    For example, consider the Count( ) method. In order for Count( )
    to return the number of elements in the sequence, the query must
    be executed, and this is done automatically when Count( ) is called.
    In this case, immediate execution takes place, with the query being
    executed automatically in order to obtain the result. Therefore,
    even though you don’t explicitly use the query in a foreach loop,
    the query is still executed.
*/

// Use immediate execution.
using System;
using System.Linq;


class ImmediateExec
{
    static void Main()
    {
        int[] nums = { 1, -2, 3, 0, -4, 5 };

        // Create a query that obtains the number of positive
        // values in nums.
        int len = (from n in nums
                   where n > 0
                   select n).Count();


        Console.WriteLine("The number of positive values in nums: " + len);
    }
}
