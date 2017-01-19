/*
    It is both permissible and common for classes that implement interfaces
    to define additional members of their own.
*/

// Implement ISeries and add GetPrevious().
class ByTwos : ISeries
{
    int start;
    int val;
    int prev;

    public ByTwos()  // ctor
    {
        start = 0;
        val = 0;
        prev = -2;
    }

    public int GetNext()  // from interface
    {
        prev = val;
        val += 2;
        return val;
    }

    public void Reset()  // from interface
    {
        val = start;
        prev = start - 2;
    }

    public void SetStart(int x)  // from interface
    {
        start = x;
        val = start;
        prev = val - 2;
    }

    // A method not specified by ISeries.
    public int GetPrevious()
    {
        return prev;
    }
}
