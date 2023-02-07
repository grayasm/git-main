/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __BAR_hpp__
#define __BAR_hpp__

#include "string.hpp"
#include "time.hpp"
#include "BARB.hpp"
#include "Offer.hpp"
#include "OHLCPrice.hpp"


namespace fx
{

    class BAR : public BARB
    {
    public:
        typedef stl::autoptr<BAR>            Ptr;

        BAR();
        BAR(const stl::string& instrument, int period, Timeframe sec);
        ~BAR();
        BAR(const BAR& tc);
        BAR& operator=(const BAR& tc);
        
        // --- IND virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of IND virtual table ---

        // --- BARB virtual table ---
        bool IsNew(const fx::Offer& offer) const;
        const fx::OHLCPrice& GetOHLC() const;
        const OHLCPriceList& GetOHLCList() const;
        // --- end of BARB virtual table ---
        

    private:
        void Init();

    private:
        stl::string         m_instrument;
        int                 m_period;
        time_t              m_timeframe;
        // ----------------------------
        sys::time           m_reftime;
        fx::OHLCPrice       m_lastOHLC;
        OHLCPriceList       m_priceList;
    };
} // namespace

#endif // __BAR_hpp__
