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

#ifndef __StrategyCrossOver_hpp__
#define __StrategyCrossOver_hpp__


#include "autoptr.hpp"
#include "Offer.hpp"
#include "Position.hpp"
#include "Transaction.hpp"
#include "MarketPlugin.hpp"



namespace fx
{
	class StrategyCrossOver
	{
	public:
		typedef misc::autoptr<StrategyCrossOver> Ptr;

		StrategyCrossOver(
			fx::MarketPlugin* plugin,
			const misc::string& instrument);

		~StrategyCrossOver();
		StrategyCrossOver(const StrategyCrossOver&) = delete;
		StrategyCrossOver& operator=(const StrategyCrossOver&) = delete;

		void Update(const fx::Offer& offer);
		bool IsCancelled() const;
		double GetClosedGPL() const;

	private:
		void OpenPosition(const fx::Offer& offer, bool buy);
		void ClosePosition(const fx::Offer& offer);
		void InitializeEMA(const fx::Offer& offer);
		void InitializeSMA(const fx::Offer& offer);
		void SetValidMarketTime(misc::time& tend, time_t& interval) const;

	private:
		fx::MarketPlugin*		m_plugin;
		misc::string			m_instrument;
		/// -------------------------------
		fx::Transaction			m_tr;
		bool					m_isCancelled;
		double					m_closedGPL;
	};
} // namespace

#endif // __StrategyCrossOver_hpp__
