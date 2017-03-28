/*
    Lambda Expressions

    Although anonymous methods are still part of C#, they have been largely
    superceded by a better approach: the lambda expression.
    The lambda expression is one of the most important features added to C#
    since its original 1.0 release.

    The Lambda Operator
    All lambda expressions use the lambda operator, which is =>. This operator
    divides a lambda expression into two parts. On the left the input parameter
    (or parameters) is specified. On the right is the lambda body.
    The => operator is sometimes verbalized as "goes to" or "becomes".

    C# supports two types of lambda expressions, and it is the lambda body
    that determines what type is being created.
        a) If the lambda body consists of a single expression, then an
           expression lambda is being created.

        b) If the lambda body consists of a block of statements enclosed
           by braces, then a statement lambda is being created.

param => expr
(param-list) => expr

param => { expr; };
(param-list) => { expr; };

*/

// Use two simple lambda expressions.

using System;


// Declare a delegate that takes an int argument
// and returns an int result.
delegate int Incr(int v);

// Declare a delegate that takes an int argument
// and returns a bool result.

delegate bool IsEven(int v);

class SimpleLambdaDemo
{
    static void Main()
    {
        // Create an Incr delegate instance that refers to
        // a lambda expression that increases its parameter by 2.

        Incr incr = count => count + 2;

        // Now, use the incr lambda expression.
        Console.WriteLine("Use incr lambda expression: ");
        int x = -10;
        while(x <= 0)
        {
            Console.Write(x + " ");
            x = incr(x); // increase x by 2
        }

        Console.WriteLine("\n");

        // Create an IsEven delegate instance that refers to
        // a lambda expression that returns true if its parameter
        // is even and false otherwise.

        IsEven isEven = n => n % 2 == 0;

        // Now, use the isEven lambda expression.
        Console.WriteLine("Use isEven lambda expression: ");
        for(int i=1; i <= 10; i++)
            if(isEven(i))
                Console.WriteLine(i + " is even.");
    }
}
