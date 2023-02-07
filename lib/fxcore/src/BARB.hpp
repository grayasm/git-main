/*
Copyright (C) 2018 Mihai Vasilian
*/

/*
    BARB will serve as the base class for all candle data structures.
    Each candle has a current bar and a period for which it stores the bars.
    IsNew will tell if the offer will paint a new bar or not.
*/


#ifndef __BARB_hpp__
#define __BARB_hpp__

#include "list.hpp"
#include "autoptr.hpp"
#include "IND.hpp"
#include "OHLCPrice.hpp"


namespace fx
{
    class BARB : public fx::IND
    {
    public:
        typedef stl::autoptr<BARB>          Ptr;
        typedef stl::list<fx::OHLCPrice>    OHLCPriceList; // requires pop_front()

        BARB();
        BARB(const BARB&);
        BARB& operator=(const BARB&);
        virtual ~BARB();

        // --- additional virtual table ---
        virtual bool IsNew(const fx::Offer& offer) const = 0;
        virtual const fx::OHLCPrice& GetOHLC() const = 0;
        virtual const OHLCPriceList& GetOHLCList() const = 0;
        // --- end of additional virtual table ---
    };
} // namespace


#endif // __BARB_hpp__
