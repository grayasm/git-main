using System;

class Example
{
    static void Main()
    {
        // Demonstrate the short-circuit operators.

        int n, d;
        n = 10;
        d = 2;

        if(d != 0 && (n % d) == 0)
             Console.WriteLine(d + " is a factor of " + n);

        d = 0; // now, set d to zero
        // Since d is zero, the second operand is not evaluated.
        if(d != 0 && (n % d) == 0)
            Console.WriteLine(d + " is a factor of " + n);

        // Now, try the same thing without the short-circuit operator.
        // This will cause a divide-by-zero error.
        if(d != 0 & (n % d) == 0)
             Console.WriteLine(d + " is a factor of " + n);


        // Side effects can be important.
        int i;
        bool someCondition = false;
        i = 0;

        // Here, i is still incremented even though the if statement fails.
        if(someCondition & (++i < 100))
            Console.WriteLine("this won't be displayed");

        Console.WriteLine("if statement executed: " + i); // displays 1
        // In this case, i is not incremented because the short-circuit
        // operator skips the increment.
        if(someCondition && (++i < 100))
            Console.WriteLine("this won't be displayed");

        Console.WriteLine("if statement executed: " + i); // still 1 !!
    }
}