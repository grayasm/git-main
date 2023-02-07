/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __StrategySMACross_hpp__
#define __StrategySMACross_hpp__

#include "autoptr.hpp"
#include "Offer.hpp"
#include "Transaction.hpp"
#include "MarketPlugin.hpp"
#include "SMA.hpp"

namespace fx
{
    class StrategySMACross
    {
    public:
        typedef stl::autoptr<StrategySMACross> Ptr;

        StrategySMACross(
            fx::MarketPlugin* plugin,
            const stl::string& instrument,
            const fx::SMA& sma1,
            const fx::SMA& sma2);

        ~StrategySMACross();
        StrategySMACross(const StrategySMACross&) = delete;
        StrategySMACross& operator=(const StrategySMACross&) = delete;

        void Update(const fx::Offer& offer);
        bool IsCancelled() const;
        double GetClosedPL() const;
        double GetClosedGPL() const;

    private:
        void OpenPosition(const fx::Offer& offer, bool buy);
        void ClosePosition(const fx::Offer& offer);
        void BuildAllIndicators(const fx::Offer& offer);

    private:
        fx::MarketPlugin*       m_plugin;
        stl::string             m_instrument;
        fx::SMA                 m_sma1;
        fx::SMA                 m_sma2;
        /// ---------------------------
        fx::Transaction         m_tr;
        double                  m_prevBid1;
        double                  m_prevBid2;
        double                  m_closedPL;
        double                  m_closedGPL;
        bool                    m_isCancelled;
    };
} // namespace


#endif // __StrategySMACross_hpp__
