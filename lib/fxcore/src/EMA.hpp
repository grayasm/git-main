/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __EMA_hpp__
#define __EMA_hpp__

#include <list>
#include "IND.hpp"
#include "SMA.hpp"
#include "BARB.hpp"
#include "Offer.hpp"
#include "Price.hpp"



namespace fx
{
    class EMA : public IND
    {
    public:
        typedef fx::SMA::BarType            BarType;
        typedef fx::SMA::PriceOrigin        PriceOrigin;
        typedef std::list<fx::Price>        EMAList;
        // Timeframe is time_t
        
        EMA();
        EMA(const stl::string& instrument,
            int period,
            Timeframe sec,
            BarType barType,
            PriceOrigin po);
        ~EMA();

        EMA(const EMA& tc);
        EMA& operator=(const EMA& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        PriceOrigin GetPriceOrigin() const;
        void GetValue(fx::Price& average) const;

    private:
        void Init();

    private:
        stl::string     m_instrument;
        int             m_period;
        Timeframe       m_timeframe;
        BarType         m_barType;
        PriceOrigin     m_priceOrigin;
        double          m_multiplier;
        // --------------------------
        fx::BARB*       m_bar;
        fx::SMA         m_firstSMA;
        fx::Price       m_currEMA;
        EMAList         m_emaList;
    };
} // namespace

#endif // __EMA_hpp__

