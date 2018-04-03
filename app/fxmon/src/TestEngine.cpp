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

#include "TestEngine.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"
//#include "StrategyRenkoAtr.hpp"
// #include "StrategySMACross.hpp"
#include "StrategyLWMACross.hpp"
#include "MarketPlugin4backtest.hpp"
#include "HistdatacomReader.hpp"
// #include "HistoryFxcmliveReader.hpp"




void TestEngine()
{
	fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");


	// checkObligatoryParams
	if (loginParams->GetLogin().empty() ||
		loginParams->GetPassword().empty() ||
		loginParams->GetUrl().empty() ||
		loginParams->GetConnection().empty())
		return;

	if (iniParams->GetEnableLogging())
	{
		const misc::string& lfile = iniParams->GetLoggingFile();
		FILE* fp = fopen(lfile.c_str(), "w+");
		if (fp)
			fclose(fp);
	}


    // initialize the indicators only and get technical data about instrument
    // no position will be opened or closed in the market here
    misc::string instrument("USD/JPY");
    fxcm::Session session(*loginParams, *iniParams);
    session.Login();
    fxcm::Session::TradingSettingsVec tsvec;
    session.GetTradingSettings(tsvec);
    fxcm::TradingSettings ts;
    for (size_t i = 0; i < tsvec.size(); ++i)
    {
        if (tsvec[i].GetInstrument() == instrument)
        {
            ts = tsvec[i];
            break;
        }
    }
    if (ts.GetInstrument().empty())
        return;
    // ----------------------------



	fx::Offer offer;
	MarketPlugin4backtest plugin(&session, *iniParams, tsvec);
	HistdatacomReader oreader(instrument, 2017, 3, ts.GetBaseUnitSize());
	// HistoryFxcmliveReader oreader(instrument);
	// fx::SMA sma1(instrument, 4, misc::time::hourSEC, fx::SMA::PRICE_CLOSE);
	// fx::SMA sma2(instrument, 60, misc::time::daySEC, fx::SMA::PRICE_CLOSE);
	// fx::StrategySMACross strategy(&plugin, instrument, sma1, sma2);
	// fx::StrategyRenkoAtr strategy(&plugin, instrument, 15, 7, 16);
    fx::StrategyLWMACross strategy(&plugin, instrument);


	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;

		// check for outside trading hours
		misc::time tnow = offer.GetTime();
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 21) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 21))
		{
			continue;
		}

		strategy.Update(offer);

		if (strategy.IsCancelled())
			break; // error with the strategy

	} // while

	session.Logout();

	// log total GPL
	if (iniParams->GetEnableLogging())
	{
		const misc::string& lfile = iniParams->GetLoggingFile();
		FILE* fp = fopen(lfile.c_str(), "a");
		if (fp)
		{
			std::stringstream ss;
			ss << "closedPL=" << strategy.GetClosedPL() <<
				" closedGPL=" << strategy.GetClosedGPL() << std::endl;
			fwrite(ss.str().c_str(), sizeof(char), ss.str().size(), fp);
			fclose(fp);
		}
	}
}

