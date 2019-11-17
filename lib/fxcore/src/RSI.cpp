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


    J. Welles Wilder Jr. - New Concepts in Technical Trading Systems pag.64
    The RSI oscillator can be an excellent technical tool for the trader;
    however there are three problems with it:
    (1) The first problem is erratic movement within the general oscillator
        configuration. To overcome this problem there must be some way to dampen
        or smooth out the extreme points.
    (2) The second problem is the scale to use for the 'Y' axis. In other words,
        how high is high and how low is low? To overcome this problem, there
        must be some common denominator to apply to all commodities so the
        amplitude of the oscillator is relative and meaningful.
    (3) The third problem is the necessity of having to keep up with
        the enourmous amounts of data. This is the least of the three problems;
        however, it can become burdensome to the trader who is following several
        commodities with an oscillator technique.

    The solution to these three problems is incorporated in the indicator which
    we will call THE RELATIVE STRENGHT INDEX.

    The equation for the Relative Strength Index, RSI is
    RSI = 100 - [ 100 : (1 + RS) ];  where RS is:
    RS = Average of 14 day's closes UP : Average of 14 day's close DOWN;

    All calculations in this file were compared for correctness with the
    Daily Work Sheet "RELATIVE STRENGTH INDEX" page 66.

    e.g.    CLOSE, UP, DOWN, UP AVG, DOWN AVG, RS and RSI.

    James Welles Wilder uses the generic term 'Price' without specifying if it
    is the Ask or Bid value. We need consistency in using only Bid or only Ask.
    I used only the Bid price for calculation here. If different - it's a bug.
*/

#include "RSI.hpp"
#include <math.h>

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
            m_bar = tc.m_bar;
            m_useSmoothing = tc.m_useSmoothing;
            m_medUp = tc.m_medUp;
            m_medDown = tc.m_medDown;
            m_RSI = tc.m_RSI;
            m_rsi = tc.m_rsi;
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
        return (m_period > 1 &&
                m_bar.GetOHLCList().size() == m_period &&
                m_RSI > -1);
    }

    void RSI::Update(const fx::Offer& offer)
    {
        if (m_instrument != offer.GetInstrument())
            throw stl::exception("RSI offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        if (isNew)
        {
            /*  pag. 65
                For the first calculation of the RSI we need the previous
                14 day's close prices. From then on, we need only the previous
                day's data.
            */
            const fx::BAR::OHLCPriceList& ohlcList = m_bar.GetOHLCList();
            if (ohlcList.size() == m_period && !m_useSmoothing)
            {
                m_medUp = 0;
                m_medDown = 0;
                m_RSI = 0;
                m_rsi = 0;

                fx::BAR::OHLCPriceList::const_iterator it = ohlcList.begin();
                for (; it != ohlcList.end(); ++it)
                {
                    // safety: if (period == 2) we only loop 1x
                    fx::BAR::OHLCPriceList::const_iterator next = it;
                    ++next;
                    if (next == ohlcList.end())
                        break;

                    double diff = next->GetBidClose() - it->GetBidClose();
                    if (diff < 0)
                        m_medDown += diff;
                    else
                        m_medUp += diff;
                }

                /*  pag. 66
                    The table calculates the average at the close of 15 day.
                    We need 14 days + current day closed.
                */
                const fx::OHLCPrice& prev = ohlcList.back();
                const fx::OHLCPrice& curr = m_bar.GetOHLC();
                double diff = curr.GetBidClose() - prev.GetBidClose();

                if (diff < 0)
                    m_medDown += diff;
                else
                    m_medUp += diff;

                m_medUp /= m_period;
                m_medDown /= m_period;

                double RS = m_medUp / fabs(m_medDown); // always > 0
                double divisor = 1 + RS;
                
                m_RSI = 100 - 100 / divisor;
                m_rsi = m_RSI;


                m_useSmoothing = true;
            }
            else if (m_useSmoothing)
            {
                /*  pag. 65
                    From this point on, it is only necessary to use the previous
                    average UP close and the previous average DOWN close in the
                    calculation of the next RSI. This procedure which
                    incorporates the dampening or smoothing factor into
                    the equation is as follows:

                    (1) average UP = (prev average UP * 13 + today's UP) / 14
                    (2) average DOWN = (prev average DOWN * 13 + today's DOWN) / 14

                    Steps (3),(4),(5) and (6) are the same as for the initial RSI.
                */
                const fx::OHLCPrice& prev = m_bar.GetOHLCList().back();
                const fx::OHLCPrice& ohlc = m_bar.GetOHLC();

                double diff = ohlc.GetBidClose() - prev.GetBidClose();
                double diffUp = (diff < 0 ? 0 : diff);
                double diffDown = (diff < 0 ? diff : 0);

                m_medUp = (m_medUp * (m_period - 1) + diffUp) / m_period;
                m_medDown = (m_medDown * (m_period - 1) + diffDown) / m_period;

                double RS = m_medUp / fabs(m_medDown); // always > 0
                double divisor = 1 + RS;

                m_RSI = 100 - 100 / divisor;
            }


            /*  Cannot calculate RSI if the current closed candle is pushed
                into period. Get first the RSI and then update.
            */
            m_bar.Update(offer);
        }
        else // !isNew
        {
            // can update first
            m_bar.Update(offer);

            if (m_rsi != -1)
            {
                const fx::OHLCPrice& prev = m_bar.GetOHLCList().back();
                const fx::OHLCPrice& ohlc = m_bar.GetOHLC();

                double diff = ohlc.GetBidClose() - prev.GetBidClose();
                double diffUp = (diff < 0 ? 0 : diff);
                double diffDown = (diff < 0 ? diff : 0);

                double medUp = (m_medUp * (m_period - 1) + diffUp) / m_period;
                double medDown = (m_medDown * (m_period - 1) + diffDown) / m_period;

                double RS = medUp / fabs(medDown); // always > 0
                double divisor = 1 + RS;

                m_rsi = 100 - 100 / divisor;
            }
        }
    }


    const sys::time& RSI::GetRefTime() const
    {
        return m_bar.GetRefTime();
    }

    double RSI::GetRSI() const
    {
        return m_RSI;
    }

    double RSI::GetRSI2() const
    {
        return m_rsi;
    }

    void RSI::Init()
    {
        m_instrument = "";
        m_period = -1;
        m_timeframe = 0;
        // m_bar - default
        m_useSmoothing = false;
        m_medUp = -1;
        m_medDown = -1;
        m_RSI = -1;
        m_rsi = -1;
    }
} // namespace