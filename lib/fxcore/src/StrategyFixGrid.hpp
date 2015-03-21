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


#ifndef __StrategyFixGrid_hpp__
#define __StrategyFixGrid_hpp__


#include "StrategyHedgeFixGrid.hpp"


namespace fx
{
	//##########################################################################
	/*
	 *	We enter the market at its price (Buy or Sell Market Order), or wait
	 *	until it bounces over the entry level (optional).	 
	 *	The entry is also the first position of the grid.
	 *	In the grid, all positions are displaced at equal distance.
	 *	Each position is opened when the market reaches its calculated price,
	 *	and is closed in negative at the distance to exit.
	 *	If the price reacts positive and reaches again the grid position
	 *	it will be opened again.
	 *
	 *	The draw down limit is established for total grid size: 50k, -20pips = -1000 pips
	 *	and the strategy stops when all closed and open positions have in total 
	 *	this PL number.
	 *	
	 *	The profit limit is established for total grid size: 30k, +10pips = +300 pips
	 *	and the strategy stops when all closed and open positions have in total
	 *	this PL number.
	 *	
	 *	        [profit]
	 *
	 *
	 *	           |
	 *	          ...
	 *	  [grid buy positions]
	 *	          ...
	 *	           |
	 *	        o-buy-o   [entry]
	 *	           |
	 *	        x-sell-x  [exit]
	 */
	class StrategyFixGrid : public StrategyBase
	{
	public:
		typedef misc::autoptr<StrategyFixGrid> Ptr;
		friend class Serializer;
		friend class Deserializer;

		StrategyFixGrid();
		StrategyFixGrid(const StrategyFixGrid& tc);
		StrategyFixGrid& operator=(const StrategyFixGrid& tc);

		StrategyFixGrid(
			const fx::Position& ep,		// where to enter the market and total grid size
			bool wait,					// wait until price bounces over the entry
			double dg,					// distance of the grid in pips
			double pa,					// amount of each position in the grid
			double de,					// distance to exit for each position in the grid
			double maxn,				// maxim negative - total draw down for total grid amount
			double maxp,				// maxim positive - total profit for total grid amount
			MarketPlugin::Ptr plugin	// market execution plugin
			);

		~StrategyFixGrid();

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
		bool CanCreateGrid();
		bool CreateGrid();
		bool UpdateGrid();
		bool ShowStatus();
		bool BlockTransaction();
		bool CloseTransaction();


	private:
		fx::Position		m_ep;		// entry price and total grid amount
		bool				m_wait;		// open entry at market when price bounces over entry
		double				m_dg;		// distance of the grid in pips
		double				m_pa;		// amount of each position in grid
		double				m_de;		// distance to exit for each grid position
		double				m_maxn;		// maxim negative - total draw down for total grid amount
		double				m_maxp;		// maxim positive - total profit for total grid amount
		MarketPlugin::Ptr	m_plugin;	// market execution plugin

		fx::Transaction		m_ct;		// current transaction
		fx::Price			m_rate;		// latest updated price
		fx::Price			m_prev_rate;// previous price value
		typedef misc::vector<FixGridPositionStub::Ptr> Grid;
		Grid				m_grid;
		bool				m_blocked;	// closed in profit or blocked at loss
	};
} // namespace

#endif // __StrategyFixGrid_hpp__