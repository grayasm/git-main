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


#include "fxcmMarketPlugin.hpp"

namespace fxcm
{
	MarketRealPlugin::MarketRealPlugin()
	{
	}

	MarketRealPlugin::MarketRealPlugin(Session* session)
	{
		m_session = session;
	}

	MarketRealPlugin::MarketRealPlugin(const MarketRealPlugin& tc)
	{
		*this = tc;
	}

	MarketRealPlugin& MarketRealPlugin::operator=(const MarketRealPlugin& tc)
	{
		if(this != &tc)
		{
			m_session = tc.m_session;
		}
		return *this;
	}

	MarketRealPlugin::~MarketRealPlugin()
	{
	}

	bool MarketRealPlugin::OpenMarketOrder(
		const fx::Position& request,
		misc::vector<fx::Position>& market,
		misc::string& error)
	{
		bool ret = m_session->CreateMarketOrder(request, market);
		if(!ret)
			error = "MarketRealPlugin: cannot create market order.";
		return ret;
	}

	bool MarketRealPlugin::CloseMarketOrder(
		const fx::Position& request,
		misc::vector<fx::Position>& market,
		misc::string& error)
	{
		bool ret = m_session->CloseMarketOrder(request, market);
		if(!ret)
			error = "MarketRealPlugin: cannot close market order.";
		return ret;
	}

	misc::string MarketRealPlugin::GetID() const
	{
		return "fxcmreal";
	}

	void MarketRealPlugin::SetSession(Session* session)
	{
		m_session = session;
	}
}