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

#include "EMA.hpp"


namespace fx
{
	EMA::EMA()
	{
		Init();
	}

	EMA::EMA(const misc::string& instrument, int period, Timeframe sec, PriceOrigin po)
	{
		Init();

		m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
		m_multiplier = 2.0 / (m_period + 1.0);
		m_firstSMA = fx::SMA(instrument, period, sec, po);
	}

	EMA::~EMA()
	{

	}

	EMA::EMA(const EMA& tc)
	{
		*this = tc;
	}

	EMA& EMA::operator=(const EMA& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
			m_multiplier = tc.m_multiplier;
			m_firstSMA = tc.m_firstSMA;
			m_reftime = tc.m_reftime;
			m_priceO = tc.m_priceO;
			m_priceC = tc.m_priceC;
			m_currEMA = tc.m_currEMA;
			m_emaList = tc.m_emaList;
		}

		return *this;
	}

	const misc::string& EMA::GetInstrument() const
	{
		return m_instrument;
	}

	int EMA::GetPeriod() const
	{
		return m_period;
	}

	EMA::Timeframe EMA::GetTimeframe() const
	{
		return m_timeframe;
	}

	EMA::PriceOrigin EMA::GetPriceOrigin() const
	{
		return m_firstSMA.GetPriceOrigin();
	}

	bool EMA::IsValid() const
	{
		return (m_period > 1 && m_period == m_emaList.size());
	}

	void EMA::Update(const fx::Offer& offer)
	{
		if (m_period < 2)
			throw misc::exception("EMA is invalid");

		if (m_instrument != offer.GetInstrument())
			throw misc::exception("EMA offer is invalid");

		/*	http://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:moving_averages
			Example for 10 period EMA:
			Initial SMA: 10_period_SUM / 10			
			Multiplier: (2 / (Time periods + 1) ) = (2 / (10 + 1) ) = 0.1818 (18.18%)
			EMA: {Close - EMA(previous)} x multiplier + EMA(previous).
		*/
		
		//	1st EMA is an SMA.
		if (!m_firstSMA.IsValid())
		{
			m_firstSMA.Update(offer);
			return;
		}

		if (m_emaList.empty())
		{
			// add first EMA
			fx::Price price;
			m_firstSMA.GetValue(price);
			m_emaList.push_back(price);

			// begin of current timeframe
			m_reftime = m_firstSMA.GetRefTime();

			// open and close of current candle
			m_priceO = fx::Price(offer.GetAsk(), offer.GetBid());
			m_priceC = m_priceO;

			return;
		}

		const misc::time& currtime = offer.GetTime();
		misc::time nextt = m_reftime + m_timeframe;


		// every price can close the candle
		if (currtime < nextt)
		{
			m_priceC = fx::Price(offer.GetAsk(), offer.GetBid());
		}

		// calculate current EMA
		double currb = 0, currs = 0;
		if (m_firstSMA.GetPriceOrigin() == fx::SMA::PRICE_OPEN)
		{
			currb = m_priceO.GetBuy();
			currs = m_priceO.GetSell();
		}
		else
		{
			currb = m_priceC.GetBuy();
			currs = m_priceC.GetSell();
		}

		double lastb = m_emaList.back().GetBuy();
		double lasts = m_emaList.back().GetSell();

		double calcb = (currb - lastb) * m_multiplier + lastb;
		double calcs = (currs - lasts) * m_multiplier + lasts;

		m_currEMA = fx::Price(calcb, calcs);


		// is current candle closed?
		if (currtime >= nextt)
		{
			// handle the list
			m_emaList.push_back(m_currEMA);

			// keep period constant
			if (m_emaList.size() > m_period)
				m_emaList.pop_front();

			
			// new candle has just started
			m_priceO = fx::Price(offer.GetAsk(), offer.GetBid());
			m_priceC = m_priceO;

			// current candle open (including weekend gap)
			while (currtime >= m_reftime + m_timeframe)
				m_reftime += m_timeframe;
		}
	}

	void EMA::GetValue(fx::Price& average) const
	{
		if (m_period < 2 || m_emaList.size() != m_period)
			throw misc::exception("EMA is invalid");

		average = m_currEMA;
	}

	const misc::time& EMA::GetRefTime() const
	{
		return m_reftime;
	}

	void EMA::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
		m_multiplier = 0;
		// m_firstSMA - default;
		// m_reftime - default;
		m_priceO = fx::Price(0, 0);
		m_priceC = fx::Price(0, 0);
		m_currEMA = fx::Price(0, 0);
		// m_emaList - clean;
	}
} // namespace
