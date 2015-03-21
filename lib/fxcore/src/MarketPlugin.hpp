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

#ifndef __MarketPlugin_hpp__
#define __MarketPlugin_hpp__

// c
// c++
// local
#include "autoptr.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "Position.hpp"
#include "Transaction.hpp"


namespace fx
{
	class MarketPlugin
	{
	public:
		typedef misc::autoptr<MarketPlugin> Ptr;

		MarketPlugin();
		virtual ~MarketPlugin();
		MarketPlugin(const MarketPlugin&);
		MarketPlugin& operator=(const MarketPlugin&);

		//! Returns true if market order is opened.
		virtual bool OpenMarketOrder(
			const fx::Position& request,			// requested position to be opened
			misc::vector<fx::Position>& market,		// opened with 1 ore more trades (liquidity)
			misc::string& error						// error message if failed
			) = 0;

		//! Returns true if market order was closed.
		virtual bool CloseMarketOrder(
			const fx::Position& request,			// requested position to be closed
			misc::vector<fx::Position>& market,		// closed with 1 or more trades (liquidity)
			misc::string& error						// error message if failed
			) = 0;

		//! Returns a plugin identifier string.
		virtual misc::string GetID() const = 0;
	};
}; // namespace


#endif // __MarketPlugin_hpp__

