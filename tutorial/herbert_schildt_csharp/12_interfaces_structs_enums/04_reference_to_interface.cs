/*
    Using Interface References
    You might be somewhat surprised to learn that you can declare a reference variable of an
interface type. In other words, you can create an interface reference variable. Such a variable
can refer to any object that implements its interface. When you call a method on an object
through an interface reference, it is the version of the method implemented by the object
that is executed. This process is similar to using a base class reference to access a derived
class object, as described in Chapter 11.

*/

// Demonstrate interface references.

using System;


// Define the interface.
public interface ISeries
{
    int GetNext();  // return next number in series
    void Reset();   // restart
    void SetStart(int x);   // set starting value
}


// Use ISeries to implement a series in which each
// value is two greater than the previous one.
class ByTwos : ISeries
{
    int start;
    int val;

    public ByTwos()
    {
        start = 0;
        val = 0;
    }

    public int GetNext()
    {
        val += 2;
        return val;
    }

    public void Reset()
    {
        val = start;
    }

    public void SetStart(int x)
    {
        start = x;
        val = start;
    }
}


// Use ISeries to implement a series of prime numbers.
class Primes : ISeries
{
    int start;
    int val;

    public Primes()
    {
        start = 2;
        val = 2;
    }

    public int GetNext()
    {
        int i, j;
        bool isprime;

        val++;
        for(i = val; i < 1000000; i++)
        {
            isprime = true;
            for(j = 2; j <= i/j; j++)
            {
                if((i%j)==0)
                {
                    isprime = false;
                    break;
                }
            }

            if(isprime)
            {
                val = i;
                break;
            }
        }
        return val;
    }

    public void Reset()
    {
        val = start;
    }

    public void SetStart(int x)
    {
        start = x;
        val = start;
    }
}


class SeriesDemo2
{
    static void Main()
    {
        ByTwos twoOb = new ByTwos();
        Primes primeOb = new Primes();
        ISeries ob;

        for(int i=0; i < 5; i++)
        {
            ob = twoOb;

            Console.WriteLine("Next ByTwos value is " + ob.GetNext());

            ob = primeOb;

            Console.WriteLine("Next prime number is " + ob.GetNext());
        }
    }
}
