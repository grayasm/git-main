.
    LINQ

    LINQ stands for Language-Integrated Query.
    It encompasses a set of features that lets you retrieve information
    from a data source. In the past, interacting with such a database
    would involve generating queries using SQL (Structured Query Language).
    Other sources of data, such as XML, required their own approaches.
    LINQ gives to C# the ability to generate queries for any LINQ-compatible
    data source. It is not necessary to use SQL or any other non-C# mechanism.
    The query capability is fully integrated into the C# language.
    In addition to using LINQ with SQL, LINQ can be used with XML files and
    ADO.NET Datasets. Perhaps equally important, it can also be used with
    C# arrays and collections.

    IEnumerable<int> posNums = from n in nums
                               where n > 0
                               select n;

    Query contextual keywords:
    --------------------------
    ascending    by       descending    equals
    from         group    in            into
    join         let      on            orderby
    select       where


    Query begin clauses:
    --------------------
    from         group    join          let
    orderby      select   where


    The Query Methods:
    ------------------
    The query methods are defined by System.Linq.Enumerable and are
    implemented as extension methods that extend the functionality
    of IEnumerable<T>. (Query methods are also defined by System.Linq.Queryable,
    which extends the functionality of IQueryable<T>.

    Query Keyword    Equivalent Query Method
    -------------    -----------------------
    select           Select(selector)
    where            Where(predicate)
    orderby          OrderBy(keySelector) or OrderByDescending(keySelector)
    join             Join(inner, outerKeySelector, innerKeySelector, resultSelector)
    group            GroupBy(keySelector)
