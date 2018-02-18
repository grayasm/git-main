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


void OpenPosition(	const fxcm::IniParams& iniParams,
					fxcm::Session& session,
					const fxcm::Offer& offer,
					int lots,
					bool buy,
					fx::Transaction& result);

void ClosePosition(	const fxcm::IniParams& iniParams,
					fxcm::Session& session,
					const fxcm::Offer& offer,
					const fx::Transaction& trIn,
					fx::Transaction& trOut); // return closed transaction

// removed from result the closed positions
void RemoveClosedPositions(	fx::Transaction& trResult,
							const fx::Transaction& trClosed);

void Log(const fxcm::IniParams& iniParams,
		 const misc::string& message);


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
	double renkoPL = 2; // renko size
	int lots = 1;
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
		bool canOpen = (tnow.hour_() >= hopen && tnow.hour_() < hclose);
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
				OpenPosition(*iniParams, session, offer, lots, buy, tr);
			}
			else if (pips < -renkoPL && canOpen)
			{
				buy = false;
				OpenPosition(*iniParams, session, offer, lots, buy, tr);
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
			fx::Transaction result;
			ClosePosition(*iniParams, session, offer, tr, result);
			RemoveClosedPositions(tr, result);
			
			closedPL += curPL;
			closedGPL += curGPL;

			misc::cout << "curPL=" << curPL << " closedGPL=" << closedGPL
				<< std::endl;


			if (!tr.IsEmpty())
				continue; // error during ClosePosition!

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
				OpenPosition(*iniParams, session, offer, lots, buy, tr);
				totalPL = 0;
			}
		}
	} // while

	session.Logout();
}


void OpenPosition(	const fxcm::IniParams& iniParams,
					fxcm::Session& session,
					const fxcm::Offer& offer,
					int lots,
					bool buy,
					fx::Transaction& result)
{
	misc::vector<fx::Position> openPositions;
	int ret = session.OpenPosition(offer, lots, buy, openPositions);
	if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
	{
		Log(iniParams, "session.OpenPosition(..) failed.\n");
		return;
	}
		
	misc::string message(offer.GetTime().tostring());
	message += " => Open Position: \n";
	result = fx::Transaction(); // clear the result

	for (size_t i = 0; i < openPositions.size(); ++i)
	{
		const fx::Position& pos = openPositions[i];
		result.Add(pos);
		message += pos.ToString();
		message += "\n";
	}

	Log(iniParams, message);
}

void ClosePosition(	const fxcm::IniParams& iniParams,
					fxcm::Session& session,
					const fxcm::Offer& offer,
					const fx::Transaction& trIn,
					fx::Transaction& trOut) // return closed transaction
{
	misc::vector<fx::Position> posOut;
	const fx::Transaction::Positions& posIn = trIn.GetPositions();
	trOut = fx::Transaction(); // clear result
	bool bFail = false;

	misc::string message(offer.GetTime().tostring());
	message += " => Close Position: \n";
	
	for (size_t i = 0; i < posIn.size(); ++i)
	{
		const fx::Position& pos = posIn[i];
		int ret = session.ClosePosition(offer, pos, posOut);

		if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
			bFail = true;

		for (size_t j = 0; j < posOut.size(); ++j)
		{
			const fx::Position& pos2 = posOut[j];
			trOut.Add(pos2);
			message += pos2.ToString();
			message += "\n";
		}		
	} // for

	fx::Price price(offer.GetAsk(), offer.GetBid());
	message += "PL=";
	message += misc::from_value(trOut.GetPL(offer.GetInstrument(), price), 2);
	message += " GPL=";
	message += misc::from_value(trOut.GetGPL(offer.GetInstrument(), price), 2);
	message += "\n";

	Log(iniParams, message);

	if (bFail)
		Log(iniParams, "session.ClosePosition(..) failed.\n");
}

void RemoveClosedPositions(	fx::Transaction& trResult,
							const fx::Transaction& trClosed)
{
	fx::Transaction::Positions& dest =
		const_cast<fx::Transaction::Positions&>(trResult.GetPositions());
	const fx::Transaction::Positions& closedVec = trClosed.GetPositions();
	for (size_t i = 0; i < closedVec.size(); ++i)
	{
		const fx::Position& pos2rem = closedVec[i];
		for (size_t j = 0; j < dest.size(); ++j)
		{
			if (pos2rem.GetTradeID() == dest[j].GetTradeID())
			{
				dest.erase(dest.begin() + j);
				break;
			}
		}
	}
}


void Log(const fxcm::IniParams& iniParams,
		 const misc::string& message)
{
	if (!iniParams.GetEnableLogging())
		return;

	FILE *pf = fopen(iniParams.GetLoggingFile().c_str(), "a+");
	if (pf == NULL)
		return;

	fwrite(message.c_str(), sizeof(char), message.size(), pf);
	fclose(pf);
}