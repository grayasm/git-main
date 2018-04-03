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
    const fxcm::IniParams& iniParams,
    const fxcm::Session::TradingSettingsVec& tsvec)
{
	m_session = session;
	m_iniParams = iniParams;
    m_tsvec = tsvec;
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
	misc::vector<fx::Position>& result)
{
	misc::autocritical_section acs(m_criticalSection);

    double MMR = 0, pipCost = 0, pointSize = 0;
    for (size_t i = 0; i < m_tsvec.size(); ++i)
    {
        const fxcm::TradingSettings& ts = m_tsvec[i];
        if (ts.GetInstrument() == offer.GetInstrument())
        {
            MMR = ts.GetMMR();
            pipCost = m_pipCost.CalcPipCost(offer, "EUR", 1000); // 1000 = 1k
            pointSize = ts.GetBaseUnitSize();
            break;
        }
    }

	fx::Currency curr(
		offer.GetInstrument(),
		fx::Price(offer.GetAsk(), offer.GetBid()),
		MMR,			    // margin
		pipCost,		    // pipCost
		1.0 / pointSize);   // rate2pip

	fx::Position pos(
		misc::from_value(m_orderID++),
		misc::from_value(m_tradeID++),
		curr,
		buy,
		lots,	// K lots
		0,		// commission
		0,		// interest
		offer.GetTime().totime_t());

	m_posvec.push_back(pos);
	result.push_back(pos);


	// Log open position action.
	if (m_iniParams.GetEnableLogging())
	{
		misc::string msg("Open  ");
		msg += offer.GetTime().tostring();
		for (size_t i = 0; i < result.size(); ++i)
		{
			const fx::Position& ipos = result[i];
			msg += ipos.IsBuy() == true ? " B=" : " S=";
			msg += ipos.IsBuy() == true ?
				misc::from_value(offer.GetAsk(), 5) :
				misc::from_value(offer.GetBid(), 5);
			msg += "\n";
		}
		Log(msg);
	}

	return 0;
}

int MarketPlugin4backtest::ClosePosition(
	const fx::Offer& offer,
	const fx::Position& pos,
	misc::vector<fx::Position>& result)
{
	misc::autocritical_section acs(m_criticalSection);

	misc::vector<fx::Position>::iterator it = m_posvec.begin();
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
		misc::string msg("Close ");
		msg += offer.GetTime().tostring();
		for (size_t i = 0; i < result.size(); ++i)
		{
			const fx::Position& ipos = result[i];

			curPL += ipos.GetPL();
			curGPL += ipos.GetGPL();
			
			msg += ipos.IsBuy() == true ? " S=" : " B=";
			msg += ipos.IsBuy() == true ?
				misc::from_value(offer.GetBid(), 5) :
				misc::from_value(offer.GetAsk(), 5);

			msg += " PL="; msg += misc::from_value(curPL, 2);
			msg += " GPL="; msg += misc::from_value(curGPL, 2);
			msg += "\n";
		}
		Log(msg);
	}
	
	return (!result.empty() == true ? 0 : -1);
}

int MarketPlugin4backtest::GetOHLCPrices(
	const misc::string& instrument,
	const misc::string& timeframe,
	const misc::time& from,
	const misc::time& to,
	misc::vector<fx::OHLCPrice>& result)
{
	misc::autocritical_section acs(m_criticalSection);

	DATE dtFrom = 0, dtTo = 0;

	fxcm::Utils::TimeToDate(from, dtFrom);
	fxcm::Utils::TimeToDate(to, dtTo);

	int ret = m_session->GetHistoryPrices(instrument.c_str(),
		timeframe.c_str(), dtFrom, dtTo, result);

	if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
	{
		misc::cout << __FUNCTION__ <<
			": m_session->GetOHLCPrices returned error: " <<
			fxcm::ErrorCodes::GetText((fxcm::ErrorCodes::ErrorId)ret).c_str()
			<< std::endl;
	}

	return ret;
}

void MarketPlugin4backtest::Log(const misc::string& msg)
{
	misc::autocritical_section acs(m_criticalSection);

	if (!m_iniParams.GetEnableLogging())
		return;

	FILE *pf = fopen(m_iniParams.GetLoggingFile().c_str(), "a+");
	if (pf == NULL)
		return;

	fwrite(msg.c_str(), sizeof(char), msg.size(), pf);
	fclose(pf);
}
