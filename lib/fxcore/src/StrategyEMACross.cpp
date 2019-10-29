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


    This strategy was described here, like this:
    https://forums.babypips.com/t/strategy/252434/4

    Price above 100 ema.
    Price above 50 ema.
    rsi (5) >= 50
    D1 current candle is bullish (wait for close)
    Then place entry buy order at last D1 max+2 pips
    Cancel the entry if not triggered by the D1 candle.
    Exit at price crossing the 5ema (both TP/SL)
    Similar logic for going short.
    Which pairs and date interval did you test?
    I can at least confirm the 70% success rate.
*/

#include "StrategyEMACross.hpp"
#include <math.h>
#include "stream.hpp"
#include "TimeUtils.hpp"
#include "IndicatorBuilder.hpp"



namespace fx
{
    StrategyEMACross::StrategyEMACross(
        fx::MarketPlugin* plugin,
        const stl::string& instrument,
        const fx::EMA& ema5,
        const fx::EMA& ema50,
        const fx::EMA& ema100)
    {
        m_plugin = plugin;
        m_instrument = instrument;
        m_ema5 = ema5;
        m_ema50 = ema50;
        m_ema100 = ema100;
        m_bar = fx::BAR(instrument, 1, ema100.GetTimeframe());
        // m_tr - default
        m_closedPL = 0;
        m_closedGPL = 0;
        m_isCancelled = false;
    }

    StrategyEMACross::~StrategyEMACross()
    {
    }

    // ask = buy
    // bid = sell
    void StrategyEMACross::Update(const fx::Offer& offer)
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
        if (!m_ema5.IsValid() || !m_ema50.IsValid() || !m_ema100.IsValid())
        {
            BuildAllIndicators(offer);
            return;
        }

        // update indicators
        m_ema5.Update(offer);
        m_ema50.Update(offer);
        m_ema100.Update(offer);

        // update last bar
        m_bar.Update(offer);

        if (m_bar.GetOHLCList().empty()) // == 1
            return;

        fx::Price ema5P, ema50P, ema100P;
        m_ema5.GetValue(ema5P);
        m_ema50.GetValue(ema50P);
        m_ema100.GetValue(ema100P);

        const fx::OHLCPrice& prevbar = *(m_bar.GetOHLCList().begin());
        const fx::OHLCPrice& currbar = m_bar.GetOHLC();
       
        double pipdiff = 2 * offer.GetPointSize();

        if (m_tr.IsEmpty() &&
            offer.GetAsk() /*buy*/ > ema100P.GetBuy() &&
            offer.GetAsk() /*buy*/ > ema50P.GetBuy() &&
            prevbar.GetAskOpen() < prevbar.GetAskClose() &&
            offer.GetAsk() > prevbar.GetAskClose() + pipdiff)
        {
            OpenPosition(offer, true);    // buy
        }
        else if (m_tr.IsEmpty() &&
            offer.GetBid() /*sell*/ < ema100P.GetSell() &&
            offer.GetBid() /*sell*/ < ema50P.GetSell() &&
            prevbar.GetBidOpen() > prevbar.GetBidClose() &&
            offer.GetBid() /*sell*/ < prevbar.GetBidClose() - pipdiff)
        {
            OpenPosition(offer, false); // sell
        }
        else if (!m_tr.IsEmpty() &&
            m_tr.GetPositions().at(0).IsBuy() &&
            offer.GetAsk() /*buy*/ < ema5P.GetBuy())
        {
            fx::Price price(offer.GetAsk(), offer.GetBid());
            m_closedPL += m_tr.GetPL(m_instrument, price);
            m_closedGPL += m_tr.GetGPL(m_instrument, price);

            ClosePosition(offer);
        }
        else if (!m_tr.IsEmpty() &&
            !m_tr.GetPositions().at(0).IsBuy() &&
            offer.GetBid() /*sell*/ > ema5P.GetSell())
        {
            fx::Price price(offer.GetAsk(), offer.GetBid());
            m_closedPL += m_tr.GetPL(m_instrument, price);
            m_closedGPL += m_tr.GetGPL(m_instrument, price);

            ClosePosition(offer);
        }
    }

    bool StrategyEMACross::IsCancelled() const
    {
        return m_isCancelled;
    }

    double StrategyEMACross::GetClosedPL() const
    {
        return m_closedPL;
    }

    double StrategyEMACross::GetClosedGPL() const
    {
        return m_closedGPL;
    }

    void StrategyEMACross::OpenPosition(const fx::Offer& offer, bool buy)
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

    void StrategyEMACross::ClosePosition(const fx::Offer& offer)
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

    void StrategyEMACross::BuildAllIndicators(const fx::Offer& offer)
    {
        // may not need to download history data
        if (m_ema5.IsValid() && m_ema50.IsValid() && m_ema100.IsValid())
            return;

        stl::vector<fx::IND*> indicators;
        indicators.push_back(&m_ema5);
        indicators.push_back(&m_ema50);
        indicators.push_back(&m_ema100);
        IndicatorBuilder::Build(m_plugin, offer, indicators);
    }
} // namespace
