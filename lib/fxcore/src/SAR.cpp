/*
	Copyright (C) 2018 Mihai Vasilian

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com

	"New Concepts in Technical Trading Systems.pdf"
	by J. Welles Wilder Jr.

	SAR formula:
	-------------
	SAR(i) = SAR(i-1) + AF ( EP - SAR(i-1) );

	if position is buy: SAR(i) <= min(L(i-1), L(i-2));
	if position is sell: SAR(i) >= max(H(i-1), H(i-2));

	EP: extreme price of the trade (Highest for a buy, Lowest for a sell)
	AF: start with +0.02 and increment with +0.02 for each new High/Low
		maximum value should be +0.2
	SAR:never move SAR(i) higher than min of today and yesterday low (if buy)
		never move SAR(i) lower than max of today and yesterday high (if sell)

	Today and yesterday means also current candle and last candle.
	------------

	The indicator normally does not need a period. This class has a period to
	calibrate the indicator before using it. SAR works like a trading strategy.
	You can trade in the direction of the indicator and reverse together
	with it when SAR is touched.
*/


#include "SAR.hpp"

namespace fx
{
	SAR::SAR()
	{
		Init();
	}

	SAR::SAR(const stl::string& instrument, int period, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
        m_bar = fx::BAR(instrument, period, sec);
	}

	SAR::~SAR()
	{
	}

	SAR::SAR(const SAR& tc)
	{
		Init();

		*this = tc;
	}

	SAR& SAR::operator=(const SAR& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
            m_bar = tc.m_bar;
			m_sarList = tc.m_sarList;
			m_isBuy = tc.m_isBuy;
			m_AF = tc.m_AF;
			m_EP = tc.m_EP;
			m_SAR = tc.m_SAR;
		}
		return *this;
	}

	const stl::string& SAR::GetInstrument() const
	{
		return m_instrument;
	}

	int SAR::GetPeriod() const
	{
		return m_period;
	}

	SAR::Timeframe SAR::GetTimeframe() const
	{
		return m_timeframe;
	}

	bool SAR::IsValid() const
	{
		return (m_period > 1 &&
			m_period == m_bar.GetOHLCList().size() &&
			m_period == m_sarList.size() &&
            m_SAR.GetBuy() > 0 &&
            m_SAR.GetSell() > 0);
	}

	void SAR::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw stl::exception("SAR offer is invalid");


        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        if (!isNew)
        {
            m_bar.Update(offer);
        }
        else
        {
            /*	Current OHLC bar is complete.
                Calculate the SAR.
            */
            const fx::OHLCPrice& ohlc = m_bar.GetOHLC();
            const fx::BAR::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

            if (ohlcList.empty())	// first SAR value is simple
            {
                m_isBuy = ohlc.GetAskOpen() < ohlc.GetAskClose();
                m_AF = 0.00;    // avoid 0.04 on next candle

                if (m_isBuy)
                {
                    m_EP = fx::Price(ohlc.GetAskHigh(), ohlc.GetBidHigh());
                    m_SAR = fx::Price(ohlc.GetAskLow(), ohlc.GetBidLow());
                }
                else
                {
                    m_EP = fx::Price(ohlc.GetAskLow(), ohlc.GetBidLow());
                    m_SAR = fx::Price(ohlc.GetAskHigh(), ohlc.GetBidHigh());
                }
            }
            else
            {
                // track EP & AF
                if (m_isBuy && ohlc.GetBidHigh() > m_EP.GetSell())
                {
                    m_EP = fx::Price(ohlc.GetAskHigh(), ohlc.GetBidHigh());
                    m_AF += 0.02;
                }
                else if (!m_isBuy && ohlc.GetAskLow() < m_EP.GetBuy())
                {
                    m_EP = fx::Price(ohlc.GetAskLow(), ohlc.GetBidLow());
                    m_AF += 0.02;
                }
                if (m_AF < 0.02) m_AF = 0.02;	// SAR reversed in this timeframe (0.00)
                if (m_AF > 0.20) m_AF = 0.2;	// SAR maxim value


                // SAR = SARp + AF (EP - SARp);
                double buy = m_SAR.GetBuy() + m_AF * (m_EP.GetBuy() - m_SAR.GetBuy());
                double sell = m_SAR.GetSell() + m_AF * (m_EP.GetSell() - m_SAR.GetSell());


                /*	Never move SAR above lower of current or previous ohlc if long.
                    Never move SAR below higher of current or previous ohlc if short.
                */
                fx::Price LP(0, 0);		// the limit
                const fx::OHLCPrice& prevohlc = ohlcList.back();
                if (m_isBuy)
                    LP = fx::Price(
                        stl::min(prevohlc.GetAskLow(), ohlc.GetAskLow()),
                        stl::min(prevohlc.GetBidLow(), ohlc.GetBidLow()));
                else
                    LP = fx::Price(
                        stl::max(prevohlc.GetAskHigh(), ohlc.GetAskHigh()),
                        stl::max(prevohlc.GetBidHigh(), ohlc.GetBidHigh()));


                if ((m_isBuy && sell > LP.GetSell()) ||
                    (!m_isBuy && buy < LP.GetBuy()))
                {
                    buy = LP.GetBuy();
                    sell = LP.GetSell();
                }

                m_SAR = fx::Price(buy, sell);
            }

            // handle the list
            m_sarList.push_back(m_SAR);

            // keep period constant
            if (m_sarList.size() > m_period)
                m_sarList.pop_front();

            // paint a new bar
            m_bar.Update(offer);
        }


		// check every Offer to see if SAR reversed
		if (!m_bar.GetOHLCList().empty())
		{
			if ((m_isBuy && offer.GetBid() < m_SAR.GetSell()) ||
				(!m_isBuy && offer.GetAsk() > m_SAR.GetBuy()))
			{
				m_isBuy = !m_isBuy;
				m_AF = 0.00;	// avoid 0.04 on next candle
				// m_EP - assign to SAR and then update
				m_SAR = m_EP;
				m_EP = fx::Price(offer.GetAsk(), offer.GetBid());

				m_sarList.push_back(m_SAR);
				if (m_sarList.size() > m_period)
					m_sarList.pop_front();
			}
		}
	}

	const sys::time& SAR::GetRefTime() const
	{
		return m_bar.GetRefTime();
	}

	bool SAR::GetIsBuy() const
	{
		return m_isBuy;
	}

	void SAR::GetValue(fx::Price& sar) const
	{
        if (m_period < 2 ||
            m_bar.GetOHLCList().size() != m_period ||
            m_SAR.GetBuy() == 0 ||
            m_SAR.GetSell() == 0)
        {
            throw stl::exception("SAR is invalid");
        }

		sar = m_SAR;
	}

	void SAR::GetOHLC(fx::OHLCPrice& ohlc) const
	{
		if (m_period < 2 || m_bar.GetOHLCList().size() != m_period)
			throw stl::exception("SAR is invalid");

		ohlc = m_bar.GetOHLC();
	}

	void SAR::GetEP(fx::Price& ep) const
	{
		ep = m_EP;
	}

	void SAR::GetAF(double& af) const
	{
		af = m_AF;
	}

	void SAR::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
        // m_bar - default
		// m_sarList - clean
		m_isBuy = false;
		m_AF = 0.02;
		// m_EP - default
		// m_SAR - default
	}
} // namespace
