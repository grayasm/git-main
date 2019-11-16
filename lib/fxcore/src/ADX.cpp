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

    ADX - Average Directional Movement Index.

    James Welles Wilder uses the generic term 'Price' without specifying if it
    is the Ask or Bid value. We need consistency in using only Bid or only Ask.
    I used only the Bid price for calculation here. If different - it's a bug.

    All calculations in this file were compared for correctness with the
    Daily Work Sheet "DIRECTIONAL MOVEMENT INDEX" page 41.

    e.g.    TR(1),+DM(1),-DM(1),TR(14),+DM(14),-DM(14),+DI(14),-DI(14)
            DI DIFF,DI SUM,DX,ADX,ADXR,ATR(14)
*/

#include "ADX.hpp"
#include "algorithm.hpp"
#include "numeric.hpp"


namespace fx
{
    ADX::ADX()
    {
        Init();
    }

    ADX::ADX(const stl::string& instrument, int period, Timeframe sec)
    {
        if (period < 2)
            throw stl::exception("ADX period must be greater than 1");

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
            m_useAccumulation = tc.m_useAccumulation;
            m_DM_up = tc.m_DM_up;
            m_DM_down = tc.m_DM_down;
            m_TR = tc.m_TR;
            m_DI_up = tc.m_DI_up;
            m_DI_down = tc.m_DI_down;
            m_DI_diff = tc.m_DI_diff;
            m_DI_add = tc.m_DI_add;
            m_DX_list = tc.m_DX_list;
            m_ADX = tc.m_ADX;
            m_adx = tc.m_adx;
            m_ADX_list = tc.m_ADX_list;
            m_ADXR = tc.m_ADXR;
            m_adxr = tc.m_adxr;
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
        return (m_period > 1 &&
            m_period == m_bar.GetOHLCList().size() &&
            m_ADX > 0);
        // m_ADXR may not be yet valid (-1)
    }

    void ADX::Update(const fx::Offer& offer)
    {
        if (m_instrument != offer.GetInstrument())
            throw stl::exception("ADX offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar.IsNew(offer);

        /*  Use the latest tick data.
            Push the OHLC if new bar is painted.
        */
        m_bar.Update(offer);

        if (isNew)
        {
            //  Current OHLC list is complete.
            if (m_bar.GetOHLCList().size() == m_period && !m_useAccumulation)
            {
                const fx::BARB::OHLCPriceList& ohlcList = m_bar.GetOHLCList();

                fx::BARB::OHLCPriceList::const_iterator previt = ohlcList.begin();
                fx::BARB::OHLCPriceList::const_iterator currit = previt;
                ++currit;

                // Directional Movement (DM) in total
                m_DM_up = 0;
                m_DM_down = 0;

                // True Range (TR) in total
                m_TR = 0;

                for (; currit != ohlcList.end(); ++previt, ++currit)
                {
                    /*  pag. 35-36
                        for an Outside day take the modulo biggest of +DM , -DM
                        for an Inside day the +DM , -DM are zero
                    */
                    double dm_up = 0;
                    double dm_down = 0;

                    if (previt->GetBidHigh() < currit->GetBidHigh())
                        dm_up = currit->GetBidHigh() - previt->GetBidHigh();
                        
                    if (previt->GetBidLow() > currit->GetBidLow())
                        dm_down = currit->GetBidLow() - previt->GetBidLow();
                    
                    if (dm_up > fabs(dm_down))
                        m_DM_up += dm_up;         // SUM of positive values
                    else
                        m_DM_down += dm_down;     // SUM of negative values

                    // TR has same formula as in ATR.cpp
                    double prevC = previt->GetBidClose();
                    double currH = currit->GetBidHigh();
                    double currL = currit->GetBidLow();

                    double v1 = currH - currL;
                    double v2 = fabs(currH - prevC);
                    double v3 = fabs(currL - prevC);

                    double tr = stl::max(v1, stl::max(v2, v3));
                    m_TR += tr;                   // SUM of true range values
                }

                /*  JWW calculation example:
                
                    Once we have determined the first +DM(14) and -DM(14)
                    it is no longer necessary to keep up with 14 day's back data
                    to determine the +DM(14) and -DM(14) for the following day.
                    We use the previous day's data and an accumulation
                    technique in this determination. The advantage to using
                    the accumulation technique is:

                    (1) It eliminates the necessity of keeping up with 14 days' previous data.
                    (2) It incorporates a smoothing effect of the DM.
                */
                m_useAccumulation = true;

                /*  pag.41 
                    +DI -DI DI_sum DI_diff DX are not available in the first 14 days
                    ADX requires 14 days with a valid DX for the first average
                */
            }
            else if (m_useAccumulation)
            {
                fx::BAR::OHLCPriceList::const_reverse_iterator currit = m_bar.GetOHLCList().rbegin();
                fx::BAR::OHLCPriceList::const_reverse_iterator previt = currit; ++previt;
                
                const fx::OHLCPrice& prev = *previt;
                const fx::OHLCPrice& curr = *currit;


                /*  pag. 35-36
                    for an Outside day take the modulo biggest of +DM , -DM
                    for an Inside day the +DM , -DM are zero
                */
                double dm_up = 0;
                double dm_down = 0;

                if (prev.GetBidHigh() < curr.GetBidHigh())
                    dm_up = curr.GetBidHigh() - prev.GetBidHigh();

                if (prev.GetBidLow() > curr.GetBidLow())
                    dm_down = curr.GetBidLow() - prev.GetBidLow();

                if (dm_up > fabs(dm_down))
                    dm_down = 0;                // keep only DM_up
                else
                    dm_up = 0;                  // keep only DM_down


                // TR for current candle
                double prevC = prev.GetBidClose();
                double currH = curr.GetBidHigh();
                double currL = curr.GetBidLow();

                double v1 = currH - currL;
                double v2 = fabs(currH - prevC);
                double v3 = fabs(currL - prevC);

                double tr = stl::max(v1, stl::max(v2, v3));

                /*  JWW formula with the accumulation and smoothing effect:

                    Today's +DM(14) = Previous +DM(14) - (Previous +DM(14) / 14) + Today's +DM(14)
                    Today's -DM(14) = Previous -DM(14) - (Previous -DM(14) / 14) + Today's -DM(14)
                */
                m_DM_up = m_DM_up - m_DM_up / m_period  + dm_up;
                m_DM_down = m_DM_down - m_DM_down / m_period + dm_down;

                /*  JWW formula for the TR:

                    Today's TR(14) = Previous TR(14) - (Previous TR(14) / 14) + TR(1)
                */
                m_TR = m_TR - m_TR / m_period + tr;

                /*  pag.39 JWW formula for PLUS/MINUS DIRECTIONAL INDICATOR

                    +DI(14) = [ +DM(14) / TR(14) ] * 100
                    -DI(14) = [ -DM(14) / TR(14) ] * 100
                */
                m_DI_up = (m_DM_up / m_TR) * 100;
                m_DI_down = (m_DM_down / m_TR) * 100;

                m_DI_diff = fabs(m_DI_up - fabs(m_DI_down));
                m_DI_add = m_DI_up + fabs(m_DI_down);

                /*  pag.40
                    Both up moves and down moves are good directional movement
                    with a high DX resulted value. The turning points will result
                    in low DX values.
                    In order to smooth out this action relative to DX, and make
                    DX indicative of both extreme up and down price movement,
                    the period for determining DX must be twice the period for
                    determining +DI(14) and -DI(14). This can be accomplished
                    simply by using a 14 day average of DX.
                */
                double DX = (m_DI_diff / m_DI_add) * 100;

                m_DX_list.push_back(DX);
                if (m_DX_list.size() > m_period)
                    m_DX_list.pop_front();

                 /* pag.40
                    We compute the DX for 14 days and then at that time begin
                    determining the AVERAGE DIRECITONAL MOVEMENT INDEX (ADX)
                    from the previous day's ADX.
                 */
                if (m_DX_list.size() == m_period)
                {
                    if (m_ADX == -1)
                    {   // use the ADX average
                        double adx = stl::accumulate(m_DX_list.begin(), m_DX_list.end(), .0);
                        m_ADX = adx / m_period;
                        m_ADX_list.push_back(m_ADX);
                    }
                    else
                    {
                        /*  pag.44
                            To obtain the ADX for the 29th day, we use the moving
                            average equation because now we are dealing with
                            averages instead of totals.

                            Today's ADX = (Previous ADX * 13 + Today's DX) / 14
                        */
                        m_ADX = (m_ADX * (m_period - 1) + DX) / m_period;
                        
                        
                        /*  pag.44
                            The ADXR is the final number which is used to rate
                            all commodities, currencies, stocks, etc.,
                            on a rating scale which is indicative of directional
                            movement. The ADXR is simply the ADX today plus
                            the ADX 14 days ago divided by 2.
                        */
                        m_ADX_list.push_back(m_ADX);
                        if (m_ADX_list.size() > m_period)
                            m_ADX_list.pop_front();
                        
                        if (m_ADX_list.size() == m_period)
                            m_ADXR = (m_ADX_list.front() + m_ADX_list.back()) / 2.;
                    }
                }
            }
        }
        else // !isNew
        {
            //  Calculate an intermediary ADX if enough data is available.
            if (m_ADX != -1)
            {
                const fx::OHLCPrice& prev = m_bar.GetOHLCList().back();
                const fx::OHLCPrice& curr = m_bar.GetOHLC();

                /*  pag. 35-36
                    for an Outside day take the modulo biggest of +DM , -DM
                    for an Inside day the +DM , -DM are zero
                */
                double dm_up = 0;
                double dm_down = 0;

                if (prev.GetBidHigh() < curr.GetBidHigh())
                    dm_up = curr.GetBidHigh() - prev.GetBidHigh();

                if (prev.GetBidLow() > curr.GetBidLow())
                    dm_down = curr.GetBidLow() - prev.GetBidLow();

                if (dm_up > fabs(dm_down))
                    dm_down = 0;                // keep only DM_up
                else
                    dm_up = 0;                  // keep only DM_down


                // TR for current candle
                double prevC = prev.GetBidClose();
                double currH = curr.GetBidHigh();
                double currL = curr.GetBidLow();

                double v1 = currH - currL;
                double v2 = fabs(currH - prevC);
                double v3 = fabs(currL - prevC);

                double tr = stl::max(v1, stl::max(v2, v3));

                /*  JWW formula with the accumulation and smoothing effect:

                    Today's +DM(14) = Previous +DM(14) - (Previous +DM(14) / 14) + Today's +DM(14)
                    Today's -DM(14) = Previous -DM(14) - (Previous -DM(14) / 14) + Today's -DM(14)
                */
                double DM_up = m_DM_up - m_DM_up / m_period + dm_up;
                double DM_down = m_DM_down - m_DM_down / m_period + dm_down;

                /*  JWW formula for the TR:

                    Today's TR(14) = Previous TR(14) - (Previous TR(14) / 14) + TR(1)
                */
                double TR = m_TR - m_TR / m_period + tr;

                /*  pag.39 JWW formula for PLUS/MINUS DIRECTIONAL INDICATOR

                    +DI(14) = [ +DM(14) / TR(14) ] * 100
                    -DI(14) = [ -DM(14) / TR(14) ] * 100
                */
                double DI_up = (DM_up / TR) * 100;
                double DI_down = (DM_down / TR) * 100;

                double DI_diff = fabs(DI_up - fabs(DI_down));
                double DI_add = DI_up + fabs(DI_down);

                /*  pag.40
                    Both up moves and down moves are good directional movement
                    with a high DX resulted value. The turning points will result
                    in low DX values.
                    In order to smooth out this action relative to DX, and make
                    DX indicative of both extreme up and down price movement,
                    the period for determining DX must be twice the period for
                    determining +DI(14) and -DI(14). This can be accomplished
                    simply by using a 14 day average of DX.
                */
                double DX = (DI_diff / DI_add) * 100;

                /*  pag.44
                    To obtain the ADX for the 29th day, we use the moving
                    average equation because now we are dealing with
                    averages instead of totals.

                    Today's ADX = (Previous ADX * 13 + Today's DX) / 14
                */
                m_adx = (m_ADX * (m_period - 1) + DX) / m_period;

                if (m_ADXR != -1)
                {
                    double adx_prev = *(++m_ADX_list.begin());
                    m_adxr = (adx_prev + m_adx) / 2.;
                }
            }
        }
    }

    const sys::time& ADX::GetRefTime() const
    {
        return m_bar.GetRefTime();
    }

    double ADX::GetADX() const
    {
        return m_ADX;
    }

    double ADX::GetADX2() const
    {
        return m_adx;
    }

    double ADX::GetADXR() const
    {
        return m_ADXR;
    }

    double ADX::GetADXR2() const
    {
        return m_adxr;
    }

    double ADX::GetDIUp() const
    {
        return m_DI_up;
    }

    double ADX::GetDIDown() const
    {
        return fabs(m_DI_down);
    }

    void ADX::Init()
    {
        m_instrument = "";
        m_period = -1;
        m_timeframe = 0;
        // m_bar - default;
        m_useAccumulation = false;
        m_DM_up = 0;
        m_DM_down = 0;
        m_TR = 0;
        m_DI_up = 0;
        m_DI_down = 0;
        m_DI_diff = 0;
        m_DI_add = 0;
        // m_DX_list - empty
        m_ADX = -1;
        m_adx = -1;
        // m_ADX_list - empty
        m_ADXR = -1;
        m_adxr = -1;
    }
} // namespace
