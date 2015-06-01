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

  resources:
  www.forexnewbies.com/pip-value-formula
  www.fxtrade.oanda.com/analysis/profit-calculator
  www.dailyfx.com/forex_forum/forexconnect/634955-implementation-pipcost-tablemanager-2.html
*/



#include "fxcmPipCost.hpp"

// c
#include <float.h>
// c++


// fxcm
#include "ForexConnect.h"
// #include "sample_tools.h"

// local
#include "strtok.hpp"
#include "fxcmTradingSettings.hpp"


namespace fxcm
{	
	PipCost::PipCost(
		fxcm::IniParams& iniParams,
		TradingSettings* tradingSettings,
		const misc::vector<fx::Currency>& currencies)
		: m_iniParams(iniParams)
	{		
		m_tradingSettings = tradingSettings;
		m_currencies = currencies;

		// update known non-calculable list at the moment
		m_nonCalculable["USD/MXN"] = 0.01;
		m_nonCalculable["USD/ZAR"] = 0.01;
		m_nonCalculable["USD/SGD"] = 0.06;
		m_nonCalculable["USD/HKD"] = 0.01;
		m_nonCalculable["USD/RUB"] = 0.20;
		m_nonCalculable["USD/CNH"] = 0.01;
		m_nonCalculable["USD/ILS"] = 0.02;
		m_nonCalculable["UK100"] = 0.13;
		m_nonCalculable["USDOLLAR"] = 0.79;
		m_nonCalculable["GER30"] = 0.1;
		m_nonCalculable["FRA40"] = 0.1;
		m_nonCalculable["EUSTX50"] = 0.1;
		m_nonCalculable["US30"] = 0.08;
		m_nonCalculable["NGAS"] = 0.08;
		m_nonCalculable["AUS200"] = 0.07;
		m_nonCalculable["ESP35"] = 0.10;
		m_nonCalculable["HKG33"] = 0.10;
		m_nonCalculable["ITA40"] = 0.10;
		m_nonCalculable["JPN225"] = 0.07;
		m_nonCalculable["NAS100"] = 0.08;
		m_nonCalculable["SPX500"] = 0.08;
		m_nonCalculable["SUI30"] = 0.08;
		m_nonCalculable["Copper"] = 0.08;
		m_nonCalculable["USOil"] = 0.08;
		m_nonCalculable["UKOil"] = 0.;
		m_nonCalculable["Bund"] = 0.;
	}

	double PipCost::CalcPipCost(IO2GOfferRow* offer) const
	{
		const misc::string& acc_symbol = m_iniParams.GetAccountSymbol();
		const misc::string& symbol = offer->getInstrument();

		// TODO: get formula for these instruments.
		std::map<misc::string, double>::const_iterator it = m_nonCalculable.find(symbol);
		if(it != m_nonCalculable.end())
		{
			double pipCost = (*it).second;
			misc::cout << "\npipCost[ " << symbol.c_str() << " ]= " << pipCost;
			return pipCost;
		}


		const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
		int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
		double pointSize = offer->getPointSize();

		misc::strtok tokenizer(symbol, "/");
		if(tokenizer.count() != 2)
			throw misc::exception("Cannot calculate pipCost.");

		// SITUATION 1
		//bool acccur_sameas_quote = false;		// acc USD, EUR/USD
		//{
		//	double lots = 1000; // 1k
		//	double pointsize = 0.0001; //non-JPY
		//	double pipCost = (lots * pointsize);
		//}
		
		if(acc_symbol == tokenizer.tokens().back())
		{
			double pipCost = (double)iBaseUnitSize * pointSize;
			misc::cout << "\npipCost[ " << symbol.c_str() << " ]= " << pipCost;
			return pipCost;
		}


		// SITUATION 2
		//bool acccur_sameas_base = false;		// acc EUR, EUR/USD
		//{
		//	double eur_usd_ask = 1.26762;
		//	double lots = 1000; // 1k
		//	double pointsize = 0.0001; // non-JPY
		//	double pipCost = (lots * pointsize) / eur_usd_ask;
		//}
		
		if(acc_symbol == tokenizer.tokens().front())
		{
			double ask = offer->getAsk();			
			double pipCost = iBaseUnitSize * pointSize / ask;
			misc::cout << "\npipCost[ " << symbol.c_str() << " ]= " << pipCost;
			return pipCost;
		}


		// SITUATION 3
		//bool acccur_sameas_comb_quote = false;	// acc CHF, EUR/USD
		//{
		//	double usd_chf_bid /*sell,lt*/ = 0.95312;
		//	double lots = 1000; // 1k
		//	double pointsize = 0.0001; // non-JPY
		//	double pipCost = (lots * pointsize) * usd_chf_bid;
		//}


		// SITUATION 4
		//bool acccur_sameas_comb_base = false;	// acc EUR, USD/CHF
		//{
		//	double eur_chf_ask = 1.20848;  // 1.20842 / 1.20848
		//	double lots = 1000;
		//	double pointsize = 0.0001; //non-JPY
		//	double pipCost = (lots * pointsize) / eur_chf_ask;
		//}

		
		misc::string acc_quote= tokenizer.tokens().back(); acc_quote += "/"; acc_quote += acc_symbol;
		misc::string acc_base = acc_symbol; acc_base += "/"; acc_base += tokenizer.tokens().back();
		
		for(misc::vector<fx::Currency>::const_iterator it = m_currencies.begin();
			it != m_currencies.end(); ++it)
		{
			const fx::Currency& curr = *it;
			if(acc_quote == curr.GetSymbol())
			{
				double bid = curr.GetPrice().GetSell(); // bid
				double pipCost = (double)iBaseUnitSize * pointSize * bid;
				misc::cout << "\npipCost[ " << symbol.c_str() << " ]= " << pipCost;
				return pipCost;
			}

			if(acc_base == curr.GetSymbol())
			{
				double ask = curr.GetPrice().GetBuy(); // ask
				double pipCost = (double)iBaseUnitSize * pointSize / ask;
				misc::cout << "\npipCost[ " << symbol.c_str() << " ]= " << pipCost;
				return pipCost;
			}
		}		

		throw misc::exception("Cannot calculate PipCost.");
	}

} // namespace