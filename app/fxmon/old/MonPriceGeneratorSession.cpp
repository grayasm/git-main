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


#include "MonPriceGeneratorSession.hpp"


MonPriceGeneratorSession::MonPriceGeneratorSession()
{
	Reset();
}

MonPriceGeneratorSession::~MonPriceGeneratorSession()
{
}

bool MonPriceGeneratorSession::Create(
		const fx::Currency& currency,
		int trendChance,
		int trendFragmentation,
		double volatility,
		const fx::MarketDummyPlugin::Ptr& plugin)
{
	m_currency = currency;
	m_plugin = plugin;

	const fx::Price& price = m_currency.GetPrice();
	double buy = price.GetBuy();
	double rate2pip = m_currency.GetRate2Pip();
	double spread = (price.GetBuy() - price.GetSell()) * rate2pip;

	m_generator = new fx::PriceGenerator(
							buy,
							spread,
							rate2pip,
							trendChance,
							trendFragmentation,
							volatility);

	return true;
}

bool MonPriceGeneratorSession::GetInstruments(misc::vector<misc::string>& symbols)
{
	symbols.push_back(m_currency.GetSymbol());

	return true;
}

bool MonPriceGeneratorSession::GetCurrencies(misc::vector<fx::Currency>& currencies)
{
	currencies.push_back(m_currency);
	
	return true;
}

bool MonPriceGeneratorSession::GetOffer(std::map<misc::string, fx::Price>& quotes)
{
	fx::Price price;
	m_generator->GetPrice(price);
	quotes[m_currency.GetSymbol()] = price;
	m_plugin->SetPrice(price);

	return true;
}

void MonPriceGeneratorSession::Reset()
{
	m_currency = fx::Currency();
	m_generator = 0;
}