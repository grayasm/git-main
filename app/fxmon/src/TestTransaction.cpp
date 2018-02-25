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
#include "Range.hpp"
#include "SMA.hpp"
#include "ATR.hpp"
#include "math.hpp"


static void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result, double renkoPL);
static void ClosePosition(const fx::Offer& offer, fx::Position& curpos, double renkoPL, double totalPL, double totalGPL);


void TestTransaction()
{
	unlink("TradeResult.txt");

	bool isConnected = false;

	// OffersReader oreader("EUR/USD");
	// HistoryPricesReader oreader("EUR/USD");
	HistdatacomReader oreader("EUR/USD");

	fx::ATR atr("EUR/USD", 14, misc::time::hourSEC);
	fx::SMA sma("EUR/USD", 7, fx::SMA::PRICE_CLOSE, misc::time::hourSEC);
	
	fx::Offer initialOffer, offer;
	fx::Position curpos;
	fx::Range range;
	double totalPL = 0;
	double renkoPL = 0;		// renko size ATR(14)
	double pointSize = 0.0001; // EUR/USD
	int lotsK = 1;

	// Frankfurt: open 8.00 UTC
	// London   : open 9.00 UTC
	// New York : open 14.00 UTC
	// Don't open new positions after 17.00 UTC = 12.00 EST (New York)

	int hopen = 8;
	int hstop = 17;

	double closedPL = 0;
	double closedGPL = 0;


	while (true)
	{
		if (!oreader.GetOffer(offer))
			break;

		// check for outside trading hours
		misc::time tnow = offer.GetTime();
		if ((tnow.wday() == misc::time::SAT) ||
			(tnow.wday() == misc::time::FRI && tnow.hour_() >= 22) ||
			(tnow.wday() == misc::time::SUN && tnow.hour_() < 22))
		{
			continue;
		}

		// update ATR, SMA
		atr.Update(offer);
		sma.Update(offer);

		if (!atr.IsValid())
			continue;

		if (!sma.IsValid())
			continue;

		atr.GetValue(renkoPL);
		renkoPL *= (1. / pointSize);
		if (renkoPL < 15.0)
			renkoPL = 15.0;


		// when can I open a position?
		bool canOpen = true;		
		if (canOpen)
			canOpen = (tnow.hour_() >= hopen && tnow.hour_() <= hstop);

		// reset protective range over the night
		if (!canOpen && (range.IsMinValid() || range.IsMaxValid()))
			range = fx::Range();


		bool noPosition = curpos.GetCurrency().GetSymbol().empty();
		
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
			{
				// check if range is in place
				canOpen = !range.IsMaxValid() ||
					(offer.GetAsk() > range.GetMax().GetBuy());

				// buy higher than sma value
				if (canOpen && range.IsMaxValid())
				{
					fx::Price smaval;
					sma.GetValue(smaval);
					canOpen = offer.GetAsk() > smaval.GetBuy();
				}

				if (canOpen)
					OpenPosition(offer, lotsK, true, curpos, renkoPL);
			}				
			else if (pips < -renkoPL && canOpen)
			{
				// check if range is in place
				canOpen = !range.IsMinValid() ||
					(offer.GetAsk() < range.GetMin().GetBuy());
				// sell lower than sma value
				if (canOpen && range.IsMinValid())
				{
					fx::Price smaval;
					sma.GetValue(smaval);
					canOpen = offer.GetAsk() < smaval.GetBuy();
				}

				if (canOpen)
					OpenPosition(offer, lotsK, false, curpos, renkoPL);
			}				
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
			closedPL += curPL;
			closedGPL += curGPL;

			ClosePosition(offer, curpos, renkoPL, closedPL, closedGPL);
			
			misc::cout << "curPL=" << curPL << " closedGPL=" << closedGPL
				<< std::endl;

			// if positive, reset previous range (if any)
			if (curPL > 0)
			{
				range = fx::Range();
			}
			else
			{
				if (curpos.IsBuy())
				{
					fx::Price limprice(
						offer.GetAsk() + 15.0 * pointSize,
						offer.GetBid() + 15.0 * pointSize);
					range.SetMax(limprice);
				}
				else
				{
					// renkoPL
					fx::Price limprice(
						offer.GetAsk() - 15.0 * pointSize,
						offer.GetBid() - 15.0 * pointSize);
					range.SetMin(limprice);
				}
			}

			
			// do not open in a range
			if (canOpen)
			{
				bool isBuy = !curpos.IsBuy(); // enter opposite direction
				if (isBuy && range.IsMaxValid())
				{
					canOpen = (offer.GetAsk() > range.GetMax().GetBuy());
					// buy higher than sma value
					fx::Price smaval;
					sma.GetValue(smaval);
					if (canOpen)
						canOpen = offer.GetAsk() > smaval.GetBuy();
				}					
				else if (!isBuy && range.IsMinValid())
				{
					canOpen = (offer.GetAsk() < range.GetMin().GetBuy());
					// sell lower than sma value
					fx::Price smaval;
					sma.GetValue(smaval);
					if (canOpen)
						canOpen = offer.GetAsk() < smaval.GetBuy();
				}
			}

			
			if (!canOpen)
			{
				// reset initialOffer at the end of the day
				initialOffer = fx::Offer();
				curpos = fx::Position();
				totalPL = 0;
			}
			else
			{
				bool isBuy = curpos.IsBuy(); // enter opposite direction
				OpenPosition(offer, lotsK, !isBuy, curpos, renkoPL);
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


void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result, double renkoPL)
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
	slog += (buy == true ? " B:" : " S:");
	slog += (buy == true ? misc::from_value(offer.GetAsk(), 5) :
						 misc::from_value(offer.GetBid(), 5));
	// slog += ", L(k)=";
	// slog += misc::from_value(lots);
	slog += "  RENKO=";
	slog += misc::from_value(renkoPL, 2);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}

void ClosePosition(const fx::Offer& offer, fx::Position& curpos, double renkoPL,
	double totalPL, double totalGPL)
{
	fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
	curpos.Close(price, offer.GetTime().totime_t());

	FILE *pf = fopen("TradeResult.txt", "a+");
	if (pf == NULL)
		return;


	bool buy = curpos.IsBuy();

	misc::string slog;
	if (curpos.GetPL() < 0)
		slog += "\t";
	slog += offer.GetTime().tostring();
	slog += (buy == true ? " S:" : " B:");
	slog += (buy == true ? misc::from_value(offer.GetBid(), 5) :
						misc::from_value(offer.GetAsk(), 5));
	//slog += ", L(k)=";
	//slog += misc::from_value(curpos.GetAmount(), 0);

	slog += "  currPL=";
	slog += misc::from_value(curpos.GetPL(), 2);
	//slog += "   totalPL=";
	//slog += misc::from_value(totalPL, 0);
	slog += "  totalGPL=";
	slog += misc::from_value(totalGPL, 0);
	slog += "  RENKO=";
	slog += misc::from_value(renkoPL, 2);
	slog += "\n";
	if (curpos.GetPL() < 0)
		slog += "\t---------------------------------------------------------\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}

