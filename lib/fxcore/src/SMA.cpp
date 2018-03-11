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
*/

#include "SMA.hpp"


namespace fx
{
	SMA::SMA()
	{
		Init();
	}

	SMA::SMA(const misc::string& instrument, int period, Timeframe sec, PriceOrigin po)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
		m_priceOrigin = po;
	}

	SMA::~SMA()
	{

	}

	SMA::SMA(const SMA& tc)
	{
		*this = tc;
	}

	SMA& SMA::operator=(const SMA& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
			m_priceOrigin = tc.m_priceOrigin;
			m_reftime = tc.m_reftime;
			m_priceO = tc.m_priceO;
			m_priceC = tc.m_priceC;
			m_offerList = tc.m_offerList;
			m_lastSum = tc.m_lastSum;
		}

		return *this;
	}

	const misc::string& SMA::GetInstrument() const
	{
		return m_instrument;
	}

	int SMA::GetPeriod() const
	{
		return m_period;
	}

	SMA::Timeframe SMA::GetTimeframe() const
	{
		return m_timeframe;
	}

	SMA::PriceOrigin SMA::GetPriceOrigin() const
	{
		return m_priceOrigin;
	}

	bool SMA::IsValid() const
	{
		return (m_period > 1 && m_period == m_offerList.size());
	}

	void SMA::Update(const fx::Offer& offer)
	{
		if (m_period < 2)
			throw misc::exception("SMA is invalid");

		if (m_instrument != offer.GetInstrument())
			throw misc::exception("SMA offer is invalid");

		// begin at full hour even if the timeframe is ex: 3min
		if (m_reftime.totime_t() == 0)
		{
			m_reftime = offer.GetTime();
			m_reftime -= m_reftime.sec_();
			m_reftime += (60 - m_reftime.min_()) * misc::time::minSEC;

			return;
		}

		const misc::time& currtime = offer.GetTime();
		if (currtime < m_reftime)
			return;
		
		misc::time nextt = m_reftime + m_timeframe;

		// get the open price (only the first candle goes here)
		if (m_priceO.GetBuy() == 0 && currtime >= m_reftime)
		{
			m_priceO = fx::Price(offer.GetAsk(), offer.GetBid());
		}
		// every price can close the candle
		else if (currtime < nextt)
		{
			m_priceC = fx::Price(offer.GetAsk(), offer.GetBid());
		}
		// candle has just closed
		else if (currtime >= nextt)
		{
			// handle the list
			if (m_priceOrigin == PRICE_OPEN)
				m_offerList.push_back(m_priceO);
			else
				m_offerList.push_back(m_priceC);

			// keep period constant
			if (m_offerList.size() > m_period)
				m_offerList.pop_front();

			// new candle has just started
			m_priceO = fx::Price(offer.GetAsk(), offer.GetBid());
			m_priceC = m_priceO; // updated for GetValue(..)

			// current candle open (including weekend gap)
			while (currtime >= m_reftime + m_timeframe)
				m_reftime += m_timeframe;

			
			// calculate the sum
			if (m_offerList.size() == m_period)
			{
				double buy = 0, sell = 0;
				PriceList::iterator it = m_offerList.begin();
				for (; it != m_offerList.end(); ++it)
				{
					buy += it->GetBuy();
					sell += it->GetSell();
				}
				m_lastSum = fx::Price(buy, sell);
			}
		}
	}

	void SMA::GetValue(fx::Price& average) const
	{
		if (m_period < 2 || m_offerList.size() != m_period)
			throw misc::exception("SMA is invalid");

		double buy = 0, sell = 0;

		if (m_priceOrigin == PRICE_OPEN)
		{
			buy = (m_lastSum.GetBuy() + m_priceO.GetBuy()) / (m_period + 1);
			sell = (m_lastSum.GetSell() + m_priceO.GetSell()) / (m_period + 1);
		}
		else
		{
			buy = (m_lastSum.GetBuy() + m_priceC.GetBuy()) / (m_period + 1);
			sell = (m_lastSum.GetSell() + m_priceO.GetSell()) / (m_period + 1);
		}		
		
		average = fx::Price(buy, sell);
	}

	const misc::time& SMA::GetRefTime() const
	{
		return m_reftime;
	}

	void SMA::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
		m_priceOrigin = PRICE_CLOSE;
		// m_reftime - default
		m_priceO = fx::Price(0, 0);
		m_priceC = fx::Price(0, 0);
		// m_offerList - clean
		m_lastSum = fx::Price(0, 0);
	}
} // namespace
