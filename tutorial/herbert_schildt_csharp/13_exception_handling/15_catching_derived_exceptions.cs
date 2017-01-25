/*
    Catching Derived Class Exceptions
    You need to be careful how you order catch clauses when trying to catch
    exception types that involve base and derived classes, because a catch
    for a base class will also match any of its derived classes.

    For example, because the base class of all exceptions is Exception,
    catching Exception catches all possible exceptions. Of course, using
    catch without an exception type provides a cleaner way to catch all
    exceptions, as described earlier. However, the issue of catching derived
    class exceptions is very important in other contexts, especially when you
    create exceptions of your own.

    If you want to catch exceptions of both a base class type and a derived
    class type, put the derived class first in the catch sequence. This is
    necessary because a base class catch will also catch all derived classes.
    Fortunately, this rule is self-enforcing because putting the base class
    first causes a compile-time error.
*/

// Derived exceptions must appear before base class exceptions.

using System;


// Create an exception.
class ExceptA : Exception
{
    public ExceptA(string message) : base(message) { }

    public override string ToString()
    {
        return Message;
    }
}


// Create an exception derived from ExceptA.
class ExceptB : ExceptA
{
    public ExceptB(string message) : base(message) { }
    public override string ToString()
    {
        return Message;
    }
}


class OrderMatters
{
    static void Main()
    {
        for(int x = 0; x < 3; x++)
        {
            try
            {
                if(x==0) throw new ExceptA("Caught an ExceptA exception");
                else if(x==1) throw new ExceptB("Caught an ExceptB exception");
                else throw new Exception();
            }
            catch (ExceptB exc)
            {
                Console.WriteLine(exc);
            }
            catch (ExceptA exc)
            {
                Console.WriteLine(exc);
            }
            catch (Exception exc)
            {
                Console.WriteLine(exc);
            }
        }
    }
}
