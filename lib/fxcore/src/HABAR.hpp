/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __HABAR_hpp__
#define __HABAR_hpp__

#include "BARB.hpp"
#include "BAR.hpp"

namespace fx
{
    class HABAR : public BARB
    {
    public:
        typedef stl::autoptr<HABAR>    Ptr;

        HABAR();
        HABAR(const stl::string& instrument, int period, Timeframe sec);
        ~HABAR();
        HABAR(const HABAR& tc);
        HABAR& operator=(const HABAR& tc);

        // --- IND virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of IND virtual table ---

        // --- BARB virtual table ---
        bool IsNew(const fx::Offer& offer) const override;
        const fx::OHLCPrice& GetOHLC() const override;
        const OHLCPriceList& GetOHLCList() const override;
        // --- end of BARB virtual table ---

    private:
        void Init();

    private:
        fx::BAR             m_bar;
        fx::OHLCPrice       m_lastHA;
        OHLCPriceList       m_haList;
    };
} // namespace

#endif // __HABAR_hpp__
