/*
    Using Multiple Constraints

    There can be more than one constraint associated with a type
    parameter. When this is the case, use a comma-separated list
    of constraints. In this list, the first constraint must be class
    or struct (if present) or the base class (if one is specified).
    It is illegal to specify both a class or struct constraint and a
    base class constraint. Next in the list must be any interface
    constraints. The new( ) constraint must be last. For example, this
    is a valid declaration.

class Gen<T> where T : MyClass, IMyInterface, new() { // ...


    When using two or more type parameters, you can specify a constraint
    for each parameter by using a separate where clause.
*/



// Use multiple where clauses.
using System;


// Gen has two type arguments and both have a where clause.
class Gen<T, V> where T : class
                where V : struct
{
    T ob1;
    V ob2;

    public Gen(T t, V v)
    {
        ob1 = t;
        ob2 = v;
    }
}


class MultipleConstraintDemo
{
    static void Main()
    {
        // This is OK because string is a class and
        // int is a value type.
        Gen<string, int> obj = new Gen<string, int>("test", 11);

        // The next line is wrong because bool is not
        // a reference type.
        // Gen<bool, int> obj = new Gen<bool, int>(true, 11);
    }
}
