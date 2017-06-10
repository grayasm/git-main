using System;

class Example
{
    static void Main()
    {
        // A negatively running for loop.
        int x;

        for(x = 100; x > -100; x -= 5)
           Console.WriteLine(x);

        // Determine if a number is prime. If it is not, then
        // display its largest factor.

        int num;
        int i;
        int factor;
        bool isprime;

        for(num = 2; num < 20; num++)
        {
            isprime = true;
            factor = 0;

            // See if num is evenly divisible.
            for(i=2; i <= num/2; i++)
            {
                if((num % i) == 0)
                {
                // num is evenly divisible. Thus, it is not prime.
                isprime = false;
                factor = i;
                }
            }

            if(isprime)
                 Console.WriteLine(num + " is prime.");
            else
                Console.WriteLine("Largest factor of " + num + " is " + factor);
        }

        // Use commas in a for statement.
        int j;

        for(i=0, j=10; i < j; i++, j--)
            Console.WriteLine("i and j: " + i + " " + j);


        // Use commas in a for statement to find the largest and
        // smallest factor of a number.
        int smallest, largest;

        num = 100;
        smallest = largest = 1;
        for(i=2, j=num/2; (i <= num/2) & (j >= 2); i++, j--)
        {
            if((smallest == 1) & ((num % i) == 0))
                smallest = i;

            if((largest == 1) & ((num % j) == 0))
                largest = j;
        }
        Console.WriteLine("Largest factor: " + largest);
        Console.WriteLine("Smallest factor: " + smallest);


        // Loop condition can be any bool expression.
        bool done = false;

        for(i=0, j=100; !done; i++, j--)
        {
            if(i*i >= j) done = true;

            Console.WriteLine("i, j: " + i + " " + j);
        }


        // Parts of the for can be empty.

        for(i = 0; i < 10; )
        {
            Console.WriteLine("Pass #" + i);
            i++; // increment loop control var
        }


        // Move more out of the for loop.

        i = 0; // move initialization out of loop

        for(; i < 10; )
        {
            Console.WriteLine("Pass #" + i);
            i++; // increment loop control var
        }

        // The Infinite Loop
        for(;;) // intentionally infinite loop
        {
            Console.WriteLine("infinite loop");
            break;
        }

        // The body of a loop can be empty.
        int sum=0;
        // Sum the numbers through 5.
        for(i = 1; i <= 5; sum += i++) ;

        Console.WriteLine("Sum is " + sum);


        // Declare loop control variable inside the for.

        int fact = 1;
        // Compute the factorial of the numbers 1 through 5.
        for(i = 1; i <= 5; i++)
        {
            sum += i; // i is known throughout the loop.
            fact *= i;
        }
        // But, i is not known here.
        Console.WriteLine("Sum is " + sum);
        Console.WriteLine("Factorial is " + fact);

    }
}