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

	misc::vector<fx::Position> trades;
	fxcm::Offer offer0, offer1;

	while (true)
	{
		msleep(2000);

		
		session.GetLastOffer(offer1, "EUR/USD");
		if (offer0.GetInstrument().empty())
		{
			offer0 = offer1;
			continue;
		}

		double pips = offer1.GetAsk() - offer0.GetAsk();
		if ( pips > 0.0001)
		{
			session.OpenMarketOrder(offer1, 1, true, trades);
			offer0 = offer1;
			continue;
		}

		if (trades.size() == 3)
			break;
	}

	session.Logout();
}
