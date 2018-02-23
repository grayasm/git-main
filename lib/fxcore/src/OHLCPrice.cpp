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


#include "OHLCPrice.hpp"


namespace fx
{
	OHLCPrice::OHLCPrice()
	{
		Init();
	}

	OHLCPrice::OHLCPrice
	(
		const char* instrument,			// 'EUR/USD'
		const char* timeframe,			// m1 , H1 , ...
		misc::time time,				// UTC
		double BidOpen, double BidHigh, double BidLow, double BidClose,
		double AskOpen, double AskHigh, double AskLow, double AskClose,
		int volume
	)
	{
		m_instrument = instrument;
		m_timeframe = timeframe;
		m_time = time;
		m_bidOpen = BidOpen;
		m_bidHigh = BidHigh;
		m_bidLow = BidLow;
		m_bidClose = BidClose;
		m_askOpen = AskOpen;
		m_askHigh = AskHigh;
		m_askLow = AskLow;
		m_askClose = AskClose;
		m_volume = volume;
	}

	OHLCPrice::OHLCPrice(const OHLCPrice& tc)
	{
		*this = tc;
	}

	OHLCPrice& OHLCPrice::operator = (const OHLCPrice& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_timeframe = tc.m_timeframe;
			m_time = tc.m_time;
			m_bidOpen = tc.m_bidOpen;
			m_bidHigh = tc.m_bidHigh;
			m_bidLow = tc.m_bidLow;
			m_bidClose = tc.m_bidClose;
			m_askOpen = tc.m_askOpen;
			m_askHigh = tc.m_askHigh;
			m_askLow = tc.m_askLow;
			m_askClose = tc.m_askClose;
			m_volume = tc.m_volume;
		}
		return *this;
	}

	OHLCPrice::~OHLCPrice()
	{
	}

	const misc::string& OHLCPrice::GetInstrument() const
	{
		return m_instrument;
	}

	void OHLCPrice::SetInstrument(const char* instrument)
	{
		m_instrument = instrument;
	}

	const misc::string& OHLCPrice::GetTimeframe() const
	{
		return m_timeframe;
	}

	void OHLCPrice::SetTimeframe(const char* timeframe)
	{
		m_timeframe = timeframe;
	}

	const misc::time& OHLCPrice::GetTime() const
	{
		return m_time;
	}

	void OHLCPrice::SetTime(const misc::time& val)
	{
		m_time = val;
	}

	double OHLCPrice::GetBidOpen() const
	{
		return m_bidOpen;
	}

	void OHLCPrice::SetBidOpen(double val)
	{
		m_bidOpen = val;
	}

	double OHLCPrice::GetBidHigh() const
	{
		return m_bidHigh;
	}

	void OHLCPrice::SetBidHigh(double val)
	{
		m_bidHigh = val;
	}

	double OHLCPrice::GetBidLow() const
	{
		return m_bidLow;
	}

	void OHLCPrice::SetBidLow(double val)
	{
		m_bidLow = val;
	}

	double OHLCPrice::GetBidClose() const
	{
		return m_bidClose;
	}

	void OHLCPrice::SetBidClose(double val)
	{
		m_bidClose = val;
	}

	double OHLCPrice::GetAskOpen() const
	{
		return m_askOpen;
	}

	void OHLCPrice::SetAskOpen(double val)
	{
		m_askOpen = val;
	}

	double OHLCPrice::GetAskHigh() const
	{
		return m_askHigh;
	}

	void OHLCPrice::SetAskHigh(double val)
	{
		m_askHigh = val;
	}

	double OHLCPrice::GetAskLow() const
	{
		return m_askLow;
	}

	void OHLCPrice::SetAskLow(double val)
	{
		m_askLow = val;
	}

	double OHLCPrice::GetAskClose() const
	{
		return m_askClose;
	}

	void OHLCPrice::SetAskClose(double val)
	{
		m_askClose = val;
	}

	int OHLCPrice::GetVolume() const
	{
		return m_volume;
	}

	void OHLCPrice::SetVolume(int val)
	{
		m_volume = val;
	}

	void OHLCPrice::Init()
	{
		// m_instrument; - empty
		// m_timeframe; - empty
		// m_time; - default
		m_bidOpen = 0;
		m_bidHigh = 0;
		m_bidLow = 0;
		m_bidClose = 0;
		m_askOpen = 0;
		m_askHigh = 0;
		m_askLow = 0;
		m_askClose = 0;
		m_volume = 0;
	}
} // namespace
