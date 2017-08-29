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

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "Offer.hpp"
#include "ErrorCodes.hpp"


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

	int i = 0;
	do
	{
		sleep(1);
		++i;
		misc::cout << "sleep(1)" << std::endl;
	} while (i < 4);

	misc::vector<fxcm::TradingSettings> tsvec;
	session.GetTradingSettings(tsvec, true);

	fxcm::TradingPermissions tradingPermission;
	session.GetTradingPermissions("EUR/USD", tradingPermission);

	session.GetOrders();

	i = 0;
	do
	{
		sleep(1);
		++i;
		misc::cout << "sleep(1)" << std::endl;
		fxcm::Offer offer("0", "EUR/USD", 0, 0, 0, 0, 0);
		
		if (session.GetLastOffer(offer, "EUR/USD") == fxcm::ErrorCodes::ERR_SUCCESS)
		{
			misc::cout	<< offer.GetId() << ", "
						<< offer.GetInstrument()
						<< ", Bid=" << std::fixed << offer.GetBid()
						<< ", Ask=" << std::fixed << offer.GetAsk()
						<< std::endl;
		}
	} while (i < 4);

	session.Logout();
	
	return 0;
}



#if 0
#include "Test.hpp"
#include "MonitorIni.hpp"
#include "fxcmSession.hpp"
#include "stream.hpp"


int test()
{
	MonitorIni monIniParams("monitor.ini");
	fxcm::IniParams sessionIni("monitor.ini");

	fxcm::Session session(sessionIni);
	if (!session.Connect())
		return -1;

	session.SetAuditFile(monIniParams.GetAuditFile());
	misc::vector<fx::Currency> currencies;
	session.GetCurrencies(currencies);
	 			
	if (currencies.size() != 1)
		return -1;

	if (currencies[0].GetSymbol() != "EUR/USD")
		return -1;

	fx::Currency euro(currencies[0]);
	fxcm::HistPriceData priceData;

	if (!session.GetHistPrices(euro.GetSymbol(),
		"m1",
		monIniParams.GetDateFrom(),
		monIniParams.GetDateTo(),
		priceData))
		return -1;
	
	for (fxcm::HistPriceData::iterator beg = priceData.begin();
		beg != priceData.end(); ++beg)
	{
		const fxcm::HistoryPrice& hprice = *beg;
		bool		isBar = hprice.IsBar();
		misc::DATE	date = hprice.GetDate();
		fx::Price	currPrice = hprice.GetCurrPrice();
		fx::Price	openPrice = hprice.GetOpenPrice();
		fx::Price	closePrice = hprice.GetClosePrice();
		fx::Price	highPrice = hprice.GetHighPrice();
		fx::Price	lowPrice = hprice.GetLowPrice();
		int			volume = hprice.GetVolume();

		volume += 0;
	}

	//std::map<misc::string, fx::Price> quotes;	
	//for(size_t i = 0, j = 0; i < 2; ++i, ++j)
	//{
	//	if(j + 1 >  currencies.size())
	//		j = 0;

	//	fx::Currency curr(currencies[j]);
	//	
	//	
//		double margin = curr.GetMargin();
//		double pipcost= curr.GetPipCost();
//		double rate2pip=curr.GetRate2Pip();

		//fx::Position pos("", "", curr, (i%2==0), 5, 0, 0);

		//for(size_t j = 0; j < 3; ++j)
		//{
		//	session.GetOffer(quotes);
		//	for(std::map<misc::string, fx::Price>::iterator it = quotes.begin();
		//		it != quotes.end(); ++it)
		//	{
		//		misc::cout << std::fixed << std::cout.precision(5) << "\n\t" <<
		//			it->first.c_str() << " B=" << it->second.GetBuy() <<
		//			" S: " << it->second.GetSell();
		//	}			
		//	
		//	//Sleep(1000);
		//}

		/*
		misc::vector<fx::Position> otrades, ctrades;
		for(size_t i = 0; i < 3; ++i)
			session.CreateMarketOrder(pos, otrades);			

		for(size_t i = 0; i < otrades.size(); ++i)
		{
			const fx::Position& trade = otrades[i];
			if(!trade.IsOpen())
			{
				ctrades.push_back(trade);
				continue;
			}

			session.CloseMarketOrder(trade, ctrades);
		}		
		*/
		
	//}
	
	session.Disconnect();
	return -1;	
}


#endif // 0