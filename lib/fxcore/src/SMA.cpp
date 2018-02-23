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

	SMA::SMA(const misc::string& instrument, int period, PriceOrigin po, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_priceOrigin = po;
		m_timeframe = sec;
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
			m_priceOrigin = tc.m_priceOrigin;
			m_timeframe = tc.m_timeframe;
			m_offerList = tc.m_offerList;
			m_lastOffer = tc.m_lastOffer;
			m_lastSum = tc.m_lastSum;
		}

		return *this;
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

		if (m_lastOffer.GetInstrument().empty())
		{
			m_lastOffer = offer;
			return;
		}
		
		if (m_offerList.empty())
		{
			const misc::time& prevtime = m_lastOffer.GetTime();
			const misc::time& currtime = offer.GetTime();			

			// begin at full hour even if the timeframe is ex: 3min
			if ((currtime.totime_t() - prevtime.totime_t() >= m_timeframe) &&
				(currtime.hour_() != prevtime.hour_()))
			{
				m_offerList.push_back(offer);
				m_lastOffer = offer;
			}

			return;
		}


		const misc::time& lasttime = m_offerList.back().GetTime();
		const misc::time& prevtime = m_lastOffer.GetTime();
		const misc::time& currtime = offer.GetTime();

		if (currtime.totime_t() - lasttime.totime_t() >= m_timeframe)
		{
			if (m_priceOrigin == PRICE_CLOSE)
				m_offerList.push_back(m_lastOffer);
			else // PRICE_OPEN
				m_offerList.push_back(offer);

			// keep period constant
			if (m_offerList.size() > m_period)
				m_offerList.pop_front();
			
			// calculate the sum
			if (m_offerList.size() == m_period)
			{
				double buy = 0, sell = 0;
				for (OfferList::iterator it = m_offerList.begin();
					it != m_offerList.end(); ++it)
				{
					buy += it->GetAsk();
					sell += it->GetBid();
				}
				m_lastSum = fx::Price(buy, sell);
			}
		}

		m_lastOffer = offer;
	}

	void SMA::GetValue(fx::Price& average) const
	{
		if (m_period < 2 || m_offerList.size() != m_period)
			throw misc::exception("SMA is invalid");

		double buy = (m_lastSum.GetBuy() + m_lastOffer.GetAsk()) / (m_period + 1);
		double sell = (m_lastSum.GetSell() + m_lastOffer.GetBid()) / (m_period + 1);
		
		average = fx::Price(buy, sell);
	}

	void SMA::Init()
	{
		m_period = -1;
		m_priceOrigin = PRICE_CLOSE;
		m_timeframe = 0;
		// m_offerList; - clean
		// m_lastOffer; - default
		m_lastSum = fx::Price(0, 0);
	}
} // namespace
