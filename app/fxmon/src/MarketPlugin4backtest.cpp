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

#include "MarketPlugin4backtest.hpp"

#include "stream.hpp"
#include "strconv.hpp"
#include "autocritical_section.hpp"
#include "Utils.hpp"
#include "ErrorCodes.hpp"


MarketPlugin4backtest::MarketPlugin4backtest(
    fxcm::Session* session,
    const fxcm::IniParams& iniParams)
{
    m_session = session;
    m_iniParams = iniParams;
    // m_pipCost - default;
    // m_criticalSection - default;
    m_orderID = 0;
    m_tradeID = 0;
    // m_posvec - clean;
}

MarketPlugin4backtest::~MarketPlugin4backtest()
{

}


int MarketPlugin4backtest::OpenPosition(
    const fx::Offer& offer,
    int lots,
    bool buy,
    stl::vector<fx::Position>& result)
{
    sys::autocritical_section acs(m_criticalSection);

    stl::string instrument = offer.GetInstrument();
    stl::string acc_symbol = m_iniParams.GetAccountSymbol();
    double MMR = 0, pipCost = 0;
    int iBaseUnitSize = 0, ret = 0;

    // get trading settings once per session
    if (m_tsVec.empty())
    {
        ret = m_session->GetTradingSettings(m_tsVec);
        if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
            return ret;
    }


    // get Instrument data: MMR=2.5  baseUnitSize=1000  pipCost=0.9
    for (size_t i = 0; i < m_tsVec.size(); ++i)
    {
        const fxcm::TradingSettings& ts = m_tsVec[i];
        if (ts.GetInstrument() == instrument)
        {
            MMR = ts.GetMMR();
            iBaseUnitSize = ts.GetBaseUnitSize();

            std::map<stl::string, double>::iterator it = 
                m_pipCostMap.find(offer.GetInstrument());
            if (it == m_pipCostMap.end())
            {
                fxcm::PipCost::OffersMap offers;
                ret = m_session->GetAllOffers(offers);
                if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
                    return ret;

                pipCost = m_pipCost.CalcPipCost(instrument, acc_symbol,
                                                iBaseUnitSize, offers);
                m_pipCostMap.insert(std::make_pair(instrument, pipCost));
            }
            else
            {
                pipCost = it->second;
            }
            
            break;
        }
    }

    fx::Currency curr(
        offer.GetInstrument(),
        fx::Price(offer.GetAsk(), offer.GetBid()),
        MMR,                // margin
        pipCost,            // pipCost
        1.0 / offer.GetPointSize());// rate2pip

    fx::Position pos(
        stl::from_value(m_orderID++),
        stl::from_value(m_tradeID++),
        curr,
        buy,
        lots,    // K lots
        0,        // commission
        0,        // interest
        offer.GetTime().totime_t());

    m_posvec.push_back(pos);
    result.push_back(pos);


    // Log open position action.
    if (m_iniParams.GetEnableLogging())
    {
        stl::string msg("Open  ");
        msg += offer.GetTime().tostring();
        for (size_t i = 0; i < result.size(); ++i)
        {
            const fx::Position& ipos = result[i];
            msg += ipos.IsBuy() == true ? " B=" : " S=";
            msg += ipos.IsBuy() == true ?
                stl::from_value(offer.GetAsk(), 5) :
                stl::from_value(offer.GetBid(), 5);
            msg += "\n";
        }
        Log(msg);
    }

    return 0;
}

int MarketPlugin4backtest::ClosePosition(
    const fx::Offer& offer,
    const fx::Position& pos,
    stl::vector<fx::Position>& result)
{
    sys::autocritical_section acs(m_criticalSection);

    stl::vector<fx::Position>::iterator it = m_posvec.begin();
    for (; it != m_posvec.end(); ++it)
    {
        if (pos.GetTradeID() == it->GetTradeID())
        {
            fx::Position& cpos = *it;

            fx::Price price(offer.GetAsk(), offer.GetBid());
            cpos.Close(price, offer.GetTime().totime_t());
            
            result.push_back(cpos);
            m_posvec.erase(it);

            break;
        }
    }

    // Log close position action.
    if (m_iniParams.GetEnableLogging())
    {
        double curPL = 0, curGPL = 0;
        stl::string msg("Close ");
        msg += offer.GetTime().tostring();
        for (size_t i = 0; i < result.size(); ++i)
        {
            const fx::Position& ipos = result[i];

            curPL += ipos.GetPL();
            curGPL += ipos.GetGPL();
            
            msg += ipos.IsBuy() == true ? " S=" : " B=";
            msg += ipos.IsBuy() == true ?
                stl::from_value(offer.GetBid(), 5) :
                stl::from_value(offer.GetAsk(), 5);

            msg += " PL="; msg += stl::from_value(curPL, 2);
            msg += " GPL="; msg += stl::from_value(curGPL, 2);
            msg += "\n";
        }
        Log(msg);
    }
    
    return (!result.empty() == true ? 0 : -1);
}

int MarketPlugin4backtest::GetOHLCPrices(
    const stl::string& instrument,
    const stl::string& timeframe,
    const sys::time& from,
    const sys::time& to,
    stl::vector<fx::OHLCPrice>& result)
{
    sys::autocritical_section acs(m_criticalSection);

    DATE dtFrom = 0, dtTo = 0;

    fxcm::Utils::TimeToDate(from, dtFrom);
    fxcm::Utils::TimeToDate(to, dtTo);

    int ret = m_session->GetHistoryPrices(instrument.c_str(),
        timeframe.c_str(), dtFrom, dtTo, result);

    if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
    {
        stl::cout << __FUNCTION__ <<
            ": m_session->GetOHLCPrices returned error: " <<
            fxcm::ErrorCodes::GetText((fxcm::ErrorCodes::ErrorId)ret).c_str()
            << std::endl;
    }

    return ret;
}

void MarketPlugin4backtest::Log(const stl::string& msg)
{
    sys::autocritical_section acs(m_criticalSection);

    if (!m_iniParams.GetEnableLogging())
        return;

    FILE *pf = fopen(m_iniParams.GetLoggingFile().c_str(), "a+");
    if (pf == NULL)
        return;

    fwrite(msg.c_str(), sizeof(char), msg.size(), pf);
    fclose(pf);
}
