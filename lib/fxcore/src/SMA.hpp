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

#ifndef __SMA_hpp__
#define __SMA_hpp__

#include <list>
#include "Offer.hpp"
#include "Price.hpp"


namespace fx
{
	class SMA
	{
	public:
		typedef std::list<fx::Price>	PriceList;
		typedef time_t					Timeframe;

		enum PriceOrigin
		{
			PRICE_OPEN = 0,
			PRICE_CLOSE
		};

		SMA();
		SMA(const misc::string& instrument, int period, Timeframe sec, PriceOrigin po);
		~SMA();

		SMA(const SMA& tc);
		SMA& operator=(const SMA& tc);

		const misc::string& GetInstrument() const;
		int GetPeriod() const;
		Timeframe GetTimeframe() const;
		PriceOrigin GetPriceOrigin() const;

		bool IsValid() const; 
		void Update(const fx::Offer& offer);
		void GetValue(fx::Price& average) const;
		const misc::time& GetRefTime() const; // begin of current timeframe

	private:
		void Init();

	private:
		misc::string	m_instrument;
		int				m_period;		
		Timeframe		m_timeframe;
		PriceOrigin		m_priceOrigin;
		// ---------------------
		misc::time		m_reftime;
		fx::Price		m_priceO;
		fx::Price		m_priceC;
		PriceList		m_offerList;
		fx::Price		m_lastSum;
	};
} // namespace

#endif // __SMA_hpp__

