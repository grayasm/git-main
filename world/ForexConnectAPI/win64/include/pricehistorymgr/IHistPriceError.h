#pragma once

#include "IHistPriceAddRef.h"

// Forward declaration
namespace quotesmgr
{
class IError;
}

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

/** The price history communicator error object interface.
    It may be used to get detailed information about errors.
 */
class HIST_PRICE_API IError : public IAddRef
{
 public:
    enum Code
    {
        QuotesManagerError = 0,
        NotReady = 1,
        BadArguments = 2,
        OtherError = 3
    };

    /** Gets the error description.
        @return
            0 - terminated C - string;
     */
    virtual const char* getMessage() const = 0;

    /** Gets error code
     */
    virtual Code getCode() const = 0;

    /** Gets QuotesManagerError object if error code is QuotesManagerError
        @return
            NULL - if error code is not QuotesManagerError
    */
    virtual quotesmgr::IError* getQuotesManagerError() = 0;

 protected:
    virtual ~IError() {}
};

}
