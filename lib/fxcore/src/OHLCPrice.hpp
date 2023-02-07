/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __OHLCPrice_hpp__
#define __OHLCPrice_hpp__

#include "string.hpp"
#include "time.hpp"

namespace fx
{
    class OHLCPrice
    {
    public:
        OHLCPrice();
        OHLCPrice(
            const char* instrument,         // 'EUR/USD'
            const char* timeframe,          // m1 , H1 , ...
            sys::time time,                 // UTC
            double BidOpen, double BidHigh, double BidLow, double BidClose,
            double AskOpen, double AskHigh, double AskLow, double AskClose,
            int volume);

        OHLCPrice(const OHLCPrice& tc);
        OHLCPrice& operator=(const OHLCPrice& tc);
        ~OHLCPrice();

        const stl::string& GetInstrument() const;
        void SetInstrument(const char* instrument);

        const stl::string& GetTimeframe() const;
        void SetTimeframe(const char* timeframe);

        const sys::time& GetTime() const;
        void SetTime(const sys::time& val);

        double GetBidOpen() const;
        void SetBidOpen(double val);

        double GetBidHigh() const;
        void SetBidHigh(double val);

        double GetBidLow() const;
        void SetBidLow(double val);

        double GetBidClose() const;
        void SetBidClose(double val);

        double GetAskOpen() const;
        void SetAskOpen(double val);

        double GetAskHigh() const;
        void SetAskHigh(double val);

        double GetAskLow() const;
        void SetAskLow(double val);

        double GetAskClose() const;
        void SetAskClose(double val);

        int GetVolume() const;
        void SetVolume(int val);

    private:
        void Init();

    private:
        stl::string     m_instrument;
        stl::string     m_timeframe;
        sys::time       m_time;
        double          m_bidOpen, m_bidHigh, m_bidLow, m_bidClose;
        double          m_askOpen, m_askHigh, m_askLow, m_askClose;
        int             m_volume;
    };
} // namespace

#endif // __OHLCPrice_hpp__
