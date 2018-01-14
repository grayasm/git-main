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


#include "HistoryPrice.hpp"


namespace fxcm
{
	HistoryPrice::HistoryPrice
	(
		const char* instrument,					// 'EUR/USD'
		const char* timeframe,					// m1 , H1 , ...
		const char* time,						// m.d.Y H:M:S
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

	HistoryPrice::HistoryPrice(const HistoryPrice& tc)
	{
		*this = tc;
	}

	HistoryPrice& HistoryPrice::operator = (const HistoryPrice& tc)
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

	HistoryPrice::~HistoryPrice()
	{
	}

	const misc::string& HistoryPrice::GetInstrument() const
	{
		return m_instrument;
	}

	void HistoryPrice::SetInstrument(const char* instrument) const
	{
		m_instrument = instrument;
	}

	const misc::string& HistoryPrice::GetTimeframe() const
	{
		return m_timeframe;
	}

	void HistoryPrice::SetTimeframe(const char* timeframe)
	{
		m_timeframe = timeframe;
	}

	double HistoryPrice::GetBidOpen() const
	{
		return m_bidOpen;
	}

	void HistoryPrice::SetBidOpen(double val)
	{
		m_bidOpen = val;
	}

	double HistoryPrice::GetBidHigh() const
	{
		return m_bidHigh;
	}

	void HistoryPrice::SetBidHigh(double val)
	{
		m_bidHigh = val;
	}

	double HistoryPrice::GetBidLow() const
	{
		return m_bidLow;
	}

	void HistoryPrice::SetBidLow(double val)
	{
		m_bidLow = val;
	}

	double HistoryPrice::GetBidClose() const
	{
		return m_bidClose;
	}

	void HistoryPrice::SetBidClose(double val)
	{
		m_bidClose = val;
	}

	double HistoryPrice::GetAskOpen() const
	{
		return m_askOpen;
	}

	void HistoryPrice::SetAskOpen(double val)
	{
		m_askOpen = val;
	}

	double HistoryPrice::GetAskHigh() const
	{
		return m_askHigh;
	}

	void HistoryPrice::SetAskHigh(double val)
	{
		m_askHigh = val;
	}

	double HistoryPrice::GetAskLow() const
	{
		return m_askLow;
	}

	void HistoryPrice::SetAskLow(double val)
	{
		m_askLow = val;
	}

	double HistoryPrice::GetAskClose() const
	{
		return m_askClose;
	}

	void HistoryPrice::SetAskClose(double val)
	{
		m_askClose = val;
	}

	int HistoryPrice::GetVolume() const
	{
		return m_volume;
	}

	void HistoryPrice::SetVolume(int val)
	{
		m_volume = val;
	}
} // namespace
