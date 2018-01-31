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


#ifndef __PipCost_hpp__
#define __PipCost_hpp__


#include <stddef.h>
#include <ForexConnect.h>
#include <map>
#include "string.hpp"
#include "vector.hpp"
#include "IniParams.hpp"
#include "TradingSettings.hpp"
#include "Currency.hpp"



namespace fxcm
{
	class PipCost
	{
	public:
		//! currencies must contain current bid/ask price
		PipCost(const IniParams& iniParams,
				const TradingSettings& tradingSettings,
				const misc::vector<fx::Currency>& currencies);
		
		PipCost(const PipCost&) = delete;
		PipCost& operator=(const PipCost&) = delete;

		double CalcPipCost(IO2GOfferRow* offer) const;

	private:
		IniParams					m_iniParams;
		TradingSettings				m_tradingSettings;
		misc::vector<fx::Currency>	m_currencies;
		std::map<misc::string, double>	m_nonCalculable;
	};
} // namespace

#endif // __PipCost_hpp__