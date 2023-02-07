/*
Copyright (C) 2019 Mihai Vasilian
*/

/*
    J.W.Wilder "New Concepts in Technical Trading Systems", page 53
    --------------------
    The Momentum Concept
    --------------------
    One of the most useful concepts in technical tradig is that of momentum;
    yet for many traders momentum is also one of the hardest concepts to
    understand. Momentum can be thought of as acceleration and deceleration.

    The (MF) momentum factor is the difference between the close price today
    and the close price two days ago. (Note: choose period=2 for MF)
*/

#ifndef __MF_hpp__
#define __MF_hpp__

#include "BAR.hpp"
#include "list.hpp"

namespace fx
{
    class MF : public IND
    {
    public:
        MF();
        MF(const stl::string& instrument, int period, Timeframe sec); // use period = 2
        ~MF();
        MF(const MF& tc);
        MF& operator=(const MF& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        double GetMF() const;   // Return m_MF (at the candle close)
        double GetMF2() const;  // Return m_mf (at the last tick)

    private:
        void Init();

    private:
        stl::string         m_instrument;
        int                 m_period;
        Timeframe           m_timeframe;
        // -----------------------------
        fx::BAR             m_bar;
        double              m_MF;   // Momentum Factor (at candle close)
        double              m_mf;   // Momentum Factor (at the last tick)
    };
} // namespace

#endif // __MF_hpp__
