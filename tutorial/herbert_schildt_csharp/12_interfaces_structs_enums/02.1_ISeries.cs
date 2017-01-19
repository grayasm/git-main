public interface ISeries
{
    int GetNext();    // return next number in series
    void Reset();     // restart
    void SetStart(int x);  // set starting value
}
