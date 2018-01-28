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

#include "GetMarketOffers.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"



void GetMarketOffers()
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
		// idle 1min
		msleep(1000ul * misc::time::minSEC);

	} // while (true)
}
