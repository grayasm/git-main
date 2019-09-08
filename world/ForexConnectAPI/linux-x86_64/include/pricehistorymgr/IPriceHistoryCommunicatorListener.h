#pragma once

#include "IHistPriceAddRef.h"

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

class IPriceHistoryCommunicatorRequest;
class IPriceHistoryCommunicatorResponse;

/** The interface provides method signatures to process 
    notifications about request completions, failures and cancellations.

    The interface must be implemented by a user code and registered using
    IPriceHistoryCommunicator::addListener.
 */
class IPriceHistoryCommunicatorListener : public pricehistorymgr::IAddRef
{
 public:
    /** Called when a requets execution is completed.

        @param request
            The request
        @param response
            The response
     */
    virtual void onRequestCompleted(IPriceHistoryCommunicatorRequest *request,
                                    IPriceHistoryCommunicatorResponse *response) = 0;

    /** Called when a requets execution is failed.

        @param request
            The request 
        @param error
            The error
     */
    virtual void onRequestFailed(IPriceHistoryCommunicatorRequest *request, IError *error) = 0;

    /** Called when a request execution is cancelled.

        @param request
            The request    
     */
    virtual void onRequestCancelled(IPriceHistoryCommunicatorRequest *request) = 0;

 protected:
    virtual ~IPriceHistoryCommunicatorListener() { }
};


}
