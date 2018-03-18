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

	PSAR formula:
	-------------
	SAR(i) = SAR(i-1) + AF ( EP - SAR(i-1));
	SAR(i) > Low(i-1) || SAR(i) > Low(i-2) -> SAR(i) = min(Low(i-2), Low(i-1));

	EP: highest trade's price for a long, or
		lowest trade's price for a short;
	AF: initial is 0.02 and is increased with 0.02 for each new High/Low
		up to its maximum value of 0.2;
	SAR:	first SAR(i) value is the High/Low of the trade of previous position;
	SAR:	never move the SAR(i) above the lowest position between today and
		yesterday, e.g. SAR(i) < min(Low(i-2), Low(i-1)) always;
*/


#include "PSAR.hpp"

namespace fx
{
	PSAR::PSAR()
	{
		Init();
	}

	PSAR::PSAR(
		const misc::string& instrument,
		Timeframe sec,
		double af,
		double afInc,
		double afMax,
		const fx::Price& sar)
	{
		Init();
		
		
	}

	PSAR::~PSAR()
	{
	}

	PSAR::PSAR(const PSAR& tc)
	{
		Init();

		*this = tc;
	}

	PSAR& PSAR::operator=(const PSAR& tc)
	{
		if (this != &tc)
		{
			
		}
		return *this;
	}

	const misc::string& PSAR::GetInstrument() const
	{
		return m_instrument;
	}

	int PSAR::GetPeriod() const
	{
		return m_period;
	}

	PSAR::Timeframe PSAR::GetTimeframe() const
	{
		return m_timeframe;
	}

	bool PSAR::IsValid() const
	{

	}

	void PSAR::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw misc::exception("PSAR offer is invalid");

		//	PSAR is already active. Normalize it to last valid timeframe.
		if (m_reftime.totime_t() == 0)
		{
			m_reftime = offer.GetTime();

			if (m_timeframe >= misc::time::minSEC)
				m_reftime -= m_reftime.sec_();

			if (m_timeframe >= misc::time::hourSEC)
				m_reftime -= m_reftime.min_() * misc::time::minSEC;

			if (m_timeframe >= misc::time::daySEC)
				m_reftime -= m_reftime.hour_() * misc::time::hourSEC;
		}

		const misc::time& currtime = offer.GetTime();
		
		misc::time nextt = m_reftime + m_timeframe;

		if (currtime < nextt)
		{
			double bid = offer.GetBid();
			double ask = offer.GetAsk();

			if (m_ohlcList.empty())
				m_ohlcList.push_back(fx::OHLCPrice());
			
			fx::OHLCPrice& ohlc = m_ohlcList.back();

			if (ohlc.GetBidOpen() == 0) // uninitialized
			{
				ohlc.SetBidOpen(bid);
				ohlc.SetBidHigh(bid);
				ohlc.SetBidLow(bid);
				ohlc.SetBidClose(bid);

				ohlc.SetAskOpen(ask);
				ohlc.SetAskHigh(ask);
				ohlc.SetAskLow(ask);
				ohlc.SetAskClose(ask);
			}
			else
			{
				ohlc.SetBidClose(bid);
				ohlc.SetAskClose(ask);

				if (ohlc.GetBidHigh() < bid)
					ohlc.SetBidHigh(bid);
				if (ohlc.GetBidLow() > bid)
					ohlc.SetBidLow(bid);
				if (ohlc.GetAskHigh() < ask)
					ohlc.SetAskHigh(ask);
				if (ohlc.GetAskLow() > ask)
					ohlc.SetAskLow(ask);
			}

			/*	Include the current INCOMPLETE OHLC bar into PSAR.
			*/
			if (m_ohlcList.size() == m_period)
			{
				double bSAR = m_SAR.GetBuy();
				double bEP = m_EP.GetBuy();
				double bLL = 0;
			}
		}
	}

	const misc::time& PSAR::GetRefTime() const
	{
		return m_reftime;
	}
} // namespace
