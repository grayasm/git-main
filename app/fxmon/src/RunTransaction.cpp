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

	msleep(2000ul); // wait to update

	// outside trading hours?
	fxcm::Offer offer;
	session.GetLastOffer(offer, "EUR/USD");

	session.OpenMarketOrder(offer, 1, true);

	// during hours?
	msleep(2000ul);

	session.Logout();
}
