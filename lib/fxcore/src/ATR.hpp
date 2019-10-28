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

#ifndef __ATR_hpp__
#define __ATR_hpp__

#include <list>
#include "IND.hpp"
#include "BAR.hpp"
#include "Offer.hpp"
#include "OHLCPrice.hpp"


namespace fx
{
    class ATR : public IND
    {
    public:
        typedef std::list<fx::OHLCPrice>    OHLCPriceList;
        // Timeframe is time_t

        ATR();
        ATR(const stl::string& instrument, int period, Timeframe sec);
        ~ATR();
        ATR(const ATR& tc);
        ATR& operator=(const ATR& tc);

        // --- virtual table ---
        const stl::string& GetInstrument() const override;
        int GetPeriod() const override;
        Timeframe GetTimeframe() const override;
        bool IsValid() const override;
        void Update(const fx::Offer& offer) override;
        const sys::time& GetRefTime() const override;
        // --- end of virtual table ---

        void GetValue(double& average) const;

    private:
        void Init();

    private:
        stl::string        m_instrument;
        int                    m_period;
        Timeframe            m_timeframe;
        // ----------------------------
        fx::BAR             m_bar;
        double                m_medATR;
        double                m_ATR;
    };
} // namespace

#endif // __ATR_hpp__

