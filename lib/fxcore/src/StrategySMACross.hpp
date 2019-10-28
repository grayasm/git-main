/*
    Copyright (C) 2018 Mihai Vasilian

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program. If not, see http://www.gnu.org/licenses/.

    contact: grayasm@gmail.com
*/

#ifndef __StrategySMACross_hpp__
#define __StrategySMACross_hpp__

#include "autoptr.hpp"
#include "Offer.hpp"
#include "Transaction.hpp"
#include "MarketPlugin.hpp"
#include "SMA.hpp"

namespace fx
{
    class StrategySMACross
    {
    public:
        typedef stl::autoptr<StrategySMACross> Ptr;

        StrategySMACross(
            fx::MarketPlugin* plugin,
            const stl::string& instrument,
            const fx::SMA& sma1,
            const fx::SMA& sma2);

        ~StrategySMACross();
        StrategySMACross(const StrategySMACross&) = delete;
        StrategySMACross& operator=(const StrategySMACross&) = delete;

        void Update(const fx::Offer& offer);
        bool IsCancelled() const;
        double GetClosedPL() const;
        double GetClosedGPL() const;

    private:
        void OpenPosition(const fx::Offer& offer, bool buy);
        void ClosePosition(const fx::Offer& offer);
        void BuildAllIndicators(const fx::Offer& offer);

    private:
        fx::MarketPlugin*       m_plugin;
        stl::string             m_instrument;
        fx::SMA                 m_sma1;
        fx::SMA                 m_sma2;
        /// ---------------------------
        fx::Transaction         m_tr;
        double                  m_prevBid1;
        double                  m_prevBid2;
        double                  m_closedPL;
        double                  m_closedGPL;
        bool                    m_isCancelled;
    };
} // namespace


#endif // __StrategySMACross_hpp__
