/*
    Using sealed to Prevent Inheritance

    Whatever the reason, in C# it is easy to prevent a class from being
    inherited by using the keyword sealed.
    To prevent a class from being inherited, precede its declaration with
    sealed. As you might expect, it is illegal to declare a class as both
    abstract and sealed because an abstract class is incomplete by itself
    and relies upon its derived classes to provide complete implementations.
*/


sealed class A
{
    // ...
}


// The following class is illegal.
class B : A    // ERROR! Can't derive from class A
{
    // ...
}
