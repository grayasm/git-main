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
#include "IND.hpp"
#include "BAR.hpp"
#include "HABAR.hpp"
#include "Offer.hpp"
#include "Price.hpp"



namespace fx
{
	class SMA : public IND
	{
	public:
		typedef stl::autoptr<SMA>		Ptr;
		typedef std::list<fx::Price>	PriceList;
		// Timeframe is time_t

		enum BarType
		{
			BT_BAR = 0,
			BT_HABAR
		};

		enum PriceOrigin
		{
			PRICE_OPEN = 0,
			PRICE_CLOSE
		};

		SMA();
		SMA(const stl::string& instrument,
			int period,
			Timeframe sec,
			BarType barType,
			PriceOrigin po);
		~SMA();

		SMA(const SMA& tc);
		SMA& operator=(const SMA& tc);

		// --- virtual table ---
		const stl::string& GetInstrument() const override;
		int GetPeriod() const override;
		Timeframe GetTimeframe() const override;
		bool IsValid() const override;
		void Update(const fx::Offer& offer) override;
		const sys::time& GetRefTime() const override;
		// --- end of virtual table ---

		PriceOrigin GetPriceOrigin() const;
		void GetValue(fx::Price& average) const;

	private:
		void Init();

	private:
		stl::string	m_instrument;
		int				m_period;		
		Timeframe		m_timeframe;
		BarType			m_barType;
		PriceOrigin		m_priceOrigin;		
		// ---------------------
		fx::BARB*		m_bar;
		fx::Price		m_sumMinus1P;
	};
} // namespace

#endif // __SMA_hpp__

