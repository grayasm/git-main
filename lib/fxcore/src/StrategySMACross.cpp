/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "StrategySMACross.hpp"
#include <math.h>
#include "stream.hpp"
#include "TimeUtils.hpp"
#include "IndicatorBuilder.hpp"



namespace fx
{
    StrategySMACross::StrategySMACross(
        fx::MarketPlugin* plugin,
        const stl::string& instrument,
        const fx::SMA& sma1,
        const fx::SMA& sma2)
    {
        m_plugin = plugin;
        m_instrument = instrument;
        m_sma1 = sma1;
        m_sma2 = sma2;
        // m_tr - default
        m_prevBid1 = 0;
        m_prevBid2 = 0;
        m_closedPL = 0;
        m_closedGPL = 0;
        m_isCancelled = false;
    }

    StrategySMACross::~StrategySMACross()
    {
    }

    void StrategySMACross::Update(const fx::Offer& offer)
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
        if (!m_sma1.IsValid() || !m_sma2.IsValid())
        {
            BuildAllIndicators(offer);
            return;
        }

        // update indicators
        m_sma1.Update(offer);
        m_sma2.Update(offer);

        fx::Price sma1P, sma2P;
        m_sma1.GetValue(sma1P);
        m_sma2.GetValue(sma2P);

        if (m_prevBid1 == 0)
        {
            m_prevBid1 = sma1P.GetSell();
            m_prevBid2 = sma2P.GetSell();
            return;
        }

        double bid1 = sma1P.GetSell();
        double bid2 = sma2P.GetSell();


        // check crossing SMA curves
        if (m_prevBid1 > m_prevBid2 && bid1 <= bid2)
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
        else if (m_prevBid1 < m_prevBid2 && bid1 >= bid2)
        {
            if (!m_tr.IsEmpty())
            {
                fx::Price price(offer.GetAsk(), offer.GetBid());
                m_closedPL += m_tr.GetPL(m_instrument, price);
                m_closedGPL += m_tr.GetGPL(m_instrument, price);

                ClosePosition(offer);
            }

            OpenPosition(offer, true);    // buy
        }


        m_prevBid1 = sma1P.GetSell();
        m_prevBid2 = sma2P.GetSell();
    }

    bool StrategySMACross::IsCancelled() const
    {
        return m_isCancelled;
    }

    double StrategySMACross::GetClosedPL() const
    {
        return m_closedPL;
    }

    double StrategySMACross::GetClosedGPL() const
    {
        return m_closedGPL;
    }

    void StrategySMACross::OpenPosition(const fx::Offer& offer, bool buy)
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

    void StrategySMACross::ClosePosition(const fx::Offer& offer)
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

    void StrategySMACross::BuildAllIndicators(const fx::Offer& offer)
    {
        // may not need to download history data
        if (m_sma1.IsValid() && m_sma2.IsValid())
            return;

        stl::vector<fx::IND*> indicators;
        indicators.push_back(&m_sma1);
        indicators.push_back(&m_sma2);
        IndicatorBuilder::Build(m_plugin, offer, indicators);
    }
} // namespace
