#pragma once

#include "IHistPriceAddRef.h"

class IO2GTimeframe;

/* A quote date type definition */
typedef double DATE;

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

/** Price History Request interface. 
    Use IPriceHistoryCommunicator to create and send a request.
 */
class HIST_PRICE_API IPriceHistoryCommunicatorRequest : public pricehistorymgr::IAddRef
{
 public:
    /** Gets instrument. */
    virtual const char* getInstrument() const = 0;

    /** Gets start date of history. */
    virtual DATE getFromDate() const = 0;

    /** Gets end date of history. */
    virtual DATE getToDate() const = 0;

    /** Gets a number which limits a number of quotes. */
    virtual int getQuotesCount() const = 0;

    /** Gets history timeframe.
        It must be released by a caller after the use.
     */
    virtual IO2GTimeframe* getTimeframe() = 0;

 protected:
    virtual ~IPriceHistoryCommunicatorRequest() { }
};

} //~namespace pricehistorymgr

