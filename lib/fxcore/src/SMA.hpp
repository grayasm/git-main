/*
	Copyright (C) 2017 Mihai Vasilian

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
		typedef std::list<fx::Offer>	OfferList;
		typedef time_t					Timeframe;

		enum PriceOrigin
		{
			PRICE_CLOSE=0,
			PRICE_OPEN
		};

		SMA();
		SMA(int period, PriceOrigin po, Timeframe sec);
		~SMA();

		SMA(const SMA& tc);
		SMA& operator=(const SMA& tc);

		//! true if it can calculate the average for the given period
		bool IsValid() const; 

		//! complete the timeframe period and update current average
		void Update(const fx::Offer& offer);

		//! return current average
		void GetValue(fx::Price& average);

	private:
		void Init();

	private:
		int				m_period;
		PriceOrigin		m_priceOrigin;
		Timeframe		m_timeframe;
		OfferList		m_offerList;
		fx::Offer		m_lastOffer;
		fx::Price		m_lastSum;
	};
} // namespace

#endif // __SMA_hpp__

