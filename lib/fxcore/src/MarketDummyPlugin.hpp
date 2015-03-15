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


#ifndef __MarketDummyPlugin_hpp__
#define __MarketDummyPlugin_hpp__



// c
// c++
#include <map>


// local
#include "autoptr.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "MarketPlugin.hpp"
#include "Position.hpp"
#include "Transaction.hpp"



namespace fx
{
	class MarketDummyPlugin : public MarketPlugin
	{
	public:
		typedef misc::autoptr<MarketDummyPlugin> Ptr;

		MarketDummyPlugin();
		virtual ~MarketDummyPlugin();
		MarketDummyPlugin(const MarketDummyPlugin&);
		MarketDummyPlugin& operator=(const MarketDummyPlugin&);

		// --- virtual table ---
		//! Returns true if market order is opened.
		virtual bool OpenMarketOrder(
			const fx::Position& request,
			misc::vector<fx::Position>& market,
			misc::string& error);

		//! Returns true if market order was closed.
		virtual bool CloseMarketOrder(
			const fx::Position& request,
			misc::vector<fx::Position>& market,
			misc::string& error);

		//! Returns a plugin identifier string.
		virtual misc::string GetID() const;
		// --- end virtual ---


		void SetPrice(const fx::Price& currp);
		const fx::Price& GetPrice() const;

	private:
		bool CreateTrade(size_t& orderId, size_t& tradeId);
		bool RemoveTrade(size_t orderId, size_t tradeId);

	
	
	private:
		fx::Price	m_price;
		
		typedef std::map<size_t, size_t>	Trades;
		Trades		m_trades;
	};

}; // namespace



#endif // __MarketDummyPlugin_hpp__
