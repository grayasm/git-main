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


#ifndef __MonPriceGeneratorSession_hpp__
#define __MonPriceGeneratorSession_hpp__


#include <map>

#include "autoptr.hpp"
#include "vector.hpp"
#include "string.hpp"
#include "Transaction.hpp"
#include "PriceGenerator.hpp"
#include "MarketDummyPlugin.hpp"


class MonPriceGeneratorSession
{
public:
	typedef misc::autoptr<MonPriceGeneratorSession> Ptr;
	MonPriceGeneratorSession();
	~MonPriceGeneratorSession();

	bool Create(
		const fx::Currency& currency,				// for which currency
		int trendChance,							// trend: 0 weak, 10 strong
		int trendFragmentation,						// 0 sidewalk, 10 strong trending
		double volatility,							// maxim volatility in pips
		const fx::MarketDummyPlugin::Ptr& plugin);	// plugin to be updated with the price

	bool GetInstruments(misc::vector<misc::string>& symbols);
	bool GetCurrencies(misc::vector<fx::Currency>& currencies);
	bool GetOffer(std::map<misc::string, fx::Price>& quotes);

private:
	//! non copyable
	MonPriceGeneratorSession(const MonPriceGeneratorSession&);
	MonPriceGeneratorSession& operator=(const MonPriceGeneratorSession&);

	//! Clears all data
	void Reset();

private:
	fx::Currency				m_currency;
	fx::PriceGenerator::Ptr		m_generator;
	fx::MarketDummyPlugin::Ptr	m_plugin;
};

#endif // __MonPriceGeneratorSession_hpp__