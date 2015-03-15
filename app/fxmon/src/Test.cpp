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


#include "Test.hpp"
#include "MonitorIni.hpp"
#include "fxcmSession.hpp"
#include "stream.hpp"
#include <windows.h>

void test()
{
	MonitorIni monIniParams("monitor.ini");
	fxcm::IniParams sessionIni("monitor.ini");

	fxcm::Session session(sessionIni);
	session.Connect();

	session.SetAuditFile(monIniParams.GetAuditFile());
	misc::vector<fx::Currency> currencies;
	session.GetCurrencies(currencies);
	 			
	std::map<misc::string, fx::Price> quotes;	
	for(size_t i = 0, j = 0; i < 20; ++i, ++j)
	{
		if(j + 1 >  currencies.size())
			j = 0;

		fx::Currency curr(currencies[j]);
		
		
		double margin = curr.GetMargin();	margin;
		double pipcost= curr.GetPipCost();	pipcost;
		double rate2pip=curr.GetRate2Pip();	rate2pip;

		fx::Position pos("", "", curr, (i%2==0), 5, 0, 0);

		for(size_t j = 0; j < 3; ++j)
		{
			session.GetOffer(quotes);
			for(std::map<misc::string, fx::Price>::iterator it = quotes.begin();
				it != quotes.end(); ++it)
			{
				misc::cout << std::fixed << std::cout.precision(5) << "\n\t" <<
					it->first.c_str() << " B=" << it->second.GetBuy() <<
					" S: " << it->second.GetSell();
			}			
			
			//Sleep(1000);
		}


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
	}
	
	session.Disconnect();
	return;	
}