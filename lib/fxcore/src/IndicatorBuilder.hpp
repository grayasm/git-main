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

#ifndef __IndicatorBuilder_hpp__
#define __IndicatorBuilder_hpp__

#include "MarketPlugin.hpp"
#include "vector.hpp"
#include "time.hpp"
#include "IND.hpp"
#include "Offer.hpp"



namespace fx
{
	class IndicatorBuilder
	{
	public:
		IndicatorBuilder() = delete;
		~IndicatorBuilder() = delete;

		static void Build(
			fx::MarketPlugin* plugin,
			const fx::Offer& offer,
			stl::vector<fx::IND*>& indicators);

	private:
		static void Update(
			const fx::Offer& offer,
			const fx::OHLCPrice& ohlc,
			stl::vector<fx::IND*>& indicators);

		static void Check(stl::vector<fx::IND*>& indicators);
	};
} // namespace

#endif // __IndicatorBuilder_hpp__
