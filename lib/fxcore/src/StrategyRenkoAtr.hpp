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
		typedef stl::autoptr<StrategyRenkoAtr> Ptr;

		StrategyRenkoAtr(
			fx::MarketPlugin* plugin,
			const stl::string& instrument,
			double renkoMin,
			int openHour,
			int closeHour);

		~StrategyRenkoAtr();
		StrategyRenkoAtr(const StrategyRenkoAtr& tc) = delete;
		StrategyRenkoAtr& operator=(const StrategyRenkoAtr& tc) = delete;

		void Update(const fx::Offer& offer);
		bool IsCancelled() const;
		double GetClosedPL() const;
		double GetClosedGPL() const;

	private:
		void OpenPosition(const fx::Offer& offer, bool buy);
		void ClosePosition(const fx::Offer& offer);
		void BuildAllIndicators(const fx::Offer& offer);

	private:
		fx::MarketPlugin*		m_plugin;
		stl::string			m_instrument;
		double					m_renkoMin;	// ex: PL=15 
		fx::ATR					m_atr14;
		fx::SMA					m_sma7;
		/// --------------------------
		fx::Transaction			m_tr;
		fx::Offer				m_initialOffer;
		fx::Range				m_range;
		double					m_totalPL;
		double					m_closedPL;
		double					m_closedGPL;
		int						m_openHour;
		int						m_closeHour;
		bool					m_isCancelled;
		
		
		

		

	};
} // namespace


#endif // __StrategyRenkoAtr_hpp__
