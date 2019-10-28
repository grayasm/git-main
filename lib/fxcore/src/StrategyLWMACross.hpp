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

#ifndef __StrategyLWMACross_hpp__
#define __StrategyLWMACross_hpp__

#include "autoptr.hpp"
#include "MarketPlugin.hpp"
#include "HABAR.hpp"
#include "LWMA.hpp"
#include "Transaction.hpp"


namespace fx
{
    class StrategyLWMACross
    {
    public:
        typedef stl::autoptr<StrategyLWMACross> Ptr;

        StrategyLWMACross(
            fx::MarketPlugin* plugin,
            const stl::string& instrument);

        ~StrategyLWMACross();
        StrategyLWMACross(const StrategyLWMACross&) = delete;
        StrategyLWMACross& operator=(const StrategyLWMACross&) = delete;

        void Update(const fx::Offer& offer);
        bool IsCancelled() const;
        double GetClosedPL() const;
        double GetClosedGPL() const;

    private:
        void OpenPosition(const fx::Offer& offer, bool buy);
        void ClosePosition(const fx::Offer& offer);
        void BuildAllIndicators(const fx::Offer& offer);


    private:
        fx::MarketPlugin*   m_plugin;
        stl::string         m_instrument;
        // ------------------------------
        fx::HABAR           m_habar;
        fx::LWMA            m_lwma1;
        fx::LWMA            m_lwma2;
        fx::Transaction     m_tr;
        double              m_closedPL;
        double              m_closedGPL;
        bool                m_isCancelled;
        // ------------------------------
    };
} // namespace

#endif // __StrategyLWMACross_hpp__
