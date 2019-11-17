/*
    Copyright (C) 2019 Mihai Vasilian

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program. If not, see http://www.gnu.org/licenses/.

    contact: grayasm@gmail.com
*/

#ifndef __StrategyEMACross_hpp__
#define __StrategyEMACross_hpp__

#include "autoptr.hpp"
#include "Offer.hpp"
#include "Transaction.hpp"
#include "MarketPlugin.hpp"
#include "EMA.hpp"
#include "RSI.hpp"

namespace fx
{
    class StrategyEMACross
    {
    public:
        typedef stl::autoptr<StrategyEMACross> Ptr;

        StrategyEMACross(
            fx::MarketPlugin* plugin,
            const stl::string& instrument,
            const fx::EMA& ema5,
            const fx::EMA& ema50,
            const fx::EMA& ema100,
            const fx::RSI& rsi5);

        ~StrategyEMACross();
        StrategyEMACross(const StrategyEMACross&) = delete;
        StrategyEMACross& operator=(const StrategyEMACross&) = delete;

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
        fx::EMA                 m_ema5;
        fx::EMA                 m_ema50;
        fx::EMA                 m_ema100;
        fx::RSI                 m_rsi5;
        /// ---------------------------
        fx::BAR                 m_bar;
        fx::Transaction         m_tr;
        double                  m_closedPL;
        double                  m_closedGPL;
        bool                    m_isCancelled;
        sys::time               m_prevTime; // time of last bad trade
    };
} // namespace


#endif // __StrategyEMACross_hpp__
