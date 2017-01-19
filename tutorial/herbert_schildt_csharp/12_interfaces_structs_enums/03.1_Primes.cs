/*
    As explained, any number of classes can implement an interface.
    For example, here is a class called Primes that generates a series
    of prime numbers. Notice that its implementation of ISeries is
    fundamentally different than the one provided by ByTwos.
*/


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
