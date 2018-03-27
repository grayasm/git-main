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
	along with this program; if not, write to the Free Software Foundation,
	Inc. 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/


#include "OHLCBar.hpp"

namespace fx
{
	OHLCBar::OHLCBar()
	{
		Init();
	}

	OHLCBar::OHLCBar(const misc::string& instrument, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_timeframe = sec;

		//----------------------
		misc::string sTimeframe;
		if (sec == misc::time::minSEC) sTimeframe = "m1";
		if (sec == misc::time::hourSEC) sTimeframe = "H1";
		if (sec == misc::time::daySEC) sTimeframe = "D1"; // not tested
		else sTimeframe = "Unknown"; // not supported
		
		m_lastOHLC.SetInstrument(instrument.c_str());
		m_lastOHLC.SetTimeframe(sTimeframe.c_str());
	}

	OHLCBar::~OHLCBar()
	{
	}

	OHLCBar::OHLCBar(const OHLCBar& tc)
	{
		Init();

		*this = tc;
	}

	OHLCBar& OHLCBar::operator=(const OHLCBar& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_timeframe = tc.m_timeframe;
			m_reftime = tc.m_reftime;
			m_lastOHLC = tc.m_lastOHLC;
		}
		return *this;
	}

	void OHLCBar::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw misc::exception("OHLCBar offer is invalid");

		// begin at next timeframe normalized up to daily candle
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
	}

	const fx::OHLCPrice& OHLCBar::GetOHLC() const
	{
		// for .GetBidOpen() == 0 current Bar is uninitialized
		return m_lastOHLC;
	}

	void OHLCBar::Init()
	{
		m_instrument = "";
		m_timeframe = 0;
		// m_reftime - default
		m_lastOHLC = fx::OHLCPrice("", "", misc::time(),
									0, 0, 0, 0,
									0, 0, 0, 0,
									0);
	}

} // namespace