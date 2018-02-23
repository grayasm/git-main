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
#include "math.hpp"

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "Offer.hpp"
#include "ErrorCodes.hpp"
#include "time.hpp"
#include "HistoryPricesReader.hpp"
#include <list>
#include "Price.hpp"
#include "SMA.hpp"
#include "ATR.hpp"
#include "Position.hpp"
#include "Transaction.hpp"


static void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result);
static void ClosePosition(const fx::Offer& offer, fx::Position& curpos);


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
	
	// session.GetOrders();
	
	msleep(2000);
	
	int ret = 0;

	fx::Offer offer;
	ret = session.GetLastOffer(offer, "EUR/USD");
	if (ret == fxcm::ErrorCodes::ERR_SUCCESS)
	{
		misc::vector<fx::Position> result;
		session.GetOpenPositions(offer, result);
		
		misc::cout << "\n";
		for (int i = 0; i < result.size(); ++i)
			misc::cout << result[i].ToString() << std::endl;
	}	

	session.Logout();	
	return 0;
}


int test3()
{
	// OffersReader oreader("EUR/USD");
	HistoryPricesReader oreader("EUR/USD");
	// HistdatacomReader oreader("EUR/USD");

	fx::Offer prev_offer, curr_offer;
	
	fx::SMA sma1("EUR/USD", 10, fx::SMA::PRICE_CLOSE, misc::time::hourSEC); // (F)ast
	fx::SMA sma2("EUR/USD", 70, fx::SMA::PRICE_CLOSE, misc::time::hourSEC);// (S)low

	double prevBuy1 = 0, currBuy1 = 0;
	double prevBuy2 = 0, currBuy2 = 0;
	
	fx::Price av1, av2;
	fx::Position pos;
	int lots = 1;

	double totalPL = 0;
	double totalGPL = 0;


	while (true)
	{
		if (!oreader.GetOffer(curr_offer))
			break;
		
		sma1.Update(curr_offer);
		sma2.Update(curr_offer);

		if (!sma1.IsValid() || !sma2.IsValid())
			continue;
		
		if (prev_offer.GetInstrument().empty())
		{
			prev_offer = curr_offer;
			continue;
		}
		
		sma1.GetValue(av1);
		sma2.GetValue(av2);

		currBuy1 = av1.GetBuy();
		currBuy2 = av2.GetBuy();

		if (prevBuy1 == 0)
		{
			prevBuy1 = currBuy1;
			prevBuy2 = currBuy2;
			continue;
		}

		bool noPos = pos.GetCurrency().GetSymbol().empty();
		
		bool bSell = (prevBuy1 > prevBuy2 && currBuy1 <= currBuy2);
		bool bBuy = (prevBuy1 < prevBuy2 && currBuy1 >= currBuy2);
		
		if (bBuy || bSell)
		{
			// must close existing position?
			if (!noPos)
			{
				ClosePosition(curr_offer, pos);
				double currPL = pos.GetPL();
				double currGPL = pos.GetGPL();

				totalPL += currPL;
				totalGPL += currGPL;

				misc::cout << "currPL=" << currPL
					<< " totalPL=" << totalPL << " totalGPL=" << totalGPL
					<< std::endl;
			}

			bool b_buy = (bSell == true ? false : (bBuy == true ? true : false));
			OpenPosition(curr_offer, lots, b_buy, pos);
		}
		
		// update offer
		prev_offer = curr_offer;
		prevBuy1 = currBuy1;
		prevBuy2 = currBuy2;
	}


	FILE *pf = fopen("TradeResult.txt", "a+");
	if (pf == NULL)
		return 0;

	misc::string slog;
	slog += "totalPL=";
	slog += misc::from_value(totalPL, 2);
	slog += " totalGPL=";
	slog += misc::from_value(totalGPL, 2);
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
	return 0;
}

int test4()
{
	// OffersReader oreader("EUR/USD");
	HistoryPricesReader oreader("EUR/USD");
	// HistdatacomReader oreader("EUR/USD");

	fx::Offer offer;
	fx::ATR atr("EUR/USD", 14, misc::time::hourSEC);
	double prevATR = 0;

	while (oreader.GetOffer(offer))
	{
		atr.Update(offer);

		if (atr.IsValid())
		{
			double currATR = 0;
			atr.GetValue(currATR);

			if (math::is_neq(prevATR, currATR))
			{
				misc::cout << "ATR=" << currATR << " RENKO=" <<
					currATR * 1 / offer.GetPointSize() <<
					std::endl;
				prevATR = currATR;
			}
		}
	}

	return 0;
}


static void Time2DATE(time_t tt, DATE& dt)
{
	struct tm *tmNow = gmtime(&tt);
	CO2GDateUtils::CTimeToOleTime(tmNow, &dt);
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
		1 / 0.0001);	// rate2pip

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

void ClosePosition(const fx::Offer& offer, fx::Position& curpos)
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
	slog += "\n";

	fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
	fclose(pf);
}
