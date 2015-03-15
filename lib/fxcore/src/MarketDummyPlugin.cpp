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

#include <time.h>
#include "MarketDummyPlugin.hpp"
#include "strconv.hpp"


namespace fx
{

	MarketDummyPlugin::MarketDummyPlugin()
	{
		// m_price;		
		srand((unsigned int)time(NULL));
	}

	MarketDummyPlugin::~MarketDummyPlugin()
	{
	}

	MarketDummyPlugin::MarketDummyPlugin(const MarketDummyPlugin& tc)
	{
		*this = tc;
	}

	MarketDummyPlugin& MarketDummyPlugin::operator=(const MarketDummyPlugin& tc)
	{
		if(this != &tc)
		{
			m_price = tc.m_price;
			m_trades = tc.m_trades;
		}
		return *this;
	}
	
	bool MarketDummyPlugin::OpenMarketOrder(
		const fx::Position& request,
		misc::vector<fx::Position>& market,
		misc::string& /*error*/)
	{
		size_t orderId = 0;
		size_t tradeId = 0;

		CreateTrade(orderId, tradeId);

		const fx::Currency& reqcurr = request.GetCurrency();
		fx::Currency currency(
				reqcurr.GetSymbol(),
				m_price,
				reqcurr.GetMargin(),
				reqcurr.GetPipCost(),
				reqcurr.GetRate2Pip());

		//TODO: remove hardcoded commission and interest value
		double commission = request.GetAmount() * 0.029;
		double interest = 0;
		fx::Position trade(
			misc::from_value(orderId),
			misc::from_value(tradeId),
			currency,
			request.IsBuy(),
			request.GetAmount(),
			commission,
			interest);
		
		market.push_back(trade);

		return true;
	}

	bool MarketDummyPlugin::CloseMarketOrder(
		const fx::Position& request,
		misc::vector<fx::Position>& market,
		misc::string& /*error*/)
	{
		fx::Position pos = request;

		size_t orderId = 0;
		size_t tradeId = 0;
		misc::to_value(pos.GetOrderID(), orderId);
		misc::to_value(pos.GetTradeID(), tradeId);
		RemoveTrade(orderId, tradeId);

		pos.Close(m_price);
		pos.SetCommission(pos.GetCommission() * 2);
		market.push_back(pos);
		return true;		
	}

	misc::string MarketDummyPlugin::GetID() const
	{
		return "dummy";
	}

	void MarketDummyPlugin::SetPrice(const fx::Price& currp)
	{
		m_price = currp;
	}

	const fx::Price& MarketDummyPlugin::GetPrice() const
	{
		return m_price;
	}

	bool MarketDummyPlugin::CreateTrade(size_t& orderId, size_t& tradeId)
	{
		size_t roId = rand();
		while(m_trades.find(roId) != m_trades.end())
			roId = rand();

		size_t rtId = rand();
		for(Trades::iterator it = m_trades.begin(); it != m_trades.end(); /*...*/)
		{
			if(it->second == rtId)
			{
				rtId = rand();
				it = m_trades.begin(); // rewind				
			}
			else
			{
				it++;
			}
		}
		
		m_trades.insert(Trades::value_type(roId, rtId));
		orderId = roId;
		tradeId = rtId;
		return true;
	}

	bool MarketDummyPlugin::RemoveTrade(size_t orderId, size_t tradeId)
	{
		Trades::iterator it = m_trades.find(orderId);
		if(it == m_trades.end())
			throw misc::exception("Order does not exist.");
		if(it->second != tradeId)
			throw misc::exception("Trade does not exist.");

		m_trades.erase(it);
		return true;
	}

} // namespace

