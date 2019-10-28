/*
    Copyright (C) 2018 Mihai Vasilian

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

#include "StrategyRenkoAtr.hpp"
#include <math.h>
#include "stream.hpp"
#include "TimeUtils.hpp"
#include "IndicatorBuilder.hpp"


namespace fx
{
    StrategyRenkoAtr::StrategyRenkoAtr(
        fx::MarketPlugin* plugin,
        const stl::string& instrument,
        double renkoMin,
        int openHour,
        int closeHour)
    {
        m_plugin = plugin;
        m_instrument = instrument;
        m_renkoMin = renkoMin;
        m_atr14 = fx::ATR(m_instrument, 14, sys::time::hourSEC);
        m_sma7 = fx::SMA(m_instrument, 7, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
        /// ---------------------
        // m_tr - clean;
        // m_initialOffer - clean;
        // m_range - default with FLT_MAX;
        m_totalPL = 0;
        m_closedPL = 0;
        m_closedGPL = 0;
        m_openHour = openHour;
        m_closeHour = closeHour;
        m_isCancelled = false;
    }

    StrategyRenkoAtr::~StrategyRenkoAtr()
    {
    }
    
    void StrategyRenkoAtr::Update(const fx::Offer& offer)
    {
        /*  In case the market plugin (session) encounters an error
            the strategy is disabled until the issue is fixed.
        */
        if (m_isCancelled)
            return;

        // check the instrument
        if (offer.GetInstrument() != m_instrument)
            return;

        // Build all indicators
        if (!m_atr14.IsValid() || !m_sma7.IsValid())
        {
            BuildAllIndicators(offer);
            return;
        }


        // update ATR, SMA
        m_atr14.Update(offer);
        m_sma7.Update(offer);

        
        // Renko brick is ATR(14)
        double price2pip = 1. / offer.GetPointSize();
        double pip2price = offer.GetPointSize();
        double renkoPL = 0;
        m_atr14.GetValue(renkoPL);
        renkoPL *= price2pip;
        if (renkoPL < m_renkoMin)
            renkoPL = m_renkoMin;


        // Time of the offer
        sys::time tnow = offer.GetTime();
        bool canOpen = (tnow.hour_() >= m_openHour && tnow.hour_() < m_closeHour);

        
        // Over the night without position at market
        if (!canOpen && m_tr.IsEmpty())
        {
            // reset protective range over the night
            if (m_range.IsMinValid() || m_range.IsMaxValid())
                m_range = fx::Range();
            return;
        }


        // Waiting to enter the market
        if (m_tr.IsEmpty())
        {
            // start a new trading day?
            if (m_initialOffer.GetInstrument().empty())
            {
                m_initialOffer = offer;
                return;
            }

            double pips = (offer.GetAsk() - m_initialOffer.GetAsk()) * price2pip;

            if (pips > renkoPL && canOpen)
            {
                // check if range is in place
                canOpen = !m_range.IsMaxValid() ||
                    (offer.GetAsk() > m_range.GetMax().GetBuy());

                // buy higher than SMA value
                if (canOpen && m_range.IsMaxValid())
                {
                    fx::Price smaval;
                    m_sma7.GetValue(smaval);
                    canOpen = offer.GetAsk() > smaval.GetBuy();
                }

                if (canOpen)
                    OpenPosition(offer, true);

            }
            else if (pips < -renkoPL && canOpen)
            {
                // check if range is in place
                canOpen = !m_range.IsMinValid() ||
                    (offer.GetAsk() < m_range.GetMin().GetBuy());

                // sell lower than SMA value
                if (canOpen && m_range.IsMinValid())
                {
                    fx::Price smaval;
                    m_sma7.GetValue(smaval);
                    canOpen = offer.GetAsk() < smaval.GetBuy();
                }

                if (canOpen)
                    OpenPosition(offer, false);

            }
            
            m_totalPL = 0;
            return;
        }


        // A transaction is ongoing
        fx::Price curprice(offer.GetAsk(), offer.GetBid());
        double curPL = m_tr.GetPL(m_instrument, curprice);
        double curGPL = m_tr.GetGPL(m_instrument, curprice);
        double diffPL = curPL - m_totalPL;

        if (diffPL > renkoPL)
        {
            int inc = diffPL / renkoPL;
            m_totalPL += (inc * renkoPL);
            return;
        }

        bool canClose = (diffPL < -2 * renkoPL);
        if (canClose)
        {
            bool buy = m_tr.GetBegin()->IsBuy();

            ClosePosition(offer);

            m_closedPL += curPL;
            m_closedGPL += curGPL;
            stl::cout << "curPL=" << curPL << " closedGPL=" << m_closedGPL
                << std::endl;


            if (!m_tr.IsEmpty())
                return; // error during ClosePosition!


            // if positive, reset previous range (if any)
            if (curPL > 0)
            {
                m_range = fx::Range();
            }
            else
            {
                if (buy)
                {
                    fx::Price limprice(
                        offer.GetAsk() + renkoPL * pip2price,
                        offer.GetBid() + renkoPL * pip2price);
                    m_range.SetMax(limprice);
                }
                else
                {
                    fx::Price limprice(
                        offer.GetAsk() - renkoPL * offer.GetPointSize(),
                        offer.GetBid() - renkoPL * offer.GetPointSize());
                    m_range.SetMin(limprice);
                }
            }


            // do not open in a range
            if (canOpen)
            {
                bool isBuy = !buy; // enter opposite direction
                if (isBuy && m_range.IsMaxValid())
                {
                    canOpen = (offer.GetAsk() > m_range.GetMax().GetBuy());

                    // buy higher than SMA value
                    fx::Price smaval;
                    m_sma7.GetValue(smaval);
                    if (canOpen)
                        canOpen = offer.GetAsk() > smaval.GetBuy();
                }
                else if (!isBuy && m_range.IsMinValid())
                {
                    canOpen = (offer.GetAsk() < m_range.GetMin().GetBuy());

                    // sell lower than SMA value
                    fx::Price smaval;
                    m_sma7.GetValue(smaval);
                    if (canOpen)
                        canOpen = offer.GetAsk() < smaval.GetBuy();
                }
            }

            // Either we are ranging or trading day has ended.
            if (!canOpen)
            {
                m_initialOffer = fx::Offer();
                m_totalPL = 0;
            }
            else
            {
                // Trading still possible
                bool isBuy = !buy;    // enter opposite direction
                OpenPosition(offer, isBuy);
                m_totalPL = 0;
            }
        } // (diffPL < -2 * renkoPL)
    } // Update(Offer)

    bool StrategyRenkoAtr::IsCancelled() const
    {
        return m_isCancelled;
    }

    double StrategyRenkoAtr::GetClosedPL() const
    {
        return m_closedPL;
    }

    double StrategyRenkoAtr::GetClosedGPL() const
    {
        return m_closedGPL;
    }

    void StrategyRenkoAtr::OpenPosition(const fx::Offer& offer, bool buy)
    {
        stl::vector<fx::Position> result;
        int ret = m_plugin->OpenPosition(offer, 1, buy, result);

        if (ret != 0)
        {
            m_isCancelled = true;
            return;
        }

        for (size_t i = 0; i < result.size(); ++i)
            m_tr.Add(result[i]);
    }

    void StrategyRenkoAtr::ClosePosition(const fx::Offer& offer)
    {
        stl::vector<fx::Position>& npos =
            const_cast<stl::vector<fx::Position>&>(m_tr.GetPositions());

        stl::vector<fx::Position>::iterator it = npos.begin();
        for (; it != npos.end(); /*erase*/)
        {
            const fx::Position& pos = *it;

            stl::vector<fx::Position> result;
            int ret = m_plugin->ClosePosition(offer, pos, result);

            if (ret != 0)
            {
                m_isCancelled = true;
                return;
            }

            stl::vector<fx::Position>::iterator tmp = npos.erase(it);
            it = tmp;
        }
    }
    
    void StrategyRenkoAtr::BuildAllIndicators(const fx::Offer& offer)
    {
        // may not need to download history data
        if (m_atr14.IsValid() && m_sma7.IsValid())
            return;

        stl::vector<fx::IND*> indicators;
        indicators.push_back(&m_atr14);
        indicators.push_back(&m_sma7);
        IndicatorBuilder::Build(m_plugin, offer, indicators);
    }

} // namespace
