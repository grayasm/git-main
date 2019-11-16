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

#include "RSI.hpp"

namespace fx
{
    RSI::RSI()
    {
        Init();
    }

    RSI::RSI(const stl::string& instrument, int period, Timeframe sec)
    {
        if (period < 2)
            throw stl::exception("RSI period must be greater than 1");

        Init();

        m_instrument = instrument;
        m_period = period;
        m_timeframe = sec;
        m_bar = fx::BAR(instrument, period, sec);
    }

    RSI::~RSI()
    {
    }

    RSI::RSI(const RSI& tc)
    {
        Init();

        *this = tc;
    }

    RSI& RSI::operator=(const RSI& tc)
    {
        if (this != &tc)
        {
            m_instrument = tc.m_instrument;
            m_period = tc.m_period;
            m_timeframe = tc.m_timeframe;
            
        }
        return *this;
    }

    const stl::string& RSI::GetInstrument() const
    {
        return m_instrument;
    }

    int RSI::GetPeriod() const
    {
        return m_period;
    }

    RSI::Timeframe RSI::GetTimeframe() const
    {
        return m_timeframe;
    }

    bool RSI::IsValid() const
    {
        return false; 
        /*(m_period > 1 &&
            m_period == m_bar.GetOHLCList().size() &&
            m_period == m_sarList.size() &&
            m_SAR.GetBuy() > 0 &&
            m_SAR.GetSell() > 0);
        */
    }

    void RSI::Update(const fx::Offer& offer)
    {
        if (m_instrument != offer.GetInstrument())
            throw stl::exception("RSI offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        if (isNew)
        {
            /*  pag.54
                The momentum factor (MF) is the difference between the close
                price today and the close price two days ago.
            */
            if (m_bar.GetOHLCList().size() == m_period)
            {
                const fx::BAR::OHLCPriceList& ohlcList = m_bar.GetOHLCList();
                const fx::OHLCPrice& init = ohlcList.front();
                const fx::OHLCPrice& curr = m_bar.GetOHLC();

                m_MF = curr.GetBidClose() - init.GetBidClose();
            }

            /*  Cannot calculate MF if the current closed candle is pushed
                into period. Get first the MF and then update.
            */
            m_bar.Update(offer);
        }
        else // !isNew
        {
            // can update first
            m_bar.Update(offer);

            if (m_bar.GetOHLCList().size() == m_period)
            {
                const fx::BAR::OHLCPriceList& ohlcList = m_bar.GetOHLCList();
                const fx::OHLCPrice& init = ohlcList.front();

                m_mf = offer.GetBid() - init.GetBidClose();
            }
        }
    }


    const sys::time& RSI::GetRefTime() const
    {
        return m_bar.GetRefTime();
    }

    void RSI::Init()
    {
        m_instrument = "";
        m_period = -1;
        m_timeframe = 0;
        // m_bar - default
    }
} // namespace