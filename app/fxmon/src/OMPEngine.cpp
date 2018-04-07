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
#include <omp.h>
#include <map>
#include <functional>
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


    // MarketPlugin4backtest needs a valid session to calculate things
    // like the pip cost, MMR, iBaseUnitSize, etc.
    // Depending on the traded instrument, the pipCost calculator may need
    // access to other offers to convert the quote into account currency.
	misc::string instrument("EUR/USD");
    int ret = 0;
    fx::Offer offer;

    fxcm::Session session(*loginParams, *iniParams);
    session.Login();
    session.GetOffers();
    msleep(3000); // wait to get the offers
    
    ret = session.GetLastOffer(offer, instrument.c_str());
    if (ret != fxcm::ErrorCodes::ERR_SUCCESS ||
        offer.GetInstrument().empty() ||
        offer.GetPointSize() == 0 ||
        offer.GetPrecision() == 0)
        return;


	MarketPlugin4backtest plugin(&session, *iniParams);
	HistdatacomReader oreader(offer, 2017);
	misc::time reftime;
	misc::vector<fx::IND*> smaVec;
	misc::vector<fx::StrategySMACross*> strategyVec;
	typedef misc::pair<misc::string, fx::StrategySMACross*> CrossPair;
	misc::vector<CrossPair> crossVec;
	
    
	// SMA(2, 1H) -> SMA(48, 1H)
	// SMA(2, 1D) -> SMA(60, 1D)
	for (int i = 2; i <= 48; ++i)	// 48hours
	{
		fx::SMA* sma = new fx::SMA(instrument, i, misc::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
		smaVec.push_back(sma);
	}

	for (int i = 2; i <= 20; ++i)	// 60days
	{
		fx::SMA* sma = new fx::SMA(instrument, i, misc::time::daySEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
		smaVec.push_back(sma);
	}
	
	if (!oreader.GetOffer(offer))
		return; // cannot get the offer?

	reftime = offer.GetTime();
	misc::cout << reftime.tostring() << std::endl;

	
	fx::IndicatorBuilder::Build(&plugin, offer, smaVec);
	
	
	for (int i = 0; i < smaVec.size()-1; ++i)
	{
		for (int j = i + 1; j < smaVec.size(); ++j)
		{
			fx::SMA* sma1 = static_cast<fx::SMA*>(smaVec[i]);
			fx::SMA* sma2 = static_cast<fx::SMA*>(smaVec[j]);

			fx::StrategySMACross* strategy =
				new fx::StrategySMACross(
				&plugin,
				instrument,
				*sma1,
				*sma2);
			strategyVec.push_back(strategy);

			std::stringstream ss;
			ss << "SMA1(" << sma1->GetPeriod() << ",";
			ss << (sma1->GetTimeframe() == misc::time::hourSEC ? "H) " : "D) ");
			ss << "SMA2(" << sma2->GetPeriod() << ",";
			ss << (sma2->GetTimeframe() == misc::time::hourSEC ? "H) " : "D) ");
			misc::string str(ss.str().c_str());
			CrossPair cpair(str, strategy);
			crossVec.push_back(cpair);
		}
	}
	

	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;

		if (reftime.mon_() != offer.GetTime().mon_())
		{
			reftime = offer.GetTime();
			// show some progress, otherwise confusing and very slow
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


		int i = 0;
#pragma omp parallel shared(strategyVec, offer) private(i)
		{
#pragma omp for
			for (i = 0; i < strategyVec.size(); ++i)
			{
				strategyVec[i]->Update(offer);

				// printf("thread %d strategyVec[%d]\n", omp_get_thread_num(), i);
			}
		} // omp parallel
		
	} // while

	session.Logout();

	std::function<bool(const CrossPair&, const CrossPair&)> lmdbpred
		= [](const CrossPair& cp1, const CrossPair& cp2) -> bool
	{
		return (cp1.second->GetClosedGPL() > cp2.second->GetClosedGPL());
	};

	misc::sort(crossVec.begin(), crossVec.end(), lmdbpred);

	// use logging only summary data
	FILE* fp = fopen(iniParams->GetLoggingFile().c_str(), "w+");

	
	for (misc::vector<CrossPair>::iterator it = crossVec.begin();
		 it != crossVec.end() && fp != NULL; ++it)
	{
		std::stringstream ss;
		ss << it->first;
		ss << " PL=" << it->second->GetClosedPL();
		ss << " GPL=" << it->second->GetClosedGPL() << std::endl;
		std::string str(ss.str());
		fwrite(str.c_str(), sizeof(char), str.size(), fp);
	}

	if (fp) fclose(fp);

	misc::cout << "Log file update.\nDestroying...\n";

	for (int i = 0; i < strategyVec.size(); ++i)
		delete strategyVec[i];

	for (int i = 0; i < smaVec.size(); ++i)
		delete smaVec[i];
}

