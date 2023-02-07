/*
Copyright (C) 2019 Mihai Vasilian
*/

/*
    J.Welles Wilder Jr. - New Concepts in Technical Trading Systems
    Section VI / pag.63
    The Relative Strength Index (RSI)

    The equation for the RSI is:
    RSI = 100 - [ 100 : (1 + RS) ];  where RS is:
    RS = Average of 14 day's closes UP : Average of 14 day's close DOWN;    
*/


#ifndef __RSI_hpp__
#define __RSI_hpp__

#include "string.hpp"
#include "IND.hpp"
#include "BAR.hpp"


namespace fx
{
    class RSI : public IND
    {
    public:
        // Timeframe is time_t

        RSI();
        RSI(const stl::string& instrument, int period, Timeframe sec);

        ~RSI();
        RSI(const RSI& tc);
        RSI& operator=(const RSI& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        double GetRSI() const;      // RSI for the period
        double GetRSI2() const;     // RSI for the last tick data

    private:
        void Init();

    private:
        stl::string         m_instrument;
        int                 m_period;
        Timeframe           m_timeframe;
        // -----------------------------
        fx::BAR             m_bar;
        bool                m_useSmoothing; // use the last calculated average
        double              m_medUp;        // average up difference
        double              m_medDown;      // average down difference
        double              m_RSI;          // RSI for the period
        double              m_rsi;          // RSI for the last tick data
    };
} // namespace

#endif // __RSI_hpp__