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



#include "PriceGenerator.hpp"
#include <time.h>

namespace fx
{
	void PriceGenerator::Init()
	{
		m_buyInitial = 1.36500;		// default buy rate 1.36500 EUR/USD
		m_spread = 2.5;
		m_rate2pip = 10000;			// 100 for JPY pairs
		m_trendChance = 0;			// buy/sell chance
		m_trendFragmentation = 2;	// sidewalk, 2 positions per trend
		m_volatility = 1.1;			// maxim volatility in pips
		m_bullish = false;			// bears
		m_trendCounter = 0;			// 0-force new trend
		m_buy = m_buyInitial;		// last buy quote 
		
		::srand((unsigned int) ::time(0));		
	}

	void PriceGenerator::Destroy()
	{

	}

	PriceGenerator::PriceGenerator()
	{
		Init();
	}

	PriceGenerator::PriceGenerator(
		double buyRate,
		double spread,
		double rate2pip,
		int trendChance, 
		int trendFragmentation,
		double volatility)
	{
		Init();

		m_buyInitial = buyRate;
		m_spread = spread;
		m_rate2pip = rate2pip;
		m_trendChance = trendChance;
		m_trendFragmentation = trendFragmentation;
		m_volatility = volatility;
		m_buy = m_buyInitial;
	}

	PriceGenerator::~PriceGenerator()
	{
		Destroy();
	}

	PriceGenerator::PriceGenerator(const PriceGenerator& tc)
	{
		Init();
		*this = tc;
	}

	PriceGenerator& PriceGenerator::operator=(const PriceGenerator& tc)
	{
		if(this != &tc)
		{
			m_buyInitial = tc.m_buyInitial;
			m_spread = tc.m_spread;
			m_rate2pip = tc.m_rate2pip;
			m_trendChance = tc.m_trendChance;
			m_trendFragmentation = tc.m_trendFragmentation;
			m_volatility = tc.m_volatility;
			m_bullish = tc.m_bullish;
			m_trendCounter = tc.m_trendCounter;
			m_buy = tc.m_buy;
		}
		return *this;
	}

	void PriceGenerator::SetBuyRate(double buyRate)
	{
		m_buyInitial = buyRate;
	}

	double PriceGenerator::GetBuyRate() const
	{
		return m_buyInitial;
	}

	void PriceGenerator::SetSpread(double spread)
	{
		m_spread = spread;
	}

	double PriceGenerator::GetSpread() const
	{
		return m_spread;
	}

	void PriceGenerator::SetRate2Pip(double rate2pip)
	{
		m_rate2pip = rate2pip;
	}

	double PriceGenerator::GetRate2Pip() const
	{
		return m_rate2pip;
	}

	void PriceGenerator::SetTrendChance(int trendChance)
	{
		m_trendChance = trendChance;
	}

	int PriceGenerator::GetTrendChance() const
	{
		return m_trendChance;
	}

	void PriceGenerator::SetTrendFragmentation(int trendFragmentation)
	{
		m_trendFragmentation = trendFragmentation;
	}

	int PriceGenerator::GetTrendFragmentation() const
	{
		return m_trendFragmentation;
	}

	void PriceGenerator::SetVolatility(double volatility)
	{
		m_volatility = volatility;
	}

	double PriceGenerator::GetVolatility() const
	{
		return m_volatility;
	}

#if 1
	void PriceGenerator::GetPrice(Price& quote)
	{
		int trendChance = (m_trendChance + 2); //[2,12]
		int trendSplit = (trendChance/2 - 1);

		if(--m_trendCounter < 0)
		{
			m_bullish = (::rand() % trendChance) > trendSplit;
			m_trendCounter = ::rand() % m_trendFragmentation;
		}
		
		double sign = (m_bullish == true ? 1 : -1);
		double pip2rate = 1 / m_rate2pip;
		double volatility = ::rand() % (int)(m_volatility * 10);
		volatility /= 10;

		m_buy += sign * volatility * pip2rate;
		quote = Price(m_buy, m_buy - m_spread * pip2rate);
		
		--m_trendCounter;
	}
#endif

#if 0
	void PriceGenerator::GetPrice(Price& quote)
	{
		const size_t count=21;
		double tab[count] = {
			1.08000,
			1.08020,
			1.08060,
			1.08080,
			1.08120,
			1.08080,
			1.08000,
			1.07920,
			1.07980,
			1.08000,
			1.08020,
			1.08060,
			1.08080,
			1.08120,
			1.08080,
			1.08000,
			1.07920,
			1.07980,
			1.08000,
			1.08020,
			1.08060
		}; // 188-208

		static int sCounter = 0;
		if(sCounter >= count) sCounter = 0;
		double buy = tab[sCounter];
		double sell = buy - m_spread * (1/m_rate2pip);
		quote = Price(buy, sell);
		sCounter ++;
	}
#endif

} // namespace

