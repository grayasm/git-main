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


#ifndef __fxcmPipCost_hpp__
#define __fxcmPipCost_hpp__


#include <map>
#include "string.hpp"
#include "vector.hpp"
#include "fxcmIniParams.hpp"
#include "Currency.hpp"



class IO2GOfferRow;


namespace fxcm
{
	class TradingSettings;


	class PipCost
	{
	public:
		//! currencies must contain current bid/ask price
		PipCost(
			fxcm::IniParams& iniParams,
			TradingSettings* tradingSettings,
			const misc::vector<fx::Currency>& currencies);

		double CalcPipCost(IO2GOfferRow* offer) const;

	private:
		PipCost(const PipCost&);
		PipCost& operator=(const PipCost&);

		fxcm::IniParams&					m_iniParams;
		TradingSettings*				m_tradingSettings;
		misc::vector<fx::Currency>		m_currencies;

		std::map<misc::string, double>	m_nonCalculable;
	};
} // namespace

#endif // __fxcmPipCost_hpp__