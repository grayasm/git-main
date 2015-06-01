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


#ifndef __fxcmMarketPlugin_hpp__
#define __fxcmMarketPlugin_hpp__

// c
// c++
// local
#include "string.hpp"
#include "MarketPlugin.hpp"
#include "Position.hpp"
#include "Transaction.hpp"
#include "fxcmSession.hpp"



namespace fxcm
{
	class MarketRealPlugin : public fx::MarketPlugin
	{
	public:
		MarketRealPlugin();
		MarketRealPlugin(Session* session);
		MarketRealPlugin(const MarketRealPlugin& tc);
		MarketRealPlugin& operator=(const MarketRealPlugin& tc);
		~MarketRealPlugin();

		//! virtual table
		virtual bool OpenMarketOrder(
			const fx::Position& request,
			misc::vector<fx::Position>& market,
			misc::string& error);

		virtual bool CloseMarketOrder(
			const fx::Position& request,
			misc::vector<fx::Position>& market,
			misc::string& error);

		virtual misc::string GetID() const;
		// --- end virtual table ---

		void SetSession(Session* session);
		
	private:
		Session* m_session;
	};
} // namespace


#endif // __fxcmMarketPlugin_hpp__
