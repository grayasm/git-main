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

	SMA::SMA(
		const misc::string& instrument,
		int period,
		Timeframe sec,
		PriceOrigin po,
		BarType barType)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
		m_priceOrigin = po;
		m_barType = barType;
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
			m_barType = tc.m_barType;
			switch (tc.m_barType)
			{
				case BT_BAR:
				{
					fx::BAR* ptr = static_cast<fx::BAR*>(tc.m_bar);
					m_bar = new fx::BAR(*ptr);
				}
				break;
				case BT_HABAR:
				{
					fx::HABAR* ptr = static_cast<fx::HABAR*>(tc.m_bar);
					m_bar = new fx::HABAR(*ptr);
					break;
				}
				default:
					throw misc::exception("SMA unknown BAR type");
			}
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

	bool SMA::IsValid() const
	{
		return (m_period > 1 && m_period == m_bar->GetOHLCList().size());
	}

	void SMA::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw misc::exception("SMA offer is invalid");

		const misc::time& reftime = m_bar->GetRefTime();

		// let the BAR normalize the timeframe
		if (reftime.totime_t() == 0)
			return m_bar->Update(offer);

		// wait for the reference time to begin
		const misc::time& currtime = offer.GetTime();
		if (currtime < reftime)
			return m_bar->Update(offer);

		// inside current timeframe?
		bool isNew = m_bar->IsNew(offer);
		if (!isNew)
		{
			m_bar->Update(offer);
		}
		else
		{
			// calculate the sum
			const BAR::OHLCPriceList& priceList = m_bar->GetOHLCList();
			if (priceList.size() == m_period)
			{
				double buy = 0, sell = 0;
				BAR::OHLCPriceList::const_iterator it = priceList.begin();
				for (; it != priceList.end(); ++it)
				{
					if (m_priceOrigin == PRICE_OPEN)
					{
						buy += it->GetAskOpen();
						sell += it->GetBidOpen();
					}
					else if (m_priceOrigin == PRICE_CLOSE)
					{
						buy += it->GetAskClose();
						sell += it->GetBidClose();
					}
				}
				m_lastSum = fx::Price(buy, sell);
			}
		}
	}


	const misc::time& SMA::GetRefTime() const
	{
		return m_bar->GetRefTime();
	}

	SMA::PriceOrigin SMA::GetPriceOrigin() const
	{
		return m_priceOrigin;
	}

	void SMA::GetValue(fx::Price& average) const
	{
		if (m_period < 2 || m_bar->GetOHLCList().size() != m_period)
			throw misc::exception("SMA is invalid");

		double buy = 0, sell = 0;
		if (m_priceOrigin == PRICE_OPEN)
		{
			buy = m_lastSum.GetBuy() / m_period;
			sell = m_lastSum.GetSell() / m_period;
		}
		else
		{
			const fx::OHLCPrice& ohlc = m_bar->GetOHLC();
			buy = (m_lastSum.GetBuy() + ohlc.GetAskClose()) / (m_period + 1);
			sell = (m_lastSum.GetSell() + ohlc.GetBidClose()) / (m_period + 1);
		}

		average = fx::Price(buy, sell);
	}

	void SMA::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
		m_priceOrigin = PRICE_CLOSE;
		m_barType = BT_BAR;
		m_bar = NULL;
		m_lastSum = fx::Price(0, 0);
	}
} // namespace
