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

#ifndef __EMA_hpp__
#define __EMA_hpp__

#include <list>
#include "SMA.hpp"
#include "Offer.hpp"
#include "Price.hpp"



namespace fx
{
	class EMA
	{
	public:
		typedef time_t						Timeframe;
		typedef fx::SMA::PriceOrigin		PriceOrigin;
		typedef std::list<fx::Price>		EMAList;
		
		EMA();
		EMA(const misc::string& instrument, int period, Timeframe sec, PriceOrigin po);
		~EMA();

		EMA(const EMA& tc);
		EMA& operator=(const EMA& tc);

		const misc::string& GetInstrument() const;
		int GetPeriod() const;
		Timeframe GetTimeframe() const;
		PriceOrigin GetPriceOrigin() const;

		bool IsValid() const; 
		void Update(const fx::Offer& offer);
		void GetValue(fx::Price& average) const;

	private:
		void Init();

	private:
		misc::string	m_instrument;
		int				m_period;
		Timeframe		m_timeframe;
		double			m_multiplier;
		fx::SMA			m_firstSMA;
		fx::Offer		m_lastOffer;
		EMAList			m_emaList;
		fx::Price		m_currEMA;
		
	};
} // namespace

#endif // __EMA_hpp__

