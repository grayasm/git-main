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

	ATR formula:
	https://en.wikipedia.org/wiki/Average_true_range

	TR = max[ (currH - currL), abs(currH - prevC), abs(currL - prevC)]
	ATR = ( ATR(t-1) x (n - 1) + TR(t) ) / n
	ATR(t-1) = sum(TRi)/n  where i=1->n
*/

#include "ATR.hpp"
#include <algorithm>

namespace fx
{
	ATR::ATR()
	{
		Init();
	}

	ATR::ATR(const misc::string& instrument, int period, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_period = period + 1;	// the 1st previous close is extra
		m_timeframe = sec;
	}

	ATR::~ATR()
	{
	}

	ATR::ATR(const ATR& tc)
	{
		*this = tc;
	}

	ATR& ATR::operator=(const ATR& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
			m_priceList = tc.m_priceList;
			m_lastOHLC = tc.m_lastOHLC;
			m_medATR = tc.m_medATR;
			m_ATR = tc.m_ATR;
		}

		return *this;
	}

	const misc::string& ATR::GetInstrument() const
	{
		return m_instrument;
	}

	int ATR::GetPeriod() const
	{
		return m_period - 1;
	}

	ATR::Timeframe ATR::GetTimeframe() const
	{
		return m_timeframe;
	}

	bool ATR::IsValid() const
	{
		return (m_period - 1 > 1 && m_period == m_priceList.size() && m_ATR > 0);
	}

	void ATR::Update(const fx::Offer& offer)
	{
		if (m_period - 1 < 2)
			throw misc::exception("ATR is invalid");

		if (m_instrument != offer.GetInstrument())
			throw misc::exception("ATR offer is invalid");

		if (m_lastOHLC.GetInstrument().empty())
		{
			// partial initialization to track the time up to full hour
			m_lastOHLC.SetInstrument(offer.GetInstrument().c_str());
			m_lastOHLC.SetTime(offer.GetTime());

			return;
		}

		if (m_priceList.empty())
		{
			const misc::time& prevtime = m_lastOHLC.GetTime();
			const misc::time& currtime = offer.GetTime();

			// create first OHLC at full hour
			if (m_lastOHLC.GetBidOpen() == 0 &&
				prevtime.hour_() == currtime.hour_())
			{
				// keep timeframe 0
				m_lastOHLC.SetTime(offer.GetTime());
				return;
			}

			// is it the first OHLC
			if (m_lastOHLC.GetBidOpen() == 0)
			{
				// reset the OHLC
				m_lastOHLC.SetTime(offer.GetTime());

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

				return;
			}

			// a new timeframe
			if (currtime.totime_t() - prevtime.totime_t() >= m_timeframe)
			{
				m_priceList.push_back(m_lastOHLC);

				// reset the OHLC
				m_lastOHLC.SetTime(offer.GetTime());

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

				return;
			}
			
			// not a new timeframe
			double bid = offer.GetBid();
			double ask = offer.GetAsk();
			m_lastOHLC.SetBidClose(bid);
			m_lastOHLC.SetAskClose(ask);

			if (m_lastOHLC.GetBidHigh() < bid)
				m_lastOHLC.SetBidHigh(bid);
			if (m_lastOHLC.GetBidLow() > bid)
				m_lastOHLC.SetBidLow(bid);
			if (m_lastOHLC.GetAskHigh() < ask)
				m_lastOHLC.SetAskHigh(ask);
			if (m_lastOHLC.GetAskLow() > ask)
				m_lastOHLC.SetAskLow(ask);

			return;
		}


		// not the first OHLC, the period has data

		// lasttime is 1 timeframe behind m_lastOHLC
		// m_lastOHLC time is beginning of current timeframe
		const misc::time& lasttime = m_priceList.back().GetTime();
		const misc::time& prevtime = m_lastOHLC.GetTime();
		const misc::time& currtime = offer.GetTime();

		// a new timeframe
		if (currtime.totime_t() - prevtime.totime_t() >= m_timeframe)
		{
			if (m_priceList.size() == m_period)
			{
				// calculate the median ATR
				// TR = max[(currH - currL), abs(currH - prevC), abs(currL - prevC)]
				// ATR = (ATR(t - 1) x (n - 1) + TR(t)) / n		(true average)
				// ATR(t - 1) = sum(TRi) / n  where i = 1->n	(median)

				m_medATR = 0;
				m_ATR = 0;

				OHLCPriceList::iterator previt = m_priceList.begin();
				OHLCPriceList::iterator currit = previt;
				++currit;

				for (; currit != m_priceList.end(); ++previt, ++currit)
				{
					double prevC = previt->GetBidClose();
					double currH = currit->GetBidHigh();
					double currL = currit->GetBidLow();

					double v1 = currH - currL;
					double v2 = fabs(currH - prevC);
					double v3 = fabs(currL - prevC);

					double TR = std::max(v1, std::max(v2, v3));

					m_medATR += TR;
				}

				double n = m_period - 1.0;
				m_medATR /= n;

				// current TR
				double prevC = m_priceList.back().GetBidClose();
				double currH = m_lastOHLC.GetBidHigh();
				double currL = m_lastOHLC.GetBidLow();

				double v1 = currH - currL;
				double v2 = fabs(currH - prevC);
				double v3 = fabs(currL - prevC);

				double TR = std::max(v1, std::max(v2, v3));

				m_ATR = (m_medATR * (n - 1) + TR) / n;
			}

			m_priceList.push_back(m_lastOHLC);

			// keep period constant
			if (m_priceList.size() > m_period)
				m_priceList.pop_front();


			// reset the OHLC
			m_lastOHLC.SetTime(offer.GetTime());

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

			return;
		}

		// not a new timeframe
		double bid = offer.GetBid();
		double ask = offer.GetAsk();
		m_lastOHLC.SetBidClose(bid);
		m_lastOHLC.SetAskClose(ask);

		if (m_lastOHLC.GetBidHigh() < bid)
			m_lastOHLC.SetBidHigh(bid);
		if (m_lastOHLC.GetBidLow() > bid)
			m_lastOHLC.SetBidLow(bid);
		if (m_lastOHLC.GetAskHigh() < ask)
			m_lastOHLC.SetAskHigh(ask);
		if (m_lastOHLC.GetAskLow() > ask)
			m_lastOHLC.SetAskLow(ask);
	}

	void ATR::GetValue(double& average) const
	{
		if (m_period -1 < 2 || m_priceList.size() != m_period)
			throw misc::exception("SMA is invalid");

		// return last ATR (true average)
		average = m_ATR;
	}

	void ATR::Init()
	{
		m_period = -1;
		m_timeframe = 0;
		// m_priceList; - clean
		// m_lastOHLC; - default
		m_medATR = 0;
		m_ATR = 0;
	}
} // namespace
