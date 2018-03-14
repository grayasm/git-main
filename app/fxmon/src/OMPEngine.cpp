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

#include "OMPEngine.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"
#include "IndicatorBuilder.hpp"
#include "StrategySMACross.hpp"
#include "MarketPlugin4backtest.hpp"
#include "HistdatacomReader.hpp"



void OMPEngine()
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
		return; // cannot let > 500 strategies write in one file; turn it off;


	fx::Offer offer;
	misc::string instrument("EUR/USD");
	fxcm::Session session(*loginParams, *iniParams);
	MarketPlugin4backtest plugin(&session, *iniParams);
	HistdatacomReader oreader(instrument);
	misc::time reftime;

	misc::vector<fx::IND*> smaVec;	
	
	// SMA(2, 1H) -> SMA(48, 1H)
	// SMA(2, 1D) -> SMA(60, 1D)

	for (int i = 2; i <= 48; ++i)
	{
		fx::SMA* sma = new fx::SMA(instrument, i, misc::time::hourSEC, fx::SMA::PRICE_CLOSE);
		smaVec.push_back(sma);
	}

	for (int i = 2; i <= 60; ++i)
	{
		fx::SMA* sma = new fx::SMA(instrument, i, misc::time::daySEC, fx::SMA::PRICE_CLOSE);
		smaVec.push_back(sma);
	}
	
	if (!oreader.GetOffer(offer))
		return; // cannot get the offer?

	reftime = offer.GetTime();
	misc::cout << reftime.tostring() << std::endl;

	// needs session for history prices only
	session.Login();

	fx::IndicatorBuilder::Build(&plugin, offer, smaVec);
	
	misc::vector<fx::StrategySMACross*> strategyVec;
	for (int i = 0; i < smaVec.size(); ++i)
	{
		int j = smaVec.size() - i - 1;
		if (i > j)
			break;

		fx::SMA* sma1 = static_cast<fx::SMA*>(smaVec[i]);
		fx::SMA* sma2 = static_cast<fx::SMA*>(smaVec[j]);

		fx::StrategySMACross* strategy =
			new fx::StrategySMACross(
			&plugin,
			instrument,
			*sma1,
			*sma2);
		strategyVec.push_back(strategy);
	}



	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;

		if (reftime.mon_() != offer.GetTime().mon_())
		{
			reftime = offer.GetTime();
			misc::cout << reftime.tostring() << std::endl;
		}

		// check for outside trading hours
		misc::time tnow = offer.GetTime();
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			continue;
		}

		for (size_t i = 0; i < strategyVec.size(); ++i)
		{
			fx::StrategySMACross* strategy = strategyVec[i];
			if (strategy->IsCancelled())
				return; // error in strategy

			strategy->Update(offer);
		}
	} // while

	session.Logout();

	for (int i = 0; i < smaVec.size(); ++i)
	{
		int j = smaVec.size() - i - 1;
		if (i > j)
			break;

		int period1 = smaVec[i]->GetPeriod();
		time_t timeframe1 = smaVec[i]->GetTimeframe();

		int period2 = smaVec[j]->GetPeriod();
		time_t timeframe2 = smaVec[j]->GetTimeframe();

		double PL = strategyVec[i]->GetClosedPL();
		double GPL = strategyVec[i]->GetClosedGPL();

		misc::cout << "SMA(" << period1 << ", "
			<< (timeframe1 == misc::time::hourSEC ? "H" : "D")
			<< ") PL=" << misc::from_value(PL, 2).c_str()
			<< " GPL=" << misc::from_value(GPL, 2).c_str() << std::endl;
	}

	misc::cout << "Destroying...\n";

	for (int i = 0; i < strategyVec.size(); ++i)
		delete strategyVec[i];

	for (int i = 0; i < smaVec.size(); ++i)
		delete smaVec[i];
}

