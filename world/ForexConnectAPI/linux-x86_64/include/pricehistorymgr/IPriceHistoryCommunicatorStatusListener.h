#pragma once

#include "IHistPriceAddRef.h"

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

/** The interface provides method signatures to process 
    notifications about PriceHistoryCommunicator ready state

    The interface must be implemented by a user code and registered using
    IPriceHistoryCommunicator::addStatusListener.
 */
class IPriceHistoryCommunicatorStatusListener : public pricehistorymgr::IAddRef
{
 public:

    /** Called when a PriceHistoryCommunicator changes ready state.
        @param ready
            true  - if communicator becoames ready
            false - otherwise
   
     */
    virtual void onCommunicatorStatusChanged(bool ready) = 0;

    /** Called when a PriceHistoryCommunicator initialization failed
        Also it means that Communicator becomes not ready (callback onCommunicatorStatusChanged will not appear)

        @param error
            The error   
    */
    virtual void onCommunicatorInitFailed(IError *error) = 0;

 protected:

    virtual ~IPriceHistoryCommunicatorStatusListener() { }
};

}
