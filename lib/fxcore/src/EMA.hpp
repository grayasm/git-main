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
#include "IND.hpp"
#include "SMA.hpp"
#include "BARB.hpp"
#include "Offer.hpp"
#include "Price.hpp"



namespace fx
{
	class EMA : public IND
	{
	public:
		typedef fx::SMA::BarType			BarType;
		typedef fx::SMA::PriceOrigin		PriceOrigin;
		typedef std::list<fx::Price>		EMAList;
		// Timeframe is time_t
		
		EMA();
		EMA(const misc::string& instrument,
			int period,
			Timeframe sec,
			BarType barType,
			PriceOrigin po);
		~EMA();

		EMA(const EMA& tc);
		EMA& operator=(const EMA& tc);

		// --- virtual table ---
		const misc::string& GetInstrument() const override;
		int GetPeriod() const override;
		Timeframe GetTimeframe() const override;
		bool IsValid() const override;
		void Update(const fx::Offer& offer) override;
		const misc::time& GetRefTime() const override;
		// --- end of virtual table ---

		PriceOrigin GetPriceOrigin() const;
		void GetValue(fx::Price& average) const;

	private:
		void Init();

	private:
		misc::string	m_instrument;
		int				m_period;
		Timeframe		m_timeframe;
		BarType			m_barType;
        PriceOrigin     m_priceOrigin;
		double			m_multiplier;
		// -----------------------
		fx::BARB*		m_bar;
		fx::SMA			m_firstSMA;
		fx::Price		m_currEMA;
		EMAList			m_emaList;
	};
} // namespace

#endif // __EMA_hpp__

