#pragma once

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

/** The common interface for objects with reference counting.
    
 */
class HIST_PRICE_API IAddRef
{
 public:
    /** Adds a reference. */
    virtual long addRef() = 0;

    /** Releases a reference. */
    virtual long release() = 0;

 protected:
    virtual ~IAddRef() { }
};

}

