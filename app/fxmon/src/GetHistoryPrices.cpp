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
			ss << "I=" << hprice.GetInstrument().c_str() << ", ";
			ss << "T=" << hprice.GetTime().tostring() << ", ";
			ss << "BO=" << hprice.GetBidOpen() << ", ";
			ss << "BH=" << hprice.GetBidHigh() << ", ";
			ss << "BL=" << hprice.GetBidLow() << ", ";
			ss << "BC=" << hprice.GetBidClose() << ", ";
			ss << "AO=" << hprice.GetAskOpen() << ", ";
			ss << "AH=" << hprice.GetAskHigh() << ", ";
			ss << "AL=" << hprice.GetAskLow() << ", ";
			ss << "AC=" << hprice.GetAskClose() << ", ";
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

void LoadHistoryPrices()
{
	fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");

	// checkObligatoryParams
	if (iniParams->GetHistoryFile().empty())
		return;

	misc::filename historyfile(iniParams->GetHistoryFile());
	if (!historyfile.access(F_OK))
		return; // error

	FILE* pf = fopen(historyfile.get_path().c_str(), "r");
	if (pf == NULL)
		return; // error
	
	misc::vector<fxcm::HistoryPrice> historyPricesVec;
	fxcm::HistoryPrice* hp = new fxcm::HistoryPrice(
		"", 
		"",
		misc::time(),
		0, 0, 0, 0,
		0, 0, 0, 0,
		0);

	misc::string fline;
	int c;
	while ((c = fgetc(pf)) != EOF)
	{
		if (c == '\n')
		{
			char* pch;
			char str[1000];
			strcpy(str, fline.c_str());
			misc::string s1;
			int i = 0;

			pch = strtok(str, ",=");
			while (pch != NULL)
			{
				i++;

				if (i % 2 != 0) { // One of: {I T BO BH BL BC AO AH AL AC V}
					s1 = misc::string(pch);
					misc::trim(s1);
				}
				else if (s1 == "I") {
					hp->SetInstrument(s1.c_str());
				}
				else if (s1 == "T")
				{
					//"2018-JAN-12 23:00:00"
					int year, day, hour, min, sec;
					char mon[5];
					sscanf(pch, "%d-%3s-%d %d:%d:%d",
						&year, mon, &day, &hour, &min, &sec);

					misc::time::Month tmon;
					if (strcmp(mon, "JAN") == 0) tmon = misc::time::JAN;
					else if (strcmp(mon, "FEB") == 0) tmon = misc::time::FEB;
					else if (strcmp(mon, "MAR") == 0) tmon = misc::time::MAR;
					else if (strcmp(mon, "APR") == 0) tmon = misc::time::APR;
					else if (strcmp(mon, "MAY") == 0) tmon = misc::time::MAY;
					else if (strcmp(mon, "JUN") == 0) tmon = misc::time::JUN;
					else if (strcmp(mon, "JUL") == 0) tmon = misc::time::JUL;
					else if (strcmp(mon, "AUG") == 0) tmon = misc::time::AUG;
					else if (strcmp(mon, "SEP") == 0) tmon = misc::time::SEP;
					else if (strcmp(mon, "OCT") == 0) tmon = misc::time::OCT;
					else if (strcmp(mon, "NOV") == 0) tmon = misc::time::NOV;
					else if (strcmp(mon, "DEC") == 0) tmon = misc::time::DEC;
					else
						throw misc::exception("Cannot convert the month from history file");

					misc::time hptime(year, tmon, day, hour, min, sec);
					hp->SetTime(hptime);
				}
				else {
					double val;
					misc::to_value(pch, val);

					if (s1 == "BO") hp->SetBidOpen(val);
					else if (s1 == "BH") hp->SetBidHigh(val);
					else if (s1 == "BL") hp->SetBidLow(val);
					else if (s1 == "BC") hp->SetBidClose(val);
					else if (s1 == "AO") hp->SetAskOpen(val);
					else if (s1 == "AH") hp->SetAskHigh(val);
					else if (s1 == "AL") hp->SetAskLow(val);
					else if (s1 == "AC") hp->SetAskClose(val);
					else if (s1 == "V") hp->SetVolume((int)val);
					else
						throw misc::exception("Cannot convert ID from history file");
				}

				printf("%s\n", pch);
				pch = strtok(NULL, ",=");
			} // while(pch)
			
			historyPricesVec.push_back(*hp);
			fline.resize(0);
			continue;
		} // c == '\n'

		fline.append(1, (char)c);
	}
	
	fclose(pf);
}