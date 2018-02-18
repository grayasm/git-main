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


#ifndef __PriceGenerator_hpp__
#define __PriceGenerator_hpp__



// C
// C++
// local
#include "autoptr.hpp"
#include "Price.hpp"

namespace fx
{
	/*	The internal random seed will be different from one instance to another,
		even if it was copied.
	*/
	class PriceGenerator
	{
		//--params
		double	m_buyInitial;				// initial buy price
		double	m_spread;					// initial spread
		double	m_rate2pip;	// pips = s * (currentRate - m_openRate) * m_rate2pip;
		int		m_trendChance;				// chance for trend to continue
		int		m_trendFragmentation;		// sidewalk to strong trending
		double	m_volatility;				// maxim volatility in pips
		//--internal
		bool	m_bullish;					// false for bearish
		int		m_trendCounter;				// countdown to new trend cycle
		double	m_buy;						// previous buy quote
		
		

		void Init();
		void Destroy();

	public:
		//types
		typedef misc::autoptr<PriceGenerator> Ptr;

		//methods
		PriceGenerator();
		PriceGenerator(
			double buyRate, 
			double spread, 
			double rate2pip, 
			int trendChance,			// 0 weak, 10 strong
			int trendFragmentation,		// 0 sidewalk, 10 strong trending
			double volatility);			// maxim volatility in pips (e.g 2.2)
		~PriceGenerator();		
		PriceGenerator(const PriceGenerator& tc);
		PriceGenerator& operator=(const PriceGenerator& tc);

		void SetBuyRate(double buyRate);
		double GetBuyRate() const;

		void SetSpread(double spread);
		double GetSpread() const;

		void SetRate2Pip(double rate2pip);
		double GetRate2Pip() const;

		void SetTrendChance(int trendChance);
		int GetTrendChance() const;

		void SetTrendFragmentation(int trendFragmentation);
		int GetTrendFragmentation() const;

		void SetVolatility(double volatility);
		double GetVolatility() const;

		void GetPrice(Price& quote);
	};
}

#endif // __PriceGenerator_hpp__

