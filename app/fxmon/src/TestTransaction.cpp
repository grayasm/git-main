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

#include "TestTransaction.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"
#include "StrategyRenkoAtr.hpp"
#include "MarketPlugin4backtest.hpp"
#include "HistdatacomReader.hpp"



void TestTransaction()
{
	fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");


	// checkObligatoryParams
	if (loginParams->GetLogin().empty() ||
		loginParams->GetPassword().empty() ||
		loginParams->GetUrl().empty() ||
		loginParams->GetConnection().empty())
		return;


	fx::Offer offer;
	misc::string instrument("EUR/USD");
	fxcm::Session session(*loginParams, *iniParams);
	MarketPlugin4backtest plugin(&session, *iniParams);
	fx::StrategyRenkoAtr strategy(&plugin, instrument, 15, 8, 17);
	HistdatacomReader oreader(instrument);

	// needs session for history prices only
	session.Login();

	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;


		// check for outside trading hours
		misc::time tnow = offer.GetTime();
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			continue;
		}

		strategy.Update(offer);

		if (strategy.IsCanceled())
			break; // error with the strategy

	} // while

	session.Logout();

}

