/*
    Copyright (C) 2019 Mihai Vasilian

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

#include "ADX.hpp"
#include "algorithm.hpp"

namespace fx
{
    ADX::ADX()
    {
        Init();
    }

    ADX::ADX(const stl::string& instrument, int period, Timeframe sec)
    {
        Init();

        m_instrument = instrument;
        m_period = period;
        m_timeframe = sec;
        m_bar = fx::BAR(instrument, m_period, sec);
    }

    ADX::~ADX()
    {
    }

    ADX::ADX(const ADX& tc)
    {
        Init();

        *this = tc;
    }

    ADX& ADX::operator=(const ADX& tc)
    {
        if (this != &tc)
        {
            m_instrument = tc.m_instrument;
            m_period = tc.m_period;
            m_timeframe = tc.m_timeframe;
            m_bar = tc.m_bar;
        }
        return *this;
    }
    
    const stl::string& ADX::GetInstrument() const
    {
        return m_instrument;
    }

    int ADX::GetPeriod() const
    {
        return m_period;
    }

    ADX::Timeframe ADX::GetTimeframe() const
    {
        return m_timeframe;
    }

    bool ADX::IsValid() const
    {
        throw 0;
    }

    void ADX::Update(const fx::Offer& offer)
    {
        if (m_instrument != offer.GetInstrument())
            throw stl::exception("ATR offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        if (!isNew)
        {
            m_bar.Update(offer);
            const fx::OHLCPrice& ohlc = m_bar.GetOHLC();
            const fx::BAR::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

            if (ohlcList.size() == m_period)
            {
                fx::BAR::OHLCPriceList::const_iterator it = ohlcList.begin();
                const fx::OHLCPrice& prev = *it;
                for (++it; it != ohlcList.end(); ++it)
                {
                    const fx::OHLCPrice& curr = *it;

                }
            }
        }


        
        const fx::OHLCPrice& prev = m_bar.GetOHLCList().back();
        const fx::OHLCPrice& curr = m_bar.GetOHLC();

        //m_bar.Update(offer);
        //const fx::OHLCPrice& ohlc = m_bar.GetOHLC();
        //const fx::BARB::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

        // Directional Movement (DM)
        double DM = 0;

        if (prev.GetBidHigh() < curr.GetBidHigh())
        {
            DM = curr.GetBidHigh() - prev.GetBidHigh();    // positive
        }

        if (prev.GetBidLow() > curr.GetBidLow())
        {
            double dmlow = curr.GetBidLow() - prev.GetBidLow();
            if (DM < fabs(dmlow))
                DM = dmlow;                                 // negative
        }

        // True Range (TR)
        double prevC = prev.GetBidClose();
        double currH = curr.GetBidHigh();
        double currL = curr.GetBidLow();

        double v1 = currH - currL;
        double v2 = fabs(currH - prevC);
        double v3 = fabs(currL - prevC);

        double TR = stl::max(v1, stl::max(v2, v3));

        // Directional Indicator (DI)
        double DI = DM / TR;    // positive or negative






    }

    const sys::time& ADX::GetRefTime() const
    {
        return m_bar.GetRefTime();
    }
} // namespace
