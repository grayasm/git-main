#pragma once

namespace quotesmgr
{

/** The period of the data grouping for the candle/bar. 
    NOTE: it was copied from from indicore2.dll
          (for original source see indicore2\indicore\source\core\candleperiod.h)

 */
class QUOTESMGR2_API CandlePeriod
{
 public:
    /** The measurement unit for the periods. 
        NOTE: Used in C# and Java wrappers
     */
    typedef enum
    {
        Tick = 0,
        Minute = 1,
        Hour = 2,
        Day = 3,
        Week = 4,
        Month = 5,
        // Reserved for future use
        Second
    } Unit;

    /** Validates unit and length. */
    static bool validate(Unit unit, int unitLength);

    /** Parse the period name.
    
        @param name     Name of the period (TL, where T is a type and L is a length).
    
        T can be:
        t   ticks
        m   minutes
        H   hours
        D   days
        W   weeks
        M   months
      */
    static bool parsePeriod(const char *name, Unit &unit, int &unitLength);

    /** Gets the start date and time for the candle of the period.

        @param time     The date and time of the tick or candle
        @param start    [output]The start date and time of the candle
        @param end      [output]The end date and time of the candle
        @param startHourOffset
            The start trading day hour offset.
        @param startWeekOffset
            The offset in days of the beginning of the trading week against the
            Sunday. For example, FXCM's trading week starts Saturday 17:00 NYT
            (i.e. Sunday trading day), so the offset is 0 day. This parameter is
            used only in case the unit is Week.
      */
    static bool getCandle(double time, double &start, double &end, Unit unit, int unitLength, int startHourOffset, int startWeekOffset);

    /** Gets the start of the trading day for the specified time. */
    static double getTradingDayStart(double time, int startHourOffset);

    /** Gets the start and the end the trading month for the specified time. */
    static void getTradingMonth(double time, double &start, double &end, int startHourOffset);

    /** Gets the start and the end the trading month for the specified time. */
    static void getTradingYear(double time, double &start, double &end, int startHourOffset);

    /** Checks whether the specified time is in non trading time interval and if it is,
        fills the lastend parameter with the start time of the non trading period.
        Only negative or zero offset is taken into the account, otherwise always returns false.
    */
    static bool isNonTrading(double date, int startHourOffset, double &lastend);
};

} // ~namespace quotesmgr
