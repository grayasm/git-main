/*
    Expression Trees
    Another LINQ-related feature is the expression tree. An expression
    tree is a representation of a lambda expression as data. Thus, an
    expression tree, itself, cannot be executed. It can, however, be
    converted into an executable form. Expression trees are encapsulated
    by the System.Linq.Expressions.Expression<TDelegate> class.

    Expression trees are useful in situations in which a query will be
    executed by something outside the program, such as a database that
    uses SQL. By representing the query as data, the query can be converted
    into a format understood by the database. This process is used by
    the LINQ to SQL feature provided by Visual C#, for example. Thus,
    expression trees help C# support a variety of data sources. You can
    obtain an executable form of an expression tree by calling the
    Compile( ) method defined by Expression.
*/

// A simple expression tree.
using System;
using System.Linq;
using System.Linq.Expressions;


class SimpleExpTree
{
    static void Main()
    {
        // Represent a lambda expression as data.
        Expression<Func<int, int, bool>>
            IsFactorExp = (n, d) => (d != 0) ? (n % d) == 0 : false;

        // Compile the expression data into executable code.
        Func<int, int, bool> IsFactor = IsFactorExp.Compile();

        // Execute the expression.
        if(IsFactor(10, 5))
            Console.WriteLine("5 is a factor of 10.");

        if(!IsFactor(10, 7))
            Console.WriteLine("7 is not a factor of 10.");

        Console.WriteLine();
    }
}
