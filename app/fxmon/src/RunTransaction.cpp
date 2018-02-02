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

#include "RunTransaction.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"



void RunTransaction()
{
	fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");


	// checkObligatoryParams
	if (loginParams->GetLogin().empty() ||
		loginParams->GetPassword().empty() ||
		loginParams->GetUrl().empty() ||
		loginParams->GetConnection().empty())
		return;


	bool isConnected = false;
	fxcm::Session session(*loginParams, *iniParams);
	if (!session.Login())
		return;

	session.GetOffers();

	misc::vector<fx::Position> result;
	fx::Position curpos;
	fxcm::Offer offer0, offer1;
	double lastPL = 0;

	while (true)
	{
		msleep(2000);

		session.GetLastOffer(offer1, "EUR/USD");

		if (offer0.GetInstrument().empty())
		{
			offer0 = offer1;
			continue;
		}


		// check if to enter market
		if (curpos.GetCurrency().GetSymbol().empty())
		{
			double pips = (offer1.GetAsk() - offer0.GetAsk()) / 0.0001;

			if (pips > 2)
				session.OpenPosition(offer1, 1, true, result);
			else if (pips < -2)
				session.OpenPosition(offer1, 1, false, result);

			if (!result.empty())
			{
				curpos = result[0];
				lastPL = 0;
			}

			continue;
		}

		// manage the open position
		fx::Price curprice(offer1.GetAsk(), offer1.GetBid());
		double curPL = curpos.GetPL(curprice);
		double diffPL = curPL - lastPL;

		if (diffPL > 5)
		{
			lastPL += 5;
			continue;
		}

		if (diffPL < -5)
		{
			session.ClosePosition(offer1, curpos, result);

			if (result.empty()) // error
				break;

			session.OpenPosition(offer1, 1, !curpos.IsBuy(), result);

			if (result.empty()) // error
				break;
			
			curpos = result[0];
			lastPL = 0;
		}
	} // while

	session.Logout();
}
