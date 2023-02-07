/*
Copyright (C) 2018 Mihai Vasilian
*/

/*
    IND will serve as the base class for all indicators.
    It defines all methods necessary to build one without knowing anything
    more about it.
    Using this abstraction it is possible to build a big number of different
    indicators (passed around as a vector) using one set of history data.
*/

#ifndef __IND_hpp__
#define __IND_hpp__

#include "string.hpp"
#include "time.hpp"
#include "Offer.hpp"


namespace fx
{
    class IND
    {
    public:
        typedef time_t            Timeframe;

        IND();
        IND(const IND&);
        IND& operator=(const IND&);
        virtual ~IND();
        
        // --- virtual table ---        
        virtual const stl::string& GetInstrument() const = 0;
        virtual int GetPeriod() const = 0;
        virtual Timeframe GetTimeframe() const = 0;
        virtual bool IsValid() const = 0;
        virtual void Update(const fx::Offer& offer) = 0;
        virtual const sys::time& GetRefTime() const = 0; // begin of current candle
        // --- end of virtual table ---
    };
} // namespace

#endif // __IND_hpp__
