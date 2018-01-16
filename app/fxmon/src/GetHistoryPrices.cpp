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

#include "GetHistoryPrices.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "Offer.hpp"
#include "ErrorCodes.hpp"
#include "time.hpp"
#include "filename.hpp"


static void Time2DATE(time_t tt, DATE& dt);

void GetHistoryPrices()
{
	fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");

	// checkObligatoryParams
	if (loginParams->GetLogin().empty() ||
		loginParams->GetPassword().empty() ||
		loginParams->GetUrl().empty() ||
		loginParams->GetConnection().empty() ||
		iniParams->GetInstrument().empty() ||
		iniParams->GetTimeframe().empty() ||
		iniParams->GetDateFrom().empty() ||
		iniParams->GetDateTo().empty() ||
		iniParams->GetHistoryFile().empty() )
		return;
	
	int toff = 0;

	if (iniParams->GetTimeframe() == "m1")
		toff = misc::time::hourSEC; // 60mins
	else if (iniParams->GetTimeframe() == "H1")
		toff = misc::time::hourSEC * 60; // 60hours
	else
		return; // error
	
	misc::filename historyfile(iniParams->GetHistoryFile());
	if (!historyfile.access(F_OK))
		return; // error
	FILE* pf = fopen(historyfile.get_path().c_str(), "a");
	if (pf == NULL)
		return; // error
	
	
	// m.d.Y H:M:S
	misc::time tFrom(iniParams->GetDateFrom());
	misc::time tTo(iniParams->GetDateTo());	
	misc::time tEnd = tFrom;
	tEnd += toff;


	fxcm::Session session(*loginParams, *iniParams);
	session.Login();

	misc::vector<fxcm::HistoryPrice> historyPricesVec;
	for (; tFrom < tTo; tFrom += toff, tEnd += toff)
	{
		if (tEnd > tTo)
			tEnd = tTo;

		DATE dtFrom, dtEnd;
		Time2DATE(tFrom.totime_t(), dtFrom);
		Time2DATE(tEnd.totime_t(), dtEnd);

		session.GetHistoryPrices(
			iniParams->GetInstrument().c_str(),
			iniParams->GetTimeframe().c_str(),
			dtFrom, dtEnd,
			historyPricesVec);

		for (size_t i = 0; i < historyPricesVec.size(); ++i)
		{
			const fxcm::HistoryPrice& hprice = historyPricesVec[i];

			std::stringstream ss;
			ss << "I=" << hprice.GetInstrument().c_str() << " ";
			ss << "T=" << hprice.GetTime().tostring() << " ";
			ss << "BO=" << hprice.GetBidOpen() << " ";
			ss << "BH=" << hprice.GetBidHigh() << " ";
			ss << "BL=" << hprice.GetBidLow() << " ";
			ss << "BC=" << hprice.GetBidClose() << " ";
			ss << "AO=" << hprice.GetAskOpen() << " ";
			ss << "AH=" << hprice.GetAskHigh() << " ";
			ss << "AL=" << hprice.GetAskLow() << " ";
			ss << "AC=" << hprice.GetAskClose() << " ";
			ss << "V=" << hprice.GetVolume() << "\n";
			
			std::string str(ss.str());
			fwrite(str.c_str(), 1, str.size(), pf);
		}
	}

	fclose(pf);

	session.Logout();
}

static void Time2DATE(time_t tt, DATE& dt)
{
	struct tm *tmNow = gmtime(&tt);
	CO2GDateUtils::CTimeToOleTime(tmNow, &dt);
}
