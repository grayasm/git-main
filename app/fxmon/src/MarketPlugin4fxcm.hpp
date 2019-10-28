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


#ifndef __MarketPlugin4fxcm_hpp__
#define __MarketPlugin4fxcm_hpp__

#include "MarketPlugin.hpp"
#include "Session.hpp"


class MarketPlugin4fxcm : public fx::MarketPlugin
{
public:
    MarketPlugin4fxcm(  fxcm::Session* session,
                        const fxcm::IniParams& iniParams);
    ~MarketPlugin4fxcm();

    MarketPlugin4fxcm(const MarketPlugin4fxcm&) = delete;
    MarketPlugin4fxcm& operator=(const MarketPlugin4fxcm&) = delete;

    // --- virtual table ---
    int OpenPosition(   const fx::Offer& offer,
                        int lots,
                        bool buy,
                        stl::vector<fx::Position>& result);

    int ClosePosition(  const fx::Offer& offer,
                        const fx::Position& pos,
                        stl::vector<fx::Position>& result);

    int GetOHLCPrices(  const stl::string& instrument,
                        const stl::string& timeframe,
                        const sys::time& from,
                        const sys::time& to,
                        stl::vector<fx::OHLCPrice>& result);
    // --- end of virtual table ---

private:
    void Log(const stl::string& msg);

private:
    fxcm::Session*        m_session;
    fxcm::IniParams        m_iniParams;
};

#endif // __MarketPlugin4fxcm_hpp__
