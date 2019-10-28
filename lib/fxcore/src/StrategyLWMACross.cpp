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


#include "StrategyLWMACross.hpp"
#include <math.h>
#include "stream.hpp"
#include "TimeUtils.hpp"
#include "IndicatorBuilder.hpp"


namespace fx
{

    StrategyLWMACross::StrategyLWMACross(
        fx::MarketPlugin* plugin,
        const stl::string& instrument)
    {
        m_plugin = plugin;
        m_instrument = instrument;
        // ----------------------
        m_habar = fx::HABAR(instrument, 14, sys::time::daySEC);
        m_lwma1 = fx::LWMA(instrument, 5, sys::time::daySEC,
                            fx::SMA::BT_HABAR, fx::SMA::PRICE_CLOSE);
        m_lwma2 = fx::LWMA(instrument, 12, sys::time::daySEC,
                            fx::SMA::BT_HABAR, fx::SMA::PRICE_CLOSE);
        // m_tr - default
        m_closedPL = 0;
        m_closedGPL = 0;
        m_isCancelled = false;
        // -------------------
        
    }

    StrategyLWMACross::~StrategyLWMACross()
    {
    }

    void StrategyLWMACross::Update(const fx::Offer& offer)
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
        if (!m_lwma1.IsValid() ||
            !m_lwma2.IsValid() ||
            !m_habar.IsValid())
        {
            BuildAllIndicators(offer);
            return;
        }
       

        bool canOpen = false, isBuy = false;
        if (offer.GetTime() >= m_habar.GetRefTime() + sys::time::daySEC)
        {
            const fx::OHLCPrice& ohlc = m_habar.GetOHLC();
            const fx::BAR::OHLCPriceList& ohlcList = m_habar.GetOHLCList();
            const fx::OHLCPrice& prevohlc = ohlcList.back();
            bool prevLong = (prevohlc.GetAskOpen() < prevohlc.GetAskClose());
            bool currLong = (ohlc.GetAskOpen() < ohlc.GetAskClose());
            canOpen = (prevLong != currLong);
            isBuy = !prevLong && currLong;
        }

        // update indicators
        m_habar.Update(offer);
        m_lwma1.Update(offer);
        m_lwma2.Update(offer);


        //  fx::Price lwma1P, lwma2P;
        //  m_lwma1.GetValue(lwma1P);
        //  m_lwma2.GetValue(lwma2P);

   
        if (canOpen && !isBuy)
        {
            if (!m_tr.IsEmpty())
            {
                fx::Price price(offer.GetAsk(), offer.GetBid());
                m_closedPL += m_tr.GetPL(m_instrument, price);
                m_closedGPL += m_tr.GetGPL(m_instrument, price);

                ClosePosition(offer);
            }

            OpenPosition(offer, false); // sell
        }
        else if (canOpen && isBuy)
        {
            if (!m_tr.IsEmpty())
            {
                fx::Price price(offer.GetAsk(), offer.GetBid());
                m_closedPL += m_tr.GetPL(m_instrument, price);
                m_closedGPL += m_tr.GetGPL(m_instrument, price);

                ClosePosition(offer);
            }

            OpenPosition(offer, true); // buy
        }

        //  m_prevBid1 = lwma1P.GetSell();
        //  m_prevBid2 = lwma2P.GetSell();
    }


    bool StrategyLWMACross::IsCancelled() const
    {
        return m_isCancelled;
    }

    double StrategyLWMACross::GetClosedPL() const
    {
        return m_closedPL;
    }

    double StrategyLWMACross::GetClosedGPL() const
    {
        return m_closedGPL;
    }

    void StrategyLWMACross::OpenPosition(const fx::Offer& offer, bool buy)
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

    void StrategyLWMACross::ClosePosition(const fx::Offer& offer)
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

    void StrategyLWMACross::BuildAllIndicators(const fx::Offer& offer)
    {
        if (m_lwma1.IsValid() &&
            m_lwma2.IsValid() &&
            m_habar.IsValid())
            return;

        stl::vector<fx::IND*> indicators;
        indicators.push_back(&m_lwma1);
        indicators.push_back(&m_lwma2);
        indicators.push_back(&m_habar);
        IndicatorBuilder::Build(m_plugin, offer, indicators);
    }

} // namespace
