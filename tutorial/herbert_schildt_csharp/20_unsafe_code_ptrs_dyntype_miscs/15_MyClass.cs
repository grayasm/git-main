/*
    To see how dynamic can simplify certain tasks, we will work through
    a simple example that uses it with reflection. As explained in Chapter 17,
    one way to invoke a method on an object of a class that was obtained
    at runtime via reflection is to call the Invoke( ) method.
    Although this works, it would be more convenient to invoke that method
    by name in cases in which the method name is known. For example,
    you might have a situation in which you know that a certain assembly
    contains a specific class, which supports methods whose names and
    actions are known. However, because this assembly is subject to change,
    you always want to make sure that you are using the latest version.
    One way to accomplish this is to use reflection to examine the assembly,
    construct an object of the class, and then invoke the methods defined
    by the class. By using dynamic, you can now invoke those methods by
    name (since the names are known) rather than through the Invoke( )
    method.

compile this file with: csc /t:library MyClass.cs
*/


public class DivBy
{
    public bool IsDivBy(int a, int b)
    {
        if((a % b) == 0)
            return true;
        return false;
    }

    public bool IsEven(int a)
    {
        if((a % 2) == 0)
            return true;
        return false;
    }
}
