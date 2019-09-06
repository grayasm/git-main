#pragma once

#include "IAddRef.h"

namespace quotesmgr
{

/** QuotesManager error object interface

 */
class IError : public IAddRef
{
 public:
    enum Code
    {
        Locked = 0,
        QuotesCatalogBusy = 1,
        QuotesCacheBusy = 2,
        QuotesCacheCorrupted = 3,
        QuotesServerConnectionError = 4,
        LoadingError = 5,
        QuotesLoaderError = 6,
        QuotesNotFound = 7,
        BadArgument = 8,
        OtherError = 9,
        LimitReached = 10
    };

    /** Gets error description
        @return
            0 - terminated C - string;
     */
    virtual const char* getMessage() const = 0;
    /** Gets error code
     */
    virtual Code getCode() const = 0;

    /** Returns specific sub code
        @return
            platform specific number
     */
    virtual int getSubCode() const = 0;

};

} //~namespace quotesmgr
