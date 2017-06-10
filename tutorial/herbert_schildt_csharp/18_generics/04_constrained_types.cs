/*
    Constrained Types

    class Gen<T> accepts any type for T. However, sometimes the programmer
    wants a restriction for the type T. This is accomplished through the
    following syntax:

class class-name<type-param> where type-param : constraints { // ...

    type-param must be derived from type contraints to compile without error.
    A base class constraint serves two important purposes.
    (1) First, it lets you use the members of the base class specified by
        the constraint within the generic class.
    (2) The second purpose of a base class constraint is to ensure that
        only type arguments that support the specified base class are used,
        base class or derived types.
*/


// A simple demonstration of a base class constraint.

using System;

class A
{
    public void Hello()
    {
        Console.WriteLine("Hello");
    }
}


// Class B inherits A.
class B : A { }

// Class C does not inherit A.
class C { }

// Because of the base class constraint, all type arguments
// passed to Test must have A as a base class.
class Test<T> where T : A
{
    T obj;
    public Test(T o)
    {
        obj = o;
    }

    public void SayHello()
    {
        // OK to call Hello() because it’s declared
        // by the base class A.
        obj.Hello();
    }
}


class BaseClassConstraintDemo
{
    static void Main()
    {
        A a = new A();
        B b = new B();
        C c = new C();

        // The following is valid because A is the specified base class.
        Test<A> t1 = new Test<A>(a);
        t1.SayHello();

        // The following is valid because B inherits A.
        Test<B> t2 = new Test<B>(b);
        t2.SayHello();

        // The following is invalid because C does not inherit A.
        // Test<C> t3 = new Test<C>(c); // Error!
        // t3.SayHello(); // Error!
    }
}
