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
	fxcm::Offer offer;
	fx::Price price;
	fx::Transaction tr;
	double closedPL = 0;
	double closedGPL = 0;

	fx::Price maxprice(0, 0);
	double PL2Enter = -50;		// price - maxprice = it's a retrace
	double trLimit = 50;		// profit on entire transaction
	double trStop = -300;		// loss on entire transaction
	int iAmount = 1;
	double price2pip = 1 / 0.0001;


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
		msleep(1000);


		// Run the transaction
		int error = session.GetLastOffer(offer, instr.c_str());
		if (error != fxcm::ErrorCodes::ERR_SUCCESS)
			continue;

		price = fx::Price(offer.GetAsk(), offer.GetBid());
		if (offer.GetAsk() == 0 || offer.GetBid() == 0)
			continue;

		if (price.GetBuy() > maxprice.GetBuy() &&
			price.GetSell() > maxprice.GetSell())
			maxprice = price;


		bool canOpen = (tnow.hour_() > 8 && tnow.hour_() < 22);

		if (!canOpen)
		{
			if (tr.Size() > 0 && tr.GetPL(instr, price) > 0) // still in profit
			{
				const fx::Transaction::Positions& posvec = tr.GetPositions();
				for (size_t i = 0; i < posvec.size(); ++i)
				{
					misc::vector<fx::Position> result;
					const fx::Position& pos = posvec[i];
					session.ClosePosition(offer, pos, result); // check result					
				}
								
				tr.Close(instr, price);
				closedPL += tr.GetPL(instr, price);
				closedGPL += tr.GetGPL(instr, price);

				misc::cout << "EndofDay: " <<
					"Pos=" << tr.Size() << " closedPL=" << closedPL <<
					" closedGPL=" << closedGPL << std::endl;

				tr = fx::Transaction();
				maxprice = price;
				
				continue;
			}

			if (tr.IsEmpty())
				continue;
		}



		// must calculate anything on tr?
		if (!tr.IsEmpty())
		{
			double curPL = tr.GetPL(instr, price);
			if (curPL > trLimit) // close in profit
			{
				const fx::Transaction::Positions& posvec = tr.GetPositions();
				for (size_t i = 0; i < posvec.size(); ++i)
				{
					misc::vector<fx::Position> result;
					const fx::Position& pos = posvec[i];
					session.ClosePosition(offer, pos, result); // check result					
				}

				tr.Close(instr, price);
				closedPL += curPL;
				closedGPL += tr.GetGPL(instr, price);

				misc::cout << "Prof: Pos=" << tr.Size()
					<< " trPL=" << curPL
					<< " closedPL=" << closedPL
					<< " closedGPL=" << closedGPL << std::endl;

				tr = fx::Transaction();
				maxprice = price;
				continue;
			}

			if (curPL < trStop) // close in loss
			{
				const fx::Transaction::Positions& posvec = tr.GetPositions();
				for (size_t i = 0; i < posvec.size(); ++i)
				{
					misc::vector<fx::Position> result;
					const fx::Position& pos = posvec[i];
					session.ClosePosition(offer, pos, result); // check result					
				}


				tr.Close(instr, price);
				closedPL += curPL;
				closedGPL += tr.GetGPL(instr, price);

				misc::cout << "Loss: Pos=" << tr.Size()
					<< " trPL=" << curPL
					<< " closedPL=" << closedPL
					<< " closedGPL=" << closedGPL << std::endl;

				tr = fx::Transaction();
				maxprice = price;
				continue;
			}

			if (tr.GetPositions().back().GetPL(price) < PL2Enter && canOpen)
			{
				misc::vector<fx::Position> result;
				session.OpenPosition(offer, iAmount, true, result);
				for (size_t i = 0; i < result.size(); ++i)
					tr.Add(result[i]);

				continue;
			}

			// anything else?
			continue;
		}

		if (tr.IsEmpty() && canOpen) // calculate first position
		{
			double diffPL = (price.GetBuy() - maxprice.GetBuy()) * price2pip;
			if (diffPL < PL2Enter)
			{
				misc::vector<fx::Position> result;
				session.OpenPosition(offer, iAmount, true, result);
				for (size_t i = 0; i < result.size(); ++i)
					tr.Add(result[i]);
			}

			continue;
		}
	} // while

	session.Logout();
}
