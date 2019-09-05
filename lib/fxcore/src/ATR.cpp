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

	ATR::ATR(const stl::string& instrument, int period, Timeframe sec)
	{
		Init();

		m_instrument = instrument;
		m_period = period + 1;	// the 1st previous close is extra
		m_timeframe = sec;
        m_bar = fx::BAR(instrument, m_period, sec); // use the extra candle
	}

	ATR::~ATR()
	{
	}

	ATR::ATR(const ATR& tc)
	{
        Init();

		*this = tc;
	}

	ATR& ATR::operator=(const ATR& tc)
	{
		if (this != &tc)
		{
			m_instrument = tc.m_instrument;
			m_period = tc.m_period;
			m_timeframe = tc.m_timeframe;
            m_bar = tc.m_bar;
			m_medATR = tc.m_medATR;
			m_ATR = tc.m_ATR;
		}

		return *this;
	}

	const stl::string& ATR::GetInstrument() const
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
		return (m_period - 1 > 1 &&
                m_period == m_bar.GetOHLCList().size() &&
                m_medATR != -1 &&
                m_ATR != -1);
	}

	void ATR::Update(const fx::Offer& offer)
	{
		if (m_instrument != offer.GetInstrument())
			throw stl::exception("ATR offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        if (!isNew)
        {
            m_bar.Update(offer);
            const fx::OHLCPrice& ohlc = m_bar.GetOHLC();
            const fx::BARB::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

            /*  Calculate an intermediary ATR if enough data is available.
                If bigger than current ATR, update it to reflect the volatility.
            */
            if (m_medATR != -1 && ohlcList.size() == m_period)
            {
                // current TR
                double prevC = ohlcList.back().GetBidClose();
                double currH = ohlc.GetBidHigh();
                double currL = ohlc.GetBidLow();

                double v1 = currH - currL;
                double v2 = fabs(currH - prevC);
                double v3 = fabs(currL - prevC);

                double TR = std::max(v1, std::max(v2, v3));

                double n = m_period - 1.0;
                double ATR = (m_medATR * (n - 1) + TR) / n;

                m_ATR = stl::max(m_ATR, ATR);
            }
        }
        else
        {
            const fx::OHLCPrice& ohlc = m_bar.GetOHLC();
            const fx::BARB::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

            /*	Current OHLC bar is complete.
                Calculate a new ATR value if possible.
            */
            if (ohlcList.size() == m_period)
            {
                /*  Calculate the median ATR
                    TR = max[(currH - currL), abs(currH - prevC), abs(currL - prevC)]
                    ATR = (ATR(t - 1) x (n - 1) + TR(t)) / n		(true average)
                    ATR(t - 1) = sum(TRi) / n  where i = 1->n	(median)
                */

                m_medATR = 0;
                m_ATR = 0;

                OHLCPriceList::const_iterator previt = ohlcList.begin();
                OHLCPriceList::const_iterator currit = previt;
                ++currit;

                for (; currit != ohlcList.end(); ++previt, ++currit)
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
                double prevC = ohlcList.back().GetBidClose();
                double currH = ohlc.GetBidHigh();
                double currL = ohlc.GetBidLow();

                double v1 = currH - currL;
                double v2 = fabs(currH - prevC);
                double v3 = fabs(currL - prevC);

                double TR = std::max(v1, std::max(v2, v3));

                m_ATR = (m_medATR * (n - 1) + TR) / n;
            }

            // paint a new bar
            m_bar.Update(offer);
        }
	}

	const sys::time& ATR::GetRefTime() const
	{
		return m_bar.GetRefTime();
	}

	void ATR::GetValue(double& average) const
	{
        if (m_period - 1 < 2 ||
            m_bar.GetOHLCList().size() != m_period ||
            m_medATR == -1 ||
            m_ATR == -1)
        {
            throw stl::exception("ATR is invalid");
        }

		// return last ATR (true average)
		average = m_ATR;
	}

	void ATR::Init()
	{
		m_instrument = "";
		m_period = -1;
		m_timeframe = 0;
        // m_bar - default;
		m_medATR = -1;
		m_ATR = -1;
	}
} // namespace
