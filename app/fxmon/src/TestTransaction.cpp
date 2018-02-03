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

#include "TestTransaction.hpp"
#include "GetOffersPrices.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "strconv.hpp"
#include "Offer.hpp"
#include "Position.hpp"


void OpenPosition(const fxcm::Offer& offer, int lots, bool buy, fx::Position& result);
void ClosePosition(const fxcm::Offer& offer, fx::Position& curpos);


void TestTransaction()
{
	bool isConnected = false;

	OffersReader oreader("EUR/USD");
	fxcm::Offer offer0, offer1;
	fx::Position curpos;
	double totalPL = 0;
	double incPL = 15;	// renko size
	int lots = 1;

	double closedPL = 0;
	double closedGPL = 0;

	while (true)
	{
		if (!oreader.GetOffer(offer1))
			break;

		// outside trading hours?
		misc::time tnow = offer1.GetTime();

		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			if (isConnected)
			{
				isConnected = false;
			}

			continue;
		}

		// trading is active
		if (!isConnected)
		{
			isConnected = true;
			offer0 = offer1;
			continue;
		}

		if (!isConnected)
		{
			// idle 1min
			msleep(1000ul * misc::time::minSEC);
			continue;
		}

		// connected and getting quotes

		// run trading with 1 position (renko:2)
		if (offer0.GetInstrument().empty())
		{
			offer0 = offer1;
			continue;
		}


		// trade daily between CET: 09:00 - 22:00
		// 9:00 Frankfurt open, 22:00 is 1h before NewYork close
		bool canOpen = (tnow.hour_() >= 8 && tnow.hour_() <= 21);
		bool noPosition = curpos.GetCurrency().GetSymbol().empty();

		if (!canOpen && noPosition)
			continue;

		if (noPosition)
		{
			double pips = (offer1.GetAsk() - offer0.GetAsk()) / 0.0001;

			if (pips > incPL && canOpen)
				OpenPosition(offer1, lots, true, curpos);
			else if (pips < -incPL && canOpen)
				OpenPosition(offer1, lots, false, curpos);
			else
				continue;

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

		if (diffPL < -2 * incPL)
		{
			// ClosePosition(offer1, curpos);
			closedPL += curPL;
			closedGPL += curGPL;

			misc::cout << "Closed: PL=" << closedPL
				<< " GPL=" << closedGPL << std::endl;
		
			// reset the trade
			curpos = fx::Position();
			totalPL = 0;
			offer0 = fxcm::Offer();

			// continue if allowed
			if (canOpen)
			{
				bool isBuy = curpos.IsBuy();
				OpenPosition(offer1, lots, !isBuy, curpos);
				totalPL = 0;
				offer0 = offer1;
			}
		}
	} // while

	// session.Logout();
}


void OpenPosition(const fxcm::Offer& offer, int lots, bool buy, fx::Position& result)
{
	static int orderID = 0;
	static int tradeID = 0;
	
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	fx::Currency currency(
		offer.GetInstrument(),
		price,
		2.5,		// margin= EUR/USD: 2.5 let's say
		0.08,		// pipCost,
		1/0.0001);	// rate2pip

	result = fx::Position(
		misc::from_value(orderID++),
		misc::from_value(tradeID++),
		currency,
		buy,
		lots,	// K lots
		0,		// commission
		0);		// interest		
}

void ClosePosition(const fxcm::Offer& offer, fx::Position& curpos)
{
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	curpos.Close(price);
}