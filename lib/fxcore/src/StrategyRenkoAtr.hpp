/*
	Copyright (C) 2018 Mihai Vasilian

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

#ifndef __StrategyRenkoAtr_hpp__
#define __StrategyRenkoAtr_hpp__


#include "autoptr.hpp"
#include "Offer.hpp"
#include "Position.hpp"
#include "Transaction.hpp"
#include "MarketPlugin.hpp"
#include "Range.hpp"
#include "ATR.hpp"
#include "SMA.hpp"



namespace fx
{
	class StrategyRenkoAtr
	{
	public:
		typedef misc::autoptr<StrategyRenkoAtr> Ptr;

		StrategyRenkoAtr(
			fx::MarketPlugin* plugin,
			const misc::string& instrument,
			double renkoMinValue,
			int atrPeriod, time_t atrTimeframe,
			int smaPeriod, time_t smaTimeframe, fx::SMA::PriceOrigin po,
			int openHour, int closeHour);
		~StrategyRenkoAtr();
		StrategyRenkoAtr(const StrategyRenkoAtr& tc) = delete;
		StrategyRenkoAtr& operator=(const StrategyRenkoAtr& tc) = delete;

		void Update(const fx::Offer& offer);
		bool IsCanceled() const;

	private:
		fx::MarketPlugin*		m_plugin;
		misc::string			m_instrument;
		double					m_renkoMinValue;	// ex: PL=15 
		int						m_atrPeriod;
		time_t					m_atrTimeframe;
		int						m_smaPeriod;
		time_t					m_smaTimeframe;
		fx::SMA::PriceOrigin	m_smaPriceOrigin;
		int						m_openHour;
		int						m_closeHour;
		fx::ATR					m_atr;
		fx::SMA					m_sma;
		double					m_renkoPL;
		bool					m_canOpen;
		fx::Transaction			m_transaction;				
	};
} // namespace


#endif // __StrategyRenkoAtr_hpp__
