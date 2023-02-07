/*
Copyright (C) 2017 Mihai Vasilian
*/

#ifndef __Offer_hpp__
#define __Offer_hpp__

#include "string.hpp"
#include "time.hpp"

namespace fx
{
    class Offer
    {
    public:
        Offer();

        Offer(  const stl::string& offerID,
                const stl::string& instrument,
                int precision,
                double pointSize,
                const sys::time& time,
                double bid,
                double ask,
                double vol,
                bool isTradingOpen);

        Offer(const Offer& tc);
        Offer& operator=(const Offer& tc);
        ~Offer();

        const stl::string& GetOfferID() const;
        void SetOfferID(const stl::string& id);

        const stl::string& GetInstrument() const;
        void SetInstrument(const stl::string& instrument);

        double GetPrecision() const;
        void SetPrecision(double precision);

        const sys::time& GetTime() const;
        void SetTime(const sys::time& time);

        double GetPointSize() const;
        void SetPointSize(double pipsize);

        double GetBid() const;
        void SetBid(double bid);

        double GetAsk() const;
        void SetAsk(double ask);

        double GetVolume() const;
        void SetVolume(double vol);

        bool GetIsTradingOpen() const;
        void SetIsTradingOpen(bool isOpen);

    private:
        void Init();

    private:
        stl::string         m_offerID;
        stl::string         m_instrument;
        int                 m_precision;
        sys::time           m_time;
        double              m_pointSize;
        double              m_bid;        // sell at bid
        double              m_ask;        // buy at ask
        double              m_volume;
        bool                m_isTradingOpen;
    };
} // namespace

#endif // __Offer_hpp__
