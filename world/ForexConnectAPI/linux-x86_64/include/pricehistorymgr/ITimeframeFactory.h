#pragma once

#include "IHistPriceAddRef.h"
#include "IHistPriceError.h"

class IO2GTimeframe;

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

class IError;

/** The factory class for any stadard or custom timeframes. */
class HIST_PRICE_API ITimeframeFactory : public IAddRef
{
 public:
    /** Creates timeframe from string
        @param timeframe
            The unique identifier of the time frame
        @param error
            [output] If not NULL and an error occurred it will contain a pointer
            to a detailed error description object. It must be released by a 
            caller after the use.
        @return
            new timefame instance
            NULL - if input string is invalid
     
     */
    virtual IO2GTimeframe* create(const char *timeframe, pricehistorymgr::IError **error) = 0;

    /** Creates timeframe
        @param timeframeUnit
            The time measurement unit
        @param timeframeSize
            The number of units in the time frame
        @param error
            [output] If not NULL and an error occurred it will contain a pointer
            to a detailed error description object. It must be released by a 
            caller after the use.
        @return
            new timefame instance
            NULL - if input parameters are invalid
     */
    virtual IO2GTimeframe* create(O2GTimeframeUnit timeframeUnit, int timeframeSize, pricehistorymgr::IError **error) = 0;

 protected:

    virtual ~ITimeframeFactory() { }
};

}
