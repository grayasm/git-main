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

#ifndef __PSAR_hpp__
#define __PSAR_hpp__

#include <list>
#include "string.hpp"
#include "IND.hpp"
#include "BAR.hpp"
#include "Price.hpp"
#include "OHLCPrice.hpp"



namespace fx
{
    class SAR : public IND
    {
    public:
        typedef std::list<fx::OHLCPrice>    OHLCPriceList;
        typedef std::list<fx::Price>        SARList;
        // Timeframe is time_t

        SAR();
        SAR(const stl::string& instrument, int period, Timeframe sec);

        ~SAR();
        SAR(const SAR& tc);
        SAR& operator=(const SAR& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        bool GetIsBuy() const;
        void GetValue(fx::Price& sar) const;
        void GetOHLC(fx::OHLCPrice& ohlc) const;
        void GetEP(fx::Price& ep) const;
        void GetAF(double& af) const;

    private:
        void Init();

    private:
        stl::string         m_instrument;
        int                 m_period;
        Timeframe           m_timeframe;
        // -----------------------------
        fx::BAR             m_bar;
        SARList             m_sarList;
        bool                m_isBuy;
        double              m_AF;
        fx::Price           m_EP;
        fx::Price           m_SAR;
    };
} // namespace

#endif // __PSAR_hpp__
