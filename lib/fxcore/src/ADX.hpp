/*
Copyright (C) 2019 Mihai Vasilian
*/

#ifndef __ADX_hpp__
#define __ADX_hpp__

#include "BAR.hpp"
#include "list.hpp"

namespace fx
{
    class ADX : public IND
    {
    public:
        ADX();
        ADX(const stl::string& instrument, int period, Timeframe sec);
        ~ADX();
        ADX(const ADX& tc);
        ADX& operator=(const ADX& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        double GetADX() const;      // ADX for the period
        double GetADX2() const;     // ADX for the period with the last tick
        double GetADXR() const;     // ADXR for the period
        double GetADXR2() const;    // ADXR for the period with the last tick
        double GetDIUp() const;     // Return m_DI_up
        double GetDIDown() const;   // Return m_DI_down w/o sign

    private:
        void Init();

    private:
        stl::string         m_instrument;
        int                 m_period;
        Timeframe           m_timeframe;
        // -----------------------------
        fx::BAR             m_bar;
        bool                m_useAccumulation;
        double              m_DM_up;        // +DM directional movement (up)
        double              m_DM_down;      // -DM directional movement (down)
        double              m_TR;           // TR true range
        double              m_DI_up;        // +DI directional indicator (up)
        double              m_DI_down;      // -DI directional indicator (down)
        double              m_DI_diff;      // difference abs value between +DI -DI
        double              m_DI_add;       // sum abs value of +DI -DI
        stl::list<double>   m_DX_list;      // DX directional movement index (period values)
        double              m_ADX;          // ADX average directional movement index
        double              m_adx;          // ADX for the latest tick data
        stl::list<double>   m_ADX_list;     // ADX period values to calculate ADXR
        double              m_ADXR;         // ADXR average directional movement index rating
        double              m_adxr;         // ADXR for the latest tick data
    };
} // namespace

#endif // __ADX_hpp__
