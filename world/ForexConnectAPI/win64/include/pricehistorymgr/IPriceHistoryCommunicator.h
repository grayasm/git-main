#pragma once

#include "IHistPriceAddRef.h"
#include "IHistPriceError.h"

/* Forward declaration section */
namespace quotesmgr
{
    class IQuotesManager;
}

/* ForexConnect classes forward declaration */
class IO2GTimeframe;
class IO2GMarketDataSnapshotResponseReader;

/* A quote date type definition */
typedef double DATE;

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

class IPriceHistoryCommunicatorRequest;
class IPriceHistoryCommunicatorResponse;
class IPriceHistoryCommunicatorListener;
class IPriceHistoryCommunicatorStatusListener;
class ITimeframeFactory;

/** The main class of the API. It provides the following functionality:
    - register/unregister user defineds listeners;
    - creating and sending of history requests;
    - cancelling of a request sending.
    
    Use PriceHistoryCommunicatorFactory to create a new instance.
    It must be released after the usage. 

    The communicator may be used only when it's ready (see isReady method).
 */
class HIST_PRICE_API IPriceHistoryCommunicator : public pricehistorymgr::IAddRef
{
 public:
    /** Subscribes a history communicator listener. */
    virtual void addListener(IPriceHistoryCommunicatorListener *listener) = 0;

    /** Unsubscribes a history communicator listener. */
    virtual void removeListener(IPriceHistoryCommunicatorListener *listener) = 0;

    /** Subscribes a history communicator listener. */
    virtual void addStatusListener(IPriceHistoryCommunicatorStatusListener *statusListener) = 0;

    /** Unsubscribes a history communicator listener. */
    virtual void removeStatusListener(IPriceHistoryCommunicatorStatusListener *statusListener) = 0;

    /** Gets an instance of the timeframe factory */
    virtual ITimeframeFactory* getTimeframeFactory() = 0;

    /** Creates a new history request.

        @param instrument
            The instrument
        @param timeframe
            The timeframe
        @param from
            The start date of history, 0 if not defined
        @param to
            The end date of history, 0 if not defined
        @param quotesCount
            The integer value which limits a number of quotes, 0 if not defined
        @param error
            [output] If not NULL and an error occurred it will contain a pointer
            to a detailed error description object. It must be released by a 
            caller after the use.
        @return
            The method returns a request object. If an error occurred then returns NULL. 
            The object returned has a reference count equal to 1 and it must be released
            after usage by a caller. It may be released just after sending if it's not 
            required anymore.
     */
    virtual IPriceHistoryCommunicatorRequest* createRequest(const char *instrument,
                                                IO2GTimeframe *timeframe,
                                                DATE from, DATE to,
                                                int quotesCount, IError **error) = 0;
    /** Sends a request.

        @param request
            The request
        @param error
            [output] If not NULL and an error occurred it will contain a pointer
            to a detailed error description object. It must be released by a caller 
            after the use.
        @return
            true - if operation is succeeded
            false - otherwise. See output error parameter for error description.
     */
    virtual bool sendRequest(IPriceHistoryCommunicatorRequest *request,
                             IError **error) = 0;

    /** Cancels a request processing.
        After the method returned the communicator guarantees that there will be no 
        more any listener calls for this request.

        @param request
            The request to cancel
     */
    virtual void cancelRequest(IPriceHistoryCommunicatorRequest *request) = 0;

    /** Checks if the communicator is ready. It cannot be used (e.g. requests created and sent)
        if it's not ready.

        @return
            true - if it's ready
     */
    virtual bool isReady() const = 0;

    /** Creates a response reader object.

        @param response
            The response to read
        @param error
            [output] If not NULL and an error occurred it will contain a pointer to a 
            detailed error description object.
        @return
            The reader response object. It must be released by a caller after the use. 
            If an error occurred returns NULL, in this case error output parameter (if not NULL) 
            contains a pointer to a detailed error description object.
    */
    virtual IO2GMarketDataSnapshotResponseReader* createResponseReader(IPriceHistoryCommunicatorResponse *response,
                                                                       IError **error) = 0;

    /** Gets an instance of QuotesManager used to get a history. It may be used to get
        additional services (e.g. get a size of local quotes storage and clear it).
        It CANNOT be used to execute quotes related tasks - the operation will complete
        with an error. Returned instance must be released by a caller after the use.
     */
    virtual quotesmgr::IQuotesManager* getQuotesManager() = 0;

 protected:
     virtual ~IPriceHistoryCommunicator() { }
};



}
