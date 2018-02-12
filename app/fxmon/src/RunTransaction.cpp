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
#include "Transaction.hpp"


void ClosePosition(fxcm::Session& session, const fxcm::Offer& offer, const fx::Transaction& trIn);
void OpenPosition(fxcm::Session& session, const fxcm::Offer& offer, int lots, bool buy, fx::Transaction& result);

static const misc::string tradingLog("/tmp/TradingResult.txt");

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


	misc::string instr("EUR/USD");
	fxcm::Offer initialOffer, offer;
	fx::Price price;
	fx::Transaction tr;
	double totalPL = 0;
	double renkoPL = 15; // renko size
	int lotsK = 1;
	bool buy = true;

	//  Frankfurt: Xetra trading takes place from 9.00a.m. until 5.30 p.m. CET. (UTC+100)
	//  New York:  Core Trading Session: 9:30 AM TO 4:00 PM ET (UTC-500)
	int hopen = 8;		// 9 a.m. Frankfurt Open
	int hclose = 18;	// 18-5=13 pm New York, closing 16 pm

	double closedPL = 0;
	double closedGPL = 0;
	
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

			// idle 1m
			msleep(1000ul * misc::time::minSEC);
			continue;
		}

		// trading is active
		if (!isConnected)
		{
			isConnected = session.Login();
			if (isConnected)
			{
				session.GetOffers();
				msleep(3000); // wait 3 sec to fill the price feed
			}
		}

		if (!isConnected)
		{
			// idle 1min
			msleep(1000ul * misc::time::minSEC);
			continue;
		}

		// connected and getting quotes
		msleep(1000);


		if (session.GetLastOffer(offer, instr.c_str()) != fxcm::ErrorCodes::ERR_SUCCESS)
			break; // error with the price feed

		// when can I open a position
		bool canOpen = true; // for now; (tnow.hour_() >= hopen && tnow.hour_() <= hclose);
		if (!canOpen && tr.IsEmpty())
		{
			msleep(1000 * misc::time::minSEC); // slow down a bit
			continue;
		}


		if (tr.IsEmpty())
		{
			// start a new trading day?
			if (initialOffer.GetInstrument().empty())
			{
				initialOffer = offer;
				continue;
			}

			double pointSize = offer.GetPointSize();
			double pips = (offer.GetAsk() - initialOffer.GetAsk()) / pointSize;

			if (pips > renkoPL && canOpen)
			{
				buy = true;
				OpenPosition(session, offer, lotsK, buy, tr);
			}
			else if (pips < -renkoPL && canOpen)
			{
				buy = false;
				OpenPosition(session, offer, lotsK, buy, tr);
			}				
			else
				continue;

			totalPL = 0;
			continue;
		}


		// Manage the position
		fx::Price curprice(offer.GetAsk(), offer.GetBid());
		double curPL = tr.GetPL(instr, curprice); // PL for 1k
		double curGPL = tr.GetGPL(instr, curprice);
		double diffPL = curPL - totalPL;

		if (diffPL > renkoPL)
		{
			totalPL += renkoPL;
			continue;
		}

		if (diffPL < -2 * renkoPL)
		{
			ClosePosition(session, offer, tr);
			
			// TODO: must detect if all positions were closed correctly

			closedPL += curPL;
			closedGPL += curGPL;

			misc::cout << "curPL=" << curPL << " closedGPL=" << closedGPL
				<< std::endl;

			// reset initialOffer at the end of the day
			if (!canOpen)
			{
				initialOffer = fxcm::Offer();
				tr = fx::Transaction();
				totalPL = 0;
			}
			else
			{
				buy = !buy;
				OpenPosition(session, offer, lotsK, buy, tr);
				totalPL = 0;
			}
		}
	} // while

	session.Logout();
}


void OpenPosition(fxcm::Session& session, const fxcm::Offer& offer, int lots, bool buy, fx::Transaction& result)
{
	misc::vector<fx::Position> openPositions;
	session.OpenPosition(offer, lots, buy, openPositions);

	result = fx::Transaction(); // clear
	for (size_t i = 0; i < openPositions.size(); ++i)
	{
		result.Add(openPositions[i]);
	}


	FILE *pf = fopen(tradingLog.c_str(), "a+");
	if (pf == NULL)
		return;

	misc::string slog;
	slog += offer.GetTime().tostring();
	slog += (buy == true ? ", B:" : ", S:");
	slog += (buy == true ? misc::from_value(offer.GetAsk(), 5) :
		misc::from_value(offer.GetBid(), 5));
	slog += ", L(k)=";
	slog += misc::from_value(lots);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}

void ClosePosition(fxcm::Session& session, const fxcm::Offer& offer, const fx::Transaction& trIn)
{
	misc::vector<fx::Position> result;
	bool buy = false;

	const fx::Transaction::Positions& positions = trIn.GetPositions();
	for (size_t i = 0; i < positions.size(); ++i)
	{
		const fx::Position& position = positions[i];
		session.ClosePosition(offer, position, result);
		
		if (i == 0)
			buy = position.IsBuy();
	} // for

	
	FILE *pf = fopen(tradingLog.c_str(), "a+");
	if (pf == NULL)
		return;


	misc::string slog;
	slog += offer.GetTime().tostring();
	slog += (buy == true ? ", S:" : ", B:");
	slog += (buy == true ? misc::from_value(offer.GetBid(), 5) :
		misc::from_value(offer.GetAsk(), 5));
	
	slog += ", PL(1k)=";
	fx::Price price(offer.GetAsk(), offer.GetBid());
	slog += misc::from_value(trIn.GetPL(offer.GetInstrument(), price), 2);
	slog += ", GPL=";
	slog += misc::from_value(trIn.GetPL(offer.GetInstrument(), price), 2);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}