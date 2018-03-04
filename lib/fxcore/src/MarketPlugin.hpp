/*
	Copyright (C) 2018 Mihai Vasilian

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/


#ifndef __MarketPlugin_hpp__
#define __MarketPlugin_hpp__


#include "vector.hpp"
#include "Offer.hpp"
#include "OHLCPrice.hpp"
#include "Position.hpp"



namespace fx
{
	/*	The core does not need to know login details, if or when to logout,
		or any other particular details about a broker. It is enough for now
		to provide few simple methods to open and close one or more positions.
		On SUCCESS return value is zero.
	*/
	class MarketPlugin
	{
	public:
		virtual ~MarketPlugin();

		virtual int OpenPosition(	const fx::Offer& offer,
									int lots,
									bool buy,
									misc::vector<fx::Position>& result) = 0;

		virtual int ClosePosition(	const fx::Offer& offer,
									const fx::Position& pos,
									misc::vector<fx::Position>& result) = 0;

		virtual int GetOHLCPrices(	const misc::string& instrument,
									const misc::string& timeframe,
									const misc::time& from,
									const misc::time& to,
									misc::vector<fx::OHLCPrice>& result) = 0;
	};
} // namespace

#endif // __MarketPlugin_hpp__
