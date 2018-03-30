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

	
	In the calculation, Open(0) is current open and Open(-1) is previous open.

	I) The 1st HA-Bar is a normal Bar with a calculated Close:
	HA-Close(0) = (Open(0) + High(0) + Low(0) + Close(0)) / 4

	II) Even though this first HA-Bar is somewhat artificial, the effects will
		dissipate over time (usually 7-10 periods).

	HAOpen = (HAOpen(-1) + HAClose(-1)) / 2
	HAClose = (Open(0) + High(0) + Low(0) + Close(0)) / 4
	HAHigh = max(High(0), HAOpen(0), HAClose(0))
	HALow = min(Low(0), HAOpen(0), HAClose(0))
*/


#include "HABAR.hpp"

namespace fx
{
	HABAR::HABAR() : BAR()
	{
		Init();
	}

	HABAR::HABAR(const misc::string& instrument, int period, Timeframe sec)
		: BAR(instrument, period, sec)
	{
		Init();
	}

	HABAR::~HABAR()
	{
	}

	HABAR::HABAR(const HABAR& tc)
		: BAR(tc)
	{
		Init();

		*this = tc;
	}

	HABAR& HABAR::operator=(const HABAR& tc)
	{
		if (this != &tc)
		{
			BAR::operator=(tc);

			m_lastHA = tc.m_lastHA;
			m_haList = tc.m_haList;
		}
		return *this;
	}

	const misc::string& HABAR::GetInstrument() const
	{
		return BAR::GetInstrument();
	}

	int HABAR::GetPeriod() const
	{
		return BAR::GetPeriod();
	}

	HABAR::Timeframe HABAR::GetTimeframe() const
	{
		return BAR::GetTimeframe();
	}

	bool HABAR::IsValid() const
	{
		return BAR::IsValid();
	}

	void HABAR::Update(const fx::Offer& offer)
	{
		if (BAR::GetInstrument() != offer.GetInstrument())
			throw misc::exception("HABAR offer is invalid");

		const misc::time& reftime = BAR::GetRefTime();

		// let the BAR normalize the timeframe
		if (reftime.totime_t() == 0)
			return BAR::Update(offer);

		// wait for the reference time to begin
		const misc::time& currtime = offer.GetTime();
		if (currtime < reftime)
			return BAR::Update(offer);


		// inside current timeframe?
		bool isNew = BAR::IsNew(offer);
		if (!isNew)
		{
			BAR::Update(offer);
			const fx::OHLCPrice& ohlc = BAR::GetOHLC(); // current BAR

			// first bar
			if (m_haList.empty())
			{
				m_lastHA = ohlc; // normal OHLC with HA-Close

				// HA-Close
				m_lastHA.SetAskClose(
					(ohlc.GetAskOpen() + ohlc.GetAskHigh() +
					ohlc.GetAskLow() + ohlc.GetAskClose()) / 4);
				m_lastHA.SetBidClose(
					(ohlc.GetBidOpen() + ohlc.GetBidHigh() +
					ohlc.GetBidLow() + ohlc.GetBidClose()) / 4);
			}
			else
			{
				// HA-Open is set 1 time per HABAR
				// HA-Close
				m_lastHA.SetAskClose(
					(ohlc.GetAskOpen() + ohlc.GetAskHigh() +
					ohlc.GetAskLow() + ohlc.GetAskClose()) / 4);
				m_lastHA.SetBidClose(
					(ohlc.GetBidOpen() + ohlc.GetBidHigh() +
					ohlc.GetBidLow() + ohlc.GetBidClose()) / 4);

				// HA-High
				m_lastHA.SetAskHigh(
					misc::max(ohlc.GetAskHigh(),
					m_lastHA.GetAskOpen(),
					m_lastHA.GetAskClose()));
				m_lastHA.SetBidHigh(
					misc::max(ohlc.GetBidHigh(),
					m_lastHA.GetBidOpen(),
					m_lastHA.GetBidClose()));

				// HA-Low
				m_lastHA.SetAskLow(
					misc::min(ohlc.GetAskLow(),
					m_lastHA.GetAskOpen(),
					m_lastHA.GetAskClose()));
				m_lastHA.SetBidLow(
					misc::min(ohlc.GetBidLow(),
					m_lastHA.GetBidOpen(),
					m_lastHA.GetBidClose()));
			}
		}
		else // isNew is true
		{
			// handle the list
			m_haList.push_back(m_lastHA);

			// keep period constant
			if (m_haList.size() > BAR::GetPeriod())
				m_haList.pop_front();

			// new candle has just started
			BAR::Update(offer);
			const fx::OHLCPrice& ohlc = BAR::GetOHLC(); // current BAR

			// HA-Open
			const fx::OHLCPrice& prevHA = m_haList.back();
			m_lastHA.SetAskOpen((prevHA.GetAskOpen() + prevHA.GetAskClose()) / 2);
			m_lastHA.SetBidOpen((prevHA.GetBidOpen() + prevHA.GetBidClose()) / 2);

			// HA-Close
			m_lastHA.SetAskClose(
				(ohlc.GetAskOpen() + ohlc.GetAskHigh() +
				ohlc.GetAskLow() + ohlc.GetAskClose()) / 4);
			m_lastHA.SetBidClose(
				(ohlc.GetBidOpen() + ohlc.GetBidHigh() +
				ohlc.GetBidLow() + ohlc.GetBidClose()) / 4);

			// HA-High
			m_lastHA.SetAskHigh(
				misc::max(ohlc.GetAskHigh(),
				m_lastHA.GetAskOpen(),
				m_lastHA.GetAskClose()));
			m_lastHA.SetBidHigh(
				misc::max(ohlc.GetBidHigh(),
				m_lastHA.GetBidOpen(),
				m_lastHA.GetBidClose()));

			// HA-Low
			m_lastHA.SetAskLow(
				misc::min(ohlc.GetAskLow(),
				m_lastHA.GetAskOpen(),
				m_lastHA.GetAskClose()));
			m_lastHA.SetBidLow(
				misc::min(ohlc.GetBidLow(),
				m_lastHA.GetBidOpen(),
				m_lastHA.GetBidClose()));
		}
	}

	const misc::time& HABAR::GetRefTime() const
	{
		return BAR::GetRefTime();
	}

	bool HABAR::IsNew(const fx::Offer& offer) const
	{
		return BAR::IsNew(offer);
	}

	const fx::OHLCPrice& HABAR::GetOHLC() const
	{
		return m_lastHA;
	}

	const BAR::OHLCPriceList& HABAR::GetOHLCList() const
	{
		return m_haList;
	}

	void HABAR::Init()
	{
		m_lastHA = fx::OHLCPrice("", "", misc::time(),
								0, 0, 0, 0,
								0, 0, 0, 0,
								0);
		// m_haList - default;
	}

} // namespace


