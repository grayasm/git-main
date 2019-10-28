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


#ifndef __MarketPlugin4backtest_hpp__
#define __MarketPlugin4backtest_hpp__

#include "vector.hpp"
#include "critical_section.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "MarketPlugin.hpp"
#include "Position.hpp"



class MarketPlugin4backtest : public fx::MarketPlugin
{
public:
    // session is used only for OHLC history prices
    MarketPlugin4backtest(    fxcm::Session* session,
                            const fxcm::IniParams& iniParams);
    ~MarketPlugin4backtest();

    MarketPlugin4backtest(const MarketPlugin4backtest&) = delete;
    MarketPlugin4backtest& operator=(const MarketPlugin4backtest&) = delete;

    // --- virtual table ---
    int OpenPosition(    const fx::Offer& offer,
                        int lots,
                        bool buy,
                        stl::vector<fx::Position>& result);

    int ClosePosition(    const fx::Offer& offer,
                        const fx::Position& pos,
                        stl::vector<fx::Position>& result);

    int GetOHLCPrices(    const stl::string& instrument,
                        const stl::string& timeframe,
                        const sys::time& from,
                        const sys::time& to,
                        stl::vector<fx::OHLCPrice>& result);
    // --- end of virtual table ---

private:
    void Log(const stl::string& msg);

private:
    fxcm::Session*                          m_session;
    fxcm::IniParams                         m_iniParams;
    stl::vector<fxcm::TradingSettings>      m_tsVec;
    fxcm::PipCost                           m_pipCost;
    std::map<stl::string, double>           m_pipCostMap;
    sys::critical_section                   m_criticalSection;
    int                                     m_orderID;
    int                                     m_tradeID;
    stl::vector<fx::Position>               m_posvec;
};

#endif // __MarketPlugin4backtest_hpp__
