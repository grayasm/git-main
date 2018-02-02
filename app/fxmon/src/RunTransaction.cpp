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
	
	
	fxcm::Offer offer0, offer1; 
	fx::Position curpos;
	misc::vector<fx::Position> result;
	double totalPL = 0;
	double incPL = 2;	// renko size
	int lots = 1;


	while (true)
	{
		// outside trading hours?
		misc::time tnow(::time(NULL));
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			if (isConnected)
			{
				if (session.Logout())
					isConnected = false;
			}

			// idle 1H
			msleep(1000ul * misc::time::hourSEC);
			continue;
		}

		// trading is active
		if (!isConnected)
		{
			isConnected = session.Login();
			if (isConnected)
				session.GetOffers();
		}

		if (!isConnected)
		{
			// idle 1min
			msleep(1000ul * misc::time::minSEC);
			continue;
		}

		// connected and getting quotes
		// idle 2sec
		msleep(2000);


		// run trading with 1 position (renko:2)
		session.GetLastOffer(offer1, "EUR/USD");

		if (offer0.GetInstrument().empty())
		{
			offer0 = offer1;
			continue;
		}


		// trade daily between CET: 09:00 - 22:00
		// 9:00 Frankfurt open, 22:00 is 1h before NewYork close
		bool canOpen = (tnow.hour_() >= 8 && tnow.hour_() <= 21);
		if (curpos.GetCurrency().GetSymbol().empty())
		{
			double pips = (offer1.GetAsk() - offer0.GetAsk()) / 0.0001;

			if (pips > incPL && canOpen  )
				session.OpenPosition(offer1, lots, true, result);
			else if (pips < -incPL && canOpen)
				session.OpenPosition(offer1, lots, false, result);
			else
				continue;

			if (result.size() != 1)
				break;

			curpos = result[0];
			totalPL = 0;

			continue;
		}

		// Manage the position
		fx::Price curprice(offer1.GetAsk(), offer1.GetBid());
		double curPL = curpos.GetPL(curprice);
		double curGPL = curpos.GetGPL(curprice);
		double diffPL = curPL - totalPL;


		if (diffPL > incPL)
		{
			totalPL += incPL;
			continue;
		}

		if (diffPL < -2*incPL)
		{
			int res = fxcm::ErrorCodes::ERR_SUCCESS;
			res = session.ClosePosition(offer1, curpos, result);

			if (result.empty() || res != fxcm::ErrorCodes::ERR_SUCCESS)
				break; // error

			// reset the trade
			curpos = fx::Position();
			totalPL = 0;
			result.clear();
			offer0 = fxcm::Offer();

			// continue if allowed
			if (canOpen)
			{
				res = session.OpenPosition(offer1, lots, !curpos.IsBuy(), result);

				if (result.size() != 1 || res != fxcm::ErrorCodes::ERR_SUCCESS)
					break; // error

				curpos = result[0];
				totalPL = 0;
				offer0 = offer1;
			}			
		}
	} // while

	session.Logout();
}
