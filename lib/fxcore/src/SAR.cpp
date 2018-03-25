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

	SAR::SAR(const misc::string& instrument, int period, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
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
			m_reftime = tc.m_reftime;
			m_lastOHLC = tc.m_lastOHLC;
			m_priceList = tc.m_priceList;
			m_sarList = tc.m_sarList;
			m_isBuy = tc.m_isBuy;
			m_AF = tc.m_AF;
			m_EP = tc.m_EP;
			m_SAR = tc.m_SAR;
		}
		return *this;
	}

	const misc::string& SAR::GetInstrument() const
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
		return (m_period - 1 > 1 &&
			m_period == m_priceList.size() &&
			m_period == m_sarList.size());
	}

	void SAR::Update(const fx::Offer& offer)
	{
		if (m_period - 1 < 2)
			throw misc::exception("SAR is invalid");

		if (m_instrument != offer.GetInstrument())
			throw misc::exception("SAR offer is invalid");

		// begin at next timeframe normalized up to daily candle;
		if (m_reftime.totime_t() == 0)
		{
			m_reftime = offer.GetTime();

			if (m_timeframe >= misc::time::minSEC)
				m_reftime -= m_reftime.sec_();
			if (m_timeframe >= misc::time::hourSEC)
				m_reftime -= (m_reftime.min_() * misc::time::minSEC);
			if (m_timeframe >= misc::time::daySEC)
				m_reftime -= (m_reftime.hour_() * misc::time::hourSEC);

			m_reftime += m_timeframe;
		}

		const misc::time& currtime = offer.GetTime();

		// wait for the reference time to begin with
		if (currtime < m_reftime)
			return;

		misc::time nextt = m_reftime + m_timeframe;
		if (currtime < nextt)
		{
			double bid = offer.GetBid();
			double ask = offer.GetAsk();

			if (m_lastOHLC.GetBidOpen() == 0) // uninitialized
			{
				m_lastOHLC.SetBidOpen(bid);
				m_lastOHLC.SetBidHigh(bid);
				m_lastOHLC.SetBidLow(bid);
				m_lastOHLC.SetBidClose(bid);

				m_lastOHLC.SetAskOpen(ask);
				m_lastOHLC.SetAskHigh(ask);
				m_lastOHLC.SetAskLow(ask);
				m_lastOHLC.SetAskClose(ask);

				m_EP = fx::Price(offer.GetAsk(), offer.GetBid());
			}
			else
			{
				m_lastOHLC.SetBidClose(bid);	// can close anytime soon
				m_lastOHLC.SetAskClose(ask);

				if (bid > m_lastOHLC.GetBidHigh())
				{
					m_lastOHLC.SetBidHigh(bid);
					m_lastOHLC.SetAskHigh(ask);
				}
				else if (bid < m_lastOHLC.GetBidLow())
				{
					m_lastOHLC.SetBidLow(bid);
					m_lastOHLC.SetAskLow(ask);
				}
			}
		}
		else if (currtime >= nextt)
		{
			/*	Current OHLC bar is complete (e.g. m_lastOHLC).
				Calculate the SAR.
			*/
			if (m_priceList.empty())	// first SAR value is simple
			{
				m_isBuy = m_lastOHLC.GetAskOpen() < m_lastOHLC.GetAskClose();
				m_AF = 0.02;

				if (m_isBuy)
				{
					m_EP = fx::Price(m_lastOHLC.GetAskHigh(), m_lastOHLC.GetBidHigh());
					m_SAR = fx::Price(m_lastOHLC.GetAskLow(), m_lastOHLC.GetBidLow());
				}
				else
				{
					m_EP = fx::Price(m_lastOHLC.GetAskLow(), m_lastOHLC.GetBidLow());
					m_SAR = fx::Price(m_lastOHLC.GetAskHigh(), m_lastOHLC.GetBidHigh());
				}
			}
			else
			{
				// track EP & AF
				if (m_isBuy && m_lastOHLC.GetBidHigh() > m_EP.GetSell())
				{
					m_EP = fx::Price(m_lastOHLC.GetAskHigh(), m_lastOHLC.GetBidHigh());
					m_AF += 0.02;
				}
				else if (!m_isBuy && m_lastOHLC.GetAskLow() < m_EP.GetBuy())
				{
					m_EP = fx::Price(m_lastOHLC.GetAskLow(), m_lastOHLC.GetBidLow());
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
				const fx::OHLCPrice& ohlc = m_priceList.back();
				if (m_isBuy)
					LP = fx::Price(
					misc::min(ohlc.GetAskLow(), m_lastOHLC.GetAskLow()),
					misc::min(ohlc.GetBidLow(), m_lastOHLC.GetBidLow()));
				else
					LP = fx::Price(
					misc::max(ohlc.GetAskHigh(), m_lastOHLC.GetAskHigh()),
					misc::max(ohlc.GetBidHigh(), m_lastOHLC.GetBidHigh()));


				if ((m_isBuy && sell > LP.GetSell()) ||
					(!m_isBuy && buy < LP.GetBuy()))
				{
					buy = LP.GetBuy();
					sell = LP.GetSell();
				}

				m_SAR = fx::Price(buy, sell);
			}

			// handle the list
			m_priceList.push_back(m_lastOHLC);
			m_sarList.push_back(m_SAR);

			// keep period constant (sarList adds new SAR frequently)
			while (m_priceList.size() > m_period)
				m_priceList.pop_front();
			while (m_sarList.size() > m_period)
				m_sarList.pop_front();

			// new candle has just started
			double bid = offer.GetBid();
			double ask = offer.GetAsk();

			m_lastOHLC.SetBidOpen(bid);
			m_lastOHLC.SetBidHigh(bid);
			m_lastOHLC.SetBidLow(bid);
			m_lastOHLC.SetBidClose(bid);

			m_lastOHLC.SetAskOpen(ask);
			m_lastOHLC.SetAskHigh(ask);
			m_lastOHLC.SetAskLow(ask);
			m_lastOHLC.SetAskClose(ask);

			// current candle open (including weekend gap)
			while (currtime >= m_reftime + m_timeframe)
				m_reftime += m_timeframe;
		}


		// check every Offer to see if SAR reversed
		if (!m_priceList.empty())
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
				while (m_sarList.size() > m_period)
					m_sarList.pop_front();
			}
		}
	}

	const misc::time& SAR::GetRefTime() const
	{
		return m_reftime;
	}

	bool SAR::GetIsBuy() const
	{
		return m_isBuy;
	}

	void SAR::GetValue(fx::Price& sar) const
	{
		if (m_period - 1 < 2 || m_priceList.size() != m_period)
			throw misc::exception("SAR is invalid");

		sar = m_SAR;
	}

	void SAR::GetOHLC(fx::OHLCPrice& ohlc) const
	{
		if (m_period - 1 < 2 || m_priceList.size() != m_period)
			throw misc::exception("SAR is invalid");

		ohlc = m_priceList.back();
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
		// m_reftime - default
		m_lastOHLC = fx::OHLCPrice("", "", misc::time(),
									0, 0, 0, 0,
									0, 0, 0, 0,
									0);
		// m_priceList - clean
		// m_sarList - clean
		m_isBuy = false;
		m_AF = 0.02;
		// m_EP - default
		// m_SAR - default
	}
} // namespace
