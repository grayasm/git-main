/*
  Copyright (C) 2014 Mihai Vasilian

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



#ifndef __Strategy2HedgeFixGrid_hpp__
#define __Strategy2HedgeFixGrid_hpp__


#include "StrategyBase.hpp"
#include "FixGridPositionStub.hpp"

namespace fx
{
	/*	This strategy is very similar with StrategyHedgeFixGrid.
	 *	Summary:
	 *	We enter the market at its price or wait until the price bounces over
	 *	the level required by entry position.
	 *	We open 2 market orders, same amount from entry position (a hedge).
	 *	Below and Above the 2 entries at the distance to the first hedge
	 *	position starts the 2 grids.
	 *	
	 *	The grid operates the same as for StrategyHedgeFixGrid.
	 *	
	 *	The draw down limit is established for entry position: 50k, -20pips = -1000 pips
	 *	and the strategy stops when all closed and open positions have in total 
	 *	this PL number.
	 *	
	 *	The profit limit is established for entry position: 30k, +10pips = +300 pips
	 *	and the strategy stop when all closed and open positions have in total
	 *	this PL number.
	 *	
	 *	       x
	 *	       x   [grid]
	 *	       x
	 *	       |
	 *	       |
	 *	       |
	 *	       |
	 *	     o-buy--o [MO] entry level
	 *	     o-sell-o [MO] entry level
	 *	       |
	 *	       |
	 *	       |
	 *	       |
	 *	       x
	 *	       x   [grid]
	 *	       x
	 */
	class Strategy2HedgeFixGrid : public StrategyBase
	{
	public:
		typedef misc::autoptr<Strategy2HedgeFixGrid> Ptr;
		friend class Serializer;
		friend class Deserializer;

		Strategy2HedgeFixGrid();
		~Strategy2HedgeFixGrid();
		Strategy2HedgeFixGrid(const Strategy2HedgeFixGrid& tc);
		Strategy2HedgeFixGrid& operator=(const Strategy2HedgeFixGrid& tc);

		Strategy2HedgeFixGrid(
			const fx::Position& ep,				// entry position - where to enter the market
			bool wait,							// wait until price bounces over the entry
			double dh,							// distance from entry to first hedge in pips
			double dg,							// distance of the grid in pips
			double ha,							// hedge amount for each position in the grid
			double de,							// distance to exit for each hedge in the grid
			double maxn,						// maxim negative - total draw down for entry position (100k, -20pips)
			double maxp,						// maxim positive - total profit for entry position (100k, +20pips)
			MarketPlugin::Ptr plugin			// market execution plugin
			);

		// --- virtual table ---
		void AcceptVisitor(StrategyVisitor& visitor);
		bool Update(const Price& rate);
		double GetPL() const;
		double GetGPL() const;
		bool ReInit();
		// --- end of virtual ---

		misc::string ToString() const;
	
	private:
		//! Reset entire content
		void Reset();
		void Validate();

		bool CanEnterMarket();
		bool EnterMarket();		
		bool CanCreateGrid();
		bool CreateGrid();
		bool UpdateGrid();
		bool ShowStatus();
		bool BlockTransaction();
		bool CloseTransaction();


	protected:
		fx::Position		m_ep;	// entry position		
		bool				m_wait;	// open entry at market when price bounces over entry
		double				m_dh;	// distance from entry to first hedge in pips
		double				m_dg;	// distance of the grid in pips
		double				m_ha;	// hedge amount for each position in the grid
		double				m_de;	// distance to exit for each hedge in the grid
		double				m_maxn;	// maxim negative - total pips as max allowed to be consumed
		double				m_maxp;	// maxim positive - close in profit entire strategy
		MarketPlugin::Ptr	m_plugin; // market execution plugin

		fx::Transaction		m_ct;		// current transaction
		fx::Price			m_enter;	// average price of all trades (liquidity) when entered the market
		fx::Price			m_rate;		// latest updated price
		fx::Price			m_prev_rate;// previous price value
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				m_grid;
		bool				m_blocked;	// closed in profit, blocked at loss

	};

} // namespace


#endif // __Strategy2HedgeFixGrid_hpp__