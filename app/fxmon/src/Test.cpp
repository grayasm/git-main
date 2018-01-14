/*
  Copyright (C) 2014 Mihai Vasilian

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


#include "unistd.hpp"
#include "stream.hpp"

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "Offer.hpp"
#include "ErrorCodes.hpp"
#include "time.hpp"

static void Time2DATE(time_t tt, DATE& dt);

int test2()
{
	fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");

	// checkObligatoryParams
	if (loginParams->GetLogin().empty() ||
		loginParams->GetPassword().empty() ||
		loginParams->GetUrl().empty() ||
		loginParams->GetConnection().empty() ||
		iniParams->GetInstrument().empty())
		return -1;

	fxcm::Session session(*loginParams, *iniParams);
	session.Login();
	session.GetOffers();
	session.GetOrders();

	misc::vector<fxcm::HistoryPrice> historyPricesVec;
	int toff = misc::time::hourSEC;
	misc::time tbeg(2018, misc::time::JAN, 8, 0, 0, 0);
	misc::time tnext = tbeg + toff;
	misc::time tend(2018, misc::time::JAN, 12, 23, 59, 0);

	for (; tbeg < tend; tbeg += toff, tnext += toff)
	{
		DATE dtFrom, dtTo;
		Time2DATE(tbeg.totime_t(), dtFrom);
		Time2DATE(tnext.totime_t(), dtTo);

		session.GetHistoryPrices(
			"EUR/USD", "m1",
			dtFrom, dtTo,
			historyPricesVec);
	}
	
	session.Logout();
	
	return 0;
}

static void Time2DATE(time_t tt, DATE& dt)
{
	struct tm *tmNow = gmtime(&tt);
	CO2GDateUtils::CTimeToOleTime(tmNow, &dt);
}
