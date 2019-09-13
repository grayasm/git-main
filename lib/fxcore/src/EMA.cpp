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

	EMA::EMA(
        const stl::string& instrument,
		int period,
		Timeframe sec,
		BarType barType,
		PriceOrigin po)
	{
		Init();

        m_instrument = instrument;
		m_period = period;
		m_timeframe = sec;
		m_barType = barType;
        m_priceOrigin = po;
		m_multiplier = 2.0 / (m_period + 1.0);
		switch (barType)
		{
			case fx::SMA::BT_BAR:
			{
				m_bar = new fx::BAR(instrument, period, sec);
                break;
			}
			case fx::SMA::BT_HABAR:
			{
				m_bar = new fx::HABAR(instrument, period, sec);
				break;
			}
			default:
				throw stl::exception("SMA unknown BAR type");
		}		
		m_firstSMA = fx::SMA(instrument, period, sec, barType, po);
	}

	EMA::~EMA()
	{
        if (m_bar)
            delete m_bar;
	}

	EMA::EMA(const EMA& tc)
	{
		Init();

		*this = tc;
	}

	EMA& EMA::operator=(const EMA& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
            m_barType = tc.m_barType;
            m_priceOrigin = tc.m_priceOrigin;
			m_multiplier = tc.m_multiplier;
            if (tc.m_bar)
            {
                switch (tc.m_barType)
                {
                    case fx::SMA::BT_BAR:
                    {
                        fx::BAR* ptr = static_cast<fx::BAR*>(tc.m_bar);
                        if (m_bar)
                            delete m_bar;
                        m_bar = new fx::BAR(*ptr);
                        break;
                    }
                    case fx::SMA::BT_HABAR:
                    {
                        fx::HABAR* ptr = static_cast<fx::HABAR*>(tc.m_bar);
                        if (m_bar)
                            delete m_bar;
                        m_bar = new fx::HABAR(*ptr);
                        break;
                    }
                    default:
                        throw stl::exception("SMA unknown BAR type");
                }
            }
            else
            {
                if (m_bar)
                    delete m_bar;
                m_bar = NULL;
            }
			m_firstSMA = tc.m_firstSMA;
			m_currEMA = tc.m_currEMA;
			m_emaList = tc.m_emaList;
		}

		return *this;
	}

	const stl::string& EMA::GetInstrument() const
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
    
	bool EMA::IsValid() const
	{
		return (m_period > 1 &&
                m_period == m_emaList.size() &&
                m_currEMA.GetBuy() > 0 &&
                m_currEMA.GetSell() > 0);
	}

	void EMA::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw stl::exception("EMA offer is invalid");

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
            m_bar->Update(offer);   // time alignment			
            return;
		}


        // add 1st EMA
		if (m_emaList.empty())
		{
			fx::Price price;
			m_firstSMA.GetValue(price);
			m_emaList.push_back(price);
		}


        bool isNew = m_bar->IsNew(offer);

        // inside current timeframe?
        if (!isNew)
        {
            m_bar->Update(offer);
            const fx::OHLCPrice& ohlc = m_bar->GetOHLC();

            double buy = 0, sell = 0;
            if (m_priceOrigin == fx::SMA::PRICE_OPEN)
            {
                buy = ohlc.GetAskOpen();
                sell = ohlc.GetBidOpen();
            }
            else
            {
                buy = ohlc.GetAskClose();
                sell = ohlc.GetBidClose();
            }

            double lastb = m_emaList.back().GetBuy();
            double lasts = m_emaList.back().GetSell();

            double calcb = (buy - lastb) * m_multiplier + lastb;
            double calcs = (sell - lasts) * m_multiplier + lasts;

            m_currEMA = fx::Price(calcb, calcs);
        }
        else
        {
            // handle the list
            m_emaList.push_back(m_currEMA);

            // keep period constant
            if (m_emaList.size() > m_period)
                m_emaList.pop_front();

            // paint a new bar
            m_bar->Update(offer);
        }
	}

	const sys::time& EMA::GetRefTime() const
	{
		return m_bar->GetRefTime();
	}

	EMA::PriceOrigin EMA::GetPriceOrigin() const
	{
		return m_firstSMA.GetPriceOrigin();
	}

	void EMA::GetValue(fx::Price& average) const
	{
        if (m_period < 2 ||
            m_emaList.size() != m_period ||
            m_currEMA.GetBuy() == 0 ||
            m_currEMA.GetSell() == 0)
        {
            throw stl::exception("EMA is invalid");
        }

		average = m_currEMA;
	}

	void EMA::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
        m_barType = fx::SMA::BT_BAR;
        m_priceOrigin = fx::SMA::PRICE_CLOSE;
		m_multiplier = 0;
		m_bar = NULL;
		// m_firstSMA - default;
		m_currEMA = fx::Price(0, 0);
		// m_emaList - clean;
	}
} // namespace
