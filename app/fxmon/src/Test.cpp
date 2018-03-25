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
#include "HistdatacomReader.hpp"
#include <list>
#include "Price.hpp"
#include "SMA.hpp"
#include "EMA.hpp"
#include "ATR.hpp"
#include "SAR.hpp"
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
	
	fx::SMA sma1("EUR/USD", 10, misc::time::hourSEC, fx::SMA::PRICE_CLOSE); // (F)ast
	fx::SMA sma2("EUR/USD", 70, misc::time::hourSEC, fx::SMA::PRICE_CLOSE);// (S)low

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
	// HistoryPricesReader oreader("EUR/USD");
	HistdatacomReader oreader("EUR/USD");

	fx::Offer offer, lastoffer;
	fx::EMA ema("EUR/USD", 14, misc::time::hourSEC, fx::SMA::PRICE_CLOSE);
	fx::SMA sma("EUR/USD", 14, misc::time::hourSEC, fx::SMA::PRICE_CLOSE);
	
	misc::time reftime;

	FILE* f1 = fopen("EMA_2017.txt", "w+");
	if (f1) fclose(f1);
	FILE* f2 = fopen("SMA_2017.txt", "w+");
	if (f2) fclose(f2);

	while (oreader.GetOffer(offer))
	{
		ema.Update(offer);
		sma.Update(offer);

		if (lastoffer.GetInstrument().empty())
			lastoffer = offer;

		if (!ema.IsValid() || !sma.IsValid())
			continue;

		if (reftime != sma.GetRefTime())
		{
			reftime = sma.GetRefTime(); // current candle

			// ---- EMA ----
			{
				FILE* pf = fopen("EMA_2017.txt", "a+");
				if (pf == NULL)
					continue;

				std::stringstream ss;
				ss << offer.GetTime().tostring() << " ";
				fx::Price pr;
				ema.GetValue(pr);
				ss << "Bid=" << pr.GetSell() << " Ask=" << pr.GetBuy() <<
					std::endl;

				std::string str = ss.str();
				fwrite(str.c_str(), sizeof(char), str.size(), pf);
				fclose(pf);
			}
			
			// ---- SMA ----
			{
				FILE* pf = fopen("SMA_2017.txt", "a+");
				if (pf == NULL)
					continue;

				std::stringstream ss;
				ss << offer.GetTime().tostring() << " ";
				fx::Price pr;
				sma.GetValue(pr);
				ss << "Bid=" << pr.GetSell() << " Ask=" << pr.GetBuy() <<
					std::endl;

				std::string str = ss.str();
				fwrite(str.c_str(), sizeof(char), str.size(), pf);
				fclose(pf);
			}
		}
	}

	return 0;
}


int test5()
{
	// OffersReader oreader("EUR/USD");
	// HistoryPricesReader oreader("EUR/USD");
	HistdatacomReader oreader("EUR/USD");

	fx::Offer offer;
	fx::ATR atr("EUR/USD", 14, misc::time::hourSEC);
	
	misc::time reftime;

	FILE* f1 = fopen("ATR_2017.txt", "w+");
	if (f1) fclose(f1);


	while (oreader.GetOffer(offer))
	{
		atr.Update(offer);

		if (reftime.totime_t() == 0)
			reftime = offer.GetTime();

		if (!atr.IsValid())
			continue;

		if (reftime.hour_() != offer.GetTime().hour_())
		{
			// reftime = sma.GetRefTime(); // current candle

			FILE* pf = fopen("ATR_2017.txt", "a+");
			if (pf == NULL)
				continue;

			std::stringstream ss;
			ss << offer.GetTime().tostring() << " ";
			double mid = 0;
			atr.GetValue(mid);
			mid *= 1 / (0.0001);

			ss << "ATR=" << mid << std::endl;

			std::string str = ss.str();
			fwrite(str.c_str(), sizeof(char), str.size(), pf);
			fclose(pf);

			reftime = atr.GetRefTime();
		}
	}

	return 0;
}


int test6()
{
	// OffersReader oreader("EUR/USD");
	// HistoryPricesReader oreader("EUR/USD");
	HistdatacomReader oreader("EUR/USD");

	fx::Offer offer;
	fx::SAR sar("EUR/USD", 14, misc::time::daySEC);
	time_t timeframe = misc::time::daySEC;
	fx::Price sarp(0, 0), epp(0, 0);
	fx::OHLCPrice ohlc;
	misc::time reftime, nextt;
	bool isBuy = true;
	double af = 0;

	FILE* f1 = fopen("PSAR_2017.txt", "w+");
	if (f1) fclose(f1);


	while (oreader.GetOffer(offer))
	{
		sar.Update(offer);

		if (reftime.totime_t() == 0)
		{
			reftime = offer.GetTime();
			nextt = reftime + timeframe;
		}			

		if (!sar.IsValid())
			continue;
		
		if (offer.GetTime() >= nextt || isBuy != sar.GetIsBuy())
		{
			FILE* pf = fopen("PSAR_2017.txt", "a+");
			if (pf == NULL)
				continue;

			std::stringstream ss;
			ss << offer.GetTime().tostring() << " ";
			ss << (sar.GetIsBuy() == true ? "L " : "S ");
			ss << " SAR=";
			sar.GetValue(sarp);
			ss << sarp.GetBuy() << "," << sarp.GetSell();
			sar.GetOHLC(ohlc);
			ss << " AO:" << ohlc.GetAskOpen();
			ss << " AH:" << ohlc.GetAskHigh();
			ss << " AL:" << ohlc.GetAskLow();
			ss << " AC:" << ohlc.GetAskClose();
			
			sar.GetEP(epp);
			ss << " EP=" << epp.GetBuy() << "," << epp.GetSell();

			sar.GetAF(af);
			ss << " AF:" << af;
			ss << std::endl;

			std::string str = ss.str();
			fwrite(str.c_str(), sizeof(char), str.size(), pf);
			fclose(pf);

			if (offer.GetTime() >= nextt)
			{
				reftime = sar.GetRefTime();
				nextt = reftime + timeframe;
			}
			
			isBuy = sar.GetIsBuy();
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
