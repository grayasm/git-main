/*
  Copyright (C) 2015 Mihai Vasilian

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

#ifndef __FixGridPositionStub_hpp__
#define __FixGridPositionStub_hpp__


#include "Transaction.hpp"
#include "MarketDummyPlugin.hpp"


namespace fx
{
	class Serializer;
	class Deserializer;
	class StrategyHedgeFixGrid;
	class Strategy2HedgeFixGrid;
	class StrategyFixGrid;
	class Strategy2FixGrid;

	//##########################################################################
	/*	This class takes care of one position in the grid.
	 *	It opens or closes the corresponding position as needed.	
	 */
	class FixGridPositionStub
	{
	public:
		typedef misc::autoptr<FixGridPositionStub> Ptr;
		friend class Serializer;
		friend class Deserializer;
		friend class StrategyHedgeFixGrid;
		friend class Strategy2HedgeFixGrid;
		friend class StrategyFixGrid;
		friend class Strategy2FixGrid;

	public:
		FixGridPositionStub();
		~FixGridPositionStub();
		FixGridPositionStub(const FixGridPositionStub& tc);
		FixGridPositionStub& operator=(const FixGridPositionStub& tc);

		FixGridPositionStub(
			const fx::Position& gp,			// fix grid's hedge position to be monitored
			double de,						// distance to exit
			MarketPlugin::Ptr plugin,		// market execution plugin
			fx::Transaction* ct				// parent transaction
			);

		bool Update(const Price& rate);
		bool IsActive() const;


	private:
		void Reset();
		void Validate();
		bool CanOpenOrder();
		bool OpenOrder();
		bool CanCloseOrder();
		bool CloseOrder();

	private:
		fx::Position		m_gp;				// grid position to be monitored
		double				m_de;				// distance to exit
		MarketPlugin::Ptr	m_plugin;			// market execution plugin
		fx::Transaction*	m_ct;				// parent transaction with all opened and closed positions at any time
		fx::Transaction		m_gt;				// all positions opened for this grid position (liquidity)
		fx::Price			m_rate;				// current price
	};	
}  // namespace

#endif // __FixGridPositionStub_hpp__

