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

#ifndef __PSAR_hpp__
#define __PSAR_hpp__

#include <list>
#include "string.hpp"
#include "IND.hpp"
#include "Price.hpp"
#include "OHLCPrice.hpp"



namespace fx
{
	class PSAR : public IND
	{
	public:
		PSAR();
		PSAR(const misc::string& instrument,
			Timeframe sec,
			bool buy,
			const fx::Price& sar);

		~PSAR();
		PSAR(const PSAR& tc);
		PSAR& operator=(const PSAR& tc);

		// --- virtual table ---
		const misc::string& GetInstrument() const override;
		int GetPeriod() const override;
		Timeframe GetTimeframe() const override;
		bool IsValid() const override;
		void Update(const fx::Offer& offer) override;
		const misc::time& GetRefTime() const override;
		// --- end of virtual table ---


	private:
		void Init();

	private:
		misc::string	m_instrument;
		Timeframe		m_timeframe;
		bool			m_buy;
		double			m_AF;
		fx::Price		m_SAR;
		// --------------------
		misc::time		m_reftime;
		fx::OHLCPrice	m_ohlc[2];
		fx::Price		m_EP;
		
	};
} // namespace

#endif // __PSAR_hpp__
