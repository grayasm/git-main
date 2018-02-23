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
#include "OffersReader.hpp"
#include "HistoryPricesReader.hpp"
#include "HistdatacomReader.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "strconv.hpp"
#include "Offer.hpp"
#include "Position.hpp"
#include "Transaction.hpp"
#include "ATR.hpp"
#include "math.hpp"


static void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result);
static void ClosePosition(const fx::Offer& offer, fx::Position& curpos, double renkoPL);


void TestTransaction()
{
	bool isConnected = false;

	// OffersReader oreader("EUR/USD");
	HistoryPricesReader oreader("EUR/USD");
	// HistdatacomReader oreader("EUR/USD");

	fx::ATR atr("EUR/USD", 14, misc::time::hourSEC);
	fx::Offer initialOffer, offer;
	fx::Position curpos;
	double totalPL = 0;
	double renkoPL = 0;	// renko size ATR(14)
	double pointSize = 0.0001; // EUR/USD
	int lotsK = 1;

	//  Frankfurt: Xetra trading takes place from 9.00a.m. until 5.30 p.m. CET. (UTC+100)
	//  New York:  Core Trading Session: 9:30 AM TO 4:00 PM ET (UTC-500)
	int hopen = 8;		// CET 9:00 is Frankfurt open
	int hclose = 17;	// CET 23:00 is New York close

	double closedPL = 0;
	double closedGPL = 0;
	


	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;

		atr.Update(offer);

		bool canOpen = true;		
		misc::time tnow = offer.GetTime();

		// outside trading hours?
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			canOpen = false;
		}

		// when can I open a position?
		if (canOpen)
			canOpen = (tnow.hour_() >= hopen && tnow.hour_() <= hclose);
		bool noPosition = curpos.GetCurrency().GetSymbol().empty();
		
		if (!atr.IsValid())
			continue;

		atr.GetValue(renkoPL);
		renkoPL *= (1. / pointSize);
		if (renkoPL < 15.0)
			renkoPL = 15.0;


		// no trade is open ? -> do nothing;
		if (!canOpen && noPosition)
			continue;

		if (noPosition)
		{
			// start a new trading day?
			if (initialOffer.GetInstrument().empty())
			{
				initialOffer = offer;
				continue;
			}

			double pips = (offer.GetAsk() - initialOffer.GetAsk()) / pointSize;

			if (pips > renkoPL && canOpen)
				OpenPosition(offer, lotsK, true, curpos);
			else if (pips < -renkoPL && canOpen)
				OpenPosition(offer, lotsK, false, curpos);
			else
				continue;

			totalPL = 0;

			continue;
		}

		// Manage the position
		fx::Price curprice(offer.GetAsk(), offer.GetBid());
		double curPL = curpos.GetPL(curprice); // PL for 1k
		double curGPL = curpos.GetGPL(curprice);
		double diffPL = curPL - totalPL;


		if (diffPL > renkoPL)
		{
			totalPL += renkoPL;
			continue;
		}

		if (diffPL < -2 * renkoPL)
		{
			ClosePosition(offer, curpos, renkoPL);

			closedPL += curPL;
			closedGPL += curGPL;
			
			misc::cout << "curPL=" << curPL << " closedGPL=" << closedGPL
				<< std::endl;


			// reset initialOffer at the end of the day
			if (!canOpen)
			{
				initialOffer = fx::Offer();
				curpos = fx::Position();
				totalPL = 0;
			}
			else
			{
				bool isBuy = curpos.IsBuy(); // trend reversed
				OpenPosition(offer, lotsK, !isBuy, curpos);
				totalPL = 0;
			}
		}
	} // while


	FILE *pf = fopen("TradeResult.txt", "a+");
	if (pf == NULL)
		return;

	misc::string slog;
	slog += "closedPL=";
	slog += misc::from_value(closedPL, 2);
	slog += " closedGPL=";
	slog += misc::from_value(closedGPL, 2);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);

}


void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result)
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
		0,		// interest
		offer.GetTime().totime_t());

	FILE *pf = fopen("TradeResult.txt", "a+");
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

void ClosePosition(const fx::Offer& offer, fx::Position& curpos, double renkoPL)
{
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	curpos.Close(price, offer.GetTime().totime_t());

	FILE *pf = fopen("TradeResult.txt", "a+");
	if (pf == NULL)
		return;


	bool buy = curpos.IsBuy();

	misc::string slog;
	slog += offer.GetTime().tostring();
	slog += (buy == true ? ", S:" : ", B:");
	slog += (buy == true ? misc::from_value(offer.GetBid(), 5) :
						misc::from_value(offer.GetAsk(), 5));
	slog += ", L(k)=";
	slog += misc::from_value(curpos.GetAmount(), 0);

	slog += ", PL(1k)=";
	slog += misc::from_value(curpos.GetPL(), 2);
	slog += ", GPL=";
	slog += misc::from_value(curpos.GetGPL(), 0);
	slog += ", RENKO=";
	slog += misc::from_value(renkoPL, 2);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}
