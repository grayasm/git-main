/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __StrategyLWMACross_hpp__
#define __StrategyLWMACross_hpp__

#include "autoptr.hpp"
#include "MarketPlugin.hpp"
#include "HABAR.hpp"
#include "LWMA.hpp"
#include "Transaction.hpp"


namespace fx
{
    class StrategyLWMACross
    {
    public:
        typedef stl::autoptr<StrategyLWMACross> Ptr;

        StrategyLWMACross(
            fx::MarketPlugin* plugin,
            const stl::string& instrument);

        ~StrategyLWMACross();
        StrategyLWMACross(const StrategyLWMACross&) = delete;
        StrategyLWMACross& operator=(const StrategyLWMACross&) = delete;

        void Update(const fx::Offer& offer);
        bool IsCancelled() const;
        double GetClosedPL() const;
        double GetClosedGPL() const;

    private:
        void OpenPosition(const fx::Offer& offer, bool buy);
        void ClosePosition(const fx::Offer& offer);
        void BuildAllIndicators(const fx::Offer& offer);


    private:
        fx::MarketPlugin*   m_plugin;
        stl::string         m_instrument;
        // ------------------------------
        fx::HABAR           m_habar;
        fx::LWMA            m_lwma1;
        fx::LWMA            m_lwma2;
        fx::Transaction     m_tr;
        double              m_closedPL;
        double              m_closedGPL;
        bool                m_isCancelled;
        // ------------------------------
    };
} // namespace

#endif // __StrategyLWMACross_hpp__
