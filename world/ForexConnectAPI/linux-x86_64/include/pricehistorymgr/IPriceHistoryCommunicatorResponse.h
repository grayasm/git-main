#pragma once

#include "IHistPriceAddRef.h"

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

/** The Price History response. The user defined listener 
    (IPriceHistoryCommunicatorListener) receives an instance of the interface
    when a request completed.

    The interface doesn't define any members, use IPriceHistoryCommunicator::createResponseReader
    to create a reader to process it.
 */
class HIST_PRICE_API IPriceHistoryCommunicatorResponse : public pricehistorymgr::IAddRef
{
 protected:
    virtual ~IPriceHistoryCommunicatorResponse() {}
};

}
